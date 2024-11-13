#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include <string>
#include <vector>
#include <unordered_map>

struct Task {
    int id;
    std::string text;
    bool completed;
};

class TaskManager {
private:
    std::vector<Task> tasks;
    int nextId;

public:
    TaskManager();
    Task addTask(const std::string& text);
    bool updateTask(int id, const std::string& text);
    bool deleteTask(int id);
    bool updateTaskCompletion(int id, bool completed);
    const std::vector<Task>& getTasks() const;
};

#endif // TASK_MANAGER_H
