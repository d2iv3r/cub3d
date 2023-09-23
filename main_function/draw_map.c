/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 12:02:50 by mel-harc          #+#    #+#             */
/*   Updated: 2023/09/23 17:06:52 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_map(t_map *s)
{
	init_value(s);
	mlx_loop_hook(s->ptr_mlx, handler_moves, s);
	mlx_loop(s->ptr_mlx);
	mlx_delete_image(s->ptr_mlx, s->img);
	mlx_terminate(s->ptr_mlx);
}
