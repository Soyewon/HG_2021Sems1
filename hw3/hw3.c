#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS

void opt(int xlen, int ylen);
int min(int a, int b, int c);
int returnp(int a, int b, int c);
void align(int, int);
char x[100] = { 0, };
char y[100] = { 0, };
int p[100][100] = { 0,0 };
int M[100][100] = { 0, };

int min(int a, int b, int c) {
	if (a >= b) {
		if (b >= c)
			return c;
		else
			return b;
	}
	else {
		if (a >= c)
			return c;
		else
			return a;
	}
}

int returnp(int a, int b, int c) {

	if (a >= b) {
		if (b >= c) { //a>=b>=c
			if (a == c)
				return 1;
			else if (a == b)
				return 1;
			else  //(b==c)
				return 3;
		}
		else {// a>=b이고 b<c
			if (a == b)
				return 1;
			else // a>b, b<c
				return 2;
		}
	}
	else { //(a < b)
		if (a >= c) {
			if (a == c)
				return 1;
			else // (a>c)
				return 3;
		}
		else
			return 1;
	}
}

void opt(int m, int n) {

	int i, j;
	int penalty;

	for (i = 0; i <= m; i++) {
		M[i][0] = 3 *i;
	}

	for (j = 0; j <= n; j++) {
		M[0][j] = 3 * j;
	}

	for (j = 0; j <= n - 1; j++) {
		for (i = 0; i <= m - 1; i++) {
			if (x[i] == y[j]) penalty = 0; else penalty = 2;
			M[i+1][j+1] = min(M[i][j] + penalty, M[i + 1][j] + 3, M[i][j + 1] + 3);
			p[i+1][j+1] = returnp(M[i][j] + penalty, M[i + 1][j] + 3, M[i][j + 1] + 3);

		}
	}
}

void align(int m, int n) {
	int max_l, k, l;
	int printx[100] = { 0, };
	int printy[100] = { 0, };
	int xdex = 0;
	int ydex = 0;

	if (m > n)
		max_l = m;
	else 
		max_l = n;

	int i = m-1;
	int j = n-1;

	for(k=0; k<max_l; k++){
		switch (p[i+1][j+1]) {
			case 1:
				printx[xdex] = x[i];
				xdex++;
				i--;
				j--;
				break;
			case 2:
				printx[xdex] = '-';
				xdex++;
				j--;
				break;
			case 3:
				printx[xdex] = x[i];
				xdex++;
				i--;
				break;
			}
	}
	

	i = m - 1;
	j = n - 1;

	for (k = 0; k < max_l; k++) {
		switch (p[i+1][j+1]) {
		case 1:
			printy[ydex] = y[j];
			ydex++;
			i--;
			j--;
			break;
		case 2:
			printy[ydex] = y[j];
			ydex++;
			j--;
			break;
		case 3:
			printy[ydex] = '-';
			ydex++;
			i--;
			break;
		}
	}

	for (i = max_l; i >= 0; i--) {
		printf("%c ", printx[i]);
	}
	printf("\n");
	for (i = max_l; i >= 0; i--) {
		printf("%c ", printy[i]);
	}

	printf("\n");

}

int main() {

	FILE* fp;
	fp = fopen("input.txt", "r");
	int n;
	int xlen, ylen;
	int i, j, k, l;

	if (fp == NULL)
		return 0;

	fscanf(fp, "%d\n", &n);


	for (i = 0; i < n; i++) {//데이터 개수만큼 반복
			fscanf(fp, "%d\n", &xlen);
			fgets(x, xlen+1, fp);

			fscanf(fp, "%d\n", &ylen);
			fgets(y, ylen + 1, fp);

			
			opt(xlen, ylen);
			align(xlen, ylen);

			printf("\n");
			for (j = 0; j < xlen+1; j++) {
				for (k = 0; k < ylen+1; k++) {
					printf("%d ", M[j][k]);
				}
				printf("\n");
			}
			printf("\n");
	}

	int p[100][100] = { 0, };
	int M[100][100] = { 0, };
}
