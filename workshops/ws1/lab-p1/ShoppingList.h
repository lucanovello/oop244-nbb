#ifndef SHOPPINGLIST_H 
#define SHOPPINGLIST_H

#include "ShoppingRec.h"
namespace seneca {

	const int MAX_NO_OF_RECS = 15;


	bool loadList();
	void displayList();
	void removeBoughtItems();
	void removeItem(int index);
	bool saveList();
	void clearList();
	void toggleBought();
	void addItemToList();
	void removeItemfromList();
	bool listIsEmpty();
}
#endif