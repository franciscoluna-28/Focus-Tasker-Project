#pragma once

#include <string>
#include "Quarter.h"

// Constante para el número total de trimestres
const int numberOfQuarters = 12;

// Estructura para la carrera
struct Career {
	std::string name;
	Quarter quarter[numberOfQuarters];
};