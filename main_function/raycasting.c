/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarhat <efarhat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 09:38:32 by mel-harc          #+#    #+#             */
/*   Updated: 2023/09/20 11:48:51 by efarhat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	cast_rays(t_map *s)
{
	t_ray	r;
	int		i;
	double	w_s;

	i = 0;
	r.ray_angle = s->ongl - (s->fov / 2);
	load_textures_c(s);
	while (i < COLUMS)
	{
		normalize_angle(&r);
		w_s = (530 / first_cray(s, &r)) * 100;
		r.ray_angle += s->fov / COLUMS;
		put_tex_colmn(s, i, w_s, r);
		i++;
	}
}

double	first_cray(t_map *s, t_ray *r)
{
	double	dis_h;
	double	dis_v;
	double	dis;

	dis_h = 0;
	dis_v = 0;
	dis = 0;
	raycating_horizontal(s, r);
	raycating_vertical(s, r);
	dis_h = sqrt(pow(r->cxh - s->px, 2) + pow(r->cyh - s->py, 2));
	dis_v = sqrt(pow(r->cxv - s->px, 2) + pow(r->cyv - s->py, 2));
	if (dis_h < dis_v)
	{
		dis = dis_h;
		r->hith = 1;
	}
	else if (dis_h > dis_v)
	{
		dis = dis_v;
		r->hith = 0;
	}
	// else if (dis_h == dis_v)
	// {
	// 	if (s->tmap->map[(int)((r->cyv - 2) / GRID)][(int)(r->cxv / GRID)] == '1')
	// 	{
	// 		puts("a");
	// 		r->hith = 0;
	// 	}
	// 	else
	// 	{
	// 		puts("b");
	// 		r->hith = 1;
	// 	}
	// }
	return (dis * cos(s->ongl - r->ray_angle));
}

void	raycating_vertical(t_map *s, t_ray *r)
{
	float	steps_x;
	float	steps_y;

	steps_x = 0;
	steps_y = 0;
	if (r->ray_angle >= (M_PI / 2) && r->ray_angle <= (1.5 * M_PI))
	{
		r->cxv = floor(s->px / GRID) * GRID - 0.00008;
		r->cyv = s->py + (tan(r->ray_angle) * (r->cxv - s->px));
		if (is_wall(s, r->cyv, r->cxv))
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
	else if (r->ray_angle >= M_PI)
	{
		r->cyh = (floor(s->py / GRID) * GRID) - 0.00008;
		r->cxh = s->px + ((r->cyh - s->py) / tan(r->ray_angle));
		if (is_wall(s, r->cyh, r->cxh))
			return ;
		steps_y = -GRID;
		steps_x = steps_y / tan(r->ray_angle);
	}
	check_steps_h(r, s, steps_x, steps_y);
}
