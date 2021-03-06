/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <thifranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 12:46:46 by thifranc          #+#    #+#             */
/*   Updated: 2016/08/18 09:05:44 by thifranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int		wild_cases(int ac, char **av)
{
	int		fd;

	if (ac != 2)
		exiting("One and only one arg please\n");
	if ((fd = open(av[1], O_RDONLY)) == -1)
		exiting("File couldn't open\n");
	return (fd);
}

t_list	*new_node(int x, int y, int z)
{
	t_list	*out;

	if (!(out = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	out->x = x;
	out->y = y;
	out->z = z;
	out->end = 0;
	out->next = NULL;
	out->color = 0;
	return (out);
}

int		line_check(char *str, t_list **head, int y)
{
	int		i;
	int		ct;
	int		tmp;

	i = 0;
	ct = 0;
	while (str[i])
	{
		while (str[i] && str[i] == ' ')
			i++;
		tmp = ft_atoi_error(str + i);
		add_in_list(&(*head), ct, y, tmp);
		if (str[i] != '\0')
			i += ft_nblen(tmp);
		if (str[i] && str[i] != ' ')
			return (0);
		ct++;
	}
	last_of(*head)->end = 1;
	return (1);
}

t_list	*get_data(int fd)
{
	char	*line;
	t_list	*out;
	int		y;

	line = NULL;
	out = NULL;
	y = 0;
	while (ft_gnl(fd, &line) > 0)
	{
		if (!line_check(line, &out, y))
			exiting("Data map not well formated, only numbers please\n");
		dprintf(1, "y = %d\n", y);
		y++;
		free(line);
	}
	close(fd);
	return (out);
}

int		main(int ac, char **av)
{
	t_list	*head;
	int		fd;
	t_dot	*tab;

	fd = wild_cases(ac, av);
	head = get_data(fd);
	if (!head)
		exiting("Nothing found in file\n");
	tab = make_tab(head);
}
