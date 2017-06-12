#ifndef TWOTOKTREE_H
#define TWOTOKTREE_H

#include <vector>


template <class T>
class TwoToKTree {
public:
  TwoToKTree(int k);
  ~TwoToKTree();

  void insert(const std::vector<T>& element);
  std::vector<std::vector<T> > orthogonal_search(const std::vector<T>& min, const std::vector<T>& max);
  std::vector<std::vector<T> > partial_match(const std::vector<T>& dims, const std::vector<T>& values);

private:
  int k;
  struct Node {
    std::vector<T> val;
    std::vector<Node*> children;
  };
  Node *root = NULL;
  Node *insert(Node *t, const std::vector<T>& e);
  unsigned int get_subtree_index(const std::vector<T> &key, const std::vector<T> &e);
  std::vector<std::vector<T> > orthogonal_search(Node *n, const std::vector<T>& min, const std::vector<T>& max);
  void destroy_node(Node *n);
};

#endif
