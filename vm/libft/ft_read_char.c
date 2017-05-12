/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyassine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/15 19:35:53 by tyassine          #+#    #+#             */
/*   Updated: 2015/12/15 20:36:32 by tyassine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

int		ft_read_char(int fd, char c)
{
	int		tmp;

	tmp = read(fd, &c, 1);
	if (tmp == 0)
		return (0);
	else if (tmp == -1)
		return (-1);
	return (1);
}
