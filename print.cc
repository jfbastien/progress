// Licensed under the Apache License, Version 2.0.

#include "print.h"
#include "support.h"

#include <cstdio>
#include <cwchar>
#include <limits>

#define ESC L"\033"

namespace {

typedef uint8_t S;
constexpr auto max_s = std::numeric_limits<S>::max();

constexpr wchar_t ascii_shades[] = {L'#', L'X', L'%', L'*', L'+', L'-',
                                    L':', L',', L'.', L' ', L' '};
constexpr size_t num_ascii_shades =
    sizeof(ascii_shades) / sizeof(ascii_shades[0]) - 1;
constexpr size_t ascii_shade_sections = max_s / num_ascii_shades;

constexpr wchar_t unicode_shades[] = {L'█', L'▉', L'▊', L'▋', L'▌', L'▍', L'▎',
                                      L'▏', L'▓', L'▒', L'░', L' ', L' '};
constexpr size_t num_unicode_shades =
    sizeof(unicode_shades) / sizeof(unicode_shades[0]) - 1;
constexpr size_t unicode_shade_sections = max_s / num_unicode_shades;

constexpr const wchar_t *colors[] = {ESC L"[40m", ESC L"[41m", ESC L"[42m",
                                     ESC L"[43m", ESC L"[44m", ESC L"[45m",
                                     ESC L"[46m", ESC L"[47m", ESC L"[47m"};
constexpr const wchar_t *reset = ESC L"[0m";
constexpr size_t num_colors = sizeof(colors) / sizeof(colors[0]) - 1;
constexpr size_t color_sections = max_s / num_colors;

template <size_t N>
const wchar_t *lookup(PrintOption opt, wchar_t (&buf)[N], size_t x, size_t y,
                      S i, S z, bool newline) {
  wchar_t ascii_shade = ascii_shades[i / ascii_shade_sections];
  wchar_t unicode_shade = unicode_shades[i / unicode_shade_sections];
  const wchar_t *color = colors[z / color_sections];
  bool ascii_use_color = ascii_shade != ascii_shades[num_ascii_shades - 1];
  const wchar_t *newline_str = newline ? L"\n" : L"";

  switch (opt) {
    case PrintOption::Color:
      swprintf(buf, N, L"%ls%c%ls%ls", ascii_use_color ? color : L"",
               ascii_shade, ascii_use_color ? reset : L"", newline_str);
      break;
    case PrintOption::Unicode:
      swprintf(buf, N, L"%c%ls", x, y, unicode_shade, newline_str);
      break;
    case PrintOption::MoveCursor:
      swprintf(buf, N, ESC L"[%zd;%zdH%c%ls", x, y, ascii_shade, newline_str);
      break;
  }

  return buf;
}

}  // end anonymous namespace

void print(PrintOption opt, S *scene_i, S *scene_z, size_t X, size_t Y) {
  if (opt != PrintOption::MoveCursor) clear_screen();
  for (size_t i = 0; i < X; ++i) {
    for (size_t j = 0; j < Y; ++j) {
      size_t idx = j * X + i;
      wchar_t buf[32];
      fputws(lookup(opt, buf, i, j, scene_i[idx], scene_z[idx], j == Y - 1),
             stdout);
    }
  }
}
