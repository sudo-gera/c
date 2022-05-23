#include <iostream>
#include <random>
#include <vector>

struct Tree {
  long q = 0;
  long w = 0;
  long size = 1;
  Tree *second = nullptr;
  Tree *first = nullptr;
  Tree(long num, long pr) : q(num), w(pr) {}
};
long TreeSize(Tree *tree) { return tree ? tree->size : 0; }
void TreeUpdate(Tree *node) {
  if (node) {
    if (node->first == nullptr and node->second == nullptr) {
      node->size = 1;
    } else if (node->first == nullptr) {
      node->size = node->second->size + 1;
    } else if (node->second == nullptr) {
      node->size = node->first->size + 1;
    } else {
      node->size = node->second->size + node->first->size + 1;
    }
  }
}
Tree *TreeMerge(Tree *second, Tree *first) {
  if (first == nullptr or second and second->w > first->w) {
    if (first) {
      second->first = TreeMerge(second->first, first);
      TreeUpdate(second);
    }
    return second;
  } else {
    if (second) {
      first->second = TreeMerge(second, first->second);
      TreeUpdate(first);
    }
    return first;
  }
}
std::pair<Tree *, Tree *> TreeSplit(Tree *tree, long key) {
  std::pair<Tree *, Tree *> res = {nullptr, nullptr};
  if (tree) {
    if (key > tree->q) {
      res = TreeSplit(tree->first, key);
      tree->first = res.first;
      TreeUpdate(tree);
      TreeUpdate(res.second);
      res.first = tree;
    } else {
      res = TreeSplit(tree->second, key);
      tree->second = res.second;
      TreeUpdate(res.first);
      TreeUpdate(tree);
      res.second = tree;
    }
  }
  return res;
}
Tree *TreeKth(Tree *tree, long k) {
  while (tree) {
    auto size = TreeSize(tree->second);
    if (size < k) {
      k -= size;
      --k;
      tree = tree->first;
    } else if (size > k) {
      tree = tree->second;
    } else if (size == k) {
      return tree;
    } else {
      assert(0);
    }
  }
  return nullptr;
}
Tree *TreeFind(Tree *tree, long num) {
  if (tree == nullptr or num == tree->q) {
    return tree;
  }
  return TreeFind(num < tree->q ? tree->second : tree->first, num);
}
Tree *TreeInsert(Tree *tree, long num, long prior) {
  Tree *find = TreeFind(tree, num);
  if (find != nullptr) {
    return tree;
  }
  auto tmp = TreeSplit(tree, num);
  tmp.second = TreeMerge(new Tree(num, prior), tmp.second);
  tree = TreeMerge(tmp.first, tmp.second);
  return tree;
}
Tree *TreeNext(Tree *tree, long num) {
  Tree *next = nullptr;
  while (tree) {
    if (tree->q <= num) {
      tree = tree->first;
    } else {
      next = tree;
      tree = tree->second;
    }
  }
  return next;
}
Tree *TreePrev(Tree *tree, long num) {
  Tree *prev = nullptr;
  while (tree) {
    if (tree->q >= num) {
      tree = tree->second;
    } else {
      prev = tree;
      tree = tree->first;
    }
  }
  return prev;
}
Tree *TreeErase(Tree *tree, long q) {
  auto tmp = TreeSplit(tree, q);
  tree = tmp.first;
  tmp = TreeSplit(tmp.second, q + 1);
  delete tmp.first;
  return TreeMerge(tree, tmp.second);
}
void TreeDel(Tree *tree) {
  if (tree == nullptr) {
    return;
  }
  TreeDel(tree->first);
  TreeDel(tree->second);
  delete tree;
}

int main() {
  long q = 0;
  Tree *got = nullptr;
  char com[30];
  Tree *tree = nullptr;
  while (std::cin >> com >> q) {
    switch (com[0]) {
    case ('i'):
      tree = TreeInsert(tree, q, rand());
      break;
    case ('d'):
      tree = TreeErase(tree, q);
      break;
    case ('e'):
      std::cout << &"true\x0x/false"[(TreeFind(tree, q) == nullptr) * 7]
                << std::endl;
      break;
    case ('n'):
      got = TreeNext(tree, q);
      goto coutput;
    case ('p'):
      got = TreePrev(tree, q);
      goto coutput;
    case ('k'):
      got = TreeKth(tree, q);
    coutput:
      if (got == nullptr) {
        std::cout << "none" << std::endl;
      } else {
        std::cout << got->q << std::endl;
      }
      break;
    default:
      assert(0);
      break;
    }
  }
  TreeDel(tree);
}
