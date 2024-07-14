#define _CRT_SECURE_NO_WARNINGS
#include "Truck.h"
#include <iomanip>

namespace seneca {
    Truck::Truck(const char* plate, int yearBuilt, double cap, const char* addr)
        : MotorVehicle(plate, yearBuilt), capacity(cap), cargoLoad(0) {
        moveTo(addr);
    }

    bool Truck::addCargo(double cargo) {
        if (cargoLoad + cargo <= capacity) {
            cargoLoad += cargo;
            return true;
        }
        return false;
    }

    bool Truck::unloadCargo() {
        if (cargoLoad > 0) {
            cargoLoad = 0;
            return true;
        }
        return false;
    }

    std::ostream& Truck::write(std::ostream& os) const {
        MotorVehicle::write(os);
        os << " | " << cargoLoad << "/" << capacity;
        return os;
    }

    std::istream& Truck::read(std::istream& in) {
        MotorVehicle::read(in);
        std::cout << "Capacity: ";
        in >> capacity;
        std::cout << "Cargo: ";
        in >> cargoLoad;
        return in;
    }

    std::ostream& operator<<(std::ostream& os, const Truck& truck) {
        return truck.write(os);
    }

    std::istream& operator>>(std::istream& in, Truck& truck) {
        return truck.read(in);
    }
}
