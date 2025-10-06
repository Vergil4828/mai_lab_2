#include "../include/money.h"
#include <initializer_list>
#include <iomanip>

void Money::sizeArray(size_t number, size_t& old_size){
    if (number==0){
        old_size=1;
        return;
    }
    old_size=0;
    size_t temp=number;
    while (temp>0){
        temp/=10;
        old_size++;
    }
}

void Money::arraySum(size_t& sum) const{
    size_t mnoj=1;
    sum=0;
    for (size_t i=0; i< moneyArraySize;i++){
        sum+=MoneyArray[i]*mnoj;
        mnoj*=10;
    }
}

void Money::createArray(size_t number){
    if (MoneyArray!=nullptr){
        delete[] MoneyArray;
        MoneyArray=nullptr;
        moneyArraySize=0;
    }



    if (number==0){
        moneyArraySize=1;
        MoneyArray=new unsigned char[1]();
        return;
    }

    size_t newSize=0;
    sizeArray(number,newSize);
    moneyArraySize=newSize;
    MoneyArray= new unsigned char[moneyArraySize]();

    size_t digits_number=number;
    for (size_t i=0;i<moneyArraySize;i++){
        MoneyArray[i]=digits_number % 10;
        digits_number/=10;
    }



    
}

Money::Money() : MoneyArray(nullptr), moneyArraySize(0){
        std::cout<< "Конструктор по умолчанию" << std::endl;
        createArray(0);
    }

Money::Money(const size_t& number, unsigned char t) : MoneyArray(nullptr), moneyArraySize(0){
    std::cout << "Конструктор с числом" << std::endl;
    createArray(number);
}

Money::Money(const std::initializer_list<unsigned char>& listNumbers): MoneyArray(nullptr), moneyArraySize(0){
    std::cout << "Конструктор со списком" << std::endl;
    moneyArraySize=listNumbers.size();
    MoneyArray=new unsigned char[moneyArraySize];

    size_t index_to_digit=0;
    for (auto& number:listNumbers){
        if (number>9){
            throw std::invalid_argument("Значение в списке не явлсяется числом");

        }
        MoneyArray[index_to_digit++]=number;
    }

}

Money::Money(const std::string& string_number): MoneyArray(nullptr), moneyArraySize(0){
    std::cout << "Конструктор с помощью строки" << std::endl;
    try {
        size_t number=std::stoul(string_number);
        createArray(number);
    }
    catch (std::exception& e){
        throw std::invalid_argument("Неудачное преобразование строки в число");

    }
}


Money::Money(const Money& other): MoneyArray(nullptr), moneyArraySize(0){
    std::cout << "Конструктор для копирования" << std::endl;
    moneyArraySize=other.moneyArraySize;
    MoneyArray=new unsigned char[moneyArraySize]();
    
    std::copy(other.MoneyArray, other.MoneyArray+moneyArraySize, MoneyArray);
}

Money::Money(Money&& other) noexcept: MoneyArray(nullptr), moneyArraySize(0){
    std::cout << "Конструктор для перемещения" << std::endl;
    moneyArraySize=other.moneyArraySize;
    MoneyArray=other.MoneyArray;
    other.MoneyArray=nullptr;
    other.moneyArraySize=0;
}

Money::~Money() noexcept {
    std::cout << "Деструктор" << std::endl;
    if (MoneyArray!=nullptr){
        delete[] MoneyArray;
        MoneyArray=nullptr;
    }
    moneyArraySize=0;
}

Money Money::add(const Money& other){
    size_t now_money_class, other_money_class;
    this->arraySum(now_money_class);
    other.arraySum(other_money_class);
    return Money(now_money_class+other_money_class,0);


}

Money Money::sub(const Money& other){
    size_t now_money_class, other_money_class;
    this->arraySum(now_money_class);
    other.arraySum(other_money_class);
    if (now_money_class<other_money_class){
        throw std::logic_error("Нельзя иметь отрицательный баланс");
    }
    return Money(now_money_class-other_money_class,0);

}

bool Money::equals(const Money& other){
    size_t now_money_class, other_money_class;
    this ->arraySum(now_money_class);
    other.arraySum(other_money_class);
    return now_money_class==other_money_class;
}

bool Money::less(const Money& other){
    size_t now_money_class, other_money_class;
    this ->arraySum(now_money_class);
    other.arraySum(other_money_class);
    return now_money_class<other_money_class;
}

bool Money::more(const Money& other){
    size_t now_money_class, other_money_class;
    this ->arraySum(now_money_class);
    other.arraySum(other_money_class);
    return now_money_class>other_money_class;
}

std::ostream& Money::print(std::ostream& output){
    size_t arrayMoney;
    arraySum(arrayMoney);
    size_t rub= arrayMoney/100;
    size_t kop=arrayMoney%100;
    output << rub << " руб. " <<std::setw(2)<< std::setfill('0')<< kop << " коп.";
    return output;
}