/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/13 12:57:09 by rsibiet           #+#    #+#             */
/*   Updated: 2016/02/15 19:52:32 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*gen_pwd_cd_3(int *k, char *p)
{
	static char		*s;

	*k = 0;
	s = ft_strjoin(p, "/");
	ft_strdel(&p);
	return (s);
}

char			*gen_pwd_cd(char *c, char *p, int i, int *k)
{
	static char		*s;
	static char		**t;

	s = gen_pwd_cd_3(k, p);
	p = ft_strjoin(s, c);
	ft_strdel(&s);
	t = ft_strsplit(p, '/');
	s = ft_strdup(t[0]);
	while (t[i++] != NULL)
	{
		if (ft_strcmp(t[i - 1], ".") != 0 && ft_strcmp(t[i - 1], "..") != 0)
		{
			ft_strdel(&p);
			p = ft_strjoin(s, "/");
			ft_strdel(&s);
			s = ft_strjoin(p, t[i - 1]);
		}
		if (ft_strcmp(t[i - 1], "..") == 0)
			s = gen_pwd_cd_2(s, 0, 0);
	}
	ft_strdel(&p);
	ft_strdel_del(&t);
	return (s);
}

static void		update_env_cd_3(t_env *e, int k, char **t)
{
	while (e->env[k] != NULL && ft_strnequ("OLDPWD=", e->env[k], 7) == 0)
		k++;
	if (e->env[k] != NULL)
	{
		ft_strdel(&(e->env[k]));
		e->env[k] = ft_strjoin("OLDPWD=", t[1]);
	}
	else
	{
		ft_strdel(&(e->oldpwd));
		e->oldpwd = ft_strjoin("OLDPWD=", t[1]);
	}
}

static char		**update_env_cd_4(t_env *e, int *j, int *i, char *c)
{
	static char		**t;

	t = NULL;
	while (e->env[*j] != NULL && ft_strnequ("PWD=", e->env[*j], 4) == 0)
		(*j)++;
	t = ft_strsplit(e->env[*j], '=');
	while (c[*i] != '\0' && c[*i] == '/')
		(*i)++;
	return (t);
}

void			update_env_cd_2(t_env *e, char *c, int k, int j)
{
	static char		*s;
	static char		**t;
	int				i;

	i = 0;
	s = NULL;
	t = update_env_cd_4(e, &j, &i, c);
	if (c[i] == '\0' && k == 0)
	{
		ft_strdel(&(e->env[j]));
		e->env[j] = ft_strdup("PWD=/");
	}
	else if (c[0] == '/')
	{
		ft_strdel(&(e->env[j]));
		e->env[j] = ft_strdup("PWD=/");
		s = gen_pwd_cd(c, e->env[j], 1, &k);
		e->env[j] = ft_strdup(s);
		ft_strdel(&s);
	}
	else
		end_update_cd_2(c, e, &k, j);
	update_env_cd_3(e, k, t);
}
