/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 13:06:52 by rsibiet           #+#    #+#             */
/*   Updated: 2015/11/29 15:35:21 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcat(char *s1, const char *s2)
{
	int	i1;
	int	i2;

	i1 = 0;
	i2 = 0;
	while (s1[i1] != '\0')
		i1++;
	while (s2[i2] != '\0')
	{
		s1[i1] = s2[i2];
		i1++;
		i2++;
	}
	s1[i1] = '\0';
	return (s1);
}
