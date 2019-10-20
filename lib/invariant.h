#ifndef LIB_INVARIANT_H_
#define LIB_INVARIANT_H_

#include <cassert>

#define INVARIANT_T(pred) assert(pred)
#define INVARIANT_F(pred) INVARIANT_T(!(pred))
#define INVARIANT_EQ(a, b) INVARIANT_T((a) == (b))
#define INVARIANT_NE(a, b) INVARIANT_T((a) != (b))

#endif  // LIB_INVARIANT_H_