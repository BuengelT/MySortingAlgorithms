#include "Hauptfenster.h"

// openGL oder directX für bessere Performance beim Zeichnen da die Berechnungen über die Grafikkarte getaetigt werden
using namespace MySortingAlgorithms;
using namespace System;
using namespace System::Windows::Forms;

#pragma region Alle Algorithmen Signaturen
/*
//https://www.geeksforgeeks.org/sorting-algorithms/
void swap(int* a, int* b);
//Quicksort(+swap) https://www.geeksforgeeks.org/quick-sort/
int partition(int a[], int low, int high);
void quickSort(int a[], int low, int high);

//Bubblesort(+swap) https://www.geeksforgeeks.org/bubble-sort/
void BubbleSort(int a[], int n);

//Selectionsort(+swap) https://www.geeksforgeeks.org/selection-sort/
void selectionSort(int a[], int n);

//Heapsort https://www.geeksforgeeks.org/heap-sort/
void heapify(int a[], int n, int i);
void heapSort(int a[], int n);

//Insertionsort https://www.geeksforgeeks.org/insertion-sort/
void insertionSort(int a[], int n);

//Mergesort https://www.geeksforgeeks.org/merge-sort/
void merge(int a[], int l, int m, int r);
void mergeSort(int a[], int l, int r);

//Shellsort https://www.geeksforgeeks.org/shellsort/
void shellSort(int a[], int n);

//Radixsort https://www.geeksforgeeks.org/radix-sort/
int getMax(int a[], int n);
void countSort(int a[], int n, int exp);
void radixSort(int a[], int n);
*/
#pragma endregion

[STAThread]
//void main(array<String^>^ args) {
void main() {	
	int arr[50];
	int aLen = sizeof(arr) / sizeof(int);	
	// Array initialisieren
	for (int i = 0; i < aLen; i++) { arr[i] = i + 1; }
		
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	
	Hauptfenster^ window = gcnew Hauptfenster(arr, aLen);

	//Anwendung soll mit Fenster starten
	Application::Run(window);	
}