// Licensed under the Apache License, Version 2.0.

#ifndef mandelbrot_h
#define mandelbrot_h

#include "compiler.h"

#include <complex>
#include <limits>

template <typename FP, typename S, size_t X, size_t Y>
ALWAYS_INLINE void mandelbrot(FP x, FP y, FP w, FP h, S (&scene_i)[X][Y],
                              S (&scene_z)[X][Y], unsigned iterations) {
  typedef std::complex<FP> C;
  constexpr FP max_z = 2.0;
  constexpr auto max_s = std::numeric_limits<S>::max();

  for (size_t i = X; i; --i)
    for (size_t j = Y; j; --j) {
      C c(x + (i - 1) / FP(X - 1) * w, y + (j - 1) / FP(Y - 1) * h);
      C z = 0;

      unsigned it = iterations;
      while (--it && std::abs(z) < max_z) z = z * z + c;

      scene_i[i - 1][j - 1] = max_s * it / float(iterations);
      scene_z[i - 1][j - 1] =
          max_s * (std::min(max_z, std::abs(z)) - max_z) / max_z;
    }
}

#endif
