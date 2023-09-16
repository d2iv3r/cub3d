/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 17:10:11 by mel-harc          #+#    #+#             */
/*   Updated: 2023/09/16 16:31:06 by mel-harc         ###   ########.fr       */
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
	else if (s->tmap->map[(int)floor (y / 80)][(int)floor (x / 80)] == '1')
		return (1);
	return (0);
}

void	check_wall(t_map *map, float x, float y)
{
	if (map->tmap->map[(int)(y / GRID)][(int)(x / GRID)] != '1' && \
		map->tmap->map[(int)((y + 4) / GRID)][(int)((x + 4) / GRID)] != '1')
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
