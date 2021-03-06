// Licensed under the Apache License, Version 2.0.

#ifndef mandelbrot_h
#define mandelbrot_h

#include "compiler.h"

#include <complex>
#include <limits>

namespace {
template <typename Scene, typename FP>
ALWAYS_INLINE void mandelbrot(FP x, FP y, FP w, FP h, Scene *scene_i,
                              Scene *scene_z, size_t X, size_t Y,
                              size_t iterations) {
  typedef std::complex<FP> C;
  typedef uint8_t S;
  constexpr FP max_z = 2.0;
  constexpr auto max_s = std::numeric_limits<S>::max();

  for (size_t i = X; i; --i)
    for (size_t j = Y; j; --j) {
      C c(x + (i - 1) / FP(X - 1) * w, y + (j - 1) / FP(Y - 1) * h);
      C z = 0;

      unsigned it = iterations;
      while (--it && std::abs(z) < max_z) z = z * z + c;

      size_t idx = (j - 1) * X + (i - 1);
      scene_i[idx].store(max_s * it / float(iterations));
      scene_z[idx].store(max_s * (std::min(max_z, std::abs(z)) - max_z) /
                         max_z);
    }
}
}

#endif
