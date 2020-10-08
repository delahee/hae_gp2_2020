#pragma once
#include <cstdlib>
#include <cstdio>
class IntArray
{
public:
	int *	data = nullptr;
	int		size = 0;

	//faire un tableau de data
	IntArray(int size=0) {
		int allocSize = size;
		if (allocSize <= 0)allocSize = 1;
		data = (int*)malloc(allocSize * sizeof(int));
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

	IntArray & operator= (const IntArray& arr) {
		resize(arr.size);
		for (int i = 0; i < arr.size; i++) 
			data[i] = arr.data[i];
		size = arr.size;
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
			size = sz;
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
		resize(idx + 1);
		return data[idx];
	}

	int& operator()(int idx) {
		return data[idx];
	}

	static IntArray iota(int sz) {
		IntArray arr(sz);
		for (int i = 0; i < sz; i++) {
			arr.set(i, i);
		}
		return arr;
	}

	static IntArray random(int sz) {
		IntArray arr(sz);
		for (int i = 0; i < sz; i++) 
			arr.set( i,  rand() );
		return arr;
	}

	//devoirs : , push_first push_back 
	//faire une recherche linéaire
	//renvoie -1 si pas trouvé
	//renvoie la position si trouvée
	//int search( int key ) 
	//

	//offset the array and 
	//
	void push_back(int val) {
		int pos = size;
		resize(size + 1);
		data[pos] = val;
	}

	//inserer l'élement en début de vecteur
	void push_front(int val) {
		int oldSize = size;

		resize(size + 1);

		for (int i = oldSize; i >= 0; --i) 
			data[i] = data[i - 1];

		data[0] = val;
	}
	
	//void insert( int pos, int val)
	//resizer
	//copier de la nouvelle fin au point d'insertion
	//affecter la valeur
	void insert(int idx, int val) {
		int oldSize = size;

		resize(size + 1);

		for (int i = oldSize; i >= idx; --i)
			data[i] = data[i - 1];

		data[idx] = val;
	}

	//comparer la clé avec chaque élément 
	//si trouvé renvoyer la position
	//renvoie -1 si pas trouvé
	int searchIter(int key, int startPos = 0) {
		for (int i = startPos; i < size; i++)
			if (data[i] == key)
				return i;
		return -1;
	}

	int searchRec(int key, int pos = 0) {
		//on est hors tableau ?
		if (pos >= size)
			return -1;
		if (data[pos] == key)//on est dans le tableau oon a trouvé
			return pos;
		return searchRec(key, pos + 1);//on est dans le tableau pas trouvé
	}

	//recherche de position d'insertion
	//on considere que le tableau est trié
	//renvoie la position ou inserer la valeur dans le tableau si il était trié.
	int searchInsertionPosIter( int key ) {
		int idx = 0;
		while (key >= data[idx]) {
			idx++;
		}
		return idx;
	}
	
	int searchInsertionPosRec(int key, int pos = 0)
	{
		if (pos >= size) return size;
		else if (data[pos] >= key) return pos;
		else return searchInsertionPosRec(key, pos + 1);
	}

	/*
	int searchInsertionPosRec(int key, int pos=0)
	{
		if (pos >= size) return size;
		if (key == data[pos] ) return pos;

		if (pos >= size - 1){
			if (key < data[pos] ) {
				return pos;
			}
			else {
				return size;
			}
		}
		else{

			if (data[pos] < key) {
				if( data[pos + 1] < key)
					return searchInsertionPosRec(key, pos + 1);
				if ( data[pos + 1] >= key)
					return pos + 1;
			}
			else {
				if (data[pos] > key )
					return pos;

			}
		}
		throw "assert";
	}
	*/
	//retourne faux si deux element du tableau ne sont pas triés
	//sinon renvoie vrai !
	bool isSortedIter() {
		for (int i = 0; i < size-1; i++) 
			if (data[i] > data[i + 1])
				return false;
		return true;
	}

	bool isSortedRec(int pos = 0) {
		if (pos >= size - 1)
			return true;
		if (data[pos] < data[pos + 1])
			return isSortedRec(pos + 1);
		return false;
	}
	//faire une recherche binaire
	//est ce que j'ai trouvé?
	//sinon chercher a gauche 
	//sinon chercher a droite

	//faire un tri par insertion
	//sort( int * data, int dataSize )
	//inserts the data in th array in a sorted fashion

	//int binarySearch( int key, int start, int end)
	//faire un tri par insertion binaire

	static IntArray sort(int* data, int dataSize);

	void sortInPlace();

	bool binarySearch(int key) {
		return binarySearch(key, 0, size-1);
	}

	bool binarySearch( int key, int start, int end ) {

		int mid = (end + start + 1) / 2;
		printf("s:%d start:%d mid:%d end:%d\n", key, start, mid,end);

		if (end < start) return false;
		
		if (data[start] == key) return true;
		if (data[end] == key)	return true;
		if (data[mid] == key)	return true;

		if (data[mid] > key)
			return binarySearch(key, start, mid - 1);
		//else
		return binarySearch(key, mid + 1, end);
		//si la donnée au milieu est la clé renvoyer true 
		// si la donnée au milieu et < la clé
		// chercher entre début et milieu -1
		// sinon chercher entre milieu + 1 et fin
		

	}
};

