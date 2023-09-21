/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarhat <efarhat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:52:37 by efarhat           #+#    #+#             */
/*   Updated: 2023/09/21 11:09:43 by efarhat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_grid(int x, int y, t_map *p, int f)
{
	int	i;
	int	j;

	if (f == 0)
		p->mm->col = get_color(0, 0, 0, 200);
	else if (f == 1)
		p->mm->col = get_color(255, 255, 255, 200);
	else
		p->mm->col = get_color(100, 100, 100, 200);
	i = 0;
	while (i < MGRID)
	{
		j = 0;
		while (j < MGRID)
		{
			mlx_put_pixel(p->img, (x * MGRID) + j, (y * MGRID) + i,
				p->mm->col);
			j++;
		}
		i++;
	}
}

void	get_abcd(t_map *p)
{
	p->mm->a = p->mm->py - (p->mm->h / 2);
	p->mm->b = p->mm->py + (p->mm->h / 2);
	p->mm->c = p->mm->px - (p->mm->w / 2);
	p->mm->d = p->mm->px + (p->mm->w / 2);
	p->mm->a /= MGRID;
	p->mm->b /= MGRID;
	p->mm->c /= MGRID;
	p->mm->d /= MGRID;
}

int	is_in_wind(int y, int x, int h, int w)
{
	if (y >= 0 && y < h && x >= 0 && x < w)
		return (1);
	return (0);
}

void	draw_empty(t_map *p)
{
	int	y;
	int	x;

	y = 0;
	while (y < p->mm->h)
	{
		x = 0;
		while (x < p->mm->w)
		{
			mlx_put_pixel(p->img, x, y, p->mm->col);
			x++;
		}
		y++;
	}
}

void	draw_player(int x, int y, t_map *p)
{
	int		i;
	float	r;

	p->mm->col = get_color(255, 0, 0, 200);
	i = 0;
	while (i < 6)
	{
		r = 0;
		while (r < (6 * M_PI))
		{
			mlx_put_pixel(p->img, cos(r) * i + (x * MGRID) + MGRID / 2,
				sin(r) * i + (y * MGRID) + MGRID / 2, p->mm->col);
			r += M_PI / 180;
		}
		i++;
	}
}

void	draw_mmap(t_map *p)
{
	int	x;

	get_abcd(p);
	p->mm->y = 0;
	while (p->mm->y < p->mm->h / MGRID)
	{
		p->mm->x = 0;
		x = p->mm->c;
		while (p->mm->x < p->mm->w / MGRID)
		{
			if (is_in_wind(p->mm->a, x, p->mm->rw / MGRID, p->mm->clm / MGRID))
			{
				if (p->tmap->map[(int)floor(p->mm->a)][(int)floor(x)] == '1')
					draw_grid(p->mm->x, p->mm->y, p, 1);
				else
					draw_grid(p->mm->x, p->mm->y, p, 0);
				// if (p->tmap->map[(int)p->mm->a][(int)x] == p->tmap->pos)
				// 	draw_player(p->mm->x, p->mm->y, p);
				// if (p->mm->a == p->mm->py && x == p->px)
			}
			else
				draw_grid(p->mm->x, p->mm->y, p, 2);
			p->mm->x++;
			x++;
		}
		p->mm->a++;
		p->mm->y++;
	}
	draw_player((p->mm->w / 2) / MGRID, (p->mm->h / 2) / MGRID, p);
}

void	mini_map(t_map *p)
{
	p->mm = (t_mm *)malloc(sizeof(t_mm));
	if (!p->mm)
		ft_error("Error\nmalloc mm!", 1, 0);
	p->mm->h = 15 * MGRID;
	p->mm->w = 30 * MGRID;
	p->mm->img = mlx_new_image(p->ptr_mlx, p->mm->w, p->mm->h);
	if (!p->mm->img)
		ft_error("Error\nmlx_new_image mm!", 1, 0);
	p->mm->px = (p->px / GRID) * MGRID;
	p->mm->py = (p->py / GRID) * MGRID;
	p->mm->rw = (p->tmap->rows / GRID) * MGRID;
	p->mm->clm = (p->tmap->colums / GRID) * MGRID;
	// printf("px = %f\npy = %f\n", p->mm->px, p->mm->py);
	draw_mmap(p);
	// mlx_delete_image(p->ptr_mlx, p->mm->img);
	// free(p->mm);
}
