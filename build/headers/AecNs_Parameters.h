#ifndef _AECNS_PARAMETERS_
#define _AECNS_PARAMETERS_

// Note that NS will be enabled when AEC is enabled.
// If both AEC and NS are disabled then the output will be the input mic signal

// ID = 0 => Set AEC enable

typedef struct
{
	int Enable;
} AecNs_Para0;

// ID = 1 => Set NS enable

typedef struct
{
	int Enable;
} AecNs_Para1;

// ID = 2 => Set AEC input signal delay

typedef struct
{
	int SpkDelay;
	int MicDelay;
} AecNs_Para2;

// ID = 3 => Set AecNs bypass

typedef struct
{
	int Bypass_En;
} AecNs_Para3;

// ID = 4 => Set NS Suppression Level

typedef struct
{
	int Level;
} AecNs_Para4;

#endif
