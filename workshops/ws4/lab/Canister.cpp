#define _CRT_SECURE_NO_WARNINGS
#include <istream>
#include <iomanip>
#include <cstring>
#include "Canister.h"
using namespace std;
namespace seneca {

	void Canister::setToDefault() {
		m_contentName = nullptr;
		m_height = 13.0;
		m_diameter = 10.0;
		m_contentVolume = 0.0;
		m_usable = true;
	}

	bool Canister::isEmpty() const {
		return m_contentVolume < MIN_QUANTITY;
	}

	bool Canister::hasSameContent(const Canister& C) const {
		return m_contentName != nullptr && C.m_contentName != nullptr && strcmp(m_contentName, C.m_contentName) == 0;
	}

	void Canister::setName(const char* Cstr) {
		if (m_usable && Cstr != nullptr) {
			delete[] m_contentName;
			m_contentName = new char[strlen(Cstr) + 1];
			strcpy(m_contentName, Cstr);
		}
	}

	Canister::Canister() {
		setToDefault();
	}

	Canister::Canister(const char* contentName) {
		setToDefault();
		setName(contentName);
	}

	Canister::Canister(double height, double diameter, const char* contentName) {
		setToDefault();
		if (height >= 10.0 && height <= 40.0 && diameter >= 10.0 && diameter <= 30.0) {
			m_height = height;
			m_diameter = diameter;
			setName(contentName);
		}
		else {
			m_usable = false;
		}
	}

	Canister::~Canister() {
		delete[] m_contentName;
	}

	Canister& Canister::setContent(const char* contentName) {
		if (contentName == nullptr) {
			m_usable = false;
		}
		else if (isEmpty()) {
			setName(contentName);
		}
		else if (!hasSameContent(*this)) {
			m_usable = false;
		}
		return *this;
	}

	Canister& Canister::pour(double quantity) {
		if (m_usable && quantity > 0 && (m_contentVolume + quantity) <= capacity()) {
			m_contentVolume += quantity;
		}
		else {
			m_usable = false;
		}
		return *this;
	}

	Canister& Canister::pour(Canister& C) {
		if (!isEmpty() && !hasSameContent(C)) {
			m_usable = false;
		}
		else if (m_usable && C.m_usable) {
			setContent(C.m_contentName);
			double availableSpace = capacity() - m_contentVolume;
			if (C.m_contentVolume > availableSpace) {
				C.m_contentVolume -= availableSpace;
				m_contentVolume = capacity();
			}
			else {
				m_contentVolume += C.m_contentVolume;
				C.m_contentVolume = 0.0;
			}
		}
		return *this;
	}

	double Canister::volume() const {
		return m_contentVolume;
	}

	std::ostream& Canister::display()const {
		std::cout.width(7);
		std::cout.precision(1);
		std::cout << std::fixed << capacity() << "cc (" << m_height << "x" << m_diameter << ") Canister";

		if (!m_usable) {
			std::cout << " of Unusable content, discard!";
		}
		else if (m_contentName != nullptr) {
			std::cout << " of ";
			std::cout.width(7);
			std::cout.precision(1);
			std::cout << std::fixed << volume() << "cc   " << m_contentName;
		}
		return std::cout;
	}

	double Canister::capacity() const {
		return PI * (m_height - 0.267) * (m_diameter / 2) * (m_diameter / 2);
	}

	void Canister::clear() {
		delete[] m_contentName;
		m_contentName = nullptr;
		m_contentVolume = 0.0;
		m_usable = true;
	}
}