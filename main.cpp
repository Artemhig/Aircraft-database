#include "Database.h"
#include <iostream>
#include <limits>

using namespace FlightScheduler;

void clearCin() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void aircraftMenu(Database& db) {
    int sub;
    std::cout << "\n--- Управление самолётами ---\n";
    std::cout << "1. Добавить\n2. Удалить\n3. Редактировать пилота\n4. Список\n0. Назад\nВыбор: ";
    std::cin >> sub;

    if (sub == 1) {
        std::string model, pilot;
        double speed, fuel, range;
        std::cout << "Модель: "; std::cin >> model;
        std::cout << "Пилот: "; std::cin >> pilot;
        std::cout << "Скорость (км/ч): "; std::cin >> speed;
        std::cout << "Запас топлива (л): "; std::cin >> fuel;
        std::cout << "Дальность (км): "; std::cin >> range;
        db.addAircraft(model, pilot, speed, fuel, range);
    } else if (sub == 2) {
        int id; std::cout << "ID самолёта: "; std::cin >> id;
        db.removeAircraft(id);
    } else if (sub == 3) {
        int id; std::cout << "ID самолёта: "; std::cin >> id;
        db.editAircraft(id);
    } else if (sub == 4) {
        db.listAircrafts();
    }
}

void routeMenu(Database& db) {
    int sub;
    std::cout << "\n--- Управление маршрутами ---\n";
    std::cout << "1. Добавить\n2. Удалить\n3. Список\n0. Назад\nВыбор: ";
    std::cin >> sub;

    if (sub == 1) {
        std::string name;
        double sx, sy, ex, ey;
        std::cout << "Название: "; std::cin >> name;
        std::cout << "Старт (x y): "; std::cin >> sx >> sy;
        std::cout << "Конец (x y): "; std::cin >> ex >> ey;
        db.addRoute(name, Point(sx, sy), Point(ex, ey));
    } else if (sub == 2) {
        int id; std::cout << "ID маршрута: "; std::cin >> id;
        db.removeRoute(id);
    } else if (sub == 3) {
        db.listRoutes();
    }
}

int main() {
    Database db;
    int choice;

    do {
        std::cout << "\n===== ПЛАНИРОВЩИК ПОЛЁТОВ =====\n";
        std::cout << "1. Самолёты\n";
        std::cout << "2. Маршруты\n";
        std::cout << "3. Отправить самолёт\n";
        std::cout << "4. Активные полёты\n";
        std::cout << "5. Проматываем время\n";
        std::cout << "0. Выход\n";
        std::cout << "Выбор: ";
        std::cin >> choice;

        switch (choice) {
            case 1: aircraftMenu(db); break;
            case 2: routeMenu(db); break;
            case 3: {
                int aid, rid;
                std::cout << "ID самолёта: "; std::cin >> aid;
                std::cout << "ID маршрута: "; std::cin >> rid;
                db.dispatchFlight(aid, rid);
                break;
            }
            case 4: db.listActiveFlights(); break;
            case 5: {
                double hours;
                std::cout << "Сколько часов прошло: ";
                std::cin >> hours;
                db.advanceTime(hours);
                break;
            }
        }
    } while (choice != 0);

    return 0;
}