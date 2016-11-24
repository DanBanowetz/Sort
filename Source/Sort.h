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

} // namespace Sort
} // namespace DA
