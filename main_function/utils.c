/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 17:10:11 by mel-harc          #+#    #+#             */
/*   Updated: 2023/09/22 21:52:38 by mel-harc         ###   ########.fr       */
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

void	check_wall(t_map *map, float x, float y)
{
	int	dis;

	dis = GRID / 8;
	if (x <= 0 || x >= map->weight || y <= 0 || y >= map->height)
		return ;
	else if ((x + dis) <= 0 || (x + dis) >= map->weight || \
		 (y + dis) <= 0 || (y + dis)  >= map->height)
		return ;
	else if ((x - dis) <= 0 || (x - dis) >= map->weight || \
		(y - dis) <= 0 || (y - dis)  >= map->height)
		return ;
	else if (map->tmap->map[(int)((y + dis) / GRID)][(int)((x + dis) / GRID)] == '1')
		return ;
	else if (map->tmap->map[(int)((y - dis) / GRID)][(int)((x - dis) / GRID)] == '1')
		return ;
	else if (map->tmap->map[(int)((y) / GRID)][(int)((x - dis) / GRID)] == '1')
		return ;
	else if (map->tmap->map[(int)((y) / GRID)][(int)((x + dis) / GRID)] == '1')
		return ;
	else if (map->tmap->map[(int)((y - dis) / GRID)][(int)((x) / GRID)] == '1')
		return ;
	else if (map->tmap->map[(int)((y + dis) / GRID)][(int)((x) / GRID)] == '1')
		return ;
	else
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

void	get_space(t_map *map)
{
	int	i;
	int	w;

	i = 0;
	w = ft_strlen(map->tmap->map[i]);
	while (map->tmap->map[i])
	{
		if (ft_strlen(map->tmap->map[i]) > (size_t)w)
			w = ft_strlen(map->tmap->map[i]);
		i++;
	}
	// map->weight = w * GRID;
	// map->height = i * GRID;
}
