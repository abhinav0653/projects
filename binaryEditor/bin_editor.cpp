#include "pch.h"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

#define MAX_ROWS 1000
#define MAX_COLS 8
#define DISP_LEN 28
#define BLANK '*' 
char arr[MAX_ROWS][MAX_COLS];

int power(int a, int b)
{
	int ret = 1;
	int i;
	for (i = 0; i < b; i++)
		ret = ret * a;
	return ret;
}
void int2bin(int c, string &s)
{
	int i;
	for (i = 0; i <= 7; i++)
	{
		s[7 - i] = (c & 1) ? '1' : '0';
		c = c >> 1;
	}
}


int str2int(string str)
{
	int ret = 0;
	int i;
	for (i = 0; i < 8; i++)
	{
		if (str[i] == '1')
			ret += power(2, i);
	}
	return ret;
}

void print(int row)
{
	int i;
	string s;
	s.resize(8);
	for (i = 0; i < 8; i++)
	{
		if (arr[row][i] == BLANK)
		{
			printf("-------- ");
			continue;
		}
		int2bin(arr[row][i], s);
		cout<<s<<" ";
	}
	cout<<endl;
}

void fill(int idx, string line)
{
	stringstream ss(line);
	string word;
	int j = 0;
	while (ss >> word) {
		arr[idx][j] = str2int(word);
		j++;
	}
}

int nextidx[MAX_ROWS];
int previdx[MAX_ROWS];
int index[MAX_ROWS];
int freelist[MAX_ROWS];
int freelistptr = -1;


void addint(int row, int col)
{
	string s;
	cin >> s;
	s.resize(8);
	int val = str2int(s);
	arr[row][col] = val;
	return;
}
void addtofreelist(int row)
{
	freelistptr++;
	freelist[freelistptr] = row;
}

int getfreeblock()
{
	if (freelistptr == -1)
		return -1;
	else
		return freelist[freelistptr--];
}
void init()
{
	int i, j;
	for (i = 0; i < MAX_ROWS; i++)
		for (j = 0; j < 8; j++)
			arr[i][j] = BLANK;

}

void save(int rows_in_doc) {
	try {
		ofstream fs("Myfile1.txt");
	
		string str;
		str.resize(8);
		for (int i = 0; i < rows_in_doc; i++) {
			for (int j = 0; j < 8; j++) {
				str[j] = arr[index[i]][j];
			}
			fs << str;
		}
		fs.close();
	}catch (exception e) {
		cout << "file cannot be opened" << endl;
	}

}
int main(int argc, char** argv)
{

	if (argc != 1)
	{
		printf("insufficient arguments\n");
		exit(0);
	}

	FILE* fp;
	fopen_s(&fp,"Myfile.txt", "r+");
	if (fp == NULL)
	{
		perror("fopen");
		printf("Unable to open file\n");
		exit(0);
	}
	int c;
	int cnt = 0;
	int currentbyte = 0;
	int currentlineindex = 0;
	int currentlinenumber = 0;
	int displine = 0;
	int rows_in_doc = 0;

	//init begin
	init();
	int row_idx, col_idx;
	row_idx = col_idx = 0;
	while ((c = fgetc(fp)) != EOF)
	{
		if (col_idx == 8) {

			nextidx[row_idx] = rows_in_doc + 1;
			previdx[row_idx] = rows_in_doc - 1;
			index[row_idx] = rows_in_doc;

			row_idx++;
			col_idx = 0;
			rows_in_doc++;
		}
		arr[row_idx][col_idx] = c;
		col_idx++;
	}
	//init end
	
	currentlinenumber = rows_in_doc - 1;// current line is the index of the last line in the file which visible on the display
	
	currentbyte = 7;
	while (1)
	{

		int currentlineindex = index[currentlinenumber];

		int start = ((currentlinenumber - DISP_LEN) > 0) ? currentlinenumber - DISP_LEN : 0;
		for (int i = start; i <= DISP_LEN; i++) {
			printf("%03d:0x%010x:", i, i * 8);
			if (i>rows_in_doc) {
				for (int j = 0; j < 8; j++) {
					printf("--------");
					printf(" ");
				}
				printf("\n");
			}
			else {
				print(index[i]);
			}
		}

		fflush(stdin);
		fflush(stdout);
		
		printf("currentline:%d  currentbyte:%d \n", currentlinenumber, currentbyte);
		printf(":");
		
		char choice;
		cin >> choice;

		
		switch (choice) {
		case 'n':
			if (currentlinenumber < rows_in_doc) {
				currentlinenumber++;
			}
			else
			{
				printf("already at the end of file\n");
			}
			break;
		case 'p':
			if (currentlinenumber > 0)
			{
				currentlinenumber--;
			}
			else {
				printf("already at the top\n");
			}
			break;
		case 'j':
			if (currentbyte > 0) {
				currentbyte--;
			}
			else
				printf("already at the leftmost byte\n");
			break;
		case 'k':
			if (currentbyte < 7) {
				currentbyte++;
			}
			else
				printf("already at the rightmost byte\n");
			break;
		case 'i':
			cout<< "Do you wish to enter a line(y/n):";
			char input;
			cin >> input;
			if (input == 'n')
				break;
			else if (input == 'y')
			{
				printf("Enter new line:\n");
				string line;
				getline(cin, line);

				int idx = getfreeblock();
				if (idx == -1) {
					printf("Error:No free block available\n");
					break;
				}

				fill(idx, line);

				nextidx[idx] = nextidx[currentlineindex];
				previdx[idx] = currentlineindex;
				nextidx[currentlineindex] = idx;
				previdx[nextidx[idx]] = idx;

				currentlineindex = idx;
				index[currentlinenumber]=idx;
				rows_in_doc++;
				break;
			}
			else
				break;
		case 'd':
			nextidx[previdx[currentlineindex]] = nextidx[currentlineindex];
			previdx[nextidx[currentlineindex]] = previdx[currentlineindex];
			index[currentlinenumber] = previdx[currentlineindex];
			rows_in_doc--;
			addtofreelist(currentlineindex);
			break;
		case 'x':
			arr[currentlineindex][currentbyte] = BLANK;
			break;
		case 'r':
			printf("Enter new byte value for replacement:\n");
			addint(currentlineindex, currentbyte);
			break;
		case 'w':
			save(rows_in_doc);
			cout << "file saved" << endl;
			break;
		case 'e':
			printf("bye\n");
			exit(0);
			break;
		default:
			printf("invalid input\n");
			fflush(stdin);
			break;
		}

	}

}