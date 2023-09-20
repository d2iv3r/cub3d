/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 13:23:41 by efarhat           #+#    #+#             */
/*   Updated: 2023/09/19 18:50:27 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	get_color(unsigned int r, unsigned int g,
	unsigned int b, unsigned int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	get_pos(t_ray ray)
{
	if (ray.ray_angle >= (3 * M_PI) / 2)
	{
		if (ray.hith)
			return (N);
		return (E);
	}
	else if (ray.ray_angle >= 0 && ray.ray_angle <= M_PI / 2)
	{
		if (ray.hith)
			return (S);
		return (E);
	}
	else if (ray.ray_angle >= M_PI / 2 && ray.ray_angle <= M_PI)
	{
		if (ray.hith)
			return (S);
		return (W);
	}
	else if (ray.ray_angle >= M_PI && ray.ray_angle <= (3 * M_PI) / 2)
	{
		if (ray.hith)
			return (N);
		return (W);
	}
	return (0);
}

void	put_tex_colmn(t_map *s, int x, double w_s, t_ray ray)
{
	int	y;
	int	xt;
	int	yt;
	int	i;
	int	p;

	p = get_pos(ray);
	if (ray.hith)
		xt = fmod(ray.cxh, GRID) * (s->tex[p]->width / GRID);
	else
		xt = fmod(ray.cyv, GRID) * (s->tex[p]->width / GRID);
	y = (ROWS / 2) - (w_s / 2);
	i = 0;
	while (i < w_s)
	{
		if (y + i > 0 && i + y < ROWS)
		{
			yt = i * ((float)s->tex[p]->height / w_s);
			s->r = s->tex[p]->pixels[(4 * yt * s->tex[p]->width) + (4 * xt)];
			s->g = s->tex[p]->pixels[(4 * yt * s->tex[p]->width) + (4 * xt + 1)];
			s->b = s->tex[p]->pixels[(4 * yt * s->tex[p]->width) + (4 * xt + 2)];
			s->a = s->tex[p]->pixels[(4 * yt * s->tex[p]->width) + (4 * xt + 3)];
			s->color = get_color(s->r, s->g, s->b, s->a);
			if (i + y >= 0 && i + y <= ROWS && x > 0 && x <= COLUMS)
				mlx_put_pixel(s->img, x, y + i, s->color);
		}
		i++;
	}
}
