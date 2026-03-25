#ifndef PE_VECTOR_HPP
#define PE_VECTOR_HPP
#include <cstddef>
namespace knk
{
  template< class T >
  class Vector {
   public:
    ~Vector();
    Vector();
   private:
    T* data;
    size_t size, capacity;
  };
}
#endif
