#include "../collections/Collection.h"

template <typename T>
class collection_iterator {
public:
  collection_iterator();

  // Used to dereference the current position that is been
  // pointed to.
  T operator*();

  // Used to get attribute of the current position
  T* operator->() const;

  // Act as ++iter
  // return the next position's iterator
  T operator++();

  // Act as iter++
  // return the current position's iterator
  T operator++(int);

  bool operator==(const collection_iterator &arg) const;

  bool operator!=(const collection_iterator &arg) const;
};
