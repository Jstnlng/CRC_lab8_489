#include<stdio.h>
#include<string.h>
#include "header.h"


#define N strlen(gen_poly)

char data[1024], checksum[28], gen_poly[]="10001000000100001";
int a,e,c;
long M = 2147483647;

int main()
{
	printf("\nEnter data : ");
	scanf("%s", data);

	printf("\n----------------------------------------");
	printf("\nGeneratng polynomial : %s", gen_poly);

	a = strlen(data);
	for(e = a; e < a+N-1; e++) 
		data[e] = '0';

	printf("\n----------------------------------------");
	printf("\nModified data is : %s", data);
	printf("\n----------------------------------------");

	crc();

	printf("\nChecksum is : %s", checksum);

	for(e = a; e < a+N-1; e++) data[e] = checksum[e-a];
	printf("\n----------------------------------------");
	printf("\nFinal codeword is : %s", data);
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

		data[e-1] = (data[e-1] == '0') ? '1' : '0';
		printf("\n----------------------------------------");
		printf("\nErroneous data : %s\n", data);
	}

	crc();

	for(e = 0; (e < N-1) && (checksum[e] != '1'); e++);
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
		checksum[c] = (( checksum[c] == gen_poly[c])?'0':'1');
}

void crc()
{
	for(e = 0; e < N; e++) checksum[e] = data[e];
	do
	{
		if(checksum[0] == '1') 
			xor();
		for(c = 0; c < N-1; c++) 
			checksum[c] = checksum[c+1];
		checksum[c] = data[e++];
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