#ifndef LIB_ERROR_STATUS_H_
#define LIB_ERROR_STATUS_H_

#include <memory>
#include <string>
#include <string_view>
#include <utility>

#include "lib/base/invariant.h"
#include "lib/error/code.h"

namespace error {

// Class describing the result of an operation that may encounter an error.
// Status is implemented assuming that errors are uncommon and optimizes for the
// case where IsOk(status) == true.
//
// The following helpers exist to check for common conditions:
// IsOk() and IsError().
//
// Specific error code and text may be accessed using the following helpers:
// GetCode() and GetText().
//
// Example usage:
//
// Status Foo(int bar) {
//   if (bar > 0) {
//     return error::kOkStatus;
//   }
//   return Status(Code::INVALID_ARGUMENT, "negative bar encountered");
// }
//
// const auto status = Foo(10);
// if (IsOk(status)) {
//   std::cout << "Great Success\n";
// } else {
//   std::cout << "Error! code: " << GetCode(status)
//             << ", text: " << GetText(status) << "\n";
// }
//
// In some cases it is useful to preserve the root cause of an error when
// crossing API boundaries. To facilitate this, Status can optionally nest.
//
// Example usage:
//
// Status Foo() { return Status(kFooError, "foo error"); }
// Status Bar() {
//   const auto foo_status = Foo();
//   if (IsError(foo_status)) {
//     return Status(kBarError, "bar error", foo_status);
//   }
//   return kOkStatus;
// }
//
// const auto bar_status = Bar();
// if (IsError(bar_status)) {
//   std::cout << GetText(bar_status);  // Print bar_status
//   std::cout << GetText(GetNestedStatus(bar_status));  // Print foo_status
// }
//
class [[nodiscard]] Status {
 public:
  constexpr Status() = default;

  // Construct Status given a numeric error code.
  // kOkCode is a valid input.
  explicit Status(const Code code) {
    if (IsError(code)) {
      detail_ = std::make_unique<Detail>(code, "", Status());
    }
  }

  // Construct an error Status given a numeric error code and descriptive text.
  // kOkCode is not a valid input as only error Status may carry text.
  Status(const Code code, const std::string_view text) {
    INVARIANT_T(IsError(code));
    detail_ = std::make_unique<Detail>(code, text, Status());
  }

  // Construct an error Status given a numeric error code, descriptive text and
  // nested status. kOkCode is not a valid input as only error Status may carry
  // text or nested status.
  //
  // Inspired by Go 2.0 error handling. Nested status is typically used to
  // preserve the root cause of an error when crossing API boundaries.
  // Conceptually similar to a stack trace of errors.
  Status(const Code code, const std::string_view text, const Status& nested) {
    INVARIANT_T(IsError(code));
    detail_ = std::make_unique<Detail>(code, text, nested);
  }

  // Default move constructor.
  Status(Status &&) = default;

  // Default move assignment operator.
  Status& operator=(Status&&) = default;

  // Custom copy.
  // Deep copy is performed for non-OK status.
  Status(const Status& that) {
    if (that.detail_) {
      detail_ = std::make_unique<Detail>(*that.detail_);
    }
  }

  // Custom copy assignment operator.
  // Deep copy is performed for non-OK status.
  Status& operator=(const Status& that) {
    if (that.detail_) {
      detail_ = std::make_unique<Detail>(*that.detail_);
    } else {
      detail_ = nullptr;
    }
    return *this;
  }

 private:
  // Internal representation of non-OK Status.
  using Detail = std::tuple<Code, std::string, Status>;

  // Return numeric error code.
  friend Code GetCode(const Status& status) {
    return status.detail_ ? std::get<Code>(*status.detail_) : kOkCode;
  }

  // Return textual description of error or empty string if no text exists.
  // This should typically provide additional information from the point of
  // origination beyond what is available in Code.
  friend std::string GetText(const Status& status) {
    return status.detail_ ? std::get<std::string>(*status.detail_) : "";
  }

  // Return nested Status.
  // A status with IsOk(status) == true implicitly contains a nested OK status.
  friend Status GetNestedStatus(const Status& status) {
    return status.detail_ ? std::get<Status>(*status.detail_) : Status();
  }

  // For efficiency kOkCode is represented by nullptr.
  // Default construct as OK.
  std::unique_ptr<const Detail> detail_{nullptr};
};

inline bool operator==(const Status& lhs, const Status& rhs) {
  return (GetCode(lhs) == GetCode(rhs)) && (GetText(lhs) == GetText(rhs));
}

inline bool operator!=(const Status& lhs, const Status& rhs) {
  return !(lhs == rhs);
}

const Status kOkStatus(kOkCode);

// Idiom to check for OK status.
// Return true iff GetCode(status) == kOkCode.
inline bool IsOk(const Status& status) { return IsOk(GetCode(status)); }

// Idiom to check for non-OK status.
// Return true iff GetCode(status) != kOkCode.
inline bool IsError(const Status& status) { return !IsOk(status); }

}  // namespace error

#endif  // LIB_ERROR_STATUS_H_