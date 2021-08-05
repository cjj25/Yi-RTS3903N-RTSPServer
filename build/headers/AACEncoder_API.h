#ifndef __AACENCODER_API_H__
#define __AACENCODER_API_H__

/* Create Encoder object */

void *AACEncoder_API_context_Create();

/* Encode process */

int AACEncoder_API_Process(void *API,
		short *Input, char *Output, int InputLen);

/* Free object */

void AACEncoder_API_free(void *API);

/* Set/Get parameter function */

int AACEncoder_API_Set(void *API,
		void *pParameters, int size, unsigned int IDs);
int AACEncoder_API_Get(void *API,
		void *pParameters, int size, unsigned int IDs);

/* Get block length of I/O buffer */

int AACEncoder_API_GetBlockLen(void *API);

#endif /* __AACENCODER_API_H__ */
