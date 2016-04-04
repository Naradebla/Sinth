#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ZeroMemory(a,b) memset(a,0,b)

#define maxSample 250
#define pi 3.1415
int loadCSV(char* path,double* outA,double* outB){
	FILE *fp;
	fp = fopen(path,"r");
	char buffer;
	char dataBuffer[10];
	char dataBufferB[10];
	double outputBuffer[maxSample];
	double outputBufferB[maxSample];
	
	int i = 0;
	int s = 0;
	int p = 0;
	int c = 0;
	while(1){
		buffer = fgetc(fp);
		if(feof(fp)){
			break;
		}
		if(buffer == ','){
			s = 1;	
		}else if(buffer == '\n'){
			s = 0;
			i = 0;
			c = 0;
			outputBuffer[p] = atof(dataBuffer);
			outputBuffer[p] = atof(dataBufferB);
			ZeroMemory(dataBuffer,10);
			ZeroMemory(dataBufferB,10);
			p++;	
		}else{
			if(s == 1){
				dataBuffer[i] = buffer;
				i++;
			}else{
				dataBufferB[c] = buffer;
				c++;
			}
		}
	}
	for(int i = 0; i < p; i++){
		*outA = outputBuffer[i];
		*outB = outputBufferB[i];
		outA++;
		outB++;
	}
	return p;
	
}
int DFT(double* input,double* time, double* output, int samples, double* freqs,int freqLen){
	double vectorA[freqLen][samples][2];
	double* inputPointer = input;
	double* freqPointer = freqs;
	double* timePointer = time;
	double reTemp = 0;
	double imTemp = 0;
	double returnVal [freqLen];
	freqPointer = freqs;
	for(int i = 0; i < freqLen;i++){
		for(int c = 0; c < samples; c++){
			reTemp = reTemp + (*inputPointer * cos(2*pi*(*freqPointer)*(*timePointer)));
			imTemp = reTemp + (*inputPointer * sin(2*pi*(*freqPointer)*(*timePointer)));
			inputPointer++;
			timePointer++;
		}
		returnVal[i] = sqrt((reTemp*reTemp)+(imTemp*imTemp));
		freqPointer++;
		inputPointer = input;
		reTemp = 0;
		imTemp = 0;
	}
	for(int i = 0; i < freqLen;i++){
		*output = returnVal[i];
		output++;
	}
	return freqLen;
}
void generateFreqList(double* target,int len, double baseFreq,double endFreq){
	double step = (endFreq-baseFreq)/len;
	for(int i = 0; i < len;i++){
		*target = baseFreq + (i*step);
		target++;
	}
}
void writeCSV(double* x, double* y,int len, char* path){
	FILE *f = fopen(path, "w");
	for(double i = 0; i < len; i++){
		fprintf(f,"%f,%f \n",*y,*x);
		x++;
		y++;
	}
	fclose(f);
}
int main(int argc, char **argv)
{
	printf("\n");
	double data[maxSample];
	double time[maxSample];
	int len = loadCSV("test.csv",&data[0],&time[0]);
	for(int i = 0; i < len;i++){
		printf("Data %i: %f,%f\n",i,data[i],time[i]);
	}
	double freqs[50];
	int freqLen = 50;
	generateFreqList(&freqs[0],freqLen,10,10000);
	double DFTVals[50];
	DFT(&data[0],&DFTVals[0],&time[0],len,&freqs[0],freqLen);
	writeCSV(&DFTVals[0],&freqs[0],freqLen,"DFT.csv");
	
}