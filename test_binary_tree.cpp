// test_binary_tree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
// tree_example_wd.cpp
// compile with
// c++ -o t_e_wd tree_example_wd.cpp -std=c++11
// execute with
// ./t_e_wd
//
// This code contains the function that deletes a node from the tree.
//
#include<iostream>
#include<stdexcept>
using namespace std;

typedef long int myint;
class Frac {
	friend ostream& operator<<(ostream& , const Frac& );
private:
	myint num;
	myint den;
public:
	Frac(const myint& = 0, const myint& = 1);
	Frac(const Frac&);
	void operator=(const Frac&);
	myint getNum() const;
	myint getDen() const;
	void setNum(const myint &);
	void setDen(const myint &);
	myint operator<(const Frac &) const;
	myint operator>(const Frac &) const;

};
Frac::Frac(const myint& _num, const myint &_den) {
	num = _num;
	den = _den;
	if (den == 0) { num = 0; den = 1; }
	if (den<0) { num *= -1; den *= -1; }
}
Frac::Frac(const Frac& _copyFrom) {
	num = _copyFrom.getNum();
	den = _copyFrom.getDen();
}
myint Frac::getNum() const { return num; }
myint Frac::getDen() const { return den; }
void Frac::setNum(const myint & _n) { num = _n; }
void Frac::setDen(const myint & _d) {
	den = _d;
	if (den == 0) { num = 0; den = 1; }
	if (den<0) { num *= -1; den *= -1; }
}
void Frac::operator=(const Frac & _copyFrom) {
	den = _copyFrom.getDen();
	num = _copyFrom.getNum();
}
myint Frac::operator<(const Frac & _cW) const {
	if (num * _cW.getDen() < den * _cW.getNum()) {
		return 1;
	}
	return 0;
}
myint Frac::operator>(const Frac &_cW) const {
	if (num * _cW.getDen() > den * _cW.getNum()) {
		return 1;
	}
	return 0;
}

class TNode {
	friend ostream& operator<<(ostream& , TNode* );
public:
	Frac value;
	TNode * lChild;
	TNode * rChild;
	TNode();

};
TNode::TNode() {
	lChild = nullptr;
	rChild = nullptr;
}

void insert(TNode*& root, const Frac& fr) {
	if (root == nullptr) {
		root = new TNode;
		root->value = fr;
	}
	else {
		if (fr<root->value) { insert(root->lChild, fr); }
		if (fr>root->value) { insert(root->rChild, fr); }
	}
}
void insert(TNode*& root, const int& b, const int&c = 1) {
	Frac fr(b, c);
	insert(root, fr);
}

TNode*& findnode(TNode* &root, const Frac& a) {
	if (root == nullptr) {
		throw out_of_range("root can not be nullptr!");
	}
	if (a < root->value) {
		findnode(root->lChild, a);
	}
	else if (a > root->value) {
		findnode(root->rChild, a);
	}
	else {
		return root;
	}
}
int pop_up(TNode* &root, const Frac& v) {
	TNode* &target = findnode(root, v);
	if (target != nullptr) {
		if (target->lChild != nullptr) {
			if (target->rChild != nullptr) {
				TNode* helper = target->rChild;
				while (helper->lChild != nullptr) {
					helper = helper->lChild;
				}
				auto temp=helper->value;
				pop_up(root, temp);
				target->value = temp;
			}
			else {//lChildÓÐ, rChildÃ»ÓÐ
				TNode* temp = target;
				target = temp->lChild;
				auto templ = temp->lChild;
				templ = nullptr;
				delete temp;
			}
		}
		else {
			//lChild==nullptr
			if (target->rChild != nullptr) {
				TNode* temp = target;
				target = temp->rChild;
				auto tempr = temp->rChild;
				tempr = nullptr;
				delete temp;
			}
			else {
				TNode* temp = target;
				target = nullptr;
				delete temp;
			}
		}
		return 1;
	}
	else {
		return 0;
	}
}



void printAll(TNode * root) {
	if (root != nullptr) {
		printAll(root->lChild);
		std::cout << (root->value).getNum();
		std::cout << "/";
		std::cout << (root->value).getDen();
		std::cout << " ";
		printAll(root->rChild);
	}
}

ostream& operator<<(ostream& os, const Frac& a) {
	os << a.getNum() << "/" << a.getDen();
	return os;
}

void printAll(ostream& os, TNode* root) {
	if (root != nullptr) {
		printAll(os,root->lChild);
		os << root->value << " ";
		printAll(os,root->rChild);
	}
}

ostream& operator<<(ostream& os, TNode* root) {
	printAll(os, root);
	return os;
}

void check(TNode* t) {
	if (t->lChild == nullptr) {
		cout << "no left child" << endl;
	}
	else {
		cout << "have left child" << endl;
		
		auto re = t->lChild;
		TNode ree = *re;
		Frac reee = ree.value;

		cout << "left child is: " << reee << endl;
		
	}
	if (t->rChild == nullptr) {
		cout << "no right child" << endl;
	}
	else {
		cout << "have right child" << endl;
		
		auto re = t->rChild;
		TNode ree = *re;
		Frac reee = ree.value;

		cout << "right child is: " << reee << endl;
	}
}


int main() {
	myint a, b, c;
	Frac tempFr;
	TNode *root;
	root = nullptr;
	insert(root, 19);
	insert(root, 37);
	insert(root, 9);
	insert(root, 15);
	insert(root, 5);
	insert(root, 7);
	insert(root, 3);
	insert(root,12);
	insert(root,10);
	insert(root,13);
	insert(root,14);
	pop_up(root, 5);
	system("PAUSE");
	check(findnode(root,7));
	system("PAUSE");
	cout << root << endl;
	system("PAUSE");
	pop_up(root, 7);
	system("PAUSE");
	check(findnode(root, 9));
	system("PAUSE");
	cout << root << endl;
	system("PAUSE");
	return 0;
}
