/*
 * Copyright (C) 2009 Google Inc. All Rights Reserved.
 *           (C) 2008 Apple Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY GOOGLE INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL GOOGLE INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "modules/storage/StorageArea.h"

#include "bindings/core/v8/ExceptionState.h"
#include "core/dom/Document.h"
#include "core/dom/ExceptionCode.h"
#include "core/frame/LocalDOMWindow.h"
#include "core/frame/LocalFrame.h"
#include "core/page/Page.h"
#include "modules/storage/DOMWindowStorage.h"
#include "modules/storage/InspectorDOMStorageAgent.h"
#include "modules/storage/Storage.h"
#include "modules/storage/StorageClient.h"
#include "modules/storage/StorageEvent.h"
#include "modules/storage/StorageNamespace.h"
#include "modules/storage/StorageNamespaceController.h"
#include "platform/weborigin/SecurityOrigin.h"
#include "public/platform/WebStorageArea.h"
#include "public/platform/WebString.h"
#include "public/platform/WebURL.h"
#include <memory>

namespace blink {

StorageArea* StorageArea::create(std::unique_ptr<WebStorageArea> storageArea,
                                 StorageType storageType) {
  return new StorageArea(std::move(storageArea), storageType);
}

StorageArea::StorageArea(std::unique_ptr<WebStorageArea> storageArea,
                         StorageType storageType)
    : m_storageArea(std::move(storageArea)),
      m_storageType(storageType),
      m_frameUsedForCanAccessStorage(nullptr),
      m_canAccessStorageCachedResult(false) {}

StorageArea::~StorageArea() {}

DEFINE_TRACE(StorageArea) {
  visitor->trace(m_frameUsedForCanAccessStorage);
}

unsigned StorageArea::length(ExceptionState& exceptionState,
                             LocalFrame* frame) {
  if (!canAccessStorage(frame)) {
    exceptionState.throwSecurityError("access is denied for this document.");
    return 0;
  }
  return m_storageArea->length();
}

String StorageArea::key(unsigned index,
                        ExceptionState& exceptionState,
                        LocalFrame* frame) {
  if (!canAccessStorage(frame)) {
    exceptionState.throwSecurityError("access is denied for this document.");
    return String();
  }
  return m_storageArea->key(index);
}

String StorageArea::getItem(const String& key,
                            ExceptionState& exceptionState,
                            LocalFrame* frame) {
  if (!canAccessStorage(frame)) {
    exceptionState.throwSecurityError("access is denied for this document.");
    return String();
  }
  return m_storageArea->getItem(key);
}

void StorageArea::setItem(const String& key,
                          const String& value,
                          ExceptionState& exceptionState,
                          LocalFrame* frame) {
  if (!canAccessStorage(frame)) {
    exceptionState.throwSecurityError("access is denied for this document.");
    return;
  }
  WebStorageArea::Result result = WebStorageArea::ResultOK;
  m_storageArea->setItem(key, value, frame->document()->url(), result);
  if (result != WebStorageArea::ResultOK)
    exceptionState.throwDOMException(
        QuotaExceededError,
        "Setting the value of '" + key + "' exceeded the quota.");
}

void StorageArea::removeItem(const String& key,
                             ExceptionState& exceptionState,
                             LocalFrame* frame) {
  if (!canAccessStorage(frame)) {
    exceptionState.throwSecurityError("access is denied for this document.");
    return;
  }
  m_storageArea->removeItem(key, frame->document()->url());
}

void StorageArea::clear(ExceptionState& exceptionState, LocalFrame* frame) {
  if (!canAccessStorage(frame)) {
    exceptionState.throwSecurityError("access is denied for this document.");
    return;
  }
  m_storageArea->clear(frame->document()->url());
}

bool StorageArea::contains(const String& key,
                           ExceptionState& exceptionState,
                           LocalFrame* frame) {
  if (!canAccessStorage(frame)) {
    exceptionState.throwSecurityError("access is denied for this document.");
    return false;
  }
  return !getItem(key, exceptionState, frame).isNull();
}

bool StorageArea::canAccessStorage(LocalFrame* frame) {
  if (!frame || !frame->page())
    return false;

  // Should the LocalFrame die before this StorageArea does,
  // that cached reference will be cleared.
  if (m_frameUsedForCanAccessStorage == frame)
    return m_canAccessStorageCachedResult;
  StorageNamespaceController* controller =
      StorageNamespaceController::from(frame->page());
  if (!controller)
    return false;
  bool result =
      controller->getStorageClient()->canAccessStorage(frame, m_storageType);
  // Move attention to the new LocalFrame.
  m_frameUsedForCanAccessStorage = frame;
  m_canAccessStorageCachedResult = result;
  return result;
}

void StorageArea::dispatchLocalStorageEvent(
    const String& key,
    const String& oldValue,
    const String& newValue,
    SecurityOrigin* securityOrigin,
    const KURL& pageURL,
    WebStorageArea* sourceAreaInstance) {
  // Iterate over all pages that have a StorageNamespaceController supplement.
  for (Page* page : Page::ordinaryPages()) {
    for (Frame* frame = page->mainFrame(); frame;
         frame = frame->tree().traverseNext()) {
      // FIXME: We do not yet have a way to dispatch events to out-of-process
      // frames.
      if (!frame->isLocalFrame())
        continue;
      LocalFrame* localFrame = toLocalFrame(frame);
      LocalDOMWindow* localWindow = localFrame->domWindow();
      Storage* storage =
          DOMWindowStorage::from(*localWindow).optionalLocalStorage();
      if (storage &&
          localFrame->document()->getSecurityOrigin()->canAccess(
              securityOrigin) &&
          !isEventSource(storage, sourceAreaInstance))
        localFrame->domWindow()->enqueueWindowEvent(
            StorageEvent::create(EventTypeNames::storage, key, oldValue,
                                 newValue, pageURL, storage));
    }
    if (InspectorDOMStorageAgent* agent =
            StorageNamespaceController::from(page)->inspectorAgent())
      agent->didDispatchDOMStorageEvent(key, oldValue, newValue, LocalStorage,
                                        securityOrigin);
  }
}

static Page* findPageWithSessionStorageNamespace(
    const WebStorageNamespace& sessionNamespace) {
  // Iterate over all pages that have a StorageNamespaceController supplement.
  for (Page* page : Page::ordinaryPages()) {
    const bool dontCreateIfMissing = false;
    StorageNamespace* storageNamespace =
        StorageNamespaceController::from(page)->sessionStorage(
            dontCreateIfMissing);
    if (storageNamespace && storageNamespace->isSameNamespace(sessionNamespace))
      return page;
  }
  return nullptr;
}

void StorageArea::dispatchSessionStorageEvent(
    const String& key,
    const String& oldValue,
    const String& newValue,
    SecurityOrigin* securityOrigin,
    const KURL& pageURL,
    const WebStorageNamespace& sessionNamespace,
    WebStorageArea* sourceAreaInstance) {
  Page* page = findPageWithSessionStorageNamespace(sessionNamespace);
  if (!page)
    return;

  for (Frame* frame = page->mainFrame(); frame;
       frame = frame->tree().traverseNext()) {
    // FIXME: We do not yet have a way to dispatch events to out-of-process
    // frames.
    if (!frame->isLocalFrame())
      continue;
    LocalFrame* localFrame = toLocalFrame(frame);
    LocalDOMWindow* localWindow = localFrame->domWindow();
    Storage* storage =
        DOMWindowStorage::from(*localWindow).optionalSessionStorage();
    if (storage &&
        localFrame->document()->getSecurityOrigin()->canAccess(
            securityOrigin) &&
        !isEventSource(storage, sourceAreaInstance))
      localFrame->domWindow()->enqueueWindowEvent(StorageEvent::create(
          EventTypeNames::storage, key, oldValue, newValue, pageURL, storage));
  }
  if (InspectorDOMStorageAgent* agent =
          StorageNamespaceController::from(page)->inspectorAgent())
    agent->didDispatchDOMStorageEvent(key, oldValue, newValue, SessionStorage,
                                      securityOrigin);
}

bool StorageArea::isEventSource(Storage* storage,
                                WebStorageArea* sourceAreaInstance) {
  ASSERT(storage);
  StorageArea* area = storage->area();
  return area->m_storageArea.get() == sourceAreaInstance;
}

}  // namespace blink
