/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_realloc.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/15 09:36:22 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2018/05/19 13:37:51 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_realloc(char *s1, char *s2)
{
	char	*tmp;
	int		len;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	tmp = ft_strnew(len);
	if (!tmp)
		return (NULL);
	if (s1)
	{
		ft_strcpy(tmp, s1);
		ft_strcat(tmp, s2);
	}
	free(s1);
	return (tmp);
}
