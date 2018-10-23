/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_utilfour.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsathiad <3kiraj@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 22:57:39 by rsathiad          #+#    #+#             */
/*   Updated: 2018/10/22 13:38:12 by rsathiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*makepath(char *path, char *name)
{
	char	*tmp;
	char	*ret;

	if (path == NULL)
		return (ft_strdup(name));
	if (name == NULL)
		return (ft_strdup(path));
	tmp = ft_strjoin(path, "/");
	ret = ft_strjoin(tmp, name);
	ft_strdel(&tmp);
	return (ret);
}

void	list_reversal(t_dir **head)
{
	t_dir *next;
	t_dir *current;
	t_dir *prev;

	if ((*head)->next == NULL || head == NULL)
		return ;
	prev = NULL;
	next = NULL;
	current = *head;
	while (current != NULL)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	*head = prev;
}

char	get_file_type(unsigned short m)
{
	if (S_ISLNK(m))
		return ('l');
	else if (S_ISFIFO(m))
		return ('l');
	else if (S_ISDIR(m))
		return ('d');
	else if (S_ISREG(m))
		return ('-');
	else if (S_ISCHR(m))
		return ('c');
	else if (S_ISBLK(m))
		return ('b');
	else
		return ('-');
}

void	ft_strchopfront(char **str_ref, char cutchar)
{
	char	*str;
	int		length_to_end;
	int		i;
	char	*cutloc;

	str = *str_ref;
	if (str == NULL)
		return ;
	i = 0;
	cutloc = ft_strrchr(str, cutchar);
	while ((str + i) != cutloc)
		i++;
	length_to_end = ft_strlen(str) - (i + 1);
	free(str);
	str = ft_strsub(str, i + 1, length_to_end);
	*str_ref = str;
	return ;
}

t_dir	*timesortmerge_lex(t_dir *a, t_dir *b)
{
	t_dir *result;

	if ((ft_strcmp(a->dir, b->dir) <= 0))
	{
		result = a;
		result->next = timesortmerge(a->next, b);
	}
	else
	{
		result = b;
		result->next = timesortmerge(a, b->next);
	}
	return (result);
}
