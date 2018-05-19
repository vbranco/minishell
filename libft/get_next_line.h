/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.h                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/02 14:23:12 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2018/05/19 16:38:52 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <sys/types.h>
# include <sys/stat.h>
# include <sys/fcntl.h>
# include <unistd.h>
# include "libft.h"
# define BUFF_SIZE 10000

typedef struct		s_buf
{
	int				call;
	char			*tmp;
	int				indice;
	int				start;
	int				fide;
}					t_buf;

int					get_next_line(const int fd, char **line);

#endif
