/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 15:23:34 by efarhat           #+#    #+#             */
/*   Updated: 2023/09/24 16:56:12 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <string.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include <stdio.h>
# include <fcntl.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft/libft.h"

# define GRID 64
# define ROWS 1000
# define COLUMS 1600
# define MINI_MAP 0.3
# define C 8
# define N 0
# define E 1
# define S 2
# define W 3

typedef struct s_element
{
	char	*id;
	char	*info;
	int		color[3];
}			t_element;

typedef struct s_pmap
{
	char		*file;
	int			fd;
	t_element	*elem;
	char		**map;
	char		pos;
	int			rows;
	int			colums;
	int			x;
	int			y;
}			t_pmap;

typedef struct s_mm
{
	mlx_image_t		*img;
	int				h;
	int				w;
	int				grid;
	int				rw;
	int				clm;
	float			px;
	float			py;
	unsigned int	col;
	int				y;
	int				x;
	int				a;
	int				b;
	int				c;
	int				d;

}			t_mm;

typedef struct s_map
{
	int				weight;
	int				height;
	mlx_t			*ptr_mlx;
	mlx_image_t		*img;
	int				window;
	t_pmap			*tmap;
	float			px;
	float			py;
	double			ongl;
	int				lr_walk;
	int				ud_walk;
	int				lr_view;
	double			move_speed;
	double			rotation_speed;
	double			fov;
	float			distance;
	unsigned int	color;
	unsigned int	cc;
	unsigned int	fc;
	mlx_texture_t	*tex[4];
	t_mm			*mm;
	int				mouse_x;
	int				mouse_y;
}	t_map;

typedef struct s_point
{
	int			x2;
	int			y2;
	int			dx;
	int			dy;
	float		xinc;
	float		yinc;
	int			steps;
	float		x;
	float		y;
	int			i;
}	t_point;

typedef struct s_ray
{
	float		cxh;
	float		cyh;
	float		cyv;
	float		cxv;
	double		ray_angle;
	int			hith;
}	t_ray;

// main
void			draw_map(t_map *map);
void			put_image(char c, t_map *map);
void			put_pixel_in_img(t_map *map, int x, int y, char c);
void			handler_moves(void *param);
void			player_pos(t_map *map);
void			init_value(t_map *s);
void			walk_move(t_map *map);
void			move_left_right(t_map *map);
void			put_rays(t_map *s, float angle, double distance);
double			_abs(double c);
void			check_wall(t_map *map, float x, float y);
void			hook(t_map *map);
void			cast_rays(t_map *s);
double			first_cray(t_map *s, t_ray *r);
void			cast_rays(t_map *s);
void			raycating_horizontal(t_map *s, t_ray *r);
void			raycating_vertical(t_map *s, t_ray *r);
int				is_wall(t_map *s, float y, float x);
void			normalize_angle(t_ray *r);
void			init_angle(t_map *s);
void			handler_move_view(t_map *s);
void			check_steps_h(t_ray *r, t_map *s, float steps_x, float steps_y);
void			check_steps_v(t_ray *r, t_map *s, float steps_x, float steps_y);
void			draw_colome(t_map *s, int i, double w_s);
double			ray_distance(double dis_h, double dis_v, t_ray *r);

int				check_map(t_pmap *tmap);
t_element		*init_telem(char *map);
void			check_elements(t_pmap *tmap);
void			get_map(t_pmap *tmap, char *s);
//		UTILS		//
int				ft_error(char *str, int ex, int ret);
char			*ft_read_file(int fd);
int				num_lines(char **arr);
void			clean_arr2d(char **arr2d);
void			put_tex_colmn(t_map *s, int x, double w_s, t_ray ray);
void			load_textures_c(t_map *s);
void			draw_c_f(t_map *s, double ws, int x, int f);
unsigned int	get_color(unsigned int r, unsigned int g,
					unsigned int b, unsigned int a);
#endif
