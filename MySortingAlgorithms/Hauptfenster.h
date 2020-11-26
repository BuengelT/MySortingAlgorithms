#pragma once
#include "ThreadPanel.h"
#include "Extern.h"

namespace MySortingAlgorithms {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;
	using namespace System::Threading;

	/// <summary>
	/// Zusammenfassung für Hauptfenster
	/// </summary>
	public ref class Hauptfenster : public System::Windows::Forms::Form
	{
	public:
		Hauptfenster(int a[], int aLength)
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//			
			{
				//Speicherplatz reservieren
				this->array_IntValues = gcnew array<int>(aLength);
				this->list_ThreadPanels = gcnew List<ThreadPanel^>();
				this->array_CheckBoxAlgorithm = gcnew array<CheckBox^>(getAlgorithmEnumCount());

				//Array initialisieren
				this->textBox_ArraySize->Text = aLength.ToString();
				for (int i = 0; i < aLength; i++)
					this->array_IntValues[i] = a[i];

				//CheckBox Array initialisieren
				for (int i = 0; i < getAlgorithmEnumCount(); i++)
					this->array_CheckBoxAlgorithm[i] = initCheckBox(i);

				//die Liste mit erzeugten Checkboxen zu dem flowLayoutPanel hinzufügen
				for (int i = 0; i < array_CheckBoxAlgorithm->Length; i++)
					this->flowLayoutPanel_CheckBox->Controls->Add(array_CheckBoxAlgorithm[i]);
			}
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~Hauptfenster()
		{
			if (components)
			{
				delete components;
			}
		}

#pragma region Member		
	private: array<int>^ array_IntValues;// Array mit int werten der Sortiert werden soll; Array aus dem Hauptfenster der an die Threadpanel verteilt wird		   
	private: array<CheckBox^>^ array_CheckBoxAlgorithm;// Array mit dynamisch generierten Checkboxen für die Algorithmen		   
	private: List<ThreadPanel^>^ list_ThreadPanels;// Collection für ThreadPanel der Algorithmen
		   //Automatisch generierte Forms
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel_Algorithms;
	private: System::Windows::Forms::Button^ button_RandomArray;
	private: System::Windows::Forms::Button^ button_RunAlgorithms;
	private: System::Windows::Forms::Button^ button_ReversedArray;
	private: System::Windows::Forms::Button^ button_AlmostSortedArray;
	private: System::Windows::Forms::Button^ button_OnePieceSwapArray;
	private: System::Windows::Forms::Button^ button_SortedArray;
	private: System::Windows::Forms::Button^ button_Stop;
	private: System::Windows::Forms::TextBox^ textBox_TickInterval;
	private: System::Windows::Forms::TextBox^ textBox_ArraySize;
	private: System::Windows::Forms::Label^ label_TickRate;
	private: System::Windows::Forms::Label^ label_ArraySize;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel_CheckBox;
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ tsmi_Menu;
	private: System::Windows::Forms::ToolStripMenuItem^ tsmi_Info;
	private: System::Windows::Forms::ToolStripMenuItem^ tsmi_Help;
	private: System::Windows::Forms::ToolStripMenuItem^ tsmi_Close;
	private: System::Windows::Forms::GroupBox^ groupBox_Options;

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::IContainer^ components;
#pragma endregion

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->flowLayoutPanel_Algorithms = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->button_RandomArray = (gcnew System::Windows::Forms::Button());
			this->button_RunAlgorithms = (gcnew System::Windows::Forms::Button());
			this->button_ReversedArray = (gcnew System::Windows::Forms::Button());
			this->button_AlmostSortedArray = (gcnew System::Windows::Forms::Button());
			this->button_OnePieceSwapArray = (gcnew System::Windows::Forms::Button());
			this->button_SortedArray = (gcnew System::Windows::Forms::Button());
			this->button_Stop = (gcnew System::Windows::Forms::Button());
			this->textBox_TickInterval = (gcnew System::Windows::Forms::TextBox());
			this->textBox_ArraySize = (gcnew System::Windows::Forms::TextBox());
			this->label_TickRate = (gcnew System::Windows::Forms::Label());
			this->label_ArraySize = (gcnew System::Windows::Forms::Label());
			this->flowLayoutPanel_CheckBox = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->tsmi_Menu = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tsmi_Info = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tsmi_Help = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tsmi_Close = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->groupBox_Options = (gcnew System::Windows::Forms::GroupBox());
			this->menuStrip1->SuspendLayout();
			this->groupBox_Options->SuspendLayout();
			this->SuspendLayout();
			// 
			// flowLayoutPanel_Algorithms
			// 
			this->flowLayoutPanel_Algorithms->BackColor = System::Drawing::SystemColors::MenuHighlight;
			this->flowLayoutPanel_Algorithms->Location = System::Drawing::Point(12, 27);
			this->flowLayoutPanel_Algorithms->Name = L"flowLayoutPanel_Algorithms";
			this->flowLayoutPanel_Algorithms->Size = System::Drawing::Size(918, 688);
			this->flowLayoutPanel_Algorithms->TabIndex = 7;
			// 
			// button_RandomArray
			// 
			this->button_RandomArray->Location = System::Drawing::Point(9, 484);
			this->button_RandomArray->Name = L"button_RandomArray";
			this->button_RandomArray->Size = System::Drawing::Size(117, 23);
			this->button_RandomArray->TabIndex = 8;
			this->button_RandomArray->Text = L"Random";
			this->button_RandomArray->UseVisualStyleBackColor = true;
			this->button_RandomArray->Click += gcnew System::EventHandler(this, &Hauptfenster::button_RandomArray_Click);
			// 
			// button_RunAlgorithms
			// 
			this->button_RunAlgorithms->BackColor = System::Drawing::Color::Green;
			this->button_RunAlgorithms->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->button_RunAlgorithms->Location = System::Drawing::Point(9, 658);
			this->button_RunAlgorithms->Name = L"button_RunAlgorithms";
			this->button_RunAlgorithms->Size = System::Drawing::Size(117, 23);
			this->button_RunAlgorithms->TabIndex = 9;
			this->button_RunAlgorithms->Text = L"Start";
			this->button_RunAlgorithms->UseVisualStyleBackColor = false;
			this->button_RunAlgorithms->Click += gcnew System::EventHandler(this, &Hauptfenster::button_RunAlgorithms_Click);
			// 
			// button_ReversedArray
			// 
			this->button_ReversedArray->Location = System::Drawing::Point(9, 513);
			this->button_ReversedArray->Name = L"button_ReversedArray";
			this->button_ReversedArray->Size = System::Drawing::Size(117, 23);
			this->button_ReversedArray->TabIndex = 10;
			this->button_ReversedArray->Text = L"Reversed";
			this->button_ReversedArray->UseVisualStyleBackColor = true;
			this->button_ReversedArray->Click += gcnew System::EventHandler(this, &Hauptfenster::button_ReversedArray_Click);
			// 
			// button_AlmostSortedArray
			// 
			this->button_AlmostSortedArray->Location = System::Drawing::Point(9, 542);
			this->button_AlmostSortedArray->Name = L"button_AlmostSortedArray";
			this->button_AlmostSortedArray->Size = System::Drawing::Size(117, 23);
			this->button_AlmostSortedArray->TabIndex = 11;
			this->button_AlmostSortedArray->Text = L"Almost Sorted";
			this->button_AlmostSortedArray->UseVisualStyleBackColor = true;
			this->button_AlmostSortedArray->Click += gcnew System::EventHandler(this, &Hauptfenster::button_AlmostSortedArray_Click);
			// 
			// button_OnePieceSwapArray
			// 
			this->button_OnePieceSwapArray->Location = System::Drawing::Point(9, 571);
			this->button_OnePieceSwapArray->Name = L"button_OnePieceSwapArray";
			this->button_OnePieceSwapArray->Size = System::Drawing::Size(117, 23);
			this->button_OnePieceSwapArray->TabIndex = 12;
			this->button_OnePieceSwapArray->Text = L"One Piece Swap";
			this->button_OnePieceSwapArray->UseVisualStyleBackColor = true;
			this->button_OnePieceSwapArray->Click += gcnew System::EventHandler(this, &Hauptfenster::button_OnePieceSwapArray_Click);
			// 
			// button_SortedArray
			// 
			this->button_SortedArray->Location = System::Drawing::Point(9, 600);
			this->button_SortedArray->Name = L"button_SortedArray";
			this->button_SortedArray->Size = System::Drawing::Size(117, 23);
			this->button_SortedArray->TabIndex = 13;
			this->button_SortedArray->Text = L"Sorted";
			this->button_SortedArray->UseVisualStyleBackColor = true;
			this->button_SortedArray->Click += gcnew System::EventHandler(this, &Hauptfenster::button_SortedArray_Click);
			// 
			// button_Stop
			// 
			this->button_Stop->BackColor = System::Drawing::Color::Red;
			this->button_Stop->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button_Stop->Location = System::Drawing::Point(9, 629);
			this->button_Stop->Name = L"button_Stop";
			this->button_Stop->Size = System::Drawing::Size(117, 23);
			this->button_Stop->TabIndex = 14;
			this->button_Stop->Text = L"Stop";
			this->button_Stop->UseVisualStyleBackColor = false;
			this->button_Stop->Click += gcnew System::EventHandler(this, &Hauptfenster::button_Stop_Click);
			// 
			// textBox_TickInterval
			// 
			this->textBox_TickInterval->Location = System::Drawing::Point(76, 432);
			this->textBox_TickInterval->MaxLength = 4;
			this->textBox_TickInterval->Name = L"textBox_TickInterval";
			this->textBox_TickInterval->Size = System::Drawing::Size(50, 20);
			this->textBox_TickInterval->TabIndex = 16;
			this->textBox_TickInterval->Text = L"50";
			this->textBox_TickInterval->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBox_TickInterval->TextChanged += gcnew System::EventHandler(this, &Hauptfenster::textBox_TickInterval_TextChanged);
			this->textBox_TickInterval->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Hauptfenster::textBox_TickInterval_KeyPress);
			// 
			// textBox_ArraySize
			// 
			this->textBox_ArraySize->Location = System::Drawing::Point(76, 458);
			this->textBox_ArraySize->MaxLength = 3;
			this->textBox_ArraySize->Name = L"textBox_ArraySize";
			this->textBox_ArraySize->Size = System::Drawing::Size(50, 20);
			this->textBox_ArraySize->TabIndex = 17;
			this->textBox_ArraySize->Text = L"30";
			this->textBox_ArraySize->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBox_ArraySize->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Hauptfenster::textBox_ArraySize_KeyPress);
			// 
			// label_TickRate
			// 
			this->label_TickRate->AutoSize = true;
			this->label_TickRate->Location = System::Drawing::Point(6, 435);
			this->label_TickRate->Name = L"label_TickRate";
			this->label_TickRate->Size = System::Drawing::Size(68, 13);
			this->label_TickRate->TabIndex = 18;
			this->label_TickRate->Text = L"Tickrate(ms):";
			// 
			// label_ArraySize
			// 
			this->label_ArraySize->AutoSize = true;
			this->label_ArraySize->Location = System::Drawing::Point(6, 461);
			this->label_ArraySize->Name = L"label_ArraySize";
			this->label_ArraySize->Size = System::Drawing::Size(53, 13);
			this->label_ArraySize->TabIndex = 19;
			this->label_ArraySize->Text = L"Elements:";
			// 
			// flowLayoutPanel_CheckBox
			// 
			this->flowLayoutPanel_CheckBox->Location = System::Drawing::Point(6, 19);
			this->flowLayoutPanel_CheckBox->Name = L"flowLayoutPanel_CheckBox";
			this->flowLayoutPanel_CheckBox->Size = System::Drawing::Size(117, 407);
			this->flowLayoutPanel_CheckBox->TabIndex = 28;
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->tsmi_Menu });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1077, 24);
			this->menuStrip1->TabIndex = 29;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// tsmi_Menu
			// 
			this->tsmi_Menu->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->tsmi_Info,
					this->tsmi_Help, this->tsmi_Close
			});
			this->tsmi_Menu->Name = L"tsmi_Menu";
			this->tsmi_Menu->Size = System::Drawing::Size(50, 20);
			this->tsmi_Menu->Text = L"Menü";
			// 
			// tsmi_Info
			// 
			this->tsmi_Info->Name = L"tsmi_Info";
			this->tsmi_Info->Size = System::Drawing::Size(180, 22);
			this->tsmi_Info->Text = L"Info";
			this->tsmi_Info->Click += gcnew System::EventHandler(this, &Hauptfenster::tsmi_Info_Click);
			// 
			// tsmi_Help
			// 
			this->tsmi_Help->Name = L"tsmi_Help";
			this->tsmi_Help->Size = System::Drawing::Size(180, 22);
			this->tsmi_Help->Text = L"Anleitung";
			this->tsmi_Help->Click += gcnew System::EventHandler(this, &Hauptfenster::tsmi_Help_Click);
			// 
			// tsmi_Close
			// 
			this->tsmi_Close->Name = L"tsmi_Close";
			this->tsmi_Close->Size = System::Drawing::Size(180, 22);
			this->tsmi_Close->Text = L"Schließen";
			this->tsmi_Close->Click += gcnew System::EventHandler(this, &Hauptfenster::tsmi_Close_Click);
			// 
			// groupBox_Options
			// 
			this->groupBox_Options->Controls->Add(this->flowLayoutPanel_CheckBox);
			this->groupBox_Options->Controls->Add(this->label_ArraySize);
			this->groupBox_Options->Controls->Add(this->label_TickRate);
			this->groupBox_Options->Controls->Add(this->button_RandomArray);
			this->groupBox_Options->Controls->Add(this->textBox_ArraySize);
			this->groupBox_Options->Controls->Add(this->button_RunAlgorithms);
			this->groupBox_Options->Controls->Add(this->textBox_TickInterval);
			this->groupBox_Options->Controls->Add(this->button_ReversedArray);
			this->groupBox_Options->Controls->Add(this->button_Stop);
			this->groupBox_Options->Controls->Add(this->button_AlmostSortedArray);
			this->groupBox_Options->Controls->Add(this->button_SortedArray);
			this->groupBox_Options->Controls->Add(this->button_OnePieceSwapArray);
			this->groupBox_Options->Location = System::Drawing::Point(936, 27);
			this->groupBox_Options->Name = L"groupBox_Options";
			this->groupBox_Options->Size = System::Drawing::Size(134, 688);
			this->groupBox_Options->TabIndex = 30;
			this->groupBox_Options->TabStop = false;
			this->groupBox_Options->Text = L"Optionen";
			// 
			// Hauptfenster
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->ClientSize = System::Drawing::Size(1077, 722);
			this->Controls->Add(this->groupBox_Options);
			this->Controls->Add(this->flowLayoutPanel_Algorithms);
			this->Controls->Add(this->menuStrip1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MainMenuStrip = this->menuStrip1;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"Hauptfenster";
			this->Text = L"Visuelle Darstellung von Sortier Algorithmen";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Hauptfenster::Hauptfenster_FormClosing);
			this->Load += gcnew System::EventHandler(this, &Hauptfenster::Hauptfenster_Load);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->groupBox_Options->ResumeLayout(false);
			this->groupBox_Options->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

#pragma region Event Methoden
		/// <summary>
		/// Lädt bei Programmstart die Dynamisch erzeugten Threadpanel
		/// </summary>
	private: System::Void Hauptfenster_Load(System::Object^ sender, System::EventArgs^ e);

		   /// <summary>
		   /// mischt die Werte von (array_IntValues) zufällig und weist allen ThreadPanels den Array zu
		   /// </summary>
	private: System::Void button_RandomArray_Click(System::Object^ sender, System::EventArgs^ e);

		   /// <summary>
		   /// vertauscht die Werte von (array_IntValues) absteigend und weist allen ThreadPanels den Array zu
		   /// </summary>
	private: System::Void button_ReversedArray_Click(System::Object^ sender, System::EventArgs^ e);

		   /// <summary>
		   /// vertauscht ungerade mit geraden Werten von (array_IntValues)und weist allen ThreadPanels den Array zu
		   /// </summary>
	private: System::Void button_AlmostSortedArray_Click(System::Object^ sender, System::EventArgs^ e);

		   /// <summary>
		   /// vertauscht nur 2 Werte von (array_IntValues) miteinander und weist allen ThreadPanels den Array zu
		   /// </summary>
	private: System::Void button_OnePieceSwapArray_Click(System::Object^ sender, System::EventArgs^ e);

		   /// <summary>
		   /// (array_IntValues) mit vorsortierten Werten; weist allen ThreadPanels den Array zu
		   /// </summary>
	private: System::Void button_SortedArray_Click(System::Object^ sender, System::EventArgs^ e);

		   /// <summary>
		   /// Aufruf der ThreadStart-Methode aller Threadpanels
		   /// </summary>
	private: System::Void button_RunAlgorithms_Click(System::Object^ sender, System::EventArgs^ e);

		   /// <summary>
		   /// in allen ThreadPanels werden die Threads beendet
		   /// </summary>
	private: System::Void button_Stop_Click(System::Object^ sender, System::EventArgs^ e);

		   /// <summary>
		   /// Abfangen von nicht Zahlenwerten, (Copy-Paste ist nicht behandelt)
		   /// </summary>
	private: System::Void textBox_TickInterval_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e);

		   /// <summary>
		   /// Abfangen von nicht Zahlenwerten, (Copy-Paste ist nicht behandelt)
		   /// </summary>
	private: System::Void textBox_ArraySize_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e);

		   /// <summary>
		   /// Zuweisen des Algorithmen TickIntervals/Thread.Sleep an die ThreadPanels
		   /// </summary>
	private: System::Void textBox_TickInterval_TextChanged(System::Object^ sender, System::EventArgs^ e);

		   /// <summary>
		   /// Überladen der Funktion zum schließen des Fensters, um abzufangen das Threads noch laufen bevor das Fenster schließt
		   /// </summary>
	private: System::Void Hauptfenster_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e);

		   /// <summary>
		   /// MenuPunkt zum Schließen des Fensters
		   /// </summary>
	private: System::Void tsmi_Close_Click(System::Object^ sender, System::EventArgs^ e);

		   /// <summary>
		   /// MenuPunkt zum anzeigen der Programm Information
		   /// </summary>
	private: System::Void tsmi_Info_Click(System::Object^ sender, System::EventArgs^ e);

		   /// <summary>
		   /// MenuPunkt zum anzeigen der Programm Hilfe
		   /// </summary>
	private: System::Void tsmi_Help_Click(System::Object^ sender, System::EventArgs^ e);

#pragma endregion

#pragma region Allgemeingültige Methoden
		   /// <summary>
		   /// Methode zum initialisieren der ThreadPanel
		   /// </summary>
	private: void initThreadPanels();

		   /// <summary>
		   /// setzt für alle ThreadPanel die neuen ArrayWerte
		   /// </summary>
	private: void setAllArrays();

		   /// <summary>
		   /// Handling-Methode der Dynamischen Checkboxen
		   /// </summary>	
	private: System::Void checkBox_All_CheckedChanged(System::Object^ sender, System::EventArgs^ e);

		   /// <summary>
		   /// initialisieren der dynamischen Checkboxen
		   /// </summary>
	private: System::Windows::Forms::CheckBox^ initCheckBox(int enumAlgorithm);
#pragma endregion
	};
}