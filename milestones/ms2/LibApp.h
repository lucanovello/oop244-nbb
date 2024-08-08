/////////////////////////////////////////////////////////////////
// Final Project Milestone 
// LibApp Module
// File:	LibApp.h
// Version: 1.0
// Author:	Luca Novello
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// 
/////////////////////////////////////////////////////////////////
#ifndef SENECA_LIBAPP_H
#define SENECA_LIBAPP_H
#include "Menu.h"
namespace seneca {
   class LibApp {
       bool m_changed;
       Menu m_mainMenu{ "Seneca Libray Application"};
       Menu m_exitMenu;
   private:
       bool confirm(const char* message);
       void load();
       void save();
       void search();
       void returnPub();
       void newPublication();
       void removePublication();
       void checkOutPub();
   public:
       LibApp();
       void run();
   };
}
#endif // !SENECA_LIBAPP_H



