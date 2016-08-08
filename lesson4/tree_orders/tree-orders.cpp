#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::ios_base;
using std::cin;
using std::cout;


class TreeOrders {
  long long n;
  vector <long long> key;
  vector <long long> left;
  vector <long long> right;

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
    if (key.size() <= 0)
      return result; // nothing to do. The tree is empty

    vector<long long> NodeIds; // stack for tree nodes while traversing
    long long curNode = 0;
    long long leftNode = 0, rightNode = 0, prevRight = -1;
    for (;;){
      if (curNode == -1){
        // need to go level up. Extract item from the stack
        if (NodeIds.size() != 0){
          curNode = NodeIds[NodeIds.size() - 1];
        }
        else // no more items. We are done
          break;

        // we already went all the way left. So, just need to go right
        // First, we print current item. Everything on the left has been printed
//        result.push_back(key[curNode]);
        if (right[curNode] != -1){
          if (right[curNode] != prevRight){
            // we did not come from there
            curNode = right[curNode];
            prevRight = -1;
            continue;
          }
          else{
            // we just came from there
            NodeIds.pop_back();
            prevRight = curNode;
            curNode = -1;
            continue;
          }
        }
        else{
          // we do not need it any more. Remove it from the stack
          NodeIds.pop_back();
          prevRight = curNode; // remember branch on the right we came from
          curNode = -1;
          continue;
        }
      }
      if (curNode != -1){
        result.push_back(key[curNode]);
        NodeIds.push_back(curNode);
        if (left[curNode] != -1){
          // store current node and traverse left
          curNode = left[curNode];
          continue;
        }
        else{
          // no items on the left...
          // store it on the stack and go right
          curNode = -1;
          continue;
        }
      }
    }

    return result;
  }

  vector <long long> post_order() {
    vector<long long> result;
    // Finish the implementation
    // You may need to add a new recursive method to do that
    if (key.size() <= 0)
      return result; // nothing to do. The tree is empty

    vector<long long> NodeIds; // stack for tree nodes while traversing
    long long curNode = 0;
    long long leftNode = 0, rightNode = 0, prevRight = -1;
    for (;;){
      if (curNode == -1){
        // need to go level up. Extract item from the stack
        if (NodeIds.size() != 0){
          curNode = NodeIds[NodeIds.size() - 1];
        }
        else // no more items. We are done
          break;

        // we already went all the way left. So, just need to go right
        // First, we print current item. Everything on the left has been printed
//        result.push_back(key[curNode]);
        if (right[curNode] != -1){
          if (right[curNode] != prevRight){
            // we did not come from there
            curNode = right[curNode];
            prevRight = -1;
            continue;
          }
          else{
            // we just came from there
            result.push_back(key[curNode]);
            NodeIds.pop_back();
            prevRight = curNode;
            curNode = -1;
            continue;
          }
        }
        else{
          // no children on the rght. It is a leaf. Print it
          result.push_back(key[curNode]);
          // we do not need it any more. Remove it from the stack
          NodeIds.pop_back();
          prevRight = curNode; // remember branch on the right we came from
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
          // store it on the stack and go right
          NodeIds.push_back(curNode);
          curNode = -1;
          continue;
        }
      }
    }

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
