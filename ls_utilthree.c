/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_utilthree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsathiad <3kiraj@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 22:46:55 by rsathiad          #+#    #+#             */
/*   Updated: 2018/10/21 22:56:07 by rsathiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*make_dir_path_for_recurse(char *path, char *dir)
{
	if (path[ft_strlen(path) - 1] == '/')
		return (ft_strjoin(path, dir));
	else
		return (makepath(path, dir));
}

int		dir_valid_accessible(char *dirpath)
{
	struct stat file_stat;
	char		*dup;

	dup = ft_strdup(dirpath);
	if (stat(dup, &file_stat) == -1)
	{
		if (ft_strrchr(dup, '/') != NULL)
		{
			ft_strchopfront(&dup, '/');
			ft_printf("ft_ls: %s: %s\n", dup, strerror(errno));
		}
		else
			ft_printf("ft_ls: %s: %s\n", dup, strerror(errno));
		free(dup);
		return (0);
	}
	free(dup);
	return (1);
}

void	print_dirname(char *dirpath)
{
	struct stat	file_stat;
	char		*dup;

	dup = ft_strdup(dirpath);
	if (ft_strrchr(dup, '/') != NULL)
	{
		ft_strchopfront(&dup, '/');
		ft_printf("ft_ls: %s: %s\n", dup, strerror(errno));
	}
	else
		ft_printf("ft_ls: %s: %s\n", dup, strerror(errno));
	free(dup);
	return ;
}

void	parsefiles(unsigned char flag, t_dir **file_list)
{
	t_dir *ref;

	ref = *file_list;
	if (!(flag & 2))
		delete_dot(&ref);
	if (flag & 4)
		mergesort_time(&ref);
	else
		mergesort_name(&ref);
	if (flag & 8)
		list_reversal(&ref);
	if (flag & 1)
		display_long_form_files(flag, &ref);
	else
		display_short_form(flag, &ref);
	*file_list = ref;
	return ;
}

char	*pathname_append(char *nonflags)
{
	char	*filename;
	char	*path;

	filename = nonflags;
	if (*filename != '/')
		path = ft_strjoin("./", filename);
	else
		path = ft_strjoin("/", filename);
	return (path);
}
