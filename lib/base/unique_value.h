#ifndef LIB_BASE_UNIQUE_VALUE_H_
#define LIB_BASE_UNIQUE_VALUE_H_

#include <functional>
#include <optional>

#include "lib/base/invariant.h"

namespace base {

// Type providing std::unique_ptr<>-like functionality for immutable values.
// The contents of UniqueValue<> may be replaced, but not modified in place.
//
// Unlike pointers where nullptr is a special value that indicates invalid
// contents, every possible value a value object can hold may be valid. This
// requires additional storage to track validity of the contained value. Despite
// the required extra state, this is still more efficient than storing values in
// heap allocated space and behaves more gracefully under memory pressure.
//
// In addition to the type of the wrapped value, users must provide a cleanup
// function object to be called whenever a UniqueValue containing a valid value
// is destroyed.
//
// CleanupFunctionObjectT is a function object implementing the call operator.
// In C++20 lambdas can be declared in unevaluated contexts 'decltype([](const T
// value){})' sufficies to declare a cleanup function object. Prior to C++20 a
// type must be defined:
//
// struct CleanupFunctionObject {
//     void operator()(const T value){
//         // cleanup 'value', only called with valid 'value'.
//     };
// };
//
// Example usage:
//
// struct CloseFunctionObject { void operator()(const int fd) { close(fd); } };
// using UniqueFileDescriptor = UniqueValue<int, CloseFunctionObject>;
// {
//     UniqueFileDescriptor fd(open("/some/path", FLAGS));
//     DoSomethingWithFd(GetValue(fd));  // Free function style value access.
//     DoSomethingElseWithFd(*fd);  // std::unique_ptr style value access.
// }  // 'fd' leaves scope and is automatically closed!
//
// See /lib/posix/unique_file_descriptor.h for a more complete example.
//
template <typename T, typename CleanupFunctionObjectT>
class UniqueValue {
 public:
  // Like std::unique_ptr<> default construction results in an empty object.
  constexpr UniqueValue() = default;

  // Construct a non-empty UniqueValue containing 'value'.
  explicit constexpr UniqueValue(const T& value) : value_(value) {}

  // Custom move constructor.
  UniqueValue(UniqueValue&& that) {
    value_ = std::move(that.value_);
    that.value_ = std::nullopt;
  }

  // Custom move assignment operator.
  UniqueValue& operator=(UniqueValue&& that) {
    if (value_) {
      std::invoke(CleanupFunctionObjectT(), *value_);
    }
    value_ = std::move(that.value_);
    that.value_ = std::nullopt;
    return *this;
  }

  // No copy constructor.
  UniqueValue(const UniqueValue&) = delete;

  // No copy assignment operator.
  UniqueValue& operator=(const UniqueValue&) = delete;

  // Invoke CleanupFunctionObjectT::operator() if this object contains a value.
  ~UniqueValue() {
    if (value_) {
      std::invoke(CleanupFunctionObjectT(), *value_);
    }
  }

  // Return the contained value.
  // Requires that this objects contains a value.
  constexpr const T& operator*() const {
    INVARIANT_T(value_);
    return *value_;
  }

  // Return true iff this object contains a value.
  explicit constexpr operator bool() const { return value_; }

 private:
  // Return the contained value.
  // Requires that this object contains a value.
  friend constexpr const T& GetValue(const UniqueValue& unique_value) {
    INVARIANT_T(unique_value.value_);
    return *unique_value.value_;
  }

  // Wrapped value. T may not be able to represent an invalid value in the way
  // that nullptr implies an invalid value in std::unique_ptr. std::optional<>
  // provides an extra bit of information to distinguish uninitialized or
  // vacated values.
  std::optional<T> value_ = std::nullopt;
};

}  // namespace base

#endif  // LIB_BASE_UNIQUE_VALUE_H_