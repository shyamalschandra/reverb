// Copyright 2019 DeepMind Technologies Limited.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "reverb/cc/table_extensions/base.h"

#include "reverb/cc/platform/logging.h"
#include "reverb/cc/priority_table_item.h"
#include "reverb/cc/table.h"
#include "tensorflow/core/platform/errors.h"

namespace deepmind {
namespace reverb {

tensorflow::Status PriorityTableExtensionBase::RegisterTable(Table* table) {
  if (table_) {
    return tensorflow::errors::FailedPrecondition(
        "Attempting to registering a table ", table, " (name: ", table->name(),
        ") with extension that has already been ", "registered with: ", table_,
        " (name: ", table->name(), ")");
  }
  table_ = table;
  return tensorflow::Status::OK();
}

void PriorityTableExtensionBase::UnregisterTable(absl::Mutex* mu,
                                                 Table* table) {
  REVERB_CHECK_EQ(table, table_)
      << "The wrong Table attempted to unregister this extension.";
  table_ = nullptr;
}

void PriorityTableExtensionBase::OnDelete(absl::Mutex* mu,
                                          const PriorityTableItem& item) {
  ApplyOnDelete(item);
}

void PriorityTableExtensionBase::OnInsert(absl::Mutex* mu,
                                          const PriorityTableItem& item) {
  ApplyOnInsert(item);
}

void PriorityTableExtensionBase::OnReset(absl::Mutex* mu) { ApplyOnReset(); }

void PriorityTableExtensionBase::OnUpdate(absl::Mutex* mu,
                                          const PriorityTableItem& item) {
  ApplyOnUpdate(item);
}

void PriorityTableExtensionBase::OnSample(absl::Mutex* mu,
                                          const PriorityTableItem& item) {
  ApplyOnSample(item);
}

void PriorityTableExtensionBase::ApplyOnDelete(const PriorityTableItem& item) {}

void PriorityTableExtensionBase::ApplyOnInsert(const PriorityTableItem& item) {}

void PriorityTableExtensionBase::ApplyOnReset() {}

void PriorityTableExtensionBase::ApplyOnUpdate(const PriorityTableItem& item) {}

void PriorityTableExtensionBase::ApplyOnSample(const PriorityTableItem& item) {}

}  // namespace reverb
}  // namespace deepmind
