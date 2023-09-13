/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 12:02:50 by mel-harc          #+#    #+#             */
/*   Updated: 2023/09/13 16:47:46 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3d.h"

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

	unsigned int color = 0x000000FF;
	// i = -1;
	// while (map->tmap->map[++i])
	// {
	// 	j = -1;
	// 	while (map->tmap->map[i][++j])
	// 	{
	// 		if (map->tmap->map[i][j] == '1')
	// 			pixels_wall(map, (j * 40), (i * 40));
	// 	}
	// }
	i = 0;
	j = 0;
	while (i < (int)map->weight)
	{
		while (j < (int)map->height)
		{
			color = 0x000000FF;
			if (j >= (int)(map->height / 2))
				color = 0xFFFFFFFF;
			mlx_put_pixel(map->img, i, j, color);
			j++;	
		}
		j = 0;
		i++;
	}
}

void	pixels_wall(t_map *map, int x, int y)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 40)
	{
		j = -1;
		while (++j < 40)
			mlx_put_pixel(map->img, x + i, y + j, 0xFFFFFF);
	}
}

void	pixels_player(t_map *map, float x, float y)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			mlx_put_pixel(map->img, x + i, y + j, 0xFF5733FF);
	}
}

