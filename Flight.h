#ifndef FLIGHT_H
#define FLIGHT_H

#include "Aircraft.h"
#include "Route.h"

namespace FlightScheduler {

struct ActiveFlight {
    int aircraftId;
    int routeId;
    double remainingTime;
    double progress;
    double totalTime;

    ActiveFlight(int aircraftId_, int routeId_, double totalTime_);

    void updatePosition(double hoursPassed);
    Point getCurrentPosition(const Route& route) const;
};

} // namespace

#endif