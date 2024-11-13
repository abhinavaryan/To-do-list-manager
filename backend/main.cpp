#include <crow.h>
#include "task_manager.h"
#include <json/json.h>

int main() {
    crow::SimpleApp app;
    TaskManager taskManager;

    CROW_ROUTE(app, "/api/tasks")
    .methods("POST"_method)([&taskManager](const crow::request& req) {
        auto json = crow::json::load(req.body);
        std::string taskText = json["task"].s();
        Task newTask = taskManager.addTask(taskText);
        crow::json::wvalue response;
        response["id"] = newTask.id;
        response["text"] = newTask.text;
        response["completed"] = newTask.completed;
        return crow::response{response};
    });

    CROW_ROUTE(app, "/api/tasks/<int>")
    .methods("PUT"_method)([&taskManager](int id, const crow::request& req) {
        auto json = crow::json::load(req.body);
        std::string taskText = json["task"].s();
        return taskManager.updateTask(id, taskText) ? crow::response{200} : crow::response{404};
    });

    CROW_ROUTE(app, "/api/tasks/<int>")
    .methods("DELETE"_method)([&taskManager](int id) {
        return taskManager.deleteTask(id) ? crow::response{200} : crow::response{404};
    });

    CROW_ROUTE(app, "/api/tasks/<int>/complete")
    .methods("PUT"_method)([&taskManager](int id, const crow::request& req) {
        auto json = crow::json::load(req.body);
        bool completed = json["completed"].b();
        return taskManager.updateTaskCompletion(id, completed) ? crow::response{200} : crow::response{404};
    });

    CROW_ROUTE(app, "/api/tasks")
    .methods("GET"_method)([&taskManager]() {
        crow::json::wvalue response;
        for (const auto& task : taskManager.getTasks()) {
            crow::json::wvalue taskJson;
            taskJson["id"] = task.id;
            taskJson["text"] = task.text;
            taskJson["completed"] = task.completed;
            response.push_back(taskJson);
        }
        return crow::response{response};
    });

    app.port(18080).multithreaded().run();
}
