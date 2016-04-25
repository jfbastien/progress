// Licensed under the Apache License, Version 2.0.

#include "compiler.h"
#include "mandelbrot.h"
#include "print.h"
#include "support.h"

#include <cwchar>
#include <string>
#include <thread>

constexpr size_t total_iterations = 1000;

NO_INLINE void wait(volatile size_t *iterations) {
  fputws(L"Computing [", stdout);
  size_t last_seen_iteration = 0;
  size_t last_printed_percent = 0;
  do {
    size_t i = *iterations;
    if (i != last_seen_iteration) {
      last_seen_iteration = i;
      size_t percent_done = last_seen_iteration * 100 / total_iterations;
      if (percent_done != last_printed_percent) {
        std::wstring bars(percent_done - last_printed_percent, L'█');
        fputws(bars.c_str(), stdout);
        fflush(stdout);
        last_printed_percent = percent_done;
      }
    }
  } while (last_seen_iteration != total_iterations - 1);
  fputws(L"]\n", stdout);
  fflush(stdout);
}

int main() {
  setup();
  clear_screen();

  size_t width, height;
  std::tie(width, height) = screen_size();
  auto scene_i = new uint8_t[width * height];
  auto scene_z = new uint8_t[width * height];

  volatile size_t iterations = 0;

  std::thread t([&scene_i, &scene_z, &iterations, width, height]() {
    for (size_t i = 1; i != total_iterations; ++i) {
      ++iterations;
      mandelbrot(0.3f, -0.2f, 0.2f, 0.2f, scene_i, scene_z, width, height, i);
    }
  });
  wait(&iterations);
  t.join();

  print(PrintOption::Color, scene_i, scene_z, width, height);

  delete[] scene_z;
  delete[] scene_i;

  return 0;
}
