#include "BTree.h"

BTree::leafNode::leafNode(int count, int size, componentNode * parent) {
	this->size = size;
	this->currentNodeCount = count;
	this->parent = parent;
	valueNodeSet = new valueNode*[size + 1];

	for (int i = 0; i < size + 1; i++) {
		valueNodeSet[i] = NULL;
	}
}
/*
//a function for traversing the component node.
int BTree::leafNode::traverseNode(std::string key, componentNode *&c, int &index) {
	//check if there are entries in the node.
	if (currentNodeCount == 0) {
		//if there aren't any then set the index to 0.
		index = 0;
		return 2;
	}

	//binary search for fast search.

	//set the index and maximum to be the highest index entry in the array.
	int position = currentNodeCount - 1, imax = currentNodeCount - 1;
	//set the minimum to be the lowest index entry in the array.
	int imin = 0;

	//while the minimum is less than or equal to the maximum
	while (imin <= imax) {
		//set the index to be the midpoint between the minimum and maximum.
		position = (imin + ((imax - imin) / 2));
		//compare the key at the index with key put in.
		int result = (valueNodeSet[position]->key).compare(key);
		//if the result is less than zero, the key put in comes after the key at the index.
		if (result < 0) {
			//set the minimum to be the location of the index plus one.
			imin = position + 1;
		}
		//if the result if more than zero, the key put in comes before the key at the index.
		else if (result > 0) {
			//set the maximum to be the value of the index minus one.
			imax = position - 1;
		}
		//if the result is zero then the key already exists 
		else {
			//try some other key, this b tree doesn't support this mumbojumbo.
			index = position;
			return 1;
		}
	}
	//the minimum is where the new valueNode should be inserted, return it.
	index = imin;

	return 0;
}
*/
//function for inserting a value node (i think).
int BTree::leafNode::insertNode(valueNode * newNode, int index, componentNode * left, componentNode * right) {
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

		//the number from the start to n/2
		int countLeft = size / 2;
		//the number from the midpoint to n.
		int countRight = ((size + 1) / 2);
		//new left node with the new current count
		leafNode * l = new leafNode(countLeft, size, parent);
		//new right node with the new current count.
		leafNode * r = new leafNode(countRight, size, parent);
		//valueNode pointer pointing to the middle of the valueNodes.
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
			parent->traverseNode(m->key, placeholder, newindex);
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
void BTree::leafNode::setSelfIter() {
	componentNode * that = this;
	class SelfIter : public Iter {
	private:
		componentNode * self;
	public:
		SelfIter(componentNode * self) {
			this->self = self;
		}
		void reset() {

		}
		void next() {

		}
		componentNode * currentItem() {

		}
		bool isValid() {

		}
	};
}

/*
//function to print the node.
void BTree::leafNode::printNode() {
	for (int i = 0; i < currentNodeCount; i++)
		std::cout << valueNodeSet[i]->key << std::endl;
	std::cout << currentNodeCount << std::endl;
}

void BTree::leafNode::printValueNodes() {
	for (int i = 0; i < currentNodeCount; i++) {
		std::cout << "|" << valueNodeSet[i]->key;
	}
	std::cout << "|" << std::endl;
}
*/