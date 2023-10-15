#include <optional>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>
#include <iostream>

template <typename T>
using Maybe = std::optional<T>;

auto readFile = [](const std::string &filename) -> Maybe<std::string>
{
    std::ifstream file(filename);

    if (file.is_open())
    {
        std::string content;
        std::string line;
        while (std::getline(file, line))
        {
            content += line + '\n';
        }

        return Maybe<std::string>(content);
    }
    else
    {
        return Maybe<std::string>();
    }
};

auto isASCII = [](const std::string &content) -> Maybe<bool>
{
    bool isAscii = std::all_of(content.begin(), content.end(), [](char c)
                               { return static_cast<unsigned char>(c) <= 127; });
    return Maybe<bool>(isAscii);
};

auto processFileContent = [](auto &result) -> Maybe<std::string>
{
    return result.has_value() ? (isASCII(result.value()) == true ? result : Maybe<std::string>()) : Maybe<std::string>();
};

int main()
{
    const std::string filename = "sample.txt";
    auto content = readFile(filename);
    auto result = processFileContent(content);

    if (result.has_value())
    {
        std::cout << "File content is in ASCII format:" << std::endl;
        std::cout << result.value() << std::endl;
    }
    else
    {
        std::cerr << "Error: File content is not in ASCII format or could not be read." << std::endl;
    }

    return 0;
}