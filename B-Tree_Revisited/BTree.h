#ifndef BTREE_H
#define BTREE_H


#include <string>
#include <iostream>
class BTree {
private:
	int nodeSize;
	//valueNodes are the nodes that contain values and keys. they are stored in leaf/component nodes.
	struct valueNode {
		std::string value;
		std::string key;
	};
	//component nodes are the abstract class that composite and leaf nodes extend from.
	//componentNode references can refer to either composite or leaf nodes.
	//this follows the composite pattern.
	class componentNode {
	protected:
		//pointer to the parent node of this node.
		componentNode * parent;
		//pointer to the set of pointers to the valuenodes.
		valueNode ** valueNodeSet;
		//pointer to the root of the tree.
		static BTree * bTreeRoot;
		//a count of the number of nodes in use currently.
		int currentNodeCount;				
		//the maximum size that a node can be.
		int size;
	public:
		//a setter function for setting valueNodes.
		void setValueNode(int index, valueNode * n);
		
		virtual int traverseNode(std::string key, componentNode *&c, int &index)=0;
		//function for inserting a value node (i think).
		virtual int insertNode(valueNode * newNode, int index, componentNode * left, componentNode * right) = 0;
		//function for deleting a value node (i think).
		virtual int deleteNode();
		//setter function for setting the parent node of this node.
		int getCurrentNodeCount(){ return currentNodeCOunt;	}
		int setParent(componentNode * n);
		//setter function for setting the root of the tree (this doesnt make any sense LOL).
		void setBTree(BTree * b);
		//function to print the node.
		virtual void printNode() = 0;
		//function for printing the value nodes stored
		virtual void printValueNodes() = 0;
	};

	//leaf nodes are the nodes that are always at the bottom. The extend from componentNodes.
	//due to the nature of B-Trees all leaf nodes are at the same level.
	class leafNode :public componentNode {
	public:

		leafNode(int count, int size, componentNode * parent);
		//a function for traversing the component node.
		int traverseNode(std::string key, componentNode *&c, int &index);
		//function for inserting a value node (i think).
		int insertNode(valueNode * newNode, int index, componentNode * left, componentNode * right);
		void printNode();
		void printValueNodes();
	};

	//compositeNodes comprise the majority of the tree (other than the bottom layer).
	//when a new layer is needed, a compositeNode layer is added to the tree.
	//compositeNodes extend from componentNodes.
	class compositeNode :public componentNode {
	private:
		//pointer to the set of pointers to the components of the layer below it.
		componentNode ** componentNodeSet;
	public:
		//constructor
		compositeNode(int count, int size, componentNode * parent);
		//im not sure what this does LEL
		void freeCompositeNode(componentNode * n);
		//a setter function for setting a componentNode in an index.
		void setComponentNode(int index, componentNode * n);
		//a function fro traversing a node.
		int traverseNode(std::string key, componentNode *&c, int &index);
		//a function for inserting a node.
		int insertNode(valueNode * n, int index, componentNode * left, componentNode * right);
		//a function for deleting a node.
		int deleteNode();
		//a function for printing the information in this node.
		void printNode();
		void printValueNodes();
		componentNode ** getComponentNodeSet();
	};
	template<typename T>
class Iter {
	virtual bool isValid() = 0;
	virtual T currentItem() = 0;
	virtual void next() = 0;
	virtual void reset() = 0;
}


	//pointer to the root of the tree.
	componentNode * root;

public:
	//constructor
	BTree();
	//constructor
	BTree(int size);
	//function for inserting a key and value into the B-Tree
	int insertBTree(std::string key, std::string value);
	//function for deleting from the B-Tree
	int deleteBtree();
	//function for setting the root of the tree (WUT).
	int setRoot(componentNode * n);
	//function for printing the information stored in the B-Tree.
	void printTree();
	void printTreeStructure();
};

#endif /* BTREE_H*/