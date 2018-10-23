/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_flag.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsathiad <3kiraj@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 22:59:45 by rsathiad          #+#    #+#             */
/*   Updated: 2018/10/21 23:04:13 by rsathiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			exit_invalid_flag(char c)
{
	ft_printf("ft_ls: illegal option -- %c\n", c);
	ft_printf("usage: ls [-Ralrt] [file ...]");
	ft_printf("\n");
	exit(EXIT_FAILURE);
}

unsigned char	get_flags(char **argv, int argc)
{
	unsigned char	flag;
	int				i;

	flag = 0;
	i = 0;
	if ((--argc) >= 1)
	{
		argv++;
		while (*argv != NULL && ((*argv)[i++] == '-' && (**argv) + 1))
		{
			while ((*argv)[i] != '\0')
			{
				if ((*argv)[i] == 'l')
					flag = ft_setbit(flag, 0);
				else if ((*argv)[i] == 'a')
					flag = ft_setbit(flag, 1);
				else if ((*argv)[i] == 't')
					flag = ft_setbit(flag, 2);
				else if ((*argv)[i] == 'r')
					flag = ft_setbit(flag, 3);
				else if ((*argv)[i] == 'R')
					flag = ft_setbit(flag, 4);
				else
					exit_invalid_flag((*argv)[i]);
				i++;
			}
			i = 0;
			argv++;
		}
	}
	return (flag);
}

char			**get_nonflags(char **argv, int argc, int *check)
{
	char	**array;
	char	**ret;

	array = (char **)malloc(sizeof(char *) * argc);
	ret = array;
	argv++;
	while (*argv != NULL && ((**argv) == '-' && ft_strlen(*argv) > 1))
		argv++;
	while (*argv != NULL)
	{
		if (nonflag_checker(*argv))
		{
			*array = ft_strdup(*argv);
			array++;
		}
		else
			*check = 1;

		argv++;
	}
	*array = NULL;
	return (ret);
}

int				nonflag_checker(char *arg)
{
	struct stat file_stat;

	if (lstat(arg, &file_stat) == -1)
	{
		ft_printf("ft_ls: %s: %s\n", arg, strerror(errno));
		return (0);
	}
	return (1);
}
