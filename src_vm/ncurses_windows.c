/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_windows.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtelega <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 16:08:31 by dtelega           #+#    #+#             */
/*   Updated: 2017/08/29 16:09:36 by dtelega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

WINDOW		*create_newwin(int height, int width, int starty, int startx)
{
	WINDOW		*local_win;
	char		border;

	border = 0;
	local_win = newwin(height, width, starty, startx);
	box(local_win, border, border);
	wrefresh(local_win);
	return (local_win);
}
