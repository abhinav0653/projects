/*
	Abhinav Agrawal
	2016pcp5430@mnit.ac.in
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_ROWS 1000
#define MAX_COLS 8
#define DISP_LEN 25
#define BLANK '*' 
char arr[MAX_ROWS][MAX_COLS];

int power(int a,int b)
{
	int ret=1;
	int i;
	for(i=0;i<b;i++)
		ret = ret*a;
	return ret;
}
void int2bin(int c, char* s)
{
	int i;
	for(i=0;i<=7;i++)
	{
	 s[7-i] = (c & 1)?'1':'0';
	 c = c>>1;
	}
	 s[i]='\0';	
}

void print(int currentline)
{
	int i;
	char s[9];
	for(i=0;i<8;i++)
	{
	    if(arr[currentline][i] == BLANK)
		{
			printf("-------- ");
			continue;
		}
		int2bin(arr[currentline][i],s);
		printf("%s ",s);
	}
	printf("\n");
}

int str2int(char* str)
{
	int ret=0;
	int i;
	for(i=0;i<8;i++)
	{
		if(str[i]=='1')
			ret+=power(2,i);
	}
	return ret;
}
void fill(int idx,char* line)
{
	char* word;
	char* sep = " ";
	char* brkt;
	int j=0;
	for(word = strtok_r(line,sep,&brkt);word;word=strtok_r(NULL,sep,&brkt))
	{
		arr[idx][j]=str2int(word);
		j++;
	}
}

int nextidx[MAX_ROWS];
int previdx[MAX_ROWS];
int freelist[MAX_ROWS];
int freelistptr=-1;

int bin2int(int a)
{
	int ret =0;
	int i=0;
	for(i=0;i<8;i++)
	{
		if( a & 1)
			ret += power(2,i);
		a = a>>1;
	}
	return ret;
}

void addint(char* s,int currentline,int currentbyte)
{
	int val = str2int(s);
	arr[currentline][currentbyte]=val;
	return;
}
void addtofreelist(int currentline)
{	
	freelistptr++;
	freelist[freelistptr]=currentline;
}

int getfreeblock()
{
	if(freelistptr==-1)
		return -1;
	else
		return freelist[freelistptr--];
}
void init()
{
	int i,j;
	for(i=0;i<MAX_ROWS;i++)
		for(j=0;j<8;j++)
			arr[i][j]=BLANK;

}
int main(int argc,char** argv)
{

	if(argc != 2)
	{
		printf("insufficient arguments\n");
		exit(0);
	}

	FILE* fp = fopen(argv[1],"r+");
	if(fp == NULL)
	{
		perror("fopen");		
		printf("Unable to open file\n");
		exit(0);
	}
	int c;
	int cnt=0;
	int currentbyte=0;
	int currentline=0;
	int displine=0;
	int row=0;
	init();
	while((c=fgetc(fp))!=EOF)
	{
		if(cnt == 8){
			nextidx[row]=row+1;
			previdx[row]=row-1;
			row++;
			cnt=0;
		}
		arr[row][cnt]=c;
		cnt++;
	}
	if(cnt!=0){
		nextidx[row]=row+1;
		previdx[row]=row-1;
		row++;
	
	}
	int i;
	//for(i=0;i<row;i++)
	//	printf("previndx for i are %d\n",previdx[i]);
	for(i=row;i<MAX_ROWS;i++){
		freelistptr++;
		freelist[freelistptr]=i;
	}
	while(1)
	{
	  int z,dline,ddline,byteaddress,start;
	  dline=previdx[currentline];
	//  printf("currenline:%d,previdx[currenline]:%d",currentline,previdx[currentline]);
	  ddline=displine-1;
	  byteaddress= displine*8-8;
	  if(dline==-1){
		start=1;
		printf("0-1:0x%010x:",byteaddress);
		int i;
		for(i=0;i<8;i++)
		{
				printf("---------");
		}
		byteaddress+=8;
		printf("\n");
		dline=nextidx[dline];
		ddline++;
	  }
	  for(z=start;z<DISP_LEN;z++){
		//printf("dline:%d,ddline:%d\n",dline,ddline);
		if(ddline>row)
			break;
		printf("%03d:0x%010x:",ddline,byteaddress);
		print(dline);
		dline=nextidx[dline];
		ddline++;
		byteaddress += 8;
	  }

	  fflush(stdin);
	  fflush(stdout);
	  printf("currentline:%d  currentbyte:%d \n",displine,currentbyte);
//	  printf("displine:%d  dispbyte:%d \n",displine,currentbyte);
	  printf(":");
	  c=getchar();
	  getchar();
	  switch(c){
		case 'j':
			if(displine<row-1){
			currentline=nextidx[currentline];
			displine++;
			}
			else
			{
				printf("already at the end of file\n");
			}
			break;
		case 'k':
			if(displine>0)
			{
			 currentline=previdx[currentline];
			 displine--;
			}
			else{
				printf("already at the top\n");
			}
			break;
		case 'h':
			if(currentbyte>0){
				currentbyte--;
			}
			else
				printf("already at the leftmost byte\n");
			break;
		case 'l':
			if(currentbyte<7){
				currentbyte++;
		//		print(currentline);
			}
			else
				printf("already at the rightmost byte\n");
			break;
		case 'o':
			printf("Do you wish to enter a line(y/n):");
			char input;
			input=getchar();
			getchar();
			if(input == 'n')
				break;
			else if(input == 'y')
			{ 
				printf("Enter new line:\n");
				char* line=NULL;
				size_t len;
				getline(&line,&len,stdin);
			//	printf("%s",line);
				int idx = getfreeblock();
				if(idx==-1){
					printf("Error:No free block available\n");
break;
}
			//	printf("idx is:%d",idx);
				fill(idx,line);
				int temp = nextidx[currentline];
				nextidx[currentline] = idx;
				previdx[idx]=currentline;
				nextidx[idx] = temp;
				previdx[temp]=idx;
				currentline=idx;
				displine++;
				row++;
				break;
			}
			else
				break;
		case 'd':
			nextidx[previdx[currentline]]=nextidx[currentline];
			previdx[nextidx[currentline]]=previdx[currentline];
			addtofreelist(currentline);
			currentline = nextidx[currentline];
		//	print(currentline);
			row--;
			break;
		case 'x':
			arr[currentline][currentbyte]=BLANK;
			break;
		case 'r':
			printf("Enter new byte value for replacement:\n");
			char* line = NULL;
			size_t len;
			getline(&line,&len,stdin);
			fflush(stdin);
			addint(line,currentline,currentbyte);
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
