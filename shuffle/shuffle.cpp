// shuffle an array
#include <iostream>
#include <algorithm> // std::random_shuffle
#include <vector>
#include <ctime> // std::time
#include <cstdlib> //std::rand, std::srand

// random gnerator function
int myrandom(int i) {return std::rand() % i;}

void print(const std::vector<int>& v) {
  std::cout << "myvector:";
  for(std::vector<int>::const_iterator it=v.begin(); it!=v.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';
}

int main() {
  std::vector<int> foo;
  for(int i=0; i<10; ++i) foo.push_back(i);
 
  print(foo);
  // using built-in random generator
  std::srand( unsigned (std::time(0)) );
  std::random_shuffle(foo.begin(), foo.end());

  print(foo); 
  // using myrandom
  std::random_shuffle(foo.begin(), foo.end(), myrandom);
  print(foo); 
  
  return 0;
} 
