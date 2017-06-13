/*
 * Copyright (C) 2011 Google Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef ResourceLoaderOptions_h
#define ResourceLoaderOptions_h

#include "platform/CrossThreadCopier.h"
#include "platform/loader/fetch/FetchInitiatorInfo.h"
#include "platform/loader/fetch/IntegrityMetadata.h"
#include "platform/weborigin/SecurityOrigin.h"
#include "wtf/Allocator.h"

namespace blink {

enum DataBufferingPolicy { BufferData, DoNotBufferData };

enum ContentSecurityPolicyDisposition {
  CheckContentSecurityPolicy,
  DoNotCheckContentSecurityPolicy
};

enum RequestInitiatorContext {
  DocumentContext,
  WorkerContext,
};

enum StoredCredentials { AllowStoredCredentials, DoNotAllowStoredCredentials };

// APIs like XMLHttpRequest and EventSource let the user decide whether to send
// credentials, but they're always sent for same-origin requests. Additional
// information is needed to handle cross-origin redirects correctly.
enum CredentialRequest {
  ClientRequestedCredentials,
  ClientDidNotRequestCredentials
};

enum SynchronousPolicy { RequestSynchronously, RequestAsynchronously };

// A resource fetch can be marked as being CORS enabled. The loader must perform
// an access check upon seeing the response.
enum CORSEnabled { NotCORSEnabled, IsCORSEnabled };

// Was the request generated from a "parser-inserted" element?
// https://html.spec.whatwg.org/multipage/scripting.html#parser-inserted
enum ParserDisposition { ParserInserted, NotParserInserted };

enum CacheAwareLoadingEnabled {
  NotCacheAwareLoadingEnabled,
  IsCacheAwareLoadingEnabled
};

struct ResourceLoaderOptions {
  USING_FAST_MALLOC(ResourceLoaderOptions);

 public:
  ResourceLoaderOptions()
      : dataBufferingPolicy(BufferData),
        allowCredentials(DoNotAllowStoredCredentials),
        credentialsRequested(ClientDidNotRequestCredentials),
        contentSecurityPolicyOption(CheckContentSecurityPolicy),
        requestInitiatorContext(DocumentContext),
        synchronousPolicy(RequestAsynchronously),
        corsEnabled(NotCORSEnabled),
        parserDisposition(ParserInserted),
        cacheAwareLoadingEnabled(NotCacheAwareLoadingEnabled) {}

  ResourceLoaderOptions(
      DataBufferingPolicy dataBufferingPolicy,
      StoredCredentials allowCredentials,
      CredentialRequest credentialsRequested,
      ContentSecurityPolicyDisposition contentSecurityPolicyOption,
      RequestInitiatorContext requestInitiatorContext)
      : dataBufferingPolicy(dataBufferingPolicy),
        allowCredentials(allowCredentials),
        credentialsRequested(credentialsRequested),
        contentSecurityPolicyOption(contentSecurityPolicyOption),
        requestInitiatorContext(requestInitiatorContext),
        synchronousPolicy(RequestAsynchronously),
        corsEnabled(NotCORSEnabled),
        parserDisposition(ParserInserted),
        cacheAwareLoadingEnabled(NotCacheAwareLoadingEnabled) {}

  // Answers the question "can a separate request with these different options
  // be re-used" (e.g. preload request) The safe (but possibly slow) answer is
  // always false.
  bool canReuseRequest(const ResourceLoaderOptions& other) const {
    // dataBufferingPolicy differences are believed to be safe for re-use.
    // FIXME: check allowCredentials.
    // FIXME: check credentialsRequested.
    // FIXME: check contentSecurityPolicyOption.
    // initiatorInfo is purely informational and should be benign for re-use.
    // requestInitiatorContext is benign (indicates document vs. worker)
    if (synchronousPolicy != other.synchronousPolicy)
      return false;
    return corsEnabled == other.corsEnabled;
    // securityOrigin has more complicated checks which callers are responsible
    // for.
  }

  // When adding members, CrossThreadResourceLoaderOptionsData should be
  // updated.
  DataBufferingPolicy dataBufferingPolicy;

  // Whether HTTP credentials and cookies are sent with the request.
  StoredCredentials allowCredentials;

  // Whether the client (e.g. XHR) wanted credentials in the first place.
  CredentialRequest credentialsRequested;

  ContentSecurityPolicyDisposition contentSecurityPolicyOption;
  FetchInitiatorInfo initiatorInfo;
  RequestInitiatorContext requestInitiatorContext;
  SynchronousPolicy synchronousPolicy;

  // If the resource is loaded out-of-origin, whether or not to use CORS.
  CORSEnabled corsEnabled;

  RefPtr<SecurityOrigin> securityOrigin;
  String contentSecurityPolicyNonce;
  IntegrityMetadataSet integrityMetadata;
  ParserDisposition parserDisposition;
  CacheAwareLoadingEnabled cacheAwareLoadingEnabled;
};

// Encode AtomicString (in FetchInitiatorInfo) as String to cross threads.
struct CrossThreadResourceLoaderOptionsData {
  DISALLOW_NEW();
  explicit CrossThreadResourceLoaderOptionsData(
      const ResourceLoaderOptions& options)
      : dataBufferingPolicy(options.dataBufferingPolicy),
        allowCredentials(options.allowCredentials),
        credentialsRequested(options.credentialsRequested),
        contentSecurityPolicyOption(options.contentSecurityPolicyOption),
        initiatorInfo(options.initiatorInfo),
        requestInitiatorContext(options.requestInitiatorContext),
        synchronousPolicy(options.synchronousPolicy),
        corsEnabled(options.corsEnabled),
        securityOrigin(options.securityOrigin
                           ? options.securityOrigin->isolatedCopy()
                           : nullptr),
        contentSecurityPolicyNonce(options.contentSecurityPolicyNonce),
        integrityMetadata(options.integrityMetadata),
        parserDisposition(options.parserDisposition),
        cacheAwareLoadingEnabled(options.cacheAwareLoadingEnabled) {}

  operator ResourceLoaderOptions() const {
    ResourceLoaderOptions options;
    options.dataBufferingPolicy = dataBufferingPolicy;
    options.allowCredentials = allowCredentials;
    options.credentialsRequested = credentialsRequested;
    options.contentSecurityPolicyOption = contentSecurityPolicyOption;
    options.initiatorInfo = initiatorInfo;
    options.requestInitiatorContext = requestInitiatorContext;
    options.synchronousPolicy = synchronousPolicy;
    options.corsEnabled = corsEnabled;
    options.securityOrigin = securityOrigin;
    options.contentSecurityPolicyNonce = contentSecurityPolicyNonce;
    options.integrityMetadata = integrityMetadata;
    options.parserDisposition = parserDisposition;
    options.cacheAwareLoadingEnabled = cacheAwareLoadingEnabled;
    return options;
  }

  DataBufferingPolicy dataBufferingPolicy;
  StoredCredentials allowCredentials;
  CredentialRequest credentialsRequested;
  ContentSecurityPolicyDisposition contentSecurityPolicyOption;
  CrossThreadFetchInitiatorInfoData initiatorInfo;
  RequestInitiatorContext requestInitiatorContext;
  SynchronousPolicy synchronousPolicy;
  CORSEnabled corsEnabled;
  RefPtr<SecurityOrigin> securityOrigin;
  String contentSecurityPolicyNonce;
  IntegrityMetadataSet integrityMetadata;
  ParserDisposition parserDisposition;
  CacheAwareLoadingEnabled cacheAwareLoadingEnabled;
};

template <>
struct CrossThreadCopier<ResourceLoaderOptions> {
  using Type = CrossThreadResourceLoaderOptionsData;
  static Type copy(const ResourceLoaderOptions& options) {
    return CrossThreadResourceLoaderOptionsData(options);
  }
};

}  // namespace blink

#endif  // ResourceLoaderOptions_h
