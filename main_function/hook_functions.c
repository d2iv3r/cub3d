/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 17:06:21 by mel-harc          #+#    #+#             */
/*   Updated: 2023/09/22 20:45:22 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	handler_moves(void *param)
{
	t_map	*s;

	s = (t_map *)param;
	hook(s);
	mlx_delete_image(s->ptr_mlx, s->img);
	s->img = mlx_new_image(s->ptr_mlx, COLUMS, ROWS);
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
		if (x >= 0 && y >= 0 && y < ROWS && x < COLUMS)
		{
			mlx_put_pixel(s->img, floor(x), floor(y), 0xFF5733FF);
			x += p.xinc;
			y += p.yinc;
		}
		else
			break ;
	}
}

void	mouse_helper(t_map *s)
{
	int		new_x;
	int		new_y;
	int		distance;
	float	r;

	mlx_get_mouse_pos(s->ptr_mlx, &new_x, &new_y);
	if (new_x > 0 && new_x < COLUMS && new_y > 0 && new_y < ROWS)
	{
		if (s->mouse_x != new_x)
		{
			distance = new_x - s->mouse_x;
			r = (_abs(distance) * (M_PI * 2) / COLUMS);
			if (distance < 0)
				s->ongl -= r;
			else
				s->ongl += r;
			s->mouse_x = new_x;
		}
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
	mouse_helper(s);
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
