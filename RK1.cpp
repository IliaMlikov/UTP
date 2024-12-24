#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

struct Task {
    std::string name;
    int priority;
    std::string deadline;


    bool operator<(const Task& other) const {
        return priority > other.priority;
    }
};

void displayTasks(const std::vector<Task>& tasks) {
    std::cout << "\nСписок задач:\n";
    for (const auto& task : tasks) {
        std::cout << "Задача: " << task.name 
                  << ", Приоритет: " << task.priority 
                  << ", Срок выполнения: " << task.deadline << '\n';
    }
}

int main() {
    std::vector<Task> tasks;
    std::string addMore;

    do {
        Task task;
        
        std::cout << "Введите название задачи: ";
        std::getline(std::cin, task.name);

        std::cout << "Введите приоритет задачи: ";
        std::cin >> task.priority;
        std::cin.ignore();

        std::cout << "Введите срок выполнения задачи: ";
        std::getline(std::cin, task.deadline);

        tasks.push_back(task);
        std::cout << "Задача добавлена\n";

        std::cout << "Хотите добавить еще одну задачу?: ";
        std::getline(std::cin, addMore);

    } while (addMore == "да");

    std::sort(tasks.begin(), tasks.end());
    displayTasks(tasks);

    return 0;
}
 