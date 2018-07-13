/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_av_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 15:11:10 by rsibiet           #+#    #+#             */
/*   Updated: 2016/02/15 19:55:18 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		split_semicolon_3(char *line, char **c, int i, int j)
{
	int		tp;
	int		len;

	tp = 1;
	len = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '"')
			tp *= -1;
		if (line[i] == ';' && tp == 1)
		{
			c[j][len] = '\0';
			len = -1;
			j++;
		}
		if (len >= 0)
			c[j][len] = line[i];
		len++;
		i++;
	}
	c[j][len] = '\0';
}

static void		split_semicolon_2(char *line, char **c, int i, int j)
{
	int		tp;
	int		len;

	tp = 1;
	len = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '"')
			tp *= -1;
		if (line[i] == ';' && tp == 1)
		{
			c[j] = (char *)malloc(sizeof(char) * (len + 1));
			j++;
			len = -1;
		}
		len++;
		i++;
	}
	c[j] = (char *)malloc(sizeof(char) * (len + 1));
	c[j + 1] = NULL;
}

char			**split_semicolon(char *line, int i, int j, int tp)
{
	static char		**c;

	c = NULL;
	while (line[i] != '\0')
	{
		if (line[i] == '"')
			tp *= -1;
		if (line[i] == ';' && tp == 1)
			j++;
		i++;
	}
	c = (char **)malloc(sizeof(char *) * (j + 1));
	split_semicolon_2(line, c, 0, 0);
	split_semicolon_3(line, c, 0, 0);
	return (c);
}

char			**ft_split_quote(char *line, int k)
{
	static char		*tp;
	t_av			av;

	av.len = 0;
	av.i = 0;
	tp = NULL;
	av.c = NULL;
	if (line == NULL)
		return (NULL);
	k = ft_strlen(line);
	k--;
	while (k >= 0 && (line[k] == ' ' || line[k] == '\t'))
		k--;
	tp = ft_strsub(line, 0, k + 1);
	ft_strdel(&line);
	line = ft_strdup(tp);
	ft_strdel(&tp);
	k = 0;
	if (remove_multiples_quotes(line, 0, 0, 0) == 0)
		mini_ft_split_quote(line, 1, &k, &av);
	else
		ft_putendl_fd("Unmatched \".", 2);
	av.c = sft_split_quote(av.c, 0, 0, 0);
	return (av.c);
}

void			mini_malloc_av(t_av *av)
{
	(av->len)++;
	(av->i)++;
}
