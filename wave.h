/*
Date:27-Jan-2014
@Created By: Ananth Hegde
Digital signal Processing
Sampling of Wave file.
This header file has a structure which defines wave file
*/
#include <stdlib.h>


typedef struct WavHeader {
 char ChunkID[4];
 int ChunkSize;
 char Format[4];
char Subchunk1ID[4];
int Subchunk1Size;
short int AudioFormat;
short int  NumChannels;
int SampleRate;
int  ByteRate;
short int  BlockAlign;
short int   BitsPerSample;
char Subchunk2ID[4];
int  Subchunk2Size;
short int *Data;
};

struct WavHeader *wavread(char *file_name);
short int *ResampleData(short int *Data,int Subchunk2Size,short BitsPerSample);
struct WavHeader *CreateSampledWaveFile(struct WavHeader *header,int SampleRate);
void waveWrite(char *file_name,struct WavHeader *header);
void DeallocateMemory(struct WavHeader *header);