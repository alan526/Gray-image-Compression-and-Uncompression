#ifndef _MINHEAP_H_
#define _MINHEAP_H_

#include "TreeNode.h"
#include <iostream>

using namespace std;

class Minheap
{
public:
	void insert(TreeNode* temp); // insert node to minheap 
	void maintainHeaptop(int index); // maintain minheap from top 
	void maintainHeapbottom(int index); // maintain minheap from bottom
	void swap(int left, int right); // change node values
	void display() const; // display all node in minheap
	int getNumber();
	TreeNode popmin(); // pop out the minimum node
	void createHF(); // use to create huffman tree
	void preorderCode(TreeNode* current, string code, string table[256]); // create huffman code
	void inorder(TreeNode* current);
	void dishf();
	void encode(string table[256]); // create huffman code
	TreeNode getNode(int index);
	string searchpixel(string totalcode); // change huffman code to its pixel
private:
	TreeNode node[256];
	int number = 0;
};


#endif // !_MINHEAP_H_
#pragma once
