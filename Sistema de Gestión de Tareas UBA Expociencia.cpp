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


#include <iostream> // Libreria inicial
#include <stdio.h> // Libreria 
#include <stdlib.h> // Libreria
#include <iomanip> // Libreria
#include <string> // Libreria
#include <vector> // Libreria
#include <Windows.h> // Libreria
#include "GuessNumberGame.h" // Modulo
#include "SubjectsAndOptionsPerCareer.h" // Modulo
#include <ctime> // Libreria
#include <sstream> // Libreria
#include <hpdf.h> // Libreria
#include <algorithm> // Libreria
#include <conio.h> // Libreria
#include "Structures.h" // Modulo
#include "Pomodoro.h" // Modulo
#undef max // Modificando uso de libreria para que funcione con windows

// Identificador para manejar la librería de Windows.h 
// Usado para cambiar los colores de la fuente de la consola
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

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

// Función para obtener unicamente la fecha actual
std::string getCurrentDate() {

    //Obtenemos la hora actual del sistema
    std::time_t now = std::time(nullptr);

    // Se crea una estructura tm para el tiempo actual
    std::tm tm_now;
    localtime_s(&tm_now, &now);
    std::ostringstream dateStream;

    // Añade el mes al flujo de salida de cadena 
    dateStream << tm_now.tm_mday << "/" <<
        tm_now.tm_mon + 1 << "/" <<

    // Se añade el año al flujo de salida de cadena (en formato de dos dígitos)
    tm_now.tm_year + 1900 - 2000;

    // Devuelve la fecha como una cadena de caracteres (string)
    return dateStream.str();
}

// VECTORES

// Vector con las respectivas carreras del edificio de ingeniería
std::vector<std::string> careerOptions = { "Ingenieria de Sistemas",
"Psicologia", "Ingenieria Electrica" };

// SELECCIÓN DE CARRERA Y OPCIONES DE CARRERA

// Función para obtener un trimestre válido
int getValidQuarter(int maxQuarters) {
    int currentQuarter = 0;
    char respuesta;
    std::string input;

    // Estructura repetitiva Do While para obtener un trimestre válido
    // Se finalizará su ejecución una vez el usuario haya obtenido un 
    // Número válido de trimestre
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

        // Asignando el valor del trimestre actual a currentQuarter
        // Ahora, se verificará si el número está dentro del límite establecido 
        // (1 - 12)
        currentQuarter = std::stoi(input);

        // Se le advierte al usuario que el valor que ha introducido 
        // Para el trimestre es inválido y se le pregunta si desea
        // Volver a introducir un valor válido
        if (currentQuarter <= 0 || currentQuarter > maxQuarters) {
            std::cout << "\nTrimestre invalido, debe ingresar un numero entre 1 y " << maxQuarters << "." << std::endl;

            std::cout << "\nDesea ingresar un nuevo trimestre? (s/n): ";
            std::cin >> respuesta;
            if (respuesta == 'n' || respuesta == 'N') exit(0);
        }
    } while (currentQuarter <= 0 || currentQuarter > maxQuarters);

    // Mensaje de "éxito" que confirma el trimestre del usuario y se devuelve
    // El trimestre actual
    showGreenConsoleMessage();
    std::cout << "\nTrimestre valido, usted actualmente se encuentra en el trimestre " << currentQuarter << std::endl;
    return currentQuarter;
}

// Función para obtener la selección de carrera del usuario
int getCareerSelection(std::vector<std::string> possibleCareerOptions) {
    int seleccion;
    std::cin >> seleccion;

    // Verifica que la última entrada del usuario sea un número 
    if (std::cin.fail()) { 

        // Si el último valor ingresado no es un número válido
        showRedConsoleMessage();
        std::cout << "\nEntrada Invalida. Por favor, intente de nuevo." << std::endl;

        // Borrar el estado de error de std::cin
        std::cin.clear(); 

        // Ignorar cualquier entrada adicional hasta una nueva línea
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

        // Llamada recursiva para obtener una selección válida
        return getCareerSelection(possibleCareerOptions); 
    }
    else if (seleccion >= 1 && seleccion <= possibleCareerOptions.size()) {

        // Se regresa el valor obtenido durante la selección
        return seleccion;
    }

     // De lo contrario, se le pide al usuario que ingrese un valor válido nuevamente
    else {
        showRedConsoleMessage();
        std::cout << "\nNumero Invalido. Por favor, intente de nuevo." << std::endl;

        // Llamada recursiva para obtener una selección válida
        showDefaultColorConsoleMessage();
        return getCareerSelection(possibleCareerOptions); 

        // Una llamada recursiva es una técnica de programación en la que
        // Una función se llama a si misma hasta que el usuario
        // Un valor válido
    }
}

// Función para imprimir las opciones de selección de carrera
void showCareerOptions(const std::vector<std::string>& possibleCareerOptions) {
    showDefaultColorConsoleMessage();
    std::cout << "\n------------------------------------------------------------" << std::endl;
    std::cout << "Por favor, indique la carrera que actualmente esta cursando" << std::endl;

    // Bucle encargado de mostrar las opciones de carrera dentro de 
    // nuestro vector secundario (solo nombres) de carrera
    for (int i = 0; i < possibleCareerOptions.size(); i++) {
        std::cout << "Escriba '" << i + 1 << "' para elegir " << possibleCareerOptions[i] << std::endl;
    }
  
}

// Obtener la selección del usuario y llamar sub - funciones
// El símbolo "&" se utiliza en los parámetros de una función para indicar que se está 
// pasando la dirección de memoria de una variable como argumento en lugar de su valor.Esto se conoce 
// como pasar el argumento por referencia.

// Pide como argumento el límite de trimestres (Quarters), el número de la carrera del
// Usuario, el vector de las opciones de carrera y el trimestre actual del usuario

bool getCareerCreditsAndTrimester(int maxQuarters, int& userCareer,
    const std::vector<std::string>& possibleCareerOptions, int& userQuarter) {
    showCareerOptions(possibleCareerOptions);

    // Ejecutamos la función de getCareerSelection y le damos el valor
    // De su resultado a la variable selección
    int selection = getCareerSelection(possibleCareerOptions);

    // Si la selección es inválida, cancela la ejecución de la función
    if (selection == -1) {
        return false;
    }

    // Y si es válida, mostramos un mensaje de "sucess" y asignamos
    // El número de la carrera del usuario a userCareer
    // Y el trimestre a userQuarter
    // Finalizando la ejecución regresando 'true'
    else {
        showGreenConsoleMessage();
        std::cout << "\nUsted ha escogido la carrera de " << possibleCareerOptions
            [static_cast<size_t>(selection) - 1] << std::endl;
        userCareer = selection;
        userQuarter = getValidQuarter(maxQuarters);
        return true;
    }
}
//De esta manera, se llamará a getCareerSelection dentro de 
// getCareerCreditsAndTrimester y se asignará el valor devuelto
// Función para ver los créditos (trigger)

// Función para verificar si el número de la carrera es válido
bool isValidCareer(int careerNumber) {

    // Se verifica que el número de la carrera del usuario es mayor
    // O igual que el tamaño del vector 'careerOptions'

    // Aquí utilizamos un operador ternario, muy similar a los condicionales 
    // La primera expresión, seguida de '?' será la que se ejecute en caso
    // De que la evaluación sea positiva y lo posterior a ':' será lo que
    // Se ejecutará si la condición no se satisface
    return (careerNumber >= 1 && careerNumber <= careerOptions.size()) ? true : false;
}

// TABLAS DE CARRERA

// Función para mostrar los créditos en las tablas de la carrera
bool getShowCurrentCredits() {
    char respuesta;

    // Estructura do while que realiza la pregunta para verificar
    // Si se desean mostrar los créditos del pensum

    // Si se escoge 1, se activa dicha opción, de lo contrario,
    // Se desactiva. Implementamos manejo de errores en caso de que se inserten valores inválidos
    do {
        showDefaultColorConsoleMessage();
        std::cout << "\nDesea ver los creditos disponibles en cada unidad materia correspondiente al pensum de la materia y mencion que eligio?" << std::endl;
        std::cout << "\nEscriba '1' y presione 'Enter' para activar esta opcion o '0' para desactivarla" << std::endl;
        std::cin >> respuesta;

        if (respuesta == '1') {
            return true;
        }
        else if (respuesta == '0') {
            return false;
        }
        showRedConsoleMessage();
        std::cout << "Entrada no valida. Por favor ingrese un numero valido (0 o 1)." << std::endl;
    } while (true);
    showDefaultColorConsoleMessage();
}

// Función para imprimir el encabezado de la tabla

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
// Pide como argumentos la estructura de la materia, el ancho para el nombre de la materia y los créditos,
// El boolean para mostrar los créditos y el total de créditos
// Función para imprimir una fila de la tabla con el nombre de la materia y los créditos correspondientes
void printTableRow(const Subject& subject, int subjectNameWidth,
    int creditNumberWidth, bool showCredits, int& totalCredits) {
    std::cout << std::left << std::setw(subjectNameWidth) << subject.name;

    // Aqui la funcion muestra unicamente los '|' al tener la opcion de mostrar créditos activada
    if (showCredits) {
        std::cout << "|" << std::right << std::setw(creditNumberWidth) << subject.credits << "|\n";
        totalCredits += subject.credits;
    }

    // De lo contrario no muestra nada
    else {
        std::cout << "\n";
    }
}

// Función para imprimir la fila de total de créditos
void printTotalCreditsRow(int subjectNameWidth, int creditNumberWidth, int totalCredits, bool showCredits) {

    // Si la opción para mostrar los crédtios está activada, se muestra la fila para
    // Mostrar los créditos
    if (showCredits) {
        showDefaultColorConsoleMessage();
        std::cout << std::left << std::setw(subjectNameWidth) << "Total de Creditos" << "|";
        std::cout << std::right << std::setw(creditNumberWidth) << totalCredits << "|\n";
    }

    // De lo contrario
    // Evita que se vea un "| 0| dentro de la fila de los créditos
    else {
        // Cancelando la ejecución de la función mediante un return
        return;
    }
}

// Función para mostrar la tabla de la carrera
// Usa los argumentos del número de la carrara, el largo del nombre de la materia
// el largo de los créditos, la carrera seleccionada, el trimestre seleccionado, 
// El boolean para mostrar los créditos y el número de la mención
 void showCurrentCareerTable(int careerNumber, int subjectNameWidth, int creditNumberWidth,
     const Career* careers, int selectedUserQuarter, bool showCredits, int mentionNumber) {

     showDefaultColorConsoleMessage();

     // Se obtiene el indice correspondiente de la carrera
     // Puesto que los arrays empiezan en 0 y nuestra selección va de 1 a 3
     const Career& career = careers[careerNumber - 1];
     std::cout << "Carrera: " << career.name << "\n\n";

     // Mostrar menú de selección
     std::string selection = "";
     bool showAllQuarters = false;

     // Estructura repetitiva para obligar al usuario a colocar
     // Un valor válido
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
             showRedConsoleMessage();
             std::cout << "Por favor, ingrese una opcion valida.\n";
         }
     }

     // Recorriendo el trimestre correspondiente mediante un
     // Bucle for each ':'el cúal se utiliza para recorrer cada
     // Arreglo dentro del contenedor


     // PARA LA EXPOCIENCIA
     // Ejemplo sencillo (própositos de enseñanza
     // Durante la expociencia
     //std::vector<int> nums = {1, 2, 3, 4, 5};
     // 
// Itera sobre cada elemento en el vector y lo imprime
     //for (const int& num : nums) {
         //std::cout << num << std::endl;
     //}

     // Bucle for each para recorrer cada elemento en el vector
     // Verificando la opción escogida mediante un if (ver todos los trimestre
     // O verificar que el número del trimestre sea igual al que asignó el usuario
     // Esto para recorrer los trimestres
     for (const Quarter& quarter : career.quarter) {
         if (showAllQuarters || quarter.quarterNumber == selectedUserQuarter) {

             // Variable para guardar las materias con contenido
             int nonEmptySubjects = 0;

             // Recorremos ahora las materias mediante otro bucle for each
             for (const Subject& subject : quarter.subjects) {

                 // Verificamos que el nombre de cada materia no esté vacio y que tengamos o el indice por defecto (0)
                 // Disponible en todas las menciones y las materias correspondientes a la mención seleccionada
                 // Por el usuario, posteriomente, se incrementa el contador de 'nonEmptySubjects'
                 if (!subject.name.empty() && (subject.mentionNumber == 0 || subject.mentionNumber == mentionNumber)) {
                     nonEmptySubjects++;
                 }
             }

             showDefaultColorConsoleMessage();
             // Solo mostrar los trimestres que tengan materias
             if (nonEmptySubjects > 0) {
                 std::cout << "Trimestre " << quarter.quarterNumber << ":\n";

                 printTableHeader(subjectNameWidth, creditNumberWidth);

                 int totalCredits = 0;

                 // Nuevamente, verificamos condiciones pero con las materias 
                 // De cada trimestre (quarter)
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

     // Se sigue la misma lógica que en la función de 
     // ShowCurrentCareerTable, con la diferencia de que esta
     // Función unicamente muestra la tabla del trimestre seleccionado
     // Para tenerlo como referencia a la hora de añadir las tareas
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

     // Obtener la ubicación para guardar el pdf
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

         // Craemos un nuevo archivo basado en el nombre del pdf
         std::string newFilenameStr = filename;
         if (newFilenameStr.substr(newFilenameStr.size() - 4) != ".pdf") {
             newFilenameStr += ".pdf";
         }

         // Guardamos el PDF
         HPDF_SaveToFile(pdf, newFilenameStr.c_str());

         // Notificaciones de sucess
         MessageBoxA(NULL, "El archivo PDF ha sido guardado con exito.", "Exito", MB_OK | MB_ICONINFORMATION);
     }
     else {
         // Notificaciones de error
         MessageBoxA(NULL, "No se ha seleccionado ninguna ubicacion para guardar el archivo PDF.", "Error", MB_OK | MB_ICONERROR);
         HPDF_Free(pdf);
         return;
     }
 }

// Función para convertir a PDF
 // Toma como argumentos el trimestre actual y el número de la mención del usuario
 void generatePDF(Quarter quarter, int userMentionNumber) {

     // Setup inicial de la libreria de HPDF

     // Configuración del PDF Inicial
     HPDF_Doc pdf = HPDF_New(NULL, NULL);

     // Estado del PDF
     HPDF_STATUS status;

     // Se añade una página nueva
     HPDF_Page page = HPDF_AddPage(pdf);

     // Y configuramos el estado de nuestra plantilla
     status = HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);

     // Si el estado del PDF, por algún motivo en específico, no es correcto
     // Se imprime un mensaje de error
     if (status != HPDF_OK) {
         std::cerr << "Error al establecer el tamaño de la página" << std::endl;
         HPDF_Free(pdf);
         return;
     }

     // Estableciendo las propiedades de fuente y de tamaño
     // De nuestro PDF
     HPDF_Font font = HPDF_GetFont(pdf, "Helvetica", NULL);
     HPDF_Page_SetFontAndSize(page, font, 12);
     HPDF_Page_BeginText(page);
     HPDF_Page_MoveTextPos(page, 50, 750);
     HPDF_Page_ShowText(page, "Lista de tareas");
     HPDF_Page_MoveTextPos(page, 0, -20);

     // Creamos una variable para ir tomando en cuenta el número de
     // Lineas. Esto, para ir creando páginas adicionales a medida
     // Que la lista de las tareas se vaya volviendo más extensa
     int numLines = 0;

     // Recorriendo las carreras del trimestre
     for (int i = 0; i < quarter.maxSubjects; i++) {

         // Condiciones para evitar nombres vacíos, materias innecesarias y que solamente
         // Se muestre la información que solicite el usuario
         if (quarter.subjects[i].name != "" && quarter.subjects[i].mentionNumber == 0 ||
             quarter.subjects[i].mentionNumber == userMentionNumber && quarter.subjects[i].wantsToSkip == false) {

              // Nuevamente, filtrado mcontenido mediante otro 'if' para 
              // evitar imprimir "tareas para" en materias que no
             // Tengan tareas en 'Tareas para'
             if (quarter.subjects[i].wantsToSkip != true && quarter.subjects[i].tasks[i].taskName != "") {
                 HPDF_Page_ShowText(page, (std::string("Tareas para ") + quarter.subjects[i].name).c_str());
                 HPDF_Page_MoveTextPos(page, 0, -20);
             }

             // Ahora si, tras hacer el filtrado necesario podemos empezar a mostrar
             // Cada una de las tareas creadas por el usuario, mediante una estructura
             // Repetitiva for
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

                 //Se aumenta el número de lineas en cada materia 
                 numLines += 7;

                 // Ahora, si el número de lineas es igual
                 // O mayor a 35, creamos otra página
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

                     // Terminamos de establecer nuestras condiciones
                     // Para crear el PDF en la página/s siguiente/s
                     HPDF_Page_SetFontAndSize(page, font, 12);
                     HPDF_Page_BeginText(page);
                     HPDF_Page_MoveTextPos(page, 50, 750);
                     numLines = 0;
                 }
             }
         }
     }
 
     // Terminando de configurar nuestro
     // Archivo .PDF
     HPDF_Page_EndText(page);
     savePDF(pdf);
     HPDF_Free(pdf);
 }

 // Función para imprimir las tareas añadidas
 void showTasks(Quarter quarter, int userMentionNumber) {
     showDefaultColorConsoleMessage();

     // Recorre todas las materias en el trimestre
     for (int i = 0; i < quarter.maxSubjects; i++) { 

         // Nuevamente, obviando materias vacías y que no hayan sido 
         // Seleccionadas por el usuario
         if(quarter.subjects[i].name != "" 
             && quarter.subjects[i].mentionNumber == 0 || 
             quarter.subjects[i].mentionNumber == userMentionNumber || quarter.subjects[i].wantsToSkip == true) // Evita que se muestren materias vacias
             // Y materias que no pertenezcan a la mencion seleccionada

 
        // Y finalmente se imprime cada una de las tareas
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

 // Función para agregar tareas
 void addTasks(Quarter& quarter, int userMentionNumber) {

     showDefaultColorConsoleMessage();

     // Recorriendo las materias de cada trimestre y estableciendo condiciones para
     // Evitar mostrar datos incorrectos
     for (int i = 0; i < quarter.maxSubjects; i++) {
         if (quarter.subjects[i].mentionNumber == userMentionNumber || quarter.subjects[i].mentionNumber == 0) {

             std::cout << "\nDesea agregar tareas para " << quarter.subjects[i].name << "? (s/n)" << std::endl;
             char choice;
             while (!(std::cin >> choice) || (choice != 's' && choice != 'n')) {
                 showRedConsoleMessage();
                 std::cout << "\nPor favor, ingrese 's' o 'n'" << std::endl;
                 std::cin.clear();
                 std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
             }
             std::cin.ignore();

             // Opción para saltarse una materia
             if (choice == 'n') {
                 quarter.subjects[i].wantsToSkip = true;
                 continue; // Saltar a la siguiente materia
             }
             else {
                 quarter.subjects[i].wantsToSkip = false;
             }
         }


         // Variable para tener en cuenta el número de 
         // Tareas a añadir
         int taskAmount;

         // Recorremos las materias que el usuario haya señalado que no quiere 
         // Saltarse, siendo aquí la propiedad de de 'wantsToSkip' falsea y mostrando
         // Solamente las materias correspondientes al número de la mención
         if (quarter.subjects[i].wantsToSkip == false && quarter.subjects[i].mentionNumber == userMentionNumber || quarter.subjects[i].mentionNumber == 0) {
             std::cout << "\nIngrese la cantidad de tareas (sumativas) para " << quarter.subjects[i].name << ": " << "(Maximo de 4)" << std::endl;
             std::cout << "Verifique sus datos antes de confirmar" << std::endl;

             // Manejando errores en caso de colocar carácteres
             while (!(std::cin >> taskAmount)) {
                 showRedConsoleMessage();
                 std::cout << "\n Por favor, ingrese un numero valido" << std::endl;

                 std::cin.clear();
                 while (std::cin.get() != '\n') {}
             }
             std::cin.ignore();


             if (taskAmount > 4) {
                 std::cout << "\nValor superior al establecido, estableciendo su limite de tareas a 4..." << std::endl;
                 taskAmount = 4;
             }

             // Se le piden al usuario los datos necesarios para
             // Cada una de las tareas dentro de las materias
             for (int j = 0; j < taskAmount; j++) {
                 Task task;
                 task.taskName = "";
                 task.currentDate = "";
                 task.deliveryDate = "";
                 task.description = "";
                 task.priority = 0;
                 std::cout << "\nTarea # " << j + 1;

                 // Preguntas al usuario

                 std::cout << "\nIngrese el nombre la de estrategia para la sumativa: ";
                 std::getline(std::cin, task.taskName);

                 std::cout << "\nFecha de creacion de la tarea " << getCurrentDate() << std::endl;

                 std::cout << "\nIngrese la fecha de entrega de la tarea (formato DD - MM - AAAA) o (DD - MM): ";
                 std::getline(std::cin, task.deliveryDate);

                 std::cout << "\nIngrese una descripcion para la sumativa: ";
                 std::getline(std::cin, task.description);

                 // Manejando errores en la prioridad
                 bool validPriority = false;
                 while (!validPriority) {
                     showDefaultColorConsoleMessage();
                     std::cout << "\nIngrese la prioridad de la actividad sumativa (1 a 5): ";
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

                 // Si la tarea, se añade satisfactoriamente,
                 // Entonces se añaden al arreglo de tareas
                 // Y se suma el número de tareas
                 showDefaultColorConsoleMessage();
                 quarter.subjects[i].tasks[j] = task;
                 quarter.subjects[i].numTasks++;



             }
         }
     }
 }
 

 // REGISTRAR USUARIO

 // Función para validar strings únicamente con letras
 bool isValidString(const std::string& string)
 {
     for (char c : string) {

        // Se verifica si cada uno de los carácteres
         // Del string dado son alfabéticos con 'std::isalpha'
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

     // Mientras que el string no sea válido
     // Se mostrará un mensaje de error y se le pedirá al
     // Usuario que ingrese el valor nuevamente
     while (!isStringValid) {
         showDefaultColorConsoleMessage();
         std::cout << insertMessage << std::endl;
         std::cin >> stringToValidate;

         // De lo contrario, la función regresa true
         showGreenConsoleMessage();
         if (isValidString(stringToValidate)) {
             isStringValid = true;
             std::cout << sucessMessage;
         }
         else {
             // Se le pregunta al usuario si desea continuar
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

     // Y se regresa el string
     return stringToValidate;
 }
 
 // Función para verificar si la cédula ingresada es válida (7 - 8 carácteres)

 // Verificación con while para repetir la pregunta hasta que el usuario
 // Coloque un valor válido
 bool isValidDocument(int& number) {
     while (true) {
         std::string numberString;
         showDefaultColorConsoleMessage();
         std::cout << "\nIngrese el numero de cedula: (7 - 8 caracteres) " << std::endl;
         std::cin >> numberString;

         // Si se añade un número, se convierte a string
         try {
             number = std::stoi(numberString);
         }

         // De lo contrario, se le pide al usuario que inserte un valor válido
         // Puesto que ha ingresado un carácter que no es numérico
         catch (const std::invalid_argument&) {
             showRedConsoleMessage();
             std::cout << "\nEl valor ingresado no es un numero valido. Por favor, intentelo de nuevo." << std::endl;
             continue;
         }

         // Si se satisfacen las condiciones anteriores,
         // El string se convierte a un número
         std::string validNumberString = std::to_string(number);

         // Ahora, verificamos el tamaño del string numérico 
         if (validNumberString.size() >= 7 && validNumberString.size() <= 8) {
             return true;
         }

         // Finalmente, si no se cumple con la condición dada, por que el número es o muy pequeño
         // O muy grande, se le pide al usuario que intente de nuevo la selección
         else {
             showRedConsoleMessage();
             std::cout << "\nEl numero debe tener entre 7 y 8 digitos. Por favor, intentelo de nuevo." << std::endl;
             continue;
         }
     }
     showDefaultColorConsoleMessage();
 }

 // Función para verificar la edad del usuario (10 - 99)
 bool isAgeValid(int& age) {
     while (true) {

     // Usamos la misma lógica de la función
     // 'isValidDocument'
     std::string numberString;
     std::cout << "\nIngrese su edad: (10 - 99)" << std::endl;
     std::cin >> numberString;

     try {
         age = std::stoi(numberString);
     }
     catch (const std::invalid_argument&) {
         std::cout << "El valor ingresado no es un numero valido. Por favor, intentelo de nuevo." << std::endl;
         continue;
     }

     std::string validNumberString = std::to_string(age);

     if (validNumberString.size() == 2) {
         return true;
     }
     else {
         std::cout << "El número debe ser entre 10 y 99. Por favor, intentelo de nuevo." << std::endl;
         continue;
     }
     }
 }
     
 // FUNCIONES AUXILIARES
 
 // Función para limpiar la pantalla
 bool cleanScreen(bool cleanScreenParameter) {

     // system("cls") es un comando que nos permite
     // Limpiar la consola dentro de C++ mediante 
     // Proveniente del encabezado de <stdlib.h>
     if (cleanScreenParameter) return system("cls");
 }

// Función para preguntar al usuario si desea limpiar la pantalla
bool askForCleaningScreen() {
    char answer;
    bool validAnswer = false;

    // Estructura repetitiva Do - While para 
    // Limpiar la pantalla
    do {
        std::cout << "Desea limpiar la pantalla? (s/n): ";
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

    // Mientras que el usuario inserte un valor que 
    // No sea válido
    } while (!validAnswer);

    // Se devuelve true si el usuario eligió limpiar la pantalla, de lo contrario false
    return answer == 's';
}

// MENÚ FAQ

// Muestra de texto
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
 Mention getUserMention(int careerNumber) {

     std::cout << "\n--------------------------------------------------------------" << std::endl;
     std::cout << "Ingrese el numero correspondiente a la mencion de su carrera:" << std::endl;
     std::cout << "Recuerde, que estas afectaran a su pensum desde el 8vo trimestre." << std::endl;

     // Se crea un vector de menciones, y dependiendo del número elegido
     // Se asignarán datos diferentes
     // Es por ende que se realizaron una serie extendida de verificaciones a la hora
     // De obtener la carrera seleccionada por el usuario
     std::vector<Mention> mentions;
     if (careerNumber == 1) {
         mentions = { {0, "General"}, {1, "Programacion"}, {2, "Inteligencia Artificial"}, {3, "Biomedica"} };
     }
     else if (careerNumber == 2) {
         mentions = { {0, "General"}, {1, "Educativa"}, {2, "Clinica"}, {3, "Organizacional"} };
     }
     else if (careerNumber == 3) {
         mentions = { {0, "General"}, {1, "Telecomunicaciones"}, {2, "Metrologia"}, {3, "Biomedica"} };
     }
     else {
         std::cout << "Carrera invalida!" << std::endl;
         return { -1, "" };
     }

     for (const Mention& mention : mentions) {
         std::cout << "Presione " << "'" << mention.number << "'" << " y 'enter' para elegir la mencion de " << mention.name << std::endl;
     }

     int mentionInput;
     std::cin >> mentionInput;

     while (std::cin.fail() || mentionInput < 0 || mentionInput >= mentions.size()) {
         std::cin.clear();
         std::cin.ignore(256, '\n');
         showRedConsoleMessage();
         std::cout << "Entrada inválida. Por favor, ingrese un numero valido correspondiente a una de las menciones mostradas." << std::endl;
         std::cin >> mentionInput;
     }
     showDefaultColorConsoleMessage();
     std::cout << "\nUsted ha escogido la mencion de " << mentions[mentionInput].name << "!" << std::endl;
     return mentions[mentionInput];
 }

 // Mostrar la información del usuario a la hora de añadir las tareas
 void showUserSelectedAndAddedOptions(int selectedCareerNumber, int selectedQuarterNumber,
     std::string userSelectedName, std::string userSelectedLastName,
     const std::vector<std::string>& careers, Mention userMention) {



     const std::string& career = careers[selectedCareerNumber - 1];

     showDefaultColorConsoleMessage();
     std::cout << "Resumen de sus datos:\n";
     std::cout << "Nombre completo: " << userSelectedName << " " << userSelectedLastName << "\n";
     std::cout << "Numero de trimestre seleccionado: " << selectedQuarterNumber << "\n";
     std::cout << "Carrera elegida: " << career << "\n";
     std::cout << "Mencion elegida: " << userMention.name << "\n";
     std::cout << "Numero de la mencion elegida: " << userMention.number << "\n";
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

    std::cout << "----------------------------------------------------" << std::endl;
    std::cout << "Universidad Bicentenaria de Aragua" << std::endl;
    std::cout << "Focus Tasker" << std::endl;
    std::cout << "Copyright 2023" << std::endl;
    std::cout << "----------------------------------------------------" << std::endl;
    std::cout << "Procediendo a ir al registro del usuario..." << std::endl;


    //getFAQ();

    // Pidiendo el nombre y el apellido del usuario 
    userName = insertValidNameOrLastName("", "\nIngrese su nombre (solo caracteres alfabeticos): ",
        "\nLo siento, su nombre solo debe contener letras. Desea intentar de nuevo? (s/n): \n",
        "\nSu nombre se ha registrado exitosamente dentro del sistema!\n");

    userLastName = insertValidNameOrLastName("", "\nAhora, ingrese su apellido (solo caracteres alfabeticos): ",
        "\nLo siento su apellido solo debe contener letras. Desea intentar de nuevo? (s/n): \n",
        "\nSu apellido se ha registrado exitosamente dentro del sistema!\n");
    // Se verifica que la cédula sea válida
    isValidDocument(userCedula);


    // Se verifica que el rango de edad esté entre 12 y 99
    isAgeValid(userAge);


    // Mostrar los datos resultantes del usuario
    showDefaultColorConsoleMessage();
    std::cout << "\n----------------------------------------------------" << std::endl;
    std::cout << "Su nombre completo es: " << userName << " " << userLastName << std::endl;
    std::cout << "Su cedula de identidad es: " << userCedula << std::endl;
    std::cout << "Su edad es: " << userAge << std::endl;
    std::cout << "----------------------------------------------------\n" << std::endl;

    bool keep_running = true;

    askForCleaningScreen();

    // Menú para el sistema
    while (keep_running) {
        keep_running = false;
        showDefaultColorConsoleMessage();
        std::cout << "\n----------------------------------------------------" << std::endl;
        std::cout << "Bienvenido (a)!" << "\n" << userName << " " << userLastName << ", " << "Que desea hacer?" << std::endl;
        std::cout << "\nPresione '1' y 'enter' para entrar al sistema de gestion de tareas de la universidad" << std::endl;
        std::cout << "Presione '2' y 'enter' para ver las preguntas frecuentes (FAQ)" << std::endl;
        std::cout << "Presione '3' y 'enter' para utilizar un pomodoro" << std::endl;
        std::cout << "Estresado por los estudios?, Puedes jugar a adivinar un numero contra el sistema presionando '4' y 'enter'" << std::endl;
        std::cin >> mainMenuUserChoice;
        std::cout << "----------------------------------------------------\n" << std::endl;

        // Switch case principal, correspondiente a las opciones
        // Del menú principal
        switch (mainMenuUserChoice) {
        case 2:
            {
                getFAQ();
                int uwu;
                std::cout << "Presione cualquier tecla y 'enter' para salir" << std::endl;
                std::cin >> uwu;
                keep_running = true;
                break;
            }


        // Ejecutando el pomodoro 
        case 3:
        {
            PomodoroTimer timer;
            timer.start();
            int uwu;
            std::cout << "Presione cualquier tecla y 'enter' para salir" << std::endl;
            std::cin >> uwu;
            break;
        }

        // Ejecutando el juego para adivinar un número
        case 4:
        {
            GuessNumberGame game;
            game.playGame();
            int uwu;
            std::cout << "Presione cualquier tecla y 'enter' para salir" << std::endl;
            std::cin >> uwu;
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


            }

            // De lo contrario, se le solicita al usuario que nuevamente, ingrese
            // Una carrera válida
            else {
                showRedConsoleMessage();
                std::cout << "\nLa carrera ingresada no es válida. Por favor, ingrese una carrera válida.";
            }

            // Se establece la estructura correspondiente el trimestre seleccionado
            // Por el usuario. Por ende se realizaron tantas verificaciones anteriormente
            // Puesto que el ingreso de datos inválidos, ejecutaría de forma incorrecta
            // Nuestra estructura

            showDefaultColorConsoleMessage();

            Quarter studentSelectedQuarter = subjectsAndOptionsPerCareer[userCareer - 1]
                .quarter[userQuarter - 1];

            Mention userMentionData = getUserMention(userCareer);

            userMentionNumber = userMentionData.number;


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

            // Se le pregunta al usuario si desea limpiar la pantalla
            askForCleaningScreen();

            // Y se muestra unicamente el trimestre actual de la carrera
            showCurrentQuarterSubjects(studentSelectedQuarter, subjectsWidth, creditsWidth,
                showCareerPathCredits, userMentionNumber);

            //Se ejecuta la función para añadir tareas
            addTasks(studentSelectedQuarter, userMentionNumber);

            // Parámetro de decisión en la opción de añadir
            // Este se ejecuta una vez el usuario haya terminado de añadir 
            // tareas
            int a;
            std::cout << "\nUsuario, que desea hacer?" << std::endl;
            std::cout << "Presione 1 para crear un pdf con las tareas añadidas" << std::endl;
            std::cout << "Presione 2 para ver las tareas añadidas" << std::endl;
            std::cout << "Presione 3 para ver las tareas añadidas y generar un pdf" << std::endl;
            std::cin >> a;

            switch (a) {
            case 1:
                generatePDF(studentSelectedQuarter, userMentionNumber);
                std::cout << "\nPDF generado exitosamente!";
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
                std::cout << "\nPuede presionar 1 para salir del programa, gracias por usar nuestro servicio" << std::endl;
                std::cin >> exitValue2;
                if (exitValue2 == 1) exit(0);
                break;

            default:
                std::cout << "\nOpción invalida. Por favor, seleccione una opcion valida del menu." << std::endl;
                break;
            }
        }
        }
        return 0;
    }
    }
#undef max



    


   







   

    

 