/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_long_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarhat <efarhat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:57:57 by efarhat           #+#    #+#             */
/*   Updated: 2023/09/11 16:58:22 by efarhat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_long_line(char **map)
{
	int		i;
	size_t	ll;

	i = 0;
	if (!*map)
		return (0);
	ll = ft_strlen(map[i]);
	while (map[i])
	{
		if (map[i + 1] && ft_strlen(map[i + 1]) > ll)
			ll = ft_strlen(map[i + 1]);
		i++;
	}
	return (ll);
}
