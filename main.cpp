#include <iostream>
#include <cstring>
#include "pe-vector.hpp"
using knk::Vector;

bool testConstructAndDestruct(const char** pname) {
  *pname = __func__;
  knk::Vector< int > v;
  return true;
}

bool testDefaultVectorIsEmpty(const char** pname) {
  *pname = __func__;
  Vector< int > v;
  return v.isEmpty();
}

bool testSizeOfEmptyVector(const char** pname) {
  *pname = __func__;
  Vector< int > v;
  return !v.getSize();
}

bool testSizeOfNonEmptyVector(const char** pname) {
  *pname = __func__;
  constexpr size_t size = 2;
  Vector< int > v(size, 5);
  return v.getSize() == size;
}

bool testElementCheckedAccess(const char** pname) {
  *pname = __func__;
  Vector< int > v;
  v.pushBack(2);
  try {
    int& r = v.at(0);
    return r == 2;
  } catch (...) {
    return false;
  }
}

bool testElementCheckedConstAccess(const char** pname) {
  *pname = __func__;
  Vector< int > v;
  v.pushBack(2);
  const Vector< int >& rv = v;
  try {
    const int& r = rv.at(0);
    return r == 2;
  } catch (...) {
    return false;
  }
}

bool testElementCheckedOutOfBoundAccess(const char** pname) {
  *pname = __func__;
  Vector< int > v;
  try {
    v.at(0);
    return false;
  } catch (const std::out_of_range& e) {
    const char* text = e.what();
    return !std::strcmp("id out of bound", text);
  } catch (...) {
    return false;
  }
}

bool testElementCheckedOutOfBoundConstAccess(const char** pname) {
  *pname = __func__;
  const Vector< int > v;
  try {
    v.at(0);
    return false;
  } catch (const std::out_of_range& e) {
    const char* text = e.what();
    return !std::strcmp("id out of bound", text);
  } catch (...) {
    return false;
  }
}

bool testCopyConstructor(const char** pname) {
  *pname = __func__;
  Vector< int > v{1, 2};
  Vector< int > yav = v;
  if (v.isEmpty() || yav.isEmpty()) {
    throw std::logic_error("Vectors expected to be non-empty");
  }
  bool isEqual = yav.getSize() == v.getSize();
  for (size_t i = 0; isEqual && i < v.getSize(); ++i) {
    try {
      isEqual = v.at(i) == yav.at(i);
    } catch (...) {
      return false;
    }
  }
  return isEqual;
}

bool testMoveConstructor(const char** pname) {
  *pname = __func__;
  Vector< int > v{1, 2, 3};
  size_t originalSize = v.getSize();
  Vector< int > moved = std::move(v);
  return moved.getSize() == originalSize && moved[0] == 1 &&
         moved[1] == 2 && moved[2] == 3;
}

bool testCopyAssignment(const char** pname) {
  *pname = __func__;
  Vector< int > v{1, 2};
  Vector< int > yav;
  yav = v;
  return yav.getSize() == v.getSize() && yav[0] == 1 && yav[1] == 2;
}

bool testMoveAssignment(const char** pname) {
  *pname = __func__;
  Vector< int > v{1, 2, 3};
  Vector< int > yav;
  yav = std::move(v);
  return yav.getSize() == 3 && yav[0] == 1 && yav[1] == 2 && yav[2] == 3;
}

bool testSwap(const char** pname) {
  *pname = __func__;
  Vector< int > a{1, 2};
  Vector< int > b{3, 4, 5};
  a.swap(b);
  return a.getSize() == 3 && a[2] == 5 && b.getSize() == 2 && b[1] == 2;
}

bool testInsertSingle(const char** pname) {
  *pname = __func__;
  Vector< int > v{1, 3};
  v.insert(1, 2);
  return v.getSize() == 3 && v[0] == 1 && v[1] == 2 && v[2] == 3;
}

bool testInsertRange(const char** pname) {
  *pname = __func__;
  Vector< int > v{1, 5};
  Vector< int > src{2, 3, 4};
  v.insert(1, src, 0, src.getSize());
  return v.getSize() == 5 && v[1] == 2 && v[3] == 4;
}

bool testEraseSingle(const char** pname) {
  *pname = __func__;
  Vector< int > v{1, 2, 3};
  v.erase(1);
  return v.getSize() == 2 && v[0] == 1 && v[1] == 3;
}

bool testEraseRange(const char** pname) {
  *pname = __func__;
  Vector< int > v{1, 2, 3, 4, 5};
  v.erase(1, 4);
  return v.getSize() == 2 && v[0] == 1 && v[1] == 5;
}

bool testPushBack(const char** pname) {
  *pname = __func__;
  Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  return v.getSize() == 2 && v[0] == 1 && v[1] == 2;
}

bool testPushBackRepeat(const char** pname) {
  *pname = __func__;
  Vector< int > v{1};
  v.pushBackRepeat(2, 3);
  return v.getSize() == 4 && v[1] == 2 && v[3] == 2;
}

bool testPopBack(const char** pname) {
  *pname = __func__;
  Vector< int > v{1, 2, 3};
  v.popBack();
  return v.getSize() == 2 && v[1] == 2;
}

bool testPushFront(const char** pname) {
  *pname = __func__;
  Vector< int > v{2, 3};
  v.pushFront(1);
  return v.getSize() == 3 && v[0] == 1 && v[2] == 3;
}

bool testGetCapacity(const char** pname) {
  *pname = __func__;
  Vector< int > v;
  size_t cap0 = v.getCapacity();
  v.pushBack(1);
  size_t cap1 = v.getCapacity();
  for (int i = 0; i < 100; ++i) {
    v.pushBack(i);
  }
  return cap1 >= 1 && v.getCapacity() >= v.getSize();
}

bool testSubscriptOperator(const char** pname) {
  *pname = __func__;
  Vector< int > v{1, 2};
  v[0] = 10;
  return v[0] == 10 && v[1] == 2;
}

bool testConstSubscriptOperator(const char** pname) {
  *pname = __func__;
  const Vector< int > v{5};
  return v[0] == 5;
}

bool testIteratorTraversal(const char** pname) {
  *pname = __func__;
  Vector< int > v{1, 2, 3};
  int sum = 0;
  for (auto it = v.begin(); it != v.end(); ++it) {
    sum += *it;
  }
  return sum == 6;
}

bool testConstIteratorTraversal(const char** pname) {
  *pname = __func__;
  const Vector< int > v{1, 2, 3};
  int sum = 0;
  for (auto it = v.cbegin(); it != v.cend(); ++it) {
    sum += *it;
  }
  return sum == 6;
}

bool testIteratorInsert(const char** pname) {
  *pname = __func__;
  Vector< int > v{1, 3};
  int val = 2;
  v.insert(v.begin() + 1, &val, &val + 1);
  return v.getSize() == 3 && v[1] == 2;
}

int main() {
  using test_t = bool (*)(const char**);
  using case_t = std::pair< test_t, const char* >;
  case_t tests[] = {
      {testConstructAndDestruct, "Vector must be default constructable"},
      {testDefaultVectorIsEmpty, "Default constructed vector must be empty"},
      {testSizeOfEmptyVector, "Size of empty vector must be zero"},
      {testSizeOfNonEmptyVector, "Size of non-empty vector must be greater than zero"},
      {testElementCheckedAccess, "Inbound access must return lvalue reference to indexed value"},
      {testElementCheckedOutOfBoundAccess,
       "Out of bound access must generate exception with specific text"},
      {testElementCheckedConstAccess, "Same as inbound access but const"},
      {testElementCheckedOutOfBoundConstAccess, "Same as out of bound but const"},
      {testCopyConstructor, "Copied vector must be equal to original"},
      {testMoveConstructor, "Move constructor must transfer resources"},
      {testCopyAssignment, "Copy assignment must duplicate content"},
      {testMoveAssignment, "Move assignment must transfer resources"},
      {testSwap, "Swap must exchange contents"},
      {testInsertSingle, "Insert single element at position"},
      {testInsertRange, "Insert range of elements"},
      {testEraseSingle, "Erase single element by index"},
      {testEraseRange, "Erase range of elements"},
      {testPushBack, "PushBack adds element to end"},
      {testPushBackRepeat, "PushBackRepeat adds multiple copies"},
      {testPopBack, "PopBack removes last element"},
      {testPushFront, "PushFront adds element to beginning"},
      {testGetCapacity, "Capacity grows appropriately"},
      {testSubscriptOperator, "Subscript operator provides mutable access"},
      {testConstSubscriptOperator, "Const subscript provides read-only access"},
      {testIteratorTraversal, "Iterators traverse elements correctly"},
      {testConstIteratorTraversal, "Const iterators traverse elements correctly"},
      {testIteratorInsert, "Iterator-based insert works"}};

  constexpr size_t count = sizeof(tests) / sizeof(case_t);
  size_t failed = 0;
  for (size_t i = 0; i < count; ++i) {
    const char* testName = nullptr;
    bool r = false;
    try {
      r = tests[i].first(&testName);
    } catch (const std::logic_error& e) {
      std::cout << "[NOT RUN] " << testName << "\n";
      std::cout << "\t"
                << "Reason: " << e.what() << "\n";
      ++failed;
      continue;
    }
    if (!r) {
      ++failed;
      std::cout << "[FAIL] " << testName << "\n";
      std::cout << "\t" << tests[i].second << "\n";
    }
  }
  std::cout << "Summary:\n\t" << (count - failed) << " passed\n";
  std::cout << "\t" << count << " total\n";
  return failed == 0 ? 0 : 1;
}
