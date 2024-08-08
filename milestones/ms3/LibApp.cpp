/////////////////////////////////////////////////////////////////
// Final Project Milestone 
// LibApp Module
// File:	LibApp.cpp
// Version: 1.0
// Author:	Luca Novello
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// 
/////////////////////////////////////////////////////////////////
#include "LibApp.h"
namespace seneca {

	LibApp::LibApp() : m_changed(false),
		m_mainMenu("Seneca Library Application"),
		m_exitMenu("Changes have been made to the data, what would you like to do?") {

		m_mainMenu << "Add New Publication"
			<< "Remove Publication"
			<< "Checkout publication from library"
			<< "Return publication to library";
		m_exitMenu << "Save changes and exit"
			<< "Cancel and go back to the main menu";
		load();
	}

	bool LibApp::confirm(const char* message) {
		Menu confirmMenu(message);
		confirmMenu << "Yes";
		return confirmMenu.run() == 1;
	}

	void LibApp::load() {
		std::cout << "Loading Data" << std::endl;
	}

	void LibApp::save() {
		std::cout << "Saving Data" << std::endl;
	}

	void LibApp::search() {
		std::cout << "Searching for publication" << std::endl;
	}

	void LibApp::returnPub() {
		search();
		std::cout << "Returning publication" << std::endl;
		std::cout << "Publication returned" << std::endl;
		m_changed = true;
	}

	void LibApp::newPublication() {
		std::cout << "Adding new publication to library" << std::endl;
		if (confirm("Add this publication to library?")) {
			m_changed = true;
			std::cout << "Publication added" << std::endl;
		}
	}

	void LibApp::removePublication() {
		std::cout << "Removing publication from library" << std::endl;
		search();
		if (confirm("Remove this publication from the library?")) {
			m_changed = true;
			std::cout << "Publication removed" << std::endl;
		}
	}

	void LibApp::checkOutPub() {
		search();
		if (confirm("Check out publication?")) {
			m_changed = true;
			std::cout << "Publication checked out" << std::endl;
		}
	}

	void LibApp::run() {
		bool done = false;
		while (!done) {
			int selection = m_mainMenu.run();
			switch (selection) {
			case 1: newPublication(); break;
			case 2: removePublication(); break;
			case 3: checkOutPub(); break;
			case 4: returnPub(); break;
			case 0:
				if (m_changed) {
					int exitSelection = m_exitMenu.run();
					if (exitSelection == 1) {
						save();
						done = true;
					}
					else if (exitSelection == 0) {
						if (confirm("This will discard all the changes are you sure?")) {
							done = true;
						}
					}
				}
				else {
					done = true;
				}
				if (done) {
					std::cout << "\n-------------------------------------------" << std::endl;
					std::cout << "Thanks for using Seneca Library Application";
				}
				break;
			}
				std::cout << std::endl;
		}
	}

}
