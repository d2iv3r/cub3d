/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 17:10:11 by mel-harc          #+#    #+#             */
/*   Updated: 2023/09/13 23:26:13 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	player_pos(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	map->px = 0;
	map->py = 0;
	while (map->tmap->map[++i])
	{
		j = -1;
		while (map->tmap->map[i][++j])
		{
			if (map->tmap->map[i][j] == 'S')
			{
				map->px = (j * 80);
				map->py = (i * 80);
			}
		}
	}
}

void	put_rays(t_map *s, float angle, double distance)
{
	t_point	p;
	int		i;
	float	X;
	float	Y;

	p.x2 = s->px + (cos(angle) * (distance * 0.2));
	p.y2 = s->py + (sin(angle) * (distance * 0.2));
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

double	_abs(double c)
{
	if (c < 0)
		c *= -1;
	return (c);
}

void	init_value(t_map *s)
{
	init_angle(s);
	get_space(s);
	s->ptr_mlx = mlx_init(s->weight, s->height, "cub3d", true);
	if (!s->ptr_mlx)
		ft_error("Error\nmlx_init", 1, 0);
	s->img = mlx_new_image(s->ptr_mlx, s->weight, s->height);
	if (!s->img)
		ft_error("Error\nmlx_new_imge", 1, 0);
	s->window = mlx_image_to_window(s->ptr_mlx, s->img, 0, 0);
	if (s->window < 0)
		ft_error("Error\nmlx_imge_to window", 1, 0);
	drawing_img(s);
	player_pos(s);
	pixels_player(s, s->px * 0.2, s->py * 0.2);
}

void	init_angle(t_map *s)
{
	if (s->tmap->pos == 'S')
		s->ongl = 90 * (M_PI / 180);
	if (s->tmap->pos == 'W')
		s->ongl = 180 * (M_PI / 180);
	if (s->tmap->pos == 'E')
		s->ongl = 0;
	if (s->tmap->pos == 'N')
		s->ongl = 270 * (M_PI / 180);
	s->rotation_speed = 2 * (M_PI / 180);
	s->fov = 60 * (M_PI / 180);
	s->move_speed = 3;
	s->lr_view = 0;
	s->ud_walk = 0;
	s->lr_walk = 0;
	s->xv = 0;
	s->yv = 0;
}