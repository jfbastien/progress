// Licensed under the Apache License, Version 2.0.

#ifndef print_h
#define print_h

#include "compiler.h"

#include <cstddef>
#include <cstdint>

enum class PrintOption {
  Color,
  Unicode,
  MoveCursor,
};

void print(PrintOption opt, uint8_t *scene_i, uint8_t *scene_z, size_t X,
           size_t Y);

#endif
