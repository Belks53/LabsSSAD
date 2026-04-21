#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Node {
public:
    int value;
    vector<Node*> neighbors;

    Node(int val) : value(val) {}

    void addNeighbor(Node* node) {
        neighbors.push_back(node);
    }
};

class DFSIterator {
private:
    stack<Node*> st;

public:
    DFSIterator(Node* root) {
        if (root) {
            st.push(root);
        }
    }

    bool hasMore() {
        return !st.empty();
    }

    Node* getNext() {
        if (st.empty()) {
            return nullptr;
        }

        Node* current = st.top();
        st.pop();

        for (int i = current->neighbors.size() - 1; i >= 0; --i) {
            st.push(current->neighbors[i]);
        }

        return current;
    }
};

int task2() {
    Node* n1 = new Node(1);
    Node* n2 = new Node(2);
    Node* n3 = new Node(3);
    Node* n4 = new Node(4);
    Node* n5 = new Node(5);
    Node* n6 = new Node(6);
    Node* n7 = new Node(7);
/*
    1
   /  \
  2     3
 / \ \   \
4   5  7   6

    */
    n1->addNeighbor(n2);
    n1->addNeighbor(n3);
    n2->addNeighbor(n4);
    n2->addNeighbor(n5);
    n3->addNeighbor(n6);
    n2->addNeighbor(n7);

    DFSIterator it(n1);

    while (it.hasMore()) {
        Node* node = it.getNext();
        cout << node->value << " ";
    }

    delete n1;
    delete n2;
    delete n3;
    delete n4;
    delete n5;
    delete n6;
    delete n7;

    return 0;
}