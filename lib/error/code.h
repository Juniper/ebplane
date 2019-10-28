#ifndef LIB_ERROR_CODE_H_
#define LIB_ERROR_CODE_H_

#include <system_error>
#include <type_traits>

namespace error {

// Strongly typed value used to encode specific errors. Code is not
// interpreted by the core status utilities with the expection of the default
// constructed value which is always considered a success.
//
// The following helpers exist to check for common conditions:
// IsOk() and IsError().
//
// Until proven otherwise, assume that std::error_code implements all necessary
// features.
//
// When possible, avoid using std::error_code features directly and implement
// wrappers in this file.
using Code = std::error_code;

static_assert(std::is_trivially_copyable_v<Code>,
              "Code should be trivially copiable");
static_assert(16 >= sizeof(Code), "Code seems unreasonably large");

// Constant that satisfies IsOk(kOkCode) == true.
const Code kOkCode;

// Idiom to check for OK code.
// Return true iff code == kOkCode.
inline bool IsOk(const Code code) { return !static_cast<bool>(code); }

// Idiom to check for error codes.
// Return true iff code != kOkCode.
inline bool IsError(const Code code) { return !IsOk(code); }

}  // namespace error

#endif  // LIB_ERROR_CODE_H_