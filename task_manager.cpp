#include "task_manager.h"

TaskManager::TaskManager() : nextId(1) {}

Task TaskManager::addTask(const std::string& text) {
    Task newTask = { nextId++, text, false };
    tasks.push_back(newTask);
    return newTask;
}

bool TaskManager::updateTask(int id, const std::string& text) {
    for (auto& task : tasks) {
        if (task.id == id) {
            task.text = text;
            return true;
        }
    }
    return false;
}

bool TaskManager::deleteTask(int id) {
    for (auto it = tasks.begin(); it != tasks.end(); ++it) {
        if (it->id == id) {
            tasks.erase(it);
            return true;
        }
    }
    return false;
}

bool TaskManager::updateTaskCompletion(int id, bool completed) {
    for (auto& task : tasks) {
        if (task.id == id) {
            task.completed = completed;
            return true;
        }
    }
    return false;
}

const std::vector<Task>& TaskManager::getTasks() const {
    return tasks;
}
