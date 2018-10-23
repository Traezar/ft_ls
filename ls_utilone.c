/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_utilone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsathiad <3kiraj@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 16:23:00 by rsathiad          #+#    #+#             */
/*   Updated: 2018/10/21 16:24:08 by rsathiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		*modeconvert(unsigned short num)
{
	char	*ret;

	ret = (char *)malloc(sizeof(char) * 11);
	memset(ret, '-', 10);
	memset(ret + 10, '\0', 1);
	ret[0] = get_file_type(num);
	ret[1] = num & S_IRUSR ? 'r' : '-';
	ret[2] = num & S_IWUSR ? 'w' : '-';
	ret[3] = num & S_IXUSR ? 'x' : '-';
	ret[4] = num & S_IRGRP ? 'r' : '-';
	ret[5] = num & S_IWGRP ? 'w' : '-';
	ret[6] = num & S_IXGRP ? 'x' : '-';
	ret[7] = num & S_IROTH ? 'r' : '-';
	ret[8] = num & S_IWOTH ? 'w' : '-';
	ret[9] = num & S_IXOTH ? 'x' : '-';
	return (ret);
}

t_dir		*create_file_list(char *path)
{
	struct stat		file_stat;
	struct dirent	*pdirent;
	DIR				*pdir;
	t_dir			*node;
	char			*local;

	node = NULL;
	if (!(pdir = opendir(path)))
	{
		print_dirname(path);
		return (NULL);
	}
	while ((pdirent = readdir(pdir)))
	{
		if (path[ft_strlen(path) - 1] == '/')
			local = ft_strjoin(path, pdirent->d_name);
		else
			local = makepath(path, pdirent->d_name);
		lstat(local, &file_stat);
		node = pushnew_filenode(pdirent->d_name, path, file_stat, node);
		ft_strdel(&local);
	}
	closedir(pdir);
	return (node);
}

void		display_long_form_files(char flag, t_dir **dirlist)
{
	t_dir	*node;
	char	*perm;

	node = *dirlist;
	while (node != NULL)
	{
		perm = modeconvert(node->perm);
		ft_printf("%s%4d %-8s ", perm, node->links, node->uname);
		if (perm[0] == 'b' || perm[0] == 'c')
			ft_printf("%-12s %3d, %3d ", node->gname, node->maj, node->min);
		else
			ft_printf("%-12s %6lld ", node->gname, node->size);
		ft_printf("%.12s %s\n", ctime(&node->time) + 4, node->dir);
		ft_strdel(&perm);
		node = node->next;
	}
}

void		display_long_form(char flag, t_dir **dirlist, int blockcount)
{
	t_dir	*node;
	char	*perm;

	node = *dirlist;
	if (blockcount == 0 && (flag & 16))
		ft_printf("total %d\n", blockcount);
	else if (blockcount != 0)
		ft_printf("total %d\n", blockcount);
	while (node != NULL)
	{
		perm = modeconvert(node->perm);
		ft_printf("%s%4d %-8s ", perm, node->links, node->uname);
		if (perm[0] == 'b' || perm[0] == 'c')
			ft_printf("%-12s %3d, %3d ", node->gname, node->maj, node->min);
		else
			ft_printf("%-12s %6lld ", node->gname, node->size);
		if (time(NULL) - node->time <= 15778463)
			ft_printf("%.12s %s", ctime(&node->time) + 4, node->dir);
		else
			ft_printf(" %.6s %5.4s", ctime(&node->time) + 4, ctime(&node->time) + 20);
		if (perm[0] == 'l')
			ft_printf(" -> %s", readlink(node->path));
		ft_printf("\n");
		ft_strdel(&perm);
		node = node->next;
	}
	return ;
}

void		display_short_form(char flag, t_dir **dirlist)
{
	t_dir	*node;

	node = *dirlist;
	while (node != NULL)
	{
		ft_printf("%s\n", node->dir);
		node = node->next;
	}
	return ;
}
