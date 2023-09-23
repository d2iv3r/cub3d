/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_raycasting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:22:34 by mel-harc          #+#    #+#             */
/*   Updated: 2023/09/23 17:02:00 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_steps_h(t_ray *r, t_map *s, float steps_x, float steps_y)
{
	if (r->ray_angle > M_PI)
	{
		while (1)
		{
			r->cxh += steps_x;
			r->cyh += steps_y;
			if (is_wall(s, r->cyh - 1, r->cxh))
				break ;
		}
	}
	else
	{
		while (1)
		{
			r->cxh += steps_x;
			r->cyh += steps_y;
			if (is_wall(s, r->cyh, r->cxh))
				break ;
		}
	}
}

void	check_steps_v(t_ray *r, t_map *s, float steps_x, float steps_y)
{
	if (r->ray_angle > (M_PI / 2) && r->ray_angle < (1.5 * M_PI))
	{
		while (1)
		{
			r->cxv += steps_x;
			r->cyv += steps_y;
			if (is_wall(s, r->cyv, r->cxv - 1))
				break ;
		}
	}
	else
	{
		while (1)
		{
			r->cxv += steps_x;
			r->cyv += steps_y;
			if (is_wall(s, r->cyv, r->cxv))
				break ;
		}
	}
}

void	draw_c_f(t_map *s, double ws, int x, int f)
{
	int	start;
	int	end;

	if (f == 0)
	{
		start = 0;
		end = (ROWS / 2) - (ws / 2);
		while (start < end)
		{
			if (x >= 0 && x < COLUMS && start >= 0 && start < ROWS)
				mlx_put_pixel(s->img, x, start, s->cc);
			start++;
		}
	}
	else
	{
		start = (ROWS / 2) + (ws / 2);
		while (start < ROWS)
		{
			if (x >= 0 && x < COLUMS && start >= 0 && start < ROWS)
				mlx_put_pixel(s->img, x, start, s->fc);
			start++;
		}
	}
}
