/*
 * Copyright (C) 2011 Apple Inc. All rights reserved.
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
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef TextTrackLoader_h
#define TextTrackLoader_h

#include "core/html/track/vtt/VTTParser.h"
#include "platform/CrossOriginAttributeValue.h"
#include "platform/heap/Handle.h"
#include "platform/loader/fetch/RawResource.h"
#include "platform/loader/fetch/ResourceOwner.h"

namespace blink {

class Document;
class TextTrackLoader;

class TextTrackLoaderClient : public GarbageCollectedMixin {
 public:
  virtual ~TextTrackLoaderClient() {}

  virtual void newCuesAvailable(TextTrackLoader*) = 0;
  virtual void cueLoadingCompleted(TextTrackLoader*, bool loadingFailed) = 0;
};

class TextTrackLoader final : public GarbageCollectedFinalized<TextTrackLoader>,
                              public ResourceOwner<RawResource>,
                              private VTTParserClient {
  USING_GARBAGE_COLLECTED_MIXIN(TextTrackLoader);

 public:
  static TextTrackLoader* create(TextTrackLoaderClient& client,
                                 Document& document) {
    return new TextTrackLoader(client, document);
  }
  ~TextTrackLoader() override;

  bool load(const KURL&, CrossOriginAttributeValue);
  void cancelLoad();

  enum State { Idle, Loading, Finished, Failed };
  State loadState() { return m_state; }

  void getNewCues(HeapVector<Member<TextTrackCue>>& outputCues);

  DECLARE_TRACE();

 private:
  // RawResourceClient
  bool redirectReceived(Resource*,
                        const ResourceRequest&,
                        const ResourceResponse&) override;
  void dataReceived(Resource*, const char* data, size_t length) override;
  void notifyFinished(Resource*) override;
  String debugName() const override { return "TextTrackLoader"; }

  // VTTParserClient
  void newCuesParsed() override;
  void fileFailedToParse() override;

  TextTrackLoader(TextTrackLoaderClient&, Document&);

  void cueLoadTimerFired(TimerBase*);
  void corsPolicyPreventedLoad(SecurityOrigin*, const KURL&);

  Document& document() const { return *m_document; }

  Member<TextTrackLoaderClient> m_client;
  Member<VTTParser> m_cueParser;
  // FIXME: Remove this pointer and get the Document from m_client.
  Member<Document> m_document;
  TaskRunnerTimer<TextTrackLoader> m_cueLoadTimer;
  State m_state;
  bool m_newCuesAvailable;
};

}  // namespace blink

#endif
