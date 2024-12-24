#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::string lonComSub(const std::string& str1, const std::string& str2) {
    int maxLength = 0;
    int endIndex = 0;

    std::vector<std::vector<int>> dp(str1.length() + 1, std::vector<int>(str2.length() + 1, 0));


    for (int i = 1; i <= str1.length(); ++i) {
        for (int j = 1; j <= str2.length(); ++j) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1; 
                if (dp[i][j] > maxLength) {
                    maxLength = dp[i][j];
                    endIndex = i; 
                }
            }
        }
    }


    return str1.substr(endIndex - maxLength, maxLength);
}

int main() {
    std::string input;
    std::cout << "Введите строку из 10 слов: ";
    std::getline(std::cin, input);

    std::istringstream iss(input);
    std::string word;
    std::vector<std::string> words;

    while (iss >> word) {
        words.push_back(word);
    }


    std::string lonSubStr;
    

    for (size_t i = 0; i < words.size(); ++i) {
        for (size_t j = i + 1; j < words.size(); ++j) {
            std::string curSub = lonComSub(words[i], words[j]);
            if (curSub.length() > lonSubStr.length()) {
                lonSubStr = curSub;
            }
        }
    }

    std::cout << "Самая длинная общая подстрока: " << lonSubStr << std::endl;
    

    return 0;
}
