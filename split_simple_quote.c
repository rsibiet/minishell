/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_simple_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 17:57:12 by rsibiet           #+#    #+#             */
/*   Updated: 2016/02/15 19:48:28 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		s_split_3(char **c, int i, int j, int tp)
{
	static char		*s;

	s = NULL;
	if (tp > 0)
	{
		s = ft_strdup(c[j]);
		ft_strdel(&c[j]);
		c[j] = (char *)malloc(sizeof(char) * (i - tp + 1));
		i = 0;
		tp = 0;
		while (s[i] != '\0')
		{
			if (c[j][i] != 39)
			{
				c[j][tp] = s[i];
				tp++;
			}
			i++;
		}
		c[j][tp] = '\0';
		ft_strdel(&s);
	}
}

static void		s_split_2(char **c, int i, int j, int tp)
{
	while (c[j] != NULL && tp == 0)
	{
		while (c[j][i] != '\0')
		{
			if (c[j][i] == 39)
				tp++;
			i++;
		}
		s_split_3(c, i, j, tp);
		tp = 0;
		i = 0;
		j++;
	}
}

char			**sft_split_quote(char **c, int i, int j, int tp)
{
	while (c[j] != NULL && tp == 0)
	{
		while (c[j][i] != '\0')
		{
			if (c[j][i] == 39)
				tp++;
			i++;
		}
		if (tp % 2 == 1)
			ft_putendl_fd("Unmatched \".", 2);
		else
		{
			tp = 0;
			i = 0;
			j++;
		}
	}
	if (c[j] == NULL)
		s_split_2(c, 0, 0, 0);
	return (c);
}
