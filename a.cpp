#include "a.h"
#include <QDebug>

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>


// Compute Levenshtein Distance
// Martin Ettl, 2012-10-05
// http://rosettacode.org/wiki/Levenshtein_distance#C.2B.2B

size_t uiLevenshteinDistance(const std::string &s1, const std::string &s2)
{
  const size_t m(s1.size());
  const size_t n(s2.size());

  if( m==0 ) return n;
  if( n==0 ) return m;

  size_t *costs = new size_t[n + 1];

  for( size_t k=0; k<=n; k++ ) costs[k] = k;

  size_t i = 0;
  for ( std::string::const_iterator it1 = s1.begin(); it1 != s1.end(); ++it1, ++i )
  {
    costs[0] = i+1;
    size_t corner = i;

    size_t j = 0;
    for ( std::string::const_iterator it2 = s2.begin(); it2 != s2.end(); ++it2, ++j )
    {
      size_t upper = costs[j+1];
      if( *it1 == *it2 )
      {
          costs[j+1] = corner;
      }
      else
      {
        size_t t(upper<corner?upper:corner);
        costs[j+1] = (costs[j]<t?costs[j]:t)+1;
      }

      corner = upper;
    }
  }

  size_t result = costs[n];
  delete [] costs;

  return result;
}



// ************************
// http://www.cyberforum.ru/cpp-beginners/thread587021.html

typedef int cost_type;

cost_type insertion_cost(std::string::value_type ch) {
    Q_UNUSED(ch)
   return 1;
}

cost_type removal_cost(std::string::value_type ch) {
    Q_UNUSED(ch)
   return 1;
}

cost_type update_cost(std::string::value_type lhs, std::string::value_type rhs) {
   return lhs == rhs ? 0 : 1;
}

//Вагнер-Фишер
cost_type edit_distance(std::string const& from, std::string const& to) {
   std::vector< std::vector<cost_type> > costTable(
               from.length() + 1,
               std::vector<cost_type>(to.length() + 1));

   costTable[0][0] = 0;

   for (std::size_t j = 0; j != to.length(); ++j) {
      costTable[0][j + 1] = costTable[0][j] + insertion_cost(to[j]);
   }

   for (std::size_t i = 0; i != from.length(); ++i) {
      costTable[i + 1][0] = costTable[i][0] + removal_cost(from[i]);

      for (std::size_t j = 0; j != to.length(); ++j) {
         costTable[i + 1][j + 1] = std::min(std::min(
            costTable[i + 1][j] + insertion_cost(to[j]),
            costTable[i][j + 1] + removal_cost(from[i])),
            costTable[i][j] + update_cost(from[i], to[j]));
      }
   }

   return costTable[from.length()][to.length()];
}


void A::lev1()
{
    std::string s0 = "leader";
    std::string s1 = "lider";
    QVERIFY(uiLevenshteinDistance(s0,s1) == 2);
    QBENCHMARK {
        uiLevenshteinDistance(s0,s1);
    };
}

void A::lev2()
{
    std::string s0 = "leader";
    std::string s1 = "lider";
    QVERIFY(edit_distance(s0,s1) == 2);
    QBENCHMARK {
        edit_distance(s0,s1);
    };
}

QTEST_MAIN(A)
