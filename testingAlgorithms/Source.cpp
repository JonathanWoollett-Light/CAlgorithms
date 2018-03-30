#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <time.h>
#include <vector>
#include <algorithm>

const int	n = 3, k = 1000;

void quickSort(int set[], int left = 0, int right = n - 1);
int partition(int set[], int left, int right);
void swap(int * a, int * b);

void mergeSort(int set[], int left = 0, int right = n - 1);
void merge(int set[], int left, int mid, int right);

void countingSort(int set[]);

void insertionSort(int set[]);

void bucketSort(int set[]);

int binarySearch(int value, const int set[]);
int linearSearch(int value, int set[]);
int linearSearch(int value, int set[]);

void printSet(int set[]);
void printSet(const std::vector<int> & set);
void printSet(const std::vector<std::vector<int>> & set);

std::vector<std::vector<int>> getOrders(const std::vector<int> & set);
std::vector<int> shiftAroundIndex(const std::vector<int> & set, int index, int numbOfShifts);
std::vector<int> shiftArray(const std::vector<int> & set, int numbOfShifts);

int main()
{
	/*
	srand(time(NULL));
	int intArray[n];
	for (int i = 0; i < n; i++)
	{
		intArray[i] = rand() % k;
	}
	bucketSort(intArray);
	*/

	std::vector<int> orderArray;
	for (int i = 0; i < n; i++) {
		orderArray.push_back(i);
	}
	std::vector<std::vector<int>> orders = getOrders(orderArray);
	printSet(orders);
	std::cout << "Combinations: " << orders.size() << std::endl;
	system("pause");
	return 0;
}
//----------------------------------------All orders of set---------------------------------------


std::vector<std::vector<int>> getOrders(const std::vector<int> & set) {
	std::vector<std::vector<int>> returnArray;//vector to contain all orderings
	std::vector<int> checkingHolder;//vector to hold current ordering being calculated
	for (int i = 0; i < n; i++) {
		returnArray.push_back(shiftArray(set, i));//getting all basic rotations E.g. for {1,2,3} this would be {3,1,2}, {2,3,1} and {1,2,3}
	}
	bool repeatedSet;
	for (int i = 0; i < n; i++) {//basic rotation to adapt
		for (int t = 0; t < n; t++) {//index to rotate around
			repeatedSet = false;
			for (int u = 1; true; u++) {//how many times to rotate around index
				checkingHolder = shiftAroundIndex(returnArray[i], t, u);
				for (int q = 0; q < returnArray.size(); q++) {
					if (returnArray[q] == checkingHolder) {//if new order has already been calculated
						repeatedSet = true;
						break;
					}
				}
				if (repeatedSet) {
					/* if new order has already been calculated then 
					 * further rotations will produce more orders that have also been already calculated
					*/
					break;
				}
				returnArray.push_back(checkingHolder);//push newly calculated order to vector of all previously calculated orderings
			}
		}
	}
	return returnArray;
}

std::vector<int> shiftAroundIndex(const std::vector<int> & set, int index, int numbOfShifts) {
	std::vector<int> holder (set);
	if (numbOfShifts > 0) {
		for (int i = 0; i < holder.size(); i++) {
			if (i == index) {
				continue;
			}
			if (i + 1 == index) {
				if (index == holder.size() - 1) {
					holder[0] = set[i];
				}
				else {
					holder[i + 2] = set[i];
				}
			}
			else if (i == holder.size() - 1) {
				if (index == 0) {
					holder[1] = set[i];
				}
				else {
					holder[0] = set[i];
				}
			}
			else {
				holder[i + 1] = set[i];
			}
		}
		if (numbOfShifts > 1) {
			return shiftAroundIndex(holder, index, numbOfShifts - 1);
		}
	}
	return holder;
}

std::vector<int> shiftArray(const std::vector<int> & set, int numbOfShifts) {
	std::vector<int> holder (set);

	if (numbOfShifts > 0) {
		for (int i = 1; i < holder.size() + 1; i++) {
			if (i == holder.size()) {
				holder[0] = set[i - 1];
			}
			else {
				holder[i] = set[i - 1];
			}
		}
		if (numbOfShifts > 1) {
			return shiftArray(holder, numbOfShifts - 1);
		}
	}
	return holder;
}


//------------------------------------------Insertion sort----------------------------------------

void insertionSort(int set[])
{
	for (int i = 1; i < n; i++)
	{
		for (int t = i - 1; set[t + 1] < set[t]; t--) {
			swap(&set[t], &set[t + 1]);
		}
	}
}

//-------------------------------------------Bucket sort------------------------------------------

void bucketSort(int set[])
{
	std::vector<int> buckets[n];

	for (int i = 0; i < n; i++)
	{
		buckets[n * set[i]].push_back(set[i]);
	}
	for (int i = 0; i < n; i++)
	{
		std::sort(buckets[i].begin(), buckets[i].end());
	}
	int index = 0;
	for (int i = 0; i < n; i++)
	{
		for (int t = 0; t < buckets[i].size(); t++)
		{
			set[index++] = buckets[i][t];
		}
	}
}

//------------------------------------------Counting sort-----------------------------------------

void countingSort(int set[])
{
	int * indexSet = new int[k]();
	for (int i = 0; i < n; i++)
	{
		indexSet[set[i]]++;
	}
	for (int i = 1; i < k; i++)
	{
		indexSet[i] += indexSet[i - 1];
	}
	int * sortedSet = new int[n];
	for (int i = 0; i < n; i++)
	{
		sortedSet[indexSet[set[i]] - 1] = set[i];
		indexSet[set[i]]--;
	}
	std::memcpy(set, sortedSet, n * sizeof int());
}

//-------------------------------------------Merge sort-------------------------------------------

void merge(int set[], int left, int mid, int right)
{
	int leftArrayIndex, rightArrayIndex, mergedArrayIndex;

	int leftArraySize = mid - left + 1,
		rightArraySize = right - mid;

	int * leftArray = new int[leftArraySize],
		* rightArray = new int[rightArraySize];

	for (leftArrayIndex = 0; leftArrayIndex < leftArraySize; leftArrayIndex++)
		leftArray[leftArrayIndex] = set[left + leftArrayIndex];
	for (rightArrayIndex = 0; rightArrayIndex < rightArraySize; rightArrayIndex++)
		rightArray[rightArrayIndex] = set[mid + 1 + rightArrayIndex];

	leftArrayIndex = 0;
	rightArrayIndex = 0;
	mergedArrayIndex = left;
	while (leftArrayIndex < leftArraySize && rightArrayIndex < rightArraySize)
	{
		if (leftArray[leftArrayIndex] <= rightArray[rightArrayIndex])
		{
			set[mergedArrayIndex] = leftArray[leftArrayIndex];
			leftArrayIndex++;
		}
		else
		{
			set[mergedArrayIndex] = rightArray[rightArrayIndex];
			rightArrayIndex++;
		}
		mergedArrayIndex++;
	}

	while (leftArrayIndex < leftArraySize)
	{
		set[mergedArrayIndex] = leftArray[leftArrayIndex];
		leftArrayIndex++;
		mergedArrayIndex++;
	}

	while (rightArrayIndex < rightArraySize)
	{
		set[mergedArrayIndex] = rightArray[rightArrayIndex];
		rightArrayIndex++;
		mergedArrayIndex++;
	}
}

void mergeSort(int set[], int left, int right)
{
	if (left < right)
	{
		int mid = left + ((right - left) / 2);

		mergeSort(set, left, mid);
		mergeSort(set, mid + 1, right);

		merge(set, left, mid, right);
	}
}

//-------------------------------------------Quick sort-------------------------------------------

void quickSort(int set[], int left, int right)
{
	if (left < right) 
	{
		int pivot = partition(set, left, right);

		quickSort(set, left, pivot - 1);
		quickSort(set, pivot + 1, right);
	}
}

int partition(int set[], int left, int right) 
{
	int pivot = set[right];

	for (int j = left; j <= right - 1; j++)
	{
		if (set[j] <= pivot)
		{
			left++;
			swap(&set[left - 1], &set[j]);
		}
	}
	swap(&set[left], &set[right]);
	return left;
}

void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

//------------------------------------------Binary search-----------------------------------------

int binarySearch(int value, int set[])
{
	int left = 0,
		right = n - 1,
		mid,
		found = -1;
	while (left <= right)
	{
		mid = left + ((right - left) / 2);
		if (set[mid] > value)
		{
			right = mid - 1;
		}
		else if (set[mid] < value)
		{
			left = mid + 1;
		}
		else
		{
			std::cout << value << " found at index " << mid << std::endl;
			return 1;
		}
	}
	std::cout << "Value does not exist in array" << std::endl;
	return 0;
}

//------------------------------------------Linear search-----------------------------------------

int linearSearch(int value, int set[])
{
	for (int i = 0; i < n; i++)
	{
		if (set[i] == value) {
			std::cout << value << " found at index " << i << std::endl;
			return 1;
		}
	}
	std::cout << "Value does not exist in array" << std::endl;
	return 0;
}
//-------------------------------------------Print set------------------------------------------

void printSet(int set[]) 
{
	std::cout << "\n{" << set[0];
	for (int i = 1; i < n; i++)
	{
		std::cout << "," << set[i];
	}
	std::cout << "}";
}

void printSet(const std::vector<int> & set)
{
	std::cout << "\n{" << set[0];
	for (int i = 1; i < set.size(); i++)
	{
		std::cout << "," << set[i];
	}
	std::cout << "}";
}

void printSet(const std::vector<std::vector<int>> & set)
{
	std::cout << "\n{";
	for (int i = 0; i < set.size(); i++)
	{
		printSet(set[i]);
	}
	std::cout << "\n}\n";
}

