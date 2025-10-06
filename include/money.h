#pragma once
#include <string>
#include <iostream>

class Money 
{
public:
    Money();
    Money(const size_t& number, unsigned char t=0);
    Money(const std::initializer_list< unsigned char > &t);
    Money(const std::string &t);

    Money(const Money& other);
    Money(Money&& other) noexcept;
    virtual ~Money() noexcept;

    Money add(const Money& other);
    Money sub(const Money& other);
    bool equals(const Money& other);
    bool less(const Money& other);
    bool more(const Money& other);

    std::ostream& print(std::ostream& output);

private:
    size_t moneyArraySize;
    unsigned char* MoneyArray;

    void sizeArray(size_t number, size_t& old_size);
    void arraySum(size_t& result) const;
    void createArray(size_t number);
};