#include "../Common/Node.h"
#include <iostream> 

// g++ SLS/main.cpp Common/Node.cpp 

using namespace std;

int main() {
  Node n1 ("Irvine");
  Node n2 ("Santa Ana");
  n1.setParent(n2);
  n1.setLocation("Anaheim");
  cout << "Parent of "<< n1.getLocation() << " is " <<n1.getParent()->getLocation()<< endl;
  return 0;
}
