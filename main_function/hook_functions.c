/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 17:06:21 by mel-harc          #+#    #+#             */
/*   Updated: 2023/09/13 23:19:25 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3d.h"

void	handler_moves(void *param)
{
	t_map	*s;

	s = (t_map *)param;
	hook(s);
	mlx_delete_image(s->ptr_mlx, s->img);
	s->img = mlx_new_image(s->ptr_mlx, s->weight, s->height);
	if (!s->img)
		ft_error("Error\nmlx_new_imge", 1, 0);
	s->window = mlx_image_to_window(s->ptr_mlx, s->img, 0, 0);
	if (s->window < 0)
		ft_error("Error\nmlx_imge_to window", 1, 0);
	cast_rays(s);
	drawing_img(s);
	handler_move_view(s);
	pixels_player(s, s->px * 0.2, s->py * 0.2);
	direction_player(s, 20);
	s->lr_walk = 0;
	s->ud_walk = 0;
	s->lr_view = 0;
}

void	direction_player(t_map *s, float distance)
{
	t_point	p;
	int		i;
	float	X;
	float	Y;

	p.x2 = s->px + (cos(s->ongl) * distance);
	p.y2 = s->py + (sin(s->ongl) * distance);
	p.dx = p.x2 - s->px;
	p.dy = p.y2 - s->py;
	if (_abs(p.dy) > _abs(p.dx))
		p.steps = _abs(p.dy);
	else
		p.steps = _abs(p.dx);
	p.xinc = p.dx / (float)p.steps;
	p.yinc = p.dy / (float)p.steps;
	i = -1;
	X = s->px * 0.2;
	Y = s->py * 0.2;
	while (++i < p.steps)
	{
		if (X >= 0 && X <= (int)s->weight && Y >= 0 && Y <= (int)s->height)
		{
			mlx_put_pixel(s->img, floor(X), floor(Y), 0xFF5733FF);
			X += p.xinc;
			Y += p.yinc;
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

void	normalize_angle(t_ray *r)
{
	r->ray_angle = remainder(r->ray_angle, 2 * M_PI);
	if (r->ray_angle < 0)
		r->ray_angle = (2 * M_PI) + r->ray_angle; 
}

void	hook(t_map *s)
{
	if (mlx_is_key_down(s->ptr_mlx, MLX_KEY_ESCAPE))
		mlx_close_window(s->ptr_mlx);
	if (mlx_is_key_down(s->ptr_mlx, MLX_KEY_A))
		s->lr_walk = -1;
	if (mlx_is_key_down(s->ptr_mlx,  MLX_KEY_D))
		s->lr_walk = 1;
	if (mlx_is_key_down(s->ptr_mlx, MLX_KEY_W) || mlx_is_key_down(s->ptr_mlx, MLX_KEY_UP))
		s->ud_walk = 1;
	if (mlx_is_key_down(s->ptr_mlx, MLX_KEY_UP))
		s->ud_walk = 1;
	if (mlx_is_key_down(s->ptr_mlx, MLX_KEY_S) || mlx_is_key_down(s->ptr_mlx, MLX_KEY_DOWN))
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

void	check_wall(t_map *map, float x, float y)
{
	if (map->tmap->map[(int)floor(y / 80)][(int)floor(x / 80)] != '1' && \
		 map->tmap->map[(int)floor((y + 4)/ 80)][(int)floor((x + 4)/ 80)] != '1')
	{
		map->px = x;
		map->py = y;
	}
}
