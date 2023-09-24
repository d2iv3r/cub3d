/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 14:46:55 by mel-harc          #+#    #+#             */
/*   Updated: 2023/09/24 14:47:04 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	cast_rays(t_map *s)
{
	t_ray	r;
	int		i;
	double	ws;
	double	dis;

	i = 0;
	ws = 0;
	r.ray_angle = s->ongl - (s->fov / 2);
	while (i < COLUMS)
	{
		normalize_angle(&r);
		dis = first_cray(s, &r);
		if ((int)dis == 0)
			ws = (530 / ROWS) * 100;
		else
			ws = (530 / dis) * 100;
		draw_c_f(s, ws, i, 0);
		put_tex_colmn(s, i, ws, r);
		draw_c_f(s, ws, i, 1);
		r.ray_angle += (s->fov / COLUMS);
		i++;
	}
}

double	first_cray(t_map *s, t_ray *r)
{
	double	dis_h;
	double	dis_v;

	dis_h = -1;
	dis_v = -1;
	if (r->ray_angle != 0 && r->ray_angle != M_PI && r->ray_angle != (M_PI * 2))
	{
		raycating_horizontal(s, r);
		dis_h = sqrt(pow(r->cxh - s->px, 2) + pow(r->cyh - s->py, 2));
	}
	if (r->ray_angle != (1.5 * M_PI) && r->ray_angle != (M_PI / 2))
	{
		raycating_vertical(s, r);
		dis_v = sqrt(pow(r->cxv - s->px, 2) + pow(r->cyv - s->py, 2));
	}
	return (ray_distance(dis_h, dis_v, r) * cos(s->ongl - r->ray_angle));
}

double	ray_distance(double dis_h, double dis_v, t_ray *r)
{
	if (dis_h != -1 && dis_h <= dis_v)
	{
		r->hith = 1;
		return (dis_h);
	}
	else if (dis_v != -1 && dis_h > dis_v)
	{
		r->hith = 0;
		return (dis_v);
	}
	return (0);
}

void	raycating_vertical(t_map *s, t_ray *r)
{
	float	steps_x;
	float	steps_y;

	steps_x = 0;
	steps_y = 0;
	if (r->ray_angle > (M_PI / 2) && r->ray_angle < (1.5 * M_PI))
	{
		r->cxv = (floor(s->px / GRID) * GRID);
		r->cyv = s->py + (tan(r->ray_angle) * (r->cxv - s->px));
		if (is_wall(s, r->cyv, r->cxv - 1))
			return ;
		steps_x = -GRID;
		steps_y = steps_x * tan(r->ray_angle);
	}
	else
	{
		r->cxv = (floor(s->px / GRID) * GRID) + GRID;
		r->cyv = s->py + (tan(r->ray_angle) * (r->cxv - s->px));
		if (is_wall(s, r->cyv, r->cxv))
			return ;
		steps_x = GRID;
		steps_y = (GRID * tan(r->ray_angle));
	}
	check_steps_v(r, s, steps_x, steps_y);
}

void	raycating_horizontal(t_map *s, t_ray *r)
{
	float	steps_x;
	float	steps_y;

	steps_x = 0;
	steps_y = 0;
	if (r->ray_angle >= 0 && r->ray_angle <= M_PI)
	{
		r->cyh = (floor(s->py / GRID) * GRID) + GRID;
		r->cxh = s->px + ((r->cyh - s->py) / tan(r->ray_angle));
		if (is_wall(s, r->cyh, r->cxh))
			return ;
		steps_x = GRID / tan(r->ray_angle);
		steps_y = GRID;
	}
	else if (r->ray_angle > M_PI)
	{
		r->cyh = (floor(s->py / GRID) * GRID);
		r->cxh = s->px + ((r->cyh - s->py) / tan(r->ray_angle));
		if (is_wall(s, r->cyh - 1, r->cxh))
			return ;
		steps_y = -GRID;
		steps_x = steps_y / tan(r->ray_angle);
	}
	check_steps_h(r, s, steps_x, steps_y);
}
