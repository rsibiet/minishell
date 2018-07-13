/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command_minishell_2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/13 12:57:00 by rsibiet           #+#    #+#             */
/*   Updated: 2016/02/16 10:55:33 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		ft_cd_4(t_env *e, char **c, int j)
{
	if (c[2] != NULL && j != -1)
		error_chdir_2(c[1]);
	else if (chdir(c[1]) == -1 && j != -1)
		error_chdir(c[1], 0);
	else if (j != -1)
		update_env_cd(e, c, 0, 1);
}

static void		ft_cd_3(t_env *e, char **c, int i, int j)
{
	static char		*tp;

	tp = NULL;
	if (i == 2 && c[2] != NULL && j != -1)
	{
		if (c[3] == NULL)
		{
			tp = opt_cd(c[2], c[1]);
			if (tp != NULL)
			{
				ft_strdel(&c[2]);
				c[2] = ft_strdup(tp);
				ft_strdel(&tp);
				if (chdir(c[2]) == -1)
					error_chdir(c[2], 0);
				else
					update_env_cd(e, c, 0, 1);
			}
		}
		else
			error_chdir(c[3], 0);
	}
	else
		ft_cd_4(e, c, j);
}

static void		ft_cd_2(t_env *e, char **c, int i, int j)
{
	int			len;

	if (ft_strcmp(c[1], "-") == 0 && c[2] == NULL)
	{
		len = ft_strlen(e->oldpwd);
		ft_strdel(&c[1]);
		c[1] = ft_strsub(e->oldpwd, 7, len - 7);
	}
	else if (ft_strcmp(c[1], "-") == 0 && c[2] != NULL)
	{
		ft_strdel(&c[1]);
		c[1] = ft_strdup(c[2]);
		j = -1;
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putendl_fd(c[1], 2);
	}
	ft_cd_3(e, c, i, j);
}

static void		ft_cd(t_env *e, char **c, int i, int j)
{
	static char		**u;

	u = NULL;
	while (e->env != NULL && e->env[j] != NULL &&
		ft_strnequ("PWD=", e->env[j], 4) == 0)
		j++;
	if (e->env != NULL && e->env[j] == NULL)
	{
		u = ft_strjoin_join(e->env, e->pwd);
		ft_strdel_del(&(e->env));
		e->env = ft_strdup_dup(u);
		ft_strdel_del(&u);
	}
	if (c[1] != NULL && (ft_strcmp(c[1], "-L") == 0 ||
				ft_strcmp(c[1], "-P") == 0))
		i = 2;
	if (e->env != NULL && (c[i] == NULL || (c[i][0] == '~'
		&& (c[i][1] == '\0' || c[i][1] == '/'))))
		ft_cd_home(e, 0, 1, c);
	else if (e->env == NULL)
		ft_putendl_fd("cd: HOME not set", 2);
	else
		ft_cd_2(e, c, i, j);
}

void			complete_av(t_env *e, char *line, int i)
{
	static char	**c;

	c = ft_split_quote(line, 0);
	if (c != NULL)
	{
		if (e->name != NULL)
			ft_strdel(&(e->name));
		e->name = ft_strdup(c[0]);
		if (ft_strcmp(c[0], "echo") == 0 && c[1] != NULL)
			control_av_echo(line, c, 0, 0);
		define_av(e, c, 0, 0);
		while (c[i] != NULL)
			i++;
		if (ft_strcmp(c[0], "cd") == 0)
			ft_cd(e, c, 1, 0);
		else if (ft_strcmp(c[0], "env") == 0 || (ft_strcmp(c[0], "setenv") == 0
					&& c[1] == NULL))
			ft_env(e, c, 0);
		else if (ft_strcmp(c[0], "setenv") == 0 ||
				ft_strcmp(c[0], "unsetenv") == 0)
			control_var_setenv(e, c, 0, 0);
		if (e->av != NULL && e->av[1] != NULL)
			complete_av_2(e, 0);
	}
}
