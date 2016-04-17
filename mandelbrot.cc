// Licensed under the Apache License, Version 2.0.

#include "mandelbrot.h"
#include <ios>
#include <iostream>
#include <locale>
#include <thread>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::wcout.imbue(std::locale("en_US.UTF-8"));

  uint8_t scene[45][140] = {0};
  for (size_t i = 1; i != 100; ++i) {
    mandelbrot(-1.5, -1.5, 2.0, 3.0, scene, i);
    std::wcout << "\033[2J\033[1;1H";  // Clear screen.
    print(scene);
    std::wcout << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(64));
  }

  return 0;
}
