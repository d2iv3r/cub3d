/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mr_cleaner.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarhat <efarhat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:14:33 by efarhat           #+#    #+#             */
/*   Updated: 2023/09/17 11:25:06 by efarhat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	clean_arr2d(char **arr2d)
{
	int	i;

	if (!arr2d || !*arr2d)
		return ;
	i = 0;
	while (arr2d[i])
	{
		free(arr2d[i]);
		arr2d[i] = NULL;
		i++;
	}
	free(arr2d);
	arr2d = NULL;
}

void	get_space(t_map *map)
{
	int	i;
	int	w;

	i = 0;
	w = ft_strlen(map->tmap->map[i]);
	while (map->tmap->map[i])
	{
		if (ft_strlen(map->tmap->map[i]) > (size_t)w)
			w = ft_strlen(map->tmap->map[i]);
		i++;
	}
	map->weight = w * GRID;
	map->height = i * GRID;
}
