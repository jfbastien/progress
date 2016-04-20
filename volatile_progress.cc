// Licensed under the Apache License, Version 2.0.

#include <iostream>
#include <string>
#include <thread>
#include "compiler.h"
#include "mandelbrot.h"
#include "print.h"
#include "support.h"

constexpr size_t total_iterations = 1000;

NO_INLINE void wait(volatile size_t *iterations) {
  std::wcout << L"Computing [";
  size_t last_seen_iteration = 0;
  size_t last_printed_percent = 0;
  do {
    size_t i = *iterations;
    if (i != last_seen_iteration) {
      last_seen_iteration = i;
      size_t percent_done = last_seen_iteration * 100 / total_iterations;
      if (percent_done != last_printed_percent) {
        std::wstring bars(percent_done - last_printed_percent, L'█');
        std::wcout << bars;
        std::flush(std::wcout);
        last_printed_percent = percent_done;
      }
    }
  } while (last_seen_iteration != total_iterations - 1);
  std::wcout << L"]\n" << std::endl;
}

int main() {
  setup();

  volatile size_t iterations = 0;
  uint8_t scene[45][130] = {0};

  std::thread t([&scene, &iterations]() {
    for (size_t i = 1; i != total_iterations; ++i) {
      ++iterations;
      mandelbrot(0.3, -0.2, 0.2, 0.2, scene, i);
    }
  });

  wait(&iterations);

  t.join();

  print(scene);
  std::wcout << std::endl;

  return 0;
}
