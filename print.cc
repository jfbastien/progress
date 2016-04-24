// Licensed under the Apache License, Version 2.0.

#include "print.h"

#include <cstdio>
#include <cwchar>
#include <limits>

#define ESC L"\033"

namespace {
typedef uint8_t S;
constexpr auto max_s = std::numeric_limits<S>::max();
constexpr wchar_t shades[] = {L'#', L'X', L'*', L'+', L'-', L'.', L' ', L' '};
constexpr size_t num_shades = sizeof(shades) / sizeof(shades[0]) - 1;
constexpr size_t shade_sections = max_s / num_shades;
constexpr const wchar_t *colors[] = {ESC L"[40m", ESC L"[41m", ESC L"[42m",
                                     ESC L"[43m", ESC L"[44m", ESC L"[45m",
                                     ESC L"[46m", ESC L"[47m", ESC L"[47m"};
constexpr const wchar_t *reset = ESC L"[0m";
constexpr size_t num_colors = sizeof(colors) / sizeof(colors[0]) - 1;
constexpr size_t color_sections = max_s / num_colors;
constexpr size_t max_chars = 11;

const wchar_t *lookup(wchar_t *buf, S i, S z) {
  wchar_t shade = shades[i / shade_sections];
  const wchar_t *color = colors[z / color_sections];
  wchar_t *pos = buf;
  if (shade != L' ') pos = wcscpy(pos, color) + wcslen(color);
  *pos++ = shade;
  if (shade != L' ') pos = wcscpy(pos, reset) + wcslen(reset);
  *pos++ = L'\0';
  return buf;
}
}

void print(S *scene_i, S *scene_z, size_t X, size_t Y) {
  for (size_t i = 0; i < X; ++i) {
    for (size_t j = 0; j < Y; ++j) {
      size_t idx = j * X + i;
      wchar_t buf[max_s];
      fputws(lookup(&buf[0], scene_i[idx], scene_z[idx]), stdout);
    }
    putwchar(L'\n');
  }
  fflush(stdout);
}
