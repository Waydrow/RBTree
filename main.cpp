#include <iostream>
#include <cstdio>
#include "RBTree.h"

using namespace std;

int main() {
	const int len = 9;
	int a[] = { 10, 40, 30, 60, 90, 70, 20, 50, 80 };

	RBTree<int> *tree = new RBTree<int>();

	for (int i = 0; i < len; i++) {
		tree->insert(a[i]);
	}
	tree->print();

	Node<int>* p = tree->find(40);
	printf("%d %d\n", p->key, p->color);

	tree->clear();

	delete tree;
	return 0;
}
