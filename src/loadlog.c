/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadlog.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 17:14:29 by abara             #+#    #+#             */
/*   Updated: 2017/03/13 17:41:58 by abara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/rt.h"

static void	init_newwinfo(t_winfo *w, char *filename)
{
	int		i;

	i = 0;
	while (i < w->file.size)
	{
		ft_memdel((void**)&w->file.file[i]);
		i++;
	}
	ft_memdel((void**)&w->file.file[i]);
	w->filename = filename;
	init_winfo_file(w, &w->file);
	parse_file(w->filename, &w->file);
	check_file(&w->file);
	get_camera(w);
	get_light(w);
	get_object(w);
	get_objecttexture(w);
}

void		loadlog(t_winfo *w, char *filename)
{
	int		i;

	i = 0;
	while (i < w->file.nbobj)
	{
		ft_memdel((void**)&w->text[i].texture.texture);
		ft_memdel((void**)&w->text[i].normal.texture);
		i++;
	}
	ft_memdel((void**)&w->text);
	ft_memdel((void**)&w->obj);
	ft_memdel((void**)&w->light);
	init_newwinfo(w, filename);
}
