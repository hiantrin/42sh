/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_autocmp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommadhi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 17:53:02 by ommadhi           #+#    #+#             */
/*   Updated: 2020/12/02 20:50:50 by ommadhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_autocmp.h"

char			*ft_clean_cmd(char *cmd, int *index, char *match)
{
	int			i;
	char		*tmp;

	i = *index;
	if (i > 0 && ft_is_whitespace(cmd[i]) && cmd[i] == '$'
			&& cmd[i] == '/' && !ft_is_whitespace(cmd[i - 1]))
		i--;
	while (i > 0 && !ft_is_whitespace(cmd[i]) &&
			cmd[i] != '$' && cmd[i] != '/')
		i--;
	(i != 0) ? i++ : 0;
	tmp = ft_strdup(&cmd[*index]);
	ft_strclr(&cmd[i]);
	ft_strjoin2(&cmd, match);
	if (ft_is_dir(ft_strrchr(cmd, ' ')))
		ft_strjoin2(&cmd, "/");
	else
		ft_strjoin2(&cmd, " ");
	ft_strjoin2(&cmd, tmp);
	*index = i + ft_strlen(match) + 1;
	ft_strdel(&tmp);
	return (cmd);
}

void			ft_edit_cmd(t_dlist *matchs, int nb_of_comp,
				char **cmd, int *index)
{
	int			i;

	i = 0;
	while (matchs && matchs->next && i < nb_of_comp)
	{
		matchs = matchs->next;
		i++;
	}
	if (matchs && matchs->data)
		*cmd = ft_clean_cmd(*cmd, index, matchs->data);
}

void			ft_get_path(t_tocmp *cmd)
{
	char		*ptr;
	char		*tmp;

	if (cmd->type == 1)
	{
		cmd->path = ft_strdup("./");
		return ;
	}
	if (cmd->type == 2)
	{
		ptr = ft_strdup(cmd->tocmp);
		ft_strdel(&cmd->tocmp);
		tmp = ft_strrchr(ptr, '/');
		if (tmp)
			cmd->tocmp = ft_strdup(tmp);
		else
			cmd->tocmp = ft_strnew(1);
		ft_strclr(ft_strrchr(ptr, '/'));
		cmd->path = ft_strdup(ptr);
		ft_strdel(&ptr);
	}
}

char			*ft_cutcmd_and_gettype(char *cmd, int index, int *type)
{
	int			i;

	i = index;
	if (ft_is_whitespace(cmd[i]) && i > 0)
		i--;
	while (i > 0 && !ft_is_whitespace(cmd[i])
			&& cmd[i] != '/' && cmd[i] != '$')
		i--;
	if (ft_is_whitespace(cmd[i]))
		*type = 1;
	if (cmd[i] == '/')
	{
		*type = 2;
		i = index;
		while (!ft_is_whitespace(cmd[i]) && i > 0)
			i--;
		return (ft_strcut(cmd, i + 1, index));
	}
	if (cmd[i] == '$')
		*type = 3;
	if (i == 0)
		*type = 4;
	i > 0 ? i++ : 0;
	return (ft_strcut(cmd, i, index));
}

void			init_autocmp(char **cmd, int *index)
{
	t_tocmp		cmp;
	t_dlist		*matchs;
	int			nb_of_comp;

	matchs = NULL;
	cmp.fullcmd = ft_strdup(*cmd);
	cmp.tocmp = ft_cutcmd_and_gettype(*cmd, *index, &cmp.type);
	ft_get_path(&cmp);
	if (cmp.type == 4)
		ft_search_for_bin(cmp, &matchs);
	if (cmp.type == 1 || cmp.type == 2)
		ft_search_in_dirs(cmp, &matchs);
	if (cmp.type == 3)
		ft_search_in_env(cmp, &matchs);
	tputs(tgetstr("vi", NULL), 0, ft_putsfd);
	nb_of_comp = ft_read_keys_and_print_matchs(matchs);
	if (ft_count_list_nodes(matchs) > 0 && nb_of_comp != -1)
		ft_edit_cmd(matchs, nb_of_comp, cmd, index);
	tputs(tgetstr("ve", NULL), 0, ft_putsfd);
	ft_strdel(&cmp.tocmp);
	(cmp.type == 1 || cmp.type == 2) ? ft_strdel(&cmp.path) : 0;
	ft_strdel(&cmp.fullcmd);
	ft_free_matches_lst(&matchs);
}
