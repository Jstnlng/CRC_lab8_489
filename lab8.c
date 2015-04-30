#include<stdio.h>
#include<string.h>
#include "header.h"
#define N strlen(g)

char t[28],cs[28],g[]="10001000000100001";
int a,e,c;
long M = 2147483647;

int main()
{
	printf("\nEnter data : ");
	scanf("%s", t);

	printf("\n----------------------------------------");
	printf("\nGeneratng polynomial : %s", g);

	a = strlen(t);
	for(e = a; e < a+N-1; e++) 
		t[e] = '0';
	printf("\n----------------------------------------");
	printf("\nModified data is : %s", t);
	printf("\n----------------------------------------");
	crc();

	printf("\nChecksum is : %s", cs);

	for(e = a; e < a+N-1; e++) t[e] = cs[e-a];
	printf("\n----------------------------------------");
	printf("\nFinal codeword is : %s", t);
	printf("\n----------------------------------------");
	printf("\nTest error detection 0(yes) 1(no)? : ");
	scanf("%d", &e);
	
	if(e == 0)
	{
		do
		{
			printf("\nEnter the position where error is to be inserted : ");
			scanf("%d", &e);
		}while(e == 0 || e > a+N-1);

		t[e-1] = (t[e-1] == '0') ? '1' : '0';
		printf("\n----------------------------------------");
		printf("\nErroneous data : %s\n", t);
	}
	crc();
	for(e = 0; (e < N-1) && (cs[e] != '1'); e++);
	{
		if(e < N-1) 
			printf("\nError detected\n\n");
		else
		{
			printf("\nNo error detected\n\n");
			printf("\n----------------------------------------\n");
		}
		return 0;
	}
}

void xor()
{
	for(c = 1; c < N; c++)
		cs[c] = (( cs[c] == g[c])?'0':'1');
}

void crc()
{
	for(e = 0; e < N; e++) cs[e] = t[e];
	do
	{
		if(cs[0] == '1') 
			xor();
		for(c = 0; c < N-1; c++) 
			cs[c] = cs[c+1];
		cs[c] = t[e++];
	}while(e <= a+N-1);
}

/*****************************************************************************/
/*                                                                           */
/* This routine is called with a pointer to a null terminted string of       */
/* characters, data, and a probability of bit error, p, and introduces       */
/* errors in the bits of the string according to this probability.           */
/* The routine does not return anything.                                     */
/*                                                                           */
/*****************************************************************************/

void IntroduceError(char *data, double p)
{
	char c, *pointer = data;
	int i;
	while (*pointer != '\0') 
	{
		c = 0x01;
		for ( i = 0; i < 8; i++) 
		{
			if ((double)random()/M <= p)
				*pointer ^= c;
			c <<= 1;
		}
		pointer++;
	}
}