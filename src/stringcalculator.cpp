#include <array>
#include <algorithm>
#include <numeric>
#include <sstream>
#include "stringcalculator.hpp"

int StringCalculator::add(const std::string& numbersString)
{
    if(numbersString.empty())
        return 0;

    if(!doesEndWithProperCharacter(numbersString))
        throw InvalidNumbersStringException(std::string("String does not end with proper character: ") + numbersString);

    std::vector<int> extractedNumbers = getNumbers(numbersString);

    checkForNegativeNumbers(extractedNumbers);
       
    return std::reduce(extractedNumbers.begin(), extractedNumbers.end());
}

bool StringCalculator::doesEndWithProperCharacter(const std::string& str)
{
    if(str.empty())
        return false;

    const char lastCharacter = str.at(str.length() - 1);
    return isPositiveNumeric(lastCharacter);
}

std::vector<int> StringCalculator::getNumbers(const std::string& numbersString)
{
    auto [delimiter, charPosition] = readSpecialDelimiterIfAvailableOrReturnDefault(numbersString);
    std::vector<int> numbers;

    while(charPosition < numbersString.length())
    {
        if(!isNumeric(numbersString.substr(charPosition)))
            throw InvalidNumbersStringException(std::string("Number expected but Invalid character found: ") + numbersString.substr(charPosition));

        const int number = getNumberAndAdvanceCharPosition(numbersString, charPosition);
        constexpr int numberLimit = 1000;
        if(number <= numberLimit)
            numbers.push_back(number);

        if(charPosition >= numbersString.length())
            break;

        skipDelimiterAndAdvanceCharPosition(numbersString, delimiter, charPosition);
    }
    
    return numbers;
}

bool StringCalculator::isNumeric(const std::string& str)
{
    if(str.empty())
        return false;
    
    return isNegativeNumeric(str) || isPositiveNumeric(str.at(0));
}

bool StringCalculator::isNegativeNumeric(const std::string& str)
{
    if(str.length() < 2)
        return false;

    return (str.at(0) == '-') && isPositiveNumeric(str.at(1));
}

bool StringCalculator::isPositiveNumeric(char character)
{
    static constexpr std::array<char, 10> validNumbers{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    return validNumbers.end() != std::find(validNumbers.begin(), validNumbers.end(), character);
}

// Beginning of str should match "//[delimiter]\n" syntax for special delimiters
std::tuple<std::string, size_t> StringCalculator::readSpecialDelimiterIfAvailableOrReturnDefault(const std::string& str)
{
    constexpr size_t minimumCharCountForDelimiterDeclaration = 4; // '//' is 2, [delimiter] is 1, '\n' is 1 = 4
    if(str.length() > minimumCharCountForDelimiterDeclaration)
    {
        const std::string delimiterDeclarationStart { "//" };
        const char delimiterDeclarationEnd = '\n';

        if(str.substr(0, 2) == delimiterDeclarationStart)
        {
            std::stringstream delimiterSS;

            size_t charPosition = 2; // Start reading after '//' characters
            while((charPosition < str.length() - 1) && (str.at(charPosition) != delimiterDeclarationEnd))
            {
                delimiterSS << str.at(charPosition);
                charPosition++;
            }
            
            if(str.at(charPosition) == delimiterDeclarationEnd) // Delimiter syntax matches
            {
                return {delimiterSS.str(), charPosition + 1};
            }
        }
    }

    return {",", 0};
}

int StringCalculator::getNumberAndAdvanceCharPosition(const std::string& str, size_t& charPosition)
{
    std::stringstream numberSS;

    while ( (charPosition < str.length()) && isNumeric(str.substr(charPosition)) )
    {
        numberSS << str.at(charPosition);
        charPosition++;
    }
    
    int extractedNumber = 0;
    numberSS >> extractedNumber;

    return extractedNumber;
}

void StringCalculator::skipDelimiterAndAdvanceCharPosition(const std::string& str, const std::string& delimiter, size_t& charPosition)
{
    if(!str.empty())
    {
        if(str.substr(charPosition, delimiter.length()) ==  delimiter)
        {
            charPosition = charPosition + delimiter.length();
            return;
        }

        if(str.at(charPosition) == '\n')
        {
            charPosition = charPosition + 1;
            return;
        }
    }
    
    std::stringstream exceptionSS;
    exceptionSS << "Delimiter (" << delimiter << ") or '\\n' expected but invalid character found: " 
        << str.at(charPosition) << " at position: " << charPosition;

    throw InvalidNumbersStringException(exceptionSS.str());
}

void StringCalculator::checkForNegativeNumbers(const std::vector<int>& numbers)
{
    std::vector<int> negativeNumbers;
    std::copy_if(numbers.begin(), numbers.end(), std::back_inserter(negativeNumbers), 
        [](int number){ return number < 0; });

    if(!negativeNumbers.empty())
    {
        std::stringstream exceptionSS;
        exceptionSS << "Negative numbers not allowed: ";
        
        for(const int number : negativeNumbers)
        {
            exceptionSS << number << ",";
        }

        throw NegativeNumbersNotAllowedException(exceptionSS.str().substr(0, exceptionSS.str().length() - 1));
    }
}