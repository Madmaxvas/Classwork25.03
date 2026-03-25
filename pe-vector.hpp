#ifndef PE_VECTOR_HPP
#define PE_VECTOR_HPP
namespace knk
{
  template< class T >
  struct Vector {
    T* data;
    size_t size, capacity;
  };
}
#endif
