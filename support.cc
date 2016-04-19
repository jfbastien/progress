// Licensed under the Apache License, Version 2.0.

#include "support.h"
#include <ios>
#include <iostream>
#include <locale>

void setup() {
  std::ios_base::sync_with_stdio(false);
  std::wcout.imbue(std::locale("en_US.UTF-8"));
}

void clear_screen() { std::wcout << "\033[2J\033[1;1H"; }
