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

// ����
template <class T>
void RBTree<T>::leftRotate(Node<T> *x) {
	// x ���Ҷ���Ϊ y
	Node<T> *y = x->right;
	// y���������Ϊ x ���Ҷ���
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

// ����
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



// ����һ����Ϊ key �Ľڵ�Ĳ���
template <class T>
void RBTree<T>::insert(T key) {
	// Ҫ����Ľڵ� node
	Node<T> *node = new Node<T>(key, BLACK, NULL, NULL, NULL);

	// �ҳ����� node Ӧ�ڵ�λ�� y
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

	// �����������
	insertFix(node);
}

// ��ӽڵ����������
template <class T>
void RBTree<T>::insertFix(Node<T> *node) {
	Node<T> *p, *pp;
	// p Ϊ node �ڵ�ĸ��ڵ�
	while ((p = node->parent) && p->color == RED) {
		// pp Ϊ node �ڵ���游�ڵ�
		pp = p->parent;
		if (p == pp->left) {
			// case 1 ����Ϊ��ɫ
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

// ɾ���ڵ����
template <class T>
void RBTree<T>::erase(T key) {
    // �Ȳ���Ҫɾ���ĵ�, ��������ֱ�ӷ���
    Node<T> *node = find(root, key);
    if (node == NULL) return;
    // ɾ������
    Node<T> *child, parent;
    int color;
    // �������Һ���
    if (node->left != NULL && node->right != NULL) {
        Node<T> *re = node->right;
        // re ΪҪ�滻�� node �Ľڵ�
        while(re->left != NULL) {
            re = re->left;
        }
        if (node->parent) {
            // node ���丸��������
            if (node == node->parent->left) {
                node->parent->left = re;
            } else {
                node->parent->right = re;
            }
        } else {
            // node Ϊ�����
            root = re;
        }
        child = re->right;
        parent = re->parent;
        color = re->color;
        if (parent == node) {
            parent = re;
        } else {
            if (child)
                child->parent = parent;
            parent->left = child;
            re->right = node->right;
            node->right->parent = re;
        }

        re->parent = node->parent;
        re->color = node->color;
        re->left = node->left;
        node->left->parent = re;
        // ��ɫ�ڵ������
        if (color == BLACK)
            eraseFix(child, parent);
        delete node;
        return;
    }

    // ֻ��һ�����ӻ��޺��ӵ����
    // ֻ�����ӻ��Һ���, ��ֱ�ӽ����ӷ��� node λ����
    if (node->left) {
        child = node->left;
    } else {
        child = node->right;
    }
    parent = node->parent;
    color = node->color;
    child->parent = parent;
    // node �и����
    if (parent) {
        // node Ϊ�丸�ڵ������
        if (node == parent->left)
            parent->left = child;
        else
            parent->right = child;
    } else {
        root = child;
    }
    if (color == BLACK) {
        eraseFix(child, parent);
    }
    delete node;
}

// ɾ���ڵ����������
template <class T>
void RBTree<T>::eraseFix(Node<T> *node, Node<T> *parent) {

}

// �ݹ���ҽڵ�
template <class T>
Node<T>* RBTree<T>::find(Node<T>* node, T key) {
    if (node == NULL || node->key == key) return node;
    if (key < node->key)
        return find(node->left, key);
    else
        return find(node->right, key);
}

// ���ҽڵ����
template <class T>
Node<T>* RBTree<T>::find(T key) {
    return find(root, key);
}

// �ݹ�����ڵ�
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

// ��ղ���
template <class T>
void RBTree<T>::clear() {
	clear(root);
}

// �ݹ��ӡ�ڵ���Ϣ
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
