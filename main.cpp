#include <iostream>
#include "include/money.h"


// Вариант 14: Замена каждого n-го символа old_value на new_value
int main() {
    


    // Конструктор из списка
    Money firstMoneyArray{5,5,5,5,5};
    firstMoneyArray.print(std::cout) << std::endl;

    // Конструктор из короткого списка
    Money secondMoneyArray{5,5,5};
    secondMoneyArray.print(std::cout) << std::endl;

    // Сложение массивов
    Money thirdMoneyArray(firstMoneyArray.add(secondMoneyArray));
    thirdMoneyArray.print(std::cout) << std::endl;

    // Вычитание массивов
    Money fourthMoneyArray(firstMoneyArray.sub(secondMoneyArray));
    fourthMoneyArray.print(std::cout) << std::endl;

    // Перемещающий конструктор
    Money fifthMoneyArray(std::move(fourthMoneyArray));
    fifthMoneyArray.print(std::cout) << std::endl;


    try {
        // Попытка вызвать исключение при вычитании
        Money sixthMoneyArray(secondMoneyArray.sub(firstMoneyArray));
        sixthMoneyArray.print(std::cout) << std::endl;
    } catch (std::exception& e) {
        std::cerr << "Ошибка:" << e.what() << std::endl;
    }

    return 0;
}