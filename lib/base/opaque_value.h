#ifndef LIB_BASE_OPAQUE_VALUE_H_
#define LIB_BASE_OPAQUE_VALUE_H_

namespace base {

// Type useful for holding values that should be treated as opaque data.
// Typically these will be integer types where the value is not meaningful to
// the code carrying the type. A very common example is POSIX file descriptors.
//
// As users should not make assumptions about the value of a handle type, only
// equality and inequality operators are provided. Arithmetic and logical
// operations are intentionally omitted.
//
// To support the common pattern of using handles as a keys to an associative
// data structure, OpaqueValue::Compare is provided.
//
// A macro is provided to simplify the creation of OpaqueValue types. It
// automatically generates a tag type to differentiate between different handle
// types with the same wrapped type. This prevents accidential mixing of types
// and prevents common errors when using positional function arguments.
//
// Example usage:
//
// DEFINE_OPAQUE_VALUE(int, FileDescriptor);
// DEFINE_OPAQUE_VALUE(int, EmployeeId);
//
// FileDescriptor fd(open("/some/path", FLAGS));
// EmployeeId id(5);
//
// fd = id;  // Compile error. Types are not convertible.
// fd = fd + 1;  // Compile error. Why are you doing math on a file descriptor?
// fd = 9;  // Compile error. No implicit type converstion.
// fd = FileDescriptor(6);  // Ok! Assignment works, as expected for a value.
// fd == fd;  // Ok! It is the same file descriptor!
// fd != FileDescriptor(1); // Ok!
//
// void foo(FileDescriptor fd, EmployeeId id);
// foo(fd, id);  // Ok! Types match.
// foo(id, fd);  // Compile error. Disaster averted.
//
// std::map<EmployeeId, PerformanceReview, EmployeeId::Compare> reviews;
// reviews[id] = PerformanceReview("Outstanding!");
//
// close(GetValue(fd));  // Raw value can be extracted. Avoid when possible.
//
template <typename T, typename TagT>
class OpaqueValue {
 public:
  constexpr OpaqueValue() = default;

  // Create an OpaqueValue containing 'value'. Value may later be extracted
  // with GetValue(my_opaque_value).
  explicit constexpr OpaqueValue(const T& value) : value_(value) {}

  // Default copy constructor.
  OpaqueValue(const OpaqueValue&) = default;

  // Default copy assignment operator.
  OpaqueValue& operator=(const OpaqueValue&) = default;

  // Compare implementation for use in associative data structures like
  // std::map<>.
  //
  // std::map<MyOpaqueValue, MyOpaqueValue::Compare> my_map;
  //
  // Using Compare implicitly assumes that the class of values wrapped by this
  // specific opaque value are unique.
  struct Compare {
    constexpr bool operator()(const OpaqueValue& lhs,
                              const OpaqueValue& rhs) const {
      return GetValue(lhs) < GetValue(rhs);
    }
  };

 private:
  // Return the value wrapped by 'opaque_value'.
  friend constexpr T GetValue(const OpaqueValue& opaque_value) {
    return opaque_value.value_;
  }

  // Wrapped value.
  T value_;
};

template <typename T, typename TagT>
inline constexpr bool operator==(const OpaqueValue<T, TagT>& lhs,
                                 const OpaqueValue<T, TagT>& rhs) {
  return GetValue(lhs) == GetValue(rhs);
}

template <typename T, typename TagT>
inline constexpr bool operator!=(const OpaqueValue<T, TagT>& lhs,
                                 const OpaqueValue<T, TagT>& rhs) {
  return GetValue(lhs) != GetValue(rhs);
}

}  // namespace base

#define _DEFINE_OPAQUE_VALUE(type, name, tag) \
  struct tag {};                              \
  using name = ::base::OpaqueValue<type, tag>;

// Helper to define a new OpaqueValue type with the provided 'name'.
#define DEFINE_OPAQUE_VALUE(type, name) \
  _DEFINE_OPAQUE_VALUE(type, name, _##name##OpaqueValueTag)

#endif  // LIB_BASE_OPAQUE_VALUE_H_