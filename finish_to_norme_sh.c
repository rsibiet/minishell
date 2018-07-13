/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_to_norme_sh.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 14:33:39 by rsibiet           #+#    #+#             */
/*   Updated: 2016/02/15 15:05:11 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	end_complete_av_4(t_env *e, int i, int len)
{
	static char		**s;
	static char		*c;

	s = NULL;
	c = NULL;
	len = ft_strlen(e->av[1]);
	s = ft_strsplit(e->env[i], '=');
	c = ft_strsub(e->av[1], 2, len - 2);
	ft_strdel(&(e->av[1]));
	if (s[1] != NULL)
		e->av[1] = ft_strjoin(s[1], c);
	else
		error_pwd_2(e);
	ft_strdel_del(&s);
	ft_strdel(&c);
}

void	error_cd_perm(char *c)
{
	ft_putstr_fd("cd: permission denied: ", 2);
	ft_putendl_fd(c, 2);
}

void	error_cd_no_file(char *c)
{
	ft_putstr_fd("cd: no such file or directory: ", 2);
	ft_putendl_fd(c, 2);
}

void	error_pwd_2(t_env *e)
{
	ft_putendl_fd("PWD empty.", 2);
	ft_strdel(&(e->name));
}

int		mini_compt_c(char **c)
{
	static int		tp;

	tp = 0;
	while (c[tp] != NULL)
		tp++;
	return (tp);
}
