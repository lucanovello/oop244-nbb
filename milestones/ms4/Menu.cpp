/////////////////////////////////////////////////////////////////
// Final Project Milestone 
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
    // MenuItem Class
    MenuItem::MenuItem(const char* content) {
        if (content) {
            m_content = new char[strlen(content) + 1];
            strcpy(m_content, content);
        }
        else {
            m_content = nullptr;
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

    // Menu Class
    Menu::Menu(const char* title) : m_title(title), m_numItems(0) {
        for (size_t i = 0; i < MAX_MENU_ITEMS; ++i) {
            m_items[i] = nullptr;
        }
    }

    Menu::~Menu() {
        for (size_t i = 0; i < m_numItems; ++i) {
            delete m_items[i];
        }
    }

    void Menu::displayTitle(std::ostream& os) const {
        if (m_title) {
            m_title.display(os);
			os << std::endl;
        }
    }

    std::ostream& Menu::display(std::ostream& os) const {
        if (m_numItems > 0) {
            displayTitle(os);
            for (size_t i = 0; i < m_numItems; ++i) {
                os << " " << (i + 1) << "- " << m_items[i]->m_content << std::endl;
            }
            os << " 0- Exit\n> ";
        }
        return os;
    }

    size_t Menu::run() const {
        display(std::cout);
        size_t selection;
        bool valid = false;
        while (!valid) {
            std::cin >> selection;
            if (std::cin.fail() || selection > m_numItems) {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                std::cout << "Invalid Selection, try again: ";
            }
            else {
                valid = true;
            }
        }
        return selection;
    }

    Menu& Menu::operator<<(const char* menuItemContent) {
        if (m_numItems < MAX_MENU_ITEMS) {
            m_items[m_numItems++] = new MenuItem(menuItemContent);
        }
        return *this;
    }
    std::ostream& operator<<(std::ostream& os, const Menu& menu) {
        menu.displayTitle(os);
        return os;
    }

    Menu::operator size_t() const {
        return m_numItems;
    }

    Menu::operator int() const {
        return static_cast<int>(m_numItems);
    }

    Menu::operator bool() const {
        return m_numItems > 0;
    }

    const char* Menu::operator[](size_t index) const {
        return *m_items[index % m_numItems];
    }


    int operator~(const Menu& menu) {
        return menu.run();
    }
}

