CXX=g++
RM=rm -f
FLAGS=-std=c++11

two_to_k_tree.o: two_to_k_tree.hpp two_to_k_tree.cpp
	$(CXX) $(FLAGS) -c two_to_k_tree.cpp

test: two_to_k_tree.o
	$(CXX) $(FLAGS) -o test_two_to_k_tree test.cpp two_to_k_tree.o
	time ./test_two_to_k_tree

clean:
	$(RM) *.o two_to_k_tree
