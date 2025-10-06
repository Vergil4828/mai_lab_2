#include <gtest/gtest.h>
#include "../include/money.h"

TEST(MoneyTest, PositiveBasicTestCase) {
    //тест на создание и сложение
    Money money1(12345); 
    Money money2(5000);   
    Money money3 = money1.add(money2); 
    std::ostringstream oss;
    money3.print(oss);

    EXPECT_EQ(oss.str(), "173 руб. 45 коп.");
}

TEST(MoneyTest, PositiveBoundaryNTestCase) {
    // Граничный случай: number=0
    Money money1(0); 
    std::ostringstream oss;
    money1.print(oss);
    EXPECT_EQ(oss.str(), "0 руб. 00 коп.");
}

TEST(MoneyTest, PostivieMoveTestCase){
    // Тест на перемещение
    Money money1(12345);
    Money money2(std::move(money1));
    std::ostringstream oss1,oss2;
    money2.print(oss2);
    EXPECT_EQ(oss2.str(), "123 руб. 45 коп.");
    money1.print(oss1);
    EXPECT_EQ(oss1.str(), "0 руб. 00 коп.");
}

TEST(MoneyTest, PositiveDestructTestCase){
    // Тест на деструктор
    {
        Money money1(12345);
    }
    EXPECT_TRUE(true);
}

TEST(MoneyTest, NegativeZeroTestCase) {
    // Тест на сложение с нулём
    Money money1(100); 
    Money money2(0);    
    Money money3 = money1.add(money2); 
    std::ostringstream oss;


    money3.print(oss);
    EXPECT_EQ(oss.str(), "1 руб. 00 коп.");
}

TEST(MoneyTest, NegativeSubtractionOverflow) {
    // Тест на вычитание из меньшего большее число
    Money money1(5000); 
    Money money2(10000); 
    EXPECT_THROW(money1.sub(money2), std::logic_error);
}

TEST(MoneyTest, NegativeInvalidStringTestCase) {
    // Тест на некорректную строку
    EXPECT_THROW(Money m("abc"), std::invalid_argument);

}

TEST(MoneyTest, PositiveInitializerListTestCase) {
    // Тест конструктора со списком
    Money money({5, 4, 3, 2, 1}); 
    std::ostringstream oss;
    money.print(oss);
    EXPECT_EQ(oss.str(), "123 руб. 45 коп.");
}

TEST(MoneyTest, PositiveStringTestCase) {
    // Тест конструктора со строкой
    Money money("12345"); 
    std::ostringstream oss;
    money.print(oss);
    EXPECT_EQ(oss.str(), "123 руб. 45 коп.");
}

TEST(MoneyTest, NegativeInitializerListInvalid) {
    // Тест на некорректный список, который имеет элемент >9
    EXPECT_THROW(Money money({5, 4, 10, 2, 1}), std::invalid_argument);
}

TEST(MoneyTest, PositiveComparisonTestCase) {
    // Тест на сравнения
    Money money1(12345); 
    Money money2(5000);  
    EXPECT_TRUE(money1.more(money2));
    EXPECT_FALSE(money1.equals(money2));
    EXPECT_FALSE(money1.less(money2));
}

TEST(MoneyTest, PositiveCopyTestCase){
    // Тест на копирование
    Money money1(12345);
    Money money2(money1);
    std::ostringstream oss1, oss2;
    money1.print(oss1);
    money2.print(oss2);
    EXPECT_EQ(oss1.str(), oss2.str());

    Money money3=money2.add(Money(1000));
    std::ostringstream oss3;
    money3.print(oss3);
    EXPECT_EQ(oss1.str(), "123 руб. 45 коп.");
    EXPECT_EQ(oss3.str(), "133 руб. 45 коп.");
    EXPECT_TRUE(money1.equals(money2));
    EXPECT_FALSE(money1.equals(money3));

}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}