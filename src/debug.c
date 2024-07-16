/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemercie <lemercie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:55:04 by lemercie          #+#    #+#             */
/*   Updated: 2024/07/16 11:33:18 by lemercie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include <stdio.h> //debugging

void	print_map(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->rows)
	{
		x = 0;
		while (x < map->cols)
		{
			printf("%f ", map->arr[y][x].depth);
			x++;
		}
		printf("\n");
		y++;
	}
}

void	print_map_2d(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->rows)
	{
		x = 0;
		while (x < map->cols)
		{
			printf("%.1f,%.1f ", map->arr[y][x].screen_x, map->arr[y][x].screen_y);
			x++;
		}
		printf("\n");
		y++;
	}
}
