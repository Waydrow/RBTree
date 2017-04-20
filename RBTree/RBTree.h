#ifndef _RBTree_
#define _RBTree_

#include <iostream>

using namespace std;

// color of node
#define RED		0
#define BLACK	1

template <class T>
class Node {
public:
	T key;
	int color;
	Node *left;
	Node *right;
	Node *parent;

	Node(T _key, int _color, Node *_left, Node *_right, Node *_parent)
		:key(_key), color(_color), left(_left), right(_right), parent(_parent) {}
};

template <class T>
class RBTree {
private:
	Node<T> *root;

public:

};

#endif // !_RBTree_
