#include "two_to_k_tree.hpp"
#include <iostream>

template <class T>
TwoToKTree<T>::TwoToKTree(int k){
  this->k = k;
}


template <class T>
TwoToKTree<T>::~TwoToKTree(){
  destroy_node(root);
}

template <class T>
void TwoToKTree<T>::destroy_node(Node *n){
  if(n == NULL){
    return;
  }
  for(int i=0; i<n->children.size(); ++i){
    destroy_node(n->children[i]);
  }
  delete n;
}


template <class T>
void TwoToKTree<T>::insert(const std::vector<T>& element){
  if(element.size() != k) throw;
  root = insert(root, element);
}

template <class T>
typename TwoToKTree<T>::Node* TwoToKTree<T>::insert(Node *n, const std::vector<T>& e){
  if(n == NULL){
    Node *n =  new Node();
    n->val = e;
    n->children = std::vector<Node*>(1 << k, NULL);
    return n;
  }

  unsigned int index = get_subtree_index(n->val, e);
  n->children[index] = insert(n->children[index], e);
  return n;
}

template <class T>
unsigned int TwoToKTree<T>::get_subtree_index(const std::vector<T> &key, const std::vector<T> &e){
  unsigned int index = 0;
  for(int i=0; i<key.size(); ++i){
    index = index | (key[i] <= e[i]);
    index = index << 1;
  }
  return index >> 1;
}

template <class T>
std::vector<std::vector<T> > TwoToKTree<T>::orthogonal_search(const std::vector<T>& min, const std::vector<T>& max){
  if(min.size() != k) throw;
  if(max.size() != k) throw;

  return orthogonal_search(root, min, max);
}

template <class T>
std::vector<std::vector<T> > TwoToKTree<T>::orthogonal_search(Node *n, const std::vector<T>& min, const std::vector<T>& max){
  if(n == NULL){
    return std::vector<std::vector<T>>(0);
  }
  unsigned int zeros_mask = 0;
  unsigned int ones_mask = 0;

  for(int i=0; i<n->val.size(); ++i){
    zeros_mask = (zeros_mask | (min[i] <= n->val[i])) << 1;
    ones_mask = (ones_mask | (max[i] >= n->val[i])) << 1;
  }
  zeros_mask = zeros_mask >> 1;
  ones_mask = ones_mask >> 1;
  //Travese only the subtrees that match the query.
  std::vector<std::vector<T> > res(0);
  for(int i=0; i<n->children.size(); ++i){
     if(((~i & zeros_mask) | (i & ones_mask)) == (1 << n->val.size()) - 1){
       std::vector<std::vector<T>> ri = orthogonal_search(n->children[i], min, max);
       res.insert(res.end(), ri.begin(), ri.end());
     }
  }
  //Include the current element if matches.
  for(int i=0; i<n->val.size(); ++i){
    if(n->val[i] < min[i] || n->val[i] > max[i]){
      return res;
    }
  }
  res.push_back(n->val);
  return res;
}

template <class T>
std::vector<std::vector<T> > TwoToKTree<T>::partial_match(const std::vector<T>& dims, const std::vector<T>& values){
  std::vector<T> mins(k);
  std::vector<T> maxs(k);
  for(int i=0; i<k; ++i){
    mins[i] = std::numeric_limits<int>::min();
    maxs[i] = std::numeric_limits<int>::max();
    for(int j=0; j<dims.size(); ++j){
      if(dims[j] == i){
        mins[i] = values[j];
        maxs[i] = values[j];
        break;
      }
    }
  }
  return orthogonal_search(mins,maxs);
}
