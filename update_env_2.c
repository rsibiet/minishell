/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/06 17:44:57 by rsibiet           #+#    #+#             */
/*   Updated: 2016/02/18 11:44:48 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		display_prompt_2(t_env *e, int i)
{
	static char		**s;

	s = NULL;
	while (e->env[i] != NULL && ft_strnequ(e->env[i], "USER=", 5) == 0)
		i++;
	if (e->env[i] != NULL && e->env[i][5] != '\0')
	{
		s = ft_strsplit(e->env[i], '=');
		ft_putstr("\x1B[32m");
		ft_putstr(s[1]);
		ft_strdel_del(&s);
	}
	ft_putchar(' ');
}

void			display_prompt(t_env *e, long sec)
{
	static char		*c;
	static char		host[80];
	static char		*tp;

	c = NULL;
	tp = NULL;
	host[79] = '\0';
	sec = time(NULL);
	if (e->env != NULL)
	{
		display_prompt_2(e, 0);
		ft_putstr("\x1B[33m");
		gethostname(host, 79);
		ft_putstr(host);
		ft_putchar(' ');
		c = ft_strdup(ctime(&sec));
		sec = ft_strlen(c);
		tp = ft_strsub(c, 4, sec - 5);
		ft_putstr("\x1B[36m");
		ft_putstr(tp);
		ft_putchar(' ');
		ft_strdel(&c);
		ft_strdel(&tp);
	}
	ft_putstr("\x1B[0m> ");
}

static void		copy_home(t_env *e, int j, int i)
{
	while (e->env != NULL && e->env[i] != NULL &&
		ft_strnequ("OLDPWD=", e->env[i], 7) == 0)
		i++;
	if ((e->env == NULL || e->env[i] == NULL)
		&& e->oldpwd == NULL && e->pwd != NULL)
		e->oldpwd = ft_strdup(e->pwd);
	else if (e->env != NULL && e->env[i] != NULL)
	{
		if (e->oldpwd != NULL)
			ft_strdel(&(e->oldpwd));
		e->oldpwd = ft_strdup(e->env[i]);
	}
	while (e->env != NULL && e->env[j] != NULL &&
		ft_strnequ("HOME=", e->env[j], 5) == 0)
		j++;
	if (e->env != NULL && e->env[j] != NULL && e->env[j][5] != '\0')
	{
		if (e->home != NULL)
			ft_strdel(&(e->home));
		e->home = ft_strdup(e->env[j]);
	}
	if (e->env == NULL)
		e->env = ft_strdup_dup(e->env2);
}

void			copy_pwd(t_env *e, int i)
{
	while (e->env != NULL && e->env[i] != NULL &&
		ft_strnequ("PWD=", e->env[i], 4) == 0)
		i++;
	if ((e->env == NULL || e->env[i] == NULL) && e->pwd == NULL)
		error_pwd(e);
	if (e->env != NULL && e->env[i] != NULL && ft_strlen(e->env[i]) == 4)
	{
		ft_strdel(&e->env[i]);
		e->env[i] = ft_strdup(e->pwd);
	}
	else if (e->env != NULL && e->env[i] != NULL)
	{
		if (e->pwd != NULL)
			ft_strdel(&(e->pwd));
		e->pwd = ft_strdup(e->env[i]);
	}
	copy_home(e, 0, 0);
}

void			go_back_cd(t_env *e, int i, int j)
{
	static char		**pw;
	static char		**op;
	static char		*tp;

	while (e->env[j] != NULL && ft_strnequ("PWD=", e->env[j], 4) == 0)
		j++;
	while (e->env[i] != NULL && ft_strnequ("OLDPWD=", e->env[i], 7) == 0)
		i++;
	pw = ft_strsplit(e->env[j], '=');
	op = ft_strsplit(e->env[i], '=');
	ft_strdel(&(e->env[j]));
	ft_strdel(&(e->env[i]));
	tp = ft_strjoin(pw[0], "=");
	e->env[j] = ft_strjoin(tp, op[1]);
	ft_strdel(&tp);
	tp = ft_strjoin(op[0], "=");
	e->env[i] = ft_strjoin(tp, pw[1]);
	ft_strdel(&tp);
	ft_strdel_del(&pw);
	ft_strdel_del(&op);
}
