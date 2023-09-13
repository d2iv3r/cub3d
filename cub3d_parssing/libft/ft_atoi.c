/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarhat <efarhat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:03:32 by efarhat           #+#    #+#             */
/*   Updated: 2023/09/11 17:36:37 by efarhat          ###   ########.fr       */
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
	while ((str[i] != '\0') && ((str[i] == 32) || (str[i] > 8 && str[i] < 14)))
		i++;
	if (str[i] == '-' || str[i++] == '+')
	{
		if (str[i] == '-')
			s = -1;
	}
	while (str[i++] != '\0')
	{
		if (!ft_isdigit(str[i]))
			ft_error("Error:\n colors must be a number!", 1, 0);
		nb = nb * 10 + (str[i] - 48);
		if (nb >= 9223372036854775807 && s == 1)
			return (-1);
		if (nb > 9223372036854775807 && s == -1)
			return (0);
	}
	return (nb * s);
}
