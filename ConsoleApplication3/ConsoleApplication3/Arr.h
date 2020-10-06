#pragma once

template<typename T>
class Arr {
public:
	T * data = nullptr;
	int size = 0;

	Arr(int _size)
	{
		this->size = _size;//init la size
		data = new T[_size];//allouer un tableau
		for (int i = 0; i < _size; i++)//boucle partout
			data[i] = {};//demander a c++ de trouver un truc a mettre
	}

	virtual ~Arr()
	{
		delete [] data;
		cout << "deleted" << endl;
	}

	T & get(int idx)
	{
		if (idx >= size) throw "out of bound maj";
		if (idx < 0) throw "out of bound min";
		return data[idx];
	}

	//fonction set ca pose une valeur T passee par valeur a la case idx du tableau
	// qui throw une exception si l 'element est hors du tableau
};