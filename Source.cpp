/*
 * Data Structures Project 4
 *
 * This project provides a class and main method for a tree data structures. SDG
 * 
 *			 author: David Gilstad
 *			created: 25 March 2019
 */
#include <iostream>
using namespace std;

/*
 * This class reperesents a tree data structure. A tree consists of nodes that hold
 * information. Nodes have a parent and children that are connected to other nodes in the
 * tree with branches. Nodes can have as many children as needed (or none), but all nodes
 * have exactly one parent node, with the exception of the root node which has none.
 */
class Tree {
	friend ostream& operator<< (ostream &s, Tree &T);
	protected:
		int* treeArray;
		int size;
	public:
		Tree();
		Tree(int numElements);
		Tree(const Tree &obj);
		~Tree();
		int LCA(int node1, int node2);
		int Parent(int child);
		int* Children(int parent);
		int* Siblings(int node);
		int Root();
		void setRoot(int rootNode);
		void setParent(int node, int parent);
		int* nodesAtLevel(int level);
		int height();
		int* Preorder();
};

Tree::Tree() {
	treeArray = new int[];
	size = 0;
}

Tree::Tree(int numElements) {
	size = numElements;
	treeArray = new int[size];
}

Tree::Tree(const Tree &obj) {
	size = obj.size;
	treeArray = new int[size];
	for (int i = 0; i < obj.size; i++)
		treeArray[i] = obj.treeArray[i];
}

Tree::~Tree() {
	delete[] treeArray;
	cout << "Tree has been deleted" << endl;
}

/*
 * Main method: Reads in information for creating a tree and prints out data using the
 * methods in the tree class.
 */
int main() {


	system("pause");
	return 0;
}