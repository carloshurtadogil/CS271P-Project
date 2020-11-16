#include <string>
using namespace std;

class Node {
  private:
    string location;
    Node* parent;

  public:
    Node(string l);

    string getLocation();
    void setLocation(string l);

    bool nullParent();
    Node* getParent();
    void setParent(Node n);
};