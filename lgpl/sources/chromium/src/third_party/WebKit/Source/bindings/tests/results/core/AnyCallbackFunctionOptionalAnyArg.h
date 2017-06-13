// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file has been auto-generated by code_generator_v8.py.
// DO NOT MODIFY!

// This file has been generated from the Jinja2 template in
// third_party/WebKit/Source/bindings/templates/callback_function.h.tmpl

// clang-format off

#ifndef AnyCallbackFunctionOptionalAnyArg_h
#define AnyCallbackFunctionOptionalAnyArg_h

#include "bindings/core/v8/ScriptWrappable.h"
#include "bindings/core/v8/TraceWrapperV8Reference.h"
#include "core/CoreExport.h"
#include "platform/heap/Handle.h"
#include "wtf/text/WTFString.h"

namespace blink {

class ScriptState;

class CORE_EXPORT AnyCallbackFunctionOptionalAnyArg final : public GarbageCollectedFinalized<AnyCallbackFunctionOptionalAnyArg>, public TraceWrapperBase {
 public:
  static AnyCallbackFunctionOptionalAnyArg* create(ScriptState* scriptState, v8::Local<v8::Value> callback);

  ~AnyCallbackFunctionOptionalAnyArg() = default;

  DECLARE_TRACE();
  DECLARE_TRACE_WRAPPERS();

  bool call(ScriptWrappable* scriptWrappable, ScriptValue optionalAnyArg, ScriptValue& returnValue);

  v8::Local<v8::Function> v8Value(v8::Isolate* isolate) {
    return m_callback.newLocal(isolate);
  }

 private:
  AnyCallbackFunctionOptionalAnyArg(ScriptState*, v8::Local<v8::Function>);

  RefPtr<ScriptState> m_scriptState;
  TraceWrapperV8Reference<v8::Function> m_callback;
};

}  // namespace blink

#endif  // AnyCallbackFunctionOptionalAnyArg_h
