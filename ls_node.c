/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_node.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsathiad <3kiraj@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 12:22:04 by rsathiad          #+#    #+#             */
/*   Updated: 2018/10/21 12:52:40 by rsathiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dir	*pushnew_filenode(char *d_name, char *path, struct stat file_stat,
		t_dir *head)
{
	t_dir *node;

	node = (t_dir *)malloc(sizeof(t_dir));
	node->dir = ft_strdup(d_name);
	node->perm = file_stat.st_mode;
	node->links = file_stat.st_nlink;
	node->uname = ft_strdup(getpwuid(file_stat.st_uid)->pw_name);
	node->gname = ft_strdup(getgrgid(file_stat.st_gid)->gr_name);
	node->size = file_stat.st_size;
	node->time = file_stat.st_mtime;
	node->blockcount = file_stat.st_blocks;
	node->path = ft_strdup(path);
	if (S_ISCHR(file_stat.st_mode) || S_ISBLK(file_stat.st_mode))
	{
		node->maj = major(file_stat.st_rdev);
		node->min = minor(file_stat.st_rdev);
	}
	else
	{
		node->maj = 0;
		node->min = 0;
	}
	node->next = head;
	return (node);
}

void	clear_four(t_dir **head)
{
	t_dir *ap;

	ap = *head;
	if (!head || !*head)
		return ;
	free(ap->dir);
	ap->dir = NULL;
	free(ap->uname);
	ap->uname = NULL;
	free(ap->gname);
	ap->gname = NULL;
	free(ap->path);
	ap->path = NULL;
	return ;
}

void	delete_dot(t_dir **head_ref)
{
	t_dir *temp;
	t_dir *prev;

	temp = *head_ref;
	while (temp != NULL && *(temp->dir) == '.')
	{
		*head_ref = temp->next;
		clear_four(&temp);
		free(temp);
		temp = *head_ref;
	}
	while (temp != NULL)
	{
		while (temp != NULL && *(temp->dir) != '.')
		{
			prev = temp;
			temp = temp->next;
		}
		if (temp == NULL)
			return ;
		prev->next = temp->next;
		clear_four(&temp);
		free(temp);
		temp = prev->next;
	}
}

void	free_clist(char **list)
{
	char *head;

	if (!list)
		return ;
	while (*list != NULL)
	{
		free(*list);
		*list = NULL;
		list++;
	}
	return ;
}

void	free_tlist(t_dir **ptr_linkedlist)
{
	t_dir *list;
	t_dir *head;

	if (ptr_linkedlist == NULL)
		return ;
	head = *ptr_linkedlist;
	while (head)
	{
		list = head;
		ft_strdel(&list->dir);
		ft_strdel(&list->uname);
		ft_strdel(&list->gname);
		ft_strdel(&list->path);
		head = head->next;
		free(list);
	}
	return ;
}
