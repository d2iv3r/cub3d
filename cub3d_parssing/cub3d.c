/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarhat <efarhat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 11:36:33 by efarhat           #+#    #+#             */
/*   Updated: 2023/09/11 16:33:54 by efarhat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char *argv[])
{
	t_map	*tmap;

	if (argc != 2)
		return (1);
	else
	{
		tmap = malloc(sizeof(t_map) * 1);
		if (!tmap)
			ft_error("Error:\n malloc tmap!", 1, 0);
		tmap->file = argv[1];
		if (!check_map(tmap))
			return (1);
		while (1)
			;
	}
	return (0);
}
