/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputman <aputman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 14:05:51 by aputman           #+#    #+#             */
/*   Updated: 2017/03/13 16:39:48 by abara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/rt.h"

static unsigned int		get_size_bmp(char *filename)
{
	unsigned int		size;
	char				*buf;
	int					fd;

	fd = open(filename, O_RDONLY);
	buf = (char*)malloc(sizeof(char) * 6);
	if (read(fd, buf, 6) > 0)
	{
		size = get_from_data(2, (unsigned char*)buf);
		ft_memdel((void**)&buf);
		return (size);
	}
	ft_memdel((void**)&buf);
	return (0);
}

static unsigned char	*get_data(char *filename, unsigned int size)
{
	unsigned char		*data;
	char				buf;
	int					fd;
	int					i;

	i = 0;
	fd = open(filename, O_RDONLY);
	data = (unsigned char *)malloc(sizeof(unsigned char) * size);
	while (read(fd, &buf, 1) > 0)
	{
		data[i] = buf;
		i++;
	}
	close(fd);
	return (data);
}

static void				get_texture_data(t_texture *t, size_t offset,
		size_t size, unsigned char *data)
{
	unsigned int		bpp;
	unsigned int		start;
	int					i;

	i = 0;
	start = offset;
	bpp = *(unsigned int*)(data + 28);
	if (bpp == 24)
	{
		while (offset < size)
		{
			t->texture[i] = data[offset];
			offset++;
			i++;
		}
	}
	else if (bpp == 32)
	{
		while (offset++ < size)
		{
			if ((offset - start) % 4 != 0)
				t->texture[i++] = data[offset];
		}
	}
}

static unsigned char	*invert_by_line(unsigned char *src, size_t w, size_t h,
		int size)
{
	unsigned char		*tmp;
	unsigned char		*dst;
	int					x;
	int					y;
	int					i;

	y = 0;
	tmp = (unsigned char*)malloc(sizeof(unsigned char) * w * 3);
	dst = (unsigned char*)malloc(sizeof(unsigned char) * size);
	while (y < h)
	{
		tmp = ft_ustrncpy_f(tmp, &src[w * y * 3], w * 3);
		ft_ustrncpy_f(&dst[w * (h - (y + 1)) * 3], tmp, w * 3);
		y++;
	}
	ft_memdel((void**)&tmp);
	return (dst);
}

void					get_texture(t_texture *texture, char *filename)
{
	unsigned int		size;
	unsigned char		*data;
	unsigned char		*tmp;
	int					i;

	size = get_size_bmp(filename);
	if (size != 0)
	{
		data = get_data(filename, size);
		texture->w = get_from_data(18, data);
		texture->h = get_from_data(22, data);
		texture->name = filename;
		texture->texture = (unsigned char*)malloc(sizeof(unsigned char) *
		texture->w * texture->h * 3);
		tmp = texture->texture;
		get_texture_data(texture, get_from_data(10, data), size, data);
		texture->texture = invert_by_line(texture->texture,
		texture->w, texture->h, texture->w * texture->h * 3);
		ft_memdel((void**)&data);
		ft_memdel((void**)&tmp);
	}
}
