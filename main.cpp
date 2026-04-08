#include "pe-vector.hpp"
#include <iostream>

bool testConstAndDest(const char ** pname)
{
  *pname = __func__;
  knk::Vector< int > v;
  return true;
}

bool testDefVecIsEmpty(onst char ** pname)
{
  *pname = __func__;
  Vector< int > v;
  return v.isEmpty();
}

bool testSizeOfEmptyVec(const char** pname){
 *pname = __func__;
 Vector< int > v;
 return !v.getSize();
}

bool testSizeOfNonEmptyVec(const char** pname){
 *pname = __func__;
 constexpr size_t size = 2;
 Vector< int > v(2ull, 5);
 return v.getSize() == 2ull;
}


int main()
{
  using test_t = bool(*)(const char **);
  using case_t = std::pair< test_t, const char *>;
  case_t tests[]{
    { testConstAndDest },
    { testDefVecIsEmpty },
    { testSizeOfEmptyVec },
    { testSizeOfNonEmptyVec }
    
  };
  constexpr size_t count = sizeof(tests) / sizeof(case_t);
  size_t failed = 0;
  for (size_t i = 0; i < count; ++i){
    bool r = tests[i]()
    const chat ** testName = nullptr;
    bool r = tests[i](&testName);
    if (!r) {
      ++failed
      std::cout << "Failed: " << testName << "\n";
      std::cout << "\t" << tests[i].second << "\n";
    }
  }
  std::cout << "Summary:\n\t " << (count - failed) << "passed\n";
  std::cout << "\t" << count << "total\n"
}
