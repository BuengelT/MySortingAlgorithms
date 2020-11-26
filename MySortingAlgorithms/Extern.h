#pragma once

using namespace System;

//WICHTIG: Bei Änderung des letzten Enum-Elementes muss dieses ebenfalls in der Funtkion getAlgorithmEnumCount(); angepasst werden
//WICHTIG: Bei hinzufügen neuer Algorithmen Anpassung von der Funktion algorithmTypeToString()
enum class AlgorithmType { QuickSort, BubbleSort, SelectionSort, HeapSort, InsertionSort, MergeSort, ShellSort, RadixSort };

enum class ArrayType { random, reversed, sorted, onepiece, almostsorted };

/// <summary>
/// Tauscht 2 Elemente eines managed Arrays miteinander
/// </summary>
void swap(array<int>^ arr, int a, int b);

/// <summary>
/// erstellt einen neuen Array
/// </summary>
array<int>^ createArray(ArrayType aType, int arrLength);

/// <summary>
/// gibt für einen AlgorithmType den entsprechenden String zurück
/// </summary>
String^ algorithmTypeToString(AlgorithmType type);

/// <summary>
/// Ermittelt den maximalen Wert eines Arrays
/// </summary>
int findMaxValue(array<int>^ arr);

/// <summary>
/// liefert die Anzahl des Algorithm Enum
/// </summary>
int getAlgorithmEnumCount();





