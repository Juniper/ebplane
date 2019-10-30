#ifndef LIB_BASE_IGNORE_H_
#define LIB_BASE_IGNORE_H_

namespace base {

// Idiom to ignore an otherwise unused variable or result.
// Prefer to (void) cast when dealing with [[nodiscard]].
template <typename T>
void Ignore(const T&) {}

}  // namespace base

#endif  // LIB_BASE_IGNORE_H_