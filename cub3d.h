/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 15:23:34 by efarhat           #+#    #+#             */
/*   Updated: 2023/09/19 10:52:01 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <string.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft/libft.h"

# define GRID 64
# define ROWS 15
# define COLUMS 27
# define MINI_MAP 0.3
# define N 0
# define E 1
# define S 2
# define W 3

///////////////////64*64///////////////////
# define N_TEX "textures/northTexture.png"
# define E_TEX "textures/eastTexture.png"
# define S_TEX "textures/southTexture.png"
# define W_TEX "textures/westTexture.png"

/////////////////128*128///////////////////
// # define N_TEX "../textures/Bricks_01.png"
// # define E_TEX "../textures/chessBoard.png"
// # define S_TEX "../textures/Tile_20.png"
// # define W_TEX "../textures/Tile_16.png"

////////////////2048*2048///////////////////
// # define N_TEX "../textures/BrickWallBlue.png"
// # define E_TEX "../textures/BrickWallPurple.png"
// # define S_TEX "../textures/redBricksWall.png"
// # define W_TEX "../textures/BrickWallGrey.png"

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
	mlx_texture_t	*tex[4];
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	unsigned int	a;
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
void	get_space(t_map *map);
void	draw_map(t_map *map);
void	drawing_img(t_map *map);
void	put_image(char c, t_map *map);
void	put_pixel_in_img(t_map *map, int x, int y, char c);
void	pixels_player(t_map *map, float x, float y);
void	pixels_wall(t_map *map, int x, int y);
void	handler_moves(void *param);
void	player_pos(t_map *map);
void	init_value(t_map *s);
void	walk_move(t_map *map);
void	move_left_right(t_map *map);
void	put_rays(t_map *s, float angle, double distance);
double	_abs(double c);
void	check_wall(t_map *map, float x, float y);
void	hook(t_map *map);
void	cast_rays(t_map *s);
double	first_cray(t_map *s, t_ray *r);
void	cast_rays(t_map *s);
void	raycating_horizontal(t_map *s, t_ray *r);
void	raycating_vertical(t_map *s, t_ray *r);
int		is_wall(t_map *s, float x, float y);
void	normalize_angle(t_ray *r);
void	init_angle(t_map *s);
void	handler_move_view(t_map *s);
void	direction_player(t_map *s, float distance);
void	put_line(t_point *p, t_map *s, float distance);
void	check_steps_h(t_ray *r, t_map *s, float steps_x, float steps_y);
void	check_steps_v(t_ray *r, t_map *s, float steps_x, float steps_y);
void	draw_colome(t_map *s, int i, double w_s);

//	UTILS MAP
char	*ft_read_file(int fd);
char	*remove_empty(char *s);
void	init_tmap(t_pmap *tmap);
void	check_empty_lines(char *s);
int		num_lines(char **arr);
char	*get_iden(char *s);
char	*get_info(char *s);
int		ft_error(char *str, int ex, int ret);
void	clean_arr2d(char **arr2d);
int		check_map(t_pmap *tmap);
int		closed_map(t_pmap tmap);
void	put_tex_colmn(t_map *s, int x, double w_s, t_ray ray);
int		is_mapcharacters(char c);
int		is_identifier(char *id);

#endif
