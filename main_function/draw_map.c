/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 12:02:50 by mel-harc          #+#    #+#             */
/*   Updated: 2023/09/17 13:25:02 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
		while (++j < 20)
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
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			ox = (x + i + 20) * MINI_MAP;
			oy = (y + j + 20) * MINI_MAP;
			if (ox >= 0 && ox <= map->weight && oy >= 0 && oy <= map->height)
				mlx_put_pixel(map->img, ox, oy, 0xFF5733FF);
		}
	}
}

void	draw_colome(t_map *s, int i, double w_s)
{
	int	start;
	int	p;

	p = 0;
	start = (s->height / 2) - (w_s / 2);
	while (p < w_s)
	{
		if ((p + start) > 0 && (p + start) < s->height)
			mlx_put_pixel(s->img, i, p + start, s->color);
		p++;
	}
}
