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
template< class T >
bool knk::Vector< T >::isEmpty() const noexept{
  return false;
} 
template< class T >
knk::Vector< T >::Vector(): 
  data_(nullptr),
  size_(0),
  capacity_(0)
{}
template< class T >
knk::Vector< T >::~Vector() {
  delete [] data_;
}
#endif
