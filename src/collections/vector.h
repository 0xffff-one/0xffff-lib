#ifndef _VECTOR_
#define _VECTOR_

#include <algorithm>

template <typename T>
class Vec {
  public:
  Vec();
  virtual ~Vec();

  private:
  T* buf;
  size_t len;

  public:
  // Get the length of the vector
  size_t size();

  // Examine if the vector is empty.
  bool is_empty();

  // Push data back to the vector
  void push(T data);

  // Pop out an element from the back of vector
  T* pop();

  // Overloading index operator
  T operator[](size_t index);
};

template <typename T>
inline Vec<T>::Vec()
{
  this->buf = nullptr;
  len = 0;
}

template <typename T>
inline size_t Vec<T>::size()
{
  return this->len;
}

template <typename T>
inline Vec<T>::~Vec()
{
  if (this->len == 0)
    delete[] this->buf;
}

template <typename T>
inline bool Vec<T>::is_empty()
{
  return this->len == 0;
}

template <typename T>
void Vec<T>::push(T data)
{
  T* new_buf = new T[this->len + 1];
  std::copy(this->buf, this->buf + this->len, new_buf);
  new_buf[this->len] = data;

  delete[] this->buf;

  this->buf = new_buf;
  this->len++;
}

template <typename T>
T* Vec<T>::pop()
{
  if (this->len > 0) {
    T* result = &this->buf[this->len - 1];
    this->len--;
    return result;
  }

  return nullptr;
}

template <typename T>
T Vec<T>::operator[](size_t idx)
{
  if (idx < this->len) {
    return this->buf[idx];
  } else {
    throw "index out of range";
  }
}

#endif /* ifndef _VECTOR_ */
