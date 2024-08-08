/////////////////////////////////////////////////////////////////
// Final Project Milestone
// Menu Module
// File:	Menu.h
// Version: 1.0
// Author:	Luca Novello
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// 
/////////////////////////////////////////////////////////////////
#ifndef SENECA_MENU_H__
#define SENECA_MENU_H__
#include <iostream>
namespace seneca {
    const size_t MAX_MENU_ITEMS = 20;

    class Menu;

    class MenuItem {
        char* m_content;
        MenuItem(const char* content = nullptr);
        MenuItem(const MenuItem&) = delete;
        MenuItem& operator=(const MenuItem&) = delete;
        ~MenuItem();
        std::ostream& display(std::ostream& os) const;
        operator bool() const;
        operator const char* () const;
        friend class Menu;
    };

    class Menu {
        MenuItem m_title;
        MenuItem* m_items[MAX_MENU_ITEMS];
        size_t m_numItems;
        void displayTitle(std::ostream& os) const;

    public:
        Menu(const char* title = nullptr);
        ~Menu();
        std::ostream& display(std::ostream& os) const;
        size_t run() const;
        friend std::ostream& operator<<(std::ostream& os, const Menu& menu);
        Menu& operator<<(const char* menuItemContent);
        friend int operator~(const Menu&);
        operator size_t() const;
        operator int() const;
        operator bool() const;
        const char* operator[](size_t index) const;
    };
    int operator~(const Menu&);
}
#endif