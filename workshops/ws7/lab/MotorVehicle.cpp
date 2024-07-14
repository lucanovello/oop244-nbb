#define _CRT_SECURE_NO_WARNINGS
#include "MotorVehicle.h"
#include <cstring>
#include <iomanip>

namespace seneca {
    MotorVehicle::MotorVehicle(const char* plate, int yearBuilt) : year(yearBuilt) {
        strncpy(licensePlate, plate, 8);
        licensePlate[8] = '\0';
        strncpy(address, "Factory", 63);
        address[63] = '\0';
    }

    void MotorVehicle::moveTo(const char* newAddress) {
        if (strcmp(address, newAddress) != 0) {
            std::cout << '|' << std::right << std::setw(8) << licensePlate << '|'
                << std::right << std::setw(20) << address << " ---> "
                << std::left << std::setw(20) << std::left << newAddress << std::endl;
            strncpy(address, newAddress, 63);
            address[63] = '\0';
        }
    }

    std::ostream& MotorVehicle::write(std::ostream& os) const {
        os << "| " << year << " | " << licensePlate << " | " << address;
        return os;
    }

    std::istream& MotorVehicle::read(std::istream& in) {
        char plate[9];
        char loc[64];
        std::cout << "Built year: ";
        in >> year;
        std::cout << "License plate: ";
        in >> plate;
        strncpy(licensePlate, plate, 8);
        licensePlate[8] = '\0';
        std::cout << "Current location: ";
        in.ignore();
        in.getline(loc, 64);
        strncpy(address, loc, 63);
        address[63] = '\0';
        return in;
    }

    std::ostream& operator<<(std::ostream& os, const MotorVehicle& vehicle) {
        return vehicle.write(os);
    }

    std::istream& operator>>(std::istream& in, MotorVehicle& vehicle) {
        return vehicle.read(in);
    }
}
