/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_isblank.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/25 14:45:45 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2017/11/25 15:04:21 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_isblank(int c)
{
	if (c == '\t' || c == ' ')
		return (1);
	return (0);
}
