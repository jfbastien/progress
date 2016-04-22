// Licensed under the Apache License, Version 2.0.

#include "support.h"

#include <clocale>
#include <cstdio>
#include <cwchar>

#include <sys/ioctl.h>
#include <unistd.h>

void setup() { setlocale(LC_ALL, "C.UTF-8"); }

void clear_screen() { fputws(L"\033[2J\033[1;1H", stdout); }

std::pair<size_t, size_t> screen_size() {
  winsize size;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
  return {size.ws_row, size.ws_col};
}
