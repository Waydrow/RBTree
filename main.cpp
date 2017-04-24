#include <iostream>
#include <cstdio>
#include "RBTree.h"

using namespace std;

int main() {
	const int len = 9;
	int a[] = { 10, 40, 30, 60, 90, 70, 20, 50, 80 };

	RBTree<int> *tree = new RBTree<int>();

	for (int i = 0; i < len; i++) {
        int x;
        cin >> x;
        // ÃÌº”
		tree->insert(x);
		tree->print();
	}
	tree->print();
    // ≤È’“
	Node<int>* p = tree->find(40);
	printf("%d %d\n", p->key, p->color);

    // «Âø’
	tree->clear();

	delete tree;
	return 0;
}
