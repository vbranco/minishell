/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/02 16:49:59 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2018/05/19 16:37:03 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

static void	ft_clean_static(t_buf *valeur)
{
	valeur->call = 0;
	valeur->tmp = NULL;
	valeur->indice = 0;
	valeur->start = 0;
}
/*
static char	*ft_realloc(char *s1, char *s2)
{
	char	*tmp;

	if (!s1 || !s2)
		return (NULL);
	tmp = ft_strjoin(s1, s2);
	free(s1);
	return (tmp);
}
*/
static int	ft_test(t_buf *valeur)
{
	if (valeur->indice == 0)
		valeur->start = 0;
	else
	{
		if (valeur->tmp[valeur->indice] == '\0')
			return (0);
		valeur->start = valeur->indice + 1;
		valeur->indice++;
	}
	if (valeur->tmp[valeur->indice] == '\0')
		return (0);
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	static t_buf	valeur;
	char			buf[BUFF_SIZE + 1];
	int				ret;

	if (fd < 0 || line == NULL || (read(fd, buf, 0) == -1))
		return (-1);
	(valeur.fide = 0 || valeur.fide != fd) ? ft_clean_static(&valeur) : 0;
	if (valeur.indice == 0)
	{
		valeur.tmp = ft_strnew(BUFF_SIZE);
		while ((ret = read(fd, buf, BUFF_SIZE)))
		{
			buf[ret] = '\0';
			valeur.tmp = ft_realloc(valeur.tmp, buf);
		}
	}
	if (ft_test(&valeur) == 0)
		return (0);
	while (valeur.tmp[valeur.indice] != '\n' && valeur.tmp[valeur.indice])
		valeur.indice++;
	(*line) = ft_strsub(valeur.tmp, valeur.start, (valeur.indice
				- valeur.start));
	valeur.fide = fd;
	return (1);
}
