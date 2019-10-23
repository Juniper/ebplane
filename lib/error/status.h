#ifndef LIB_ERROR_STATUS_H_
#define LIB_ERROR_STATUS_H_

#include <memory>
#include <string>
#include <string_view>
#include <utility>

#include "lib/base/invariant.h"
#include "lib/base/opaque_value.h"

namespace error {

// Strongly typed integer used to encode specific errors. Code is not
// interpreted by the core status utilities with the expection of the value zero
// which is always considered a success.
//
// Note that the following helpers exist to check for common conditions:
// IsOk() and IsError().
DEFINE_OPAQUE_VALUE(int, Code);

constexpr Code kOkCode(0);

// Idiom to check for OK code.
// Return true iff code == Code::OK.
inline constexpr bool IsOk(const Code code) { return kOkCode == code; }

// Idiom to check for error codes.
// Return true iff code != Code::OK.
inline constexpr bool IsError(const Code code) { return !IsOk(code); }

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
class Status {
 public:
  constexpr Status() = default;

  // Construct Status given a numeric error code.
  // Code::OK is a valid input.
  constexpr explicit Status(const Code code) {
    if (IsError(code)) {
      detail_ = std::make_unique<Detail>(code, "");
    }
  }

  // Construct an error Status given a numeric error code and descriptive text.
  // Code::OK is not a valid input as only error Status may carry text.
  constexpr Status(const Code code, const std::string& text) {
    INVARIANT_T(IsError(code));
    detail_ = std::make_unique<Detail>(code, text);
  }

  // Default move constructor.
  Status(Status&&) = default;

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
  using Detail = std::tuple<Code, std::string>;

  // Return numeric error code.
  friend Code GetCode(const Status& status) {
    return status.detail_ ? std::get<Code>(*status.detail_) : kOkCode;
  }

  // Return textual description of error or empty string if no text exists.
  friend std::string GetText(const Status& status) {
    return status.detail_ ? std::get<std::string>(*status.detail_) : "";
  }

  // For efficiency Code::OK is represented by nullptr.
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
// Return true iff GetCode(status) == Code::OK.
inline bool IsOk(const Status& status) { return IsOk(GetCode(status)); }

// Idiom to check for non-OK status.
// Return true iff GetCode(status) != Code::OK.
inline bool IsError(const Status& status) { return !IsOk(status); }

}  // namespace error

#endif  // LIB_ERROR_STATUS_H_