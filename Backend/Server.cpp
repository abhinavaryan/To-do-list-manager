#include <iostream>
#include <vector>
#include <string>
#include <cppnetlib/http/server.hpp>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

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

    json toJson() const {
        return json{{"title", title}, {"description", description}, {"completed", completed}};
    }
};

class ToDoList {
private:
    std::vector<Task> tasks;

public:
    void addTask(const Task& task) {
        tasks.push_back(task);
    }

    json getTasksAsJson() const {
        json taskList = json::array();
        for (const auto& task : tasks) {
            taskList.push_back(task.toJson());
        }
        return taskList;
    }
};

ToDoList todoList;

void handle_request(const cppnetlib::http::request& req, cppnetlib::http::response& res) {
    if (req.method() == "GET" && req.path() == "/tasks") {
        res.set_content(todoList.getTasksAsJson().dump(), "application/json");
    } else if (req.method() == "POST" && req.path() == "/tasks") {
        json newTask = json::parse(req.body());
        todoList.addTask(Task(newTask["title"], newTask["description"]));
        res.set_content("Task added", "text/plain");
    } else {
        res.set_content("Not Found", "text/plain");
        res.status(404);
    }
}

int main() {
    cppnetlib::http::server server(3000);
    server.set_request_handler(handle_request);
    server.start();
    return 0;
}
