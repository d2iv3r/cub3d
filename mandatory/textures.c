/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarhat <efarhat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 13:23:41 by efarhat           #+#    #+#             */
/*   Updated: 2023/09/24 11:05:40 by efarhat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	get_color(unsigned int r, unsigned int g,
	unsigned int b, unsigned int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	get_rgb(t_map *s, int p, int yt, int xt)
{
	int	r;
	int	g;
	int	b;
	int	a;

	r = s->tex[p]->pixels[(4 * xt * s->tex[p]->width) + (4 * yt)];
	g = s->tex[p]->pixels[(4 * xt * s->tex[p]->width) + (4 * yt + 1)];
	b = s->tex[p]->pixels[(4 * xt * s->tex[p]->width) + (4 * yt + 2)];
	a = s->tex[p]->pixels[(4 * xt * s->tex[p]->width) + (4 * yt + 3)];
	s->color = get_color(r, g, b, a);
}

void	load_textures_c(t_map *s)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (!ft_strcmp(s->tmap->elem[i].id, "NO"))
			s->tex[N] = mlx_load_png(s->tmap->elem[i].info);
		else if (!ft_strcmp(s->tmap->elem[i].id, "EA"))
			s->tex[E] = mlx_load_png(s->tmap->elem[i].info);
		else if (!ft_strcmp(s->tmap->elem[i].id, "SO"))
			s->tex[S] = mlx_load_png(s->tmap->elem[i].info);
		else if (!ft_strcmp(s->tmap->elem[i].id, "WE"))
			s->tex[W] = mlx_load_png(s->tmap->elem[i].info);
		else if (!ft_strcmp(s->tmap->elem[i].id, "F"))
			s->fc = get_color(s->tmap->elem[i].color[0],
					s->tmap->elem[i].color[1], s->tmap->elem[i].color[2], 255);
		else if (!ft_strcmp(s->tmap->elem[i].id, "C"))
			s->cc = get_color(s->tmap->elem[i].color[0],
					s->tmap->elem[i].color[1], s->tmap->elem[i].color[2], 255);
		i++;
	}
	if (!s->tex[N] || !s->tex[E] || !s->tex[S] || !s->tex[W])
		ft_error("Error:\nLoading the textures!", 1, 0);
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
	int		y;
	int		xt;
	int		yt;
	long	i;
	int		p;

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
			get_rgb(s, p, xt, yt);
			if (i + y >= 0 && i + y < ROWS && x >= 0 && x <= COLUMS)
				mlx_put_pixel(s->img, x, y + i, s->color);
		}
		i++;
	}
}
