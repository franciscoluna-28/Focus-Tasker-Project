// Sistema de Gestión de Tareas UBA Expociencia.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <string>
#include <vector>
#include <Windows.h>
#include "GuessNumberGame.h"

void showRedConsoleMessage() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 4);
}

void showGreenConsoleMessage() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 2);
}

void showDefaultColorConsoleMessage() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 15);
}

// Identificador para manejar la librería de Windows.h
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

// Función para verificar si se han ingresado únicamente carácteres alfabéticos
bool containsOnlyLetters(std::string const& str) {
    return str.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") ==
        std::string::npos;
}



// Función para obtener un número entero válido dentro de un rango específico
int getValidNumber(int min, int max,
    const std::string& message) {
    int numero = 0;
    bool valido = false;

    // Mientras que el booleano de válido sea falsy
    // Esta parte se ejecutará
    while (!valido) {
        std::cout << message << " (" << min << "-" << max << "): ";
        std::cin >> numero;


        if (numero < min || numero > max) {
            std::cout << "Número inválido, debe ingresar un número entre " << min <<
                " y " << max << "." << std::endl;
        }
        else {
            valido = true;
        }
    }

    return numero;
}

// Vector con las respectivas carreras
std::vector<std::string> careerOptions = { "Ingenieria de Sistemas",
"Psicologia", "Ingenieria Electrica" };

// SELECCIÓN DE CARRERA Y OPCIONES DE CARRERA

// Función para obtener un trimestre válido
int getValidQuarter(int maxQuarters) {
    int currentQuarter = 0;
    char respuesta;
    std::string input;

    do {
        showDefaultColorConsoleMessage();
        std::cout << "\nIngrese el trimestre en el que se encuentra actualmente (1-" << maxQuarters << "): ";
        std::cin >> input;

        // Verificar si la entrada es un número válido
        if (input.find_first_not_of("0123456789") != std::string::npos) {
            showRedConsoleMessage();
            std::cout << "\nEntrada invalida, debe ingresar un numero." << std::endl;
            continue;
        }

        currentQuarter = std::stoi(input);

        if (currentQuarter <= 0 || currentQuarter > maxQuarters) {
            std::cout << "\nTrimestre invalido, debe ingresar un numero entre 1 y " << maxQuarters << "." << std::endl;

            std::cout << "\nDesea ingresar un nuevo trimestre? (s/n): ";
            std::cin >> respuesta;
            if (respuesta == 'n' || respuesta == 'N') return 0;
        }
    } while (currentQuarter <= 0 || currentQuarter > maxQuarters);

    showGreenConsoleMessage();
    std::cout << "\nTrimestre valido, usted actualmente se encuentra en el trimestre " << currentQuarter << std::endl;
    return currentQuarter;
}

// Función para obtener la selección de carrera del usuario
int getCareerSelection(std::vector<std::string> possibleCareerOptions) {
    int seleccion;
    std::cin >> seleccion;

    if (seleccion == 0) {
        return -1; // Devuelve -1 para indicar que el usuario quiere retroceder
    }
    else if (seleccion >= 1 && seleccion <= possibleCareerOptions.size()) {
        return seleccion;
    }
    else {
        std::cout << "\nNumero Invalido. Por favor, intente de nuevo." << std::endl;
        return getCareerSelection(possibleCareerOptions); // Llamada recursiva para obtener una selección válida
    }
}

// Función para imprimir las opciones de selección de carrera
void showCareerOptions(const std::vector<std::string>& possibleCareerOptions) {
    std::cout << "------------------------------------------------------------" << std::endl;
    std::cout << "Por favor, indique la carrera que actualmente está cursando" << std::endl;
    for (int i = 0; i < possibleCareerOptions.size(); i++) {
        std::cout << "Escriba '" << i + 1 << "' para elegir " << possibleCareerOptions[i] << std::endl;
    }
  
}

// Obtener la selección del usuario y llamar sub - funciones
bool getCareerCreditsAndTrimester(int maxQuarters, int& carreraUsuario,
    const std::vector<std::string>& possibleCareerOptions, int& userQuarter) {
    showCareerOptions(possibleCareerOptions);
    int seleccion = getCareerSelection(possibleCareerOptions);

    if (seleccion == -1) {
        return false;
    }
    else {
        showGreenConsoleMessage();
        std::cout << "\nUsted ha escogido la carrera de " << possibleCareerOptions
            [static_cast<size_t>(seleccion) - 1] << std::endl;
        carreraUsuario = seleccion;
        userQuarter = getValidQuarter(maxQuarters);
        return true;
    }
}
//De esta manera, se llamará a getCareerSelection dentro de 
// getCareerCreditsAndTrimester y se asignará el valor devuelto
// Función para ver los créditos (trigger)

// Función para mostrar los créditos en las tablas de la carrera
bool getShowCurrentCredits() {
    char respuesta;
    do {
        showDefaultColorConsoleMessage();
        std::cout << "\nDesea ver los créditos disponibles en cada unidad materia correspondiente al pensum de la materia que eligió?" << std::endl;
        std::cout << "\nEscriba '1' y presione 'Enter' para activar esta opción o '0' para desactivarla" << std::endl;
        std::cin >> respuesta;

        if (respuesta == '1') {
            return true;
        }
        else if (respuesta == '0') {
            return false;
        }
        showRedConsoleMessage();
        std::cout << "Entrada no válida. Por favor ingrese un número válido (0 o 1)." << std::endl;
    } while (true);
}


// Función para verificar si el número de la carrera es válido
bool isValidCareer(int careerNumber) {
    return (careerNumber >= 1 && careerNumber <= careerOptions.size()) ? true : false;
}

// CONSTANTES A UTILIZAR POR EL SISTEMA
const int MAX_QUARTERS = 12;

// VARIABLES DADAS POR EL USUARIO
int userQuarter;
bool showCareerPathCredits;
int userCareer;
int mainMenuUserChoice;




int main()
{

    // Se imprimen las opciones a mostrar para la carrera del usuario

    // Menú para el sistema
    std::cout << "Bienvenido! Que desea hacer?" << std::endl;
    std::cout << "Presione '1' y 'enter' para entrar al sistema de gestión de tareas por trimestre" << std::endl;
    std::cout << "Presione '2' y 'enter' para ver los pensum disponibles" << std::endl;
    std::cout << "Presione '3' y 'enter' para ver las preguntas frecuentes (FAQ)" << std::endl;
    std::cout << "Presione '4' y 'enter' para utilizar un pomodoro" << std::endl;
    std::cout << "Estresado por los estudios?, puedes jugar a adivinar un número contra el sistema presionando '5' y 'enter'" << std::endl;
    std::cin >> mainMenuUserChoice;

    switch(mainMenuUserChoice){
        case 5:
            GuessNumberGame game;
            game.playGame();
    }












    //getCareerCreditsAndTrimester(MAX_QUARTERS,
        //userCareer, careerOptions, userQuarter);

    if (!userQuarter) exit(0);

    if (isValidCareer(userCareer)) {
        showCareerPathCredits = getShowCurrentCredits();

        std::cout << "trimestre: " << userQuarter << std::endl;

        std::cout << "carrera: " << userCareer << std::endl;

        std::cout << "opcion de ver créditos: " << showCareerPathCredits;
    }
    else {
        std::cout << "La carrera ingresada no es válida. Por favor, ingrese una carrera válida.";
    }



    
}

