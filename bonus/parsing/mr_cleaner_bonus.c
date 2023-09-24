/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mr_cleaner_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-harc <mel-harc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 14:40:15 by mel-harc          #+#    #+#             */
/*   Updated: 2023/09/24 14:40:18 by mel-harc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

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
