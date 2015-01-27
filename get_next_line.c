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
#include <unistd.h>

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

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	*line = ft_strsub(save, 0, i);
	save = ft_strsub(save, i + 1, ft_strlen(save) - (i - 1));
	return (save);
}

static int	ft_last_line(char *savebuff, char *save, char **line)
{
	if (savebuff)
		*line = ft_strdup(savebuff);
	else
		*line = ft_strdup(save);
	return (BUFF_SIZE);
}

int			get_next_line(int const fd, char **line)
{
	int			value_read;
	static char	save[BUFF_SIZE] = "";
	char		*savebuff;

	if (!(savebuff = NULL) && (!line || fd < 0))
		return (-1);
	if (*save && ft_strlen(save) > 0 && ft_end_line(save))
	{
		ft_strncpy(save, ft_give_clean(save, line), BUFF_SIZE);
		return (1);
	}
	else if (*save && ft_strlen(save) > 0)
		savebuff = ft_strdup(save);
	while ((value_read = read(fd, save, BUFF_SIZE)) > 0)
	{
		save[value_read] = '\0';
		savebuff = ft_strjoin(savebuff, save);
		if (ft_end_line(savebuff))
		{
			ft_strncpy(save, ft_give_clean(savebuff, line), BUFF_SIZE);
			return (1);
		}
	}
	ft_bzero(save, ft_last_line(savebuff, save, line));
	return (value_read);
}
