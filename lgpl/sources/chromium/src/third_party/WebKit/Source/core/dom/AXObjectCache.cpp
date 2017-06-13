/*
 * Copyright (C) 2008, 2009, 2010 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 * 3.  Neither the name of Apple Computer, Inc. ("Apple") nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE AND ITS CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL APPLE OR ITS CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "core/dom/AXObjectCache.h"

#include "wtf/PtrUtil.h"
#include <memory>

namespace blink {

AXObjectCache::AXObjectCacheCreateFunction AXObjectCache::m_createFunction =
    nullptr;

void AXObjectCache::init(AXObjectCacheCreateFunction function) {
  DCHECK(!m_createFunction);
  m_createFunction = function;
}

AXObjectCache* AXObjectCache::create(Document& document) {
  DCHECK(m_createFunction);
  return m_createFunction(document);
}

AXObjectCache::AXObjectCache() {}

AXObjectCache::~AXObjectCache() {}

std::unique_ptr<ScopedAXObjectCache> ScopedAXObjectCache::create(
    Document& document) {
  return WTF::wrapUnique(new ScopedAXObjectCache(document));
}

ScopedAXObjectCache::ScopedAXObjectCache(Document& document)
    : m_document(&document) {
  if (!m_document->axObjectCache())
    m_cache = AXObjectCache::create(*m_document);
}

ScopedAXObjectCache::~ScopedAXObjectCache() {
  if (m_cache)
    m_cache->dispose();
}

AXObjectCache* ScopedAXObjectCache::get() {
  if (m_cache)
    return m_cache.get();
  AXObjectCache* cache = m_document->axObjectCache();
  DCHECK(cache);
  return cache;
}

}  // namespace blink
