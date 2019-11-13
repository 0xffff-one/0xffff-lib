#ifndef SKIP_LIST
#define SKIP_LIST

#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <functional>

template <typename K, typename V, typename Comparator = std::less<K> >
class SkipList {
 private:
  struct Node {
    K key;
    V value;
    size_t level_num{};
    struct nodeLevel {
      struct Node *forward;
    } * level;
    Node(K key, V value, int level) {
      this->key = key;
      this->value = value;
      this->level = new nodeLevel[level];
      this->level_num = level;
      std::memset(this->level, 0, sizeof(struct nodeLevel *) * level);
    }

    Node(const Node &other) {
      this->key = other.key;
      this->value = other.value;
      this->level_num = other.level_num;
      std::copy(other.level, other.level + level_num, this->level);
    }

    virtual ~Node() { delete this->level; }
  };

  static const size_t MAXLEVEL = 32;
  int largestLevel{};
  Node *header, *tail;
  size_t len;
  Comparator cmp;

  static int randomLevel();

 public:
  SkipList(Comparator comparator);
  SkipList(const SkipList<K, V, Comparator> &other);
  SkipList &operator=(const SkipList<K, V, Comparator> &other);
  virtual ~SkipList();

  Node *insert(K key, V value, bool replace= false);
  Node *search(const K &key);
  bool remove(const K &key);
  size_t size() const;
};

template <typename K, typename V, typename Comparator>
SkipList<K, V, Comparator>::SkipList(Comparator comparator) : cmp(comparator) {
  this->len = 0;
  this->header = new Node(K(), V(), MAXLEVEL);

  for (size_t i = 0; i < MAXLEVEL; i++) {
    this->header->level[i].forward = nullptr;
  }

  this->largestLevel = 1;
  this->tail = nullptr;
}

template <typename K, typename V, typename Comparator>
SkipList<K, V, Comparator>::~SkipList() {
  Node *node = this->header->level[0].forward, *next;
  delete this->header;
  while (node) {
    next = node->level[0].forward;
    delete node;
    node = next;
  }
}

// http://www.voidcn.com/article/p-mwawflgq-bgg.html
template <typename K, typename V, typename Comparator>
int SkipList<K, V, Comparator>::randomLevel() {
  int level = 1;

  while ((random() & 0xFFFF) < (0.25 * 0xFFFF)) level += 1;

  return (level < signed(MAXLEVEL)) ? level : MAXLEVEL;
}

template <typename K, typename V, typename Comparator>
SkipList<K, V, Comparator>::SkipList(const SkipList<K, V, Comparator> &other) {
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

template <typename K, typename V, typename Comparator>
typename SkipList<K, V, Comparator>::Node *SkipList<K, V, Comparator>::insert(
        K key, V value, bool replace) {
  // store the level and the position to insert After
  Node *update[MAXLEVEL], *x;
  Comparator lessThan = this->cmp;

  x = this->header;
  for (int i = this->largestLevel - 1; i >= 0; i--) {
    while (x->level[i].forward && /*this level enable*/
           lessThan(x->level[i].forward->key, key)) {
      x = x->level[i].forward;
    }

    // equal key conflict
    if (x->level[i].forward &&
        !lessThan(x->level[i].forward->key, key) &&
        !lessThan(key, x->level[i].forward->key)) {
        if(!replace) return nullptr;
        else
            this->len--; // minus one first
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
  x = new Node(key, value, level_num);

  for (int i = 0; i < this->largestLevel; i++) {
    x->level[i].forward = update[i]->level[i].forward;
    update[i]->level[i].forward = x;
  }

  this->len++;
  return x;
}

template <typename K, typename V, typename Comparator>
inline size_t SkipList<K, V, Comparator>::size() const {
  return this->len;
}

template<typename K, typename V, typename Comparator>
typename SkipList<K, V, Comparator>::Node *SkipList<K, V, Comparator>::search(const K &key) {
    Node *x = this->header, *ret = nullptr;
    Comparator less = this->cmp;
    for(int i=this->largestLevel-1;i>=0;i--) {
        while (x->level[i].forward &&
            less(x->level[i].forward->key, key)) {
            x = x->level[i].forward;
        }

        // equal just return
        if(x->level[i].forward &&
            !less(x->level[i].forward->key, key) &&
            !less(key, x->level[i].forward->key)) {
            ret = x->level[i].forward;
            return ret;
        }
    }
    return ret;
}

template<typename K, typename V, typename Comparator>
bool SkipList<K, V, Comparator>::remove(const K& key) {
    Node *x = this->header;
    bool ret = false;
    Comparator less = this->cmp;
    for(int i=this->largestLevel-1;i>=0;i--) {
        while (x->level[i].forward &&
               less(x->level[i].forward->key, key)) {
            x = x->level[i].forward;
        }

        // equal just return
        if(x->level[i].forward &&
           !less(x->level[i].forward->key, key) &&
           !less(key, x->level[i].forward->key)) {
//            ret = x->level[i].forward;
            Node *del = x->level[i].forward;
            x->level[i].forward = del->level[i].forward;
            delete del;
            ret = true;
            this->len--;
            return ret;
        }
    }
    return ret;
}


#endif  // SKIP_LIST
