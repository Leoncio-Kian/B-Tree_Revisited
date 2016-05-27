#include "BTree.h"

//pointer to the root of the tree.
BTree *BTree::componentNode::bTreeRoot = nullptr;


//function for deleting a value node (i think).
int BTree::componentNode::deleteNode() {

	return 0;
}

//a setter function for setting valueNodes.
void BTree::componentNode::setValueNode(int index, valueNode * n) {
	this->valueNodeSet[index] = n;
	n = NULL;
}

//setter function for setting the root of the tree (this doesnt make any sense LOL).
void BTree::componentNode::setBTree(BTree * b) {
	bTreeRoot = b;
}


BTree::componentNode** BTree::compositeNode::getComponentNodeSet() {
	return componentNodeSet;
}