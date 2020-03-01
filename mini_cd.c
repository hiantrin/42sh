/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 21:57:44 by szakaria          #+#    #+#             */
/*   Updated: 2020/03/01 17:42:44 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			ft_putstr2(char *s1, char *s2)
{
	ft_putstr(s1);
	ft_putendl(s2);
	return (0);
}

char		*serach_home(t_list *list)
{
	list->first = list;
	while (list->first)
	{
		if (ft_strncmp(list->first->str, "HOME", mylen(list->first->str)) == 0)
			return (&list->first->str[5]);
		list->first = list->first->next;
	}
	return (NULL);
}

int			test_dir(char *argv, int *status, t_pi pi)
{
	char *new;

	new = check(argv);
	change_lien(&new, argv);
	if (new == NULL)
	{
		ft_putstr_fd("42sh: cd: no such file or directory: ", pi.pipe[2][1]);
		ft_putendl_fd(argv, pi.pipe[2][1]);
		status[0] = 0;
		return (0);
	}
	else if (new[0] != 'x' && new[0] != 'd' && new[0] != 'r')
	{
		ft_putstr_fd("42sh: cd: not a directory: ", pi.pipe[2][1]);
		ft_putendl_fd(argv, pi.pipe[2][1]);
		status[0] = 0;
		free(new);
		return (0);
	}
	else if (new[0] == 'x')
		return (print_cd_error(argv, pi.pipe, &status[0], new));
	free(new);
	return (1);
}

t_list		*mini_cd(char **argv, t_list *list, t_pi pi, int *status)
{
	int			i;

	i = 1;
	while (argv[i])
		i++;
	i--;
	if (argv[1] && !argv[1][0])
		return (list);
	if (i > 1)
		mini_norme_mini_cd(pi.pipe, &status[0]);
	if (i == 1 && ft_strcmp(argv[1], "-") == 0 && pi.new == NULL)
		list = mini_cd2(list, pi, &status[0]);
	else if (i == 1 && test_dir(argv[1], &status[0], pi) == 0)
		return (list);
	else if (pi.new == NULL)
	{
		list = add_pwd(list, pi, "OLDPWD");
		if ((i == 0 || ft_strcmp(argv[1], "~") == 0)
				&& access(serach_home(list), F_OK) == 0)
			chdir(serach_home(list));
		if (access(argv[1], F_OK) == 0)
			chdir(argv[1]);
		list = add_pwd(list, pi, "PWD");
	}
	return (list);
}

void		mini_norme_mini_cd(int **pipe, int *status)
{
	ft_putendl_fd("42sh: cd: Too many arguments.", pipe[2][1]);
	status[0] = 0;
}
