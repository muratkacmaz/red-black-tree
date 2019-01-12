/*
	Murat Kaçmaz
	150140052
*/

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <ctime>

#define RED 0
#define	BLACK 1

using namespace std;


struct Node
{
	string gender;
	int age;
	string key;
	int color;
	int numWomanSize; // Subtreelerdeki toplam kadin sayisi
	int numManSize; // Subtreelerdeki toplam erkek sayisi
	int numWomanRank; // Solunda kalan toplam kadin sayisi
	int numManRank; // solunda kalan toplam erkek sayisi
	Node* left;
	Node* right;
	Node* parent;

	Node(string name, string gend, int agee)
	{
		this->key = name;
		this->gender = gend;
		this->age = agee;
		this->color = RED;
		this->left = this->right = this->parent = NULL;
		this->numManRank = this->numManSize = 0;
		this->numWomanRank = this->numWomanSize = 0;
	}

	Node()
	{
		this->key = " ";
		this->gender = " ";
		this->age = 0;
		this->color = RED;
		this->left = this->right = this->parent = NULL;
		this->numManRank = this->numManSize = 0;
		this->numWomanRank = this->numWomanSize = 0;
	}
};



class RBTree
{
	Node* root;
public:

	RBTree() { this->root = NULL; }

	int numWomenSize(Node*); // suubtreelerdeki kadýný buluyor
	int numMenSize(Node*);
	void rankFix(Node*);
	void num_woman(int);
	void num_man(int);
	void treeInsert(Node*);
	void treeFix(Node*);
	void inOrderPrint(Node*, int);
	void leftRotate(Node*);
	void rightRotate(Node*);
	void print();

};



int RBTree::numWomenSize(Node* node) // suubtreelerdeki toplam kadýný buluyor
{
	if (node == NULL) { return 0; }
	if (node->gender != "F")
	{
		node->numWomanRank = numWomenSize(node->left);
		node->numWomanSize = node->numWomanRank + numWomenSize(node->right);

		return node->numWomanSize;
	}
	else
	{
		node->numWomanRank = numWomenSize(node->left) + 1;
		node->numWomanSize = node->numWomanRank + numWomenSize(node->right);
		return node->numWomanSize;
	}
}

int RBTree::numMenSize(Node* node)
{
	if (node == NULL) { return 0; }
	if (node->gender != "M")
	{
		node->numManRank = numMenSize(node->left);
		node->numManSize = node->numManRank + numMenSize(node->right);
		return	node->numManSize;
	}
	else
	{
		node->numManRank = numMenSize(node->left) + 1;
		node->numManSize = node->numManRank + numMenSize(node->right);
		return	node->numManSize;
	}

}


void RBTree::num_woman(int value)
{
	Node* temp = root;
	cout << value << "rd woman  : ";
	while (1)
	{
		if (value == temp->numWomanRank)
		{
			if (temp->gender == "F")
			{
				cout << temp->key << endl;
				break;
			}
			else temp = temp->left;
		}

		else if (value < temp->numWomanRank)
		{
			temp = temp->left;
		}

		else
		{
			value = value - temp->numWomanRank;
			temp = temp->right;
		}

	}

}


void RBTree::num_man(int value)
{

	Node* temp = root;
	cout << value << "th man : ";
	while (1)
	{
		if (value == temp->numManRank)
		{
			if (temp->gender == "M")
			{
				cout << temp->key << endl;
				break;
			}
			else temp = temp->left;
		}

		else if (value < temp->numManRank)
		{
			temp = temp->left;
		}

		else
		{
			value = value - temp->numManRank;
			temp = temp->right;
		}

	}

}






void RBTree::treeInsert(Node* node)

{
	Node* temp = new Node;
	if (root == NULL)
	{
		root = node;
	}


	else
	{
		temp = root;

		while (1)
		{
			if (strcmp(temp->key.c_str(), node->key.c_str()) > 0)
			{
				if (!temp->left)
				{
					temp->left = new Node;
					temp->left = node;
					node->parent = temp;
					break;

				}

				else
				{
					temp = temp->left;
					continue;
				}

			}
			else if (strcmp(temp->key.c_str(), node->key.c_str()) < 0)
			{
				if (!temp->right)
				{
					temp->right = new Node;
					temp->right = node;
					node->parent = temp;
					break;
				}
				else
				{
					temp = temp->right;
					continue;
				}
			}


		} /// while
	}

	treeFix(node);

	root->numWomanSize = numWomenSize(root);
	root->numManSize = numMenSize(root);

	return;


}


void RBTree::treeFix(Node* node)
{
	if (strcmp(root->key.c_str(), node->key.c_str()) == 0)
	{
		root->color = BLACK;
	}

	while (node->parent != NULL && node->parent->color == RED && node != root)
	{


		if (node->parent == node->parent->parent->left)
		{
			Node* uncle = node->parent->parent->right;


			if (uncle == NULL || uncle->color == BLACK)
			{
				if (node == node->parent->right)
				{
					node = node->parent;
					leftRotate(node);
				}
				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				rightRotate(node->parent->parent);

			}
			else
			{
				node->parent->color = BLACK;
				uncle->color = BLACK;
				node->parent->parent->color = RED;
				node = node->parent->parent;
			}
		}
		else
		{
			Node* uncle = node->parent->parent->left;

			if (uncle == NULL || uncle->color == BLACK)
			{
				if (node == node->parent->left)
				{
					node = node->parent;
					rightRotate(node);
				}
				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				leftRotate(node->parent->parent);
			}
			else
			{
				node->parent->color = BLACK;
				uncle->color = BLACK;
				node->parent->parent->color = RED;
				node = node->parent->parent;
			}//else 2
		}// else1

		root->color = BLACK;
	}// while




}

void RBTree::leftRotate(Node* node)
{
	if (node->right != NULL)
	{
		Node* child = node->right;

		if (child->left == NULL)
		{
			node->right = NULL;
		}
		else
		{
			node->right = child->left;
			child->left->parent = node;
		}

		if (node->parent == NULL)
		{
			root = child;
		}
		else
		{
			child->parent = node->parent;
			if (node == node->parent->right)
			{
				node->parent->right = child;
			}
			else
			{
				node->parent->left = child;
			}
		}
		child->left = node;
		node->parent = child;

	}

	else return;
}

void RBTree::rightRotate(Node* node)
{
	if (node->left != NULL)
	{
		Node* child = node->left;

		if (child->right == NULL)
		{
			node->left = NULL;
		}
		else
		{
			node->left = child->right;
			child->right->parent = node;
		}

		if (node->parent == NULL)
		{
			root = child;
		}
		else
		{
			child->parent = node->parent;
			if (node == node->parent->left)
			{
				node->parent->left = child;
			}
			else
			{
				node->parent->right = child;
			}
		}
		child->right = node;
		node->parent = child;

	}

	else return;


}

void RBTree::print()
{
	inOrderPrint(root, 0);

}

void RBTree::inOrderPrint(Node* root, int tab_value)
{

	if (root->left)
	{
		inOrderPrint(root->left, tab_value + 1);
	}
	if (root->color == RED)
	{
		for (int i = 0; i < tab_value; i++)
		{
			cout << "\t";
		}
		cout << "|----";

		cout << "(R)" << root->key << "-" << root->age << "-" << root->gender << endl;

	}
	else
	{
		for (int i = 0; i < tab_value; i++)
		{
			cout << "\t";
		}
		if (tab_value>0)
			cout << "|----";

		cout << "(B)" << root->key << "-" << root->age << "-" << root->gender << endl;

	}

	if (root->right)
	{

		inOrderPrint(root->right, tab_value + 1);
	}
}



int main(int argc, char* argv[])
{
	vector<Node*> person_array;
	Node *n;
	RBTree tree;
	string name,Gender,Age;
	ifstream fileRead;
	fileRead.open(argv[1]);
	string lineRead;
	int i;
	while (getline(fileRead, lineRead))
	{
		i = 0;
		istringstream iss(lineRead);
		getline(iss, name, '\t');
		getline(iss, Gender, '\t');
		getline(iss, Age, '\n');

		
		int agee = atoi(Age.c_str());

		n = new Node(name, Gender, agee);

		
		person_array.push_back(n);
	}
	fileRead.close();
	

	for (int i = 0; i < person_array.size(); i++)
	{
		tree.treeInsert(person_array[i]);
	}


	tree.print();
	cout << endl;

	tree.num_woman(3);
	tree.num_man(4);

	return 0;


}
