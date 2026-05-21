#include "Route.h"
#include <cmath>
#include <sstream>
#include <iostream>

namespace FlightScheduler {

Route::Route() : id(-1), name(""), start(0, 0), end(0, 0) {}

Route::Route(int id, const std::string& name, const Point& start, const Point& end)
    : id(id), name(name), start(start), end(end) {}

int Route::getId() const { return id; }
std::string Route::getName() const { return name; }
Point Route::getStart() const { return start; }
Point Route::getEnd() const { return end; }

double Route::calculateDistance() const {
    double dx = end.x - start.x;
    double dy = end.y - start.y;
    return std::sqrt(dx * dx + dy * dy);
}

double Route::calculateFlightTime(double aircraftSpeed) const {
    if (aircraftSpeed <= 0) return 0;
    return calculateDistance() / aircraftSpeed;
}

Point Route::getPositionAtProgress(double progress) const {
    if (progress <= 0) return start;
    if (progress >= 1) return end;
    double x = start.x + (end.x - start.x) * progress;
    double y = start.y + (end.y - start.y) * progress;
    return Point(x, y);
}

void Route::display() const {
    std::cout << "ID: " << id
              << " | Маршрут: " << name
              << " | (" << start.x << ", " << start.y
              << ") -> (" << end.x << ", " << end.y << ")"
              << " | Расстояние: " << calculateDistance() << " км"
              << std::endl;
}

std::string Route::toFileString() const {
    return std::to_string(id) + "|" + name + "|" +
           std::to_string(start.x) + "|" + std::to_string(start.y) + "|" +
           std::to_string(end.x) + "|" + std::to_string(end.y);
}

Route Route::fromFileString(const std::string& line) {
    std::stringstream ss(line);
    std::string token;
    int id;
    std::string name;
    double sx, sy, ex, ey;

    std::getline(ss, token, '|'); id = std::stoi(token);
    std::getline(ss, name, '|');
    std::getline(ss, token, '|'); sx = std::stod(token);
    std::getline(ss, token, '|'); sy = std::stod(token);
    std::getline(ss, token, '|'); ex = std::stod(token);
    std::getline(ss, token, '|'); ey = std::stod(token);

    return Route(id, name, Point(sx, sy), Point(ex, ey));
}

} // namespace