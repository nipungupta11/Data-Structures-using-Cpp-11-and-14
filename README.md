# Data-Structures-using-Cpp-11-and-14
This repository contains source code for various data structures. These are written using C++ 11 and C++14.

File Name: BinarySearchTree.cpp  
Function written:  
void insert(std::shared_ptr<BST>& root, int data)  
-Insert a node at appropriate position in Binary Tree  

void printNodesRecursively(std::shared_ptr<BST> root)  
-Print nodes recursively  
-First print root node, then left sub tree, then right sub tree  

void printNodes(std::shared_ptr<BST>& root)  
-Print nodeswithout recursion, using stack  
-First print root node, then left sub tree, then right sub tree  

void printNodesAt_K_DistanceFromRoot(std::shared_ptr<BST> root, int distance)  
-Print all nodes at K distance from Root of binary tree  
-Using queue, fetching each element and corresponding sub-element   

void printInOrderTraversal(std::shared_ptr<BST> root)  
-Function to print Binary Tree InOrder traversal  
-without recursion, using stack 

void printHeightOfTree(std::shared_ptr<BST> root)
-Function to print height of binary tree
-Used queue to store tree elements and then pops back
  
void constructBSTFromArray(std::shared_ptr<BST>& node, std::vector<int> elements)
-Function to construct a binart tree from a given input array (iteratively)
-Used queue to store and process tree nodes  

