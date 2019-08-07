#ifndef _VECTOR_
#define _VECTOR_

#include <algorithm>
#include <optional>
#include <stdexcept>

template <typename T>
class Vec {
 public:
  Vec();
  Vec(const Vec<T>& v);
  T& operator=(const Vec<T>& v);
  virtual ~Vec();

 private:
  T* buf;
  size_t len;
  size_t _capacity;

  // Reallocate the underlying buffer base on `resize`.
  void reallocate(size_t resize);

 public:
  // Get the length of the vector
  size_t size();

  // Get the size of underneath array
  size_t capacity();

  // Set the size of underneath array to at least len + additional
  // Do nothing if capacity already greater than len + additional
  void reserve(size_t additional);

  // Examine if the vector is empty.
  bool is_empty();

  // Push data back to the vector
  void push(T data);

  // Pop out an element from the back of vector
  // this function is no exception safe
  std::optional<T> pop() noexcept;

  // Overloading index operator
  T operator[](size_t index);
};

template <typename T>
inline Vec<T>::Vec() {
  this->buf = nullptr;

  this->len = 0;
  this->_capacity = 0;
}

// Copy ctor
template <typename T>
Vec<T>::Vec(const Vec<T>& v) {
  this->buf = new T[v._capacity];
  std::copy(v.buf, v.buf + v.len, this->buf);
  this->len = v.len;
  this->_capacity = v._capacity;
}

// Copy assignment
template <typename T>
T& Vec<T>::operator=(const Vec<T>& v) {
  this->buf = new T[v._capacity];
  std::copy(v.buf, v.buf + v.len, this->buf);

  this->len = v.len;
  this->_capacity = v._capacity;
}

// Set this->_capacity to resize and reallocate to a new buffer
template <typename T>
void Vec<T>::reallocate(size_t resize) {
  this->_capacity = resize;
  if (this->_capacity == 0) {
    delete[] this->buf;
    this->buf = nullptr;
    return;
  }
  T* new_buf = new T[this->_capacity];
  std::copy(this->buf, this->buf + this->len, new_buf);
  delete[] buf;
  buf = new_buf;
}

template <typename T>
inline size_t Vec<T>::size() {
  return this->len;
}

template <typename T>
inline size_t Vec<T>::capacity() {
  return this->_capacity;
}

template <typename T>
void Vec<T>::reserve(size_t additional) {
  size_t new_capacity = this->len + additional;
  if (this->_capacity < new_capacity) reallocate(new_capacity);
}

template <typename T>
inline Vec<T>::~Vec() {
  if (this->buf != nullptr) delete[] this->buf;
}

template <typename T>
inline bool Vec<T>::is_empty() {
  return this->len == 0;
}

template <typename T>
void Vec<T>::push(T data) {
  size_t total = this->len + 1;
  if (total > this->_capacity) {
    if (this->_capacity == 0)
      this->_capacity = 1;
    else
      this->_capacity <<= 1;

    reallocate(this->_capacity);
  }
  buf[this->len] = data;
  this->len++;
}

// Pop the last element of the vector, if the vector is empty, return None.
template <typename T>
std::optional<T> Vec<T>::pop() noexcept {
  if (this->len > 0) {
    T ret = this->buf[this->len-- - 1];
    if (this->len == 0)
      reallocate(0);
    else if (this->_capacity > this->len << 2)
      reallocate(this->_capacity >> 1);

    return ret;
  }

  return {};
}

template <typename T>
T Vec<T>::operator[](size_t idx) {
  if (idx < this->len)
    return this->buf[idx];
  else
    throw "index out of range";
}

#endif /* ifndef _VECTOR_ */
