/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarhat <efarhat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:03:32 by efarhat           #+#    #+#             */
/*   Updated: 2023/09/21 13:02:05 by efarhat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_atoi(const char *str)
{
	int					i;
	int					s;
	unsigned long long	nb;

	i = 0;
	s = 1;
	nb = 0;
	while ((str[i] != '\0') && is_empty(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			s = -1;
	}
	while (str[i] != '\0' && ft_isdigit(str[i]))
	{
		nb = nb * 10 + (str[i] - 48);
		if (nb >= 9223372036854775807 && s == 1)
			return (-1);
		if (nb > 9223372036854775807 && s == -1)
			return (0);
		i++;
	}
	while (str[i] && is_empty(str[i]))
		i++;
	if (str[i])
		ft_error("Error\nInvalid color number\n", 1, 0);
	return ((int)nb * s);
}
