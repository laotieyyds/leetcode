#pragma once
#include<iostream>

using namespace std;

class Sort
{
public:
	void BubbleSort(vector<int>& nums) {
		for (int i = 0; i < nums.size(); i++) {
			for (int j = i; j < nums.size(); j++) {
				if (nums[j] < nums[i]) swap(nums[i], nums[j]);
			}
		}
		return;
	}

	//quick sort
	void quicksort(vector<int>& nums, int left, int right) {
		if (left >= right) return;
		int lo = left, hi = right;
		int pivot = nums[left];
		while (left < right)
		{
			while (left < right && nums[right] >= pivot)
			{
				right--;
			}
			nums[left] = nums[right];
			while (left < right && nums[left] <= pivot)
			{
				left++;
			}
			nums[right] = nums[left];
		}
		nums[left] = pivot;
		int index = left;
		quicksort(nums, lo, index - 1);
		quicksort(nums, index + 1, hi);
	}
	void QuickSort(vector<int>& nums) {
		quicksort(nums, 0, nums.size() - 1);
	}

	//heap sort
	void MaxHeapify(vector<int>& nums,int heap_size, int i) {
		int left = 2 * i;
		int right = 2 * i + 1;
		int largest = i;
		if (left < heap_size-1 && nums[left] > nums[largest]) {
			largest = left;
		}
		if (right < heap_size-1 && nums[right] > nums[largest]) {
			largest = right;
		}
		if (largest != i) {
			swap(nums[largest], nums[i]);
			MaxHeapify(nums, heap_size - 1, largest);
		}
		return;
	}
	void BuildMaxHeap(vector<int>& nums) {
		for (int i = nums.size() / 2; i >= 0; i--) {
			MaxHeapify(nums, nums.size(), i);
		}
		return;
	}
	void HeapSort(vector<int>& nums) {
		BuildMaxHeap(nums);
		for (int i = nums.size() - 1; i > 0; i--) {
			swap(nums[0], nums[i]);
			MaxHeapify(nums, i, 0);
		}
		return;
	}

private:

};