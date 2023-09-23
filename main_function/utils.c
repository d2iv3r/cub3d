/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 17:10:11 by mel-harc          #+#    #+#             */
/*   Updated: 2023/09/23 17:17:06 by mel-harc         ###   ########.fr       */
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
	if (x <= 0)
		return (1);
	else if (x >= s->weight)
		return (1);
	else if (y <= 0)
		return (1);
	else if (y >= s->height)
		return (1);
	else if (s->tmap->map[(int)floor (y / GRID)][(int)floor (x / GRID)] == '1')
		return (1);
	return (0);
}

void	check_wall(t_map *m, float x, float y)
{
	if (x <= 0 || x >= m->weight || y <= 0 || y >= m->height)
		return ;
	else if ((x + C) <= 0 || (x + C) >= m->weight || \
		(y + C) <= 0 || (y + C) >= m->height)
		return ;
	else if ((x - C) <= 0 || (x - C) >= m->weight || \
		(y - C) <= 0 || (y - C) >= m->height)
		return ;
	else if (m->tmap->map[(int)((y + C) / GRID)][(int)((x + C) / GRID)] == '1')
		return ;
	else if (m->tmap->map[(int)((y - C) / GRID)][(int)((x - C) / GRID)] == '1')
		return ;
	else if (m->tmap->map[(int)((y) / GRID)][(int)((x - C) / GRID)] == '1')
		return ;
	else if (m->tmap->map[(int)((y) / GRID)][(int)((x + C) / GRID)] == '1')
		return ;
	else if (m->tmap->map[(int)((y - C) / GRID)][(int)((x) / GRID)] == '1')
		return ;
	else if (m->tmap->map[(int)((y + C) / GRID)][(int)((x) / GRID)] == '1')
		return ;
	else
	{
		m->px = x;
		m->py = y;
	}
}

void	normalize_angle(t_ray *r)
{
	r->ray_angle = remainder(r->ray_angle, 2 * M_PI);
	if (r->ray_angle < 0)
		r->ray_angle = (2 * M_PI) + r->ray_angle; 
}
