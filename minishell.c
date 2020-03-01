/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 02:02:20 by szakaria          #+#    #+#             */
/*   Updated: 2020/03/01 17:42:44 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char		*mypath_git(char *pwd)
{
	char			cwd[BUFF_SIZE];
	struct dirent	*sd;
	DIR				*dir;
	char			*tmp;

	getcwd(cwd, sizeof(cwd));
	dir = opendir(cwd);
	if (dir)
		while ((sd = readdir(dir)) != NULL)
			if (ft_strcmp(sd->d_name, ".git") == 0)
			{
				tmp = pwd;
				pwd = ft_strjoin(pwd, "\033[34;1mgit:(\033[0m\033[31;1mmaste");
				ft_memdel(&tmp);
				tmp = pwd;
				pwd = ft_strjoin(pwd, "r\033[34;1m)\033[0m \x1b[93m✗\033[0m ");
				ft_memdel(&tmp);
				closedir(dir);
				return (pwd);
			}
	closedir(dir);
	return (pwd);
}

char		*mypath(void)
{
	return (NULL);
}

t_list		*ft_exit(t_list *list, char **argv, t_pi *pi, t_norme2 *norme)
{
	int i;

	i = 0;
	while (argv[i])
		i++;
	if (i == 1)
	{
		free_my_pi(pi);
		free_mylist(list);
		ft_fresh(argv);
		free_2d(norme->tab);
		free_2d(norme->andand);
		free_2d(norme->oror);
		free(norme->str);
		return (NULL);
	}
	norme->status = 0;
	free(norme->str);
	ft_putendl("exit: too many arguments");
	ft_fresh(argv);
	return (list);
}

t_list		*read_trait_commande(char *commande, t_list *list, char **argv)
{
	char	*pwd;

	pwd = mypath();
	argv = NULL;
	if ((commande = ft_readline("42sh> ")) != NULL)
	{
		commande = ft_filter_quote(0, commande);
		if (commande && (search_no_espace(commande) == 0 ||
			check_if_and_and(&commande, 0) == 0))
		{
			save_historique(commande, 1);
			ft_memdel(&commande);
			return (list);
		}
		ft_memdel(&pwd);
		if (!commande || ft_strlen(commande) == 0)
		{
			ft_memdel(&commande);
			return (list);
		}
		save_historique(commande, 1);
		if ((list = ft_trait0v2(list, commande)) == NULL)
			return (NULL);
	}
	return (list);
}

int			main(int argc, char **argv, char **env)
{
	t_list		*list;
	char		*commande;

	argc = 0;
	if (!env[0])
	{
		ft_putstr(" ⛔️ \x1b[31m \x1b[1m We need The Linux ");
		ft_putendl("Environment to run this programme ! \033[0m");
		return (0);
	}
	list = stock_list(env);
	list->first = list;
	commande = ft_strnew(0);
	while (1)
	{
		if ((list = read_trait_commande(commande, list, argv)))
			continue ;
		else
			exit(0);
	}
	free_mylist(list->first);
	return (0);
}
