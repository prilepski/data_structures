#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::ios_base;
using std::cin;
using std::cout;

struct TreeNode{
  TreeNode():
    node(-1),
    index(-1){
  }

  long long node;
  long long index;
};

class TreeOrders {
  long long n;
  vector <long long> key;
  vector <long long> left;
  vector <long long> right;
  vector <TreeNode> tree;

public:
  void read() {
    cin >> n;
    key.resize(n);
    left.resize(n);
    right.resize(n);
    long long numEmpty = 0;
    for (long long i = 0; i < n; i++) {
      cin >> key[i] >> left[i] >> right[i];
      if (left[i] == -1)
        numEmpty++;
      if (right[i] == -1)
        numEmpty++;
    }

    tree.resize(key.size() + numEmpty);

    buildTree();
  }

  void buildTree(){
    if (tree.size() <= 0)
      return;

    TreeNode Node;
    Node.node = key[0];
    Node.index = 0;
    tree[0] = Node;
/*
    Node.node = key[left[0]];
    Node.index = left[0];
    tree[1] = Node;


    tree[2] = key[right[0]];
*/
    long long LeftNode, RightNode;
    for (long long i = 0; i <= tree.size() / 2; ++i){
      if (tree[i].node == -1)
        continue;
      LeftNode = 2 * i + 1;
      if (LeftNode < tree.size()){
        if (left[tree[i].index] != -1){
          Node.node = key[left[tree[i].index]];
          Node.index = left[tree[i].index];
        }
        else{
          Node.index = -1;
          Node.node = -1;
        }
        tree[LeftNode] = Node;
      }

      RightNode = 2 * i + 2;
      if (RightNode < tree.size()){
        if (right[tree[i].index] != -1){
          Node.node = key[right[tree[i].index]];
          Node.index = right[tree[i].index];
        }
        else{
          Node.node = -1;
          Node.index = -1;
        }
        tree[RightNode] = Node;
      }
    }
    return;
  }

  vector <long long> in_order() {
    vector<long long> result;
    // Finish the implementation
    // You may need to add a new recursive method to do that
    if (key.size() <= 0)
      return result; // nothing to do. The tree is empty

    vector<long long> NodeIds; // stack for tree nodes while traversing
    long long curNode = 0;
    long long leftNode = 0, rightNode = 0;
    for (;;){
      if (curNode == -1){
        // need to go level up. Extract item from the stack
        if (NodeIds.size() != 0){
          curNode = NodeIds[NodeIds.size() - 1];
          NodeIds.pop_back();
        }
        else // no more items. We are done
          break;

        // we already went all the way left. So, just need to go right
        // First, we print current item. Everything on the left has been printed
        result.push_back(key[curNode]);
        if (right[curNode] != -1){
          curNode = right[curNode];
          continue;
        }
        else{
          // no children on the rght. Time to go up
          curNode = -1;
          continue;
        }
      }
      if (curNode != -1){
        if (left[curNode] != -1){
          // store current node and traverse left
          NodeIds.push_back(curNode);
          curNode = left[curNode];
          continue;
        }
        else{
          // no items on the left...
          // put it into stack
          NodeIds.push_back(curNode);
          curNode = -1;
          continue;
        }
      }
    }

    return result;
  }

  vector <long long> pre_order() {
    vector<long long> result;
    // Finish the implementation
    // You may need to add a new recursive method to do that

    return result;
  }

  vector <long long> post_order() {
    vector<long long> result;
    // Finish the implementation
    // You may need to add a new recursive method to do that

    return result;
  }
};

void print(vector <long long> a) {
  for (size_t i = 0; i < a.size(); i++) {
    if (i > 0) {
      cout << ' ';
    }
    cout << a[i];
  }
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(0);
  TreeOrders t;
  t.read();
  print(t.in_order());
  print(t.pre_order());
  print(t.post_order());
  return 0;
}
