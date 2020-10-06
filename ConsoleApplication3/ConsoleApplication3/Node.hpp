#pragma once

class Node {
public:

	float	key = 0.0;
	Node*	left = nullptr;
	Node*	right = nullptr;
	
	//ecrire constructeur

	Node(){
	}

	Node( float value, Node * l = nullptr, Node *r = nullptr) {
		key = value;
		this->left = l;
		this->right = r;
	}

	//ecrire destructeur
	~Node() {
		delete left;
		delete right;
	}

	Node * heapify(float newVal) {
		//newval il doit
		//garder le fait que la clé de left et la clé de right 
		//sont supérieur a la clé en cours
		if (newVal<key) {
			Node* nuNode = new Node(newVal);
			nuNode->left = this;
			return nuNode;
		}
		else {
			if (right == nullptr)
				right = new Node(newVal);
			else if( left == nullptr )
				left = new Node(newVal);
			else {//gauche est pas nul, droit est pas nul
				//le fils gauche devient le resultat de l'entassement de la nouvelle valeur dans le fils gauche
				left = left->heapify(newVal);
			}
			return this;
		}
	}

	bool isOk();

	Node* remove(float val) {//rendre la fonction static car elle doit pouvoir rendre this
		Node* cur = this;

		if (val == key) 
			cur = cur->deleteMin();
		if (cur == nullptr) return nullptr;

		if (cur->left) cur->left = cur->left->remove(val);
		if (cur->right) cur->right = cur->right->remove(val);

		return cur;
	}

	float getMin() {
		//la valeur la plus faible de l'arbre
		return key;
	}

	Node* deleteMin() {
		Node* l = left;
		Node* r = right;

		left = right = nullptr;

		delete this;

		if (l == nullptr) return r;
		if (r == nullptr) return l;

		return Node::merge(l, r);
	}

	static Node* merge(Node* a0, Node* a1);

	static Node* fromTabRec(float* t, int tLen) {
		if (!tLen) return nullptr;
		Node* cur = new Node(t[0]);
		if (tLen > 1)
			cur = merge(cur, fromTabRec(t + 1, tLen - 1));
		return cur;
	}

	static Node* fromTab(float* t, int tLen) {
		if (!tLen) return nullptr;
		Node* root = new Node(t[0]);
		if( tLen > 1 )
			for (int i = 1; i < tLen; ++i) {
				root->heapify(t[i]);
			}
		return root;
	}
};

