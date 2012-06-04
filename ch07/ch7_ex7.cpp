#include <iostream>
#include <string>
#include <sstream>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

using namespace std;

struct Tnode {
  string word;
  int count;
  Tnode* left;
  Tnode* right;
};

typedef int (*CMP)(const void*, const void*);

Tnode* findNode(Tnode *, Tnode *, CMP);

Tnode* createNode(Tnode *root, std::string word, CMP compareFunc) {
  Tnode *t = new Tnode;
  t->word = word;
  t->count = 1;
  t->left = nullptr;
  t->right = nullptr;
  if (Tnode *r = findNode(root, t, compareFunc)) {
    r->count++;
    delete t;
    return r;
  }
  return t;
}

Tnode* findNode(Tnode *root, Tnode *p, CMP compareFunc) {
  if (!root) {
    return nullptr;
  }
  while (1) {
    int res = compareFunc(root, p);
    if (res == 0) {
      break;
    } else if (res > 0) {
      if (root->left) {
        root = root->left;
        continue;
      } else {
        root = nullptr;
        break;
      }
    } else if (res < 0) {
      if (root->right) {
        root = root->right;
        continue;
      } else {
        root = nullptr;
        break;
      }
    }
  }
  return root;
}

void addNode(Tnode*& root, Tnode* n, CMP compareFunc) {
  if (!root) {
    root = n;
    return;
  }
  Tnode *p = root;
  while (1) {
    int res = compareFunc(p, n);
    if (res == 0) {
      p->count++;
      break;
    } else if (res > 0) {
      if (p->left) { p = p->left; continue; }
      else { p->left = n; break; }
    } else if (res < 0){ 
      if (p->right) { p = p->right; continue; }
      else { p->right = n; break; }
    }
  }
}

void printTree(Tnode* root) {
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
  Tnode* root = nullptr;
  for (int i = 0; i < 2000000; i++) {
    ostringstream oss;
    char formated_valued[10];
    snprintf(formated_valued, 10, "%5d", rand() % 500);
    oss << "Hugo " << formated_valued;
    //printf("adding [%s]\n", oss.str().c_str()); time
    Tnode* r = createNode(root, oss.str(), ex7_cmp1);
    addNode(root, r, ex7_cmp1);
  }
  printf("root is name = [%s][%d]\n", root->word.c_str(), root->count);
  printTree(root);
  return 1;
}
