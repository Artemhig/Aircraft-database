cmake_minimum_required(VERSION 3.10)
project(FlightScheduler)

set(CMAKE_CXX_STANDARD 17)

add_executable(scheduler
    main.cpp
    Aircraft.cpp
    Route.cpp
    Flight.cpp
    Database.cpp
)