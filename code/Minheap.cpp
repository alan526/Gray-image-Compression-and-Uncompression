#include "Minheap.h"

void Minheap::insert(TreeNode* temp) {

	node[number].pixel = temp->pixel;
	node[number].fr = temp->fr;
	node[number].leftchild = temp->leftchild;
	node[number].rightchild = temp->rightchild;
	maintainHeapbottom(number);
	number++;
}

void Minheap::maintainHeapbottom(int index) {
	bool stop = true;
	while (index > 0 && (index-1)/2 >= 0 && stop) {
		int p = (index - 1) / 2;
		if (index % 2 == 0) {
			int lfr = 2 * p + 1;
			int rfr = 2 * p + 2;
			int min;
			if (node[lfr].fr > node[rfr].fr) {
				min = rfr;
			}
			else {
				min = lfr;
			}
			if (node[p].fr > node[min].fr) {
				swap(p, min);
			}
			else {
				stop = false;
			}
		}
		else {
			int lfr = 2 * p + 1;
			if (node[p].fr > node[lfr].fr) {
				swap(p, lfr);
			}
			else {
				stop = false;
			}
		}
		index = p;
	}
}

void Minheap::maintainHeaptop(int index) {
	bool stop = true;
	while (stop && (index*2+1) < number) {
		if (index * 2 + 2 < number) {
			int lfr = 2 * index + 1;
			int rfr = 2 * index + 2;
			int min;
			if (node[lfr].fr > node[rfr].fr) {
				min = rfr;
			}
			else {
				min = lfr;
			}
			if (node[index].fr > node[min].fr) {
				swap(index, min);
				index = min;
			}
			else {
				stop = false;
			}
		}
		else {
			int lfr = 2 * index + 1;
			if (node[index].fr > node[lfr].fr) {
				swap(index, lfr);
				index = lfr;
			}
			else {
				stop = false;
			}
		}
	}
}

void Minheap::swap(int left, int right) {
	TreeNode temp = node[left];
	node[left].fr = node[right].fr;
	node[left].pixel = node[right].pixel;
	node[left].leftchild = node[right].leftchild;
	node[left].rightchild = node[right].rightchild;
	node[right].fr = temp.fr;
	node[right].pixel = temp.pixel;
	node[right].leftchild = temp.leftchild;
	node[right].rightchild = temp.rightchild;
}

void Minheap::display()const {
	for (int i = 0; i < number; i++) {
		cout << node[i].pixel << " => " << node[i].fr << endl;
	}
}

TreeNode Minheap::popmin() {
	TreeNode temp = node[0];
	swap(0, number - 1);
	number--;
	maintainHeaptop(0);
	return(temp);
}

int Minheap::getNumber() {
	return(number);
}

void Minheap::createHF() {
	if (number >= 2) {
		TreeNode min1 = popmin();
		TreeNode min2 = popmin();
		TreeNode* temp = new TreeNode(-1, min1.getfr() + min2.getfr());
		TreeNode* right = new TreeNode(min1.getpixel(), min1.getfr(), min1.rightchild, min1.leftchild);
		TreeNode* left = new TreeNode(min2.getpixel(), min2.getfr(), min2.rightchild, min2.leftchild);
		temp->leftchild = left;
		temp->rightchild = right;
		insert(temp);
	}
}

void Minheap::preorderCode(TreeNode* current, string code, string table[256]) {
	if (current) {
		if (current->getpixel() >= 0) {
			table[current->pixel] = code;
		}
		preorderCode(current->leftchild, code + "0", table);
		preorderCode(current->rightchild, code + "1", table);
	}
}

void Minheap::inorder(TreeNode* current) {
	if (current) {
		inorder(current->leftchild);
		cout << current->pixel << " => " << current->fr << endl;
		inorder(current->rightchild);
	}
}

void Minheap::dishf() {
	inorder(&node[0]);
}

void Minheap::encode(string table[256]) {
	preorderCode(&node[0], "", table);

}

TreeNode Minheap::getNode(int index) {
	return(node[index]);
}

string Minheap::searchpixel(string totalcode) {
	TreeNode* current = &node[0];
	string output = "";
	for (int i = 0; i < totalcode.length(); i++) {
		if (totalcode[i] == '0') {
			current = current->leftchild;
		}
		else {
			current = current->rightchild;
		}
		if (current == nullptr) {
			current = &node[0];
		}
		else if (current->pixel >= 0) {
			output += to_string(current->pixel) + " ";
			current = &node[0];
		}
	}
	return(output);
}
