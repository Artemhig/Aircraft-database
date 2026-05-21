#ifndef DATABASE_H
#define DATABASE_H
#include "Aircraft.h"
#include "Route.h"
#include "Flight.h"
#include <vector>
#include <string>

namespace FlightScheduler {

class Database {
private:
    std::vector<Aircraft> aircrafts;
    std::vector<Route> routes;
    std::vector<ActiveFlight> activeFlights;
    int nextAircraftId;
    int nextRouteId;

    void loadAircrafts();
    void saveAircrafts() const;
    void loadRoutes();
    void saveRoutes() const;

public:
    Database();

    // Aircraft management
    void addAircraft(const std::string& model, const std::string& pilot,
                     double speed, double fuel, double range);
    void removeAircraft(int id);
    void editAircraft(int id);
    void listAircrafts() const;
    Aircraft* findAircraft(int id);

    // Route management
    void addRoute(const std::string& name, const Point& start, const Point& end);
    void removeRoute(int id);
    void listRoutes() const;
    Route* findRoute(int id);

    // Flight operations
    bool dispatchFlight(int aircraftId, int routeId);
    void listActiveFlights() const;
    void advanceTime(double hours);
};

} // namespace

#endif