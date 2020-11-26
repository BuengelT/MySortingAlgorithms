#pragma once
#include "Extern.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Collections::Generic;
using namespace System::Threading;

namespace MySortingAlgorithms {

	/// <summary>
	/// Zusammenfassung für ThreadPanel
	/// </summary>
	public ref class ThreadPanel : public System::Windows::Forms::UserControl
	{
	public:
		ThreadPanel(array<int>^ arr)
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//	
			{
				this->array_IntValues = (array<int>^)arr->Clone();
				this->label_ArrayElements->Text = arr->Length.ToString();
				this->int_DrawInterval = 50;

				calcVarDrawPanel();
			}
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~ThreadPanel()
		{
			if (components)
			{
				delete components;
			}
		}

#pragma region Member		
	private: array<int>^ array_IntValues;//Array mit int-Werten die sortiert werden		   
	private: Thread^ thread_Run;// Der Thread zum ausführen des Algorithmus		   
	private: AlgorithmType algorithmType_Select;// legt fest welcher Algorithmus im ThreadPanel genutzt wird		   
	private: int int_DrawInterval;// Thread-Sleep Variable für Wartezeiten zwischen den Steps

		   //Variablen die berechnet werden, um die Balken zu Zeichnen
	private: float pixelWidthOfAllBars;
	private: float pixelWidthOfAllGaps;
	private: float pixelWidthOfOneBar;
	private: float pixelWidthOfOneGap;
	private: float pixelHeightOfOneBarElement;
	private: int arrayMaxValue;

		   //Automatisch genrierte Forms
	private: System::Windows::Forms::Button^ button_StartAlgorithm;
	private: System::Windows::Forms::Button^ button_RandomArray;
	private: System::Windows::Forms::Panel^ panel_Draw;
	private: System::Windows::Forms::Label^ label_ArrayElements;
	private: System::Windows::Forms::Button^ button_Pause;
	private: System::Windows::Forms::Label^ label_AlgorithmName;

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::Container^ components;
#pragma endregion

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button_StartAlgorithm = (gcnew System::Windows::Forms::Button());
			this->button_RandomArray = (gcnew System::Windows::Forms::Button());
			this->panel_Draw = (gcnew System::Windows::Forms::Panel());
			this->label_ArrayElements = (gcnew System::Windows::Forms::Label());
			this->button_Pause = (gcnew System::Windows::Forms::Button());
			this->label_AlgorithmName = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// button_StartAlgorithm
			// 
			this->button_StartAlgorithm->BackColor = System::Drawing::Color::Green;
			this->button_StartAlgorithm->Location = System::Drawing::Point(88, 191);
			this->button_StartAlgorithm->Name = L"button_StartAlgorithm";
			this->button_StartAlgorithm->Size = System::Drawing::Size(23, 23);
			this->button_StartAlgorithm->TabIndex = 8;
			this->button_StartAlgorithm->UseVisualStyleBackColor = false;
			this->button_StartAlgorithm->Click += gcnew System::EventHandler(this, &ThreadPanel::button_StartAlgorithm_Click);
			// 
			// button_NewArray
			// 
			this->button_RandomArray->BackColor = System::Drawing::SystemColors::Control;
			this->button_RandomArray->Location = System::Drawing::Point(3, 191);
			this->button_RandomArray->Name = L"button_NewArray";
			this->button_RandomArray->Size = System::Drawing::Size(50, 23);
			this->button_RandomArray->TabIndex = 7;
			this->button_RandomArray->Text = L"RND";
			this->button_RandomArray->UseVisualStyleBackColor = false;
			this->button_RandomArray->Click += gcnew System::EventHandler(this, &ThreadPanel::button_RandomArray_Click);
			// 
			// panel_Draw
			// 
			this->panel_Draw->BackColor = System::Drawing::Color::White;
			this->panel_Draw->Location = System::Drawing::Point(3, 3);
			this->panel_Draw->Name = L"panel_Draw";
			this->panel_Draw->Size = System::Drawing::Size(294, 180);
			this->panel_Draw->TabIndex = 5;
			// 
			// label_ArrayElements
			// 
			this->label_ArrayElements->AutoSize = true;
			this->label_ArrayElements->Location = System::Drawing::Point(265, 196);
			this->label_ArrayElements->Name = L"label_ArrayElements";
			this->label_ArrayElements->Size = System::Drawing::Size(29, 13);
			this->label_ArrayElements->TabIndex = 9;
			this->label_ArrayElements->Text = L"label";
			// 
			// button_Pause
			// 
			this->button_Pause->BackColor = System::Drawing::Color::Red;
			this->button_Pause->ForeColor = System::Drawing::SystemColors::ControlText;
			this->button_Pause->Location = System::Drawing::Point(59, 191);
			this->button_Pause->Name = L"button_Pause";
			this->button_Pause->Size = System::Drawing::Size(23, 23);
			this->button_Pause->TabIndex = 10;
			this->button_Pause->UseVisualStyleBackColor = false;
			this->button_Pause->Click += gcnew System::EventHandler(this, &ThreadPanel::button_Pause_Click);
			// 
			// label_AlgorithmName
			// 
			this->label_AlgorithmName->AutoSize = true;
			this->label_AlgorithmName->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label_AlgorithmName->Location = System::Drawing::Point(117, 191);
			this->label_AlgorithmName->Name = L"label_AlgorithmName";
			this->label_AlgorithmName->Size = System::Drawing::Size(85, 20);
			this->label_AlgorithmName->TabIndex = 11;
			this->label_AlgorithmName->Text = L"Algorithm";
			// 
			// ThreadPanel
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Beige;
			this->Controls->Add(this->label_AlgorithmName);
			this->Controls->Add(this->button_Pause);
			this->Controls->Add(this->label_ArrayElements);
			this->Controls->Add(this->button_StartAlgorithm);
			this->Controls->Add(this->button_RandomArray);
			this->Controls->Add(this->panel_Draw);
			this->Name = L"ThreadPanel";
			this->Size = System::Drawing::Size(300, 220);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &ThreadPanel::ThreadPanel_Paint);
			this->ResumeLayout(false);
			this->PerformLayout();
		}
#pragma endregion

#pragma region Event Methoden
		/// <summary>
		/// Button: Neuen Zufalls Array generieren
		/// </summary>
	public: System::Void button_RandomArray_Click(System::Object^ sender, System::EventArgs^ e);

		  /// <summary>
		  /// Button: ThreadStart des Algorithmus
		  /// </summary>
	public: System::Void button_StartAlgorithm_Click(System::Object^ sender, System::EventArgs^ e);

		  /// <summary>
		  /// Button: Thread Beenden Brute-Force
		  /// </summary>
	public: System::Void button_Pause_Click(System::Object^ sender, System::EventArgs^ e);

		  /// <summary>
		  /// Automatisches Zeichnen des Panels, beim initialisieren
		  /// </summary>
	private: System::Void ThreadPanel_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e);
#pragma endregion

#pragma region Allgemeingültige Methoden
		   /// <summary>
		   /// Array Zeichnen mit 2 Hervorhebungen
		   /// </summary>
	public: void drawArray(int a, int b);

		  /// <summary>
		  /// Array Zeichnen ohne Hervorhebungen
		  /// </summary>
	public: void drawArray();

		  /// <summary>
		  /// Array Zeichnen mit 1x Hervorhebung
		  /// </summary>
	public: void drawArray(int a);

		  /// <summary>
		  /// Berechnung der Variablen die zum zeichnen des Arrays benötigt werden
		  /// </summary>
	public: void calcVarDrawPanel();
#pragma endregion

#pragma region Quicksort Methoden
		  /// <summary>
		  /// quickSortStart(array[int]^ arr, int low, int high);
		  /// https://www.geeksforgeeks.org/quick-sort/
		  /// </summary>
	private: void quickSortStart(Object^ obj);
	private: void quickSort(array<int>^ arr, int low, int high); // Überladung für rekursiven Aufruf
	private: int partition(array<int>^ arr, int low, int high);
#pragma endregion

#pragma region Bubblesort Methoden
		   /// <summary>
		   /// bubbleSortStart(array[int]^ arr, int n);
		   /// https://www.geeksforgeeks.org/bubble-sort/
		   /// </summary>		  
	private: void bubbleSortStart(Object^ obj);
#pragma endregion

#pragma region Selectionsort Methoden
		   /// <summary>
		   /// selectionSortStart(array[int]^ arr, int n);
		   /// https://www.geeksforgeeks.org/selection-sort/
		   /// </summary>		   
	private: void selectionSortStart(Object^ obj);
#pragma endregion

#pragma region Heapsort Methoden
		   /// <summary>
		   /// heapSortStart(array[int]^ arr, int n);
		   /// https://www.geeksforgeeks.org/heap-sort/
		   /// </summary>		 
	private: void heapSortStart(Object^ obj);
	private: void heapify(array<int>^ arr, int n, int i);
#pragma endregion

#pragma region Insertionsort Methoden
		   /// <summary>
		   /// insertionSortStart(array[int]^ arr, int n);
		   /// https://www.geeksforgeeks.org/insertion-sort/
		   /// </summary>		   
	private: void insertionSortStart(Object^ obj);
#pragma endregion

#pragma region Mergesort Methoden
		   /// <summary>
		   /// mergeSortStart(array[int]^ arr, int l, int r);
		   /// https://www.geeksforgeeks.org/merge-sort/
		   /// </summary>
	private: void mergeSortStart(Object^ obj);
	private: void mergeSort(array<int>^ arr, int l, int r); // Überladung für Rekursiven Aufruf
	private: void merge(array<int>^ arr, int l, int m, int r);
#pragma endregion

#pragma region Shellsort Methoden
		   /// <summary>
		   /// shellSortStart(array[int]^ arr, int n);
		   /// https://www.geeksforgeeks.org/shellsort/
		   /// </summary>
	private: void shellSortStart(Object^ obj);
#pragma endregion

#pragma region Radixsort Methoden
		   /// <summary>
		   /// radixSort(array[int]^ arr, int n);
		   /// https://www.geeksforgeeks.org/radix-sort/
		   /// </summary>
	private: void radixSortStart(Object^ obj);
	private: void countSort(array<int>^ arr, int n, int exp);
#pragma endregion

#pragma region Setter Methoden		   
	public: void setLabelArrayElements(String^ str);
	public: void setLabelAlgorithmName(String^ str);
	public: void setArrayIntValues(array<int>^ arr);
	public: void setDrawInterval(int value);
	public: void setAlgorithmType(AlgorithmType value);
#pragma endregion			  
	};
}
