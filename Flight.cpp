#include "Flight.h"
#include <algorithm>

namespace FlightScheduler {

ActiveFlight::ActiveFlight(int aircraftId_, int routeId_, double totalTime_)
    : aircraftId(aircraftId_), routeId(routeId_),
      remainingTime(totalTime_), progress(0.0), totalTime(totalTime_) {}

void ActiveFlight::updatePosition(double hoursPassed) {
    double timeReduction = std::min(hoursPassed, remainingTime);
    remainingTime -= timeReduction;

    if (remainingTime <= 0.0001) {
        progress = 1.0;
        remainingTime = 0;
    } else {
        double timeFlown = totalTime - remainingTime;
        progress = timeFlown / totalTime;
    }
}

Point ActiveFlight::getCurrentPosition(const Route& route) const {
    return route.getPositionAtProgress(progress);
}

} // namespace