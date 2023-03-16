#include "TreeNode.h"

TreeNode::TreeNode() {

}

TreeNode::TreeNode(int newpixel, int newfr) : pixel(newpixel), fr(newfr), rightchild(nullptr), leftchild(nullptr){

}

TreeNode::TreeNode(int newpixel, int newfr, TreeNode* right, TreeNode* left): pixel(newpixel), fr(newfr), rightchild(right), leftchild(left) {

}

int TreeNode::getpixel() {
	return(pixel);
}

int TreeNode::getfr() {
	return(fr);
}