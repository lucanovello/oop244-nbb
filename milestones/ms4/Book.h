/////////////////////////////////////////////////////////////////
// Final Project Milestone 
// Book Module
// File:	Book.h
// Version: 1.0
// Author:	Luca Novello
/////////////////////////////////////////////////////////////////
#ifndef SENECA_BOOK_H
#define SENECA_BOOK_H
#include <cstring>
#include <iostream>
#include "Publication.h"

namespace seneca {
    class Book : public Publication {
        char* m_authorName;

    public:
        Book();
        ~Book();
        Book(const Book& src);
        Book& operator=(const Book& src);
        char type() const override;
        std::ostream& write(std::ostream& os) const override;
        std::istream& read(std::istream& istr) override;
        void set(int member_id) override;
        operator bool() const override;
    };
}
#endif // SENECA_BOOK_H
