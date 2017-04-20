#ifndef _RBTree_
#define _RBTree_

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

	// 左旋操作
	void leftRotate(Node<T> *x);
	// 右旋操作
	void rightRotate(Node<T> *y);
	// 添加的修正操作
	void insertFix(Node<T> *node);
	// 删除的修正操作
	void eraseFix();

	void clear(Node<T> * &node);
	void print(Node<T> *node, T key, int direction);

public:
	
	RBTree();
	// 插入操作
	void insert(T key);
	// 删除操作
	void erase(T key);
	// 查找操作
	void find(T key);
	// 清空操作
	void clear();
	// debug
	void print();
	~RBTree();
};

#include "RBTree.cpp"

#endif // !_RBTree_
