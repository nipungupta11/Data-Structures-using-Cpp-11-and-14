// BinarySearchTree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <memory>
#include <iostream>
#include <stack>
#include <queue>
using namespace std;

struct BST
{
	int data;
	std::shared_ptr<BST> left;
	std::shared_ptr<BST> right;
};


void insert(std::shared_ptr<BST>& root, int data)
{
	if (root == nullptr)
	{
		root = std::make_shared<BST>();
		root->data = data;
		return;
	}
	if (data < root->data)
		insert(root->left, data);
	else
		insert(root->right, data);
}


void printNodesRecursively(std::shared_ptr<BST> root)
{
	if (root == nullptr)
	{
		return;
	}
	std::cout << root->data << endl;
	
	printNodesRecursively(root->left);
	printNodesRecursively(root->right);
}

//without recursion using stack
void printNodes(std::shared_ptr<BST>& root)
{
	if (root == nullptr)
	{
		return;
	}
	std::cout << root->data << endl;

	std::stack<std::shared_ptr<BST>> stackBST;

	auto pushToStack = [&](shared_ptr<BST> item)
	{
		if (item != nullptr)
			stackBST.push(item);
	};

	pushToStack(root->right);
	pushToStack(root->left);

	while (!stackBST.empty())
	{
		std::shared_ptr<BST> bstItem = stackBST.top();
		stackBST.pop();
		cout << bstItem->data << endl;
		pushToStack(bstItem->right);
		pushToStack(bstItem->left);
	}
}

//Assuming tree has all positive elements
void printNodesAt_K_DistanceFromRoot(std::shared_ptr<BST> root, int distance)
{
	if (root == nullptr)
		return;
	if (distance == 0)
		cout << root->data << endl;

	std::shared_ptr<BST> Left = root->left;
	std::shared_ptr<BST> Right = root->right;
	std::queue<int> elements;
	

	int leftNode = -1, rightNode = -1;
	while (distance > 0)
	{
		std::queue<int> empty;
		std::swap(elements, empty);
		if (Left != nullptr)
			elements.push(Left->data);

		if (Right != nullptr)
			elements.push(Right->data);

		--distance;
	}
}

//without recursion
void printInOrderTraversal(std::shared_ptr<BST> root)
{
	if (root == nullptr)
	{
		return;
	}

	std::stack<std::shared_ptr<BST>> stackBST;
	auto pushToStack = [&](shared_ptr<BST> item)
	{
		if (item != nullptr)
			stackBST.emplace(item);
	};

	pushToStack(root);

	//push only left item
	auto pushLeft = [&](shared_ptr<BST> item)
	{
		while (item != nullptr)
		{
			pushToStack(item);
			item = item->left;
		}
	};

	pushLeft(root->left);

	while (!stackBST.empty())
	{
		auto item = stackBST.top();
		cout << item->data << endl;
		stackBST.pop();
		if (item->right == nullptr)
		{
			continue;
		}
		//right elemet exist, push onto stack and puish its left items as well until left is nullptr
		pushToStack(item->right);
		pushLeft(item->right->left);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	std::shared_ptr<BST> bst;
	insert(bst, 50);
	insert(bst, 500);
	insert(bst, 5);
	insert(bst, 15);
	insert(bst, 25);
	insert(bst, 75);
	insert(bst, 555);
	printNodesRecursively(bst);
	cout << "without recursion" << endl;
	printNodes(bst);
	cout << "Inorder traversal" << endl;
	printInOrderTraversal(bst);
	return 0;
}

