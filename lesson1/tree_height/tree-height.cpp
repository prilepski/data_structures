#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

class TreeNode{
public:
  TreeNode(long index):
    index(index)
    {}

  TreeNode():
    index(-1), level(-1)
    {}

  long index;
  long level;
  std::vector<TreeNode*> children;
};

class TreeHeight {
  long n; // number of nodes
  std::vector<long> parent;
  std::vector<TreeNode*> tree;
  long rootNode;

public:
  virtual ~TreeHeight(){
    for (long i = 0; i < tree.size(); ++i){
      if (tree[i] != NULL)
        delete tree[i];
    }
  }
  void read() {
    rootNode = -1;
    std::cin >> n;
    parent.resize(n);
    tree.resize(n);
    for (long i = 0; i < tree.size(); ++i){
      tree[i] = new TreeNode(-1);
    }

    for (long i = 0; i < n; i++){
      std::cin >> parent[i];

      // create i-th node of the tree & add it to vector
      if (!tree[i]->index == -1){
        tree[i]->index = i;
      }

      if (parent[i] == -1){
        // this is a root node
        rootNode = i; // remember root node
        tree[i]->level = 1; // root node is at level 1
        continue;
      } else if (tree[parent[i]]->index == -1){
        // add i-th node as a child to entered parent
        // node has not been created yet. Create it first
        tree[parent[i]]->index = parent[i];
      }
      // add i-th node as childrent to specified by entry node
      tree[parent[i]]->children.push_back(tree[i]);
    }
  }

  long compute_height() {
    // Replace this code with a faster implementation
    long maxHeight = 0;
    for (long vertex = 0; vertex < n; vertex++) {
      long height = 0;
      for (long i = vertex; i != -1; i = parent[i])
        height++;
      maxHeight = std::max(maxHeight, height);
    }
    return maxHeight;
  }

  long compute_height2(){
    long maxHeight = 0;

    if (rootNode == -1 || tree.size() < 1)
      return 0; // no root node or empty tree

    std::queue<TreeNode*> treeQueue;
    treeQueue.push(tree[rootNode]);

    while (treeQueue.size() != 0){
      TreeNode* currNode = treeQueue.front();
      treeQueue.pop();

      // update max height
      maxHeight = std::max(maxHeight, currNode->level);

      // iterate through all children
      for (long i = 0; i < currNode->children.size(); ++i){
        currNode->children[i]->level = currNode->level + 1;
        treeQueue.push(currNode->children[i]);
      }
    }
    return maxHeight;
  }
};

int main() {
  std::ios_base::sync_with_stdio(0);
  TreeHeight tree;
  tree.read();
//  std::cout << tree.compute_height() << std::endl;
  std::cout << tree.compute_height2() << std::endl;
}
