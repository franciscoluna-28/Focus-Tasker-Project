#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>

class GuessNumberGame {
public:
    void playGame() {
        int num, guess, tries = 0;
        int maxNum = getMaxNum();
        srand(static_cast<unsigned int>(time(0))); // seed random number generator
        // Se ha usado static_cast<unsigned int> para evitar la posible perdida de datos


        num = rand() % maxNum + 1; // random number between 1 and maxNum
        std::cout << "Guess My Number Game (1 - " << maxNum << ")\n\n";

        do {
            std::cout << "Enter a guess between 1 and " << maxNum << " : ";
            std::cin >> guess;
            tries++;

            if (guess > num)
                std::cout << "Too high!\n\n";
            else if (guess < num)
                std::cout << "Too low!\n\n";
            else
                std::cout << "\nCorrect! You got it in " << tries << " guesses!\n";
        } while (guess != num);
    }

private:
    int getMaxNum() {
        int difficulty;
        std::cout << "Select difficulty level: \n";
        std::cout << "1. Easy (1-5)\n";
        std::cout << "2. Medium (1-10)\n";
        std::cout << "3. Hard (1-25)\n";
        std::cin >> difficulty;

        switch (difficulty) {
        case 1:
            return 5;
        case 2:
            return 10;
        case 3:
            return 25;
        default:
            return 10; // default to medium difficulty
        }
    }
};