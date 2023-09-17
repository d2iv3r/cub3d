/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarhat <efarhat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 17:10:11 by mel-harc          #+#    #+#             */
/*   Updated: 2023/09/17 11:49:45 by efarhat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double	_abs(double c)
{
	if (c < 0)
		c *= -1;
	return (c);
}

int	is_wall(t_map *s, float y, float x)
{
	if (x < 0)
		return (1);
	else if (x > (int)(s->weight))
		return (1);
	else if (y < 0)
		return (1);
	else if (y > (int)(s->height))
		return (1);
	else if (s->tmap->map[(int)floor (y / GRID)][(int)floor (x / GRID)] == '1')
		return (1);
	return (0);
}

void	check_wall(t_map *map, float x, float y)
{
	if (map->tmap->map[(int)(y / GRID)][(int)(x / GRID)] != '1' && \
		map->tmap->map[(int)((y + 30) / GRID)][(int)((x + 30) / GRID)] != '1')
	{
		map->px = x;
		map->py = y;
	}
}

void	normalize_angle(t_ray *r)
{
	r->ray_angle = remainder(r->ray_angle, 2 * M_PI);
	if (r->ray_angle < 0)
		r->ray_angle = (2 * M_PI) + r->ray_angle;
}
