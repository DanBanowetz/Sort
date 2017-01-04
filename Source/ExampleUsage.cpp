/**
 * The MIT License (MIT)
 *
 * Copyright © Daniel Adamitskiy. All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "Sort.h"
#include <ctime>
#include <functional>
#include <vector>
#include <algorithm>
#include <stdio.h>

bool AscendingOrderPredicate(int a, int b)
{
	return a < b;
}

void RandomizeContainer(std::vector<int>& container)
{
	std::random_shuffle(container.begin(), container.end());
}

void PrintContainerContents(const std::vector<int>& container)
{
	for (int i = 0; i < container.size(); ++i)
	{
		printf("%i,", container[i]);
	}

	printf("\n\n");
}

int main(int argc, char* argv[])
{
	// Seed random
	srand(static_cast<unsigned int>(time(0)));

	// Create a container with random items
	std::vector<int> container;
	for (int i = 0; i < 25; ++i) 
	{ 
		container.push_back(static_cast<int>(3.14f * (rand() % 100))); 
	}

	RandomizeContainer(container);
	const unsigned int containerSize = static_cast<unsigned int>(container.size());

	// Debug output
	printf("Unsorted container:\n");
	PrintContainerContents(container);

	// Sort with a lambda
	DA::Sort::BubbleSort<std::vector<int>>(container, containerSize, [](int a, int b) { return a < b; });
	
	// Debug output
	printf("Sorted container via bubble sort:\n");
	PrintContainerContents(container);
	RandomizeContainer(container);
	printf("Unsorted container:\n");
	PrintContainerContents(container);

	// Sort with a function pointer 
	DA::Sort::InsertionSort<std::vector<int>>(container, containerSize, AscendingOrderPredicate);

	// Debug output
	printf("Sorted container via insertion sort:\n");
	PrintContainerContents(container);
	RandomizeContainer(container);
	printf("Unsorted container:\n");
	PrintContainerContents(container);

	// Sort with std::function
	std::function<bool(int, int)> LessThanFunc = &AscendingOrderPredicate;
	DA::Sort::SelectionSort<std::vector<int>>(container, containerSize, LessThanFunc);

	// Debug output
	printf("Sorted container via selection sort:\n");
	PrintContainerContents(container);
	
	//Sort with Quick sort
	DA::Sort::RadixSort<std::vector<int>,int>(container, containerSize);

	printf("Sorted container via Radix sort:\n");
	PrintContainerContents(container);
	RandomizeContainer(container);
	printf("Unsorted container:\n");
	PrintContainerContents(container);
	
	DA::Sort::QuickSort<std::vector<int>,int>(container, [](int a, int b) { return a >= b; }, 0, containerSize-1);

	printf("Sorted container via Quick Sort:\n");
	PrintContainerContents(container);
	RandomizeContainer(container);
	printf("Unsorted container: \n");
	PrintContainerContents(container);

	system("Pause");
	return 0;
}
