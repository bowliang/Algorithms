/*
 *  test_math.cpp
 *  cpputils
 *
 *  Created by Bowen Liang.
 *
 */

#include <iostream>
#include "math.hpp"

using std::cout;
using std::endl;
using namespace algorithm;

int main(int argc, char *argv[]) {
	
  cout<<"Factorial using templates"<<endl;

  
  cout<<"Combinations using templates"<<endl;

  // set seed for random number generator
  srnd(1);
  
  cout<<"Printing 100 real numbers between 0 and 1"<<endl;
  for (int i=0; i<100; ++i)
    cout<<" "<<rnd();
  cout<<endl;
  
  
  
  return 0;
}
