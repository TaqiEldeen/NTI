#include <stdio.h>

int binary_search(unsigned char* ptr, int size, int num);

int main(void){
	unsigned char arr[] = {1, 2, 5, 6, 7, 9};
	
	printf("index: %d\n", binary_search(arr, sizeof(arr)/sizeof(arr[0]), 8));
	
	return 0;
}

int binary_search(unsigned char* ptr, int size, int num) {
	int first = 0;
	int last  =  size - 1;
	int result = -1;

	while(first <= last) {
		int mid = (first + last) / 2;

		if(ptr[mid] == num) {
			result = mid;
			break;
		} else if(ptr[mid] > mid) {
			first = mid + 1;
		} else {
			last = mid - 1;
		}

	}

	return result;
}


