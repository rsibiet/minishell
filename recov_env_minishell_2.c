/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recov_env_minishell_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 19:11:56 by rsibiet           #+#    #+#             */
/*   Updated: 2016/02/16 11:00:00 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void				create_basic_env(t_env *e, char *pwd, char host[100])
{
	e->env[0] = ft_strdup("HOSTTYPE=unknown");
	e->env[1] = ft_strdup("VENDOR=apple");
	e->env[2] = ft_strdup("OSTYPE=darwin");
	e->env[3] = ft_strdup("MACHTYPE=x86_64");
	e->env[4] = ft_strdup("SHLVL=1");
	e->env[5] = ft_strjoin("PWD=", pwd);
	e->env[6] = ft_strjoin("LOGNAME=", getlogin());
	e->env[7] = ft_strjoin("USER=", (getpwuid(getuid()))->pw_name);
	e->env[8] = ft_strjoin("GROUP=", (getgrgid(getgid()))->gr_name);
	gethostname(host, 99);
	e->env[9] = ft_strjoin("HOST=", host);
	e->env[10] = NULL;
	e->env2 = ft_strdup_dup(e->env);
	ft_strdel(&pwd);
}

void				copy_env(char **envp, t_env *e, size_t i)
{
	static char		*pwd;
	static char		host[100];

	pwd = NULL;
	host[99] = '\0';
	if (envp[0] == NULL)
	{
		if ((e->env = (char **)malloc(sizeof(char *) * 11)) == NULL)
			malloc_error();
		if ((pwd = (char *)malloc(sizeof(char) * (i + 1))) == NULL)
			malloc_error();
		while (getcwd(pwd, i) == NULL)
		{
			i *= 2;
			if ((pwd = (char *)malloc(sizeof(char) * (i + 1))) == NULL)
				malloc_error();
		}
		create_basic_env(e, pwd, host);
	}
	else
	{
		e->env = ft_strdup_dup(envp);
		e->env2 = ft_strdup_dup(envp);
	}
}

static void			exit_minishell(t_env *e)
{
	if (ft_strcmp(e->name, "exit") == 0 && test_exit(e, 0) == 0)
	{
		ft_strdel(&(e->name));
		ft_strdel_del(&(e->env));
		ft_strdel_del(&(e->env2));
		if (e->av != NULL)
			ft_strdel_del(&(e->av));
		ft_strdel_del(&(e->path));
		ft_strdel(&(e->pwd));
		ft_strdel(&(e->oldpwd));
		if (e->home != NULL)
			ft_strdel(&(e->home));
		ft_putendl("exit");
		exit(0);
	}
}

static pid_t		fork_loop_2(t_env *e, pid_t pid, int i)
{
	if (ft_strcmp(e->name, "exit") != 0 && ft_strcmp(e->name, "env") != 0
		&& ft_strcmp(e->name, "setenv") != 0 &&
		ft_strcmp(e->name, "unsetenv") != 0 &&
		ft_strcmp(e->name, "cd") != 0)
		pid = fork();
	if (pid < 0)
		error_fork();
	if (pid > 0 && ft_strcmp(e->name, "echo") == 0 && e->av[1] != NULL &&
			ft_strcmp(e->av[1], "$?") == 0)
		ft_putnbr(WEXITSTATUS(e->status));
	if (pid > 0 && ft_strcmp(e->name, "echo") == 0 && e->av[1] == NULL)
		ft_putchar('\n');
	else if (pid == 0 && ft_strcmp(e->name, "echo") == 0 &&
			ft_strcmp(e->av[1], "$?") == 0)
	{
		ft_putchar(' ');
		ft_strdel(&(e->av[1]));
		while (e->av[i + 1] != NULL)
		{
			e->av[i] = ft_strdup(e->av[i + 1]);
			ft_strdel(&(e->av[i + 1]));
			i++;
		}
	}
	return (pid);
}

void				fork_loop(t_env *e, pid_t pid, char *line)
{
	if (e->av != NULL)
		ft_strdel_del(&(e->av));
	complete_av(e, line, 0);
	if (e->name != NULL)
	{
		pid = fork_loop_2(e, pid, 1);
		if (pid == 0 && ft_strcmp(e->name, "exit") != 0 &&
			ft_strcmp(e->name, "env") != 0 &&
			ft_strcmp(e->name, "setenv") != 0 &&
			ft_strcmp(e->name, "unsetenv") != 0 &&
			ft_strcmp(e->name, "cd") != 0)
			ft_execute(e);
		if (ft_strcmp(e->name, "exit") != 0 && ft_strcmp(e->name, "env") != 0
			&& ft_strcmp(e->name, "setenv") != 0 &&
			ft_strcmp(e->name, "unsetenv") != 0 &&
			ft_strcmp(e->name, "cd") != 0)
		{
			if (e->name[0] == '.' && e->name[1] == '/')
				pid = waitpid(pid, &(e->status), WUNTRACED | WCONTINUED);
			else
				wait(0);
		}
		exit_minishell(e);
	}
}
