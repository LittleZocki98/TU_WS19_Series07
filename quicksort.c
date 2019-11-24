#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// quicksort algorithm
void quickSort(double*, int);

// method to print array to console
void printArr(double*);

int main(int argc, char* argv[]) {
  // initialize rng
	srand((int)(time(NULL)));

	double time;
	clock_t t1, t2;
  
  // test-array
	double* arr = (double*)calloc(1, sizeof(double));
  
	for (int i = 1; i <= 10; i++) {
		time = 0;
    
    // try 50x for better average in time usage
		for (int j = 0; j < 50; j++) {
			arr = realloc(arr, (i + 1) * sizeof(double));
      
      // using first element of array to tell, how many elements are following...
			arr[0] = i;

      // fill array with random numbers
			for (int k = 0; k < i; k++) {
				arr[k + 1] = rand() % 100;
			}

			t1 = clock();
			quickSort(arr, 1);
			t2 = clock();

			time += (double)(t2 - t1) / CLOCKS_PER_SEC;
			
		}
    // print to console, how long it took on average to sort one array of length i
		printf("i = %d => t = %g\n", i, time / 50.0);
	}
  
  // free memory
	free(arr);

	return 0;
}

void quickSort(double* arr, int ascending) {
  // check, if array size > 1
  // if size <= 1 the array is already "sortet"
	if (((int)*arr) > 1) {
  
		int size1 = 0, size2 = 0;
    
    // pick random pivot
		int pivInd = rand() % (int)(*arr);
		double pivVal = arr[pivInd + 1];

		// count elements bigget/smaller than pivot
		for (int i = 1; i <= (int)*arr; i++) {
			if (((arr[i] < pivVal) && ascending) || ((arr[i] > pivVal) && !ascending)) {
				size1++;
			}
		}
		size2 = ((int)(*arr) - size1);

		// allocate memory for tmp arrays
		double* tmp1 = (double*)calloc(size1 + 1, sizeof(double));
		double* tmp2 = (double*)calloc(size2 + 1, sizeof(double));

		tmp1[0] = size1;
		tmp2[0] = size2;

		// fill tmp arrays
		int j = 1, k = 1;
		for (int i = 1; i <= (int)*arr; i++) {
			if (((arr[i] < pivVal) && ascending) || ((arr[i] > pivVal) && !ascending)) {
				tmp1[j] = arr[i];
				j++;
			}
			else {
				tmp2[k] = arr[i];
				k++;
			}
		}

		// sort tmp arrays
		quickSort(tmp1, ascending);
		quickSort(tmp2, ascending);

		// combine arrays
		int i = 1;
		for (int j = 1; j <= size1; j++) {
			arr[i] = tmp1[j];
			i++;
		}
		arr[i] = pivVal;
		for (int j = 1; j <= size2; j++) {
			arr[i] = tmp2[j];
			i++;
		}

		// free memory
		free(tmp1);
		free(tmp2);		
	}
}

void printArr(double *arr) {
	printf("\n");
	for (int i = 0; i < *arr; i++) {
		printf("arr[%d] = %+g\n", i, arr[i + 1]);
	}
}
