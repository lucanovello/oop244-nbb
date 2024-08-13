/////////////////////////////////////////////////////////////////
// Final Project Milestone
// Book Module
// File:	Book.cpp
// Version:	1.0
// Author:	Luca Novello
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// 
/////////////////////////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Book.h"
#include "Utils.h"

namespace seneca {

    Book::Book() : m_authorName(nullptr) {}

    Book::Book(const Book& src) : Publication(src) {
        m_authorName = nullptr;
        *this = src;
    }

    Book& Book::operator=(const Book& src) {
        if (this != &src) {
            Publication::operator=(src);
            delete[] m_authorName;
            if (src.m_authorName) {
                m_authorName = new char[strlen(src.m_authorName) + 1];
                strcpy(m_authorName, src.m_authorName);
            }
            else {
                m_authorName = nullptr;
            }
        }
        return *this;
    }

    Book::~Book() {
        delete[] m_authorName;
    }

    char Book::type() const {
        return 'B';
    }

    std::ostream& Book::write(std::ostream& os) const {
        Publication::write(os);

        if (conIO(os)) {
            os << " ";
			os.fill(' ');
            os.setf(std::ios::left);
            os.width(SENECA_AUTHOR_WIDTH);
            if (m_authorName) {
                char buffer[SENECA_AUTHOR_WIDTH + 1];
                std::strncpy(buffer, m_authorName, SENECA_AUTHOR_WIDTH);
                buffer[SENECA_AUTHOR_WIDTH] = '\0';
                os.setf(std::ios::left);
				os.width(SENECA_AUTHOR_WIDTH);
                os  << buffer;
            }
            else {
                os << os.width(SENECA_AUTHOR_WIDTH) << "N/A";
            }
            os << " |";
        }
        else {
            os << '\t';
            if (m_authorName) {
                char buffer[SENECA_AUTHOR_WIDTH + 1];
                std::strncpy(buffer, m_authorName, SENECA_AUTHOR_WIDTH);
                buffer[SENECA_AUTHOR_WIDTH] = '\0';
                os << buffer;
            }
            else {
                os << "N/A";
            }
        }
        return os;
    }

    std::istream& Book::read(std::istream& istr) {
        char author[257] = { '\0' };
        Publication::read(istr);
        delete[] m_authorName;
        m_authorName = nullptr;

        if (conIO(istr)) {
            istr.ignore();
            std::cout << "Author: ";
            istr.get(author, 257);
        }
        else {
            istr.ignore(1, '\t');
            istr.get(author, 257);
        }

        if (istr) {
            m_authorName = new char[strlen(author) + 1];
            strcpy(m_authorName, author);
        }
        return istr;
    }

    void Book::set(int member_id) {
        Publication::set(member_id);
        resetDate();
    }

    Book::operator bool() const {
        return m_authorName && m_authorName[0] != '\0' && Publication::operator bool();
    }

}
