/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_infinit_cycle.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtelega <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 20:24:57 by dtelega           #+#    #+#             */
/*   Updated: 2017/08/28 20:24:58 by dtelega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "sdl_vm.h"

void		ncurses_speed(t_data *data, char key)
{
	if (data->ncurses_timeout > 0 && data->ncurses_timeout < 1024)
		(!data->mute) ? (sdl_sound(MUS_SPEED)) : 0;
	if (key == 's')
		data->ncurses_timeout /= 2;
	else
	{
		if (data->ncurses_timeout == 0)
			data->ncurses_timeout = 1;
		else
			data->ncurses_timeout *= 2;
	}
	if (data->ncurses_timeout < 0)
		data->ncurses_timeout = 0;
	else if (data->ncurses_timeout > 1024)
		data->ncurses_timeout = 1024;
}

char		ncurses_one_cm_mode(t_data *data, char pause)
{
	data->one_command_mode = 0;
	pause = ' ';
	data->pause = 1;
	display_stats(data, data->stats_win);
	refresh();
	return (pause);
}

char		ncurses_cycle_pause(t_data *data, char pause)
{
	data->pause = 0;
	display_stats(data, data->stats_win);
	refresh();
	(!data->mute) ? (sdl_sound(MUS_BEEP)) : 0;
	return ('q');
}

char		ncurses_global_cycle(t_data *data, char pause)
{
	char	cmd;

	data->pause = 1;
	display_stats(data, data->stats_win);
	refresh();
	cmd = getch();
	if (cmd == 'a' || cmd == 's')
		ncurses_speed(data, cmd);
	if (cmd == ' ')
		pause = ncurses_cycle_pause(data, pause);
	else if (cmd == 'n' && (data->one_command_mode = 1))
		return ('n');
	return (pause);
}
