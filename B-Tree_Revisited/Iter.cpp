#include "BTree.h"

BTree::Iter * BTree::componentNode::makeInOrderIter() {
	class inOrderIter: public Iter{
	private:
		std::queue<componentNode* > nodeWaitingLine;
	public:
		bool isValid() {
			return !nodeWaitingLine.empty();
		}
		BTree::componentNode * currentItem() {
			return nodeWaitingLine.front();
		}
		void next() {

			compositeNode * isACompositeNode = dynamic_cast<compositeNode*>(nodeWaitingLine.front());

			if (isACompositeNode) {
				componentNode ** nodeSet = isACompositeNode->getComponentNodeSet();
				//get the nodeCount
				int nodeCount = isACompositeNode->getCurrentNodeCount();
				//go through the compositeNode
				for (int index = 0; index <= nodeCount; index++) {
					//add the componentNode specified by the index to the queue
					nodeWaitingLine.push(nodeSet[index]);
				}
			}

			nodeWaitingLine.pop();
		}
		void reset() {
			while (isValid) {
				nodeWaitingLine.pop();
			}
			nodeWaitingLine.push(root);
		}
	};
	return new inOrderIter();
}

BTree::Iter * BTree::componentNode::makeLevelOrderIter() {
	class levelOrderIter : public Iter {
	private:
		std::stack<componentNode* > nodeWaitingLine;
	public:
		bool isValid() {
			return !nodeWaitingLine.empty();
		}
		BTree::componentNode * currentItem() {
			return nodeWaitingLine.top();
		}
		void next() {

			compositeNode * isACompositeNode = dynamic_cast<compositeNode*>(nodeWaitingLine.top());

			if (isACompositeNode) {
				componentNode ** nodeSet = isACompositeNode->getComponentNodeSet();
				//get the nodeCount
				int nodeCount = isACompositeNode->getCurrentNodeCount();
				//go through the compositeNode
				for (int index = 0; index <= nodeCount; index++) {
					//add the componentNode specified by the index to the queue
					nodeWaitingLine.push(nodeSet[index]);
				}
			}

			nodeWaitingLine.pop();
		}
		void reset() {
			while (isValid) {
				nodeWaitingLine.pop();
			}
			nodeWaitingLine.push(root);
		}
	};
	return new levelOrderIter();
}

