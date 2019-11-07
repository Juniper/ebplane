#ifndef _LIB_BASE_SPAN_H_
#define _LIB_BASE_SPAN_H_

#include <array>
#include <vector>

#include "lib/base/invariant.h"

namespace base {

// Span describes a half-open linear range of address space containing zero or
// more instances of a single type. Span does not imply anything about the
// ownership of memory however it should never describe invalid addresses.
//
// GetBase() and GetLimit() correspond roughly to std::begin() and std::end()
// where valid data resides in the half-open interval [GetBase(), GetLimit()).
//
// The type of Span<const char> is very similar to std::string_view but should
// be preferred to std::string_view when the described memory contains raw
// bytes. Span<char> provides functionality unavailable in std::string_view or
// any other type in the standard library prior to C++20.
//
// Span provides a subset of the functionality present in C++20's std::span and
// should be replaced by "using Span = std::span;" when C++20 support is
// ready. All access to span is facilitated through free functions to ease
// transition to std::span in the future.
//
// IsEmpty(), GetSize(), GetByteSize() and MakeSpan() provide support for common
// interactions with Span.
//
// Example usage:
//
// std::vector<double> mutable_data(50);
// const std::array<double, 10> immutable_data;
//
// const auto mutable_span = base::MakeSpan(mutable_data);
// const auto immutable_span = base::MakeSpan(immutable_data);
//
// double* mutable_ptr = GetBase(mutable_span);
// const double* immutable_ptr = GetBase(immutable_span);
//
// assert(50 == GetSize(mutable_span));
// assert(!IsEmpty(mutable_span));
// assert(50 * sizeof(double) == GetByteSize(mutable_span));
//
template <typename T>
class Span {
 public:
  constexpr Span() = default;

  // Construct a new span using 'base' and 'limit'.
  // An explicitly constructed span must never have 'base' == nullptr. Users
  // should prefer other approaches like std::optional<Span<T>> to represent a
  // nullable span.
  constexpr Span(T* const base, T* const limit) : base_(base), limit_(limit) {
    INVARIANT_NE(nullptr, base);
    INVARIANT_NE(nullptr, limit);
    INVARIANT_LE(base, limit);
  }

  // Default copy constructor.
  constexpr Span(const Span&) = default;

  // Default copy assignment operator.
  Span& operator=(const Span&) = default;

  // Default move constructor.
  constexpr Span(Span&&) = default;

  // Default move assignment operator.
  Span& operator=(Span&&) = default;

  // Implicit conversion from Span<T> to Span<const T>.
  constexpr operator Span<const T>() const {
    return Span<const T>(base_, limit_);
  }

 private:
  // Return a pointer to the first element in 'span'.
  friend constexpr T* GetBase(const Span span) { return span.base_; }

  // Return a pointer to an address one position past the last element in
  // 'span'.
  friend constexpr T* GetLimit(const Span span) { return span.limit_; }

  // Pointer to the first element in this span.
  T* base_ = nullptr;

  // Pointer to an address one position past the last element in this span.
  // An empty span will always have 'base_' == 'limit_'.
  T* limit_ = nullptr;
};

// Return true iff 'span' contains no elements.
template <typename T>
inline constexpr bool IsEmpty(const Span<T> span) {
  return GetLimit(span) == GetBase(span);
}

// Return the number of elements in 'span'.
template <typename T>
inline constexpr size_t GetSize(const Span<T> span) {
  return GetLimit(span) - GetBase(span);
}

// Return the size of 'span' in bytes.
template <typename T>
inline constexpr size_t GetByteSize(const Span<T> span) {
  return sizeof(T) * GetSize(span);
}

// Return a new span starting at 'base' and containing 'size' elements.
template <typename T>
inline constexpr Span<T> MakeSpan(T* const base, const size_t size) {
  return Span<T>(base, base + size);
}

// Return a new span wrapping the contents of 'x'.
template <typename T>
inline constexpr Span<T> MakeSpan(std::vector<T>& x) {
  return MakeSpan(x.data(), x.size());
}

// Return a new span wrapping the contents of 'x'.
template <typename T>
inline constexpr Span<const T> MakeSpan(const std::vector<T>& x) {
  return MakeSpan(x.data(), x.size());
}

// Return a new span wrapping the contents of 'x'.
template <typename T, size_t N>
inline constexpr Span<T> MakeSpan(std::array<T, N>& x) {
  return MakeSpan(x.data(), x.size());
}

// Return a new span wrapping the contents of 'x'.
template <typename T, size_t N>
inline constexpr Span<const T> MakeSpan(const std::array<T, N>& x) {
  return MakeSpan(x.data(), x.size());
}

}  // namespace base

#endif  // _LIB_BASE_SPAN_H_