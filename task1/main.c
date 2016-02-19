#include "stdio.h"
//#include "stdlib.h"
void free_mem(int **arr, int size) {
	for (int i = 0; i < size; ++i) {
		free(arr[i]);
	}
	free(arr);
}

int main(int argc, char *argv) {
	int n;
	scanf("%d", &n);
	int **arr = malloc(sizeof(int) * (n + 1));
	for (int i = 0; i <= n; ++i) {
		arr[i] = malloc(sizeof(int)* (n + 1));
	}
	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= n; ++j) {
			arr[i][j] = i * j;
		}
	}
	int x1, x2, y1, y2;
	while (scanf("%d", &x1)) {
		if (x1 == 0) {
			free_mem(arr, n + 1);
			return 0;
		}

		scanf("%d%d%d", &y1, &x2, &y2);
		for (int i = y1; i <= y2; ++i) {
			for (int j = x1; j <= x2; ++j) {
				printf("%d ", arr[i][j]);
			}
			printf("\n");
		}
	}

}
