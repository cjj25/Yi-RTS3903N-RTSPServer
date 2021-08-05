#ifndef _RT_AEC_NS_API_H_
#define _RT_AEC_NS_API_H_

/*
	Realtek AEC and NS spec:

	Speaker Number¡G1
	Microphone Number¡G1
	SampleRate¡G16000 Hz
	Process Block length¡G256 samples
	Input string must be "DeInterleaved". Interleaved string is not supported.
	I/O Data format is defined by AecNs_Resolution. It means the number of fractional bits.
	Output is mono signal string.
*/

#define AecNs_Resolution		24
#define One_AecNs				(long)(1<<AecNs_Resolution)

/* 	Function for processing data. Where 
   	pMic is 1-dimensional deinterleaved microphone signal array.
   	pSpk is 1-dimensional deinterleaved speaker signal array.
   	pOut is 1-dimensional output signal array.
*/

// Create AecNs object and initial

void* RTAecNs_API_context_Create(int fs);

// Free all objects and buffers

void  RTAecNs_API_free(void* AecNsAPI);

// Main process , return value is useless so far

int   RTAecNs_API_Process(void* AecNsAPI , long **pMic , long **pSpk , long *pOut);

// Set/Get Aec and NS parameter , return value equals to -1 means Set/Get fail.
// The IDs and parameter define can be found in AecNs_Parameters.h

int   RTAecNs_API_Set(void* AecNsAPI , void* pParameters , int size , unsigned int IDs);
int   RTAecNs_API_Get(void* AecNsAPI , void* pParameters , int size , unsigned int IDs);

#endif
