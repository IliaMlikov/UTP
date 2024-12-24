#include <iostream>
#include <sstream>
#include <string>

int countB(const std::string& input) {
    std::istringstream iss(input);
    std::string word;
    int count = 0;

    while (iss >> word) {
        if (!word.empty() && word.back() == 'b') {
            count++;
        }
    }

    return count;
}

int length(const std::string& input) {
    std::istringstream iss(input);
    std::string word;
    int maxLength = 0;

    while (iss >> word) {
        if (word.length() > maxLength) {
            maxLength = word.length();
        }
    }

    return maxLength;
}

int countD(const std::string& input) {
    std::istringstream iss(input);
    std::string word;
    std::string lastWord;

    while (iss >> word) {
        lastWord = word;
    }

    int count = 0;
    for (char c : lastWord) {
        if (c == 'd') {
            count++;
        }
    }

    return count;
}

int main() {
    std::string userInput;
    std::cout << "Введите строку из 10 слов: ";
    std::getline(std::cin, userInput);

    int result1 = countB(userInput);
    std::cout << "Количество слов, оканчивающихся на 'b': " << result1 << std::endl;
    int result2 = length(userInput);
    std::cout << "Длина самого длинного слова: " << result2 << std::endl;
    int result3 = countD(userInput);
    std::cout << "Количество букв 'd' в последнем слове: " << result3 << std::endl;


    std::istringstream iss(userInput);
    std::string word;
    int count = 0;


    while (iss >> word) {
        if (word.length() >= 3) {
            if (word[1] == word[word.length() - 2]) {
                count++;
            }
        }
    }
    std::cout << "Количество слов с совпадающими вторым и предпоследним символами: " << count << std::endl;




    return 0;
}