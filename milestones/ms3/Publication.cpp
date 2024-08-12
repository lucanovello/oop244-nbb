#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Publication.h"
#include "Lib.h"
#include "Streamable.h"
#include "Date.h" 


namespace seneca {

    Publication::Publication()
        : m_title(nullptr), m_membership(0), m_libRef(-1), m_date() {
        m_shelfId[0] = '\0';
    }

    Publication::Publication(const Publication& src) : m_title(nullptr) {
        init(src);
    }

    Publication& Publication::operator=(const Publication& src) {
        if (this != &src) {
            delete[] m_title;
            init(src);
        }
        return *this;
    }

    Publication::~Publication() {
        delete[] m_title;
    }

    void Publication::set(int member_id) {
        m_membership = member_id;
    }

    void Publication::setRef(int value) {
        m_libRef = value;
    }

    void Publication::resetDate() {
        m_date = Date();  // Assuming Date class has a default constructor for the current date
    }

    char Publication::type() const {
        return 'P';
    }

    bool Publication::onLoan() const {
        return m_membership != 0;
    }

    Date Publication::checkoutDate() const {
        return m_date;
    }

    bool Publication::operator==(const char* title) const {
        return strstr(m_title, title) != nullptr;
    }

    Publication::operator const char* () const {
        return m_title;
    }

    int Publication::getRef() const {
        return m_libRef;
    }

    bool Publication::conIO(std::ios& io) const {
        return &io == &std::cin || &io == &std::cout;
    }

    std::ostream& Publication::write(std::ostream& os) const {
        if (conIO(os)) {
            os << "| " << m_shelfId << " | ";
            os.width(SENECA_TITLE_WIDTH);
            os.setf(std::ios::left);
            os.fill('.');
            os << m_title << " | ";
            if (onLoan()) {
                os << m_membership;
            }
            else {
                os << " N/A ";
            }
            os << " | " << m_date << " |";
        }
        else {
            os << type() << '\t' << m_libRef << '\t' << m_shelfId << '\t' << m_title
                << '\t' << m_membership << '\t' << m_date;
        }
        return os;
    }

    std::istream& Publication::read(std::istream& istr) {
        // Clear current state and prepare for new input
        delete[] m_title;
        m_title = nullptr;
        m_shelfId[0] = '\0';
        m_membership = 0;
        m_libRef = -1;
        m_date = Date(); // Reset to current date

        // Temporary variables for reading
        char shelfId[SENECA_SHELF_ID_LEN + 1] = { 0 };
        char title[256] = { 0 };
        int membership = 0;
        Date date;

        // Check if the input is from console
        if (conIO(istr)) {
            std::cout << "Shelf No: ";
            istr.getline(shelfId, SENECA_SHELF_ID_LEN + 1);

            // If the shelf ID is not exactly the expected length, set fail state
            if (strlen(shelfId) != SENECA_SHELF_ID_LEN) {
                istr.setstate(std::ios::failbit);
                return istr;
            }

            std::cout << "Title: ";
            istr.getline(title, 256);

            std::cout << "Date: ";
            istr >> date;

            // If date is in an invalid state, set fail state
            if (!date) {
                istr.setstate(std::ios::failbit);
                return istr;
            }

            // Only if everything is valid, proceed to assign values
            m_title = new char[strlen(title) + 1];
            strcpy(m_title, title);
            strcpy(m_shelfId, shelfId);
            m_date = date;
        }
        else {
            // Non-console input (from file)
            istr >> m_libRef;
            istr.ignore();
            istr.getline(shelfId, SENECA_SHELF_ID_LEN + 1, '\t');
            istr.getline(title, 256, '\t');
            istr >> membership;
            istr.ignore();
            istr >> date;

            // If date is in an invalid state, set fail state
            if (!date) {
                istr.setstate(std::ios::failbit);
                return istr;
            }

            // Assign values only if all are valid
            m_title = new char[strlen(title) + 1];
            strcpy(m_title, title);
            strcpy(m_shelfId, shelfId);
            m_membership = membership;
            m_date = date;
        }

        return istr;
    }



    Publication::operator bool() const {
        return m_title != nullptr && m_shelfId[0] != '\0';
    }

    void Publication::init(const Publication& src) {
        if (src.m_title != nullptr) {
            m_title = new char[std::strlen(src.m_title) + 1];
            std::strcpy(m_title, src.m_title);
        }
        else {
            m_title = nullptr;
        }
        std::strcpy(m_shelfId, src.m_shelfId);
        m_membership = src.m_membership;
        m_libRef = src.m_libRef;
        m_date = src.m_date;
    }
}