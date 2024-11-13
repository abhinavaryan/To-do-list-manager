#include "todo.h"

void Todo::addTask(const std::string& task) {
    tasks.push_back(task);
}

std::vector<std::string> Todo::getTasks() const {
    return tasks;
}