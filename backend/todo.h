#ifndef TODO_H
#define TODO_H

#include <string>
#include <vector>

class Todo {
public:
    void addTask(const std::string& task);
    std::vector<std::string> getTasks() const;

private:
    std::vector<std::string> tasks;
};

#endif