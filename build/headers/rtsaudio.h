/*
 * Realtek Semiconductor Corp.
 *
 * include/rtsaudio.h
 *
 * Copyright (C) 2016      Wind Han<wind_han@realsil.com.cn>
 */
#ifndef _INCLUDE_RTSAUDIO_H
#define _INCLUDE_RTSAUDIO_H

#ifdef __cplusplus
extern "C"
{
#endif

enum enum_rts_audio_type_id {
	RTS_AUDIO_TYPE_ID_MP3 = 1,
	RTS_AUDIO_TYPE_ID_ULAW,
	RTS_AUDIO_TYPE_ID_ALAW,
	RTS_AUDIO_TYPE_ID_PCM,
	RTS_AUDIO_TYPE_ID_G726,
	RTS_AUDIO_TYPE_ID_AMRNB,
	RTS_AUDIO_TYPE_ID_AAC,
	RTS_AUDIO_TYPE_ID_SBC,
	RTS_AUDIO_TYPE_ID_OPUS,
};

struct rts_aec_control {
	uint32_t aec_enable;
	uint32_t ns_enable;
	uint32_t ns_level;
	uint32_t aec_scale;
	uint32_t dump_enable;
	char mic_name[256];
	char spk_name[256];
	uint32_t aec_thr;
	uint32_t reserved[2];
};

struct rts_mixer_control {
	uint32_t mixer_thr;
	uint32_t reserved[4];
};

int rts_av_query_aec_ctrl(unsigned int chnno, struct rts_aec_control **ppctrl);
int rts_av_set_aec_ctrl(struct rts_aec_control *ctrl);
void rts_av_release_aec_ctrl(struct rts_aec_control *ctrl);

int rts_av_query_amixer_ctrl(unsigned int chnno,
			struct rts_mixer_control **ppctrl);
int rts_av_set_amixer_ctrl(struct rts_mixer_control *ctrl);
void rts_av_release_amixer_ctrl(struct rts_mixer_control *ctrl);

int rts_audio_codec_check_encode_id(int id);
int rts_audio_codec_check_decode_id(int id);

int rts_av_query_audio_encode_ability(unsigned int chnno,
				      struct rts_audio_ability_t **ability);
void rts_av_release_audio_encode_ability(struct rts_audio_ability_t *ability);
#ifdef __cplusplus
}
#endif
#endif
