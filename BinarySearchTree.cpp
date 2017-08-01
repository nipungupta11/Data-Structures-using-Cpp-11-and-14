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

void printNodesAt_K_DistanceFromRoot(std::shared_ptr<BST> root, int distance)
{
	if (root == nullptr)
		return;
	if (distance == 0)
		cout << root->data << endl;

	std::queue<int> elements;
	std::queue<shared_ptr<BST>> nodeToTraverse;
	
	auto pushElement = [&](shared_ptr<BST>& element)
	{
		if (element != nullptr)
		{
			elements.push(element->data);
			nodeToTraverse.emplace(element);
		}
	};

	while (distance > 0)
	{
		if (nodeToTraverse.empty())
		{
			pushElement(root->left);
			pushElement(root->right);
			--distance;
			continue;
		}

		std::queue<int> empty;
		std::swap(elements, empty);

		std::queue<shared_ptr<BST>> emptyNodeToTraverse;
		std::swap(nodeToTraverse, emptyNodeToTraverse);

		while (!emptyNodeToTraverse.empty())
		{
			auto item = emptyNodeToTraverse.front();
			emptyNodeToTraverse.pop();
			pushElement(item->left);
			pushElement(item->right);
		}
		--distance;
		continue;
	}

	while (!elements.empty())
	{
		auto item = elements.front();
		elements.pop();
		cout << item << endl;
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


void printHeightOfTree(std::shared_ptr<BST> root)
{
	if (root == nullptr)
	{
		cout << "height is 0" << endl;
		return;
	}

	std::queue<shared_ptr<BST>> nodeToTraverse;

	auto pushElement = [&](shared_ptr<BST>& element)
	{
		if (element != nullptr)
		{
			nodeToTraverse.emplace(element);
		}
	};

	int height = 0;
	do
	{
		height++;

		if (nodeToTraverse.empty())
		{
			pushElement(root->left);
			pushElement(root->right);
			continue;
		}

		std::queue<shared_ptr<BST>> emptyNodeToTraverse;
		std::swap(nodeToTraverse, emptyNodeToTraverse);

		while (!emptyNodeToTraverse.empty())
		{
			auto item = emptyNodeToTraverse.front();
			emptyNodeToTraverse.pop();
			pushElement(item->left);
			pushElement(item->right);
		}
		continue;
	} while (!nodeToTraverse.empty());
	cout << "height of tree is:" << height << endl;
}

//Retruns Binary Tree constructed from a given array
void constructBSTFromArray(std::shared_ptr<BST>& node, std::vector<int> elements)
{
  auto insertNode = [](std::shared_ptr<BST> temp, std::queue<std::shared_ptr<BST>>& qItem, int item)->bool
  {
    if (item < temp->data)
    {
      //process in left
      if (temp->left == nullptr)
      {
        temp->left = std::make_shared<BST>(item);
        return true;
      }
      qItem.emplace(temp->left);
    }
    else
    {
      if (temp->right == nullptr)
      {
        temp->right = std::make_shared<BST>(item);
        return true;
      }
      qItem.emplace(temp->right);
    }
    return false;
  };

  auto placeInBST = [&](const int& item, std::shared_ptr<BST> tempNode)
  {
    if (node == nullptr)
    {
      node = std::make_shared<BST>(item);
      return;
    }

    std::queue<std::shared_ptr<BST>> qItem;

    if (insertNode(tempNode, qItem, item))
      return;

    do
    {
      auto t = qItem.front();
      qItem.pop();
      if (insertNode(t, qItem, item))
        return;
    } while (!qItem.empty());

  };

  for (auto var : elements)
  {
    placeInBST(var, node);
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
	insert(bst, 10);
	insert(bst, 13);
	insert(bst, 600);
	insert(bst, 525);

	printNodesRecursively(bst);
	cout << "without recursion" << endl;
	printNodes(bst);
	cout << "Inorder traversal" << endl;
	printInOrderTraversal(bst);
	cout << "printNodesAt_K_DistanceFromRoot" << endl;
	printNodesAt_K_DistanceFromRoot(bst, 3);
	cout << "PrintHeightOfTree" << endl;
	printHeightOfTree(bst);
	cout << "constructBSTFromArray" << endl;
	std::vector<int> elements{ 10, 15, 13, 11, 9, 7, 16, 14 };
  	constructBSTFromArray(bst, elements);
	printNodes(bst);

	return 0;
}

