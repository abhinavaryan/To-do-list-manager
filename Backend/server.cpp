22#include <iostream>
23#include <vector>
24#include <string>
25#include <cppnetlib/http/server.hpp>
26#include <nlohmann/json.hpp>
27
28using json = nlohmann::json;
29
30class Task {
31private:
32    std::string title;
33    std::string description;
34    bool completed;
35
36public:
37    Task(const std::string& title, const std::string& description)
38        : title(title), description(description), completed(false) {}
39
40    void markAsCompleted() {
41        completed = true;
42    }
43
44    json toJson() const {
45        return json{{"title", title}, {"description", description}, {"completed", completed}};
46    }
47};
48
49class ToDoList {
50private:
51    std::vector<Task> tasks;
52
53public:
54    void addTask(const Task& task) {
55        tasks.push_back(task);
56    }
57
58    json getTasksAsJson() const {
59        json taskList = json::array();
60        for (const auto& task : tasks) {
61            taskList.push_back(task.toJson());
62        }
63        return taskList;
64    }
65};
66
67ToDoList todoList;
68
69void handle_request(const cppnetlib::http::request& req, cppnetlib::http::response& res) {
70    if (req.method() == "GET" && req.path() == "/tasks") {
71        res.set_content(todoList.getTasksAsJson().dump(), "application/json");
72    } else if (req.method() == "POST" && req.path() == "/tasks") {
73        json newTask = json::parse(req.body());
74        todoList.addTask(Task(newTask["title"], newTask["description"]));
75        res.set_content("Task added", "text/plain");
76    } else {
77        res.set_content("Not Found", "text/plain");
78        res.status(404);
79    }
80}
81
82int main() {
83    cppnetlib::http::server server(3000);
84    server.set_request_handler(handle_request);
85    server.start();
86    return 0;
87}
