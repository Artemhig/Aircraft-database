#include "Database.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <limits>

namespace FlightScheduler {

Database::Database() : nextAircraftId(1), nextRouteId(1) {
    loadAircrafts();
    loadRoutes();
}

// ========== Aircraft ==========

void Database::addAircraft(const std::string& model, const std::string& pilot,
                           double speed, double fuel, double range) {
    aircrafts.emplace_back(nextAircraftId++, model, pilot, speed, fuel, range);
    saveAircrafts();
    std::cout << "Самолёт добавлен!" << std::endl;
}

void Database::removeAircraft(int id) {
    auto it = std::remove_if(aircrafts.begin(), aircrafts.end(),
        [id](const Aircraft& a) { return a.getId() == id; });
    if (it != aircrafts.end()) {
        aircrafts.erase(it, aircrafts.end());
        saveAircrafts();
        std::cout << "Самолёт удалён!" << std::endl;
    } else {
        std::cout << "Самолёт не найден!" << std::endl;
    }
}

void Database::editAircraft(int id) {
    Aircraft* a = findAircraft(id);
    if (!a) {
        std::cout << "Самолёт не найден!" << std::endl;
        return;
    }
    std::string newPilot;
    std::cout << "Введите нового пилота (текущий: " << a->getPilot() << "): ";
    std::cin.ignore();
    std::getline(std::cin, newPilot);
    a->setPilot(newPilot);
    saveAircrafts();
    std::cout << "Данные обновлены!" << std::endl;
}

void Database::listAircrafts() const {
    if (aircrafts.empty()) {
        std::cout << "Нет самолётов." << std::endl;
        return;
    }
    for (const auto& a : aircrafts) {
        a.display();
    }
}

Aircraft* Database::findAircraft(int id) {
    auto it = std::find_if(aircrafts.begin(), aircrafts.end(),
        [id](const Aircraft& a) { return a.getId() == id; });
    return it != aircrafts.end() ? &(*it) : nullptr;
}

// ========== Routes ==========

void Database::addRoute(const std::string& name, const Point& start, const Point& end) {
    routes.emplace_back(nextRouteId++, name, start, end);
    saveRoutes();
    std::cout << "Маршрут добавлен!" << std::endl;
}

void Database::removeRoute(int id) {
    auto it = std::remove_if(routes.begin(), routes.end(),
        [id](const Route& r) { return r.getId() == id; });
    if (it != routes.end()) {
        routes.erase(it, routes.end());
        saveRoutes();
        std::cout << "Маршрут удалён!" << std::endl;
    } else {
        std::cout << "Маршрут не найден!" << std::endl;
    }
}

void Database::listRoutes() const {
    if (routes.empty()) {
        std::cout << "Нет маршрутов." << std::endl;
        return;
    }
    for (const auto& r : routes) {
        r.display();
    }
}

Route* Database::findRoute(int id) {
    auto it = std::find_if(routes.begin(), routes.end(),
        [id](const Route& r) { return r.getId() == id; });
    return it != routes.end() ? &(*it) : nullptr;
}

// ========== Flights ==========

bool Database::dispatchFlight(int aircraftId, int routeId) {
    Aircraft* a = findAircraft(aircraftId);
    Route* r = findRoute(routeId);

    if (!a || !r) {
        std::cout << "Самолёт или маршрут не найдены!" << std::endl;
        return false;
    }

    if (a->getStatus() == AircraftStatus::IN_FLIGHT) {
        std::cout << "Самолёт уже в полёте!" << std::endl;
        return false;
    }

    double flightTime = r->calculateFlightTime(a->getSpeed());
    activeFlights.emplace_back(aircraftId, routeId, flightTime);
    a->setStatus(AircraftStatus::IN_FLIGHT);

    std::cout << "✈ Самолёт " << a->getModel() << " вылетел по маршруту \""
              << r->getName() << "\" | Время в пути: " << flightTime << " ч."
              << std::endl;
    return true;
}

void Database::listActiveFlights() const {
    if (activeFlights.empty()) {
        std::cout << "Нет активных полётов." << std::endl;
        return;
    }

    for (const auto& flight : activeFlights) {
        Aircraft* a = const_cast<Database*>(this)->findAircraft(flight.aircraftId);
        Route* r = const_cast<Database*>(this)->findRoute(flight.routeId);
        if (a && r) {
            Point pos = flight.getCurrentPosition(*r);
            std::cout << "✈ " << a->getModel() << " (ID:" << a->getId()
                      << ") | Маршрут: " << r->getName()
                      << " | Позиция: (" << pos.x << ", " << pos.y << ")"
                      << " | Осталось: " << flight.remainingTime << " ч."
                      << std::endl;
        }
    }
}

void Database::advanceTime(double hours) {
    for (auto& flight : activeFlights) {
        flight.updatePosition(hours);
    }

    // Remove completed flights
    auto it = std::remove_if(activeFlights.begin(), activeFlights.end(),
        [](const ActiveFlight& f) { return f.remainingTime <= 0; });
    for (auto rem = it; rem != activeFlights.end(); ++rem) {
        Aircraft* a = const_cast<Database*>(this)->findAircraft(rem->aircraftId);
        if (a) a->setStatus(AircraftStatus::ON_GROUND);
    }
    activeFlights.erase(it, activeFlights.end());

    std::cout << "⏱ Прошло " << hours << " ч. Полёты обновлены." << std::endl;
}

// ========== File I/O ==========

void Database::loadAircrafts() {
    std::ifstream file("data/aircrafts.txt");
    if (!file.is_open()) return;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        Aircraft a = Aircraft::fromFileString(line);
        aircrafts.push_back(a);
        if (a.getId() >= nextAircraftId)
            nextAircraftId = a.getId() + 1;
    }
    file.close();
}

void Database::saveAircrafts() const {
    std::ofstream file("data/aircrafts.txt");
    if (!file.is_open()) return;

    for (const auto& a : aircrafts) {
        file << a.toFileString() << std::endl;
    }
    file.close();
}

void Database::loadRoutes() {
    std::ifstream file("data/routes.txt");
    if (!file.is_open()) return;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        Route r = Route::fromFileString(line);
        routes.push_back(r);
        if (r.getId() >= nextRouteId)
            nextRouteId = r.getId() + 1;
    }
    file.close();
}

void Database::saveRoutes() const {
    std::ofstream file("data/routes.txt");
    if (!file.is_open()) return;

    for (const auto& r : routes) {
        file << r.toFileString() << std::endl;
    }
    file.close();
}

} // namespace