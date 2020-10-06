#include "Node.hpp"

bool Node::isOk() {
	if (left == nullptr && right == nullptr)
		return true;
	else if (left == nullptr)//on a un truc a droite
		return (right->key >= key) && right->isOk();//on fait confiance a droite et hop recurrence !
	else if (right == nullptr) {
		//gauche est pas nul
		return (left->key >= key) && left->isOk();//on fait confiance a droite et hop recurrence !
	}
	else {
		// les deux ne sont pas nuls
		if (key > left->key) return false;
		if (key > right->key) return false;
		return left->isOk() && right->isOk();
	}
}

Node* Node::merge(Node* a0, Node* a1) {
	if (a0 == nullptr ) return a0;
	if (a1 == nullptr ) return a0;

	float val = a1->getMin();
	Node* cur = a0;
	cur = cur->heapify(val);

	Node* l = a1->left;
	Node* r = a1->right;

	a1->left = nullptr;
	a1->right = nullptr;

	delete a1;

	cur = merge(cur, l);
	cur = merge(cur, r);

	return cur;
}
