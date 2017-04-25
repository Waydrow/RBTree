# RBTree
RBTree's c++ implemention

## Guide

### Initial

```c++
RBTree<int> *tree = new RBTree<int>();
```

### Insert

```c++
// The type of x equal to Initial type
tree->insert(x);
```

### Find

```c++
// x is the key that you want to find
// it will return the point of the node (key is x) if x exist
Node<int>* p = tree->find(x);
```

### Print

```c++
// it will show info of the current rb tree
tree->print();
```

### Delete

```c++
// it will delete the node that has value of x in the tree
tree->erase(x);
```

### Clear

```c++
// it will delete all nodes of the tree
tree->clear();
```

### Release Space

```c++
delete tree;
```