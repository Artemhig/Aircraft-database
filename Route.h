#ifndef ROUTE_H
#define ROUTE_H

#include <string>
#include <iostream>

namespace FlightScheduler {

struct Point {
    double x, y;
    Point(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
};

class Route {
private:
    int id;
    std::string name;
    Point start;
    Point end;

public:
    Route();
    Route(int id, const std::string& name, const Point& start, const Point& end);

    int getId() const;
    std::string getName() const;
    Point getStart() const;
    Point getEnd() const;

    double calculateDistance() const;
    double calculateFlightTime(double aircraftSpeed) const;
    Point getPositionAtProgress(double progress) const;

    void display() const;

    std::string toFileString() const;
    static Route fromFileString(const std::string& line);
};

} // namespace

#endif