// Workshop 3: 
// Name: Luca Novello
// Student No: 038515003
// Class: OOP244_NBB
/////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Item.h"
using namespace std;
namespace seneca {

	void Item::setName(const char* name) {
		if (name != nullptr && name[0] != '\0') {
			strncpy(m_itemName, name, MAX_ITEMNAME_LENGTH);
			m_itemName[MAX_ITEMNAME_LENGTH] = '\0';
		}
		else {
			m_itemName[0] = '\0';
		}
	}

	void Item::setEmpty() {
		setName("\0");
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
			cout.width(MAX_ITEMNAME_LENGTH);
			cout.setf(ios::left);
			cout.fill('.');
			cout << m_itemName;
			cout.unsetf(ios::left);
			cout.fill(' ');
			cout << " | ";
			cout.width(7);
			cout.setf(ios::right);
			cout.setf(ios::fixed);
			cout.precision(2);
			cout << m_price;
			cout.unsetf(ios::right);
			cout << " | ";
			cout.setf(ios::left);
			cout.width(3);
			cout << (m_taxed ? "Yes" : "No");
			cout.unsetf(ios::left);
			cout << " |" << endl;
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
		return m_taxed ? m_price * TAXRATE : 0.0;
	}
}
