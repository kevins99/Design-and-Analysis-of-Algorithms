#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int *arr, count;
int place(int k, int pos) {
	for(int i=1; i<k; i++) {
		if(arr[i] == pos)
			return 0;
		if(abs(k-i) == abs(pos - arr[i]))
			return 0;
	}
	return 1;
}

void nqa(int k, int n) {
	for(int i = 1; i<=n; i++) {
		if (place(k, i)){
			arr[k] = i;
			if (k == n) {
				for(int i=1; i<=n; i++)
					printf("%d\t", arr[i]);
				printf("\n");
			}
			else nqa(k+1, n);
		}
	}
}

int main(void) {
	int n;
	printf("Enter the number of rows\n");
	scanf("%d", &n);
	arr = (int*)malloc(n * sizeof(int));
	nqa(0,n);
}
