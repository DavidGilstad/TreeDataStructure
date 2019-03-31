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
 * have exactly one parent node, with the exception of the root node which has no parent.
 */
class Tree {
	friend ostream& operator<< (ostream &s, Tree &T);
protected:
	int size, // # of nodes in the tree
		root, // root element of the tree
		*treeArray; // array holding all elements and their parent
public:
	Tree();
	Tree(int numElements);
	Tree(const Tree &obj);
	~Tree();
	int Root();
	int Parent(int child);
	int numChildren(int parent);
	int Level(int node);
	int height();
	int LCA(int n1, int n2);
	void setRoot(int rootNode);
	void setParent(int node, int parent);
	void Children(int parent);
	void Siblings(int node);
	void nodesAtLevel(int level);
	void preorder();
};

/* Outputs the tree in the form "parent->child, parent->child,..., parent->child". */
ostream& operator<< (ostream &s, Tree &T) {
	s << "0->" << T.treeArray[0];
	for (int i = 1; i < T.size; i++)
		s << "  " << i << "->" << T.treeArray[i];
	return s;
}

/* Default constructor that creates a tree of size 0. */
Tree::Tree() {
	treeArray = new int[0];
	size = 0;
}

/* Non-default constructor that creates a tree with given # of elements. */
Tree::Tree(int numElements) {
	size = numElements;
	treeArray = new int[numElements];
}

/* Copy constructor. */
Tree::Tree(const Tree &obj) {
	size = obj.size;
	treeArray = new int[size];
	for (int i = 0; i < obj.size; i++)
		treeArray[i] = obj.treeArray[i];
}

/* Destructor. */
Tree::~Tree() {
	delete[] treeArray;
	cout << "Tree has been deleted" << endl;
}

/* Returns the root of the tree. */
int Tree::Root() {
	return root;
}

/* Returns the parent of the given node. */
int Tree::Parent(int child) {
	if (child >= size) {
		// throw youSuckException();
		return 0;
	}
	else if (child < 0)
		return -1;
	return treeArray[child];
}

/* Tells how many children a given node has. */
int Tree::numChildren(int parent) {
	int numChildren = 0;
	for (int i = 0; i < size; i++)
		if (parent == treeArray[i]) ++numChildren;
	return numChildren;
}

/* Returns what level the given node is on. */
int Tree::Level(int node) {
	int level = 0;
	do {
		level++;
		node = Parent(node);
	} while (node != -1);
	return level;
}

/* Returns the height of the tree. */
int Tree::height() {
	int max = 0;
	for (int i = 0; i < size; i++)
		if (Level(i) > max) max = Level(i);
	return max;
}

/* Returns the "youngest" node in common with both n1 and n2. */
int Tree::LCA(int n1, int n2) {
	int temp = n2;
	while (n1 != -1) {
		while (n2 != -1) {
			if (n1 == n2) return n1;
			else n2 = Parent(n2);
		}
		n2 = temp;
		n1 = Parent(n1);
	} return root;
}

/* Sets the root to the given node. */
void Tree::setRoot(int rootNode) {
	root = rootNode;
}

/* Gives the given node the given parent. */
void Tree::setParent(int node, int parent) {
	treeArray[node] = parent;
}

void Tree::Children(int parent) {
	for (int i = 0; i < size; i++)
		if (parent == treeArray[i]) cout << i << " ";
	cout << endl;
}

void Tree::Siblings(int node) {
	int parent = Parent(node);
	for (int i = 0, index = 0; i < size; i++)
		if (parent == treeArray[i] && i != node) cout << i << " ";
	cout << endl;
}

void Tree::nodesAtLevel(int level) {
	for (int i = 0; i < size; i++)
		if (level == Level(i)) cout << i << " ";
	cout << endl;
}

void Tree::preorder() {
	int currRoot = root, currNode, index = 0, numOutput = 1, *used = new int[size];
	for (int i = 0; i < size; i++) used[i] = 0;
	cout << currRoot << " ";
	used[root] = 1;
	while (numOutput < size) {
		if (Parent(index) == currRoot && used[index] != 1) {
			cout << index << " ";
			used[index] = 1;
			numOutput++;
			currRoot = index;
			index = 0;
		}
		else {
			index++;
			if (index >= size) {
				currRoot = Parent(currRoot);
				index = 0;
			}
		}
	}
	cout << endl;
}

/*
 * Main method: Reads in information for creating a tree and
 * prints out data using the methods in the tree class.
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

	cout << "The children of node 12 are: " << endl;
	myTree->Children(12);
	cout << "The children of node 10 are: " << endl;
	myTree->Children(10);
	cout << "The siblings of node 3 are: " << endl;
	myTree->Siblings(3);
	cout << "The siblings of node 12 are: " << endl;
	myTree->Siblings(12);
	cout << "The nodes at level 3 are: " << endl;
	myTree->nodesAtLevel(3);

	cout << "The height of the tree is: " << myTree->height() << endl;
	cout << "The level of node 3 in the tree is: " << myTree->Level(3) << endl;
	cout << "The level of node 12 in the tree is: " << myTree->Level(12) << endl;
	cout << "The preorder of the tree is: " << endl;
	myTree->preorder();

	delete myTree;
	delete newTree;
	system("pause");
	return 0;
}