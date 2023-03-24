#pragma once

#include "Subject.h"

// Constante para el número máximo de materias por trimestre
const int maxSubjectsPerQuarter = 7;

// Estructura para el trimestre
struct Quarter {
	int quarterNumber;
	int maxSubjects;
	Subject subjects[maxSubjectsPerQuarter];
};