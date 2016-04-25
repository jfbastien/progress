// Licensed under the Apache License, Version 2.0.

#include "mandelbrot.h"
#include "print.h"
#include "support.h"

int main() {
  setup();
  clear_screen();

  size_t width, height;
  std::tie(width, height) = screen_size();
  auto scene_i = new uint8_t[width * height];
  auto scene_z = new uint8_t[width * height];

  for (size_t i = 1; i != 100; ++i) {
    mandelbrot(0.3f, -0.2f, 0.2f, 0.2f, scene_i, scene_z, width, height, i);
    print(PrintOption::Color, scene_i, scene_z, width, height);
  }

  delete[] scene_z;
  delete[] scene_i;

  return 0;
}
