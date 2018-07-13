/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_av.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 12:22:34 by rsibiet           #+#    #+#             */
/*   Updated: 2016/02/15 19:55:35 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		compt_nb_av(char *line, int *j, int len, int tem)
{
	int		i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	while (line[i] != '\0')
	{
		if (line[i] == '"')
			tem *= -1;
		if (tem == 1 && (line[i] == ' ' || line[i] == '\t'))
		{
			while (line[i] == ' ' || line[i] == '\t')
				i++;
			(*j)++;
			len = 0;
		}
		else
		{
			len++;
			i++;
		}
	}
}

static void		complete_tav(t_av *av, char *line, int tem, int j)
{
	av->i = 0;
	av->len = 0;
	while (line[av->i] == ' ' || line[av->i] == '\t')
		(av->i)++;
	while (line[av->i] != '\0')
	{
		if (line[av->i] == '"')
			tem *= -1;
		if (tem == 1 && (line[av->i] == ' ' || line[av->i] == '\t'))
		{
			while (line[av->i] == ' ' || line[av->i] == '\t')
				(av->i)++;
			av->c[j][av->len] = '\0';
			j++;
			av->len = 0;
		}
		else
		{
			av->c[j][av->len] = line[av->i];
			(av->len)++;
			(av->i)++;
		}
	}
	if (av->len != 0)
		av->c[j][av->len] = '\0';
}

static void		malloc_av(t_av *av, char *line, int tem, int j)
{
	while (line[av->i] == ' ' || line[av->i] == '\t')
		(av->i)++;
	while (line[av->i] != '\0')
	{
		if (line[av->i] == '"')
			tem *= -1;
		if (tem == 1 && (line[av->i] == ' ' || line[av->i] == '\t'))
		{
			while (line[av->i] == ' ' || line[av->i] == '\t')
				(av->i)++;
			if ((av->c[j] = (char *)malloc(sizeof(char *) *
							(av->len + 1))) == NULL)
				malloc_error();
			j++;
			av->len = 0;
		}
		else
			mini_malloc_av(av);
	}
	if (av->len > 0)
	{
		if ((av->c[j] = (char *)malloc(sizeof(char *) * (av->len + 1))) == NULL)
			malloc_error();
	}
}

static void		remove_quotes(t_av *av, int i, int j)
{
	static char		**s;
	static char		*b;

	s = NULL;
	b = NULL;
	while (av->c[i] != NULL)
	{
		s = ft_strsplit(av->c[i], '"');
		ft_strdel(&(av->c[i]));
		av->c[i] = ft_strdup(s[0]);
		while (s[j] != NULL)
		{
			b = ft_strjoin(av->c[i], s[j]);
			ft_strdel(&(av->c[i]));
			av->c[i] = ft_strdup(b);
			ft_strdel(&b);
			j++;
		}
		ft_strdel_del(&s);
		j = 1;
		i++;
	}
}

void			mini_ft_split_quote(char *line, int j, int *k, t_av *av)
{
	while (line[*k] == ' ' || line[*k] == '\t' || line[*k] == '"')
		(*k)++;
	if (line[*k] != '\0')
	{
		compt_nb_av(line, &j, 0, 1);
		if ((av->c = (char **)malloc(sizeof(char *) * (j + 1))) == NULL)
			malloc_error();
		av->c[j] = NULL;
		malloc_av(av, line, 1, 0);
		complete_tav(av, line, 1, 0);
		remove_quotes(av, 0, 1);
	}
	else if (*k == 0)
		ft_putendl_fd("minishell: permission denied:", 2);
	else
		ft_putendl_fd("minishell: permission denied: ", 2);
}
