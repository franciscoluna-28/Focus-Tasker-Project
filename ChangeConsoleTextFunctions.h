#pragma once
#include <windows.h>
// Funci�n para mostrar el texto rojo
void showRedConsoleMessage(HANDLE hConsole) {
    SetConsoleTextAttribute(hConsole, 4);
}

// Funci�n para mostrar el texto verde
void showGreenConsoleMessage(HANDLE hConsole) {
    SetConsoleTextAttribute(hConsole, 2);
}

// Funci�n para mostrar el texto por defecto
void showDefaultColorConsoleMessage(HANDLE hConsole) {
    SetConsoleTextAttribute(hConsole, 15);
}