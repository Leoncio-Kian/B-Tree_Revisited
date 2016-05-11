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

	//create a pointer for traversal
	componentNode * P_traversalNode = root;

	//create a new pointer and dynamic cast the root to it.
	compositeNode * rootCompositeNode = dynamic_cast<compositeNode*> (root);
	//if its a composite node the pointer will have a value.
	if (rootCompositeNode) {
		//begin traversal through nodes (recursively) until finding correct node and index to insert).
		rootCompositeNode->traverseNode(key, P_traversalNode, index);
		//insert the valude node into the node at correct index.
		P_traversalNode->insertNode(n, index, NULL, NULL);
	}
	//otherwise the node is a leaf node (or some error occurred and there is no root).
	else {
		//YOU SHOULD CHECK TO MAKE SURE THERE IS A ROOT.

		//traverse the leaf node for the correct index to insert the valueNode.
		//CHECK WHY P_traversalNode IS NEEDED
		root->traverseNode(key, P_traversalNode, index);
		//insert the valueNode at the correct index.
		root->insertNode(n, index, NULL, NULL);
	}
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
	//create a new compositeNode pointer and dynamiccast the root to it.
	compositeNode * rootCompositeNode = dynamic_cast<compositeNode*> (root);
	//if the compositeNode has a value then the root is a compositeNode. 
	if (rootCompositeNode)
		//start printing (recursively).
		rootCompositeNode->printNode();
	//else the root is a leaf node and can be treated as is.
	else
		//start printing (recursively).
		root->printNode();
}