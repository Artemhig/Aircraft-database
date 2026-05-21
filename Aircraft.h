#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include <string>
#include <iostream>

namespace FlightScheduler {

enum class AircraftStatus {
    ON_GROUND,
    IN_FLIGHT
};

class Aircraft {
private:
    int id;
    std::string model;
    std::string pilot;
    double speed;           // км/ч
    double fuelCapacity;    // литры
    double range;           // км
    AircraftStatus status;

public:
    Aircraft();
    Aircraft(int id, const std::string& model, const std::string& pilot,
             double speed, double fuelCapacity, double range);

    // Getters
    int getId() const;
    std::string getModel() const;
    std::string getPilot() const;
    double getSpeed() const;
    double getFuelCapacity() const;
    double getRange() const;
    AircraftStatus getStatus() const;

    // Setters
    void setPilot(const std::string& newPilot);
    void setStatus(AircraftStatus newStatus);

    // Display
    void display() const;

    // File I/O
    std::string toFileString() const;
    static Aircraft fromFileString(const std::string& line);
};

} // namespace

#endif