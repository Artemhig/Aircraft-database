#include "Aircraft.h"
#include <sstream>

namespace FlightScheduler {

Aircraft::Aircraft()
    : id(-1), model(""), pilot(""), speed(0), fuelCapacity(0), range(0),
      status(AircraftStatus::ON_GROUND) {}

Aircraft::Aircraft(int id, const std::string& model, const std::string& pilot,
                   double speed, double fuelCapacity, double range)
    : id(id), model(model), pilot(pilot), speed(speed),
      fuelCapacity(fuelCapacity), range(range), status(AircraftStatus::ON_GROUND) {}

int Aircraft::getId() const { return id; }
std::string Aircraft::getModel() const { return model; }
std::string Aircraft::getPilot() const { return pilot; }
double Aircraft::getSpeed() const { return speed; }
double Aircraft::getFuelCapacity() const { return fuelCapacity; }
double Aircraft::getRange() const { return range; }
AircraftStatus Aircraft::getStatus() const { return status; }

void Aircraft::setPilot(const std::string& newPilot) { pilot = newPilot; }
void Aircraft::setStatus(AircraftStatus newStatus) { status = newStatus; }

void Aircraft::display() const {
    std::cout << "ID: " << id
              << " | Модель: " << model
              << " | Пилот: " << pilot
              << " | Скорость: " << speed << " км/ч"
              << " | Статус: " << (status == AircraftStatus::IN_FLIGHT ? "В полёте" : "На земле")
              << std::endl;
}

std::string Aircraft::toFileString() const {
    return std::to_string(id) + "|" + model + "|" + pilot + "|" +
           std::to_string(speed) + "|" + std::to_string(fuelCapacity) + "|" +
           std::to_string(range) + "|" + std::to_string(static_cast<int>(status));
}

Aircraft Aircraft::fromFileString(const std::string& line) {
    std::stringstream ss(line);
    std::string token;
    int id, statusInt;
    std::string model, pilot;
    double speed, fuelCapacity, range;

    std::getline(ss, token, '|'); id = std::stoi(token);
    std::getline(ss, model, '|');
    std::getline(ss, pilot, '|');
    std::getline(ss, token, '|'); speed = std::stod(token);
    std::getline(ss, token, '|'); fuelCapacity = std::stod(token);
    std::getline(ss, token, '|'); range = std::stod(token);
    std::getline(ss, token, '|'); statusInt = std::stoi(token);

    Aircraft a(id, model, pilot, speed, fuelCapacity, range);
    a.setStatus(static_cast<AircraftStatus>(statusInt));
    return a;
}

} // namespace