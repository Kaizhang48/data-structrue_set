//writen by KAIZHANG
#include<iostream>
using namespace std;

typedef long int myint;
class Frac {
	friend ostream& operator<<(ostream&, const Frac&);
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

ostream& operator<<(ostream& os, const Frac& a) {
	os << a.getNum() << "/" << a.getDen();
	return os;
}

//==========THIS IS TREE======================================
class TNode {
	friend ostream& operator<<(ostream&, TNode*);
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

TNode* copytree(TNode* root)
{
	TNode* newnode;
	if (root == nullptr)
		return nullptr;
	else
	{
		newnode = new TNode;    
		newnode->value = root->value;
		newnode->lChild = copytree(root->lChild);        
		newnode->rChild = copytree(root->rChild);          
		return newnode;                              
	}
}

void deleteBST(TNode** root) {
	if ((*root) == nullptr) {
		return;
	}
	deleteBST(&((*root)->lChild));
	deleteBST(&((*root)->rChild));
	if ((*root)->lChild == nullptr && (*root)->rChild == nullptr) {
		delete (*root);
		*root = nullptr;
	}
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
		return root;
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
				auto temp = helper->value;
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

void printAll(ostream& os, TNode* root) {
	if (root != nullptr) {
		printAll(os, root->lChild);
		os << root->value << " ";
		printAll(os, root->rChild);
	}
}

ostream& operator<<(ostream& os, TNode* root) {
	printAll(os, root);
	return os;
}

void check(TNode* t) {
	if (t->lChild == nullptr) {
		cout << t->value << " no left child" << ", ";
	}
	else {
		cout << t->value << " have left child: ";

		auto re = t->lChild;
		TNode ree = *re;
		Frac reee = ree.value;

		cout << reee << ", ";

	}
	if (t->rChild == nullptr) {
		cout << " no right child" << endl;
	}
	else {
		cout << " have right child: ";

		auto re = t->rChild;
		TNode ree = *re;
		Frac reee = ree.value;

		cout << reee << endl;
	}
}
//===============THIS IS SET=======================================
class SetOfFractions {
	friend ostream& operator<<(ostream&, SetOfFractions);
private:
	TNode* root;
public:
	SetOfFractions();
	SetOfFractions(const SetOfFractions &);
	SetOfFractions(SetOfFractions &&);
	void operator=(const SetOfFractions &);
	void operator=(SetOfFractions &&);
	myint isElement(const Frac &) ;
	bool pop_up(const Frac&);
	void insertInS(const Frac &);
	void printAllFractions() const;
	~SetOfFractions();
};

bool pop_up(const Frac& target){
     return pop_up(root, target)
}

ostream& operator<<(ostream& os, SetOfFractions a) {
	os << a.root;
	return os;
}

SetOfFractions::SetOfFractions() : root(nullptr) {}

SetOfFractions::SetOfFractions(const SetOfFractions& copyfrom) {
	root = new TNode;
	root = copytree(copyfrom.root);
}

SetOfFractions::SetOfFractions(SetOfFractions && movefrom) {
	root = movefrom.root;
	movefrom.root = nullptr;
}

void SetOfFractions::operator=(const SetOfFractions& assigment) {
	deleteBST(&root);
	root = new TNode;
	root = copytree(assigment.root);
}

void SetOfFractions::operator=(SetOfFractions && moverassignment) {
	TNode* temp = root;
	deleteBST(&temp);
	delete temp;
	deleteBST(&root);
	delete root;
	root = moverassignment.root;
	moverassignment.root = nullptr;
}
 
myint SetOfFractions::isElement(const Frac& el) {
	TNode* temp = findnode(root, el);
	if (temp != nullptr) {
		return 1;
	}
	return 0;
}

 void SetOfFractions::insertInS(const Frac& fr) {
	 insert(root, fr);
}

 void SetOfFractions::printAllFractions()const {
	 cout << root << endl;
 }
 
 SetOfFractions::~SetOfFractions() {
	 deleteBST(&root);
	 delete root;
 }

int main() 
{
	Frac a(3, 2);
	Frac b(4, 3);
	Frac c(7, 3);
	Frac d(8, 7);
	cout << a << b << c << d << endl;
	SetOfFractions aa;
	aa.insertInS(a);
	aa.insertInS(b);
	aa.insertInS(c);
	aa.insertInS(d);
	SetOfFractions bb = aa;
	cout << aa << endl;
	cout << "bb is(in order to see if copy constructor works):" << endl;
	cout << bb << endl;
	SetOfFractions cc;
	cc = aa;
	cout << "cc is(in order to see if copy assignment works): " << endl;
	cout << cc << endl;

	return 0;
}
