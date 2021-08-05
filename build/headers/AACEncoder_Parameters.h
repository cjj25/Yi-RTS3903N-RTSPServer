#ifndef _AACENCODER_PARAMETERS_
#define _AACENCODER_PARAMETERS_

/* ID = 0 => Set SampleRate and BitRate */

typedef struct {
	int m_SampleRate;
	int m_BitRate;
} AacEncoder_Para0;

/* ID = 1 => Set channel number */

typedef struct {
	int m_Channels;
} AacEncoder_Para1;

#endif
