#pragma once

#include <functional>

//créer une classe similaire à std::vector<T>
template<typename T>
class DynArr
{
public:
	T*		data = nullptr;
	size_t	allocSize = 0;

	DynArr( int size ) {
		//a remplir en reprenant le fonctionnement de arr.h
		this->allocSize = size;
		//data = new T[size];
		data = (T*) malloc( size * sizeof(T) );
		for (int i = 0; i < size; ++i) 
			data[i] = {};
		//assigner la taille d'allocation
		//allouer un tableau de data
		//remplir data avec des données par défaut avec un boucle
	};

	virtual ~DynArr() {
		free(data);
	};

	// ajouter get
	T& get(int index){
		if (index >= allocSize || index < 0) throw "assert:out of bound";
		return data[index];
	}
	
	// ajouter set affectation
	// ajouter que set alloue de l'espace supplémentaire
	// si le tableau est trop petit
	void set(int index, const T & toto) {
		if (index >= allocSize)
			resize( (allocSize+1) );
		data[index] = toto;
	}

	//
	void resize(int newAllocSize) {
		//si la taille est deja bonne on ne cahnge rien
		if (newAllocSize < allocSize )
			return;

		//on realloue a la bonne taille

		int allocSizeByte = newAllocSize * sizeof(T);
		data = (T*) realloc( data, allocSizeByte );

		//on met a zero les element supp
		for (int i = allocSize; i < newAllocSize; ++i)
			data[i] = {};

		//on change la taille d'alloc officielle
		allocSize = newAllocSize;
	}

	void reverse() {//renverser les elements du tableau
		//pour i de 0 a allocsize / 2
		//mettre val(i) dans temp
		//mettre val( allocsize - i - 1 ) dans val[0]
		//mettre temp dans ( allocsize - i - 1 ) 
		T tmp;
		for (int i = 0; i < allocSize / 2; ++i) {
			tmp = data[i];
			data[i] = data[allocSize - i - 1];
			data[allocSize - i - 1] = tmp;
		}
	}

	int length() const {
		return allocSize;
	}

	void push_back(const T & elem) { 
		// ajouter l'element a la fin de ce tableau
		//adds elements to the end of the array
		set(length(), elem);
	}

	void append(const DynArr<T> & arr) {//ajouter les elemnt d'un autre tableau a celui ci
		// pour chaque element de arr
		// mettre cet element dans ce tableau
		for (int i = 0; i < arr.length();i++) 
			push_back(arr.data[i]);
	}

	void iter( std::function< void(T) > _iter ) {
		for( int i = 0; i<length();i++)
			_iter( data[i]);
	}
};