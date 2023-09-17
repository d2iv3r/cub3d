/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 17:06:21 by mel-harc          #+#    #+#             */
/*   Updated: 2023/09/17 15:37:49 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	handler_moves(void *param)
{
	t_map	*s;

	s = (t_map *)param;
	hook(s);
	mlx_delete_image(s->ptr_mlx, s->img);
	s->img = NULL;
	s->window = 0;
	s->img = mlx_new_image(s->ptr_mlx, s->weight, s->height);
	if (!s->img)
		ft_error("Error\nmlx_new_imge", 1, 0);
	s->window = mlx_image_to_window(s->ptr_mlx, s->img, 0, 0);
	if (s->window < 0)
		ft_error("Error\nmlx_imge_to window", 1, 0);
	cast_rays(s);
	drawing_img(s);
	handler_move_view(s);
	pixels_player(s, s->px, s->py);
	direction_player(s, 20);
	s->lr_walk = 0;
	s->ud_walk = 0;
	s->lr_view = 0;
}

void	direction_player(t_map *s, float distance)
{
	t_point	p;
	int		i;
	float	x;
	float	y;

	i = -1;
	x = (s->px + 20) * MINI_MAP;
	y = (s->py + 20) * MINI_MAP;
	put_line(&p, s, distance);
	while (++i < p.steps)
	{
		if (x >= 0 && x <= s->weight && y >= 0 && y <= s->height)
		{
			mlx_put_pixel(s->img, floor(x), floor(y), 0xFF5733FF);
			x += p.xinc;
			y += p.yinc;
		}
		else
			break ;
	}
}

void	handler_move_view(t_map *s)
{
	if (s->ud_walk)
		walk_move(s);
	if (s->lr_walk)
	{
		s->ongl += M_PI / 2;
		walk_move(s);
		s->ongl -= M_PI / 2;
	}
	if (s->lr_view)
		s->ongl += (s->lr_view * s->rotation_speed);
}

void	hook(t_map *s)
{
	if (mlx_is_key_down(s->ptr_mlx, MLX_KEY_ESCAPE))
		mlx_close_window(s->ptr_mlx);
	if (mlx_is_key_down(s->ptr_mlx, MLX_KEY_A))
		s->lr_walk = -1;
	if (mlx_is_key_down(s->ptr_mlx, MLX_KEY_D))
		s->lr_walk = 1;
	if (mlx_is_key_down(s->ptr_mlx, MLX_KEY_W) || \
		mlx_is_key_down(s->ptr_mlx, MLX_KEY_UP))
		s->ud_walk = 1;
	if (mlx_is_key_down(s->ptr_mlx, MLX_KEY_UP))
		s->ud_walk = 1;
	if (mlx_is_key_down(s->ptr_mlx, MLX_KEY_S) || \
		mlx_is_key_down(s->ptr_mlx, MLX_KEY_DOWN))
		s->ud_walk = -1;
	if (mlx_is_key_down(s->ptr_mlx, MLX_KEY_LEFT))
		s->lr_view = -1;
	if (mlx_is_key_down(s->ptr_mlx, MLX_KEY_RIGHT))
		s->lr_view = 1;
}

void	walk_move(t_map *map)
{
	float	step;
	float	x;
	float	y;

	if (map->lr_walk)
	{
		step = map->lr_walk * map->move_speed;
		y = map->py + sin(map->ongl) * step;
		x = map->px + cos(map->ongl) * step;
	}
	if (map->ud_walk)
	{
		step = map->ud_walk * map->move_speed;
		y = map->py + sin(map->ongl) * step;
		x = map->px + cos(map->ongl) * step;
	}
	check_wall(map, x, y);
}
