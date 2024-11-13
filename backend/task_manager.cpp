#include "task_manager.h"

nlohmann::json TaskManager::getTasks() {
    nlohmann::json jTasks = nlohmann::json::array();
    for (const auto& task : tasks) {
        jTasks.push_back({{"id", task.id}, {"text", task.text}, {"completed", task.completed}});
    }
    return jTasks;
}

Task TaskManager::addTask(const std::string& text) {
    Task newTask(nextId++, text);
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
    auto it = std::remove_if(tasks.begin(), tasks.end(), [id](Task& task) {
        return task.id == id;
    });
    if (it != tasks.end()) {
        tasks.erase(it, tasks.end());
        return true;
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
