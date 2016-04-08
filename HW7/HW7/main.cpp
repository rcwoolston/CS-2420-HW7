#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void quickSort(int *arr, int left, int right);
void mergeSort(int *arr, int low, int high);
void merge(int *arr, int low, int mid,int high);
int sizeOfArray(fstream &file);
void loadArray(int *arr, int numberOfItems, fstream &file);
void maxHeap(int *arr, int i, int n);
void buildMaxHeap(int *a, int n);
void heapsort(int *arr, int n);
void swapT(int& a, int& b);
void display(int arr[], int size);

int main() {
	fstream fin;
	int tempInt, numberOfItems = 0;
	int *A;

	fin.open("Assign7Data.txt");

	while (fin>>tempInt) {;
		//cout << tempInt << endl;
		numberOfItems++;
	}
	//Reset seek to 0
	fin.clear();
	fin.seekg(0,ios::beg);

	cout << numberOfItems;
	A = new int[numberOfItems];

	int here = 0;
	while (here < numberOfItems) {
		fin >> tempInt;
		A[here] = tempInt;
		here++;
	}

	display(A, numberOfItems);
	mergeSort(A,0,numberOfItems-1);
	display(A, numberOfItems);

	//quickSort(A, 0, numberOfItems-1);

	//display(A, numberOfItems);

	// Read in the dictionary
	fstream finDictionary;
	string tempString;
	int lengthOfDictionary = 0;
	finDictionary.open("dictionary.txt");

	lengthOfDictionary = sizeOfArray(finDictionary);

	A = new int[lengthOfDictionary];

	// Quick Sort
	A = new int[lengthOfDictionary];
	loadArray(A, lengthOfDictionary, finDictionary);
	quickSort(A, 0, lengthOfDictionary - 1);
	display(A, lengthOfDictionary);

	//Merge Sort
	A = new int[lengthOfDictionary];
	loadArray(A, lengthOfDictionary, finDictionary);
	mergeSort(A, 0, lengthOfDictionary - 1);
	display(A, lengthOfDictionary);

	// Heap Sort
	A = new int[lengthOfDictionary];
	loadArray(A, lengthOfDictionary, finDictionary);	
	buildMaxHeap(A, lengthOfDictionary);
	heapsort(A, lengthOfDictionary);
	display(A, lengthOfDictionary);

	

	fin.close();
	finDictionary.close();

	system("pause");
	return 0;
}
void swapT(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}
void display(int arr[], int size) {
	int here = 0;
	cout << endl << endl;
	while (here < size) {
		cout << "Index: " << here << "  Contain: " << arr[here] << endl;
		here++;
	}
}
void quickSort(int *arr, int left, int right) {
	int i = left, j = right, pivot = arr[(left + right)/2];

	while (i <= j) {
		while (arr[i] < pivot) {
			i++;
		}
		while (arr[j] > pivot) {
			j--;
		}
		if (i <= j) {
			swapT(arr[i], arr[j]);
			i++;
			j--;
		}
	}

	if (left < j)
		quickSort(arr, left, j);
	if (i < right)
		quickSort(arr, i, right);
}

int sizeOfArray(fstream &file) {
	file.clear();
	file.seekg(0, ios::beg);
	int size = 0;
	string tempString;

	while (file >> tempString) {
		size++;
	}

	return size;
}

void loadArray(int *arr, int numberOfItems, fstream &file) {
	file.clear();
	file.seekg(0, ios::beg);
	int here = 0;
	string tempString;

	while (here < numberOfItems) {
		int sum = 0;
		file >> tempString;
		for (int i = 0; i < tempString.length(); i++) {
			sum += tempString[i];
		}
		arr[here] = sum;
		here++;
	}
}
void mergeSort(int *arr, int low, int high) {
	if (low >= high) {
		return;
	}
	else {
		int mid = (low + high) / 2;
		mergeSort(arr, low, mid);
		mergeSort(arr, mid + 1, high);
		merge(arr, low, mid, high);
	}
}
void merge(int *arr,int low,int mid,int high) {
	int * b = new int[high + 1 - low];
	int h = low, i =0, j = mid+1, k;
	while ((h <= mid) && (j <= high)){
		if (arr[h] <= arr[j]) {
			b[i] = arr[h];
			h++;
		}
		else {
			b[i] = arr[j];
			j++;
		}
		i++;
	}
	if (h>mid){
		for (k = j; k <= high; k++){
			b[i] = arr[k];
			i++;
		}
	}
	else {
		for (k = h; k <= mid; k++){
			b[i] = arr[k];
			i++;
		}
	}
	for (k = 0; k <= high - low; k++){
		arr[k + low] = b[k];
	}
	delete[] b;
}
void maxHeap(int *arr, int i, int n) {
	int j, temp;
	temp = arr[i];
	j = 2 * i;
	while (j <= n) {
		if (j < n && arr[j + 1] > arr[j]) {
			j = j + 1;
		}
		if (temp > arr[j]) {
			break;
		}
		else if (temp <= arr[j]) {
			arr[j / 2] = arr[j];
			j = 2 * j;
		}
	}
	arr[j / 2] = temp;
	return;
}
void buildMaxHeap(int *arr, int n) {
	for (int i = n / 2; i >= 1; i--) {
		maxHeap(arr, i, n);
	}
}
void heapsort(int *arr, int n) {
	int temp;
	for (int i = n; i >= 2; i--) {
		swapT(arr[i], arr[1]);
		maxHeap(arr, 1, i - 1);
	}
}