// Licensed under the Apache License, Version 2.0.

#include "support.h"

#include <clocale>
#include <cstdio>
#include <cwchar>

void setup() { setlocale(LC_ALL, "en_US.UTF-8"); }

void clear_screen() { fputws(L"\033[2J\033[1;1H", stdout); }
