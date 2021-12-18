#include <stdio.h>
#include<stdlib.h>
#include <time.h>

int arrc[10000000] = { 0, }; // 랜덤배열 카피용
int arr[10000000] = { 0, };// 배열
int b[10000000] = { 0, }; //머지소트 카피용 배열
int t[6]; // input값 받기용 배열
float r1[3][2] = { 0, };
float r2[3][3] = { 0, };
float r3[3][3] = { 0. };
int n;// input값 받기용 임시변수

clock_t start, end, sorting_t = 0;
float mavg[3]; // 랜덤 mergesort평균
float qavg[3]; // 랜덤 quicksort평균

void merge(int arr[], int l, int m, int r) // l<m<r
{
	int i, j, k;

	for (i = l; i <= r; i++)
	{
		b[i] = arr[i];
	}

	i = l; j = m + 1; k = l; 

	while (i <= m && j <= r) {
		if (b[i] <= b[j])
		{
			arr[k++] = b[i++];
		}
		else
		{
			arr[k++] = b[j++];
		}
	}
	if (i > m)
		while (j <= r)
		{
			arr[k++] = b[j++];
		}
	else
		while (i <= m)
		{
			arr[k++] = b[i++];
		}
}

void mergesort(int arr[], int l, int r)
{
	int m;

	if (l < r) {
		m = (l + r) / 2;
		mergesort(arr, l, m);
		mergesort(arr, m + 1, r);
		merge(arr, l, m, r);
	}
}

void quicksort(int arr[], int l, int r) {

	int p;

	if (l < r) {
		p = partition(arr, l, r);
		quicksort(arr, l, p - 1);
		quicksort(arr, p + 1, r);
	}
}

int partition(int arr[], int l, int r) {

	int temp;
	int x = arr[l];
	int i = l + 1;
	int j = r;

	while (1) {
		while (arr[i] <= x && i <= r) { i++; }
		while (arr[j] > x && j >= l) { j--; }

		if (i < j) {
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;

		}
		else break;
	}
	temp = arr[l];
	arr[l] = arr[j];
	arr[j] = temp;
	return j;
}

void make_s(int n) {
	int i;
	for (i = 0; i < n; i++) {
		arr[i] = i;
	}
}

void make_r(int n) {
	srand(time(NULL));
	int i;
	for (i = 0; i < n; i++) {
		arr[i] = rand();
	}
}

void CopyArr(int n)
{
	int i;
	for (i = 0; i < n; i++)
		arrc[i] = arr[i];
}

float sort_time(void)
{
	float res;
	sorting_t = end - start;
	res = ((float)sorting_t / CLOCKS_PER_SEC);
	return res;
}

void cal_avg() {

	int i = 0;
	for (i = 0; i < 3; i++) {
		mavg[i] = (r2[i][0] + r2[i][1] + r2[i][2]) / 3;
		qavg[i] = (r3[i][0] + r3[i][1] + r3[i][2]) / 3;
	}
}

void print_sorted() {

	printf("sorted       N=%d          N=%d        N=%d\n", t[0], t[1], t[2]);
	printf("Mergesort   %f           %f       %f\n", r1[0][0], r1[1][0], r1[2][0]);
	printf("Quicksort   %f          %f       %f\n", r1[0][1], r1[1][1], r1[2][1]);

}

void print_random() {

	printf("random                N=%d      N=%d       N=%d\n", t[3], t[4], t[5]);
	printf("Mergesort   data1     %f       %f       %f\n", r2[0][0], r2[1][0], r2[2][0]);
	printf("            data2     %f       %f       %f\n", r2[0][1], r2[1][1], r2[2][1]);
	printf("            data3     %f       %f       %f\n", r2[0][2], r2[1][2], r2[2][2]);
	printf("            average   %f       %f       %f\n", mavg[0], mavg[1], mavg[2]);
	printf("\n");
	printf("Quicksort   data1     %f       %f       %f\n", r3[0][0], r3[1][0], r3[2][0]);
	printf("            data2     %f       %f       %f\n", r3[0][1], r3[1][1], r3[2][1]);
	printf("            data3     %f       %f       %f\n", r3[0][2], r3[1][2], r3[2][2]);
	printf("            average   %f       %f       %f\n", qavg[0], qavg[1], qavg[2]);

}


int main()
{
	int i, j;

	FILE* fp;
	fp = fopen("input.txt", "r");

	if (fp == NULL)
		return 0;

	for (i = 0; i < 6; i++) {//데이터 개수만큼 반복
		fscanf(fp, "%d\n", &n);
		t[i] = n;
	}

	for (i = 0; i < 3; i++) {
		make_s(t[i]);

		start = clock();
		mergesort(arr, 0, t[i]);
		end = clock();
		r1[i][0] = sort_time();

		make_s(t[i]);

		start = clock();
		quicksort(arr, 0, t[i]);
		end = clock();
		r1[i][1] = sort_time();
	}

	for (j = 0; j < 3; j++) {
		for (i = 3; i < 6; i++) {
			make_r(t[i]);

			CopyArr(t[i]);
			start = clock();
			mergesort(arr, 0, t[i]);
			end = clock();
			r2[i - 3][j] = sort_time();

			start = clock();
			quicksort(arrc, 0, t[i]);
			end = clock();
			r3[i - 3][j] = sort_time();
		}
	}

	cal_avg();
	print_sorted();
	printf("\n\n");
	print_random();

	fclose(fp);
}