#include <iostream>
#include <cstdio>
#include "RBTree.h"

using namespace std;

int main() {
	const int len = 9;
	int a[] = { 10, 40, 30, 60, 90, 70, 20, 50, 80 };

	RBTree<int> *tree = new RBTree<int>();

	for (int i = 0; i < len; i++) {
        int x = a[i];
        //cin >> x;
        // 插入
		tree->insert(x);
		//tree->print();
	}
	tree->print();
	int y;
	cin >> y;
	tree->insert(y);
	tree->print();
	for (int i = 0; i < len; i++) {
        int x;
        cin >> x;
        tree->erase(x);
        tree->print();
	}
	tree->print();
    // 查找
	Node<int>* p = tree->find(40);
	printf("%d %d\n", p->key, p->color);

    // 清空
	tree->clear();

	delete tree;
	return 0;
}
