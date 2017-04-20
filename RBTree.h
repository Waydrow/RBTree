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

	// ��������
	void leftRotate(Node<T> *x);
	// ��������
	void rightRotate(Node<T> *y);
	// ��ӵ���������
	void insertFix(Node<T> *node);
	// ɾ������������
	void eraseFix();

	void clear(Node<T> * &node);
	void print(Node<T> *node, T key, int direction);

public:
	
	RBTree();
	// �������
	void insert(T key);
	// ɾ������
	void erase(T key);
	// ���Ҳ���
	void find(T key);
	// ��ղ���
	void clear();
	// debug
	void print();
	~RBTree();
};

#include "RBTree.cpp"

#endif // !_RBTree_
