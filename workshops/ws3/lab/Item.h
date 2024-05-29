// Workshop 3: 
// Name: Luca Novello
// Student No: 038515003
// Class: OOP244_NBB
/////////////////////////////////////////////
#ifndef SENECA_ITEM_H_
#define SENECA_ITEM_H_
namespace seneca {
	const int MAX_ITEMNAME_LENGTH = 20;
	const double TAXRATE = 0.13;

	class Item {
		char m_itemName[MAX_ITEMNAME_LENGTH + 1];  // holds the item name up to 20 chars
		double m_price;
		bool m_taxed;
		void setName(const char* name);
	public:
		void setEmpty();
		void set(const char* name, double price, bool taxed);
		void display()const;
		bool isValid()const;
		double price()const;
		double tax()const;
	};
}

#endif // !SENECA_SUBJECT_H
