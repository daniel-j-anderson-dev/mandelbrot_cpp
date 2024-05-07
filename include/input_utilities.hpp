#ifndef INPUT_UTILITIES_HPP
#define INPUT_UTILITIES_HPP

#include <iostream>
#include <string_view>
#include <sstream>

/// @brief This function `prompt`s the user for a line of input.
/// @param prompt A message that tells the user what to input. (not mutated)
/// @return A line of user input with trailing whitespace removed
/// @throws `std::ios::failure` when printing or reading input fails with either `std::ios::failbit` or `std::ios::badbit`
std::string getInput(const std::string_view prompt) {
    std::cout.exceptions(std::ios::failbit | std::ios::badbit);
    std::cin.exceptions(std::ios::failbit | std::ios::badbit);

    try {
        std::cout << prompt;
        std::cout.flush();

        std::string input;
        std::getline(std::cin, input);

        size_t end = input.find_last_not_of(" \n\r\t");
        if (end != std::string::npos) {
            input.erase(end + 1);
        }

        return input;
    }
    catch (const std::ios::failure& io_error) {
        throw io_error;
    }
}

/// @brief Prompts the user for a line of input and parses it into the specified type.
/// @tparam T the type that will be parsed from input
/// @param prompt A message to guide the user on what to input. Can be either a const char* or std::std::string.
/// @return The user's input parsed as type T.
/// @throws `std::ios::failure` if there is an I/O error during input or output operations.
/// @throws `std::invalid_argument` if the input cannot be parsed into the specified type T.
/// @note This function will repeatedly prompt the user until valid input is provided.
/// @code
/// ```
/// // Prompt the user for a radius and parse it as a double
/// double radius = getParsedInput<double>("Please enter the radius: ");
/// ```
/// @endcode
/// @see getInput
template <typename T>
T getParsedInput(const std::string_view prompt) {
    std::cerr.exceptions(std::ios::failbit | std::ios::badbit);

    while (true) {
        try {
            std::string input = getInput(prompt);

            std::stringstream stream(input);
            T parsedInput;
            stream >> parsedInput;

            if (!stream.fail() && stream.eof()) {
                return parsedInput;
            }
            else {
                std::cerr << "\nInvalid Input\nPlease try again\n" << std::endl;
            }
        }
        catch (const std::exception& io_error) {
            throw io_error;
        }
    }
}

#endif