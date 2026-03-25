#include pe-vector.hpp
#include <iostream>
  
bool test 1()
{
  knk::Vector< int > v;
  return true;
}

int main()
{
  using test_t = bool(*)();
  test_t tests[] = {
    test1
  };
  constexpr size_t count = sizeof(tests) / sizeof(test_t);
  for (size_i = 0; i < count; ++i){
    bool r = tests[i]();
    if (r!) {
      std::cout << "Failed: " << i << "\n";
    }
  }
}
