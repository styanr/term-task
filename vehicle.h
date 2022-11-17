#ifndef VEHICLE_H
#define VEHICLE_H
#include <string>

enum type_of_engine {Petrol, Diesel, Electric};


class Vehicle
{
public:
    Vehicle();
private:
    std::string brand;
    type_of_engine engine_type;
    unsigned axles_count; //кількість осей
};

#endif // VEHICLE_H
