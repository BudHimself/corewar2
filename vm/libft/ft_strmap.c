/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyassine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 22:05:55 by tyassine          #+#    #+#             */
/*   Updated: 2015/12/01 00:34:18 by tyassine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*fstr;
	int		i;
	int		j;

	i = 0;
	j = ft_strlen((char *)s) + 1;
	if (!(fstr = (char *)malloc(j * sizeof(char))))
		return (NULL);
	while (s[i] != '\0')
	{
		fstr[i] = f(s[i]);
		i++;
	}
	fstr[i] = '\0';
	return (fstr);
}
