// Copyright (c) Facebook, Inc. and its affiliates.

#pragma once

#include "glean/rts/fact.h"
#include "glean/rts/lookup.h"

namespace facebook {
namespace glean {
namespace rts {

struct Store {
  /// Insert a new fact into the set if it doesn't conflict with existing
  /// facts. The return value indicates whether the fact was new.
  ///
  /// PRECONDITION: The new fact doesn't conflict with an existing one.
  /// A conflict occurs in two cases.
  ///   - There is a fact with the same id but different type, key or value.
  ///   - There is a fact with the same type and key but different id.
  ///
  /// Inserting the same fact twice is fine.
  virtual void insert(Fact::Ref fact) = 0;

  virtual ~Store() {}
};

inline void copyFacts(Store& store, Lookup& lookup) {
  for (auto iter = lookup.enumerate(); auto fact = iter->get(); iter->next()) {
    store.insert(fact);
  }
}

}
}
}
