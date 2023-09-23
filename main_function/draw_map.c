/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 12:02:50 by mel-harc          #+#    #+#             */
/*   Updated: 2023/09/22 22:35:59 by mel-harc         ###   ########.fr       */
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
	while (++i < (GRID * MINI_MAP))
	{
		j = -1;
		while (++j < (GRID * MINI_MAP) && y + j < ROWS && i + x < COLUMS)
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
			if (ox >= 0 && ox <= COLUMS && oy >= 0 && oy <= ROWS)
				mlx_put_pixel(map->img, ox, oy, 0xFF5733FF);
		}
	}
}
