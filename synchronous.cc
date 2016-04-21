// Licensed under the Apache License, Version 2.0.

#include "mandelbrot.h"
#include "print.h"
#include "support.h"

int main() {
  setup();

  uint8_t scene_i[45][130];
  uint8_t scene_z[45][130];

  for (size_t i = 1; i != 100; ++i) {
    mandelbrot(0.3f, -0.2f, 0.2f, 0.2f, scene_i, scene_z, i);
    clear_screen();
    print(scene_i, scene_z);
  }

  return 0;
}
