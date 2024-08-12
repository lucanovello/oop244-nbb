/////////////////////////////////////////////////////////////////
// Final Project Milestone 
// Streamable Module
// File:	Streamable.h
// Version: 1.0
// Author:	Luca Novello
/////////////////////////////////////////////////////////////////
#ifndef SENECA_STREAMABLE_H
#define SENECA_STREAMABLE_H
#include <iostream>

namespace seneca {

    class Streamable {
    public:
        virtual std::ostream& write(std::ostream& os) const = 0;
        virtual std::istream& read(std::istream& istr) = 0;
        virtual bool conIO(std::ios& io) const = 0;
        virtual operator bool() const = 0;
        virtual ~Streamable() = default;
    };
	inline std::istream& operator>>(std::istream& istr, Streamable& s) {
		return s.read(istr);
	}
	inline std::ostream& operator<<(std::ostream& os, const Streamable& s) {
		if (s) {
			s.write(os);
		}
		return os;
	}
}
#endif // SENECA_STREAMABLE_H
