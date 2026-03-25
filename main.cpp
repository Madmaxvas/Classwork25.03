#include <iostream>
#include pe-vector.hpp
using knk::Vector;

bool testConstructAndDestruct(const char ** pname)
{
  *pname = __func__;
  knk::Vector< int > v;
  return true;
}
bool testDefaultVectorIsEmpty(const char ** pname)
{
  *pname = __func__;
  Vector< int > v;
  return v.isEmpty();
}


int main()
{
  using test_t = bool(*)(const char **);
  using case_t = std::pair< test_t , const char *>;
  test_t tests[] = {
    { testConstructAndDestruct, "Vector must be default constructable" },
    { testDefaultVectorIsEmpty, "Default constructed vector must be empty" }
  };
  constexpr size_t count = sizeof(tests) / sizeof(test_t);
  size_t failed = 0;
  for (size_i = 0; i < count; ++i){
    const char * testName = nullptr;
    bool r = tests[i].first(&testName);
    if (r!) {
      ++failed;
      std::cout << "Failed: " << testName << "\n";
      std::cout << "\t" << test[i].second << "\n";
    }
  }
  std::cout << "Summary: " << (count - failed) << " passed\n";
  std::cout << "\t" << count << " total\n";
}
