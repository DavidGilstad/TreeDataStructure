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
		int LCA(int n1, int n2);
		int Parent(int child);
		int* Children(int parent);
		int* Siblings(int node);
		int Root();
		void setRoot(int rootNode);
		void setParent(int node, int parent);
		int Level(int node);
		int* nodesAtLevel(int level);
		int height();
		int* Preorder();

		void print();
};

void Tree::print() {
	cout << "0->" << treeArray[0];
	for (int i = 1; i < size; i++)
		cout << ",   " << i << "->" << treeArray[i];
	cout << endl;
}

ostream& operator<< (ostream &s, Tree &T) {
	s << "0->" << T.treeArray[0];
	for (int i = 1; i < T.size; i++)
		s << ",   " << i << "->" << T.treeArray[i];
	s << endl;
	return s;
}

Tree::Tree() {
	treeArray = new int[0];
	size = 0;
}

Tree::Tree(int numElements) {
	size = numElements;
	treeArray = new int[numElements];
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

int Tree::LCA(int n1, int n2) {
	int temp = n2;
	while (n1 != -1) {
		while (n2 != -1) {
			if (n1 == n2) return n1;
			else n2 = Parent(n2);
		}
		n2 = temp;
		n1 = Parent(n1);
	}
	return Root();
}

int Tree::Parent(int child) {
	return treeArray[child];
}

int* Tree::Children(int parent) {
	int numChildren = 0;
	for (int i = 0; i < size; i++)
		if (parent == treeArray[i]) ++numChildren;
	int *result = new int[numChildren];
	int resultIndex = 0;
	for (int i = 0; i < size; i++)
		if (parent == treeArray[i]) result[resultIndex++] = i;
	return result;
}

int* Tree::Siblings(int node) {
	int parent = Parent(node);
	int numChildren = -1; // account for this node
	for (int i = 0; i < size; i++)
		if (parent == treeArray[i]) ++numChildren;
	int *result = new int[numChildren];
	int resultIndex = 0;
	for (int i = 0; i < size; i++)
		if (parent == treeArray[i] && i != node) result[resultIndex++] = i;
	return result;
}

int Tree::Root() {
	for (int i = 0; i < size; i++)
		if (Parent(i) == -1) return i;
}

void Tree::setRoot(int rootNode) {
	treeArray[rootNode] = -1;
}

void Tree::setParent(int node, int parent) {
	treeArray[node] = parent;
}

int Tree::Level(int node) {
	int level = 0;
	do {
		level++;
		node = Parent(node);
	} while (node != -1);
	return level;
}

int* Tree::nodesAtLevel(int level) {
	int numOnLevel = 0;
	for (int i = 0; i < size; i++)
		if (level == Level(i)) numOnLevel++;
	int* result = new int[numOnLevel];
	for (int i = 0, index = 0; i < size; i++)
		if (level == Level(i)) result[index++] = i;
	return result;
}

int Tree::height() {
	int max = 1;
	for (int i = 0; i < size; i++)
		if (Level(i) > max) max = Level(i);
	return max;
}

/*
 * Main method: Reads in information for creating a tree and prints out data using the
 * methods in the tree class.
 */
int main() {
	
	Tree *T = new Tree(11);
	T->setRoot(6);
	T->setParent(0, 6);
	T->setParent(5, 6);
	T->setParent(4, 6);
	T->setParent(1, 0);
	T->setParent(2, 0);
	T->setParent(3, 5);
	T->setParent(7, 4);
	T->setParent(8, 7);
	T->setParent(9, 7);
	T->setParent(10, 7);

	cout << "The tree is: " << endl << *T << endl;

	cout << "The root is: " << T->Root() << endl;
	cout << "The height is: " << T->height() << endl;
	cout << "The level of node 2 is: " << T->Level(2) << endl;
	cout << "The least common ancestor of 8 and 3 is: " << T->LCA(8, 3) << endl;
	T->setParent(3, 4);
	cout << "The new LCA of 8 and 3 is: " << T->LCA(3, 8) << endl;
	cout << "The siblings of 9 are: " << T->Siblings(9)[0] << ", " << T->Siblings(9)[1] << endl;
	

	system("pause");
	return 0;
}
