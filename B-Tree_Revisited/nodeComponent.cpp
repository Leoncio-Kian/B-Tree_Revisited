#include "BTree.h"

//pointer to the root of the tree.
BTree *BTree::componentNode::bTreeRoot = nullptr;

//a function for traversing the component node.
int BTree::componentNode::traverseNode(std::string key, componentNode *&c, int &index) {
	//check if there are entries in the node.
	if (currentNodeCount == 0) {
		//if there aren't any then set the index to 0.
		index = 0;
		return 2;
	}

	//binary search for fast search.

	//set the index and maximum to be the highest index entry in the array.
	int index, imax = currentNodeCount - 1;
	//set the minimum to be the lowest index entry in the array.
	int imin = 0;

	//while the minimum is less than or equal to the maximum
	while (imin <= imax) {
		//set the index to be the midpoint between the minimum and maximum.
		index = (imin + ((imax - imin) / 2));
		//compare the key at the index with key put in.
		int result = (valueNodeSet[index]->key).compare(key);
		//if the result is less than zero, the key put in comes after the key at the index.
		if (result < 0) {
			//set the minimum to be the location of the index plus one.
			imin = index + 1;
		}
		//if the result if more than zero, the key put in comes before the key at the index.
		else if (result > 0) {
			//set the maximum to be the value of the index minus one.
			imax = index - 1;
		}
		//if the result is zero then the key already exists 
		else {
			//try some other key, this b tree doesn't support this mumbojumbo.
			return 1;
		}
	}
	//the minimum is where the new valueNode should be inserted, return it.
	index = imin;

	return 0;
}

//function for inserting a value node (i think).
int BTree::componentNode::insertNode(valueNode * newNode, int index, componentNode * left, componentNode * right) {
	//shift all valueNodes after the index one to the right to make space for the new valueNode.
	for (int i = currentNodeCount; i >= index; i--) {
		//shifting one valuenode to the right.
		valueNodeSet[i] = valueNodeSet[i - 1];
	}

	//add the new node to the array.
	valueNodeSet[index] = newNode;

	//increase the currentnodecount to account for the new valueNode.
	++currentNodeCount;
	//check if the component node is full.
	if (currentNodeCount == size + 1) {
		//the component is full, time to resize

		
		int countLeft = size / 2;
		int countRight = ((size + 1) / 2);
		leafNode * l = new leafNode(countLeft, size, parent);
		leafNode * r = new leafNode(countRight, size, parent);

		valueNode * m = valueNodeSet[countLeft];

		//add lower half to node l, upper half to node r

		int j, k = 0;
		for (j = 0; j < (size) / 2; j++) 
			l->setValueNode(j, valueNodeSet[j]);  
		
		j++;

		for (; j < size + 1; j++) {
			r->setValueNode(k, valueNodeSet[j]);
			k++;
		}
		//find index in parent

		if (parent) {
			int newindex;
			componentNode * placeholder = NULL;
			parent->componentNode::traverseNode(m->key, placeholder, newindex);
			l->setParent(parent);
			r->setParent(parent);
			parent->insertNode(m, newindex, l, r);
		}
		else {
			//need new root
			compositeNode * newRoot = new compositeNode(0, size, NULL);
			l->setParent((componentNode *)newRoot);
			r->setParent((componentNode *)newRoot);
			newRoot->insertNode(m, 0, l, r);
			bTreeRoot->setRoot(newRoot);
		}
	}
	return 0;
}
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

//function to print the node.
void BTree::componentNode::printNode() {
	for (int i = 0; i < currentNodeCount; i++)
 		std::cout << valueNodeSet[i]->key << std::endl;
	std::cout << currentNodeCount << std::endl;
}




BTree::leafNode::leafNode(int count, int size, componentNode * parent) {
	this->size = size;
	this->currentNodeCount = count;
	this->parent = parent;
	valueNodeSet = new valueNode*[size + 1];

	for (int i = 0; i < size + 1; i++) {
		valueNodeSet[i] = NULL;
	}
}




BTree::compositeNode::compositeNode(int count, int size, componentNode * parent) {
	this->size = size;
	this->currentNodeCount = count;
	this->parent = parent;
	valueNodeSet = new valueNode*[size + 1];
	componentNodeSet = new componentNode*[size + 3];

	for (int i = 0; i < size + 1; i++) {
		valueNodeSet[i] = NULL;
		componentNodeSet[i] = NULL;
	}
	componentNodeSet[size + 1] = NULL;
	componentNodeSet[size + 2] = NULL;
}
void BTree::compositeNode::freeCompositeNode(componentNode * n) {
	int i;
	for (i = 0; i < size; i++) {
		componentNodeSet[i] = NULL;
		valueNodeSet[i] = NULL;
	}
	componentNodeSet[++i] = NULL;
}
void BTree::compositeNode::setComponentNode(int index, componentNode * n) {
	this->componentNodeSet[index] = n;
	n = NULL;
}
int BTree::compositeNode::traverseNode(std::string key, componentNode *&c, int &imin) {
	int index, imax = currentNodeCount - 1;
	imin = 0;
	while (imin <= imax && currentNodeCount != 0) {
		index = (imin + ((imax - imin) / 2));
		int result = (((compositeNode*)c)->valueNodeSet[index]->key).compare(key);
		if (result < 0) {
			//valueArray is less than key
			imin = index + 1;
		}
		else if (result > 0) {
			//valueArry is more than key
			imax = index - 1;
		}
		else {
			//key already exists!
			return 1;
		}
	}
	c = ((compositeNode *)c)->componentNodeSet[imin];
	return c->traverseNode(key, c, imin);
}
int BTree::compositeNode::insertNode(valueNode * n, int index, componentNode * left, componentNode * right) {
	for (int i = currentNodeCount; i >= index; i--) {
		valueNodeSet[i] = valueNodeSet[i - 1];
		componentNodeSet[i + 1] = componentNodeSet[i];
	}

	valueNodeSet[index] = n;

	componentNodeSet[index] = left;
	componentNodeSet[index + 1] = right;
	
	if (++currentNodeCount == size + 1) {
		//the composite is full, time to resize
		int count1 = size / 2;
		int count2 = ((size + 1) / 2);
		compositeNode * l = new compositeNode(count1, size, parent);
		compositeNode * r = new compositeNode(count2, size, parent);

		valueNode * m = valueNodeSet[count1];

		//add lower half to node l, upper half to node r

		int j, k = 0;
		for (j = 0; j < (size + 1) / 2; j++) {
			l->setComponentNode(j, componentNodeSet[j]);
			l->setValueNode(j, valueNodeSet[j]);
		}

		l->setComponentNode(j, componentNodeSet[j]);
		j++;

		for (; j <= size + 1; j++) {
			r->setComponentNode(k, componentNodeSet[j]);
			r->setValueNode(k, valueNodeSet[j]);
			k++;
		}

		r->setComponentNode(k, componentNodeSet[j + 1]);
	

		//insert node and pairing to parent
		if (parent) {
			int newindex;
			componentNode * placeholder = NULL;
			parent->componentNode::traverseNode(m->key, placeholder, newindex);
			l->setParent(parent);
			r->setParent(parent);
			parent->insertNode(m, newindex, l, r);
		}
		else {
			//need new root
			compositeNode * newRoot = new compositeNode(0, size, NULL);
			l->setParent((componentNode *)n);
			r->setParent((componentNode *)n);
			newRoot->insertNode(m, 0, l, r);
			bTreeRoot->setRoot(newRoot);
		}
	}
	return 0;
}
int BTree::compositeNode::deleteNode() {

	return 0;
}
//setter function for setting the parent node of this node.
int BTree::componentNode::setParent(componentNode * n) {
	parent = n;
	return 0;
}
void BTree::compositeNode::printNode() {
	for (int i = 0; i < currentNodeCount; i++) {
		if (compositeNode * cn = dynamic_cast<compositeNode*> (componentNodeSet[i]))
			cn->printNode();
		else
			componentNodeSet[i]->printNode();	

		std::cout << valueNodeSet[i]->key << std::endl;
	}
	if (compositeNode * cn = dynamic_cast<compositeNode*> (componentNodeSet[currentNodeCount]))
		cn->printNode();
	else
		componentNodeSet[currentNodeCount]->printNode();
	std::cout << currentNodeCount << std::endl;
}	