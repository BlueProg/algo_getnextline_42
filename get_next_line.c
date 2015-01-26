/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmole <mmole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/26 15:05:26 by mmole             #+#    #+#             */
/*   Updated: 2015/01/26 15:05:27 by mmole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/includes/libft.h"
#include <sys/types.h>

#include <stdio.h>

static int	ft_end_line(char *save)
{
	int	i;

	i = 0;
	while (save[i])
	{
		if (save[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_give_clean(char *save, char **line)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = save;
	ft_putendl(" -- AVANT --");

	// printf("save2: >%s<\n", tmp);
	ft_putendl(save);
	ft_putendl(" -- APRES --");

	while (tmp[i] != '\n')
		i++;

	tmp = save;
	*line = ft_strsub(tmp, 0, i);

	ft_putendl(save);


	ft_putendl(" -- ");

	save = ft_strsub(save, i + 1, ft_strlen(save) - (i - 1));
	printf("save4: >%s<\n", save);
	// printf("save: %s\n", save);
	// printf("line : %s\n\n\n\n", *line);
	return (save);
}

int			get_next_line(int const fd, char **line)
{
	int			value_read;
	static char	save[BUFF_SIZE + 1] = "";
	char		*savebuff;

	savebuff = NULL;
	// printf("save:%s\n", save);
	if (*save && save && ft_strlen(save) > 0 && ft_end_line(save))
	{
		ft_give_clean(save, line);
		return (1);
	}
	else if (*save && save && ft_strlen(save) > 0)
		savebuff = ft_strdup(save);
	while ((value_read = read(fd, save, BUFF_SIZE)) > 0)
	{
		savebuff = ft_strjoin(savebuff, save);
		printf("savebuff: %s\n", savebuff);
		if (ft_end_line(savebuff))
		{
			ft_strncpy(save, ft_give_clean(savebuff, line), BUFF_SIZE);
			return (1);
		}
	}
	return (value_read);
}