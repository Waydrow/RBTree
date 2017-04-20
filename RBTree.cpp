#ifndef _RBTREE_CPP_
#define _RBTREE_CPP_

#include <iostream>
#include <cstdio>
#include "RBTree.h"
using namespace std;


template <typename T>
RBTree<T>::RBTree() {
	root = NULL;
}

template <class T>
RBTree<T>::~RBTree() {
	clear();
}

// 左旋
template <class T>
void RBTree<T>::leftRotate(Node<T> *x) {
	// x 的右儿子为 y
	Node<T> *y = x->right;
	// y的左儿子设为 x 的右儿子
	x->right = y->left;
	if (y->left != NULL) {
		y->left->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == NULL) {
		root = y;
	} else if (x == x->parent->left) {
		x->parent->left = y;
	} else {
		x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
}

// 右旋
template <class T>
void RBTree<T>::rightRotate(Node<T> *y) {
	Node<T> *x = y->left;
	y->left = x->right;
	if (x->right != NULL) {
		x->right->parent = y;
	}
	x->parent = y->parent;
	if (y->parent == NULL) {
		root = x;
	} else if (y == y->parent->right) {
		y->parent->right = x;
	} else {
		y->parent->left = x;
	}
	x->right = y;
	y->parent = x;
}



// 插入一个键为 key 的节点的操作
template <class T>
void RBTree<T>::insert(T key) {
	// 要插入的节点 node
	Node<T> *node = new Node<T>(key, BLACK, NULL, NULL, NULL);

	// 找出树中 node 应在的位置 y
	Node<T> *y = NULL;
	Node<T> *x = root;
	while (x != NULL) {
		y = x;
		if (node->key < x->key) {
			x = x->left;
		} else {
			x = x->right;
		}
	}
	node->parent = y;
	if (y == NULL) {
		root = node;
	} else if (node->key < y->key) {
		y->left = node;
	} else {
		y->right = node;
	}
	node->left = NULL;
	node->right = NULL;
	node->color = RED;

	// 添加修正操作
	insertFix(node);
}

// 添加节点的修正操作
template <class T>
void RBTree<T>::insertFix(Node<T> *node) {
	Node<T> *p, *pp;
	// p 为 node 节点的父节点
	while ((p = node->parent) && p->color == RED) {
		// pp 为 node 节点的祖父节点
		pp = p->parent;
		if (p == pp->left) {
			// case 1 叔叔为红色
			Node<T> *uncle = pp->right;
			if (uncle && uncle->color == RED) {
				p->color = BLACK;
				uncle->color = BLACK;
				pp->color = RED;
				node = pp;
			} else if (node == p->right) { // case 2
				Node<T> *tmp;
				leftRotate(p);
				tmp = p;
				p = node;
				node = tmp;
			} else if (node == p->left) { // case 3
				p->color = BLACK;
				pp->color = RED;
				rightRotate(pp);
			}
		} else {
			Node<T> *u = pp->left;
			if (u && u->color == RED) {
				p->color = BLACK;
				u->color = BLACK;
				pp->color = RED;
				node = pp;
			} else if (node == p->left) {
				Node<T> *tmp;
				rightRotate(p);
				tmp = p;
				p = node;
				node = tmp;
			} else if (node == p->right) {
				p->color = BLACK;
				pp->color = RED;
				leftRotate(pp);
			}
		}
	}
	root->color = BLACK;
}

// 递归清除节点
template <class T>
void RBTree<T>::clear(Node<T> * &node) {
	if (node == NULL) return;
	if (node->left != NULL) {
		return clear(node->left);
	}
	if (node->right != NULL) {
		return clear(node->right);
	}
	delete node;
	node = NULL;
}

// 清空操作
template <class T>
void RBTree<T>::clear() {
	clear(root);
}

// 递归打印节点信息
template <class T>
void RBTree<T>::print(Node<T> *node, T key, int direction) {
	if (node != NULL) {
		if (direction == 0) {
			printf("key = %d, color = black (root)\n", node->key);
		} else {
			printf("key = %d, color = ", node->key);
			if (node->color == RED)
				printf("red");
			else
				printf("black");
			printf(", %d's ", key);
			if (direction == 1)
				printf("right child\n");
			else
				printf("left child\n");
		}
		print(node->left, node->key, -1);
		print(node->right, node->key, 1);
	}
}

// debug
template <class T>
void RBTree<T>::print() {
	if (root == NULL) {
		printf("The tree is empty.\n");
		return;
	}
	print(root, root->key, 0);
}


#endif // !_RBTREE_CPP_
