#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>
#include <thread>

class PomodoroTimer {
public:
    void start() {
        std::cout << "\nBienvenido al temporizador Pomodoro!" << std::endl;
        bool exit = false;
        while (!exit) {
            int minutes;
            std::cout << "\nPor favor ingrese la duración del temporizador en minutos (minimo 1, maximo 60), o ingrese 0 para salir: ";
            std::cin >> minutes;

            if (minutes == 0) {
                std::cout << "\nSaliendo del temporizador Pomodoro..." << std::endl;
                return;
            }
            else if (minutes < 1 || minutes > 60) {
                std::cout << "\nEl tiempo debe estar entre 1 y 60 minutos." << std::endl;
            }
            else {
                pomodoro(minutes, false);
                system("CLS");


                char choice;
                std::cout << "\n¿Desea descansar? (s/n): ";
                std::cin >> choice;
                if (choice == 's' || choice == 'S') {
                    std::cout << "\nDescansando por 1 minuto..." << std::endl;
                    pomodoro(1, true);
                }
                else {
                    std::cout << "\nComenzando nuevo pomodoro..." << std::endl;
                }

                std::cout << "\nPresione cualquier tecla para regresar al menú principal." << std::endl;
                std::cin.ignore();
                std::cin.get();
                system("CLS");
            }
        }
    }






private:
    void pomodoro(int minutes, bool is_break) {
        auto end_time = std::chrono::system_clock::now() + std::chrono::minutes(minutes);
        while (std::chrono::system_clock::now() < end_time) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            auto remaining_time = std::chrono::duration_cast<std::chrono::seconds>(end_time - std::chrono::system_clock::now()).count();
            int minutes = remaining_time / 60;
            int seconds = remaining_time % 60;
            std::cout << "\rTiempo restante" << (is_break ? " de descanso" : "") << ": " << std::setfill('0') << std::setw(2) << minutes << ":" << std::setfill('0') << std::setw(2) << seconds << std::flush;
        }
        std::cout << "\r¡Tiempo completado" << (is_break ? " de descanso" : "") << "!" << std::endl;
        system("CLS");
        std::cout << "\nPresione cualquier tecla para regresar al menú principal." << std::endl;
        std::cin.ignore();
        std::cin.get();
        system("CLS");
    }

};