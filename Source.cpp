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
	friend ostream& operator<< (ostream &s, int *A);
	friend ostream& operator<< (ostream &s, Tree &T);
	protected:
		int size, root, *treeArray;
	public:
		Tree();
		Tree(int numElements);
		Tree(const Tree &obj);
		~Tree();
		int LCA(int n1, int n2);
		int Parent(int child);
		int* Children(int parent);
		int numChildren(int parent);
		int* Siblings(int node);
		int Root();
		void setRoot(int rootNode);
		void setParent(int node, int parent);
		int Level(int node);
		int* nodesAtLevel(int level);
		int height();
		int* Preorder();
};


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
	int *result = new int[numChildren(parent)];
	int resultIndex = 0;
	for (int i = 0; i < size; i++)
		if (parent == treeArray[i]) result[resultIndex++] = i;
	return result;
}

int Tree::numChildren(int parent) {
	int numChildren = 0;
	for (int i = 0; i < size; i++)
		if (parent == treeArray[i]) ++numChildren;
	return numChildren;
}

int* Tree::Siblings(int node) {
	int parent = Parent(node);
	int *result = new int[numChildren(parent) - 1];
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
	root = rootNode;
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
	int max = 0;
	for (int i = 0; i < size; i++)
		if (Level(i) > max) max = Level(i);
	return max;
}

int* Tree::Preorder() {

}

/*
 * Main method: Reads in information for creating a tree and prints out data using the
 * methods in the tree class.
 */
int main() {
	Tree *myTree;
	int numNodes, node, parent;

	cin >> numNodes;
	myTree = new Tree(numNodes);
	for (int i = 0; i < numNodes; i++) {
		cin >> node >> parent;
		myTree->setParent(node, parent);
		if (parent == -1) myTree->setRoot(node);
	}

	cout << "The tree read in is: " << endl << *myTree << endl;
	Tree *newTree = new Tree(*myTree);
	cout << "The copied tree is: " << endl << *newTree << endl;
	cout << "The root of the tree is: " << myTree->Root() << endl;

	cout << "The least common ancesor of nodes 3 and 8 is: " << newTree->LCA(3, 8) << endl;
	cout << "The least common ancesor of nodes 13 and 8 is: " << newTree->LCA(13, 8) << endl;
	cout << "The least common ancesor of nodes 13 and 11 is: " << newTree->LCA(11, 13) << endl;

	cout << "The children of node 12 is: " << myTree->Children(12) << endl;
	cout << "The children of node 10 is: " << myTree->Children(10) << endl;

	cout << "The siblings of node 3 is: " << myTree->Siblings(3) << endl;
	cout << "The siblings of node 12 is: " << myTree->Siblings(12) << endl;

	cout << "The nodes at level 3 are: " << myTree->nodesAtLevel(3) << endl;
	cout << "The height of the tree is: " << myTree->height() << endl;

	cout << "The level of node 3 in the tree is: " << myTree->Level(3) << endl;
	cout << "The level of node 12 in the tree is: " << myTree->Level(12) << endl;

	cout << "The preorder traversal of the tree is: " << endl;
	cout << myTree->Preorder() << endl;

	delete myTree;
	delete newTree;

	system("pause");
	return 0;
}