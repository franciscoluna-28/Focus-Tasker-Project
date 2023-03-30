#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>

class GuessNumberGame {
public:
    void playGame() {
        int num, guess, tries = 0;
        int maxNum = getMaxNum();

        // Generador de semilla aleatorio
        // Se ha usado static_cast<unsigned int> para evitar la posible perdida de datos
        srand(static_cast<unsigned int>(time(0))); 



        // random number between 1 and maxNum
        num = rand() % maxNum + 1; 
        std::cout << "Adivina mi número aleatorio (1 - " << maxNum << ")\n\n";

        do {
            std::cout << "Introduzca un numero entre 1 y " << maxNum << ": ";
            std::cin >> guess;
            tries++;

            if (guess > num)
                std::cout << "Valor muy alto!\n\n";
            else if (guess < num)
                std::cout << "Valor muy bajo!\n\n";
            else
                std::cout << "\nCorrecto! Lo adivinaste en " << tries << " intentos!\n";
        } while (guess != num);
    }

private:
    int getMaxNum() {
        int difficulty;
        std::cout << "Elija el nivel de dificultad \n";
        std::cout << "1. Facil (1-5)\n";
        std::cout << "2. Medio (1-10)\n";
        std::cout << "3. Dificil (1-25)\n";
        std::cin >> difficulty;

        switch (difficulty) {
        case 1:
            return 5;
        case 2:
            return 10;
        case 3:
            return 25;
        default:

            // Por defecto en dificultad media
            return 10; 

        }
    }
};