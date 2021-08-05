#ifndef __MP3DECODER_API_H__
#define __MP3DECODER_API_H__

void* MP3Decoder_API_context_Create();

/* Check ID3 header and remove it to avoid decode error */

int MP3Decoder_API_ID3Header_Check(void *API , void* Input , int InputLen);

/* Decode process */

int MP3Decoder_API_Process(void *API , void* Input , void* Output , int InputLen);

/* Free object */

void MP3Decoder_API_free(void *API);

/* Return 0 means the whole ID3 header is removed. */

int MP3Decoder_API_Get_ID3(void* API);

/* Return sample rate */

int MP3Decoder_API_Get_SampleRate(void *API);

/* Return bit rate */

int MP3Decoder_API_Get_BitRate(void *API);

/* Return bit number of decoded output sample */

int MP3Decoder_API_Get_SampleBits(void *API);

/* Return channel number */

int MP3Decoder_API_Get_Channels(void *API);

/* Return output length of decoded stream , zero means decode error or decode finish. */

int MP3Decoder_API_Get_OutputLen(void *API);

int MP3Decoder_API_Get_ByteConsume(void *API);
int MP3Decoder_API_Get_ByteLeft(void *API);

int MP3Decoder_API_Get_Min_InputLen();
int MP3Decoder_API_Get_Min_OutputLen();

#endif /* __MP3DECODER_API_H__ */
