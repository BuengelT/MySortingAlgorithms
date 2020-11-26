#include "Hauptfenster.h"

#pragma region Event Methoden
/// <summary>
/// Lädt bei Programmstart die Dynamisch erzeugten Threadpanel
/// </summary>
System::Void MySortingAlgorithms::Hauptfenster::Hauptfenster_Load(System::Object^ sender, System::EventArgs^ e)
{
	initThreadPanels();
}

/// <summary>
/// mischt die Werte von (array_IntValues) zufällig und weist allen ThreadPanels den Array zu
/// </summary>
System::Void MySortingAlgorithms::Hauptfenster::button_RandomArray_Click(System::Object^ sender, System::EventArgs^ e)
{
	this->array_IntValues = createArray(ArrayType::random, Convert::ToInt32(this->textBox_ArraySize->Text));
	setAllArrays();
}

/// <summary>
/// vertauscht die Werte von (array_IntValues) absteigend und weist allen ThreadPanels den Array zu
/// </summary>
System::Void MySortingAlgorithms::Hauptfenster::button_ReversedArray_Click(System::Object^ sender, System::EventArgs^ e)
{
	this->array_IntValues = createArray(ArrayType::reversed, Convert::ToInt32(this->textBox_ArraySize->Text));
	setAllArrays();
}

/// <summary>
/// vertauscht ungerade mit geraden Werten von (array_IntValues)und weist allen ThreadPanels den Array zu
/// </summary>
System::Void MySortingAlgorithms::Hauptfenster::button_AlmostSortedArray_Click(System::Object^ sender, System::EventArgs^ e)
{
	this->array_IntValues = createArray(ArrayType::almostsorted, Convert::ToInt32(this->textBox_ArraySize->Text));
	setAllArrays();
}

/// <summary>
/// vertauscht nur 2 Werte von (array_IntValues) miteinander und weist allen ThreadPanels den Array zu
/// </summary>
System::Void MySortingAlgorithms::Hauptfenster::button_OnePieceSwapArray_Click(System::Object^ sender, System::EventArgs^ e)
{
	this->array_IntValues = createArray(ArrayType::onepiece, Convert::ToInt32(this->textBox_ArraySize->Text));
	setAllArrays();
}

/// <summary>
/// (array_IntValues) mit vorsortierten Werten; weist allen ThreadPanels den Array zu
/// </summary>
System::Void MySortingAlgorithms::Hauptfenster::button_SortedArray_Click(System::Object^ sender, System::EventArgs^ e)
{
	this->array_IntValues = createArray(ArrayType::sorted, Convert::ToInt32(this->textBox_ArraySize->Text));
	setAllArrays();
}

/// <summary>
/// Aufruf der ThreadStart-Methode aller Threadpanels
/// </summary>
System::Void MySortingAlgorithms::Hauptfenster::button_RunAlgorithms_Click(System::Object^ sender, System::EventArgs^ e)
{
	for (int i = 0; i < this->list_ThreadPanels->Count; i++)
	{
		this->list_ThreadPanels[i]->button_Pause_Click(nullptr, nullptr);
		this->list_ThreadPanels[i]->button_StartAlgorithm_Click(nullptr, nullptr);
	}
}

/// <summary>
/// in allen ThreadPanels werden die Threads beendet
/// </summary>
System::Void MySortingAlgorithms::Hauptfenster::button_Stop_Click(System::Object^ sender, System::EventArgs^ e)
{
	for (int i = 0; i < this->list_ThreadPanels->Count; i++)
	{
		this->list_ThreadPanels[i]->button_Pause_Click(nullptr, nullptr);
	}
}

/// <summary>
/// Abfangen von nicht Zahlenwerten, (Copy-Paste ist nicht behandelt)
/// </summary>
System::Void MySortingAlgorithms::Hauptfenster::textBox_TickInterval_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e)
{
	e->Handled = !Char::IsDigit(e->KeyChar) && !Char::IsControl(e->KeyChar);
}

/// <summary>
/// Abfangen von nicht Zahlenwerten, (Copy-Paste ist nicht behandelt)
/// </summary>
System::Void MySortingAlgorithms::Hauptfenster::textBox_ArraySize_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e)
{
	e->Handled = !Char::IsDigit(e->KeyChar) && !Char::IsControl(e->KeyChar);
}

/// <summary>
/// Zuweisen des Algorithmen TickIntervals/Thread.Sleep an die ThreadPanels
/// </summary>
System::Void MySortingAlgorithms::Hauptfenster::textBox_TickInterval_TextChanged(System::Object^ sender, System::EventArgs^ e)
{
	for (int i = 0; i < this->list_ThreadPanels->Count; i++)
	{
		if (!String::IsNullOrEmpty(this->textBox_TickInterval->Text))
			this->list_ThreadPanels[i]->setDrawInterval(Convert::ToInt32(this->textBox_TickInterval->Text));
	}
}

/// <summary>
/// Überladen der Funktion zum schließen des Fensters, um abzufangen das Threads noch laufen bevor das Fenster schließt
/// </summary>
System::Void MySortingAlgorithms::Hauptfenster::Hauptfenster_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e)
{
	for (int i = 0; i < this->list_ThreadPanels->Count; i++)
	{
		this->list_ThreadPanels[i]->button_Pause_Click(nullptr, nullptr);
	}
	Thread::Sleep(100);
}

/// <summary>
/// MenuPunkt zum Schließen des Fensters
/// </summary>
System::Void MySortingAlgorithms::Hauptfenster::tsmi_Close_Click(System::Object^ sender, System::EventArgs^ e)
{
	Hauptfenster_FormClosing(nullptr, nullptr);
	this->Close();
}

/// <summary>
/// MenuPunkt zum anzeigen der Programm Information
/// </summary>
System::Void MySortingAlgorithms::Hauptfenster::tsmi_Info_Click(System::Object^ sender, System::EventArgs^ e)
{
	MessageBox::Show("Author: Timm Büngel" + Environment::NewLine		
		+ "Copyright 2020", "Info");
}

/// <summary>
/// MenuPunkt zum anzeigen der Programm Hilfe
/// </summary>
System::Void MySortingAlgorithms::Hauptfenster::tsmi_Help_Click(System::Object^ sender, System::EventArgs^ e)
{
	MessageBox::Show("Funktionsbeschreibung:" + Environment::NewLine + Environment::NewLine
		+ "1. Im Oberen Bereich der Optionen ist durch markieren der jeweilige Sortier-Algorithmus festzulegen, welche Algorithmen angezeigt werden." + Environment::NewLine + Environment::NewLine
		+ "2. mit der Tickrate kann die Geschwidigkeit für die Sortieralgorithmen festgelegt werden. Angabe in Milliesekunden.*" + Environment::NewLine + Environment::NewLine
		+ "3. Elemets erlaubt die Festlegung über die Anzahlder zu Sortierenden Elemente.*" + Environment::NewLine + Environment::NewLine
		+ "4. Über die Optionen: Random, Reversed, Almost Sorted, One Piece Swap und Sorted, lassen sich die Elemente nach einem Muster anordnen.*" + Environment::NewLine + Environment::NewLine
		+ "5. Über Start und Stop werden die Algorithmen gestartet/beendet.*" + Environment::NewLine + Environment::NewLine
		+ "Darüber hinaus verfügt jeder Algorithmus über einen eigenen Start/Stop Mechanismus, sowie eine RND-Funktion mit der die Elemente Zufällig gemischt werden." + Environment::NewLine + Environment::NewLine
		+ "*Diese Option wird für Alle Algoritmen festgelegt."
		, "Hilfe");
}
#pragma endregion

#pragma region Allgemeingültige Methoden
/// <summary>
/// Methode zum initialisieren der ThreadPanel
/// </summary>
void MySortingAlgorithms::Hauptfenster::initThreadPanels()
{
	//Liste leeren bevor neue Elemente hinzugefügt werden
	this->list_ThreadPanels->Clear();

	//x ThreadPanel-Elemente zu der Liste hinzufügen 
	for (int i = 0; i < this->array_CheckBoxAlgorithm->Length; i++)
	{
		if (this->array_CheckBoxAlgorithm[i]->Checked)
		{
			ThreadPanel^ element = gcnew MySortingAlgorithms::ThreadPanel(this->array_IntValues);
			element->setAlgorithmType(static_cast<AlgorithmType>(i));
			element->setLabelAlgorithmName(algorithmTypeToString(static_cast<AlgorithmType>(i)));
			this->list_ThreadPanels->Add(element);
		}
	}

	// Wenn sich Elemente im flowLayoutPanel_Algorithms, wird dieser geleert
	if (this->flowLayoutPanel_Algorithms->Controls->Count > 0)
		this->flowLayoutPanel_Algorithms->Controls->Clear();

	// Die Liste der ThreadPanels zu dem flowLayoutPanel hinzufügen
	for (int i = 0; i < this->list_ThreadPanels->Count; i++)
	{
		this->list_ThreadPanels[i]->setDrawInterval(Convert::ToInt32(textBox_TickInterval->Text));
		this->flowLayoutPanel_Algorithms->Controls->Add(this->list_ThreadPanels[i]);
	}
}

/// <summary>
/// setzt für alle ThreadPanel die neuen ArrayWerte
/// </summary>
void MySortingAlgorithms::Hauptfenster::setAllArrays()
{
	for (int i = 0; i < this->list_ThreadPanels->Count; i++)
	{
		// Thread Stoppen falls dieser bereits läuft
		this->list_ThreadPanels[i]->button_Pause_Click(nullptr, nullptr);
		// Neuen Array festlegen
		this->list_ThreadPanels[i]->setArrayIntValues(this->array_IntValues);
		// Neuen Array Zeichen/Werte berechnen
		this->list_ThreadPanels[i]->calcVarDrawPanel();
		// Array einmal Zeichnen
		this->list_ThreadPanels[i]->drawArray();
		// Anzahl der Array Elemente festlegen
		this->list_ThreadPanels[i]->setLabelArrayElements(this->array_IntValues->Length.ToString());
	}
}

/// <summary>
/// Handling-Methode der Dynamischen Checkboxen
/// </summary>	
System::Void MySortingAlgorithms::Hauptfenster::checkBox_All_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
{
	// Wird eine der Cehckboxen geändert, werden die ThreadPanels neu geladen
	initThreadPanels();
}

/// <summary>
/// initialisieren einer dynamischen Checkbox die zurückgegeben wird
/// </summary>
System::Windows::Forms::CheckBox^ MySortingAlgorithms::Hauptfenster::initCheckBox(int val)
{
	System::Windows::Forms::CheckBox^ element = (gcnew System::Windows::Forms::CheckBox());
	element->AutoSize = true;
	element->Checked = true;
	element->CheckState = System::Windows::Forms::CheckState::Checked;
	element->Text = algorithmTypeToString(static_cast<AlgorithmType>(val));
	element->Name = "checkBox_" + algorithmTypeToString(static_cast<AlgorithmType>(val));
	element->UseVisualStyleBackColor = true;
	// Alle dynamisch erzeugten Checkboxen verwenden dieselbe Event-Methode
	element->CheckedChanged += gcnew System::EventHandler(this, &Hauptfenster::checkBox_All_CheckedChanged);
	return element;

}
#pragma endregion