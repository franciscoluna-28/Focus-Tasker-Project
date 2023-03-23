#pragma once
#include <string>

// Estructura para la tarea
struct Task {
	std::string taskName, currentDate, deliveryDate, description;
	int priority = 0;
};