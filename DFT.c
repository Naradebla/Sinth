#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define maxSample 250
#define ZeroMemory(a,b) memset(a,0,b)
int loadCSV(char* path,double* out){
	FILE *fp;
	fp = fopen(path,"r");
	char buffer;
	char dataBuffer[10];
	double outputBuffer[maxSample];
	
	int i = 0;
	int s = 0;
	int p = 0;
	while(1){
		buffer = fgetc(fp);
		if(feof(fp)){
			break;
		}
		if(buffer == ','){
			i = 0;
			s = 1;
			outputBuffer[p] = atof(dataBuffer);
			ZeroMemory(dataBuffer,10);
			p++;		
		}else if(buffer == '\n'){
			s = 0;
		}else{
			if(s == 0){
				dataBuffer[i] = buffer;
				i++;
			}
		}
	}
	for(int i = 0; i < p; i++){
		*out = outputBuffer[i];
		out++;
	}
	return p;
	
}
int main(int argc, char **argv)
{
	double data[maxSample];
	int len = loadCSV("test.csv",&data[0]);
	for(int i = 0; i < len;i++){
		printf("%d",data[i]);
	}
}