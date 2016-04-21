// Licensed under the Apache License, Version 2.0.

#ifndef print_h
#define print_h

#include "compiler.h"

#include <cstdint>
#include <cstdio>
#include <cwchar>
#include <limits>

template <typename S>
NO_INLINE void print(S *scene_i, S *scene_z, size_t X, size_t Y) {
  constexpr auto max_s = std::numeric_limits<S>::max();
  constexpr wchar_t shades[] = {L'#', L'X', L'*', L'+', L'-', L'.', L' ', L' '};
  constexpr size_t num_shades = sizeof(shades) / sizeof(shades[0]) - 1;
  constexpr size_t shade_sections = std::numeric_limits<S>::max() / num_shades;
  constexpr const wchar_t *colors[] = {L"\033[40m", L"\033[41m", L"\033[42m",
                                       L"\033[43m", L"\033[44m", L"\033[45m",
                                       L"\033[46m", L"\033[47m", L"\033[47m"};
  constexpr const wchar_t *reset = L"\033[0m";
  constexpr size_t num_colors = sizeof(colors) / sizeof(colors[0]) - 1;
  constexpr size_t color_sections = max_s / num_colors;
  for (size_t i = 0; i < X; ++i) {
    for (size_t j = 0; j < Y; ++j) {
      size_t idx = j * X + i;
      auto shade = shades[scene_i[idx] / shade_sections];
      if (shade != L' ') fputws(colors[scene_z[idx] / color_sections], stdout);
      putwchar(shade);
      if (shade != L' ') fputws(reset, stdout);
    }
    putwchar(L'\n');
  }
  fflush(stdout);
}

#endif
