#include "two_to_k_tree.cpp"

#include <iostream>
#include <limits>

using namespace std;


vector<vector<int> > rand_elements(unsigned int seed, int k, int size, int max, int min){
  vector<vector<int> >  res(size, vector<int>(k));
  srand(seed);
  for (int i=0; i <size; i++){
    for (int j=0; j<k; ++j){
      res[i][j] = rand() % max + min;
    }
  }
  return res;
}

void print_dim_vector(const vector<vector<int>> &vec){
  for(vector<int> v : vec){
    cout << '{';
    for(int e : v){
      cout << e << ',';
    }
    cout << "\b}" << endl;
  }
  cout << endl;
}

void print_element(const vector<int> & vec){
  cout << "{";
  for(int e : vec){
    cout << e << ',';
  }
  cout << "\b}" << endl;
}

bool aInb(const vector<int>& a, const vector<vector<int> >& b){
  for(auto e: b){
    if(e == a){
      return true;
    }
  }
  return false;
}

bool check_results(const vector<vector<int> >& elements, const vector<vector<int> >& results, const std::vector<int>& min, const std::vector<int>& max){
  for(vector<int> e: elements){
    bool shouldBe = true;
    for(int i=0; i<e.size(); ++i){
      if(min[i] > e[i] || max[i] < e[i]){
        shouldBe = false;
      }
    }
    if(shouldBe && !aInb(e, results)){
      cout << "\t Failed test in element ";
      print_element(e);
      cout << endl;
      return false;
    }else if(!shouldBe && aInb(e, results)){
      cout << "\t Failed test in element: ";
      print_element(e);
      cout << endl;
      return false;
    }
  }
  return true;
}

bool do_test(int testid, const vector<vector<int> >& elements, const vector<vector<int> >& results, const std::vector<int>& min, const std::vector<int>& max){
  cout << "Starting test " << testid << ":" << endl;
  bool result = false;
  if(check_results(elements, results, min, max)){
    cout << "\t Test successful!" << endl;
    result = true;
  }
  cout << endl;
  return result;
}

void test1(){
  TwoToKTree<int> tree(1);
  vector<vector<int> > elements = rand_elements(11234, 1, 1000, 20, 0);
  for(vector<int> e : elements){
    tree.insert(e);
  }
  vector<int> min({5});
  vector<int> max({10});
  do_test(1,elements, tree.orthogonal_search(min, max), min, max);
}

void test2(){
  TwoToKTree<int> tree(2);
  vector<vector<int> > elements = rand_elements(21234, 2, 1000, 20, 0);
  for(vector<int> e : elements){
    tree.insert(e);
  }
  vector<int> min({5,5});
  vector<int> max({10,15});
  do_test(2,elements, tree.orthogonal_search(min, max), min, max);
}

void test3(){
  TwoToKTree<int> tree(3);
  vector<vector<int> > elements = rand_elements(31234, 3, 1000, 20, 0);
  for(vector<int> e : elements){
    tree.insert(e);
  }
  vector<int> min({5,5, 2});
  vector<int> max({10,15, 14});

  do_test(3,elements, tree.orthogonal_search(min, max), min, max);
}

void test4(){
  TwoToKTree<int> tree(4);
  vector<vector<int> > elements = rand_elements(41234, 4, 1000, 20, 0);
  for(vector<int> e : elements){
    tree.insert(e);
  }
  vector<int> min({5,5, 2, 9});
  vector<int> max({10,15, 14, 20});

  do_test(4,elements, tree.orthogonal_search(min, max), min, max);
}

void test5(){
  TwoToKTree<int> tree(5);
  vector<vector<int> > elements = rand_elements(51234, 5, 1000, 20, 0);
  for(vector<int> e : elements){
    tree.insert(e);
  }
  vector<int> min({5,5, 2, 9, 4});
  vector<int> max({10,15, 14, 20, 18});

  do_test(5, elements, tree.orthogonal_search(min, max), min, max);
}

void testPM2(){
  TwoToKTree<int> tree(2);
  vector<vector<int> > elements = rand_elements(521234, 2, 1000, 20, 0);
  for(vector<int> e : elements){
    tree.insert(e);
  }
  vector<int> min({10,std::numeric_limits<int>::min()});
  vector<int> max({10,std::numeric_limits<int>::max()});
  //print_dim_vector(tree.partial_match({0}, {10}));
  do_test(6,elements, tree.partial_match({0}, {10}), min, max);
}

void testPM5(){
  TwoToKTree<int> tree(5);
  vector<vector<int> > elements = rand_elements(521234, 5, 3000, 20, 0);
  for(vector<int> e : elements){
    tree.insert(e);
  }
  vector<int> min({10,std::numeric_limits<int>::min(),5, std::numeric_limits<int>::min(), std::numeric_limits<int>::min() });
  vector<int> max({10,std::numeric_limits<int>::max(),5, std::numeric_limits<int>::max(), std::numeric_limits<int>::max()  });
  //print_dim_vector(tree.partial_match({0}, {10}));
  do_test(7,elements, tree.partial_match({0,2}, {10, 5}), min, max);
}


int main(){
  //Test orthogonal search in 1-5 dimensions
  test1();
  test2();
  test3();
  test4();
  test5();

  //Test partial match
  testPM2();
  testPM5();
}
