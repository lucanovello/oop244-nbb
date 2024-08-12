#define _CRT_SECURE_NO_WARNINGS
#include "Book.h"
#include "Lib.h"
#include "Publication.h"


namespace seneca {
    Book::Book() : m_authorName(nullptr) {}

    Book::~Book() {
        delete[] m_authorName;
    }

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

    char Book::type() const {
        return 'B';
    }

    std::ostream& Book::write(std::ostream& os) const {
        Publication::write(os);
        if (conIO(os)) {
            os << " ";
            if (m_authorName) {
                os.width(SENECA_AUTHOR_WIDTH);
                os.setf(std::ios::left);
                os << m_authorName;
                os.unsetf(std::ios::left);
            }
            else {
                os << "N/A";
            }
            os << " |";
        }
        else {
            os << '\t' << (m_authorName ? m_authorName : "N/A");
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