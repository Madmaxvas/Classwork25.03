#ifndef PE_VECTOR_HPP
#define PE_VECTOR_HPP

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <algorithm>

namespace knk {

template< class T >
class Vector {
 public:
  ~Vector();
  Vector();
  Vector(size_t size, const T& value);
  explicit Vector(std::initializer_list< T > il);

  Vector(const Vector< T >& rhs);
  Vector(Vector< T >&& rhs) noexcept;
  Vector< T >& operator=(const Vector< T >& rhs);
  Vector< T >& operator=(Vector< T >&& rhs) noexcept;
  void swap(Vector< T >& rhs) noexcept;

  void insert(size_t id, const T& t);
  void insert(size_t id, const Vector< T >& rhs, size_t beg, size_t end);
  void erase(size_t id);
  void erase(size_t beg, size_t end);

  struct VectorIterator {
   public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    VectorIterator() noexcept : ptr_(nullptr) {}
    explicit VectorIterator(T* ptr) noexcept : ptr_(ptr) {}

    reference operator*() const noexcept { return *ptr_; }
    pointer operator->() const noexcept { return ptr_; }

    VectorIterator& operator++() noexcept {
      ++ptr_;
      return *this;
    }
    VectorIterator operator++(int) noexcept {
      VectorIterator tmp(*this);
      ++ptr_;
      return tmp;
    }
    VectorIterator& operator--() noexcept {
      --ptr_;
      return *this;
    }
    VectorIterator operator--(int) noexcept {
      VectorIterator tmp(*this);
      --ptr_;
      return tmp;
    }

    VectorIterator& operator+=(difference_type n) noexcept {
      ptr_ += n;
      return *this;
    }
    VectorIterator& operator-=(difference_type n) noexcept {
      ptr_ -= n;
      return *this;
    }
    VectorIterator operator+(difference_type n) const noexcept {
      return VectorIterator(ptr_ + n);
    }
    VectorIterator operator-(difference_type n) const noexcept {
      return VectorIterator(ptr_ - n);
    }
    difference_type operator-(const VectorIterator& other) const noexcept {
      return ptr_ - other.ptr_;
    }

    reference operator[](difference_type n) const noexcept {
      return ptr_[n];
    }

    bool operator==(const VectorIterator& other) const noexcept {
      return ptr_ == other.ptr_;
    }
    bool operator!=(const VectorIterator& other) const noexcept {
      return ptr_ != other.ptr_;
    }
    bool operator<(const VectorIterator& other) const noexcept {
      return ptr_ < other.ptr_;
    }
    bool operator<=(const VectorIterator& other) const noexcept {
      return ptr_ <= other.ptr_;
    }
    bool operator>(const VectorIterator& other) const noexcept {
      return ptr_ > other.ptr_;
    }
    bool operator>=(const VectorIterator& other) const noexcept {
      return ptr_ >= other.ptr_;
    }

   private:
    T* ptr_;
  };

  struct VectorConstIterator {
   public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = const T*;
    using reference = const T&;

    VectorConstIterator() noexcept : ptr_(nullptr) {}
    explicit VectorConstIterator(const T* ptr) noexcept : ptr_(ptr) {}
    VectorConstIterator(const VectorIterator& it) noexcept
        : ptr_(&*it) {}

    reference operator*() const noexcept { return *ptr_; }
    pointer operator->() const noexcept { return ptr_; }

    VectorConstIterator& operator++() noexcept {
      ++ptr_;
      return *this;
    }
    VectorConstIterator operator++(int) noexcept {
      VectorConstIterator tmp(*this);
      ++ptr_;
      return tmp;
    }
    VectorConstIterator& operator--() noexcept {
      --ptr_;
      return *this;
    }
    VectorConstIterator operator--(int) noexcept {
      VectorConstIterator tmp(*this);
      --ptr_;
      return tmp;
    }

    VectorConstIterator& operator+=(difference_type n) noexcept {
      ptr_ += n;
      return *this;
    }
    VectorConstIterator& operator-=(difference_type n) noexcept {
      ptr_ -= n;
      return *this;
    }
    VectorConstIterator operator+(difference_type n) const noexcept {
      return VectorConstIterator(ptr_ + n);
    }
    VectorConstIterator operator-(difference_type n) const noexcept {
      return VectorConstIterator(ptr_ - n);
    }
    difference_type operator-(const VectorConstIterator& other) const noexcept {
      return ptr_ - other.ptr_;
    }

    reference operator[](difference_type n) const noexcept {
      return ptr_[n];
    }

    bool operator==(const VectorConstIterator& other) const noexcept {
      return ptr_ == other.ptr_;
    }
    bool operator!=(const VectorConstIterator& other) const noexcept {
      return ptr_ != other.ptr_;
    }
    bool operator<(const VectorConstIterator& other) const noexcept {
      return ptr_ < other.ptr_;
    }
    bool operator<=(const VectorConstIterator& other) const noexcept {
      return ptr_ <= other.ptr_;
    }
    bool operator>(const VectorConstIterator& other) const noexcept {
      return ptr_ > other.ptr_;
    }
    bool operator>=(const VectorConstIterator& other) const noexcept {
      return ptr_ >= other.ptr_;
    }

   private:
    const T* ptr_;
  };

  VectorIterator begin() noexcept { return VectorIterator(data_); }
  VectorIterator end() noexcept { return VectorIterator(data_ + size_); }
  VectorConstIterator begin() const noexcept {
    return VectorConstIterator(data_);
  }
  VectorConstIterator end() const noexcept {
    return VectorConstIterator(data_ + size_);
  }
  VectorConstIterator cbegin() const noexcept {
    return VectorConstIterator(data_);
  }
  VectorConstIterator cend() const noexcept {
    return VectorConstIterator(data_ + size_);
  }

  template< class FwdIterator >
  void insert(VectorIterator pos, FwdIterator begin, FwdIterator end);

  bool isEmpty() const noexcept;
  size_t getSize() const noexcept;
  size_t getCapacity() const noexcept;

  void pushBack(const T& t);
  void pushBackRepeat(const T& t, size_t k);
  void popBack();
  void pushFront(const T& t);

  T& operator[](size_t id) noexcept;
  const T& operator[](size_t id) const noexcept;
  T& at(size_t id);
  const T& at(size_t id) const;

 private:
  T* data_;
  size_t size_;
  size_t capacity_;

  explicit Vector(size_t size);
  void reserve(size_t new_capacity);
};

template< class T >
bool operator==(const Vector< T >& lhs, const Vector< T >& rhs);

}  // namespace knk

template< class T >
knk::Vector< T >::Vector(std::initializer_list< T > il)
    : Vector(il.size()) {
  size_t j = 0;
  for (auto i = il.begin(); i != il.end(); ++i) {
    data_[j++] = *i;
  }
}

template< class T >
void knk::Vector< T >::pushBackRepeat(const T& t, size_t k) {
  Vector< T > cpy(*this);
  for (size_t i = 0; i < k; ++i) {
    cpy.pushBack(t);
  }
  swap(cpy);
}

template< class T >
void knk::Vector< T >::pushBack(const T& t) {
  if (size_ == capacity_) {
    reserve(capacity_ == 0 ? 1 : capacity_ * 2);
  }
  data_[size_++] = t;
}

template< class T >
void knk::Vector< T >::pushFront(const T& t) {
  insert(0, t);
}

template< class T >
void knk::Vector< T >::popBack() {
  if (size_ == 0) {
    throw std::logic_error("popBack on empty vector");
  }
  --size_;
}

template< class T >
T& knk::Vector< T >::at(size_t id) {
  const Vector< T >* cthis = this;
  const T& cr = cthis->at(id);
  return const_cast< T& >(cr);
}

template< class T >
const T& knk::Vector< T >::at(size_t id) const {
  if (id >= size_) {
    throw std::out_of_range("id out of bound");
  }
  return data_[id];
}

template< class T >
T& knk::Vector< T >::operator[](size_t id) noexcept {
  return const_cast< T& >(
      (*static_cast< const Vector< T >* >(this))[id]);
}

template< class T >
const T& knk::Vector< T >::operator[](size_t id) const noexcept {
  return data_[id];
}

template< class T >
knk::Vector< T >::Vector(const Vector< T >& rhs)
    : Vector(rhs.getSize()) {
  for (size_t i = 0; i < rhs.getSize(); ++i) {
    data_[i] = rhs.data_[i];
  }
}

template< class T >
void knk::Vector< T >::swap(Vector< T >& rhs) noexcept {
  std::swap(data_, rhs.data_);
  std::swap(size_, rhs.size_);
  std::swap(capacity_, rhs.capacity_);
}

template< class T >
knk::Vector< T >::Vector(Vector< T >&& rhs) noexcept : Vector() {
  swap(rhs);
}

template< class T >
knk::Vector< T >& knk::Vector< T >::operator=(Vector< T >&& rhs) noexcept {
  Vector< T > cpy(std::move(rhs));
  swap(cpy);
  return *this;
}

template< class T >
knk::Vector< T >& knk::Vector< T >::operator=(const Vector< T >& rhs) {
  if (this == std::addressof(rhs)) {
    return *this;
  }
  Vector< T > cpy(rhs);
  swap(cpy);
  return *this;
}

template< class T >
knk::Vector< T >::Vector(size_t size)
    : data_(size ? new T[size] : nullptr),
      size_(size),
      capacity_(size) {}

template< class T >
knk::Vector< T >::Vector(size_t size, const T& value) : Vector(size) {
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
size_t knk::Vector< T >::getCapacity() const noexcept {
  return capacity_;
}

template< class T >
knk::Vector< T >::Vector()
    : data_(nullptr), size_(0), capacity_(0) {}

template< class T >
knk::Vector< T >::~Vector() {
  delete[] data_;
}

template< class T >
void knk::Vector< T >::reserve(size_t new_capacity) {
  if (new_capacity <= capacity_) {
    return;
  }
  T* new_data = new T[new_capacity];
  for (size_t i = 0; i < size_; ++i) {
    new_data[i] = std::move(data_[i]);
  }
  delete[] data_;
  data_ = new_data;
  capacity_ = new_capacity;
}

template< class T >
void knk::Vector< T >::insert(size_t id, const T& t) {
  if (id > size_) {
    throw std::out_of_range("insert position out of range");
  }
  Vector< T > cpy(*this);
  if (cpy.size_ == cpy.capacity_) {
    cpy.reserve(cpy.capacity_ == 0 ? 1 : cpy.capacity_ * 2);
  }
  for (size_t i = cpy.size_; i > id; --i) {
    cpy.data_[i] = std::move(cpy.data_[i - 1]);
  }
  cpy.data_[id] = t;
  ++cpy.size_;
  swap(cpy);
}

template< class T >
void knk::Vector< T >::insert(
    size_t id, const Vector< T >& rhs, size_t beg, size_t end) {
  if (id > size_ || beg > end || end > rhs.size_) {
    throw std::out_of_range("insert range out of bounds");
  }
  Vector< T > cpy(*this);
  size_t count = end - beg;
  if (cpy.size_ + count > cpy.capacity_) {
    cpy.reserve(cpy.capacity_ == 0 ? count : cpy.capacity_ + count);
  }
  for (size_t i = cpy.size_; i > id; --i) {
    cpy.data_[i + count - 1] = std::move(cpy.data_[i - 1]);
  }
  for (size_t i = 0; i < count; ++i) {
    cpy.data_[id + i] = rhs.data_[beg + i];
  }
  cpy.size_ += count;
  swap(cpy);
}

template< class T >
void knk::Vector< T >::erase(size_t id) {
  if (id >= size_) {
    throw std::out_of_range("erase position out of range");
  }
  Vector< T > cpy(*this);
  for (size_t i = id; i + 1 < cpy.size_; ++i) {
    cpy.data_[i] = std::move(cpy.data_[i + 1]);
  }
  --cpy.size_;
  swap(cpy);
}

template< class T >
void knk::Vector< T >::erase(size_t beg, size_t end) {
  if (beg > end || end > size_) {
    throw std::out_of_range("erase range out of bounds");
  }
  if (beg == end) {
    return;
  }
  Vector< T > cpy(*this);
  size_t count = end - beg;
  for (size_t i = end; i < cpy.size_; ++i) {
    cpy.data_[i - count] = std::move(cpy.data_[i]);
  }
  cpy.size_ -= count;
  swap(cpy);
}

template< class T >
template< class FwdIterator >
void knk::Vector< T >::insert(
    VectorIterator pos, FwdIterator begin, FwdIterator end) {
  size_t id = pos - VectorIterator(data_);
  Vector< T > cpy(*this);
  size_t count = 0;
  FwdIterator it = begin;
  while (it != end) {
    ++count;
    ++it;
  }
  if (cpy.size_ + count > cpy.capacity_) {
    cpy.reserve(cpy.capacity_ == 0 ? count : cpy.capacity_ + count);
  }
  for (size_t i = cpy.size_; i > id; --i) {
    cpy.data_[i + count - 1] = std::move(cpy.data_[i - 1]);
  }
  it = begin;
  for (size_t i = 0; i < count; ++i) {
    cpy.data_[id + i] = *it;
    ++it;
  }
  cpy.size_ += count;
  swap(cpy);
}

template< class T >
bool knk::operator==(const Vector< T >& lhs, const Vector< T >& rhs) {
  if (lhs.getSize() != rhs.getSize()) {
    return false;
  }
  for (size_t i = 0; i < lhs.getSize(); ++i) {
    if (lhs[i] != rhs[i]) {
      return false;
    }
  }
  return true;
}

#endif
