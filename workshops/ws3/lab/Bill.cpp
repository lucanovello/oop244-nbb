// Workshop 3: 
// Name: Luca Novello
// Student No: 038515003
// Class: OOP244_NBB
/////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Bill.h"
#include "Item.h"
using namespace std;
namespace seneca {

	double Bill::totalTax() const {
		double totalTaxes = 0.0f;
		if (isValid()) {
			for (int i = 0; i < m_noOfItems; i++)
			{
				totalTaxes += m_items[i].tax();
			}
		}
		else {
			cout << "Items are not valid";
		}
		return totalTaxes;
	}

	double Bill::totalPrice() const {
		double totalPrices = 0.0f;
		if (isValid()) {
			for (int i = 0; i < m_noOfItems; i++)
			{
				totalPrices += m_items[i].price();
			}
		}
		else {
			cout << "Items are not valid";
		}
		return totalPrices;
	}

	void Bill::Title() const {

		cout << "+--------------------------------------+" << endl;
		if (isValid()) {
			cout << "| ";
			cout.width(MAX_TITLE_LENGTH);
			cout.setf(ios::left);
			cout << m_title << " |" << endl;
		}
		else {
			cout << "| Invalid Bill                         |" << endl;
		}
		cout << "+----------------------+---------+-----+" << endl;
		cout << "| Item Name            | Price   + Tax |" << endl;
		cout << "+----------------------+---------+-----+" << endl;
	}

	void Bill::footer() const {
		cout << "+----------------------+---------+-----+" << endl;
		if (isValid()) {
			cout << "|                Total Tax: ";
			cout.width(10);
			cout.setf(ios::right);
			cout.precision(2);
			cout << totalTax() << " |" << endl;
			cout << "|              Total Price: ";
			cout.width(10);
			cout.setf(ios::right);
			cout.precision(2);
			cout << totalPrice() << " |" << endl;
			cout << "|          Total After Tax: ";
			cout.width(10);
			cout.setf(ios::right);
			cout.precision(2);
			cout << (totalTax() + totalPrice()) << " |" << endl;
			cout.unsetf(ios::right);
		}
		else {
			cout << "| Invalid Bill                         |" << endl;
		}
		cout << "+--------------------------------------+" << endl;
	}

	void Bill::setEmpty() {
		m_title[0] = '\0';
		m_items = nullptr;
	}

	bool Bill::isValid() const {
		if (m_title[0] != '\0' && m_items != nullptr && m_noOfItems >= 0) {
			for (int i = 0; i < m_noOfItems; i++)
			{
				if (!m_items[i].isValid()) {
					return false;
				}
			}
			return true;
		}
		return false;

	}

	void Bill::init(const char* title, int noOfItems) {
		if (title != nullptr && title[0] != '\0' && noOfItems > 0) {
			m_noOfItems = noOfItems;
			strncpy(m_title, title, MAX_TITLE_LENGTH);
			m_title[MAX_TITLE_LENGTH] = '\0';
			m_items = new Item[m_noOfItems];
			for (int i = 0; i < m_noOfItems; ++i) {
				m_items[i].setEmpty();
			}
			m_itemsAdded = 0;
		}
		else {
			setEmpty();
		}
	}

	bool Bill::add(const char* item_name, double price, bool taxed) {
		if (m_itemsAdded < m_noOfItems) {
            m_items[m_itemsAdded].set(item_name, price, taxed);
            m_itemsAdded++;
            return true;
		}
		return false;
	}

	void Bill::display() const {
		Title();
		for (int i = 0; i < m_noOfItems; i++)
		{
			m_items[i].display();
		}
		footer();
	}

	void Bill::deallocate() {
		delete[] m_items;
		m_items = nullptr;
	}




}