#include "mini.h"

int			echo(char **parsed)
{
	int		flag;
	int		i;

	flag = 0;
	if (*(parsed + 1))
	{
		if (ft_strcmp(*(parsed + 1), "-n") == 0)
			flag = 1;
	}
	i = 1;
	if (flag)
		i++;
	while (parsed[i])
	{
		ft_printf("%s", parsed[i]);
		i++;
		if (parsed[i])
			ft_printf(" ");
	}
	if (!flag)
		ft_printf("\n");
	return (1);
}
