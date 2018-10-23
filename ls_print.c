/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsathiad <3kiraj@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 14:58:15 by rsathiad          #+#    #+#             */
/*   Updated: 2018/10/21 15:11:09 by rsathiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		print_blocks(t_dir **list)
{
	int		count;
	t_dir	*ptr;

	if (!list || !*list)
		return (0);
	ptr = *list;
	count = 0;
	while (ptr->next)
	{
		count += ptr->blockcount;
		ptr = ptr->next;
	}
	count += ptr->blockcount;
	return (count);
}

t_dir	*parsedir(unsigned char flag, t_dir **list)
{
	t_dir	*ref;
	int		blockcount;

	ref = *list;
	if (!(flag & 2))
		delete_dot(&ref);
	blockcount = print_blocks(&ref);
	if (flag & 4)
		mergesort_time(&ref);
	else
		mergesort_name(&ref);
	if (flag & 8)
		list_reversal(&ref);
	if (flag & 1)
		display_long_form(flag, &ref, blockcount);
	else
		display_short_form(flag, &ref);
	*list = ref;
	return (ref);
}

void	list_directory(char flag, t_dir **file_list, char *path, int check)
{
	t_dir	*current;
	t_dir	*dlist;

	current = *file_list;
	while (current)
	{
		if (S_ISDIR(current->perm))
		{
			if (check == 1)
				ft_printf("%s:\n", current->path);
			check = 1;
			dlist = create_file_list(current->path);
			list_function(flag, &dlist, current->path, check);
			free_tlist(&dlist);
		}
		current = current->next;
		if (current)
			ft_printf("\n");
	}
	return ;
}

void	list_function(char flag, t_dir **filelist, char *localdir,
		int check)
{
	t_dir	*current;
	char	*dirpath;
	t_dir	*llist;

	if (*filelist == NULL)
		return ;
	if (flag & 16)
	{
		current = parsedir(flag, filelist);
		while (current)
		{
			if (S_ISDIR(current->perm) && NOTPARENT && (NOTCHILD))
			{
				dirpath = make_dir_path_for_recurse(localdir, current->dir);
				ft_printf("\n%s:\n", dirpath);
				llist = create_file_list(dirpath);
				list_function(flag, &llist, dirpath, check);
				free_tlist(&llist);
				free(dirpath);
			}
			current = current->next;
		}
	}
	else
		parsedir(flag, filelist);
}
