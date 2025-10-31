/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeojeon <hyeojeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:48:48 by bohchoi           #+#    #+#             */
/*   Updated: 2024/12/04 09:07:41 by hyeojeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*s1_p;
	unsigned char	*s2_p;
	size_t			i;

	i = 0;
	s1_p = (unsigned char *)s1;
	s2_p = (unsigned char *)s2;
	while ((s1_p[i] || s2_p[i]) != '\0' && i < n)
	{
		if (s1_p[i] != s2_p[i])
			return (s1_p[i] - s2_p[i]);
		i++;
	}
	return (0);
}
