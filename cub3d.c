/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 11:36:33 by efarhat           #+#    #+#             */
/*   Updated: 2023/09/13 16:21:00 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char *argv[])
{
	t_pmap	*tmap;
	t_map	map;

	if (argc != 2)
		return (1);
	else
	{
		tmap = malloc(sizeof(t_pmap) * 1);
		if (!tmap)
			ft_error("Error:\n malloc tmap!", 1, 0);
		tmap->file = argv[1];
		if (!check_map(tmap))
			return (1);
		map.tmap = tmap;
		draw_map(&map);
	}
	return (0);
}
