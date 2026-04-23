ifndef PE_VECTOR_HPP
#define PE_VECTOR_HPP
#include <cstddef>
#include <initializer_list>
namespace knk {
  template< class T >
  class Vector {
   public:
    ~Vector();
    Vector();
    Vector(size_t size, const T& value);
    explicit Vector(std::initializer_list< T > il);

    // Дописать тесты (!)
    Vector(const Vector< T >& rhs);
    Vector(Vector< T >&& rhs) noexcept;
    Vector< T >& operator=(const Vector< T >& rhs);
    Vector< T >& operator=(Vector< T >&& rhs) noexcept;
    void swap(Vector< T >& rhs) noexcept;

    // Классная работа (!)
    // Использовать copy-and-swap
    // - Реализовать
    // - Протестировать
    void insert(size_t id, const T& t);
    void insert(size_t id, const Vector< T >& rhs, size_t beg, size_t end);
    void erase(size_t id);
    void erase(size_t beg, size_t end);

    // Домашняя работа
    // Реализовать итераторы вектора (random acccess)
    // - const и не-const
    // - САМИ итераторы НЕ тестировать
    // Придумать ещё по 3 insert/erase (всего 6), но с итераторами
    struct VectorIterator {};
    template< class FwdIterator >
    void insert(VectorIterator pos, FwdIterator begin, FwdIterator end);

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;

    // Реализовать + тестирование
    size_t getCapcity() const noexcept;
    void pushBack(const T&);
    void pushBackRepeat(const T&, size_t k);
    void popBack();
    void pushFront(const T&);

    // дописать тесты (!)
    T& operator[](size_t id) noexcept;
    const T& operator[](size_t id) const noexcept;
    T& at(size_t id);
    const T& at(size_t id) const;

   private:
    T* data_;
    size_t size_, capacity_;

    explicit Vector(size_t size);
  };
  template< class T >
  bool operator==(const Vector< T >& lhs, const Vector< T >& rhs);
}
template< class T >
knk::Vector< T >::Vector(std::initializer_list< T > il):
  Vector(il.size())
{
  size_t j = 0;
  for (auto i = il.begin(); i != il.end(); ++i) {
    data_[j++] = *i;
  }
}
template< class T >
void knk::Vector< T >::pushBackRepeat(const T& t, size_t k)
{
  Vector< T > cpy(*this);
  for (size_t i = 0; i < k; ++i) {
    cpy.pushBack(t);
  }
  swap(cpy);
}
template< class T >
void knk::Vector< T >::pushBack(const T& t)
{
  Vector< T > v(getSize() + 1);
  for (size_t i = 0; i < getSize(); ++i) {
    v[i] = (*this)[i];
  }
  v[getSize()] = t;
  swap(v);
}
template< class T >
void knk::Vector< T >::pushFront(const T& t)
{
  Vector< T > v(getSize() + 1);
  v[0] = t;
  for (size_t i = 1; i < v.getSize(); ++i) {
    v[i] = (*this)[i - 1];
  }
  swap(v);
}
template< class T >
T& knk::Vector< T >::at(size_t id)
{
  const Vector< T >* cthis = this;
  const T& cr = cthis->at(id);
  T& r = const_cast< T& >(cr);
  return r;
}
template< class T >
const T& knk::Vector< T >::at(size_t id) const
{
  if (id < getSize()) {
    return (*this)[id];
  }
  throw std::out_of_range("id out of bound");
}
template< class T >
T& knk::Vector< T >::operator[](size_t id) noexcept {
  return const_cast< T& >((*static_cast< const Vector< T >* >(this))[id]);
}
template< class T >
const T& knk::Vector< T >::operator[](size_t id) const noexcept {
  return data_[id];
}
template< class T >
knk::Vector< T >::Vector(const Vector< T >& rhs):
  Vector(rhs.getSize())
{
  for (size_t i = 0; i < rhs.getSize(); ++i) {
    data_[i] = rhs.data_[i];
  }
}
template< class T >
void knk::Vector< T >::swap(Vector< T >& rhs) noexcept
{
  std::swap(data_, rhs.data_);
  std::swap(size_, rhs.size_);
  std::swap(capacity_, rhs.capacity_);
}
template< class T >
knk::Vector< T >::Vector(Vector< T >&& rhs) noexcept:
  Vector()
{
  swap(rhs);
}
template< class T >
knk::Vector< T >& knk::Vector< T >::operator=(Vector< T >&& rhs) noexcept
{
  Vector< T > cpy(std::move(rhs));
  swap(cpy);
  return *this;
}
template< class T >
knk::Vector< T >& knk::Vector< T >::operator=(const Vector< T >& rhs)
{
  if (this == std::addressof(rhs))
  {
    return *this;
  }
  Vector< T > cpy(rhs);
  swap(cpy);
  return *this;
}
template< class T >
knk::Vector< T >::Vector(size_t size):
  data_(size ? new T[size] : nullptr),
  size_(size),
  capacity_(size)
{}
template< class T >
knk::Vector< T >::Vector(size_t size, const T& value):
  Vector(size)
{
  for (size_t i = 0; i < size; ++i) {
    data_[i] = value;
  }
}
template< class T >
size_t knk::Vector< T >::getSize() const noexcept {
  return size_;
}
template< class T >
bool knk::Vector< T >::isEmpty() const noexcept {
  return !size_;
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
