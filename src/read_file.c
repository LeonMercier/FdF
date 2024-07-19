/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemercie <lemercie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:21:35 by lemercie          #+#    #+#             */
/*   Updated: 2024/07/19 09:18:35 by lemercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int	getlen_strv(char **strv)
{
	int	len;

	len = 0;
	while (*strv)
	{
		strv++;
		len++;
	}
	return (len);
}

int	hexchar_to_int(char c)
{
	const char	upper[] = {"0123456789ABCDEF"};
	const char	lower[] = {"0123456789abcdef"};
	int			i;

	i = 0;
	while (i < 16)
	{
		if (c == lower[i] || c == upper[i])
			return (i);
		i++;
	}
	ft_printf("Error in hexchar_to_int(): %c \n", c);
	return (-1);
}

// shifting to the left and adding 255 adds the alpha channel at full opacity
int	parse_color(char *str)
{
	int	color;
	int	word;

	color = 0;
	str += 2;
	while (*str)
	{
		word = hexchar_to_int(*str);
		if (word < 0 || word > 16)
			break ;
		color = (color * 16) + word;
		str++;
	}
	color = color << 8;
	color += 255;
	return (color);
}

// the second call to ft_split get rid of the newlines of the last column
static void	parse_point(t_map *map, char *point, int y, int x)
{
	char	**strv;
	int		err_atoi;

	strv = ft_split(point, ',');	//TODO fail check
	err_atoi = 0;
	map->arr[y][x].depth =  ft_atoi_safe2(strv[0], &err_atoi);
	if (err_atoi)
		ft_printf("atoi error: %i\n", err_atoi);
	if (strv[1]) // TODO check ft_split fail
		map->arr[y][x].color = parse_color(ft_split(strv[1], '\n')[0]); 
	else
		map->arr[y][x].color = 0xFFFFFFFF;
}

static int	parse_line(t_map *map, char *line)
{
	char	**strv;
	int		i;
	t_point **new_arr;

	strv = ft_split(line, ' ');
	if (!strv)
		return (-1);
	map->cols = getlen_strv(strv); // assuming rectangular map, this would 
								   // really only need to be set once
	map->rows++;
	new_arr = malloc(map->rows  * sizeof(t_point *));
	if (map->arr)
		ft_memmove(new_arr, map->arr, sizeof(t_point *) * (map->rows - 1));
	map->arr = new_arr;
	map->arr[map->rows - 1] = malloc(map->cols * sizeof(t_point));
	i = 0;
	while (*strv) 
	{
		parse_point(map, *strv, map->rows - 1, i);
		strv++;
		i++;
	}
	return (0);
}

// TODO: do we know whether GNL has reached EOF or failed internally?
int	read_file(t_map *map, char *filename)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error: Could not open file\n");
		return (-1);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (parse_line(map, line) < 0)
		{
			ft_printf("Error in parse_line()\n");
			free(line);
			return (-1);
		}
		free(line);
	}
	close(fd);
	return (0);
}
