#ifndef _VECTOR_
#define _VECTOR_

#include <algorithm>
#include <optional>

template <typename T>
class Vec {
 public:
  Vec();
  virtual ~Vec();

 private:
  T* buf;
  size_t len;
  size_t _capacity;
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
  std::optional<T> pop();

  // Overloading index operator
  T operator[](size_t index);
};

template <typename T>
inline Vec<T>::Vec() {
  this->buf = nullptr;
  this->len = 0;
  this->_capacity = 0;
}

// Set this->_capacity to resize and reallocate to a new buffer
template <typename T>
void Vec<T>::reallocate(size_t resize) {
  this->_capacity = resize;
  if (this->_capacity == 0) {
    delete[] buf;
    buf = nullptr;
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
  if (this->_capacity < new_capacity) {
    reallocate(new_capacity);
  }
}

template <typename T>
inline Vec<T>::~Vec() {
  if (this->len == 0) delete[] this->buf;
}

template <typename T>
inline bool Vec<T>::is_empty() {
  return this->len == 0;
}

template <typename T>
void Vec<T>::push(T data) {
  size_t total = this->len + 1;
  if (total > this->_capacity) {
    if (this->_capacity == 0) {
      this->_capacity = 1;
    } else {
      this->_capacity = this->_capacity * 2;
    }
    reallocate(this->_capacity);
  }
  buf[this->len++] = data;
}

template <typename T>
std::optional<T> Vec<T>::pop() {
  if (this->len > 0) {
    T return_val = this->buf[this->len-- - 1];
    if (this->len == 0) {
      reallocate(0);
    } else if ((this->_capacity / this->len) > 4) {
      reallocate(this->_capacity /= 2);
    }
    return return_val;
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
