// Licensed under the Apache License, Version 2.0.

#ifndef print_h
#define print_h

#include "compiler.h"

#include <cstdint>
#include <cstdio>
#include <cwchar>
#include <limits>

template <typename S, size_t X, size_t Y>
NO_INLINE void print(S (&scene_i)[X][Y], S (&scene_z)[X][Y]) {
  constexpr auto max_s = std::numeric_limits<S>::max();
  constexpr wchar_t shades[] = {L'#', L'X', L'*', L'+', L'-', L'.', L' ', L' '};
  constexpr size_t num_shades = sizeof(shades) / sizeof(shades[0]) - 1;
  constexpr size_t shade_sections = std::numeric_limits<S>::max() / num_shades;
  constexpr const wchar_t *colors[] = {L"\033[30m", L"\033[31m", L"\033[32m",
                                       L"\033[33m", L"\033[34m", L"\033[35m",
                                       L"\033[36m", L"\033[37m", L"\033[37m"};
  constexpr const wchar_t *reset = L"\033[0m";
  constexpr size_t num_colors = sizeof(colors) / sizeof(colors[0]) - 1;
  constexpr size_t color_sections = max_s / num_colors;
  for (size_t i = 0; i < X; ++i) {
    for (size_t j = 0; j < Y; ++j) {
      fputws(colors[scene_z[i][j] / color_sections], stdout);
      putwchar(shades[scene_i[i][j] / shade_sections]);
      fputws(reset, stdout);
    }
    putwchar(L'\n');
  }
  fflush(stdout);
}

#endif
