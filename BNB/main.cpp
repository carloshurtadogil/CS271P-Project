#include "../Common/Node.h"
#include <iostream> 
// g++ BNB/main.cpp Common/Node.cpp 
using namespace std;

int main() {
  Node irvine ("Irvine");
  Node santaAna ("Santa Ana");
  irvine.setParent(santaAna);
  cout << "Parent of "<< irvine.getLocation() << " is " <<irvine.getParent()->getLocation()<< endl;
  return 0;
}
