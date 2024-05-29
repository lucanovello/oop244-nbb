// Workshop 3: 
// Name: Luca Novello
// Student No: 038515003
// Class: OOP244_NBB
/////////////////////////////////////////////
#ifndef SENECA_BILL_H_
#define SENECA_BILL_H_
#include "Item.h"
namespace seneca {
	const int MAX_TITLE_LENGTH = 36;

	class Bill {
		char m_title[MAX_TITLE_LENGTH + 1];
		Item* m_items;
		int m_noOfItems;
		int m_itemsAdded;
		double totalTax()const;
		double totalPrice()const;
		void Title()const;
		void footer()const;
		void setEmpty();
		bool isValid()const;
	public:
		void init(const char* title, int noOfItems);
		bool add(const char* item_name, double price, bool taxed);
		void display()const;
		void deallocate();
	};
}
#endif // !SENECA_TRANSCRIPT_H
