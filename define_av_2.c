/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_av_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 14:17:33 by rsibiet           #+#    #+#             */
/*   Updated: 2016/02/15 19:35:07 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				test_exit(t_env *e, int i)
{
	if (e->av[1] == NULL)
		return (0);
	else if (e->av[2] != NULL)
	{
		ft_putendl_fd("exit: Expression Syntax.", 2);
		return (1);
	}
	if (e->av[1][i] == '-')
		i++;
	while (e->av[1][i] != '\0')
	{
		if (ft_isdigit(e->av[1][i]) == 0)
		{
			if (e->av[1][i] == '-' || e->av[1][i] == '+')
				ft_putendl_fd("exit: Badly formed number.", 2);
			else
				ft_putendl_fd("exit: Expression Syntax.", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

static void		remove_multiples_quotes_2(char *line, int *i, int *len)
{
	static char		*tp;
	static char		*tp2;

	tp = NULL;
	tp2 = NULL;
	if (*i != 0 && line[*i] == '"' && line[*i - 1] == '"')
	{
		*len = ft_strlen(line);
		if (*i >= 1)
			tp = ft_strsub(line, 0, *i - 1);
		if (*i + 1 != '\0')
			tp2 = ft_strsub(line, *i + 1, *len - (*i + 1));
		ft_strdel(&line);
		if (*i >= 1)
			line = ft_strjoin(tp, tp2);
		else if (tp2 != NULL)
			line = ft_strdup(tp2);
		if (tp != NULL)
			ft_strdel(&tp);
		if (tp2 != NULL)
			ft_strdel(&tp2);
		*i = 0;
	}
}

int				remove_multiples_quotes(char *line, int i, int j, int len)
{
	while (line[i] == '"' || line[i] == ' ' || line[i] == '\t')
	{
		if (line[i] == '"')
			j++;
		i++;
	}
	if (line[i] != '\0')
	{
		i = 0;
		j = 0;
		while (line[i] != '\0')
		{
			if (line[i] == '"')
				j++;
			remove_multiples_quotes_2(line, &i, &len);
			i++;
		}
	}
	if (j % 2 == 1)
		return (1);
	return (0);
}

void			control_var_setenv(t_env *e, char **c, int i, int tp)
{
	if (ft_strcmp(c[0], "setenv") == 0 && c[1] != NULL)
	{
		if (ft_isalpha(c[1][0]) == 0)
		{
			ft_putstr_fd("setenv: Variable name must ", 2);
			ft_putendl_fd("begin with a letter.", 2);
			tp = -1;
		}
		while (tp != -1 && c[1][i] != '\0')
		{
			if (ft_isalnum(c[1][i]) == 0)
			{
				tp = -1;
				ft_putstr_fd("setenv: Variable name must contain ", 2);
				ft_putendl_fd("alphanumeric characters.", 2);
			}
			i++;
		}
	}
	if (tp == 0)
		modify_env(e, c, 0, 0);
}

void			complete_av_2(t_env *e, int i)
{
	static char	**s;

	s = NULL;
	if (ft_strcmp(e->av[1], "~") == 0)
	{
		while (e->env != NULL && e->env[i] != NULL &&
			ft_strnequ("HOME=", e->env[i], 5) == 0)
			i++;
		if (e->env == NULL || e->env[i] == NULL)
			error_pwd(e);
		else
		{
			s = ft_strsplit(e->env[i], '=');
			ft_strdel(&e->av[1]);
			e->av[1] = ft_strdup(s[1]);
			ft_strdel_del(&s);
		}
	}
	else if (e->av[1] != NULL && e->av[1][0] == '~' && e->av[1][1] == '/')
		complete_av_3(e, 0, 0);
	else if (ft_strcmp(e->name, "ls") == 0 && e->av[1] != NULL &&
		e->av[1][0] == '~' && (e->av[1][1] == '+' || e->av[1][1] == '-'))
		complete_av_4(e, 0);
	else
		complete_av_6(e, 0, 0, 0);
}
