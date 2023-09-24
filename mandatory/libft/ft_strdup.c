/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarhat <efarhat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 12:49:03 by efarhat           #+#    #+#             */
/*   Updated: 2022/11/07 19:57:36 by efarhat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*p;

	len = ft_strlen(s1);
	p = malloc(len * sizeof(char) + 1);
	if (p == NULL)
	{
		return (NULL);
	}
	ft_memcpy(p, s1, len);
	ft_memset(p + len, '\0', 1);
	return (p);
}
