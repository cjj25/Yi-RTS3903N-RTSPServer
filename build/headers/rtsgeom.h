/*
 * Realtek Semiconductor Corp.
 *
 * librtsgeom/include/rtsgeom.h
 *
 * Copyright (C) 2016      Ming Qian<ming_qian@realsil.com.cn>
 */
#ifndef _LIBRTSGEOM_INCLUDE_RTSGEOM_H
#define _LIBRTSGEOM_INCLUDE_RTSGEOM_H

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef PI
#define PI	(3.141592653589793)
#endif

struct rts_geom_point {
	double x;
	double y;
};

/*
 * a * y = k * x + c;
 * generally set a = 1 or a = 0
 * */
struct rts_geom_line {
	double a;
	double k;
	double c;
};

struct rts_geom_segment {
	struct rts_geom_point start;
	struct rts_geom_point end;
};

struct rts_geom_rect {
	struct rts_geom_point start;
	double width;
	double height;
};

struct rts_geom_interval {
	double start;
	double end;
};

struct rts_geom_circle {
	struct rts_geom_point center;
	double radius;
};

double rts_geom_calc_line_x(struct rts_geom_line *line, double y);
double rts_geom_calc_line_y(struct rts_geom_line *line, double x);
int rts_geom_compare_point(struct rts_geom_point *pa,
			   struct rts_geom_point *pb);
int rts_geom_calc_line_from_2_point(struct rts_geom_point *pa,
				    struct rts_geom_point *pb,
				    struct rts_geom_line *line);
double rts_geom_check_point_in_line(struct rts_geom_line *line,
				    struct rts_geom_point *point);
int rts_geom_check_same_line(struct rts_geom_line *linea,
			     struct rts_geom_line *lineb);
int rts_geom_check_line_parallel(struct rts_geom_line *linea,
				 struct rts_geom_line *lineb);
int rts_geom_get_lines_cross_point(struct rts_geom_line *linea,
				   struct rts_geom_line *lineb,
				   struct rts_geom_point *point);
int rts_geom_get_line_and_segment_cross_point(
		struct rts_geom_line *line,
		struct rts_geom_segment *segment,
		struct rts_geom_point *point);
int rts_geom_intersect_line_rect(struct rts_geom_line *line,
				 struct rts_geom_rect *rect,
				 struct rts_geom_point *pa,
				 struct rts_geom_point *pb);
int rts_geom_get_interval_overlap(struct rts_geom_interval *a,
				  struct rts_geom_interval *b,
				  struct rts_geom_interval *result);
int rts_geom_check_segment_intersect_rect(
		struct rts_geom_rect *rect,
		struct rts_geom_segment *segment);
int rts_geom_get_vertical_line(struct rts_geom_line *line,
			       struct rts_geom_point *point,
			       struct rts_geom_line *vline);
int rts_geom_get_parallel_line(struct rts_geom_line *line,
			       struct rts_geom_point *point,
			       struct rts_geom_line *pline);
double rts_geom_calc_points_distance(struct rts_geom_point *a,
				     struct rts_geom_point *b);
double rts_geom_calc_point_line_distance(struct rts_geom_point *point,
					 struct rts_geom_line *line);
int rts_geom_get_line_and_circle_cross_point(struct rts_geom_line *line,
					     struct rts_geom_circle *circle,
					     struct rts_geom_point *pa,
					     struct rts_geom_point *pb);
double rts_geom_calc_line_angle(struct rts_geom_line *line);
double rts_geom_calc_lines_intersection_angle(struct rts_geom_line *linea,
					      struct rts_geom_line *lineb);
double rts_geom_calc_linear_equation(struct rts_geom_line *line,
				     struct rts_geom_point *point);

#ifdef __cplusplus
}
#endif
#endif
