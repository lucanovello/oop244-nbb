#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Account.h"

using namespace std;
namespace seneca {
    void Account::setEmpty() {
        m_number = -1;
        m_balance = 0.0;
    }
    // New account
    Account::Account() {
        m_number = 0;
        m_balance = 0.0;
    }
    Account::Account(int number, double balance) {
        setEmpty();
        if (number >= 10000 && number <= 99999
            && balance > 0) {
            m_number = number;
            m_balance = balance;
        }
    }
    std::ostream& Account::display() const {
        if (*this) {
            cout << " ";
            cout << m_number;
            cout << " | ";
            cout.width(12);
            cout.precision(2);
            cout.setf(ios::right);
            cout.setf(ios::fixed);
            cout << m_balance;
            cout.unsetf(ios::right);
            cout << " ";
        }
        else if (~*this) {
            cout << "  NEW  |         0.00 ";
        }
        else {
            cout << "  BAD  |    ACCOUNT   ";
        }
        return cout;
    }

    // Conversion operator to bool
    Account::operator bool() const {
        return m_number >= 10000 && m_number <= 99999 && m_balance >= 0;
    }

    // Conversion operator to int
    Account::operator int() const {
        return m_number;
    }

    // Conversion operator to double
    Account::operator double() const {
        return m_balance;
    }

    // Unary operator to check if account is new
    bool Account::operator ~() const {
        return m_number == 0;
    }

    // Assignment operator to set a new account to an integer
    Account& Account::operator=(int number) {
        if (m_number == 0) {
            if (number >= 10000 && number <= 99999) {
                m_number = number;
            }
            else {
                m_number = -1;
                m_balance = 0.0;
            }
        }
        return *this;
    }

    // Assignment operator to move account details
    Account& Account::operator=(Account& other) {
        if (m_number == 0 && other) {
            m_number = other.m_number;
            m_balance = other.m_balance;
            other.m_number = 0;
            other.m_balance = 0.0;
        }
        return *this;
    }

    // Arithmetic assignment operator +=
    Account& Account::operator+=(double value) {
        if (*this && value >= 0) {
            m_balance += value;
        }
        return *this;
    }

    // Arithmetic assignment operator -=
    Account& Account::operator-=(double value) {
        if (*this && value >= 0 && m_balance >= value) {
            m_balance -= value;
        }
        return *this;
    }

    // Shift operator <<
    Account& Account::operator<<(Account& other) {
        if (this != &other && *this && other) {
            m_balance += other.m_balance;
            other.m_balance = 0.0;
        }
        return *this;
    }

    // Shift operator >>
    Account& Account::operator>>(Account& other) {
        if (this != &other && *this && other) {
            other.m_balance += m_balance;
            m_balance = 0.0;
        }
        return *this;
    }

    // Binary helper operator +
    double operator+(const Account& lhs, const Account& rhs) {
        if (lhs && rhs) {
            return static_cast<double>(lhs) + static_cast<double>(rhs);
        }
        return 0.0;
    }

    // Binary helper operator +=
    double& operator+=(double& lhs, const Account& rhs) {
        if (rhs) {
            lhs += static_cast<double>(rhs);
        }
        return lhs;
    }
}