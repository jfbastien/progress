// Licensed under the Apache License, Version 2.0.

#ifndef mandelbrot_h
#define mandelbrot_h

#include <complex>
#include <cstdint>
#include <iostream>
#include <limits>

template <typename FP, typename S, size_t X, size_t Y>
void mandelbrot(FP x, FP y, FP w, FP h, S (&scene)[X][Y], unsigned iterations) {
  typedef std::complex<FP> C;

  for (size_t i = X; i; --i)
    for (size_t j = Y; j; --j) {
      C c(x + (i - 1) / FP(X - 1) * w, y + (j - 1) / FP(Y - 1) * h);
      C z = 0;

      unsigned it = iterations;
      while (--it && std::abs(z) < 2.0) z = z * z + c;

      scene[i - 1][j - 1] =
          std::numeric_limits<S>::max() * it / float(iterations);
    }
}

template <typename S, size_t X, size_t Y>
void print(S (&scene)[X][Y]) {
  constexpr wchar_t t[] = {L'█', L'▓', L'▒', L'░', L' '};
  constexpr size_t shades = sizeof(t) / sizeof(t[0]);
  constexpr size_t sections = std::numeric_limits<S>::max() / shades;
  for (size_t i = 0; i < X; ++i) {
    for (size_t j = 0; j < Y; ++j) {
      std::wcout << t[scene[i][j] / sections];
    }
    std::wcout << L'\n';
  }
}

#endif
