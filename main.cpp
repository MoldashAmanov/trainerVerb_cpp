#include <iostream>
#include <fstream>
#include <limits>
#include "Trainer.h"

int main()
{
    Trainer trainer;
    int choice;

    do 
    {
        std::cout << "\n==================================\n";
        std::cout << "  ТРЕНАЖЕР НЕПРАВИЛЬНЫХ ГЛАГОЛОВ\n";
        std::cout << "==================================\n";
        std::cout << "1. Тест (10 вопросов)\n";
        std::cout << "2. Тест (20 вопросов)\n";
        std::cout << "3. Тест (50 вопросов)\n";
        std::cout << "4. История результатов\n";
        std::cout << "0. Выход\n";
        std::cout << "Ваш выбор: ";
        
        if (!(std::cin >> choice)) 
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка! Введите число.\n";
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) 
        {
            case 1: trainer.startQuiz(10); break;
            case 2: trainer.startQuiz(20); break;
            case 3: trainer.startQuiz(50); break;
            case 4: {
                std::ifstream file("stats.txt");
                if (file) {
                    std::string line;
                    std::cout << "\n--- История ---\n";
                    while (std::getline(file, line)) std::cout << line << '\n';
                } else {
                    std::cout << "История пуста. Пройдите тест!\n";
                }
                break;
            }
            case 0: std::cout << "Удачи в изучении английского!\n"; break;
            default: std::cout << "Неизвестная команда.\n";
        }
    } while (choice != 0);

    return 0;
}