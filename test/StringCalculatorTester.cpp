#include "gtest/gtest.h"
#include "stringcalculator.hpp"


TEST(StringCalculatorTest, ReturnsZeroForEmptyString)
{
    ASSERT_EQ(0, StringCalculator::add(""));
}

TEST(StringCalculatorTest, ReturnsExactValueForOneParameterString)
{
    ASSERT_EQ(2, StringCalculator::add("2"));
    ASSERT_EQ(98, StringCalculator::add("98"));
    ASSERT_EQ(989, StringCalculator::add("989"));
    ASSERT_EQ(1000, StringCalculator::add("1000"));
}

TEST(StringCalculatorTest, CalculatesSumForCommaOrNewLineDelimittedString)
{
    
    ASSERT_EQ(5, StringCalculator::add("2,3"));
    ASSERT_EQ(10, StringCalculator::add("2,3,5"));
    ASSERT_EQ(10, StringCalculator::add("2,3,5,0"));
    ASSERT_EQ(43, StringCalculator::add("12,31"));
    ASSERT_EQ(585, StringCalculator::add("272\n313"));
    ASSERT_EQ(135, StringCalculator::add("92,43"));
    ASSERT_EQ(1092, StringCalculator::add("92,1000"));
    ASSERT_EQ(225, StringCalculator::add("92,43\n51\n16,23"));
    ASSERT_EQ(226, StringCalculator::add("92,43\n51\n16,23\n1"));
}

TEST(StringCalculatorTest, CalculatesSumForSpeciallyDelimittedString)
{
    
    ASSERT_EQ(4, StringCalculator::add("//;\n1;3"));
    ASSERT_EQ(6, StringCalculator::add("//|\n1|2|3"));
    ASSERT_EQ(7, StringCalculator::add("//sep\n2sep5"));
    ASSERT_EQ(799, StringCalculator::add("//sep\n212sep587"));
}

TEST(StringCalculatorTest, ThrowsExceptionForUnmeaningfulString)
{
    ASSERT_THROW(StringCalculator::add(",dhj"), InvalidNumbersStringException);
    ASSERT_THROW(StringCalculator::add(",5ss42"), InvalidNumbersStringException);
    ASSERT_THROW(StringCalculator::add("1241,5ss42"), InvalidNumbersStringException);
    ASSERT_THROW(StringCalculator::add("1241\\5ss42"), InvalidNumbersStringException);
    ASSERT_THROW(StringCalculator::add(",1"), InvalidNumbersStringException);
    ASSERT_THROW(StringCalculator::add(",123"), InvalidNumbersStringException);
    ASSERT_THROW(StringCalculator::add("\\123"), InvalidNumbersStringException);
    ASSERT_THROW(StringCalculator::add("\\n123"), InvalidNumbersStringException);
    ASSERT_THROW(StringCalculator::add("\n865"), InvalidNumbersStringException);
    ASSERT_THROW(StringCalculator::add("n865"), InvalidNumbersStringException);
    ASSERT_THROW(StringCalculator::add("8,\n65"), InvalidNumbersStringException);
    ASSERT_THROW(StringCalculator::add("8,6,\n5"), InvalidNumbersStringException);
    ASSERT_THROW(StringCalculator::add("8,6,5\n"), InvalidNumbersStringException);
    ASSERT_THROW(StringCalculator::add("8,6,5n"), InvalidNumbersStringException);
    ASSERT_THROW(StringCalculator::add("asdafn123"), InvalidNumbersStringException);
    ASSERT_THROW(StringCalculator::add("1,2,3,"), InvalidNumbersStringException);
    ASSERT_THROW(StringCalculator::add("1,2,3,s"), InvalidNumbersStringException);
    ASSERT_THROW(StringCalculator::add("//|\n1|2,3"), InvalidNumbersStringException);
    ASSERT_THROW(StringCalculator::add("/|\n1|2|3"), InvalidNumbersStringException);
    ASSERT_THROW(StringCalculator::add("//|1|2|3"), InvalidNumbersStringException);
    ASSERT_THROW(StringCalculator::add("//|\n1|2|-"), InvalidNumbersStringException);
}

TEST(StringCalculatorTest, ThrowsExceptionForNegativeNumbers)
{
    ASSERT_THROW(StringCalculator::add("1,-2"), NegativeNumbersNotAllowedException);
    ASSERT_THROW(StringCalculator::add("-1,2"), NegativeNumbersNotAllowedException);
    ASSERT_THROW(StringCalculator::add("//;\n1;-3"), NegativeNumbersNotAllowedException);
    ASSERT_THROW(StringCalculator::add("//|\n1|-2|3"), NegativeNumbersNotAllowedException);
    ASSERT_THROW(StringCalculator::add("//sep\n-2sep5"), NegativeNumbersNotAllowedException);
    ASSERT_THROW(StringCalculator::add("//sep\n212sep-587"), NegativeNumbersNotAllowedException);
}

TEST(StringCalculatorTest, NumbersBiggerThan1000IsIgnored)
{
    ASSERT_EQ(0, StringCalculator::add("1001"));
    ASSERT_EQ(8, StringCalculator::add("1002,3,5,0"));
    ASSERT_EQ(12, StringCalculator::add("12,31000"));
    ASSERT_EQ(272, StringCalculator::add("272\n3130"));
    ASSERT_EQ(1, StringCalculator::add("//;\n1;1003"));
    ASSERT_EQ(4, StringCalculator::add("//|\n1|2002|3"));
    ASSERT_EQ(122, StringCalculator::add("//sep\n122sep5009"));
    ASSERT_EQ(212, StringCalculator::add("//sep\n212sep5870"));
}