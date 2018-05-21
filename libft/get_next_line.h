#	ifndef GET_NEXT_LINE_H
#	define GET_NEXT_LINE_H

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

#define EOF (-1)
#define BUFF_SIZE 4096

typedef	struct	s_getch
{
	int			fd;
	int			n;
	char		buf[BUFF_SIZE];
	char		*bufp;
}				t_getch;

int				get_next_line(const int fd, char **line);
//t_getch			*set_getch(const int fd);
//t_list			*tog_lst(t_list **lst, const int fd);

#	endif
