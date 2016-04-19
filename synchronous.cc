// Licensed under the Apache License, Version 2.0.

#include "mandelbrot.h"
#include "support.h"
#include <iostream>

int main() {
  setup();

  uint8_t scene[45][130] = {0};
  for (size_t i = 1; i != 100; ++i) {
    mandelbrot(0.3, -0.2, 0.2, 0.2, scene, i);
    clear_screen();
    print(scene);
    std::wcout << std::endl;
  }

  return 0;
}
