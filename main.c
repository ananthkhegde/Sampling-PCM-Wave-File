/*
Date:27-Jan-2014
@Created By: Ananth Hegde
Digital signal Processing
Sampling of Wave file.
This is a driver file
*/
#include<stdio.h>
#include<conio.h>
#include<malloc.h>
#include<math.h>
#include "wave.h"

#define PATH "C:\\Users\\ananth\\Downloads\\sample.wav"
#define DEST "C:\\Users\\ananth\\Desktop\\new.wav"

int main()
{
 // Driver.
 int  newsSampleRate;
 struct WavHeader *header,*sampledheader;
 header = wavread(PATH);
 printf("Sampling frequency of selected wave file is: %dHz\n",header->SampleRate);
 printf("Please enter the sampling frequency for the file to be converted:\n");
 scanf("%d",&newsSampleRate);
 printf("\nConverting..... Please wait...");
 sampledheader = CreateSampledWaveFile(header,newsSampleRate);
 waveWrite(DEST,sampledheader);
 DeallocateMemory(header);
 DeallocateMemory(sampledheader);
 return 0;
}
