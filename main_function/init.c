/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:29:10 by mel-harc          #+#    #+#             */
/*   Updated: 2023/09/23 17:09:24 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_angle(t_map *s)
{
	if (s->tmap->pos == 'S')
		s->ongl = 90 * (M_PI / 180);
	if (s->tmap->pos == 'W')
		s->ongl = M_PI;
	if (s->tmap->pos == 'E')
		s->ongl = 0;
	if (s->tmap->pos == 'N')
		s->ongl = 270 * (M_PI / 180);
	s->rotation_speed = 3 * (M_PI / 180);
	s->fov = 60 * (M_PI / 180);
	s->move_speed = GRID / 7;
	s->lr_view = 0;
	s->ud_walk = 0;
	s->lr_walk = 0;
	s->weight = s->tmap->colums;
	s->height = s->tmap->rows;
}

void	init_value(t_map *s)
{
	init_angle(s);
	mlx_get_mouse_pos(s->ptr_mlx, &s->mouse_x, &s->mouse_y);
	s->ptr_mlx = mlx_init(COLUMS, ROWS, "cub3d", true);
	if (!s->ptr_mlx)
		ft_error("Error\nmlx_init", 1, 0);
	player_pos(s);
	load_textures_c(s);
}

void	player_pos(t_map *s)
{
	int	i;
	int	j;

	i = -1;
	s->px = 0;
	s->py = 0;
	while (s->tmap->map[++i])
	{
		j = -1;
		while (s->tmap->map[i][++j])
		{
			if (s->tmap->map[i][j] == 'S' || s->tmap->map[i][j] == 'W' || \
				s->tmap->map[i][j] == 'E' || s->tmap->map[i][j] == 'N')
			{
				s->px = (j * GRID) + (GRID / 7);
				s->py = (i * GRID) + (GRID / 7);
			}
		}
	}
}
