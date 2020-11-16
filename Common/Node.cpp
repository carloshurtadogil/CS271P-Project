#include "Node.h"

Node::Node (string l) {
  location = l;
  parent = NULL;
}

string Node::getLocation() {
  return location;
}

void Node::setLocation(string l) {
  location = l;
}

bool Node::nullParent() {
  return parent == NULL;
}

Node* Node::getParent() {
  return parent;
};

void Node::setParent(Node n) {
  parent = &(n);
}