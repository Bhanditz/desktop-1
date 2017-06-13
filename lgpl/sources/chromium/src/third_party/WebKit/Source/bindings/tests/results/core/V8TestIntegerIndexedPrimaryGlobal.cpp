// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file has been auto-generated by code_generator_v8.py.
// DO NOT MODIFY!

// This file has been generated from the Jinja2 template in
// third_party/WebKit/Source/bindings/templates/interface.cpp.tmpl

// clang-format off
#include "V8TestIntegerIndexedPrimaryGlobal.h"

#include "bindings/core/v8/ExceptionState.h"
#include "bindings/core/v8/V8DOMConfiguration.h"
#include "bindings/core/v8/V8Document.h"
#include "bindings/core/v8/V8Node.h"
#include "bindings/core/v8/V8ObjectConstructor.h"
#include "core/dom/Document.h"
#include "wtf/GetPtr.h"
#include "wtf/RefPtr.h"

namespace blink {

// Suppress warning: global constructors, because struct WrapperTypeInfo is trivial
// and does not depend on another global objects.
#if defined(COMPONENT_BUILD) && defined(WIN32) && COMPILER(CLANG)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wglobal-constructors"
#endif
const WrapperTypeInfo V8TestIntegerIndexedPrimaryGlobal::wrapperTypeInfo = { gin::kEmbedderBlink, V8TestIntegerIndexedPrimaryGlobal::domTemplate, V8TestIntegerIndexedPrimaryGlobal::trace, V8TestIntegerIndexedPrimaryGlobal::traceWrappers, nullptr, "TestIntegerIndexedPrimaryGlobal", 0, WrapperTypeInfo::WrapperTypeObjectPrototype, WrapperTypeInfo::ObjectClassId, WrapperTypeInfo::NotInheritFromActiveScriptWrappable, WrapperTypeInfo::Independent };
#if defined(COMPONENT_BUILD) && defined(WIN32) && COMPILER(CLANG)
#pragma clang diagnostic pop
#endif

// This static member must be declared by DEFINE_WRAPPERTYPEINFO in TestIntegerIndexedPrimaryGlobal.h.
// For details, see the comment of DEFINE_WRAPPERTYPEINFO in
// bindings/core/v8/ScriptWrappable.h.
const WrapperTypeInfo& TestIntegerIndexedPrimaryGlobal::s_wrapperTypeInfo = V8TestIntegerIndexedPrimaryGlobal::wrapperTypeInfo;

// not [ActiveScriptWrappable]
static_assert(
    !std::is_base_of<ActiveScriptWrappableBase, TestIntegerIndexedPrimaryGlobal>::value,
    "TestIntegerIndexedPrimaryGlobal inherits from ActiveScriptWrappable<>, but is not specifying "
    "[ActiveScriptWrappable] extended attribute in the IDL file.  "
    "Be consistent.");
static_assert(
    std::is_same<decltype(&TestIntegerIndexedPrimaryGlobal::hasPendingActivity),
                 decltype(&ScriptWrappable::hasPendingActivity)>::value,
    "TestIntegerIndexedPrimaryGlobal is overriding hasPendingActivity(), but is not specifying "
    "[ActiveScriptWrappable] extended attribute in the IDL file.  "
    "Be consistent.");

namespace TestIntegerIndexedPrimaryGlobalV8Internal {

static void lengthAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();

  TestIntegerIndexedPrimaryGlobal* impl = V8TestIntegerIndexedPrimaryGlobal::toImpl(holder);

  v8SetReturnValueInt(info, impl->length());
}

static void lengthAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Object> holder = info.Holder();
  TestIntegerIndexedPrimaryGlobal* impl = V8TestIntegerIndexedPrimaryGlobal::toImpl(holder);

  ExceptionState exceptionState(info.GetIsolate(), ExceptionState::SetterContext, "TestIntegerIndexedPrimaryGlobal", "length");

  // Prepare the value to be set.
  int cppValue = toInt8(info.GetIsolate(), v8Value, NormalConversion, exceptionState);
  if (exceptionState.hadException())
    return;

  impl->setLength(cppValue);
}

static void voidMethodDocumentMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestIntegerIndexedPrimaryGlobal* impl = V8TestIntegerIndexedPrimaryGlobal::toImpl(info.Holder());

  if (UNLIKELY(info.Length() < 1)) {
    V8ThrowException::throwTypeError(info.GetIsolate(), ExceptionMessages::failedToExecute("voidMethodDocument", "TestIntegerIndexedPrimaryGlobal", ExceptionMessages::notEnoughArguments(1, info.Length())));
    return;
  }

  Document* document;
  document = V8Document::toImplWithTypeCheck(info.GetIsolate(), info[0]);
  if (!document) {
    V8ThrowException::throwTypeError(info.GetIsolate(), ExceptionMessages::failedToExecute("voidMethodDocument", "TestIntegerIndexedPrimaryGlobal", "parameter 1 is not of type 'Document'."));

    return;
  }

  impl->voidMethodDocument(document);
}

} // namespace TestIntegerIndexedPrimaryGlobalV8Internal

void V8TestIntegerIndexedPrimaryGlobal::lengthAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestIntegerIndexedPrimaryGlobalV8Internal::lengthAttributeGetter(info);
}

void V8TestIntegerIndexedPrimaryGlobal::lengthAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Value> v8Value = info[0];

  TestIntegerIndexedPrimaryGlobalV8Internal::lengthAttributeSetter(v8Value, info);
}

void V8TestIntegerIndexedPrimaryGlobal::voidMethodDocumentMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestIntegerIndexedPrimaryGlobalV8Internal::voidMethodDocumentMethod(info);
}

void V8TestIntegerIndexedPrimaryGlobal::namedPropertyGetterCallback(v8::Local<v8::Name> name, const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (!name->IsString())
    return;
  const AtomicString& propertyName = toCoreAtomicString(name.As<v8::String>());

  V8TestIntegerIndexedPrimaryGlobal::namedPropertyGetterCustom(propertyName, info);
}

void V8TestIntegerIndexedPrimaryGlobal::namedPropertySetterCallback(v8::Local<v8::Name> name, v8::Local<v8::Value> v8Value, const v8::PropertyCallbackInfo<v8::Value>& info) {
  if (!name->IsString())
    return;
  const AtomicString& propertyName = toCoreAtomicString(name.As<v8::String>());

  V8TestIntegerIndexedPrimaryGlobal::namedPropertySetterCustom(propertyName, v8Value, info);
}

void V8TestIntegerIndexedPrimaryGlobal::namedPropertyDeleterCallback(v8::Local<v8::Name> name, const v8::PropertyCallbackInfo<v8::Boolean>& info) {
  if (!name->IsString())
    return;
  const AtomicString& propertyName = toCoreAtomicString(name.As<v8::String>());

  V8TestIntegerIndexedPrimaryGlobal::namedPropertyDeleterCustom(propertyName, info);
}

void V8TestIntegerIndexedPrimaryGlobal::namedPropertyQueryCallback(v8::Local<v8::Name> name, const v8::PropertyCallbackInfo<v8::Integer>& info) {
  if (!name->IsString())
    return;
  const AtomicString& propertyName = toCoreAtomicString(name.As<v8::String>());

  V8TestIntegerIndexedPrimaryGlobal::namedPropertyQueryCustom(propertyName, info);
}

void V8TestIntegerIndexedPrimaryGlobal::namedPropertyEnumeratorCallback(const v8::PropertyCallbackInfo<v8::Array>& info) {
  V8TestIntegerIndexedPrimaryGlobal::namedPropertyEnumeratorCustom(info);
}

void V8TestIntegerIndexedPrimaryGlobal::indexedPropertyGetterCallback(uint32_t index, const v8::PropertyCallbackInfo<v8::Value>& info) {
  V8TestIntegerIndexedPrimaryGlobal::indexedPropertyGetterCustom(index, info);
}

void V8TestIntegerIndexedPrimaryGlobal::indexedPropertySetterCallback(uint32_t index, v8::Local<v8::Value> v8Value, const v8::PropertyCallbackInfo<v8::Value>& info) {
  V8TestIntegerIndexedPrimaryGlobal::indexedPropertySetterCustom(index, v8Value, info);
}

void V8TestIntegerIndexedPrimaryGlobal::indexedPropertyDeleterCallback(uint32_t index, const v8::PropertyCallbackInfo<v8::Boolean>& info) {
  V8TestIntegerIndexedPrimaryGlobal::indexedPropertyDeleterCustom(index, info);
}

const V8DOMConfiguration::AccessorConfiguration V8TestIntegerIndexedPrimaryGlobalAccessors[] = {
    {"length", V8TestIntegerIndexedPrimaryGlobal::lengthAttributeGetterCallback, V8TestIntegerIndexedPrimaryGlobal::lengthAttributeSetterCallback, nullptr, nullptr, nullptr, nullptr, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::OnInstance, V8DOMConfiguration::CheckHolder},
};

const V8DOMConfiguration::MethodConfiguration V8TestIntegerIndexedPrimaryGlobalMethods[] = {
    {"voidMethodDocument", V8TestIntegerIndexedPrimaryGlobal::voidMethodDocumentMethodCallback, nullptr, 1, v8::None, V8DOMConfiguration::OnInstance, V8DOMConfiguration::CheckHolder, V8DOMConfiguration::DoNotCheckAccess},
};

static void installV8TestIntegerIndexedPrimaryGlobalTemplate(v8::Isolate* isolate, const DOMWrapperWorld& world, v8::Local<v8::FunctionTemplate> interfaceTemplate) {
  // Initialize the interface object's template.
  V8DOMConfiguration::initializeDOMInterfaceTemplate(isolate, interfaceTemplate, V8TestIntegerIndexedPrimaryGlobal::wrapperTypeInfo.interfaceName, V8TestIntegerIndexedPrimaryGlobal::domTemplateForNamedPropertiesObject(isolate, world), V8TestIntegerIndexedPrimaryGlobal::internalFieldCount);

  v8::Local<v8::Signature> signature = v8::Signature::New(isolate, interfaceTemplate);
  ALLOW_UNUSED_LOCAL(signature);
  v8::Local<v8::ObjectTemplate> instanceTemplate = interfaceTemplate->InstanceTemplate();
  ALLOW_UNUSED_LOCAL(instanceTemplate);
  v8::Local<v8::ObjectTemplate> prototypeTemplate = interfaceTemplate->PrototypeTemplate();
  ALLOW_UNUSED_LOCAL(prototypeTemplate);

  // Global object prototype chain consists of Immutable Prototype Exotic Objects
  prototypeTemplate->SetImmutableProto();

  // Global objects are Immutable Prototype Exotic Objects
  instanceTemplate->SetImmutableProto();

  // Register DOM constants, attributes and operations.
  V8DOMConfiguration::installAccessors(isolate, world, instanceTemplate, prototypeTemplate, interfaceTemplate, signature, V8TestIntegerIndexedPrimaryGlobalAccessors, WTF_ARRAY_LENGTH(V8TestIntegerIndexedPrimaryGlobalAccessors));
  V8DOMConfiguration::installMethods(isolate, world, instanceTemplate, prototypeTemplate, interfaceTemplate, signature, V8TestIntegerIndexedPrimaryGlobalMethods, WTF_ARRAY_LENGTH(V8TestIntegerIndexedPrimaryGlobalMethods));

  // Indexed properties
  v8::IndexedPropertyHandlerConfiguration indexedPropertyHandlerConfig(V8TestIntegerIndexedPrimaryGlobal::indexedPropertyGetterCallback, V8TestIntegerIndexedPrimaryGlobal::indexedPropertySetterCallback, nullptr, V8TestIntegerIndexedPrimaryGlobal::indexedPropertyDeleterCallback, indexedPropertyEnumerator<TestIntegerIndexedPrimaryGlobal>, v8::Local<v8::Value>(), v8::PropertyHandlerFlags::kNone);
  instanceTemplate->SetHandler(indexedPropertyHandlerConfig);

  // Array iterator (@@iterator)
  instanceTemplate->SetIntrinsicDataProperty(v8::Symbol::GetIterator(isolate), v8::kArrayProto_values, v8::DontEnum);
}

v8::Local<v8::FunctionTemplate> V8TestIntegerIndexedPrimaryGlobal::domTemplate(v8::Isolate* isolate, const DOMWrapperWorld& world) {
  return V8DOMConfiguration::domClassTemplate(isolate, world, const_cast<WrapperTypeInfo*>(&wrapperTypeInfo), installV8TestIntegerIndexedPrimaryGlobalTemplate);
}

v8::Local<v8::FunctionTemplate> V8TestIntegerIndexedPrimaryGlobal::domTemplateForNamedPropertiesObject(v8::Isolate* isolate, const DOMWrapperWorld& world) {
  v8::Local<v8::FunctionTemplate> parentTemplate = V8None::domTemplate(isolate, world);

  v8::Local<v8::FunctionTemplate> namedPropertiesObjectFunctionTemplate = v8::FunctionTemplate::New(isolate, V8ObjectConstructor::isValidConstructorMode);
  namedPropertiesObjectFunctionTemplate->SetClassName(v8AtomicString(isolate, "TestIntegerIndexedPrimaryGlobalProperties"));
  namedPropertiesObjectFunctionTemplate->Inherit(parentTemplate);

  v8::Local<v8::ObjectTemplate> namedPropertiesObjectTemplate = namedPropertiesObjectFunctionTemplate->PrototypeTemplate();
  namedPropertiesObjectTemplate->SetInternalFieldCount(V8TestIntegerIndexedPrimaryGlobal::internalFieldCount);
  // Named Properties object has SetPrototype method of Immutable Prototype Exotic Objects
  namedPropertiesObjectTemplate->SetImmutableProto();
  V8DOMConfiguration::setClassString(isolate, namedPropertiesObjectTemplate, "TestIntegerIndexedPrimaryGlobalProperties");
  v8::NamedPropertyHandlerConfiguration namedPropertyHandlerConfig(V8TestIntegerIndexedPrimaryGlobal::namedPropertyGetterCallback, V8TestIntegerIndexedPrimaryGlobal::namedPropertySetterCallback, V8TestIntegerIndexedPrimaryGlobal::namedPropertyQueryCallback, V8TestIntegerIndexedPrimaryGlobal::namedPropertyDeleterCallback, V8TestIntegerIndexedPrimaryGlobal::namedPropertyEnumeratorCallback, v8::Local<v8::Value>(), static_cast<v8::PropertyHandlerFlags>(int(v8::PropertyHandlerFlags::kOnlyInterceptStrings) | int(v8::PropertyHandlerFlags::kNonMasking)));
  namedPropertiesObjectTemplate->SetHandler(namedPropertyHandlerConfig);

  return namedPropertiesObjectFunctionTemplate;
}

bool V8TestIntegerIndexedPrimaryGlobal::hasInstance(v8::Local<v8::Value> v8Value, v8::Isolate* isolate) {
  return V8PerIsolateData::from(isolate)->hasInstance(&wrapperTypeInfo, v8Value);
}

v8::Local<v8::Object> V8TestIntegerIndexedPrimaryGlobal::findInstanceInPrototypeChain(v8::Local<v8::Value> v8Value, v8::Isolate* isolate) {
  return V8PerIsolateData::from(isolate)->findInstanceInPrototypeChain(&wrapperTypeInfo, v8Value);
}

TestIntegerIndexedPrimaryGlobal* V8TestIntegerIndexedPrimaryGlobal::toImplWithTypeCheck(v8::Isolate* isolate, v8::Local<v8::Value> value) {
  return hasInstance(value, isolate) ? toImpl(v8::Local<v8::Object>::Cast(value)) : nullptr;
}

}  // namespace blink
