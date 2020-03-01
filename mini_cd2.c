/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:57:09 by szakaria          #+#    #+#             */
/*   Updated: 2020/03/01 17:42:44 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char		*old_pwd2(char *str, char *str2)
{
	ft_memdel(&str);
	str = ft_strjoin("OLDPWD=", str2);
	return (str);
}

t_list		*old_pwd(t_list *list)
{
	t_list		*tmp;
	char		cwd[BUFF_SIZE];
	int			len;

	len = 0;
	list->first = list;
	getcwd(cwd, sizeof(cwd));
	while (list->first)
	{
		if (ft_strncmp(list->first->str, "PWD"
					, (len = mylen(list->first->str))) == 0)
		{
			tmp = list;
			while (tmp)
			{
				if (ft_strncmp(tmp->str, "OLDPWD", mylen(tmp->str)) == 0)
					tmp->str = old_pwd2(tmp->str, &list->first->str[len + 1]);
				tmp = tmp->next;
			}
			ft_memdel(&list->first->str);
			list->first->str = ft_strjoin("PWD=", cwd);
		}
		list->first = list->first->next;
	}
	return (list);
}

t_list		*add_pwd(t_list *list, t_pi pi, char *str)
{
	char		**argv;
	char		cwd[BUFF_SIZE];

	argv = (char **)malloc(sizeof(char *) * 4);
	argv[3] = NULL;
	getcwd(cwd, sizeof(cwd));
	argv[0] = ft_strdup("setenv");
	argv[1] = ft_strdup(str);
	argv[2] = ft_strdup(cwd);
	list = my_setenv(argv, list, pi);
	ft_fresh(argv);
	return (list);
}

t_list		*mini_cd2(t_list *list, t_pi pi, int *status)
{
	char	*old;

	list->first = list;
	while (list->first)
	{
		if (ft_strncmp(list->first->str, "OLDPWD"
					, mylen(list->first->str)) == 0)
		{
			if (access(&list->first->str[7], F_OK) == 0)
			{
				old = ft_strdup(&list->first->str[7]);
				list = add_pwd(list, pi, "OLDPWD");
				chdir(old);
				list = add_pwd(list, pi, "PWD");
				free(old);
				return (list);
			}
			else
				break ;
		}
		list->first = list->first->next;
	}
	help_saloupi_to_treat_cd2(list->first, pi.pipe[2][1]);
	status[0] = 0;
	return (list);
}

void		help_saloupi_to_treat_cd2(t_list *list, int error)
{
	if (list == NULL)
		ft_putendl_fd("42sh: cd: OLDPWD not set", error);
	else
		ft_putendl_fd("42sh: cd: no such file or directory", error);
}
