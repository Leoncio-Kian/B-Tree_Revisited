#include "BTree.h"



BTree::BTree(int size) {
	nodeSize = size;
	root = new leafNode(0, size, NULL);
	root->setBTree(this);
}
BTree::BTree() {
	nodeSize = 0;
}

int BTree::insertBTree(std::string key, std::string value) {
	valueNode * n = new valueNode;
	n->value = value;

	n->key = key;
	int index;
	componentNode * temp = root;
	if (compositeNode * cn = dynamic_cast<compositeNode*> (root)) {
		cn->traverseNode(key, temp, index);
		temp->insertNode(n, index, NULL, NULL);
	}
	else {
		root->traverseNode(key, temp, index);
		root->insertNode(n, index, NULL, NULL);
	}
	return 0;
}
int BTree::deleteBtree() {
	return 0;
}
int BTree::setRoot(componentNode * n) {
	root = n;
	return 0;
}
void BTree::printTree() {
	if (compositeNode * cn = dynamic_cast<compositeNode*> (root))
		cn->printNode();
	else
		root->printNode();
}