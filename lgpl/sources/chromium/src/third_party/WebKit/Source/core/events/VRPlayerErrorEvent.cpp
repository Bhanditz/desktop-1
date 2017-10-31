// Copyright (c) 2017 Opera Software AS. All rights reserved.

#include "core/events/VRPlayerErrorEvent.h"

namespace blink {

VRPlayerErrorEvent::VRPlayerErrorEvent(unsigned short type)
    : Event(EventTypeNames::operavrplayererror, false, false), type_(type) {}

VRPlayerErrorEvent::~VRPlayerErrorEvent() {}

const AtomicString& VRPlayerErrorEvent::InterfaceName() const {
  return EventNames::VRPlayerErrorEvent;
}

DEFINE_TRACE(VRPlayerErrorEvent) {
  Event::Trace(visitor);
}

}  // namespace blink