#ifndef SENECA_ACCOUNT_H_
#define SENECA_ACCOUNT_H_
#include <iostream>

namespace seneca {
   class Account {
      int m_number;
      double m_balance; 
      void setEmpty();
   public:
      Account();
      Account(int number, double balance);
      std::ostream& display()const;

      operator bool() const;
      operator int() const;
      operator double() const;
      bool operator ~() const;
      Account& operator=(int number);
      Account& operator=(Account& other);
      Account& operator+=(double value);
      Account& operator-=(double value);
      Account& operator<<(Account& other);
      Account& operator>>(Account& other);

      friend double operator+(const Account& lhs, const Account& rhs);
      friend double& operator+=(double& lhs, const Account& rhs);

   };
   
   
}
#endif // SENECA_ACCOUNT_H_