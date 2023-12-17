#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include "SortString.h"


static char filename[] = "C:\\Users\\vkobi\\OneDrive\\Desktop\\28\\dict0.txt";

// ������������ ����� ����� � �������
#define MAX_LEN_WORD 80
// ������������ ���������� ����
#define MAX_WORDS 20000

// �����, ����������� �� ����� 
char words[MAX_WORDS][MAX_LEN_WORD + 1];
// ���������� ���� � �������
int n = 0;

// ������ ��� ���������� 
char a[MAX_WORDS][MAX_LEN_WORD + 1];

int getNextDelim(FILE* fp, char token[]);
int getNextWord(FILE* fp, char token[]);

int LoadWords(char* filename) {
	// ������� ����
	FILE* fin = fopen(filename, "rt");
	if (fin == NULL) {
		// ���� ���� �� ������ ������� - �������� �� ����
		printf("File %s doesn't opened!\n", filename);
		return 0;
	}

	char token[MAX_LEN_WORD + 1];
	// ���� �� ����� �����
	while (!feof(fin)) {
		// ���� ���� ����������� - ����� ���
		while (getNextDelim(fin, token)) {
		}
		// ���� ���� ����� - ����� ���
		if (getNextWord(fin, token)) {
			if (n < MAX_WORDS) {
				strcpy(words[n], token);
				n++;
			}
			else {
				printf("Words are more than elements in array!!\n", filename);
				fclose(fin);
				return 0;
			}
		}
	}
	// ��������� ���� � �������
	fclose(fin);
	return 1;
}

// ���������� 0 - ���� ch - �� �����.
// ���������� 1 - ���� ch - �����.
// ��������� �������� ��� ��������� ���� (� ������ < 128)
// � ��� ������� ���� �� ��������� ANSI
int isalpha_my(unsigned char ch) {

	if (isalpha(ch))
		return 1;

	// ANSI ���������!!!
	if (ch >= 192 && ch <= 223)
		return 1;
	if (ch >= 224 && ch <= 255)
		return 1;

	return 0;
}

// ���������� 1 - ����  �� ����� �������� �����������.
// � ���� ������ � token ������������ ������, ���������� 
// ���� �����������.
// ���� � ����� ��� �� ����������� - ���������� 0.
// � ���� ������ ��������� token ������������.
int getNextDelim(FILE* fp, char token[])
{
	int ch = getc(fp);
	if (ch == EOF) {
		return 0;
	}
	if (isalpha_my((unsigned char)ch)) {
		ungetc(ch, fp);
		return 0;
	}
	token[0] = (unsigned char)ch;
	token[1] = '\0';
		return 1;
}

// ���������� 1 - ����  �� ����� ��������� �����.
// � ���� ������ � token ������������ ������, ���������� 
// ��� �����. ������������� ��� ����� �� ����� MAX_LEN_WORD ��������.
// ���� � ����� �� ���� ����� - ���������� 0.
// � ���� ������ token �������� ������ ������.
int getNextWord(FILE* fp, char token[])
{
	int i = 0;
	int ch;
	while (((ch = getc(fp)) != EOF) && (i < MAX_LEN_WORD)) {
		if (!isalpha_my((unsigned char)(ch))) {
			break;
		}
		token[i++] = ch;
	}
	ungetc(ch, fp);
	token[i] = '\0';
		if (i == 0)
			return 0;
	return 1;
}


void fillArrayStrings() {

	for (int i = 0; i < n; i++) {
		strcpy(a[i], words[i]);
	}

}

int isSortedStrings() {
	for (int i = 0; i < n - 1; i++) {
		if (strcmp(a[i], a[i + 1]) > 0) {
			return 0;
		}
	}
	return 1;
}

void SelectionSortStrings() {
	for (int i = 0; i < n - 1; i++) {

		int iMin = i;
		for (int j = i + 1; j < n; j++) {
			if (strcmp(a[j], a[iMin]) < 0) {
				iMin = j;
			}
		}

		if (i != iMin) {
			char tmp[MAX_LEN_WORD + 1];
			strcpy(tmp, a[i]);
			strcpy(a[i], a[iMin]);
			strcpy(a[iMin], tmp);
		}
	}
}

void QuickSortStrings() {
	qsort(a, n, sizeof(a[0]), strcmp);
}

void  BubbleSortStrings() {
	for (int i = 0; i < n - 1; i++) {
		for (int j = (n - 1); j > i; j--) {
			// ���� ������� ������� ������ �����������
			if (strcmp(a[j - 1], a[j]) > 0 ){
				// ������ �� �������
				char* temp = a[j - 1];
				strcpy(a[j - 1], a[j]);
				strcpy(a[j], temp);
			}
		}
	}
}

void InserSortStrings() {
	for (int pos = 1; pos < n; pos++) {
		char value[MAX_LEN_WORD + 1];
		strcpy(value, a[pos]);
		int i = pos;
		while ((i > 0) && (strcmp(value, a[i - 1]) < 0)) {
			strcpy(a[i], a[i - 1]);
			i--;
		}
		strcpy(a[i], value);
	}
}


void Merge(char* a[], int low, int mid, int high) //Merging the Array Function
{
	int nL = mid - low + 1;
	int nR = high - mid;

	char** L = malloc(sizeof(char*) * nL);
	char** R = malloc(sizeof(char*) * nR);
	int i;
	for (i = 0; i < nL; i++)
	{
		L[i] = malloc(sizeof(a[low + i]));
		strcpy(L[i], a[low + i]);
	}
	for (i = 0; i < nR; i++)
	{
		R[i] = malloc(sizeof(a[mid + i + 1]));
		strcpy(R[i], a[mid + i + 1]);
	}
	int j = 0, k;
	i = 0;
	k = low;
	while (i < nL && j < nR)
	{
		if (strcmp(L[i], R[j]) < 0)strcpy(a[k++], L[i++]);
		else strcpy(a[k++], R[j++]);
	}
	while (i < nL)strcpy(a[k++], L[i++]);
	while (j < nR)strcpy(a[k++], R[j++]);

}


void MergeSortStrings(int low, int high) //Main MergeSort function
{
	int low = 0;
	int high = n - 1;
	if (low < high)
	{
		int mid = (low + high) / 2;
		MergeSortStrings(a, low, mid);
		MergeSortStrings(a, mid + 1, high);
		Merge(a, low, mid, high);
	}
}


void hairbrush() 
{
	if (a && n)
	{
		size_t jump = n, i;
		int swapped = 1;
		while (jump > 1 || swapped)
		{
			if (jump > 1)
				jump /= 1.24733;
			swapped = 0;
			for (i = 0; i + jump < n; ++i)
				if (strcmp(a[i + jump], a[i])>0)
				{
					char* tmp = a[i];
					strcpy(a[i], a[i + jump]);
					strcpy(a[i + jump], tmp);
					swapped = 1;
				}
		}
	}
}


