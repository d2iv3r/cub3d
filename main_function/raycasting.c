/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 09:38:32 by mel-harc          #+#    #+#             */
/*   Updated: 2023/09/13 16:34:40 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_colome(t_map *s, int i, double w_s)
{
	int start;
	int p = 0;

	start = 0;
	start = (s->height/2) - (w_s/2);
	while (p < w_s )
	{
		if ((p + start) > 0 && (p + start) < (int)s->height)
			mlx_put_pixel(s->img, i, p + start, s->color);
		p++;
	}
}

void	cast_rays(t_map *s)
{
	t_ray	r;
	int		i;
	double w_s;
	
	i = 0;
	r.ray_angle = s->ongl - (s->fov / 2);
	while (i < (int)(s->weight))
	{
		normalize_angle(&r);
		w_s = (530/first_cray(s, &r)) * 100;
		r.ray_angle += s->fov / s->weight;
		draw_colome(s, i, w_s);
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
	if (dis_h <= dis_v)
	{
		// put_rays(s, r->ray_angle, dis_h);
		dis = dis_h;
		s->color = 0x00FF00FF;
	}
	else if (dis_h > dis_v)
	{
		// put_rays(s, r->ray_angle, dis_v);
		dis = dis_v;
		s->color = 0x0000FFFF;
	}
	return (dis * cos(s->ongl - r->ray_angle)); 
}

int is_wall(t_map *s ,float y, float x)
{
	if (x < 0)
		return (1);
	else if (x > (int)(s->weight))
		return (1);
	else if (y < 0)
		return (1);
	else if (y > (int)(s->height))
		return (1);
	else if (s->tmap->map[(int)floor (y / 40)][(int)floor (x / 40)] == '1')
		return (1);
	else
		return (0);
}

void	raycating_vertical(t_map *s, t_ray *r)
{
	float	steps_x = 0;
	float	steps_y = 0;

	if (r->ray_angle >= (M_PI / 2) && r->ray_angle <= (1.5 * M_PI))
	{
		r->cxv = floor(s->px / 40) * 40 - 0.0006;
		r->cyv = s->py + (tan(r->ray_angle) * (r->cxv - s->px));
		if (is_wall(s, r->cyv, r->cxv))
			return ;
		steps_x = -40;
		steps_y = steps_x * tan(r->ray_angle);
	}
	else
	{
		r->cxv = (floor(s->px / 40) * 40) + 40;
		r->cyv = s->py + (tan(r->ray_angle) * (r->cxv - s->px));
		if (is_wall(s,r->cyv, r->cxv))
			return ;
		steps_x = 40;
		steps_y = (40 * tan(r->ray_angle));
	}
	while (1)
	{
		r->cxv += steps_x;
		r->cyv += steps_y;
		if (is_wall(s, r->cyv, r->cxv))
			break ;
	}
}

void	raycating_horizontal(t_map *s, t_ray *r)
{
	float steps_x = 0;
	float steps_y = 0;
	
	if (r->ray_angle >= 0 && r->ray_angle <= M_PI)
	{
		r->cyh = (floor(s->py / 40) * 40) + 40;
		r->cxh = s->px + ((r->cyh - s->py) / tan(r->ray_angle));
		if (is_wall(s,r->cyh, r->cxh))
			return ;
		steps_x = 40 / tan(r->ray_angle);
		steps_y = 40;
	}
	else if (r->ray_angle >= M_PI)
	{
		r->cyh = floor(s->py / 40) * 40 - 0.0006;
		r->cxh = s->px + ((r->cyh - s->py) / tan(r->ray_angle));
		if (is_wall(s,r->cyh, r->cxh))
			return ;
		steps_y = -40;
		steps_x = steps_y / tan(r->ray_angle);
	}
	while (1)
	{
		r->cxh += steps_x;
		r->cyh += steps_y;
		if (is_wall(s,r->cyh, r->cxh))
			break ;
	}
}
