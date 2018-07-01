/*
Date:27-Jan-2014
@Created By: Ananth Hegde
Digital signal Processing
Sampling of Wave file.
This file has libraries for manupulating wave files
*/
#include<stdio.h>
#include<conio.h>
#include<math.h>
#include "wave.h"

/*Reads the wave file*/
struct WavHeader *wavread(char *file_name)
{
 struct WavHeader *header;
 short int *Data;
 FILE *fhandle=fopen(file_name,"rb");
 header = (struct WavHeader*) malloc (sizeof(struct WavHeader)*1);
 fread(header,44,1,fhandle);
 Data=(short int*) malloc (sizeof(short int)*header->Subchunk2Size/(header->BitsPerSample/8));
 fread(Data,header->BitsPerSample/8,header->Subchunk2Size/(header->BitsPerSample/8),fhandle);
 header->Data = Data;
 fclose(fhandle);
 return header;

}


  /*Resamples and returns entire wave file*/
 struct WavHeader *CreateSampledWaveFile(struct WavHeader *header,int SampleRate)
{
 struct WavHeader *sampledheader;
 int m,n;
 double samplevalue = 0;
 double temp =0;
 short int *ReSampledData1;
 char ChunkID[4];

 double radians,phasediff,sinc,frequencyratio;
 radians = (double)2*3.142*(header->SampleRate/2);
 frequencyratio = (double)SampleRate/header->SampleRate;
 sampledheader = (struct WavHeader*) malloc (sizeof(struct WavHeader)*1);
 sampledheader->Subchunk2Size = header->Subchunk2Size*((float)SampleRate/header->SampleRate);
 ReSampledData1=(short int*) malloc (sizeof(short int)*sampledheader->Subchunk2Size/(header->BitsPerSample/8));
 for( m = 0; m < sampledheader->Subchunk2Size/2;m++)
 {
  
 for( n = ((float)m/frequencyratio - 1);n<=((float)m/frequencyratio + 1);n++)
 {
  phasediff = (double) radians*((double)(1.0*m/SampleRate) - ((double)1.0*n/header->SampleRate));
  
  if(n>=0 && n <  header->Subchunk2Size/2)
  {
   //temp = (double)phasediff; 
  if(phasediff ==0) //if(n == m/frequencyratio)
  {
  sinc = 1.0;
  }
  else
  {
   sinc = (double)sinf(phasediff)/phasediff;
  }
   samplevalue = samplevalue + (double)1.0*header->Data[n]*sinc; 
  }
 }
 ReSampledData1[m] = samplevalue;
 //printf("\n%f",samplevalue);
 samplevalue = 0.0;
 }
 
 sampledheader->ChunkSize = 36 + sampledheader->Subchunk2Size;
 for(m=0;m<4;m++)
 {
 sampledheader->ChunkID[m] = header->ChunkID[m];
 sampledheader->Format[m] = header->Format[m];
 sampledheader->Subchunk1ID[m] = header->Subchunk1ID[m];
 sampledheader->Subchunk2ID[m]=header->Subchunk2ID[m];
 }
 sampledheader->Subchunk1Size = header->Subchunk1Size;
 sampledheader->AudioFormat = header->AudioFormat;
 sampledheader->NumChannels = header->NumChannels;
 sampledheader->SampleRate =SampleRate ;
 sampledheader->ByteRate = sampledheader->SampleRate*sampledheader->NumChannels*(header->BitsPerSample/8);
 sampledheader->BlockAlign = sampledheader->NumChannels*(header->BitsPerSample/8);
 sampledheader->BitsPerSample=header->BitsPerSample;
 sampledheader->Data = ReSampledData1;
 return sampledheader;
}

 /*Writes the entire data into wave format*/
 void waveWrite(char *file_name,struct WavHeader *header)
{
 FILE *fhandle=fopen(file_name,"wb");
 fwrite(header,sizeof(struct WavHeader),1,fhandle);
 fwrite(header->Data,header->BitsPerSample/8,header->Subchunk2Size/(header->BitsPerSample/8),fhandle);
 fclose(fhandle);
}

 /*Releases memory*/
 void DeallocateMemory(struct WavHeader *header)
 {
  free(header->Data);
  free(header);
 }