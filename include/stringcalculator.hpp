#include <string>
#include <tuple>
#include <vector>
#include <exception>

class StringCalculator
{
public:
    /// @brief Calculates sum of values in given string. If given string is not appropriate, function will throw exception.
    /// @param numbers is the string argument which contains numbers and delimiters.
    /// @return Returns sum of values in given string.
    static int add(const std::string& numbersString);
private:
    [[nodiscard]] static std::vector<int> getNumbers(const std::string& numbers);
    [[nodiscard]] static std::tuple<std::string, size_t> readSpecialDelimiterIfAvailableOrReturnDefault(const std::string &str);
    [[nodiscard]] static bool doesEndWithProperCharacter(const std::string& str);
    [[nodiscard]] static int getNumberAndAdvanceCharPosition(const std::string& str, size_t& charPosition);
    static void skipDelimiterAndAdvanceCharPosition(const std::string &str, const std::string &delimiter, size_t &charPosition);
    [[nodiscard]] static bool isNumeric(const std::string &str);
    [[nodiscard]] static bool isPositiveNumeric(char character);
    [[nodiscard]] static bool isNegativeNumeric(const std::string &str);
    static void checkForNegativeNumbers(const std::vector<int> &numbers);
};

class InvalidNumbersStringException : public std::exception 
{
public:
    explicit InvalidNumbersStringException(std::string msg) : message(std::move(msg)) {}

    [[nodiscard]] const char *what() const noexcept override
    {
        return message.c_str();
    }

private:
    std::string message;
};

class NegativeNumbersNotAllowedException : public std::exception 
{
public:
    explicit NegativeNumbersNotAllowedException(std::string msg) : message(std::move(msg)) {}

    [[nodiscard]] const char *what() const noexcept override
    {
        return message.c_str();
    }

private:
    std::string message;
};