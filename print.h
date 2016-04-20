// Licensed under the Apache License, Version 2.0.

#ifndef print_h
#define print_h

#include "compiler.h"
#include <cstdint>
#include <cstdio>
#include <cwchar>
#include <limits>

template <typename S, size_t X, size_t Y>
NO_INLINE void print(S (&scene)[X][Y]) {
  constexpr wchar_t t[] = {L'█', L'▓', L'▒', L'░', L' '};
  constexpr size_t shades = sizeof(t) / sizeof(t[0]);
  constexpr size_t sections = std::numeric_limits<S>::max() / shades;
  for (size_t i = 0; i < X; ++i) {
    for (size_t j = 0; j < Y; ++j) {
      putwchar(t[scene[i][j] / sections]);
    }
    putwchar(L'\n');
  }
  fflush(stdout);
}

#endif
