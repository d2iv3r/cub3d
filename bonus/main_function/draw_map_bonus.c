/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 14:46:22 by mel-harc          #+#    #+#             */
/*   Updated: 2023/09/24 14:46:27 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	draw_map(t_map *s)
{
	init_value(s);
	mlx_loop_hook(s->ptr_mlx, handler_moves, s);
	mlx_loop(s->ptr_mlx);
	mlx_delete_image(s->ptr_mlx, s->img);
	mlx_terminate(s->ptr_mlx);
}

void	drawing_img(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (map->tmap->map[++i])
	{
		j = -1;
		while (map->tmap->map[i][++j])
		{
			if (map->tmap->map[i][j] == '1')
				pixels_wall(map, (j * GRID) * MINI_MAP, (i * GRID) * MINI_MAP);
		}
	}
}

void	pixels_wall(t_map *map, int x, int y)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 20)
	{
		j = -1;
		while (++j < 20 && y + j < ROWS && i + x < COLUMS)
			mlx_put_pixel(map->img, x + i, y + j, 0xFFFFFF);
	}
}

void	pixels_player(t_map *map, float x, float y)
{
	int		i;
	int		j;
	float	ox;
	float	oy;

	i = -1;
	while (++i < 8)
	{
		j = -1;
		while (++j < 8)
		{
			ox = (x + i) * MINI_MAP;
			oy = (y + j) * MINI_MAP;
			if (ox >= 0 && ox <= COLUMS && oy >= 0 && oy <= ROWS)
				mlx_put_pixel(map->img, ox, oy, 0xFFFFFF);
		}
	}
}

void	direction_player(t_map *s, float distance)
{
	t_point	p;
	int		i;
	float	x;
	float	y;

	i = -1;
	x = s->px * MINI_MAP;
	y = s->py * MINI_MAP;
	put_line(&p, s, distance);
	while (++i < p.steps)
	{
		if (x >= 0 && x <= s->weight && y >= 0 && y <= s->height
			&& y < ROWS && x < COLUMS)
		{
			mlx_put_pixel(s->img, floor(x), floor(y), 0xFFFFFF);
			x += p.xinc;
			y += p.yinc;
		}
		else
			break ;
	}
}
