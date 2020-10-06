#pragma once
#include <cstdlib>
class IntArray
{
public:
	int *	data = nullptr;
	int		size = 0;

	//faire un tableau de data
	IntArray(int size) {
		data = (int*)malloc(size * sizeof(int));
		this->size = size;
	};

	IntArray(const IntArray & arr) {
		int size = arr.size;
		data = (int*)malloc(size * sizeof(int));
		this->size = size;
		for (int i = 0; i < size; ++i) {
			data[i] = arr.data[i];
		}
	};

	//faire un delete
	~IntArray() {
		free(data);
	}

	//faire un resize
	void resize(int sz) {
		if (size < sz) {
			int newAllocSize = sz + 1;
			data = (int*) realloc(data, newAllocSize * sizeof(int));
			if (data == nullptr)
				throw "out of memory";
		}
	}

	//faire un get
	int& get(int idx) {
		return data[idx];
	}

	//faire un set
	int& set(int idx, int val) {
		resize(idx + 1);
		return data[idx] = val;
	}

	//faire un operator[]
	int& operator[](int idx) {
		return data[idx];
	}

	int& operator()(int idx) {
		return data[idx];
	}

	static IntArray iota(int sz) {
		IntArray arr(sz);
		for (int i = 0; i < sz; i++) {
			arr(i) = i;
		}
		return arr;
	}

	static IntArray random(int sz) {
		IntArray arr(sz);
		for (int i = 0; i < sz; i++) 
			arr(i) = rand();
		return arr;
	}

	//devoirs : search, push_first push_back 
	//faire une recherche linéaire
	//renvoie -1 si pas trouvé
	//renvoie la position si trouvée
	//int search( int key ) 
	//

	//offset the array and 
	//
	//void push_back(  int val)
	//void push_front(  int val)


	//recherche de position d'insertion
	//renvoie la position ou inserer dans le tableau si il était trié.
	//int searchInsertionPos( int key ) 


	//void insert( int pos, int val)
	//faire une recherche binaire
	//est ce que j'ai trouvé?
	//sinon chercher a gauche 
	//sinon chercher a droite

	//faire un tri par insertion

	//faire un tri par insertion binaire
};

