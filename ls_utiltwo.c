/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_utiltwo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsathiad <3kiraj@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 22:31:26 by rsathiad          #+#    #+#             */
/*   Updated: 2018/10/21 22:46:22 by rsathiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dir	*timesortmerge(t_dir *a, t_dir *b)
{
	t_dir *result;

	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if ((a->time > b->time))
	{
		result = a;
		result->next = timesortmerge(a->next, b);
	}
	else if (a->time < b->time)
	{
		result = b;
		result->next = timesortmerge(a, b->next);
	}
	else
		result = timesortmerge_lex(a, b);
	return (result);
}

t_dir	*namesortmerge(t_dir *a, t_dir *b)
{
	t_dir *result;

	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (ft_strcmp(a->dir, b->dir) <= 0)
	{
		result = a;
		result->next = namesortmerge(a->next, b);
	}
	else
	{
		result = b;
		result->next = namesortmerge(a, b->next);
	}
	return (result);
}

void	frontbacksplit(t_dir *head, t_dir **front, t_dir **back)
{
	t_dir *fast;
	t_dir *slow;

	slow = head;
	fast = head->next;
	while (fast != NULL)
	{
		fast = fast->next;
		if (fast != NULL)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*front = head;
	*back = slow->next;
	slow->next = NULL;
}

void	mergesort_time(t_dir **list)
{
	t_dir *head;
	t_dir *a;
	t_dir *b;

	head = *list;
	if (head == NULL || head->next == NULL)
		return ;
	frontbacksplit(head, &a, &b);
	mergesort_time(&a);
	mergesort_time(&b);
	*list = timesortmerge(a, b);
}

void	mergesort_name(t_dir **list)
{
	t_dir *head;
	t_dir *a;
	t_dir *b;

	head = *list;
	if (head == NULL || head->next == NULL)
		return ;
	frontbacksplit(head, &a, &b);
	mergesort_name(&a);
	mergesort_name(&b);
	*list = namesortmerge(a, b);
}
