#include "Extern.h"

void swap(array<int>^ arr, int a, int b)
{
	int temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
}

array<int>^ createArray(ArrayType aType, int arrLength)
{
	array<int>^ result;
	Random^ rand = gcnew Random();
	int number = rand->Next(5, 100);
	if (arrLength > 1)
		result = gcnew array<int>(arrLength);
	else
		result = gcnew array<int>(number);

	// Array initialisieren mit jedem Element
	for (int i = 0; i < result->Length; i++) {
		result[i] = i + 1;
	}

	if (aType == ArrayType::random)
	{
		//Array durchlaufen und jedes Element mit einem zufälligen Element tauschen
		for (int i = 0; i < result->Length; i++) {
			swap(result, i, rand->Next(result->Length - 1));
		}
	}
	else if (aType == ArrayType::reversed)
	{
		// Reihenfolge umdrehen
		for (int i = 0; i < result->Length / 2; i++) {
			swap(result, i, result->Length - 1 - i);
		}
	}
	else if (aType == ArrayType::onepiece)
	{
		//zwei zufällige Elemente miteinander tauschen
		swap(result, rand->Next(result->Length - 1), rand->Next(result->Length - 1));
	}
	else if (aType == ArrayType::almostsorted)
	{
		// benachbarte Elemente tauschen
		for (int i = 0; i < result->Length - 1; i += 2) {
			swap(result, i, i + 1);
		}
	}
	return result;
}

String^ algorithmTypeToString(AlgorithmType type)
{
	switch (type)
	{
	case AlgorithmType::QuickSort: return "QuickSort";
	case AlgorithmType::BubbleSort:	return "BubbleSort";
	case AlgorithmType::SelectionSort: return "SelectionSort";
	case AlgorithmType::HeapSort: return "HeapSort";
	case AlgorithmType::InsertionSort: return "InsertionSort";
	case AlgorithmType::MergeSort: return "MergeSort";
	case AlgorithmType::ShellSort: return "ShellSort";
	case AlgorithmType::RadixSort: return "RadixSort";
	default: return "N/A";
	}
}

int findMaxValue(array<int>^ arr)
{
	int result = arr[0];
	for (int i = 0; i < arr->Length; i++)
	{
		if (arr[i] > result) {
			result = arr[i];
		}
	}
	return result;
}

int getAlgorithmEnumCount()
{
	int result = 1; // Starten bei 1, da die loop nur durch != beendet werden kann und somit das letzte Element nicht mitgezählt wird
	for (int alg = (int)AlgorithmType::QuickSort; alg != (int)AlgorithmType::RadixSort; alg++)
	{
		result++;
	}

	return result;
}
