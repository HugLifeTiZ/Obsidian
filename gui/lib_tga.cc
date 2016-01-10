//------------------------------------------------------------------------
//  TGA (Targa) IMAGE LOADING
//------------------------------------------------------------------------
//
//  Oblige Level Maker
//
//  Copyright (C) 2013-2016 Andrew Apted
//  Copyright (C) 1997-2001 Id Software, Inc.
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//------------------------------------------------------------------------
//
//  NOTE: this is based on the TGA loading code from Quake 2.
//
//------------------------------------------------------------------------

#include "headers.h"
#include "main.h"

#include "lib_tga.h"
#include "lib_file.h"

#ifdef HAVE_PHYSFS
#include "m_addons.h"
#endif


tga_image_c::tga_image_c(int W, int H) :
	width(W), height(H),
	opacity(OPAC_UNKNOWN)
{
	pixels = new rgb_color_t[W * H];
}


tga_image_c::~tga_image_c()
{
	delete[] pixels;
	pixels = NULL;
}


typedef struct
{
	u8_t	id_length, colormap_type, image_type;
	u16_t	colormap_index, colormap_length;
	u8_t	colormap_size;
	u16_t	x_origin, y_origin, width, height;
	u8_t	pixel_size, attributes;

} targa_header_t;


tga_image_c * TGA_LoadImage (const char *path)
{
// load the file

	int length;

#ifdef HAVE_PHYSFS
	byte * buffer = VFS_LoadFile(path, &length);
#else
	byte * buffer = FileLoad(path, &length);
#endif

	if (! buffer)
		return NULL;

	byte * buf_p   = buffer;
///	byte * buf_end = buffer + length;


// decode the TGA header

	targa_header_t	targa_header;

	targa_header.id_length = *buf_p++;
	targa_header.colormap_type = *buf_p++;
	targa_header.image_type = *buf_p++;
	
	targa_header.colormap_index = (buf_p[0]) | (buf_p[1] << 8);
	buf_p += 2;
	targa_header.colormap_length = (buf_p[0]) | (buf_p[1] << 8);
	buf_p += 2;
	targa_header.colormap_size = *buf_p++;
	targa_header.x_origin = (buf_p[0]) | (buf_p[1] << 8);
	buf_p += 2;
	targa_header.y_origin = (buf_p[0]) | (buf_p[1] << 8);
	buf_p += 2;
	targa_header.width = (buf_p[0]) | (buf_p[1] << 8);
	buf_p += 2;
	targa_header.height = (buf_p[0]) | (buf_p[1] << 8);
	buf_p += 2;
	targa_header.pixel_size = *buf_p++;
	targa_header.attributes = *buf_p++;

	if (targa_header.image_type != 2 &&
		targa_header.image_type != 10) 
	{
		Main_FatalError("Bad tga file: Only type 2 and 10 images supported\n");
	}

	if (targa_header.colormap_type !=0 ||
	    (targa_header.pixel_size != 24 && targa_header.pixel_size != 32))
	{
		Main_FatalError("Bad tga file: only 24 or 32 bit images supported (no colormaps)\n");
	}


	int width  = targa_header.width;
	int height = targa_header.height;

	if (width == 0 || height == 0)
		Main_FatalError("Bad tga file: width or height is zero\n");


	tga_image_c * img = new tga_image_c(width, height);

	img->width  = width;
	img->height = height;

	bool is_masked  = false;  // opacity testing
	bool is_complex = false;  // 


// decode the pixel stream

	rgb_color_t	*dest = img->pixels;
	rgb_color_t	*p;

	if (targa_header.id_length != 0)
		buf_p += targa_header.id_length;  // skip TARGA image comment

	if (targa_header.image_type == 2)   // Uncompressed, RGB images
	{
		for (int y = height-1 ; y >= 0 ; y--)
		{
			p = dest + y * width;

			for (int x = 0 ; x < width ; x++)
			{
				byte b = *buf_p++;
				byte g = *buf_p++;
				byte r = *buf_p++;
				byte a = 255;

				if (targa_header.pixel_size == 32)
					a = *buf_p++;

				*p++ = MAKE_RGBA(r, g, b, a);

				if (a == 0)
					is_masked = true;
				else if (a != 255)
					is_complex = true;
			}
		}
	}
	else if (targa_header.image_type == 10)   // Runlength encoded RGB images
	{
		byte r=0, g=0, b=0, a=0;

		byte packet_header, packet_size;

		for (int y = height-1 ; y >= 0 ; y--)
		{
			p = dest + y * width;

			for (int x = 0 ; x < width ; )
			{
				packet_header = *buf_p++;
				packet_size = 1 + (packet_header & 0x7f);

				if (packet_header & 0x80)    // run-length packet
				{
					b = *buf_p++;
					g = *buf_p++;
					r = *buf_p++;
					a = 255;

					if (targa_header.pixel_size == 32)
						a = *buf_p++;

					if (a == 0)
						is_masked = true;
					else if (a != 255)
						is_complex = true;
	
					for (int j = 0 ; j < packet_size ; j++)
					{
						*p++ = MAKE_RGBA(r, g, b, a);

						x++;

						if (x == width)  // run spans across edge
						{
							x = 0;
							if (y > 0)
								y--;
							else
								goto breakOut;

							p = dest + y*width;
						}
					}
				}
				else        // not a run-length packet
				{
					for (int j = 0 ; j < packet_size; j++)
					{
						b = *buf_p++;
						g = *buf_p++;
						r = *buf_p++;
						a = 255;

						if (targa_header.pixel_size == 32)
							a = *buf_p++;

						*p++ = MAKE_RGBA(r, g, b, a);

						if (a == 0)
							is_masked = true;
						else if (a != 255)
							is_complex = true;
	
						x++;

						if (x == width)  // pixel packet run spans across edge
						{
							x = 0;
							if (y > 0)
								y--;
							else
								goto breakOut;

							p = dest + y * width;
						}						
					}
				}
			}
			breakOut: ;
		}
	}

	VFS_FreeFile(buffer);

	img->opacity =	is_complex ? OPAC_Complex :
					is_masked  ? OPAC_Masked  : OPAC_Solid;

	return img;
}


//--- editor settings ---
// vi:ts=4:sw=4:noexpandtab
