#pragma once

#include <string>
#include "Task.h"

// Estructura para la materia 
struct Subject {
	std::string name;
	int credits;
	int mentionNumber;
	Task tasks[4];
	int numTasks;
};