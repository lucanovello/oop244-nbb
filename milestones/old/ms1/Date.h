/////////////////////////////////////////////////////////////////
// Final Project Milestone 1 
// Date Module
// File:    Date.h
// Version: 1.0
// Author:	Fardad Soleimanloo
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// Luca Novello     2024-07-1           Milestone 1
/////////////////////////////////////////////////////////////////
#ifndef SENECA_DATE_H__
#define SENECA_DATE_H__
#include <iostream>
namespace seneca {
    const int NO_ERROR = 0;
    const int CIN_FAILED = 1;
    const int YEAR_ERROR = 2;
    const int MON_ERROR = 3;
    const int DAY_ERROR = 4;
    const char DATE_ERROR[][16] = {
        "No Error",
        "cin Failed",
        "Year Error",
        "Month Error",
        "Day Error"
    };
    const int MIN_YEAR = 1500;

    class Date {
        int m_year;
        int m_mon;
        int m_day;
        int m_ErrorCode;
        int m_CUR_YEAR;

        int daysSince0001_1_1()const;
        bool validate();
        void errCode(int theErrorCode);
        int systemYear()const;
        bool bad()const;
        int mdays()const;
        void setToToday();

    public:
        Date();
        Date(int year, int mon, int day);
        int errCode()const;
        const char* dateStatus()const;
        int currentYear()const;
        std::istream& read(std::istream& is = std::cin);
        std::ostream& write(std::ostream& os = std::cout)const;

        bool operator==(const Date& other) const;
        bool operator!=(const Date& other) const;
        bool operator>=(const Date& other) const;
        bool operator<=(const Date& other) const;
        bool operator<(const Date& other) const;
        bool operator>(const Date& other) const;
        int operator-(const Date& other) const;
        operator bool() const;

        friend std::ostream& operator<<(std::ostream& os, const Date& RO);
        friend std::istream& operator>>(std::istream& is, Date& RO);
    };
}
#endif