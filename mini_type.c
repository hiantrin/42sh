/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 23:53:03 by hiantrin          #+#    #+#             */
/*   Updated: 2020/03/01 17:42:44 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	mini_type(char **argv, t_pi pi, t_list *list, int *status)
{
	int		i;

	i = 0;
	while (argv[++i])
	{
		if (mini_type1(argv[i], pi) == 1)
		{
		}
		else if (mini_type1v2(argv[i], pi) == 1)
		{
		}
		else if (mini_type2(argv[i], pi) == 1)
		{
		}
		else if (mini_type3(argv[i], list, pi, &status[0]) == 1)
		{
		}
		else
		{
			ft_putstr_fd("42sh: type: ", pi.pipe[2][1]);
			ft_putstr_fd(argv[i], pi.pipe[2][1]);
			ft_putendl_fd(": not found", pi.pipe[2][1]);
			status[0] = 0;
		}
	}
}

int		mini_type1(char *str, t_pi pi)
{
	if (ft_strcmp(str, ".") == 0 || ft_strcmp(str, "..") == 0 ||
			ft_strcmp(str, "alias") == 0 || ft_strcmp(str, "bg") == 0 ||
			ft_strcmp(str, "break") == 0 || ft_strcmp(str, "builtin") == 0 ||
			ft_strcmp(str, "caller") == 0 || ft_strcmp(str, "cd") == 0 ||
			ft_strcmp(str, "command") == 0 || ft_strcmp(str, "compgen") == 0 ||
			ft_strcmp(str, "complete") == 0 || ft_strcmp(str, "continue") == 0
			|| ft_strcmp(str, "declare") == 0 || ft_strcmp(str, "dirs") == 0 ||
			ft_strcmp(str, "disown") == 0 || ft_strcmp(str, "echo") == 0 ||
			ft_strcmp(str, "[") == 0 || ft_strcmp(str, "bind") == 0 ||
			ft_strcmp(str, "enable") == 0 || ft_strcmp(str, "eval") == 0 ||
			ft_strcmp(str, "exec") == 0 || ft_strcmp(str, "exit") == 0 ||
			ft_strcmp(str, "export") == 0 || ft_strcmp(str, "false") == 0 ||
			ft_strcmp(str, "fc") == 0 || ft_strcmp(str, "fg") == 0 ||
			ft_strcmp(str, "getopts") == 0 || ft_strcmp(str, "hash") == 0 ||
			ft_strcmp(str, "help") == 0 || ft_strcmp(str, "history") == 0 ||
			ft_strcmp(str, "jobs") == 0 || ft_strcmp(str, "kill") == 0 ||
			ft_strcmp(str, "let") == 0 || ft_strcmp(str, "local") == 0 ||
			ft_strcmp(str, "logout") == 0 || ft_strcmp(str, "popd") == 0)
	{
		ft_putstr_fd(str, pi.pipe[1][1]);
		ft_putendl_fd(" is a shell builtin", pi.pipe[1][1]);
		return (1);
	}
	return (0);
}

int		mini_type1v2(char *str, t_pi pi)
{
	if (ft_strcmp(str, "printf") == 0 || ft_strcmp(str, "pushd") == 0 ||
			ft_strcmp(str, "pwd") == 0 || ft_strcmp(str, "read") == 0 ||
			ft_strcmp(str, "readonly") == 0 || ft_strcmp(str, "return") == 0 ||
			ft_strcmp(str, "set") == 0 || ft_strcmp(str, "shift") == 0 ||
			ft_strcmp(str, "shopt") == 0 || ft_strcmp(str, "source") == 0 ||
			ft_strcmp(str, "suspend") == 0 || ft_strcmp(str, "test") == 0 ||
			ft_strcmp(str, "times") == 0 || ft_strcmp(str, "trap") == 0 ||
			ft_strcmp(str, "true") == 0 || ft_strcmp(str, "type") == 0 ||
			ft_strcmp(str, "typeset") == 0 || ft_strcmp(str, "ulimit") == 0 ||
			ft_strcmp(str, "umask") == 0 || ft_strcmp(str, "unalias") == 0 ||
			ft_strcmp(str, "unset") == 0 || ft_strcmp(str, "wait") == 0)
	{
		ft_putstr_fd(str, pi.pipe[1][1]);
		ft_putendl_fd(" is a shell builtin", pi.pipe[1][1]);
		return (1);
	}
	return (0);
}

int		mini_type2(char *str, t_pi pi)
{
	if (ft_strcmp(str, "if") == 0 || ft_strcmp(str, "then") == 0 ||
			ft_strcmp(str, "else") == 0 || ft_strcmp(str, "elif") == 0 ||
			ft_strcmp(str, "fi") == 0 || ft_strcmp(str, "case") == 0 ||
			ft_strcmp(str, "esac") == 0 || ft_strcmp(str, "for") == 0 ||
			ft_strcmp(str, "select") == 0 || ft_strcmp(str, "while") == 0 ||
			ft_strcmp(str, "until") == 0 || ft_strcmp(str, "do") == 0 ||
			ft_strcmp(str, "done") == 0 || ft_strcmp(str, "in") == 0 ||
			ft_strcmp(str, "function") == 0 || ft_strcmp(str, "time") == 0 ||
			ft_strcmp(str, "}") == 0 || ft_strcmp(str, "{") == 0 ||
			ft_strcmp(str, "!") == 0 || ft_strcmp(str, "[[") == 0 ||
			ft_strcmp(str, "]]") == 0)
	{
		ft_putstr_fd(str, pi.pipe[1][1]);
		ft_putendl_fd(" is a shell keyword", pi.pipe[1][1]);
		return (1);
	}
	return (0);
}

int		mini_type3(char *str, t_list *list, t_pi pi, int *status)
{
	char	**tab;
	char	*path;

	tab = ft_strsplit(serach_env2(list), ':');
	path = check_if_exist(str, tab);
	free_2d(tab);
	if (path == NULL)
		return (0);
	else
	{
		ft_putstr_fd(str, pi.pipe[1][1]);
		ft_putstr_fd(" is ", pi.pipe[1][1]);
		ft_putendl_fd(path, pi.pipe[1][1]);
		free(path);
		status[0] = 0;
		return (1);
	}
	return (0);
}
