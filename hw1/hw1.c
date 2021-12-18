#include <stdio.h>

#define N 1000
int data_n;

typedef struct tree {
	int left;
	int right;
	int parent;
	int data;
}Tree;

Tree t[N];

int main()
{
	FILE* fp;
	fp = fopen("input.txt", "r");
	int i;
	int j;
	int k;
	int node_n;
	int parent_n, right_n, left_n;

	for (i = 0; i < N; i++) {
		t[i].right = -1;
		t[i].left = -1;
		t[i].parent = -1;
		t[i].data = -1;
	}

	if (fp == NULL)
		return 0;

	fscanf(fp, "%d\n", &data_n);

	for (i = 0; i < data_n; i++) { //데이터 개수만큼 반복
		int result = 0;
		fscanf(fp, "%d\n", &node_n); //노드개수 받기
		for (j = 0; j < node_n; j++) { //트리 만들기
			fscanf(fp, "%d %d %d\n", &parent_n, &left_n, &right_n);
			t[parent_n].left = left_n;
			t[parent_n].right = right_n;
			t[left_n].parent = parent_n;
			t[right_n].parent = parent_n;
			t[parent_n].data = parent_n; //자기자신 값
		}

		/*for (int i = 1; i <= node_n; i++) {
			printf("%d %d %d %d\n", t[i].parent,t[i].data, t[i].left, t[i].right);
		}*/

		for (k = 0; k < node_n; k++) { //1부터 노드개수만큼 좌.우 서브트리개수 비교
			if (t[k].left != -1 && t[k].right != -1) {
				int cl = count_n(t[k].left);
				int cr = count_n(t[k].right);
				if (cl < cr)
					result++;

			}
			else if (t[k].left == -1 && t[k].right != -1)
				result++;
		}
		printf("%d\n", result);
	}

	fclose(fp);

}


int count_n(int root) { //subtree개수 구하기
	int cnt = 0;
	if (t[root].data == -1) return 0;
	else
	{
		cnt = 1 + count_n(t[root].left) + count_n(t[root].right);
	}
	return cnt;

}
