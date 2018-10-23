/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsathiad <3kiraj@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 22:10:47 by rsathiad          #+#    #+#             */
/*   Updated: 2018/10/21 13:56:16 by rsathiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include "libft/includes/libft.h"
# include "libft/includes/ft_printf.h"
# include <sys/stat.h>
# include <sys/types.h>
# include <string.h>
# include <errno.h>
# include <dirent.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>
# include <uuid/uuid.h>
# include <stdlib.h>
# include <stdio.h>

# define NOTCHILD	ft_strcmp(current->dir , ".") != 0
# define NOTPARENT	ft_strcmp(current->dir ,"..") != 0

typedef	struct		s_dir
{
	char			*dir;
	unsigned short	perm;
	int				links;
	char			*uname;
	char			*gname;
	long			size;
	long			time;
	int				blockcount;
	char			*path;
	int				maj;
	int				min;
	struct s_dir	*next;
}					t_dir;

char				*getdirpath(char *arg);
char				*pathname_append(char *nonflags);
char				*make_dir_path_for_recurse(char *path, char *dir);
int					dir_valid_accessible(char *dirpathref);
void				print_dirname(char *dirpathref);
void				ft_strchopfront(char **str, char cut);
char				get_file_type(unsigned short num);
int					nonflag_checker(char *arg);
unsigned char		get_flags(char **argv, int argc);
char				**get_nonflags(char **argv, int argc, int *check);
char				*makepath(char *dir, char *path);
char				*modeconvert(unsigned short num);
t_dir				*create_file_list(char *path);
void				parsefiles(unsigned char flag, t_dir **file_list);
t_dir				*parsedir(unsigned char flag, t_dir **list);
void				list_function(char flag, t_dir **filelist, char *localdir,
		int check);
void				list_directory(char flag, t_dir **file_list, char *path,
		int check);
void				process_nonflag_args(char **nonflag, char flag, int check);
int					process_files_in_args(char **nonflags, char flag,
		int check);
void				process_dir_in_args(char **arg, char flag, int check);
t_dir				*pushnew_filenode(char *d_name, char *dir,
		struct stat file_stat, t_dir*head);
int					print_blocks(t_dir **ptr);
void				delete_dot (t_dir **dirlist);
void				list_reversal(t_dir **head);
void				display_long_form_files(char flag, t_dir **dirlist);
void				display_long_form(char flag, t_dir **dirlist,
		int blockcount);
void				display_short_form(char flag, t_dir **dirlist);
void				frontbacksplit(t_dir *head, t_dir **front, t_dir **back);
void				mergesort_name(t_dir **list);
void				mergesort_time(t_dir **list);
t_dir				*timesortmerge_lex(t_dir *a, t_dir *b);
t_dir				*timesortmerge(t_dir *a, t_dir *b);
t_dir				*namesortmerge(t_dir *a, t_dir *b);
void				free_clist(char **list);
void				free_tlist(t_dir **ptr_linkedlist);

#endif
