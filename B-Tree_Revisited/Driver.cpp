#include "BTree.h"
//#include <iostream>

class Driver {
private:
	BTree * btree;
public:
	Driver(){};
	Driver(int size) {
		btree = new BTree(size);
	}
	void run() {
		int i = 0, counter = 0;
		std::string key, value;

		while (i != -1) {
			std::cout << "enter what you would like to do" << std::endl;
			std::cin >> i;
			switch (i) {
				case -1:
					break;
				case 1:
					//forget adding the value, the value doesnt matter for testing.
					std::cin >> key;
					btree->insertBTree(key, std::to_string(counter++));
					break;
				case 2:
					btree->printTree();
					break;
			}
		}
	}
};

int main() {
	Driver driver;
	driver = Driver(4);
	driver.run();


	return 0;
}