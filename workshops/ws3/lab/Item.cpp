#include <iostream>
#include <cstring>
#include "Item.h"
using namespace std;
namespace seneca {

	void Item::setName(const char* name) {
		if (name != nullptr && name[0] != '\0') {
			strncpy(m_itemName, name, 20);
			m_itemName[20] = '\0';
		}
		else {
			m_itemName[0] = '\0';
		}
	}

	void Item::setEmpty() {
		setName('\0');
		m_price = 0.0;
		m_taxed = false;
	}

	void Item::set(const char* name, double price, bool taxed) {
		if (name != nullptr && name[0] != '\0' && price > 0) {
			setName(name);
			m_price = price;
			m_taxed = taxed;
		}
		else {
			setEmpty();
		}
	}

	void Item::display() const {
		if (isValid()) {
			cout << "| ";
			cout.width(20);
			cout.setf(ios::left);
			cout.fill('.');
			cout << m_itemName;
			cout.width(7);
			cout.setf(ios::fixed);
			cout.precision(2);
			cout.fill(' ');
			cout << " | " << m_price;
			cout << " | " << (m_taxed ? "Yes" : "No") << " |" << endl;
		}
		else {
			cout << "| xxxxxxxxxxxxxxxxxxxx | xxxxxxx | xxx |" << endl;
		}
	}

	bool Item::isValid() const {
		return m_itemName[0] != '\0' && m_price > 0.0;
	}

	double Item::price() const {
		return m_price;
	}

	double Item::tax() const {
		return m_taxed ? m_price * m_taxRate : 0.0;
	}
}
