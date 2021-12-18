#include <stdio.h>

int sudo[9][9] = { 0, };

void print_sudo();
int backt(int x, int y, int z);
int do_sudo();
int finish;

int main(void) {

	FILE*fp = fopen("input.txt", "r");
	int n;
	int i, j, k;
	int num;

	if (fp == NULL)
		return 0;

	fscanf(fp, "%d\n", &n);

	for (i = 0; i < n; i++) {
		for (j = 0; j < 9; j++) {
			for (k = 0; k < 9; k++) {
				fscanf(fp, "%d", &num);
				sudo[j][k] = num;
			}
		}
		printf("sudoku %d\n", i + 1);
		do_sudo();
		print_sudo();
		finish = 0;
	}

	fclose(fp);
	return 0;
}

void print_sudo() {
	int i, j;
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			printf("%d ", sudo[i][j]);
		}
		printf("\n");
	}
}

int do_sudo() {
	int i, j, k;

	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			if (sudo[i][j] == 0) {
				for (k = 1; k < 10; k++) {
					if (backt(i, j, k) == 1) {
						sudo[i][j] = k;
						do_sudo();
						if (finish == 1) return 0;
						sudo[i][j] = 0;
					}
				}
				return 0;
			}
		}
	}
	finish = 1;
	return 0;
}

int backt( int x, int y, int z) {
	int i, j;
	int result;
	for (i = 0; i < 9; i++) {
		if (sudo[x][i] == z)
			return 0;
	}

	for (j = 0; j < 9; j++) {
		if (sudo[j][y] == z)
			return 0;
	}

	int k = (x / 3) * 3;
	int w = (y / 3) * 3;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			if (sudo[k + i][w + j] == z)
				return 0;
		}
	}
	return 1;

	
}
