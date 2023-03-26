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
#include "SubjectsAndOptionsPerCareer.h"
#include <ctime>
#include <sstream>
#include <hpdf.h>
#include <algorithm>
#undef max



// COMANDOS 
//git clone https ://github.com/Microsoft/vcpkg.git -> 
// En una nueva carpeta dentro de c, llamada dev
//cd vcpkg
//bootstrap-vcpkg.bat
//vcpkg integrate install
//./vcpkg install libharu



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

// Función para obtener unicamente la fecha actual
std::string getCurrentDate() {
    std::time_t now = std::time(nullptr);
    std::tm tm_now;
    localtime_s(&tm_now, &now);
    std::ostringstream dateStream;
    dateStream << tm_now.tm_year + 1900 << "-" <<
        tm_now.tm_mon + 1 << "-" <<
        tm_now.tm_mday;
    return dateStream.str();
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

//MENCIONES
// Ing. Sistemas - Inteligencia Artificial, Biomédica, programación
// Psicología - Mención Clínica,

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
    showDefaultColorConsoleMessage();
    std::cout << "\n------------------------------------------------------------" << std::endl;
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

// Función para verificar si el número de la carrera es válido
bool isValidCareer(int careerNumber) {
    return (careerNumber >= 1 && careerNumber <= careerOptions.size()) ? true : false;
}


// TABLAS DE CARRERA

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

// Función para imprimir el encabezado de la tabla
void printTableHeader(int subjectNameWidth, int creditNumberWidth, bool showCredits = false) {
    std::cout << std::left << std::setw(subjectNameWidth) << "Nombre de la Materia";
    if (showCredits) {
        std::cout << "|" << std::right << std::setw(creditNumberWidth) << "Creditos" << "|\n";
    }
    else {
        std::cout << "\n";
    }
}

// Función para imprimir una fila de la tabla con el nombre de la materia y los créditos correspondientes
void printTableRow(const Subject& subject, int subjectNameWidth,
    int creditNumberWidth, bool showCredits, int& totalCredits) {
    std::cout << std::left << std::setw(subjectNameWidth) << subject.name;
    if (showCredits) {
        std::cout << "|" << std::right << std::setw(creditNumberWidth) << subject.credits << "|\n";
        totalCredits += subject.credits;
    }
    else {
        std::cout << "\n";
    }
}

// Función para imprimir la fila de total de créditos
 void printTotalCreditsRow(int subjectNameWidth, int creditNumberWidth, int totalCredits) {
        std::cout << std::left << std::setw(subjectNameWidth) << "Total de Creditos" << "|";
        std::cout << std::right << std::setw(creditNumberWidth) << totalCredits << "|\n";
    }

// Función para mostrar la tabla de la carrera
 void showCurrentCareerTable(int careerNumber, int subjectNameWidth, int creditNumberWidth,
     const Career* careers, int selectedUserQuarter, bool showCredits) {

     const Career& career = careers[careerNumber - 1];
     std::cout << "Carrera: " << career.name << "\n\n";

     // Mostrar menú de selección
     std::string selection = "";
     bool showAllQuarters = false;

     while (selection != "s" && selection != "n") {
         std::cout << "Desea ver todos los trimestres? (s/n): ";
         std::cin >> selection;
         if (selection == "s") {
             showAllQuarters = true;
         }
         else if (selection == "n") {
             showAllQuarters = false;
         }
         else {
             std::cout << "Por favor, ingrese una opción válida.\n";
         }
     }

     for (const Quarter& quarter : career.quarter) {
         if (showAllQuarters || quarter.quarterNumber == selectedUserQuarter) {

             int nonEmptySubjects = 0;
             for (const Subject& subject : quarter.subjects) {
                 if (!subject.name.empty()) {
                     nonEmptySubjects++;
                 }
             }

             // Solo mostrar los trimestres que tengan materias
             if (nonEmptySubjects > 0) {
                 std::cout << "Trimestre " << quarter.quarterNumber << ":\n";

                 printTableHeader(subjectNameWidth, creditNumberWidth);

                 int totalCredits = 0;
                 for (const Subject& subject : quarter.subjects) {
                     if (!subject.name.empty()) {
                         printTableRow(subject, subjectNameWidth, creditNumberWidth, showCredits, totalCredits);
                     }
                 }

                 printTotalCreditsRow(subjectNameWidth, creditNumberWidth, totalCredits);

                 std::cout << "\n";
             }
         }
     }
 }
 // Esta función incluye selección de (s/n)


 // Función para unicamente mostrar la tabla del trimestre actual
 // para las tareas
 void showCurrentQuarterSubjects(const Quarter& quarter, int subjectNameWidth, int creditNumberWidth, bool showCredits) {

     int nonEmptySubjects = 0;
     for (const Subject& subject : quarter.subjects) {
         if (!subject.name.empty()) {
             nonEmptySubjects++;
         }
     }

     // Solo mostrar el trimestre actual si tiene materias
     if (nonEmptySubjects > 0) {
         std::cout << "\nTrimestre " << quarter.quarterNumber << ":\n";

         printTableHeader(subjectNameWidth, creditNumberWidth);

         int totalCredits = 0;
         for (const Subject& subject : quarter.subjects) {
             if (!subject.name.empty()) {
                 printTableRow(subject, subjectNameWidth, creditNumberWidth, showCredits, totalCredits);
             }
         }

         printTotalCreditsRow(subjectNameWidth, creditNumberWidth, totalCredits);

         std::cout << "\n";
     }
 }


 // AÑADIR TAREAS Y CONVERTIR A PDF


// Función para convertir a PDF
 void generatePDF(Quarter quarter) {
     HPDF_Doc pdf = HPDF_New(NULL, NULL);
     HPDF_STATUS status;
     HPDF_Page page = HPDF_AddPage(pdf);
     status = HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
     if (status != HPDF_OK) {
         std::cerr << "Error al establecer el tamaño de la página" << std::endl;
         HPDF_Free(pdf);
         return;
     }
     HPDF_Font font = HPDF_GetFont(pdf, "Helvetica", NULL);
     HPDF_Page_SetFontAndSize(page, font, 12);
     HPDF_Page_BeginText(page);
     HPDF_Page_MoveTextPos(page, 50, 750);
     HPDF_Page_ShowText(page, "Lista de tareas");
     HPDF_Page_MoveTextPos(page, 0, -20);
     int numLines = 0;
     for (int i = 0; i < quarter.maxSubjects; i++) {
         if (quarter.subjects[i].name != "") {
             HPDF_Page_ShowText(page, (std::string("Tareas para ") + quarter.subjects[i].name).c_str());
             HPDF_Page_MoveTextPos(page, 0, -20);
         }
         for (int j = 0; j < quarter.subjects[i].numTasks; j++) {
             Task task = quarter.subjects[i].tasks[j];
             HPDF_Page_ShowText(page, (std::string("Tarea #") + std::to_string(j + 1)).c_str());
             HPDF_Page_MoveTextPos(page, 0, -20);
             HPDF_Page_ShowText(page, (std::string("Nombre de la tarea: ") + task.taskName).c_str());
             HPDF_Page_MoveTextPos(page, 0, -20);
             HPDF_Page_ShowText(page, (std::string("Fecha de entrega: ") + task.deliveryDate).c_str());
             HPDF_Page_MoveTextPos(page, 0, -20);
             HPDF_Page_ShowText(page, (std::string("Descripción: ") + task.description).c_str());
             HPDF_Page_MoveTextPos(page, 0, -20);
             HPDF_Page_ShowText(page, (std::string("Prioridad: ") + std::to_string(task.priority)).c_str());
             HPDF_Page_MoveTextPos(page, 0, -20);
             HPDF_Page_ShowText(page, "----------------------------------------");
             HPDF_Page_MoveTextPos(page, 0, -20);
             numLines += 7;
             if (numLines >= 35
                 ) {
                 HPDF_Page_EndText(page);
                 page = HPDF_AddPage(pdf);
                 status = HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
                 if (status != HPDF_OK) {
                     std::cerr << "Error al establecer el tamaño de la página" << std::endl;
                     HPDF_Free(pdf);
                     return;
                 }
                 HPDF_Page_SetFontAndSize(page, font, 12);
                 HPDF_Page_BeginText(page);
                 HPDF_Page_MoveTextPos(page, 50, 750);
                 numLines = 0;
             }
         }
     }
     HPDF_Page_EndText(page);
     HPDF_SaveToFile(pdf, "task_list.pdf");
     HPDF_Free(pdf);
 }

 // Función para imprimir las tareas añadidas
 void showTasks(Quarter quarter) {
     showDefaultColorConsoleMessage();
     for (int i = 0; i < quarter.maxSubjects; i++) { // Recorre todas las materias en el trimestre
         if(quarter.subjects[i].name != "") // Evita que se muestren materias vacias
         std::cout << "Tareas para " << quarter.subjects[i].name << ":" << quarter.subjects[i].numTasks << std::endl;
         for (int j = 0; j < quarter.subjects[i].numTasks; j++) { // Recorre todas las tareas de la materia actual
             Task task = quarter.subjects[i].tasks[j];
             std::cout << "Tarea #" << j + 1 << std::endl;
             std::cout << "Nombre de la tarea: " << task.taskName << std::endl;
             std::cout << "Fecha de entrega: " << task.deliveryDate << std::endl;
             std::cout << "Descripción: " << task.description << std::endl;
             std::cout << "Prioridad: " << task.priority << std::endl;
             std::cout << std::endl;
         }
     }
 }

// Función para agregar tareas
 void addTasks(Quarter& quarter) {

     showDefaultColorConsoleMessage();
     for (int i = 0; i < quarter.maxSubjects; i++) { // Recorre todas las materias en el trimestre
         int taskAmount;
         std::cout << "\nIngrese la cantidad de tareas para " << quarter.subjects[i].name << ": " << "(Maximo de 4)" << std::endl;
         while (!(std::cin >> taskAmount)) { // Mientras la entrada no sea un número, se seguirá pidiendo una cantidad de tareas válida
             showRedConsoleMessage();
             std::cout << "\n Por favor, ingrese un número válido" << std::endl;
                
             std::cin.clear();
             while (std::cin.get() != '\n') {} // Limpiar el buffer de entrada para que no interfiera con la siguiente entrada de datos
         }
         std::cin.ignore(); // Limpiar el buffer de entrada para que no interfiera con la siguiente entrada de datos

         if (taskAmount > 4) { // Si la cantidad de tareas es mayor a 4, se establece a 4
             std::cout << "\nValor superior al establecido, estableciendo su límite de tareas 4..." << std::endl;
             taskAmount = 4;
         }


         for (int j = 0; j < taskAmount; j++) { // Ingresa los detalles de cada tarea
             Task task;
             task.taskName = "";
             task.currentDate = "";
             task.deliveryDate = "";
             task.description = "";
             task.priority = 0;
             std::cout << "\nTarea # " << j + 1;

             std::cout << "\nIngrese el nombre de la tarea: ";
             std::getline(std::cin, task.taskName);

             std::cout << "\nFecha de creación de la tarea " << getCurrentDate() << std::endl;

             std::cout << "\nIngrese la fecha de entrega de la tarea (formato DD/MM/AAAA): ";
             std::getline(std::cin, task.deliveryDate);

             std::cout << "\nIngrese una descripcion de la tarea: ";
             std::getline(std::cin, task.description);

             bool validPriority = false;
             while (!validPriority) { // Mientras la entrada no sea válida, se seguirá pidiendo una prioridad válida
                 showDefaultColorConsoleMessage();
                 std::cout << "\nIngrese la prioridad de la tarea (1 a 5): ";
                 std::string priorityStr;
                 std::getline(std::cin, priorityStr);

                 try {
                     int priority = std::stoi(priorityStr);
                     if (priority < 1 || priority > 5) { // Si la prioridad está fuera del rango permitido, se pide al usuario que ingrese una prioridad válida
                         showRedConsoleMessage();
                         std::cout << "\nLa prioridad debe ser un número entre 1 y 5" << std::endl;
                     }
                     else { // Si la prioridad es válida, se establece en la tarea actual
                         task.priority = priority;
                         validPriority = true;
                     }
                 }
                 catch (std::invalid_argument&) { // Si la entrada no es un número, se pide al usuario que ingrese una prioridad válida
                     showRedConsoleMessage();
                     std::cout << "\nLa prioridad debe ser un número entre 1 y 5" << std::endl;
                 }
             }

             showDefaultColorConsoleMessage();
             // Agrega la tarea a la materia actual
             quarter.subjects[i].tasks[j] = task;
             quarter.subjects[i].numTasks++;
         }
     }
 };


 // REGISTRAR USUARIO

 // Función para validar strings únicamente con letras
 bool isValidString(const std::string& string)
 {
     for (char c : string) {
         if (!std::isalpha(c)) {
             return false;
         }
     }
     return true;
 }



 // Función para obtener un nombre o apellido válido
 std::string insertValidNameOrLastName(std::string stringToValidate, std::string insertMessage,
     std::string warningMessage, std::string sucessMessage) {

     showDefaultColorConsoleMessage();
     bool isStringValid = false;
     while (!isStringValid) {
         showDefaultColorConsoleMessage();
         std::cout << insertMessage;
         std::cin >> stringToValidate;

         showGreenConsoleMessage();
         if (isValidString(stringToValidate)) {
             isStringValid = true;
             std::cout << sucessMessage;
         }
         else {
             showRedConsoleMessage();
             std::cout << warningMessage;
             char answer;
             std::cin >> answer;
             if (answer == 'n' || answer == 'N') {
                 break;
             }
         }
     }

     showDefaultColorConsoleMessage();
     return stringToValidate;
 }
 

 // Función para verificar
 bool isValidDocument(int& number) {
     while (true) {
         std::string numberString;
         std::cout << "Ingrese el número de cedula: " << std::endl;
         std::cin >> numberString;

         try {
             number = std::stoi(numberString);
         }
         catch (const std::invalid_argument&) {
             std::cout << "El valor ingresado no es un numero válido. Por favor, intentelo de nuevo." << std::endl;
             continue;
         }

         std::string validNumberString = std::to_string(number);

         if (validNumberString.size() >= 7 && validNumberString.size() <= 8) {
             return true;
         }
         else {
             std::cout << "El numero debe tener entre 7 y 8 digitos. Por favor, intentelo de nuevo." << std::endl;
             continue;
         }
     }
 }

 // Función para verificar la edad del usuario (10 - 99)
 bool isAgeValid(int& age) {
     while (true) {
     std::string numberString;
     std::cout << "\nIngrese su edad: " << std::endl;
     std::cin >> numberString;

     try {
         age = std::stoi(numberString);
     }
     catch (const std::invalid_argument&) {
         std::cout << "El valor ingresado no es un numero válido. Por favor, intentelo de nuevo." << std::endl;
         continue;
     }

     std::string validNumberString = std::to_string(age);

     if (validNumberString.size() == 2) {
         return true;
     }
     else {
         std::cout << "El número debe tener 2 dígitos. Por favor, inténtelo de nuevo." << std::endl;
         continue;
     }
     }
 }
     
 






 















// CONSTANTES A UTILIZAR POR EL SISTEMA

const int MAX_QUARTERS = 12;
const int subjectsWidth = 30; 
const int creditsWidth = 10;

// Los valores de subjectsWidth y creditsWidth, indican
// el ancho de campo

// VARIABLES DADAS POR EL USUARIO

// VARIABLES RELACIONADAS CON EL TRIMESTRE
int userQuarter;



// VARIABLES RELACIONADAS CON LA CARRERA
int userCareer;
int mainMenuUserChoice;
int maxCareersLimit;
int mentionNumber;
Quarter studentSelectedQuarter = subjectsAndOptionsPerCareer[userCareer - 1]
.quarter[userQuarter - 1];



// VARIABLES RELACIONADAS CON LOS CREDITOS
bool showCareerPathCredits;

// VARIABLES RELACIONADAS CON EL REGISTRO PRINCIPAL

int userCedula;
std::string userName;
std::string userLastName;
int userAge;

int main()
{

    // Pidiendo el nombre y el apellido del usuario 
    userName = insertValidNameOrLastName("", "\nIngrese su nombre (solo carácteres alfabeticos): ",
        "\nLo siento, su nombre solo debe contener letras. ¿Desea intentar de nuevo? (s/n): ",
        "\nSu nombre se ha registrado exitosamente dentro del sistema!");

    userLastName = insertValidNameOrLastName("", "\nAhora, ingrese su apellido (solo carácteres alfabeticos): ",
        "\nLo siento su apellido solo debe contener letras. ¿Desea intentar de nuevo? (s/n): ",
        "\nSu apellido se ha registrado exitosamente dentro del sistema!");
    // Se verifica que la cédula sea válida
    isValidDocument(userCedula);


    // Se verifica que el rango de edad esté entre 12 y 99
    isAgeValid(userAge);
    


    // Mostrar los datos resultantes del usuario
    
    std::cout << "Su nombre completo es: " << userName << " " << userLastName << std::endl;
    std::cout << "Su cedula de identidad es: " << userCedula << std::endl;
    std::cout << "Su edad es: " << userAge << std::endl;


    // Menú para el sistema
    std::cout << "Bienvenido! Que desea hacer?" << std::endl;
    std::cout << "Presione '1' y 'enter' para entrar al sistema de gestion de tareas de la universidad" << std::endl;
    std::cout << "Presione '2' y 'enter' para ver las preguntas frecuentes (FAQ)" << std::endl;
    std::cout << "Presione '3' y 'enter' para utilizar un pomodoro" << std::endl;
    std::cout << "Estresado por los estudios?, puedes jugar a adivinar un número contra el sistema presionando '4' y 'enter'" << std::endl;
    std::cin >> mainMenuUserChoice;

    switch (mainMenuUserChoice) {

    // Si el usuario presiona 1
    case 1: 

        getCareerCreditsAndTrimester(MAX_QUARTERS,
            userCareer, careerOptions, userQuarter);

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

        // Se muestra la tabla de la carrera dependiendo del parámetro de showCareerPathCredits
        showCurrentCareerTable(userCareer, subjectsWidth, creditsWidth,
            subjectsAndOptionsPerCareer, userQuarter, showCareerPathCredits);

        //Se muestra la tabla de materias trimestre actual
        showCurrentQuarterSubjects(studentSelectedQuarter, subjectsWidth, creditsWidth,
            showCareerPathCredits);

        //Se ejecuta la función para añadir tareas
        addTasks(studentSelectedQuarter);

        // Parámetro de decisión en la opción de añadir
        //int a = 0;

       //std::cout << "Usuario, que desea hacer?" << std::endl;
       //std::cout << "presione 1 para crear un pdf con las tareas añadidas" << std::endl;
       //std::cout << "presione 2 para ver las tareas añadidas" << std::endl;
       //std::cout << "presione 3 para ver las tareas añadidas y generar un pdf" << std::endl;
       //std::cin >> a;

       //switch (a)
       //{
       //case 1:
           //generatePDF(studentSelectedQuarter);
           //std::cout << "PDF generado exitosamente!";
           //break;

       //case 2:
           //showTasks(studentSelectedQuarter);
           //int exitValue;
           //std::cin >> exitValue;
           //break;

       //case 3:
           //showTasks(studentSelectedQuarter);
           //generatePDF(studentSelectedQuarter);

       //default:
           //break;
       //}



        break;
    

         //case 4:
             //GuessNumberGame game;
             //game.playGame();
             //break;
}
    return 0;
    }


#undef max



    


    // Se crea la estructura para el trimestre de acuerdo a los datos dados 
    // en getCareerCreditsAndTrimester

    // Crear objeto Trimestre para las tareas


    
 


        //std::cout << "A continuacion, se muestra la respectiva tabla de las materias del trimestre que cursa actualmente" << std::endl;







        // Menú despúes de realizar la selección de tareas
       







   

    

    // Se le pediría al usuario que ingrese su carrera y trimestre
    //getCareerCreditsAndTrimester(MAX_QUARTERS,
        //userCareer, careerOptions, userQuarter);

    //if (!userQuarter) exit(0);

    //if (isValidCareer(userCareer)) {
        //showCareerPathCredits = getShowCurrentCredits();

        //std::cout << "trimestre: " << userQuarter << std::endl;

        //std::cout << "carrera: " << userCareer << std::endl;

        //std::cout << "opcion de ver créditos: " << showCareerPathCredits;
    //}
    //else {
        //std::cout << "La carrera ingresada no es válida. Por favor, ingrese una carrera válida.";
    //}

    //showCurrentCareerTable(userCareer, subjectsWidth, creditsWidth,
        //subjectsAndOptionsPerCareer, userQuarter, showCareerPathCredits);

    // Se crea la estructura para el trimestre de acuerdo a los datos dados 
    // en getCareerCreditsAndTrimester

    // Crear objeto Trimestre para las tareas
        //Quarter studentSelectedQuarter = subjectsAndOptionsPerCareer[userCareer - 1]
            //.quarter[userQuarter - 1];


        //std::cout << "A continuacion, se muestra la respectiva tabla de las materias del trimestre que cursa actualmente" << std::endl;

        //Se muestra la tabla de materias trimestre actual
        //showCurrentQuarterSubjects(studentSelectedQuarter, subjectsWidth, creditsWidth,
            //showCareerPathCredits);

        // Se ejecuta la función para añadir tareas
        //addTasks(studentSelectedQuarter);

        //int a;



        // Menú despúes de realizar la selección de tareas
        //std::cout << "Usuario, que desea hacer?" << std::endl;
        //std::cout << "presione 1 para crear un pdf con las tareas añadidas" << std::endl;
        //std::cout << "presione 2 para ver las tareas añadidas" << std::endl;
        //std::cin >> a;

        //switch (a)
        //{
        //case 1:
            //generatePDF(studentSelectedQuarter);
            //std::cout << "PDF generado exitosamente!";
            //break;

        //case 2:
            //showTasks(studentSelectedQuarter);
            //int exitValue;


            //std::cin >> exitValue;

        //default:
            //break;
        //}





