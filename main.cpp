#include "pe-vector.hpp"
#include <iostream>

bool testConstAndDest(const char ** pname) {
  *pname = __func__;
  knk::Vector<int> v;
  return true;
}

bool testDefVecIsEmpty(const char ** pname) {
  *pname = __func__;
  knk::Vector<int> v;
  return v.isEmpty();
}

bool testSizeOfEmptyVec(const char** pname) {
  *pname = __func__;
  knk::Vector<int> v;
  return v.getSize() == 0;
}

bool testPushBack(const char** pname) {
  *pname = __func__;
  knk::Vector<int> v;
  v.pushBack(42);
  return v.getSize() == 1 && v.getCapacity() >= 1;
}

bool testPopBack(const char** pname) {
  *pname = __func__;
  knk::Vector<int> v(1, 10);
  v.popBack();
  return v.getSize() == 0;
}

int main() {
  using test_t = bool(*)(const char **);
  using case_t = std::pair<test_t, const char *>;
  
  case_t tests[]{
    { testConstAndDest, "Constructor/Destructor" },
    { testDefVecIsEmpty, "Default IsEmpty" },
    { testSizeOfEmptyVec, "Empty Size check" },
    { testPushBack, "PushBack check" },
    { testPopBack, "PopBack check" }
  };
  
  constexpr size_t count = sizeof(tests) / sizeof(case_t);
  size_t failed = 0;

  for (size_t i = 0; i < count; ++i) {
    const char * testName = nullptr;
    bool r = tests[i].first(&testName);
    if (!r) {
      ++failed;
      std::cout << "Failed: " << (testName ? testName : "unknown") << "\n";
      std::cout << "\t" << tests[i].second << "\n";
    }
  }

  std::cout << "Summary:\n\t " << (count - failed) << " passed\n";
  std::cout << "\t " << count << " total\n";
  
  return failed == 0 ? 0 : 1;
}
