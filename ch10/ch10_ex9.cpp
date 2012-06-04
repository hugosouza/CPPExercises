#include <iostream>
#include <string>
#include <sstream>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <boost/lexical_cast.hpp>

using namespace std;

struct Tnode {
  string word;
  int count;
  Tnode* left;
  Tnode* right;
};

typedef Tnode * TnodePtr;

typedef int (*CMP)(const void*, const void*);

class NodeTree {
  TnodePtr _root;
  CMP _cmp;

  bool addNode(TnodePtr);
  TnodePtr findNode(TnodePtr);
public:
  NodeTree(CMP cmp) : _root(nullptr), _cmp(cmp)  {}
  ~NodeTree();

  bool createNode(std::string);
  void printTree(TnodePtr);
};

NodeTree::~NodeTree() {
  printf("Delete tree, please\n");
}

bool NodeTree::createNode(std::string word) {
  TnodePtr t = new Tnode;
  t->word = word;
  t->count = 1;
  t->left = nullptr;
  t->right = nullptr;
  return addNode(t);
}

TnodePtr NodeTree::findNode(TnodePtr p) {
  if (!_root) {
    return nullptr;
  }
  TnodePtr nodePtr = _root;
  while (1) {
    int res = _cmp(_root, p);
    if (res == 0) {
      break;
    } else if (res > 0) {
      if (nodePtr->left) {
        nodePtr = nodePtr->left;
        continue;
      } else {
        nodePtr = nullptr;
        break;
      }
    } else if (res < 0) {
      if (nodePtr->right) {
        nodePtr = nodePtr->right;
        continue;
      } else {
        nodePtr = nullptr;
        break;
      }
    }
  }
  return nodePtr;
}

bool NodeTree::addNode(TnodePtr n) {
  if (!_root) {
    _root = n;
    return true;
  }
  TnodePtr nodePtr = _root;
  while (1) {
    int res = _cmp(nodePtr, n);
    if (res == 0) {
      nodePtr->count++;
      break;
    } else if (res > 0) {
      if (nodePtr->left) { nodePtr = nodePtr->left; continue; }
      else { nodePtr->left = n; break; }
    } else if (res < 0) {
      if (nodePtr->right) { nodePtr = nodePtr->right; continue; }
      else { nodePtr->right = n; break; }
    }
  }
  return true;
}

void NodeTree::printTree(TnodePtr root = nullptr) {
  if (root == nullptr) {
    root = _root;
  }
  if (root->left) {
    printTree(root->left);
  }
  printf("[%s] [%d]\n", root->word.c_str(), root->count);
  if (root->right) {
    printTree(root->right);
  }
}

int ex7_cmp1(const void *a, const void *b) {
  return static_cast<const Tnode *>(a)->word.compare(static_cast<const Tnode *>(b)->word);
}

int main(int argc, char** argv) {
  NodeTree root(ex7_cmp1);
  int count = 5;
  if (argc >= 2) {
    count = boost::lexical_cast<int>(argv[1]);
  }
  for (int i = 0; i < count; i++) {
    ostringstream oss;
    char formated_valued[10];
    snprintf(formated_valued, 10, "%5d", rand() % 500);
    oss << "Hugo " << formated_valued;
    printf("adding [%s]\n", oss.str().c_str());
    root.createNode(oss.str());
  }
  printf("Done, calling root.printTree()\n");
  root.printTree();
  return 1;
}
