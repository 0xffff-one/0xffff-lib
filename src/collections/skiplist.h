#ifndef SKIP_LIST
#define SKIP_LIST

#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <functional>

template <typename T, typename Comparator = std::less<T> >
class SkipList {
 private:
  struct Node {
    T value;
    size_t level_num{};
    struct nodeLevel {
      struct Node *forward;
    } * level;
    Node(T value, int level) {
      this->value = value;
      this->level = new nodeLevel[level];
      this->level_num = level;
      std::memset(this->level, 0, sizeof(struct nodeLevel *) * level);
    }

    Node(const Node &other) {
      this->value = other.value;
      this->level_num = other.level_num;
      std::copy(other.level, other.level + level_num, this->level);
    }

    virtual ~Node() { delete this->level; }
  };

  static const size_t MAXLEVEL = 32;
  int largestLevel;
  Node *header, *tail;
  size_t len;
  Comparator cmp;

  static int randomLevel();

 public:
  SkipList(Comparator comparator);
  SkipList(const SkipList<T, Comparator> &other);
  SkipList &operator=(const SkipList<T, Comparator> &other);
  virtual ~SkipList();

  Node *insert(T value);
  size_t size() const;
};

template <typename T, typename Comparator>
SkipList<T, Comparator>::SkipList(Comparator comparator) : cmp(comparator) {
  this->len = 0;
  this->header = new Node(0, MAXLEVEL);

  for (size_t i = 0; i < MAXLEVEL; i++) {
    this->header->level[i].forward = nullptr;
  }

  this->largestLevel = 1;
  this->tail = nullptr;
}

template <typename T, typename Comparator>
SkipList<T, Comparator>::~SkipList() {
  Node *node = this->header->level[0].forward, *next;
  delete this->header;
  while (node) {
    next = node->level[0].forward;
    delete node;
    node = next;
  }
}

// http://www.voidcn.com/article/p-mwawflgq-bgg.html
template <typename T, typename Comparator>
int SkipList<T, Comparator>::randomLevel() {
  int level = 1;

  while ((random() & 0xFFFF) < (0.25 * 0xFFFF)) level += 1;

  return (level < signed(MAXLEVEL)) ? level : MAXLEVEL;
}

template <typename T, typename Comparator>
SkipList<T, Comparator>::SkipList(const SkipList<T, Comparator> &other) {
  SkipList nl = SkipList(other.cmp);
  nl.largestLevel = other.largestLevel;
  nl.len = other.len;
  Node *head = other.header, *next;
  for (size_t i = 0; i < nl.len; i++) {
    next = head->level[0].forward;
    *head = Node(*head);
    head = next;
  }
}

template <typename T, typename Comparator>
typename SkipList<T, Comparator>::Node *SkipList<T, Comparator>::insert(
    T value) {
  Node *update[MAXLEVEL], *x;
  Comparator lessThan = this->cmp;

  x = this->header;
  for (int i = this->largestLevel - 1; i >= 0; i--) {
    while (x->level[i].forward && /*this level enable*/
           lessThan(x->level[i].forward->value, value)) {
      x = x->level[i].forward;
    }

    // equal just return the existing node's ptr
    if (x->level[i].forward && !lessThan(x->level[i].forward->value, value) &&
        !lessThan(value, x->level[i].forward->value)) {
      return x->level[i].forward;
    }
    update[i] = x;
  }

  int level_num = randomLevel();
  if (level_num > this->largestLevel) {
    for (int i = this->largestLevel; i < level_num; i++) {
      update[i] = this->header;
    }
    this->largestLevel = level_num;
  }
  x = new Node(value, level_num);

  for (int i = 0; i < this->largestLevel; i++) {
    x->level[i].forward = update[i]->level[i].forward;
    update[i]->level[i].forward = x;
  }

  this->len++;
  return x;
}

template <typename T, typename Comparator>
inline size_t SkipList<T, Comparator>::size() const {
  return this->len;
}

#endif  // SKIP_LIST
