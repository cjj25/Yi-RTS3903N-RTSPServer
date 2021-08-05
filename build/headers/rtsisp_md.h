/*
 * Realtek Semiconductor Corp.
 *
 * rtsisp/rtsisp_md.h
 *
 * Copyright (C) 2017      Ming Qian<ming_qian@realsil.com.cn>
 */
#ifndef _RTSISP_RTSISP_MD_H
#define _RTSISP_RTSISP_MD_H
#ifdef __cplusplus
extern "C"
{
#endif

#include <rtsisp_def.h>

uint32_t rts_isp_get_md_supported_grid_num(void);
uint32_t rts_isp_get_md_supported_detect_mode(void);
uint32_t rts_isp_get_md_supported_data_type(void);
int rts_isp_get_md_count(void);
int rts_isp_get_md_type(int fd, uint8_t mdidx);
int rts_isp_set_md_enable(int fd, uint8_t mdidx, int enable, int line_mode);
int rts_isp_get_md_enable(int fd, uint8_t mdidx, int *penable, int *line_mode);
int rts_isp_set_md_data_fmt(int fd, struct rts_isp_md_data_fmt *pfmt);
int rts_isp_get_md_data_fmt(int fd, struct rts_isp_md_data_fmt *pfmt);
int rts_isp_set_md_grid_bitmap(int fd, uint8_t mdidx,
			       struct rts_bitmap_t *pbitmap);
int rts_isp_get_md_grid_bitmap(int fd, uint8_t mdidx,
			       struct rts_bitmap_t *pbitmap);
int rts_isp_get_md_result(int fd, uint8_t mdidx,
			  struct rts_bitmap_t *pbitmap);
int rts_isp_set_md_grid(int fd, unsigned int strmidx, uint8_t mdidx,
			struct rts_grid_t *pgrid);
int rts_isp_get_md_grid(int fd, unsigned int strmidx, uint8_t mdidx,
			struct rts_grid_t *pgrid);
int rts_isp_set_md_rect(int fd, uint8_t strmidx, uint8_t mdidx,
			struct rts_rect_t *prect);
int rts_isp_get_md_rect(int fd, uint8_t strmidx, uint8_t mdidx,
			struct rts_rect_t *prect);
int rts_isp_set_md_grid_absolute(int fd, uint8_t mdidx,
				 struct rts_grid_t *pgrid);
int rts_isp_get_md_grid_absolute(int fd, uint8_t mdidx,
				 struct rts_grid_t *pgrid);
int rts_isp_set_md_rect_absolute(int fd, uint8_t mdidx,
				 struct rts_rect_t *prect);
int rts_isp_get_md_rect_absolute(int fd, uint8_t mdidx,
				 struct rts_rect_t *prect);
int rts_isp_set_md_sensitivity(int fd, uint8_t mdidx, uint8_t val);
int rts_isp_get_md_sensitivity(int fd, uint8_t mdidx, uint8_t *pval);
int rts_isp_set_md_percentage(int fd, uint8_t mdidx, uint8_t val);
int rts_isp_get_md_percentage(int fd, uint8_t mdidx, uint8_t *pval);
int rts_isp_set_md_threshold(int fd, uint8_t mdidx, uint32_t thd);
int rts_isp_get_md_threshold(int fd, uint8_t mdidx, uint32_t *thd);
int rts_isp_set_md_frame_interval(int fd, uint8_t mdidx, uint8_t val);
int rts_isp_get_md_frame_interval(int fd, uint8_t mdidx, uint8_t *pval);
int rts_isp_get_md_status(int fd, uint8_t mdidx);
int rts_isp_set_md_grid_res(int fd, uint16_t res_width, uint16_t res_height,
			    struct rts_grid_t *pgrid);
int rts_isp_get_md_grid_res(int fd, uint16_t res_width, uint16_t res_height,
			    struct rts_grid_t *pgrid);
int rts_isp_set_md_rect_res(int fd, uint8_t mdidx, uint16_t res_width,
			    uint16_t res_height, struct rts_rect_t *prect);
int rts_isp_get_md_rect_res(int fd, uint8_t mdidx, uint16_t res_width,
			    uint16_t res_height, struct rts_rect_t *prect);

int rts_isp_get_md_data_bpp(enum rts_isp_md_data_type type);
int rts_isp_get_md_data_length(uint32_t w, uint32_t h,
			       enum rts_isp_md_data_type type);
int rts_isp_set_md_dma(int fd, struct rts_isp_md_data *md_data);
int rts_isp_get_md_dma_addr(int fd, enum rts_isp_md_data_type type,
			    uint32_t *phy_addr);
int rts_isp_trig_md_data(int fd);
int rts_isp_set_md_dma_ready(int fd);
int rts_isp_set_md_detect_mode(int fd, enum rts_isp_md_detect_mode mode);
int rts_switch_md_control(int fd, int on);
int rts_isp_check_md_data_ready(int fd);
int rts_isp_set_md_line_area(int fd, struct rts_isp_md_line_area *area);
int rts_isp_get_md_line_area(int fd, struct rts_isp_md_line_area *area);
int rts_isp_set_md_line_nice_thd(int fd, int thd);
int rts_isp_get_md_line_nice_thd(int fd, int *thd);
int rts_isp_set_md_line_pause_pos(int fd, int pos);
int rts_isp_get_md_line_pause_pos(int fd, int *pos);
int rts_isp_get_md_line_result(int fd,
			       struct rts_isp_md_line_result *result);
int rts_isp_get_md_line_status(int fd);
int rts_isp_calc_md_line_bitmap(struct rts_grid_t *grid,
				struct rts_coordinate_t *start,
				struct rts_coordinate_t *end,
				struct rts_bitmap_t *bitmap,
				int value,
				int *number);
int rts_isp_calc_md_line_area(struct rts_grid_t *grid,
			      struct rts_coordinate_t *s,
			      struct rts_coordinate_t *e,
			      struct rts_isp_md_line_area *area);
uint32_t rts_isp_get_md_rect_result_num(void);
#ifdef __cplusplus
}
#endif
#endif
