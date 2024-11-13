#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

class Task {
public:
    int id;
    std::string text;
    bool completed;

    Task(int id, const std::string& text, bool completed = false)
        : id(id), text(text), completed(completed) {}
};

class TaskManager {
private:
    std::vector<Task> tasks;
    int nextId;

public:
    TaskManager() : nextId(1) {}

    nlohmann::json getTasks();
    Task addTask(const std::string& text);
    bool updateTask(int id, const std::string& text);
    bool deleteTask(int id);
    bool updateTaskCompletion(int id, bool completed);
};

#endif // TASK_MANAGER_H
