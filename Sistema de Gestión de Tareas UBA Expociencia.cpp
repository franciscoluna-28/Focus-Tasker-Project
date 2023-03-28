// Sistema de Gestión de Tareas UBA Expociencia.cpp 

// Estudiantes: Oscar Medina, Carlos Ruiz y Francisco Luna
// Catedra: Programación I
// Cuarta Actividad Sumativa y Proyecto para la expociencia
// De programación I (30 - 03 - 2023)

// FAQ DEL CÓDIGO

// 1) Cómo instalar las librerías requeridas para C++ dentro de
// este proyecto? (Windows)

// R: Usamos un gestor de paquetes para C++ llamado "vcpkg"
// cuya instalación se realiza de la siguiente manera:

// Paso 1) Clonar el repositorio mediante 'git clone https://github.com/Microsoft/vcpkg.git'
// En una nueva carpeta dentro de 'C' o la unidad de disco correspondiente,
// la cual puede ser llamada preferiblemente 'dev'.
// Paso 2) Una vez clonado el repositorio, avanzamos al mismo mediante
// el comando 'cd vcpkg'.
// Paso 3) Ejecutamos 'bootstrap-vcpkg.bat'.
// Esto satisfacerá la instalación de VCPKG dentro de nuestro sistema operativo.
// Paso 4) Ejecutamos 'vcpkg integrate install'.
// Paso 5) Ejecutamos 'vcpkg install libharu'.
// Esto instalará la librería libharu necesaria para el proyecto mediante VCPKG.


// Se debe tener en cuenta que, además de la biblioteca 'libharu', 
//se pueden instalar otras bibliotecas requeridas para el proyecto utilizando 
//el comando 'vcpkg install' seguido del nombre de la biblioteca.


// 2) ¿Como se configura el entorno de desarrollo para usar las librerias
// Instaladas?
// Para configurar las librerías requeridas en C++ en Visual Studio, sigue estos pasos :

//Abre el explorador de soluciones.
// Selecciona la solución correspondiente.
// Ve a "Directorios de VC++" en las propiedades de configuración.
// Agrega la ruta de los encabezados en "Directorios de inclusión", 
// Por ejemplo : "C:\dev\vcpkg\installed\x64-windows\include".
// Agrega la ruta de las bibliotecas en "Directorios de archivo de biblioteca",
// Por ejemplo : "C:\dev\vcpkg\installed\x64-windows\lib".
// Ahora puedes incluir la librería necesaria con '#include <nombre_de_la_librería.h>


// ACLARACIONES DEL CÓDIGO

// MÓDULOS Y ESTRUCTURACIÓN
// Decidimos realizar funciones para implementar las funcionalidades
// principales de nuestro programa (Añadir tareas a materias,
// mostrar los PDFs creados, etc y encapsular la lógica de las 
// actividades secundarias dentro de clases para su posterior manejo
// dentro del programa principal.

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
#include <conio.h>
#include "Structures.h"
#include "Pomodoro.h"
#undef max


// COMANDOS 
//git clone https://github.com/Microsoft/vcpkg.git -> 
// En una nueva carpeta dentro de c, llamada dev
//cd vcpkg
//bootstrap-vcpkg.bat
//vcpkg integrate install
//./vcpkg install libharu


// Función usada para cambiar el texto a rojo en errores
void showRedConsoleMessage() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 4);
}

// Función usada para cambiar el texto a verde en mensajes de 
// Ejecución exitosa
void showGreenConsoleMessage() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 2);
}

// Función usada para mostrar el color por default
// Nuevamente
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
    dateStream << tm_now.tm_mday << "/" <<
        tm_now.tm_mon + 1 << "/" <<
        tm_now.tm_year + 1900 - 2000;
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

    if (std::cin.fail()) { // Si el último valor ingresado no es un número válido
        std::cout << "\nEntrada Invalida. Por favor, intente de nuevo." << std::endl;
        std::cin.clear(); // Borrar el estado de error de std::cin
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignorar cualquier entrada adicional hasta una nueva línea
        return getCareerSelection(possibleCareerOptions); // Llamada recursiva para obtener una selección válida
    }
    else if (seleccion == 0) {
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
        std::cout << "\nDesea ver los creditos disponibles en cada unidad materia correspondiente al pensum de la materia y mencion que eligió?" << std::endl;
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
void printTotalCreditsRow(int subjectNameWidth, int creditNumberWidth, int totalCredits, bool showCredits) {
    if (showCredits) {
        std::cout << std::left << std::setw(subjectNameWidth) << "Total de Creditos" << "|";
        std::cout << std::right << std::setw(creditNumberWidth) << totalCredits << "|\n";
    }

    // Evita que se vea un "| 0| dentro de la fila de los créditos
    else {

        // Sencillamente, se remueve el texto relacionado a los créditos
        // Cancelando la ejecución de la función mediante un return
        return; 
    }
}

// Función para mostrar la tabla de la carrera
 void showCurrentCareerTable(int careerNumber, int subjectNameWidth, int creditNumberWidth,
     const Career* careers, int selectedUserQuarter, bool showCredits, int mentionNumber) {

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
                 if (!subject.name.empty() && (subject.mentionNumber == 0 || subject.mentionNumber == mentionNumber)) {
                     nonEmptySubjects++;
                 }
             }

             // Solo mostrar los trimestres que tengan materias
             if (nonEmptySubjects > 0) {
                 std::cout << "Trimestre " << quarter.quarterNumber << ":\n";

                 printTableHeader(subjectNameWidth, creditNumberWidth);

                 int totalCredits = 0;
                 for (const Subject& subject : quarter.subjects) {
                     if (!subject.name.empty() && (subject.mentionNumber == 0 || subject.mentionNumber == mentionNumber)) {
                         printTableRow(subject, subjectNameWidth, creditNumberWidth, showCredits, totalCredits);
                     }
                 }

                 printTotalCreditsRow(subjectNameWidth, creditNumberWidth, totalCredits, showCredits);

                 std::cout << "\n";
             }
         }
     }
 }
 // Esta función incluye selección de (s/n)


 // Función para unicamente mostrar la tabla del trimestre actual
 // para las tareas
 void showCurrentQuarterSubjects(const Quarter& quarter, int subjectNameWidth,
     int creditNumberWidth, bool showCredits, int mentionNumber) {

     int nonEmptySubjects = 0;
     for (const Subject& subject : quarter.subjects) {
         if (!subject.name.empty() && (subject.mentionNumber == 0 || subject.mentionNumber == mentionNumber)) {
             nonEmptySubjects++;
         }
     }

     // Solo mostrar el trimestre actual si tiene materias
     if (nonEmptySubjects > 0) {
         std::cout << "\nTrimestre " << quarter.quarterNumber << ":\n";

         printTableHeader(subjectNameWidth, creditNumberWidth);

         int totalCredits = 0;
         for (const Subject& subject : quarter.subjects) {
             if (!subject.name.empty() && (subject.mentionNumber == 0 || subject.mentionNumber == mentionNumber)) {
                 printTableRow(subject, subjectNameWidth, creditNumberWidth, showCredits, totalCredits);
             }
         }

         printTotalCreditsRow(subjectNameWidth, creditNumberWidth, totalCredits, showCredits);

         std::cout << "\n";
     }
 }


 // AÑADIR TAREAS Y CONVERTIR A PDF

 // Función para guardar el archivo del PDF
 // En un directorio personalizado
 void savePDF(HPDF_Doc pdf) {
     // Get the path to save the PDF file
     OPENFILENAMEA ofn;
     char szFileName[MAX_PATH] = "";
     ZeroMemory(&ofn, sizeof(ofn));
     ofn.lStructSize = sizeof(ofn);
     ofn.hwndOwner = NULL;
     ofn.lpstrFilter = "PDF Files (*.pdf)\0*.pdf\0All Files (*.*)\0*.*\0";
     ofn.lpstrFile = szFileName;
     ofn.nMaxFile = MAX_PATH;
     ofn.Flags = OFN_EXPLORER | OFN_OVERWRITEPROMPT;

     if (GetSaveFileNameA(&ofn)) {
         std::string filename = szFileName;

         // Create new filename based on the selected filename
         std::string newFilenameStr = filename;
         if (newFilenameStr.substr(newFilenameStr.size() - 4) != ".pdf") {
             newFilenameStr += ".pdf";
         }

         // Save the PDF file with new filename
         HPDF_SaveToFile(pdf, newFilenameStr.c_str());

         // Show notification of success
         MessageBoxA(NULL, "El archivo PDF ha sido guardado con éxito.", "Éxito", MB_OK | MB_ICONINFORMATION);
     }
     else {
         // Show notification of failure
         MessageBoxA(NULL, "No se ha seleccionado ninguna ubicación para guardar el archivo PDF.", "Error", MB_OK | MB_ICONERROR);
         HPDF_Free(pdf);
         return;
     }
 }

// Función para convertir a PDF
 void generatePDF(Quarter quarter, int userMentionNumber) {
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

         if (quarter.subjects[i].name != "" && quarter.subjects[i].mentionNumber == 0 || 
             quarter.subjects[i].mentionNumber == userMentionNumber) {

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
             HPDF_Page_ShowText(page, (std::string("Descripcion: ") + task.description).c_str());
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
                     std::cerr << "Error al establecer el tamaño de la pagina" << std::endl;
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
     savePDF(pdf);
     HPDF_Free(pdf);
 }

 // Función para imprimir las tareas añadidas
 void showTasks(Quarter quarter, int userMentionNumber) {
     showDefaultColorConsoleMessage();
     for (int i = 0; i < quarter.maxSubjects; i++) { // Recorre todas las materias en el trimestre
         if(quarter.subjects[i].name != "" 
             && quarter.subjects[i].mentionNumber == 0 || 
             quarter.subjects[i].mentionNumber == userMentionNumber) // Evita que se muestren materias vacias
             // Y materias que no pertenezcan a la mencion seleccionada

         std::cout << "Tareas para " << quarter.subjects[i].name << ":" << quarter.subjects[i].numTasks << std::endl;
         for (int j = 0; j < quarter.subjects[i].numTasks; j++) { // Recorre todas las tareas de la materia actual
             Task task = quarter.subjects[i].tasks[j];
             std::cout << "Tarea #" << j + 1 << std::endl;
             std::cout << "Nombre de la tarea: " << task.taskName << std::endl;
             std::cout << "Fecha de entrega: " << task.deliveryDate << std::endl;
             std::cout << "Descripcion: " << task.description << std::endl;
             std::cout << "Prioridad: " << task.priority << std::endl;
             std::cout << std::endl;
         }
     }
 }

 void addTasks(Quarter& quarter, int userMentionNumber) {

     showDefaultColorConsoleMessage();
     for (int i = 0; i < quarter.maxSubjects; i++) {
         if (quarter.subjects[i].mentionNumber == userMentionNumber || 
             quarter.subjects[i].mentionNumber == 0) {
             
             // Se verifica si la materia actual tiene la mención correspondiente o si se deben mostrar todas las materias
             int taskAmount;

             std::cout << "\nIngrese la cantidad de tareas para " << quarter.subjects[i].name << ": " << "(Maximo de 4)" << std::endl;
             while (!(std::cin >> taskAmount)) {
                 showRedConsoleMessage();
                 std::cout << "\n Por favor, ingrese un numero valido" << std::endl;

                 std::cin.clear();
                 while (std::cin.get() != '\n') {}
             }
             std::cin.ignore();

             if (taskAmount > 4) {
                 std::cout << "\nValor superior al establecido, estableciendo su límite de tareas 4..." << std::endl;
                 taskAmount = 4;
             }


             for (int j = 0; j < taskAmount; j++) {

                 Task task;
                 task.taskName = "";
                 task.currentDate = "";
                 task.deliveryDate = "";
                 task.description = "";
                 task.priority = 0;
                 std::cout << "\nTarea # " << j + 1;

                 std::cout << "\nIngrese el nombre de la tarea: ";
                 std::getline(std::cin, task.taskName);

                 std::cout << "\nFecha de creacion de la tarea " << getCurrentDate() << std::endl;

                 std::cout << "\nIngrese la fecha de entrega de la tarea (formato DD/MM/AAAA): ";
                 std::getline(std::cin, task.deliveryDate);

                 std::cout << "\nIngrese una descripcion para la tarea: ";
                 std::getline(std::cin, task.description);

                 bool validPriority = false;
                 while (!validPriority) {
                     showDefaultColorConsoleMessage();
                     std::cout << "\nIngrese la prioridad de la tarea (1 a 5): ";
                     std::string priorityStr;
                     std::getline(std::cin, priorityStr);

                     try {
                         int priority = std::stoi(priorityStr);
                         if (priority < 1 || priority > 5) {
                             showRedConsoleMessage();
                             std::cout << "\nLa prioridad debe ser un numero entre 1 y 5" << std::endl;
                         }
                         else {
                             task.priority = priority;
                             validPriority = true;
                         }
                     }
                     catch (std::invalid_argument&) {
                         showRedConsoleMessage();
                         std::cout << "\nLa prioridad debe ser un numero entre 1 y 5" << std::endl;
                     }
                 }

                 showDefaultColorConsoleMessage();
                 quarter.subjects[i].tasks[j] = task;
                 quarter.subjects[i].numTasks++;
             }
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
 
 // Función para verificar si la cédula ingresada es válida (7 - 8 carácteres)
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
     
 // FUNCIONES AUXILIARES
 
 // Función para limpiar la pantalla
 bool cleanScreen(bool cleanScreenParameter) {
     if (cleanScreenParameter) return system("cls");
 }

// Función para preguntar al usuario si desea limpiar la pantalla
bool askForCleaningScreen() {
    char answer;
    bool validAnswer = false;

    do {
        std::cout << "¿Desea limpiar la pantalla? (s/n): ";
        std::cin >> answer;

        if (std::cin.fail()) {
            // Si el usuario proporciona un valor no válido, se limpia el buffer de entrada y se repite la pregunta
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else {
            // Se convierte la respuesta a minúsculas para simplificar las comparaciones
            answer = std::tolower(answer);

            if (answer == 's') {
                validAnswer = true;
                cleanScreen(true);
            }
            else if (answer == 'n') {
                validAnswer = true;
            }
        }

    } while (!validAnswer);

    // Se devuelve true si el usuario eligió limpiar la pantalla, de lo contrario false
    return answer == 's';
}

// MENÚ FAQ
 void getFAQ() {
     std::cout << "-------------------------------------" << std::endl;
     std::cout << "1) De que trata nuestra aplicacion?" << std::endl;
     std::cout << "\nNuestra aplicacion dentro de la consola de C++ trata sobre un sistema de organizacion de tareas para la UBA. El cual esta basado en distintas aplicaciones como Notion y TickTick. A pesar de las limitaciones por la falta de una  GUI (Interfaz de usuario) hemos podido implementar funciones complejas como agregar 3 pensum enteros de nuestra universidad, agregar menciones, crear tareas, convertir estas a PDF e incluso incluir secciones como esta y la de Pomodoro.\n" << std::endl;
     std::cout << "-------------------------------------" << std::endl;
     std::cout << "\n2) Para quien esta pensada esta aplicacion?" << std::endl;
     std::cout << "\nNuestra aplicacion esta pensada para estudiantes de la UBA que busquen organizar dentro de las fechas de entrega para que posteriormente puedan hacer sus horarios y calendarios.\n" << std::endl;
     std::cout << "-------------------------------------" << std::endl;
     std::cout << "\n3) Que podemos hacer aqui?" << std::endl;
     std::cout << "\nNo solamente pensamos en estudiantes de nuestra universidad sino en personas que quieren entretenerse o usar otras herramientas de productividad como el pomodoro.\n" << std::endl;
     std::cout << "-------------------------------------" << std::endl;
     std::cout << "\n4) El orden de las tareas a agregar es lineal?" << std::endl;
     std::cout << "\nSi! Realizamos este enfoque para llevar un orden coherente de las actividades sumativas a agregar sin dejar ninguna materia atras. No querras olvidarte de alguna tarea, no?\n" << std::endl;
     std::cout << "-------------------------------------" << std::endl;
     std::cout << "\n4) Que tecnologias se usaron?" << std::endl;
     std::cout << "\nComo lenguaje de programacion, utilizamos 'C++' junto con la libreria de Libharu, la cual es una libreria de codigo abierto para generar archivos '.pdf'.\n" << std::endl;
     std::cout << "-------------------------------------" << std::endl;
 }

 // Función principal para obtener la mención
// Obtener la mención del usuario
 Mention getUserMention(int careerNumber) {
     std::cout << "Ingrese la mencion correspondiente a su carrera" << std::endl;

     std::vector<Mention> mentions;
     if (careerNumber == 1) {
         mentions = { {0, "Sin mencion"}, {1, "Programacion"}, {2, "Biomedicina"}, {3, "Inteligencia Artificial"} };
     }
     else if (careerNumber == 2) {
         mentions = { {0, "Sin mencion"}, {1, "Psicologia X1"}, {2, "Psicologia X2"}, {3, "Psicologia X3"} };
     }
     else if (careerNumber == 3) {
         mentions = { {0, "Sin mencion"}, {1, "Ingenieria Mecánica"}, {2, "Ingenieria Electronica"}, {3, "Ingenieria en Telecomunicaciones"} };
     }
     else {
         std::cout << "Carrera inválida!" << std::endl;
         return { -1, "" };
     }

     for (const Mention& mention : mentions) {
         std::cout << "Presione " << mention.number << " y enter para elegir la mencion de " << mention.name << std::endl;
     }

     int mentionInput;
     std::cin >> mentionInput;

     for (const Mention& mention : mentions) {
         if (mentionInput == mention.number) {
             std::cout << "Usted ha escogido " << mention.name << "!" << std::endl;
             return mention;
         }
     }

     std::cout << "Valor inválido!" << std::endl;
     return { -1, "" };
 }

 // Mostrar la información del usuario a la hora de añadir las tareas
 void showUserSelectedAndAddedOptions(int selectedCareerNumber, int selectedQuarterNumber,
     std::string userSelectedName, std::string userSelectedLastName,
     const std::vector<std::string>& careers, Mention userMention) {



     const std::string& career = careers[selectedCareerNumber - 1];
     std::cout << "Carrera: " << career << "\n\n";

     std::cout << "Resumen de sus datos:\n";
     std::cout << "Nombre completo: " << userSelectedName << " " << userSelectedLastName << "\n";
     std::cout << "Numero de trimestre seleccionado: " << selectedQuarterNumber << "\n";
     std::cout << "Carrera elegida: " << career << "\n";
     std::cout << "Mencion elegida: " << userMention.name << "\n";
     std::cout << "Numero de la mencion elegida " << userMention.number << "\n";
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
int userMentionNumber;

// VARIABLES RELACIONADAS CON LOS CREDITOS
bool showCareerPathCredits;

// VARIABLES RELACIONADAS CON EL REGISTRO PRINCIPAL
int userAge;
int userCedula;
std::string userName;
std::string userLastName;

// Ejecucíon del programa principal
int main()
{
    //getFAQ();

    // Pidiendo el nombre y el apellido del usuario 
    //userName = insertValidNameOrLastName("", "\nIngrese su nombre (solo carácteres alfabeticos): ",
        //"\nLo siento, su nombre solo debe contener letras. ¿Desea intentar de nuevo? (s/n): ",
        //"\nSu nombre se ha registrado exitosamente dentro del sistema!");

    //userLastName = insertValidNameOrLastName("", "\nAhora, ingrese su apellido (solo carácteres alfabeticos): ",
        //"\nLo siento su apellido solo debe contener letras. ¿Desea intentar de nuevo? (s/n): ",
        //"\nSu apellido se ha registrado exitosamente dentro del sistema!");
    // Se verifica que la cédula sea válida
    //isValidDocument(userCedula);


    // Se verifica que el rango de edad esté entre 12 y 99
    //isAgeValid(userAge);


    // Mostrar los datos resultantes del usuario

    //std::cout << "Su nombre completo es: " << userName << " " << userLastName << std::endl;
    //std::cout << "Su cedula de identidad es: " << userCedula << std::endl;
    //std::cout << "Su edad es: " << userAge << std::endl;

    bool keep_running = true;

    // Menú para el sistema
    while (keep_running) {
        std::cout << "Bienvenido! Que desea hacer?" << std::endl;
        std::cout << "Presione '1' y 'enter' para entrar al sistema de gestion de tareas de la universidad" << std::endl;
        std::cout << "Presione '2' y 'enter' para ver las preguntas frecuentes (FAQ)" << std::endl;
        std::cout << "Presione '3' y 'enter' para utilizar un pomodoro" << std::endl;
        std::cout << "Estresado por los estudios?, puedes jugar a adivinar un número contra el sistema presionando '4' y 'enter'" << std::endl;
        std::cin >> mainMenuUserChoice;

        // Switch case principal, correspondiente a las opciones
        // Del menú principal
        switch (mainMenuUserChoice) {

        case 3:
        {
            PomodoroTimer timer;
            timer.start();
            break;
        }
        
    

        // Si el usuario presiona 1, va a 
        // Las opciones para añadir tareas, ver Pensum
        // Mostrar las tareas al final y convertir
        // Sus tareas a PDF
        case 1:
        {
            getCareerCreditsAndTrimester(MAX_QUARTERS,
                userCareer, careerOptions, userQuarter);
            // Si la carrera ingresada por el usuario es válida
            // Se va a la opción para elegir si se desean ver los
            // Créditos o no
            if (isValidCareer(userCareer)) {
                showCareerPathCredits = getShowCurrentCredits();

                std::cout << "trimestre: " << userQuarter << std::endl;

                std::cout << "carrera: " << userCareer << std::endl;

                std::cout << "opcion de ver créditos: " << showCareerPathCredits;
            }

            // De lo contrario, se le solicita al usuario que nuevamente, ingrese
            // Una carrera válida
            else {
                std::cout << "La carrera ingresada no es válida. Por favor, ingrese una carrera válida.";
            }

            // Se establece la estructura correspondiente el trimestre seleccionado
            // Por el usuario. Por ende se realizaron tantas verificaciones anteriormente
            // Puesto que el ingreso de datos inválidos, ejecutaría de forma incorrecta
            // Nuestra estructura
            Quarter studentSelectedQuarter = subjectsAndOptionsPerCareer[userCareer - 1]
                .quarter[userQuarter - 1];

            Mention userMentionData = getUserMention(userCareer);

            userMentionNumber = userMentionData.number;

            std::cout << userMentionNumber;

            // Resumen los datos que ha ido colocando el usuario
            // Y pregunta de mención
            showUserSelectedAndAddedOptions(userCareer, userQuarter,
                userName, userLastName, careerOptions, userMentionData);

            // Se muestra la tabla de la carrera dependiendo del parámetro de showCareerPathCredits


            showCurrentCareerTable(userCareer, subjectsWidth, creditsWidth,
                subjectsAndOptionsPerCareer, userQuarter,
                showCareerPathCredits, userMentionNumber);


            // Se muestra la tabla de materias trimestre actual, esto para recordarle al
            // Usuario las materias que está tomando actualmente de acuerdo al 
            // trimestre que seleccionó

            // Se limpia la pantalla (se le preguntaría al usuario, si 
            // desea limpiarla ofc
            askForCleaningScreen();

            // Y se muestra unicamente el trimestre actual de la carrera
            showCurrentQuarterSubjects(studentSelectedQuarter, subjectsWidth, creditsWidth,
                showCareerPathCredits, userMentionNumber);

            std::cout << userMentionNumber;

            //Se ejecuta la función para añadir tareas
            addTasks(studentSelectedQuarter, userMentionNumber);

            // Parámetro de decisión en la opción de añadir
            // Este se ejecuta una vez el usuario haya terminado de añadir 
            // tareas
            int a;
            std::cout << "Usuario, que desea hacer?" << std::endl;
            std::cout << "presione 1 para crear un pdf con las tareas añadidas" << std::endl;
            std::cout << "presione 2 para ver las tareas añadidas" << std::endl;
            std::cout << "presione 3 para ver las tareas añadidas y generar un pdf" << std::endl;
            std::cin >> a;

            switch (a) {
            case 1:
                generatePDF(studentSelectedQuarter, userMentionNumber);
                std::cout << "PDF generado exitosamente!";
                break;

            case 2:
                showTasks(studentSelectedQuarter, userMentionNumber);
                int exitValue;
                std::cin >> exitValue;
                break;

            case 3:
                showTasks(studentSelectedQuarter, userMentionNumber);
                generatePDF(studentSelectedQuarter, userMentionNumber);
                int exitValue2;
                std::cout << "Puede presionar 1 para salir del programa, gracias por usar nuestro servicio";
                std::cin >> exitValue2;
                if (exitValue2 == 1) exit(0);
                break;

            default:
                std::cout << "Opción inválida. Por favor, seleccione una opción válida del menú." << std::endl;
                break;
            }
        }
        }
        return 0;
    }
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





