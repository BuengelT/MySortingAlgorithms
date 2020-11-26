#include "ThreadPanel.h"

#pragma region Event Methoden
/// <summary>
/// Button: Neuen Zufalls Array generieren
/// </summary>
System::Void MySortingAlgorithms::ThreadPanel::button_RandomArray_Click(System::Object^ sender, System::EventArgs^ e)
{
	//this->array_IntValues = createArray(ArrayType::random, 0); // Um jedes mal zufällige Anzahl Elemente zu wählen
	
	this->array_IntValues = createArray(ArrayType::random, this->array_IntValues->Length);//Festlegen der neuen Array-Werte
	this->label_ArrayElements->Text = this->array_IntValues->Length.ToString();	
	calcVarDrawPanel();// Balken-Werte berechnen
	drawArray();//Array einmalig zeichnen
}

/// <summary>
/// Button: ThreadStart des Algorithmus
/// </summary>
System::Void MySortingAlgorithms::ThreadPanel::button_StartAlgorithm_Click(System::Object^ sender, System::EventArgs^ e)
{
	//this->thread->Join(); Um Threads zu syncronisieren, (Das Fenster nicht schließen bevor der laufende Thread beendet ist)
	//https://docs.microsoft.com/de-de/dotnet/api/system.threading.thread.join?view=netframework-4.8

	if (this->algorithmType_Select == AlgorithmType::QuickSort)
	{
		this->thread_Run = gcnew Thread(gcnew ParameterizedThreadStart(this, &ThreadPanel::quickSortStart));
		this->thread_Run->Start(Tuple::Create(this->array_IntValues, 0, this->array_IntValues->Length - 1));
	}
	else if (this->algorithmType_Select == AlgorithmType::BubbleSort)
	{
		this->thread_Run = gcnew Thread(gcnew ParameterizedThreadStart(this, &ThreadPanel::bubbleSortStart));
		this->thread_Run->Start(Tuple::Create(this->array_IntValues, this->array_IntValues->Length));
	}
	else if (this->algorithmType_Select == AlgorithmType::SelectionSort)
	{
		this->thread_Run = gcnew Thread(gcnew ParameterizedThreadStart(this, &ThreadPanel::selectionSortStart));
		this->thread_Run->Start(Tuple::Create(this->array_IntValues, this->array_IntValues->Length));
	}
	else if (this->algorithmType_Select == AlgorithmType::HeapSort)
	{
		this->thread_Run = gcnew Thread(gcnew ParameterizedThreadStart(this, &ThreadPanel::heapSortStart));
		this->thread_Run->Start(Tuple::Create(this->array_IntValues, this->array_IntValues->Length));
	}
	else if (this->algorithmType_Select == AlgorithmType::InsertionSort)
	{
		this->thread_Run = gcnew Thread(gcnew ParameterizedThreadStart(this, &ThreadPanel::insertionSortStart));
		this->thread_Run->Start(Tuple::Create(this->array_IntValues, this->array_IntValues->Length));
	}
	else if (this->algorithmType_Select == AlgorithmType::MergeSort)
	{
		this->thread_Run = gcnew Thread(gcnew ParameterizedThreadStart(this, &ThreadPanel::mergeSortStart));
		this->thread_Run->Start(Tuple::Create(this->array_IntValues, 0, this->array_IntValues->Length - 1));
	}
	else if (this->algorithmType_Select == AlgorithmType::ShellSort)
	{
		this->thread_Run = gcnew Thread(gcnew ParameterizedThreadStart(this, &ThreadPanel::shellSortStart));
		this->thread_Run->Start(Tuple::Create(this->array_IntValues, this->array_IntValues->Length));
	}
	else if (this->algorithmType_Select == AlgorithmType::RadixSort)
	{
		this->thread_Run = gcnew Thread(gcnew ParameterizedThreadStart(this, &ThreadPanel::radixSortStart));
		this->thread_Run->Start(Tuple::Create(this->array_IntValues, this->array_IntValues->Length));
	}
}

/// <summary>
/// Button: Thread Beenden Brute-Force
/// </summary>
System::Void MySortingAlgorithms::ThreadPanel::button_Pause_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (this->thread_Run != nullptr && this->thread_Run->IsAlive)
	{
		this->thread_Run->Abort();
	}
}

/// <summary>
/// Button: Automatisches Zeichnen des Panels, beim initialisieren
/// </summary>
System::Void MySortingAlgorithms::ThreadPanel::ThreadPanel_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e)
{
	drawArray();
}
#pragma endregion

#pragma region Allgemeingültige Methoden
/// <summary>
/// Array Zeichnen mit 2 Hervorhebungen
/// </summary>
void MySortingAlgorithms::ThreadPanel::drawArray(int a, int b)
{
	//Erstellen des Grafikobjektes
	Graphics^ leinwand = this->panel_Draw->CreateGraphics();
	//Pinsel zum zeichnen der Balken
	SolidBrush^ black = gcnew SolidBrush(System::Drawing::Color::Black);
	SolidBrush^ red = gcnew SolidBrush(System::Drawing::Color::Red);
	//Pinsel mit der Backcolor um das Panel neu leeren
	SolidBrush^ clearBackground = gcnew SolidBrush(this->panel_Draw->BackColor);
	leinwand->FillRectangle(clearBackground, 0, 0, this->panel_Draw->Width, this->panel_Draw->Height);

	int j = 0;
	// startwert von i ist das Ende des ersten gap, i wird bei jedem durchlaufe um bar+gap erhöht
	for (float i = pixelWidthOfOneGap; i < this->panel_Draw->Width && j < this->array_IntValues->Length; i += (pixelWidthOfOneGap + pixelWidthOfOneBar), j++)
	{
		leinwand->FillRectangle(black,
			i, // x-start an der Stelle wo die vorherige gap endet		
			this->pixelHeightOfOneBarElement * (this->arrayMaxValue - this->array_IntValues[j]), // y-start; Komplement berechnen da bis zum unteren Rand gezeichnet wird
			this->pixelWidthOfOneBar, // Breite eines Balkens
			this->pixelHeightOfOneBarElement * this->array_IntValues[j] // Höhe des Balken
		);
		if (j == a || j == b) // für übergebener Wert wird der entsprechende Balken rot gefärbt
			leinwand->FillRectangle(red,
				i, // x-start an der Stelle wo die vorherige gap endet		
				this->pixelHeightOfOneBarElement * (this->arrayMaxValue - this->array_IntValues[j]), // y-start; Komplement berechnen da bis zum unteren Rand gezeichnet wird
				this->pixelWidthOfOneBar, // Breite eines Balkens
				this->pixelHeightOfOneBarElement * this->array_IntValues[j] // Höhe des Balken
			);
	}
}

/// <summary>
/// Array Zeichnen ohne Hervorhebungen(Überladung)
/// </summary>
void MySortingAlgorithms::ThreadPanel::drawArray()
{
	drawArray(-1, -1);
}

/// <summary>
/// Array Zeichnen mit 1x Hervorhebung(Überladung)
/// </summary>
void MySortingAlgorithms::ThreadPanel::drawArray(int a)
{
	drawArray(a, -1);
}

/// <summary>
/// Berechnung der Variablen die zum zeichnen des Arrays benötigt werden
/// </summary>
void MySortingAlgorithms::ThreadPanel::calcVarDrawPanel()
{
	this->pixelWidthOfAllBars = this->panel_Draw->Width * 0.8f; //80% Balken
	this->pixelWidthOfAllGaps = this->panel_Draw->Width * 0.2f; //20% Lücken

	this->pixelWidthOfOneBar = (this->pixelWidthOfAllBars / this->array_IntValues->Length); //pixelGröße eines Balkens
	this->pixelWidthOfOneGap = (this->pixelWidthOfAllGaps / (this->array_IntValues->Length + 1)); // pixelGröße einer Lücke; +1 um am ende nochh ein Gap hinzuzufügen
	this->arrayMaxValue = findMaxValue(this->array_IntValues); // maxElement des Arrays ermitteln, um die Balkenhöhe festzulegen
	this->pixelHeightOfOneBarElement = (this->panel_Draw->Height / (float)this->arrayMaxValue); // pixelhöhe eines Elementes
}
#pragma endregion

#pragma region Quicksort Methoden
/// <summary>
/// quickSortStart(array[int]^ arr, int low, int high);
/// https://www.geeksforgeeks.org/quick-sort/
/// </summary>
void MySortingAlgorithms::ThreadPanel::quickSortStart(Object^ obj)
{
	// parameter aus dem Object auslesen
	auto args = safe_cast<Tuple<array<int>^, int, int>^>(obj);
	array<int>^ arr = args->Item1;
	int low = args->Item2;
	int high = args->Item3;

	if (low < high)
	{
		// Pivot auswählen
		int pi = partition(arr, low, high);

		// links und rechts vom pivot sortieren
		quickSort(arr, low, (pi - 1));
		quickSort(arr, (pi + 1), high);
	}

	//Last Draw to remove red bars
	drawArray();
}

/// <summary>
/// Funktion für rekursives Aufrufen von Quicksort.
/// <summary>
void MySortingAlgorithms::ThreadPanel::quickSort(array<int>^ arr, int low, int high)
{
	if (low < high)
	{
		// Pivot auswählen
		int pi = partition(arr, low, high);

		// links und rechts vom pivot sortieren
		quickSort(arr, low, (pi - 1));
		quickSort(arr, (pi + 1), high);
	}
}

/// <summary>
/// Quicksort - Festlegen des Pivot Elements.
/// <summary>
int MySortingAlgorithms::ThreadPanel::partition(array<int>^ arr, int low, int high)
{
	int pivot = arr[high]; // Pivot entspricht dem letzten Element
	int i = (low - 1); // Index des niedrigeren elements

	for (int j = low; j <= high - 1; j++)
	{
		if (arr[j] < pivot) // kleinere Elemente werde auf die linke Seite geschoben
		{
			i++;
			if (i != j)
			{
				drawArray(i, j);
				Thread::Sleep(this->int_DrawInterval);
				swap(arr, i, j);
			}
		}
	}
	drawArray(i + 1, high);
	Thread::Sleep(this->int_DrawInterval);
	swap(arr, (i + 1), high);
	return (i + 1);
}
#pragma endregion

#pragma region Bubblesort Methoden
/// <summary>
/// bubbleSortStart(array[int]^ arr, int n);
/// https://www.geeksforgeeks.org/bubble-sort/
/// </summary>		  
void MySortingAlgorithms::ThreadPanel::bubbleSortStart(Object^ obj)
{
	auto args = safe_cast<Tuple<array<int>^, int>^>(obj);
	array<int>^ arr = args->Item1;
	int n = args->Item2;

	int i, j;
	for (i = 0; i < n - 1; i++)

		// Last i elements are already in place  
		for (j = 0; j < n - i - 1; j++)
			if (arr[j] > arr[j + 1])
			{
				Thread::Sleep(this->int_DrawInterval);
				swap(arr, j, j + 1);
				drawArray(j, j + 1);
			}

	//Last Draw to remove red bars
	drawArray();
}
#pragma endregion

#pragma region Selectionsort Methoden
/// <summary>
/// selectionSortStart(array[int]^ arr, int n);
/// https://www.geeksforgeeks.org/selection-sort/
/// </summary>		   
void MySortingAlgorithms::ThreadPanel::selectionSortStart(Object^ obj)
{
	auto args = safe_cast<Tuple<array<int>^, int>^>(obj);
	array<int>^ arr = args->Item1;
	int n = args->Item2;

	int i, j, min_idx;

	// One by one move boundary of unsorted subarray  
	for (i = 0; i < n - 1; i++)
	{
		// Find the minimum element in unsorted array  
		min_idx = i;
		for (j = i + 1; j < n; j++)
			if (arr[j] < arr[min_idx])
				min_idx = j;

		// Swap the found minimum element with the first element 
		drawArray(min_idx, i);
		Thread::Sleep(this->int_DrawInterval);
		swap(arr, min_idx, i);

	}
	drawArray();
}
#pragma endregion

#pragma region Heapsort Methoden
/// <summary>
/// heapSortStart(array[int]^ arr, int n);
/// https://www.geeksforgeeks.org/heap-sort/
/// </summary>		 
void MySortingAlgorithms::ThreadPanel::heapSortStart(Object^ obj)
{
	auto args = safe_cast<Tuple<array<int>^, int>^>(obj);
	array<int>^ arr = args->Item1;
	int n = args->Item2;

	// Build heap (rearrange array) 
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);

	// One by one extract an element from heap 
	for (int i = n - 1; i >= 0; i--)
	{

		// Move current root to end
		drawArray(0, i);
		Thread::Sleep(this->int_DrawInterval);
		swap(arr, 0, i);

		// call max heapify on the reduced heap 
		heapify(arr, i, 0);
	}

	//Last Draw to remove red bars
	drawArray();
}

void MySortingAlgorithms::ThreadPanel::heapify(array<int>^ arr, int n, int i)
{
	int largest = i; // Initialize largest as root 
	int l = 2 * i + 1; // left = 2*i + 1 
	int r = 2 * i + 2; // right = 2*i + 2 

	// If left child is larger than root 
	if (l < n && arr[l] > arr[largest])
		largest = l;

	// If right child is larger than largest so far 
	if (r < n && arr[r] > arr[largest])
		largest = r;

	// If largest is not root 
	if (largest != i)
	{
		Thread::Sleep(this->int_DrawInterval);
		swap(arr, i, largest);
		drawArray(i, largest);

		// Recursively heapify the affected sub-tree 
		heapify(arr, n, largest);
	}
}
#pragma endregion

#pragma region Insertionsort Methoden
/// <summary>
/// insertionSortStart(array[int]^ arr, int n);
/// https://www.geeksforgeeks.org/insertion-sort/
/// </summary>		   
void MySortingAlgorithms::ThreadPanel::insertionSortStart(Object^ obj)
{
	auto args = safe_cast<Tuple<array<int>^, int>^>(obj);
	array<int>^ arr = args->Item1;
	int n = args->Item2;

	int i, key, j;
	for (i = 1; i < n; i++)
	{
		//key = 3
		key = arr[i];
		j = i - 1;

		/* Move elements of arr[0..i-1], that are
		greater than key, to one position ahead
		of their current position */
		while (j >= 0 && arr[j] > key)
		{
			drawArray(j + 1, j);
			Thread::Sleep(this->int_DrawInterval);
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		drawArray(j + 1);
		Thread::Sleep(this->int_DrawInterval);
		arr[j + 1] = key;
	}

	//Last Draw to remove red bars
	drawArray();
}
#pragma endregion

#pragma region Mergesort Methoden
/// <summary>
/// mergeSortStart(array[int]^ arr, int l, int r);
/// https://www.geeksforgeeks.org/merge-sort/
/// </summary>
void MySortingAlgorithms::ThreadPanel::mergeSortStart(Object^ obj)
{
	auto args = safe_cast<Tuple<array<int>^, int, int>^>(obj);
	array<int>^ arr = args->Item1;
	int l = args->Item2;
	int r = args->Item3;

	if (l < r)
	{
		// Same as (l+r)/2, but avoids overflow for 
		// large l and h 
		int m = l + (r - l) / 2;

		// Sort first and second halves 
		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);

		merge(arr, l, m, r);
	}

	//Last Draw to remove red bars
	drawArray();
}

void MySortingAlgorithms::ThreadPanel::mergeSort(array<int>^ arr, int l, int r)
{
	if (l < r)
	{
		// Same as (l+r)/2, but avoids overflow for 
		// large l and h 
		int m = l + (r - l) / 2;

		// Sort first and second halves 
		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);

		merge(arr, l, m, r);
	}
}

void MySortingAlgorithms::ThreadPanel::merge(array<int>^ arr, int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	/* create temp arrays */
	array<int>^ L = gcnew array<int>(n1);
	array<int>^ R = gcnew array<int>(n2);
	//int* L[n1],* R[n2];		

	/* Copy data to temp arrays L[] and R[] */
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; // Initial index of first subarray 
	j = 0; // Initial index of second subarray 
	k = l; // Initial index of merged subarray 
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			Thread::Sleep(this->int_DrawInterval);
			drawArray(k);
			i++;
		}
		else
		{
			arr[k] = R[j];
			Thread::Sleep(this->int_DrawInterval);
			drawArray(k);
			j++;
		}
		k++;
	}

	/* Copy the remaining elements of L[], if there
	   are any */
	while (i < n1)
	{
		arr[k] = L[i];
		Thread::Sleep(this->int_DrawInterval);
		drawArray(k);
		i++;
		k++;
	}

	/* Copy the remaining elements of R[], if there
	   are any */
	while (j < n2)
	{
		arr[k] = R[j];
		Thread::Sleep(this->int_DrawInterval);
		drawArray(k);
		j++;
		k++;
	}
}

#pragma endregion

#pragma region Shellsort Methoden
/// <summary>
/// shellSortStart(array[int]^ arr, int n);
/// https://www.geeksforgeeks.org/shellsort/
/// </summary>
void MySortingAlgorithms::ThreadPanel::shellSortStart(Object^ obj)
{
	auto args = safe_cast<Tuple<array<int>^, int>^>(obj);
	array<int>^ arr = args->Item1;
	int n = args->Item2;

	// Start with a big gap, then reduce the gap 
	for (int gap = n / 2; gap > 0; gap /= 2)
	{
		// Do a gapped insertion sort for this gap size. 
		// The first gap elements a[0..gap-1] are already in gapped order 
		// keep adding one more element until the entire array is 
		// gap sorted  
		for (int i = gap; i < n; i += 1)
		{
			// add a[i] to the elements that have been gap sorted 
			// save a[i] in temp and make a hole at position i 								
			int temp = arr[i];

			// shift earlier gap-sorted elements up until the correct  
			// location for a[i] is found 
			int j;
			for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
			{
				drawArray(j - gap, j);
				Thread::Sleep(this->int_DrawInterval);
				arr[j] = arr[j - gap];

			}
			//  put temp (the original a[i]) in its correct location 
			drawArray(j);
			Thread::Sleep(int_DrawInterval);
			arr[j] = temp;
		}
	}
	Console::WriteLine("End");
	//Last Draw to remove red bars
	drawArray();
}
#pragma endregion

#pragma region Radixsort Methoden
/// <summary>
/// radixSort(array[int]^ arr, int n);
/// https://www.geeksforgeeks.org/radix-sort/
/// </summary>
void MySortingAlgorithms::ThreadPanel::radixSortStart(Object^ obj)
{
	auto args = safe_cast<Tuple<array<int>^, int>^>(obj);
	array<int>^ arr = args->Item1;
	int n = args->Item2;

	// Find the maximum number to know number of digits 
	int m = findMaxValue(arr);

	// Do counting sort for every digit. Note that instead 
	// of passing digit number, exp is passed. exp is 10^i 
	// where i is current digit number 
	for (int exp = 1; m / exp > 0; exp *= 10)
		countSort(arr, n, exp);

	//Last Draw to remove red bars
	drawArray();
}

void MySortingAlgorithms::ThreadPanel::countSort(array<int>^ arr, int n, int exp)
{
	array<int>^ output = gcnew array<int>(n);
	//int output[n]; // output array		
	int i, count[10] = { 0 };

	// Store count of occurrences in count[] 
	for (i = 0; i < n; i++)
		count[(arr[i] / exp) % 10]++;

	// Change count[i] so that count[i] now contains actual 
	//  position of this digit in output[] 
	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];

	// Build the output array 
	for (i = n - 1; i >= 0; i--)
	{

		output[count[(arr[i] / exp) % 10] - 1] = arr[i];
		count[(arr[i] / exp) % 10]--;
		drawArray(count[(arr[i] / exp) % 10] - 1, (arr[i] / exp) % 10);
		Thread::Sleep(this->int_DrawInterval);

	}

	// Copy the output array to arr[], so that arr[] now 
	// contains sorted numbers according to current digit 
	for (i = 0; i < n; i++)
	{
		arr[i] = output[i];
		drawArray(i);
		Thread::Sleep(this->int_DrawInterval);
	}

}

#pragma endregion

#pragma region Setter Methoden
void MySortingAlgorithms::ThreadPanel::setLabelArrayElements(String^ str) { this->label_ArrayElements->Text = str; }
void MySortingAlgorithms::ThreadPanel::setLabelAlgorithmName(String^ str) { this->label_AlgorithmName->Text = str; }
void MySortingAlgorithms::ThreadPanel::setArrayIntValues(array<int>^ arr) { this->array_IntValues = (array<int>^)arr->Clone(); } // Kopie des Arrays erstellen, daher mit clone() arbeiten
void MySortingAlgorithms::ThreadPanel::setDrawInterval(int value) { this->int_DrawInterval = value; }
void MySortingAlgorithms::ThreadPanel::setAlgorithmType(AlgorithmType value) { this->algorithmType_Select = value; }
#pragma endregion