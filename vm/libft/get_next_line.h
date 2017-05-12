/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyassine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 15:54:21 by tyassine          #+#    #+#             */
/*   Updated: 2016/06/20 17:23:03 by tyassine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>

# define BUFF_SIZE 2124

typedef struct			s_lst_txt
{
	int					fd;
	char				*text;
	size_t				pos;
	struct s_lst_txt	*next;
}						t_lst_txt;

char					*ft_get_line(t_lst_txt *text);
t_lst_txt				*ft_is_in_lst(int fd, t_lst_txt *lst);
t_lst_txt				*ft_lst_new_text(char *text, int fd, t_lst_txt *lst);
int						get_next_line(int const fd, char **line);
#endif
