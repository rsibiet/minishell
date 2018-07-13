/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_av_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 14:17:33 by rsibiet           #+#    #+#             */
/*   Updated: 2016/02/15 14:55:28 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	complete_av_6(t_env *e, int i, int len, int j)
{
	static char	*s;

	s = NULL;
	while (e->av != NULL && e->av[i] != NULL)
	{
		if (e->av[i][j] == '"')
		{
			len = ft_strlen(e->av[i]);
			s = ft_strdup(e->av[i]);
			ft_strdel(&(e->av[i]));
			e->av[i] = ft_strsub(s, 1, len - 1);
			ft_strdel(&s);
		}
		i++;
	}
}

void	modify_env_3(t_env *e, char *c, int i, int len)
{
	static char		**t;
	static char		*tp;

	t = NULL;
	tp = NULL;
	len = ft_strlen(c);
	while (e->env != NULL && e->env[i] != NULL &&
			ft_strnequ(e->env[i], c, len) == 0)
		i++;
	if (e->env != NULL && e->env[i] != NULL && e->env[i][len] == '=')
	{
		ft_strdel(&(e->env[i]));
		e->env[i] = ft_strjoin(c, "=");
	}
	else if (e->env != NULL)
	{
		t = ft_strdup_dup(e->env);
		ft_strdel_del(&(e->env));
		tp = ft_strjoin(c, "=");
		e->env = ft_strjoin_join(t, tp);
		ft_strdel_del(&t);
		ft_strdel(&tp);
	}
}

void	complete_av_5(t_env *e, int i, int len)
{
	static char	**s;
	static char	*c;

	s = NULL;
	c = NULL;
	while (e->env != NULL && e->env[i] != NULL &&
			ft_strnequ("OLDPWD=", e->env[i], 7) == 0)
		i++;
	if (e->env == NULL || e->env[i] == NULL)
		error_pwd(e);
	else
	{
		len = ft_strlen(e->av[1]);
		s = ft_strsplit(e->env[i], '=');
		c = ft_strsub(e->av[1], 2, len - 2);
		ft_strdel(&(e->av[1]));
		if (s[1] != NULL)
			e->av[1] = ft_strjoin(s[1], c);
		else
			error_oldpwd(e);
		ft_strdel_del(&s);
		ft_strdel(&c);
	}
}

void	complete_av_4(t_env *e, int i)
{
	if (e->av[1][1] == '+')
	{
		while (e->env != NULL && e->env[i] != NULL &&
				ft_strnequ("PWD=", e->env[i], 4) == 0)
			i++;
		if (e->env == NULL || e->env[i] == NULL)
			error_pwd(e);
		else
			end_complete_av_4(e, i, 0);
	}
	else
		complete_av_5(e, 0, 0);
}

void	complete_av_3(t_env *e, int i, int len)
{
	static char	**s;
	static char	*c;

	s = NULL;
	c = NULL;
	while (e->env != NULL && e->env[i] != NULL &&
			ft_strnequ("HOME=", e->env[i], 5) == 0)
		i++;
	if (e->env == NULL || e->env[i] == NULL)
		error_pwd(e);
	else
	{
		len = ft_strlen(e->av[1]);
		s = ft_strsplit(e->env[i], '=');
		c = ft_strsub(e->av[1], 1, len - 1);
		ft_strdel(&e->av[1]);
		e->av[1] = ft_strjoin(s[1], c);
		ft_strdel_del(&s);
		ft_strdel(&c);
	}
}
