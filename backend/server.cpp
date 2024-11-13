#include <iostream>
#include <cpprest/http_listener.h>
#include "todo.h"

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

Todo todo;

void handleGet(http_request request) {
    json::value responseData;
    auto tasks = todo.getTasks();
    for (size_t i = 0; i < tasks.size(); ++i) {
        responseData[i] = json::value::string(tasks[i]);
    }
    request.reply(status_codes::OK, responseData);
}

void handlePost(http_request request) {
    request.extract_json().then([=](json::value requestData) {
        std