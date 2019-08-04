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
  size_t cap;

  public:
  // Get the length of the vector
  size_t size();

  // Get the size of underneath array
  size_t capity();

  // Set the size of underneath array
  size_t capity(size_t s);

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
inline Vec<T>::Vec()
{
  this->buf = nullptr;
  len = 0;
  cap = 0;
}

template <typename T>
inline size_t Vec<T>::size()
{
  return this->len;
}

template<typename T>
inline size_t Vec<T>::capity()
{
  return this->cap;
}

template<typename T>
inline size_t Vec<T>::capity(size_t s)
{
  if (s >= this->len) {
    T *new_buf = new T[s];
    this->cap = s;
    std::copy(this->buf, this->buf+this->len, new_buf);
  }
  return this->cap;
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
  size_t total = this->len+1;
  if (total > this->cap) {
    size_t new_cap = total*3/2 + 1;
    T *new_buf = new T[new_cap];
    this->cap = new_cap;
    std::copy(this->buf, this->buf + this->len, new_buf);
    delete[] this->buf;
    this->buf = new_buf;
  }
  buf[this->len]= data;
  this->len++;

}

template <typename T>
std::optional<T> Vec<T>::pop()
{
  if (this->len > 0) {
    if ((this->cap / this->len) > 2) {
        capity((this->len-1)*3/2);
    }
    return this->buf[this->len-- -1];
  }

  return {};
}

template <typename T>
T Vec<T>::operator[](size_t idx)
{
  if (idx < this->len)
    return this->buf[idx];
  else
    throw "index out of range";
}

#endif /* ifndef _VECTOR_ */
