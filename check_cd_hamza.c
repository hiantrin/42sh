/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cd_hamza.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 12:23:56 by hiantrin          #+#    #+#             */
/*   Updated: 2020/03/01 17:42:44 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*check(char *str)
{
	struct stat	l;
	char		*mine;

	mine = (char *)malloc(sizeof(char) * 2);
	mine[1] = '\0';
	if (lstat(str, &l) == 0)
	{
		print_type(l.st_mode, mine);
		if (!(l.st_mode & S_IRUSR) && mine[0] == 'd')
			mine[0] = 'r';
		if (!(l.st_mode & S_IXUSR) && (mine[0] == 'd' || mine[0] == 'r'))
			mine[0] = 'x';
	}
	else if (lstat(str, &l) == -1)
	{
		free(mine);
		mine = NULL;
	}
	return (mine);
}

void	print_type(mode_t st_mode, char *perm)
{
	if ((st_mode & S_IFMT) == S_IFDIR)
		perm[0] = 'd';
	else if ((st_mode & S_IFMT) == S_IFREG)
		perm[0] = '-';
	else if ((st_mode & S_IFMT) == S_IFLNK)
		perm[0] = 'l';
	else if ((st_mode & S_IFMT) == S_IFIFO)
		perm[0] = 'p';
	else if ((st_mode & S_IFMT) == S_IFCHR)
		perm[0] = 'c';
	else if ((st_mode & S_IFMT) == S_IFBLK)
		perm[0] = 'b';
	else if ((st_mode & S_IFMT) == S_IFSOCK)
		perm[0] = 's';
}

void	change_lien(char **new, char *str)
{
	if (new[0] != NULL && new[0][0] == 'l')
	{
		if (access(str, F_OK) == 0)
		{
			new[0][0] = 'd';
			if (access(str, X_OK) == -1)
			{
				new[0][0] = 'x';
			}
		}
		else
			new[0] = NULL;
	}
}

int		print_cd_error(char *argv, int **pipe, int *status, char *new)
{
	ft_putstr_fd("42sh: cd: permission denied: ", pipe[2][1]);
	ft_putendl_fd(argv, pipe[2][1]);
	status[0] = 0;
	free(new);
	return (0);
}
