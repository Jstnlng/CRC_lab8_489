#include "header.h"

#define N strlen(gen_poly)
// #define BIT_ERROR_RATE 0.00001

char data[1024], codeword[1041], crc[17], gen_poly[]="10001000000100001";
int data_size, i, crc_index;
double bre;
long M = 2147483647;

int main(int argc, char ** argv)
{
	if(argc != 2)
	{
		printf("\nUsage:\n\t ./lab8 <BIT_ERROR_RATE>\n\n");
		exit(1);
	}
	bre = atof(argv[1]);
	//prompt the user for data input
	printf("\nEnter data : ");
	scanf("%s", data);
	printf("\nPolynomial :  %s", gen_poly);

	//copy input into a seperate larger array 
	//where the codeword will be stored
	strcpy(codeword, data);

	data_size = strlen(data);

	//pad the codeword with 0's
	for(i = data_size; i < data_size+N-1; i++) 
	{
		codeword[i] = '0';
	}

	printf("\nModified data is :        %s", codeword);

	//initial crc calculation from the user input
	calculateCRC();

	printf("\nChecksum is : %s", crc);

	//codeword calculation before error is introduced
	for(i = data_size; i < data_size+N-1; i++) 
	{
			codeword[i] = crc[i-data_size];
	}
	printf("\nFinal codeword is :       %s", codeword);

	//introduce error with a bit rate error 
	//value that is given up at the top
	IntroduceError(codeword, bre);
	//XORwithPoly(codeword);
	
	//display the altered codeword
	printf("\nCorrupted Codeword data : %s\n", codeword);

	//recalculate the crc
	calculateCRC();

	//find if there is error in the codeword
	for(i = 0; (i < N-1) && (crc[i] != '1'); i++);
	{
		if(i < N-1) printf("\nError detected\n\n");
		else printf("\nNo error detected\n\n");
		return 0;
	}
}

//this function calculates the crc of the data
void calculateCRC()
{
	for(i = 0; i < N; i++) 
	{
		crc[i] = codeword[i];
	}

	do
	{
		if(crc[0] == '1') 
		{
			for(crc_index = 1; crc_index < N; crc_index++)
				{
					crc[crc_index] = ((crc[crc_index] == gen_poly[crc_index]) ? '0' : '1');
				}
		}

		for(crc_index = 0; crc_index < N-1; crc_index++) 
		{
			crc[crc_index] = crc[crc_index+1];
		}
		
		crc[crc_index] = codeword[i++];
	}while(i <= data_size+N-1);
}

//we altered the IntroduceError function so that
//it would work with a char array of '1' and '0'
//characters instead of hex
void IntroduceError(char *data, double p)
{
	char *pointer = data;
	i = 0;
	while (pointer[i] != '\0') 
	{
		if ((double)random()/M <= p) 
			pointer[i] = (pointer[i] == '0') ? '1' : '0';
		i++;
	}
}

void XORwithPoly(char *data)
{
	char *pointer = data;
	i = 0;
	while (pointer[i] != '\0') 
	{
		pointer[i] = (pointer[i] != gen_poly[i%17]) ? '1' : '0';
		i++;
	}
}