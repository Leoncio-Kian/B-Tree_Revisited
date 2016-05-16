#include "BTree.h"


//constructor
BTree::BTree(int size) {
	//set the size of each node.
	nodeSize = size;
	//create the first node and set it as a root.
	//the first node is always a leaf.
	root = new leafNode(0, size, NULL);
	//set the leafNode's root pointer to this instance of the B-Tree.
	root->setBTree(this);
}

//crap constructor, not even sure why its here.
//probably some silly compiler error if its not.
BTree::BTree() {
	nodeSize = 0;
}

//function for inserting a key and value into the B-Tree
int BTree::insertBTree(std::string key, std::string value) {
	//create a new value node.
	valueNode * n = new valueNode;

	//SHOULD PROBABLY HAVE SOME SORT OF ERROR CHECKING HERE TO MAKE SURE THESE STRINGS ARE VALID.
	
	//set the value and key for the valueNode
	n->value = value;
	n->key = key;
	
	//????
	int index;


	//begin traversal through nodes (recursively) until finding correct node and index to insert).
	root->traverseNode(key, root, index);
	//insert the valude node into the node at correct index.
	root->insertNode(n, index, NULL, NULL);
	
	return 0;
}

//function for deleting from the B-Tree
int BTree::deleteBtree() {
	return 0;
}
//function for setting the root of the tree (WUT).
int BTree::setRoot(componentNode * n) {
	//set the root to be the new node.
	root = n;
	return 0;
}

//function for printing the information stored in the B-Tree.
void BTree::printTree() {
		//start printing (recursively).
		root->printNode();
}
void BTree::printTreeStructure() {
	//start printing structure
	root->printStructure();
}