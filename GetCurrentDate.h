#pragma once
#include <ctime>
#include <sstream>
#include <iomanip>
#include <string>


// Función para obtener la fecha actual
std::string getCurrentDate() {

    // La hora inicial empieza en 0
    time_t t = time(0);

    // Posteriormente, se obtiene la fecha actua
    tm now;
    localtime_s(&now, &t);
    std::stringstream dateStream;
    dateStream << std::put_time(&now, "%Y-%m-%d");
    return dateStream.str();
}
