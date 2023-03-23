#pragma once
#include <windows.h>
// Función para mostrar el texto rojo
void showRedConsoleMessage(HANDLE hConsole) {
    SetConsoleTextAttribute(hConsole, 4);
}

// Función para mostrar el texto verde
void showGreenConsoleMessage(HANDLE hConsole) {
    SetConsoleTextAttribute(hConsole, 2);
}

// Función para mostrar el texto por defecto
void showDefaultColorConsoleMessage(HANDLE hConsole) {
    SetConsoleTextAttribute(hConsole, 15);
}