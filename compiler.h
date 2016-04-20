// Licensed under the Apache License, Version 2.0.

#ifndef compiler_h
#define compiler_h

#ifndef __has_attribute
# define __has_attribute(x) 0
#endif

#if __has_attribute(noinline) || defined(__GNUC__)
# define NO_INLINE __attribute__((noinline))
#else
# define NO_INLINE
#endif

#if __has_attribute(always_inline) || defined(__GNUC__)
# define ALWAYS_INLINE __attribute__((always_inline))
#else
# define ALWAYS_INLINE
#endif

#endif
