/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recov_env_minishell.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/22 18:00:36 by rsibiet           #+#    #+#             */
/*   Updated: 2016/02/16 10:57:08 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			ft_execute(t_env *e)
{
	static char		*com;

	com = NULL;
	if (e->av[0][0] == '/')
	{
		if (execve(e->name, e->av, e->env) == -1)
			error_command_not_found(e->name);
	}
	else
	{
		update_path(e, 0);
		if (ft_strnequ(e->name, "./", 2) == 0)
		{
			if ((com = ft_find_command(e, 0, NULL)) == NULL)
				error_command_not_found(e->name);
		}
		else
			com = ft_strdup(e->name);
		execve(com, e->av, e->env);
	}
	if (com != NULL)
		ft_strdel(&com);
	exit(0);
}

static void		read_path(t_env *e, int i)
{
	static char		**s;
	static char		*t;

	s = NULL;
	t = NULL;
	while (e->env[i] != NULL && ft_strnequ("PATH=", e->env[i], 5) == 0)
		i++;
	if (e->env[i] == NULL)
	{
		s = ft_strsplit("PATH=/usr/bin:/bin:/usr/sbin:/sbin", '=');
		t = ft_strdup(s[1]);
		ft_strdel(&s[1]);
		s[1] = ft_strjoin(t, "/usr/local/bin:/usr/local/munki");
		ft_strdel(&t);
	}
	else
		s = ft_strsplit(e->env[i], '=');
	if (s[1][0] == '\0')
	{
		ft_putendl_fd("PATH empty.", 2);
		exit(0);
	}
	e->path = ft_strsplit(s[1], ':');
	ft_strdel_del(&s);
}

void			sig_handler(int signo)
{
	if (signo == SIGINT)
		ft_putchar('\n');
}

static void		split_line(t_env *e, int i, char *line)
{
	static char		**c;
	pid_t			pid;

	pid = 0;
	c = NULL;
	display_prompt(e, 0);
	get_next_line(0, &line);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] != '\0')
	{
		i = 0;
		c = split_semicolon(line, 0, 1, 1);
		while (c[i] != NULL)
		{
			if (c[i][0] != '\0')
				signal(SIGINT, sig_handler);
			if (c[i][0] != '\0')
				fork_loop(e, pid, c[i]);
			i++;
		}
		free(c);
		c = NULL;
	}
	ft_strdel(&line);
}

int				main(int ac, char **av, char **envp)
{
	t_env	e;
	char	*line;

	e.env = NULL;
	e.env2 = NULL;
	e.name = NULL;
	e.av = NULL;
	e.pwd = NULL;
	e.oldpwd = NULL;
	e.home = NULL;
	line = NULL;
	e.status = 0;
	if (ac != 1 || av == NULL)
	{
		ft_putendl_fd("to many argument. Minishell need no argument.", 2);
		return (0);
	}
	copy_env(envp, &e, 10);
	read_path(&e, 0);
	while (1)
	{
		copy_pwd(&e, 0);
		split_line(&e, 0, line);
	}
	return (0);
}
