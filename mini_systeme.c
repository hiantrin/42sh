/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_systeme.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 02:04:03 by szakaria          #+#    #+#             */
/*   Updated: 2020/03/01 17:52:08 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	ft_fresh(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		ft_memdel(&tab[i++]);
	free(tab);
	tab = NULL;
}

char	*serach_env2(t_list *list)
{
	list->first = list;
	while (list->first)
	{
		if (ft_strncmp(list->first->str, "PATH", mylen(list->first->str)) == 0)
			return (&list->first->str[5]);
		list->first = list->first->next;
	}
	return (NULL);
}

char	*join_path(char *path1, char *path2)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin(path1, "/");
	tmp2 = ft_strjoin(tmp, path2);
	ft_memdel(&tmp);
	return (tmp2);
}

int		ft_joinandsearch(char *path, char *commande, t_norme norme, t_list *l)
{
	struct stat sb;
	char		*newpath;
	char		**env;
	int			pid;

	if (commande[0] == '/' || commande[0] == '.' || strcmp(commande, "..") == 0)
		return (0);
	newpath = join_path(path, commande);
	if (lstat(newpath, &sb) > -1)
	{
		pid = fork();
		if (pid == 0)
		{
			env = my_magic(l);
			help_the_systeme(norme);
			execve(newpath, norme.env, env);
		}
		ft_memdel(&newpath);
		return (1);
	}
	ft_memdel(&newpath);
	return (0);
}

int		search_commande(t_list *list, char *commande, char **argv, t_pi pi)
{
	char	**path;
	int		len;
	t_norme	norme;

	path = NULL;
	len = 0;
	if (serach_env2(list))
	{
		path = ft_strsplit(serach_env2(list), ':');
		len = 0;
		while (path[len])
		{
			norme.env = argv;
			norme.pi = pi;
			if (ft_joinandsearch(path[len++], commande, norme, list) == 1)
			{
				ft_fresh(path);
				return (1);
			}
		}
		if (path[0])
			ft_fresh(path);
	}
	return (0);
}
