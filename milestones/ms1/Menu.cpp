/////////////////////////////////////////////////////////////////
// Final Project Milestone 1 
// Menu Module
// File:	Menu.cpp
// Version: 1.0
// Author:	Luca Novello
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// 
/////////////////////////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Menu.h"

namespace seneca {
	MenuItem::MenuItem(const char* content) : m_content(nullptr) {
		if (content && content[0] != '\0') {
			m_content = new char[strlen(content) + 1];
			strcpy(m_content, content);
		}
	}

	MenuItem::~MenuItem() {
		delete[] m_content;
	}

	std::ostream& MenuItem::display(std::ostream& os) const {
		if (m_content) {
			os << m_content;
		}
		return os;
	}

	MenuItem::operator bool() const {
		return m_content != nullptr;
	}

	MenuItem::operator const char* () const {
		return m_content;
	}

	Menu::Menu(const char* title) : m_title(title), m_numItems(0) {
		for (unsigned int i = 0; i < MAX_MENU_ITEMS; ++i) {
			m_items[i] = nullptr;
		}
	}

	Menu::~Menu() {
		for (unsigned int i = 0; i < m_numItems; ++i) {
			delete m_items[i];
		}
	}

	void Menu::displayTitle(std::ostream& os) const {
		if (m_title) {
			os << m_title << ":\n";
		}
	}

	std::ostream& Menu::display(std::ostream& os) const {
		if (m_title) {
			displayTitle(os);
			for (unsigned int i = 0; i < m_numItems; ++i) {
				os.width(2);
				os << (i + 1) << "- " << m_items[i]->m_content << '\n';
			}
			os << " 0- Exit\n > ";
		}
		return os;
	}

	unsigned int Menu::run() const {
		unsigned int selection;
		bool valid = false;
		display(std::cout);
		do {
			std::cin >> selection;
			if (std::cin.fail() || selection > m_numItems) {
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				std::cout << "Invalid Selection, try again: ";
			}
			else {
				valid = true;
			}
		} while (!valid);
		return selection;
	}

	Menu& Menu::operator<<(const char* menuItemContent) {
		if (m_numItems < MAX_MENU_ITEMS) {
			m_items[m_numItems++] = new MenuItem(menuItemContent);
		}
		return *this;
	}

	Menu::operator unsigned int() const {
		return m_numItems;
	}

	Menu::operator int() const {
		return m_numItems;
	}

	Menu::operator bool() const {
		return m_numItems > 0;
	}

	const char* Menu::operator[](unsigned int index) const {
		return *m_items[index % m_numItems];
	}

	std::ostream& operator<<(std::ostream& os, const Menu& menu) {
		return menu.display(os);
	}
}

