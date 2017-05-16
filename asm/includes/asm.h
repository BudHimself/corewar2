/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 17:13:38 by jjourdai          #+#    #+#             */
/*   Updated: 2017/03/20 16:37:10 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "libft.h"
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <errno.h>
# include <op.h>
# include <fcntl.h>
# include <sys/types.h>

# define USAGE_ERROR "Usage: ./asm [-a] <sourcefile.s>"
# define ILLEGAL_OPTION "asm: illegal option -- %c\n"
# define NOT_ALLOW " is not an allowed character [%d,%d]\n" ,line, i + 1
# define FLAG ""

typedef enum	e_enum
{
	SUCCESS = 1,
	TRUE = 1,
	FALSE = 0,
	ERROR = 0,
	SPACE = ' ',
}				t_enum;

int		apply_flag(char **flag, int *option);
void	check_option(char c, int *option);

#endif
