/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_raycasting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:22:34 by mel-harc          #+#    #+#             */
/*   Updated: 2023/09/17 16:43:48 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_steps_h(t_ray *r, t_map *s, float steps_x, float steps_y)
{
	while (1)
	{
		r->cxh += steps_x;
		r->cyh += steps_y;
		if (is_wall(s, r->cyh, r->cxh))
			break ;
	}
}

void	check_steps_v(t_ray *r, t_map *s, float steps_x, float steps_y)
{
	while (1)
	{
		r->cxv += steps_x;
		r->cyv += steps_y;
		if (is_wall(s, r->cyv, r->cxv))
			break ;
	}
}
