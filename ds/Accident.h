#pragma once
#include <string>

// We cast the integer from the CSV directly to these enums.
enum class Weather { Unspecified = -1, Fine = 1, Raining = 2, Snowing = 3, Fog = 4, Other = 5 };
enum class JunctionDetail { Unspecified = -1, NotAtJunction = 0, Roundabout = 1, Crossroads = 2, Other = 3 };
enum class Severity { Unspecified = -1, Fatal = 1, Serious = 2, Slight = 3 };

struct Accident {
    int collision_year;
    std::string date;
    std::string time;
    Weather weather_conditions;
    JunctionDetail junction_detail;
    Severity collision_severity;
    int number_of_vehicles;
    int number_of_casualties;
};