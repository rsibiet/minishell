/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_switch_fl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 15:38:43 by rsibiet           #+#    #+#             */
/*   Updated: 2016/01/27 15:38:45 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_switch_fl(float *a, float *b)
{
	float	tp;

	tp = *a;
	*a = *b;
	*b = tp;
}
