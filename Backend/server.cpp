#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

class Task {
private:
    std::string title;
    std::string description;
    bool completed;

public:
    Task(const std::string& title, const std::string& description)
        : title(title), description(description), completed(false) {}

    void markAsCompleted() {
        completed = true;
    }

    std::string getTitle() const {
        return title;
    }

    std::string getDescription() const {
        return description;
    }

    bool isCompleted() const {
        return completed;
    }

    void display() const {
        std::cout << "Title: " << title << "\n"
                  << "Description: " << description << "\n"
                  << "Status: " << (completed ? "Completed" : "Pending") << "\n";
    }
};

class ToDoList {
private:
    std::vector<Task> tasks;

public:
    void addTask(const Task& task) {
        tasks.push_back(task);
    }

    void removeTask(int index) {
        if (index >= 0 && index < tasks.size()) {
            tasks.erase(tasks.begin() + index);
        } else {
            std::cout << "Invalid task index!\n";
        }
    }

    void markTaskAsCompleted(int index) {
        if (index >= 0 && index < tasks.size()) {
            tasks[index].markAsCompleted();
        } else {
            std::cout << "Invalid task index!\n";
        }
    }

    void displayTasks() const {
        if (tasks.empty()) {
            std::cout << "No tasks available.\n";
            return;
        }
        for (size_t i = 0; i < tasks.size(); ++i) {
            std::cout << "Task " << i + 1 << ":\n";
            tasks[i].display();
            std::cout << std::endl;
        }
    }
};

void displayMenu() {
    std::cout << "To-Do List Manager\n";
    std::cout << "1. Add Task\n";
    std::cout << "2. Remove Task\n";
    std::cout << "3. Mark Task as Completed\n";
    std::cout << "4. Display Tasks\n";
    std::cout << "5. Exit\n";
    std::cout << "Choose an option: ";
}

int main() {
    ToDoList todoList;
    int choice;

    do {
        displayMenu();
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string title, description;
                std::cout << "Enter task title: ";
                std::cin.ignore(); // Clear the newline character from the input buffer
                std::getline(std::cin, title);
                std::cout << "Enter task description: ";
                std::getline(std::cin, description);
                todoList.addTask(Task(title, description));
                break;
            }
            case 2: {
                int index;
                std::cout << "Enter task index to remove: ";
                std::cin >> index;
                todoList.removeTask(index - 1); // Adjust for zero-based index
                break;
            }
            case 3: {
                int index;
                std::cout << "Enter task index to mark as completed: ";
                std::cin >> index;
                todoList.markTaskAsCompleted(index - 1); // Adjust for zero-based index
                break;
            }
            case 4:
                todoList.displayTasks();
                break;
            case 5:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}