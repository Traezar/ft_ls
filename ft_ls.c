/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsathiad <3kiraj@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 18:09:05 by rsathiad          #+#    #+#             */
/*   Updated: 2018/10/21 14:29:03 by rsathiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*getdirpath(char *arg)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(arg);
	while (arg[len - i] != '/')
		i++;
	return (ft_strsub(arg, 0, len - i + 1));
}

int		process_files_in_args(char **nonflags, char flag, int check)
{
	struct stat	stats;
	t_dir		*list;
	char		*path;

	list = NULL;
	while (*nonflags != NULL)
	{
		if (nonflag_checker(*nonflags))
		{
			lstat(*nonflags, &stats);
			path = pathname_append(*nonflags);
			if (S_ISDIR(stats.st_mode) == 0)
				list = pushnew_filenode(*nonflags, path, stats, list);
			free(path);
		}
		nonflags++;
	}
	if (list != NULL)
	{
		mergesort_name(&list);
		parsefiles(flag, &list);
		free_tlist(&list);
		return (1);
	}
	return (check);
}

void	process_dir_in_args(char **nonflags, char flag, int check)
{
	struct stat	file_stat;
	t_dir		*dir_list;
	char		*filename;
	char		*path;

	dir_list = NULL;
	while (*nonflags != NULL)
	{
		if (nonflag_checker(*nonflags))
		{
			stat(*nonflags, &file_stat);
			if (S_ISDIR(file_stat.st_mode) != 0)
				dir_list = pushnew_filenode(*nonflags,
						*nonflags, file_stat, dir_list);
		}
		nonflags++;
	}
	if (dir_list != NULL)
	{
		mergesort_name(&dir_list);
		list_directory(flag, &dir_list, path, check);
		free_tlist(&dir_list);
	}
	return ;
}

void	process_nonflag_args(char **nonflag, char flag, int check)
{
	check = process_files_in_args(nonflag, flag, check);
	if (check == 1)
		ft_printf("\n");
	process_dir_in_args(nonflag, flag, check);
	return ;
}

int		main(int argc, char **argv)
{
	unsigned char	flag;
	char			**nonflag;
	t_dir			*dirlist;
	char			*path;
	int				check;

	nonflag = NULL;
	check = 0;
	flag = get_flags(argv, argc);
	nonflag = get_nonflags(argv, argc, &check);
	ft_printf("%s \n\n %d", *nonflag, check);
	if (*nonflag == NULL && check == 1)
		return (0);
	if (*nonflag == NULL && check == 0)
	{
		path = getdirpath(argv[0]);
		dirlist = create_file_list(path);
		list_function(flag, &dirlist, path, 1);
		free_tlist(&dirlist);
	}
	else
		process_nonflag_args(nonflag, flag, check);
	ft_strdel(&path);
	free_clist(nonflag);
	return (0);
}
