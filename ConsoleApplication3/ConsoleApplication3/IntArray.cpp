#include "IntArray.h"

IntArray IntArray::sort(int* data, int dataSize) {
	//inserer le tableau d'entree pour produire un tableau trié
	IntArray arr;
	arr.resize(dataSize);
	for (int i = 0; i < dataSize; ++i) {
		int val = data[i];
		int pos = arr.searchInsertionPosRec(val);
		arr.insert(pos, val);
	}
	return arr;
}

void IntArray::sortInPlace()
{
	int i;
	int j;

	for (int i = 1; i < size; i++) {
		j = i;
		while (j > 0 && (data[j] < data[j - 1])) {
			int val = data[j-1];
			data[j-1] = data[j];
			data[j] = val;
			j--;
		}
	}

}
