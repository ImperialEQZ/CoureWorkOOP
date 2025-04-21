#include <windows.h>
#include "ControlUnit.h"
int main() {
    SetConsoleOutputCP(CP_UTF8);
    ControlUnit control;
    control.run();
    return 0;
}