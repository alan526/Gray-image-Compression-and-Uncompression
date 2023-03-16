#ifndef _TREENODE_H_
#define _TREENODE_H_

#include <string>

using namespace std;

class TreeNode {

public:
	TreeNode();
	TreeNode(int newpixel, int newfr);
	TreeNode(int newpixel, int newfr, TreeNode* right, TreeNode* left);
	int getpixel();
	int getfr();
private:
	int pixel;
	int fr;
	TreeNode* rightchild;
	TreeNode* leftchild;

	friend class Minheap;
};
#endif // !TreeNode
#pragma once
