// Licensed under the Apache License, Version 2.0.

#ifndef print_h
#define print_h

#include "compiler.h"
#include "support.h"

#include <cstddef>
#include <cstdint>

enum class PrintOption {
  Color,
  Unicode,
  MoveCursor,
};

void print_one(PrintOption opt, wchar_t *buf, size_t N, size_t x, size_t y,
               uint8_t i, uint8_t z, bool newline);

namespace {
template <typename Scene>
void print(PrintOption opt, Scene *scene_i, Scene *scene_z, size_t X,
           size_t Y) {
  if (opt != PrintOption::MoveCursor) clear_screen();
  for (size_t i = 0; i < X; ++i) {
    for (size_t j = 0; j < Y; ++j) {
      size_t idx = j * X + i;
      wchar_t buf[32];
      print_one(opt, buf, sizeof(buf) / sizeof(buf[0]), i, j,
                scene_i[idx].load(), scene_z[idx].load(), j == Y - 1);
    }
  }
}
}

#endif
