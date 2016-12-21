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

#pragma once

#define DA_SORT_MAJOR_VERSION 1
#define DA_SORT_MINOR_VERSION 1

namespace DA
{
namespace Sort
{

/**
* @brief Swaps two items of generic type without needing a temporary variable.
*
* @param a - First item
* @param b - Second item
*/
template<typename Type>
inline void XorSwap(Type& a, Type& b)
{
	if (&a != &b)
	{
		a ^= b;
		b ^= a;
		a ^= b;
	}
}

/**
* @brief Swaps two items of generic type by creating a temporary variable of given type.
*
* @param a - First item
* @param b - Second item
*/
template<typename Type>
inline void Swap(Type& a, Type& b)
{
	Type tempType = a;
	a = b;
	b = tempType;
}
/*
* @brief Gets the largest value from the container.
*
* @param container - Reference to the continer to find the largest value.
* @parama containerSize - Size of the container.
*/
template<typename Type, typename Container>
inline Type getMax(Container& container, const unsigned int containerSize)
{
	Type max = container[0];
	for (int i = 1; i < containerSize; i++)
	{
		if (container[i] > max)
		{
			max = container[i];
		}
	}
	return max;
}
/**
* @brief Bubble Sort iterates over a container swapping two items as it iterates left to right. Iteration repeats
*        until a pass is made without needing to swap anything. Best case performace is O(n), worst case O(n^2).
*
* @param container - Reference to the container to sort.
* @param containerSize	- Size of the container.
* @param predicate - Predicate to sort with.
*/
template<typename Container, typename Predicate>
inline void BubbleSort(Container& container, const unsigned int containerSize, const Predicate& predicate)
{
	unsigned int searchableLength = containerSize - 1;
	unsigned int known = 0;
	do
	{
		known = 0;
		for (unsigned int i = 0; i < searchableLength; ++i)
		{
			if (predicate(container[i + 1], container[i]))
			{
				Swap(container[i], container[i + 1]);
				known = i;
			}
		}

		searchableLength = known;
	} while (searchableLength != 0);
}

/**
* @brief Insertion Sort iterates over a container left to right, grabbing the next element and inserting it into the
*        correctly sorted position of everything to the left of it. Best case performance is O(n), worst case O(n^2).
*
* @param container - Reference to the container to sort.
* @param containerSize	- Size of the container.
* @param predicate - Predicate to sort with.
*/
template<typename Container, typename Predicate>
inline void InsertionSort(Container& container, const unsigned int containerSize, const Predicate& predicate)
{
	for (unsigned int i = 1; i < containerSize; ++i)
	{
		for (unsigned int j = i; (j > 0) && predicate(container[j], container[j - 1]); --j)
		{
			Swap(container[j], container[j - 1]);
		}
	}
}

/**
* @brief Selection Sort iterates over the container from left to right subdividing into the left sorted list and right
*        unsorted list. During traversal, the correct index (min or max) is found and swapped for the correct position
*        in the sorted division. Best case performance is O(n^2), worst cast O(n^2).
*
* @param container - Reference to the container to sort.
* @param containerSize	- Size of the container.
* @param predicate - Predicate to sort with.
*/
template<typename Container, typename Predicate>
inline void SelectionSort(Container& container, const unsigned int containerSize, const Predicate& predicate)
{
	unsigned int minimumPosition = 0;
	for (unsigned int i = 0; i < containerSize - 1; ++i)
	{
		minimumPosition = i;

		for (unsigned int j = i + 1; j < containerSize; ++j)
		{
			if (predicate(container[j], container[minimumPosition]))
			{
				minimumPosition = j;
			}
		}

		if (minimumPosition != i)
		{
			Swap(container[i], container[minimumPosition]);
		}
	}
}
/**
* @brief partition rearranges the entries in the array from start to end so all the values are in the correct position
* either to the left or right of the pivot position based on the predicate that is passed in.
* 
* @param container - Refernce to the container to sort.
* @param Predicate - Predicate to sort with.
* @param Start - the position in the container to start at.
* @param End - The position in the container to end at.
*/
template<typname Container, typename Predicate, typename Type>
inline Type partition(Container& container, const Predicate& predicate, const unsigned int start, const unsigned int end)
{
	Type pivotValue = container[start];
	Type pivotPosition = start;
	for (int pos = start + 1; pos <= end; pos++)
	{
		if (predicate(container[pos], pivotValue))
		{
			Swap(container[pivotPosition + 1], container[pos]);
			Swap(container[pivotPosition], container[pivotPosition + 1]);
			pivotPosition++;
		}
	}
	return pivotPosition;
}
/**
* @brief Uses the Quicksort Algorith to sort the container from start to end based on the provided predicate.
* Best case performance is O(n log n), worst case O(n^2).
* 
* @param container - Refernce to the container to sort.
* @param Predicate - Predicate to sort with.
* @param Start - the position in the container to start at.
* @param End - The position in the container to end at.
*/
template<typename Container, typename Predicate, typename Type>
inline void QuickSort(Container& container, const Predicate& predicate, const unsigned int start, const unsigned int end)
{
	if (predicate(start, end))
	{
		Type p = partition(container, start, end);


		quickSort(container, start, p - 1);

		quickSort(container, p + 1, end);
	}

}
/**
* @brief Counting sort operates by counting the number of objects that have each distinct key value,
* and using arithmetic on those counts to determine  the positions of each key value in the outut sequence.
* Best case is O(n+k), worst case is O(n+k).
* 
* @param container - Reference to the container to sort.
* @param containerSize - the size of the container
* @param exp - The current digit number to check against.
*/
template<typename Container, typename Type>
inline void CountSort(Container& container, const unsigned int containerSize, const unsigned int exp)
{
	Type output[containerSize];
	Type i, count[10] = { 0 };
	for (i = 0; i < containerSize; i++)
	{
		count[(container[i] / exp) % 10]++;
	}
	for (i = 1; i < 10; i++)
	{
		count[i] += count[i - 1];
	}
	for (i = n - 1; i >= 0; i--)
	{
		output[count[(container[i] / exp) % 10] - 1] = container[i];
		count[(container[i] / exp) % 10]--;
	}
	for (i = 0; i < containerSize; i++)
	{
		container[i] = output[i];
	}
}

/*
* @brief Sorts data with integer keys by grouping the idiviudal digits which share the same significant position and value.
* Best case is O(nk), worst case O(nk).
* 
* @param container - Reference to the container to sort.
* @param containerSize - Size of the container to sort.
*/
template<typename Container, typename Predicate, typename Type>
inline void RadixSort(Container& container, const unsigned int containerSize)
{
	Type m = getMax(container, containerSize);

	for (int exp = 1; m / exp>0; exp *= 10)
	{
		countSort(container, containerSize, exp);
	}
}

} // namespace Sort
} // namespace DA
