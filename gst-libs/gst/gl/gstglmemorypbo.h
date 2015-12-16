/*
 * GStreamer
 * Copyright (C) 2012 Matthew Waters <ystreet00@gmail.com>
 * Copyright (C) 2015 Matthew Waters <matthew@centricular.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef _GST_GL_MEMORY_PBO_H_
#define _GST_GL_MEMORY_PBO_H_

#include <gst/gst.h>
#include <gst/gstallocator.h>
#include <gst/gstmemory.h>
#include <gst/video/video.h>

#include <gst/gl/gstglmemory.h>

G_BEGIN_DECLS

#define GST_TYPE_GL_MEMORY_PBO_ALLOCATOR (gst_gl_memory_pbo_allocator_get_type())
GType gst_gl_memory_pbo_allocator_get_type(void);

#define GST_IS_GL_MEMORY_PBO_ALLOCATOR(obj)              (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GST_TYPE_GL_MEMORY_PBO_ALLOCATOR))
#define GST_IS_GL_MEMORY_PBO_ALLOCATOR_CLASS(klass)      (G_TYPE_CHECK_CLASS_TYPE ((klass), GST_TYPE_GL_MEMORY_PBO_ALLOCATOR))
#define GST_GL_MEMORY_PBO_ALLOCATOR_GET_CLASS(obj)       (G_TYPE_INSTANCE_GET_CLASS ((obj), GST_TYPE_GL_MEMORY_PBO_ALLOCATOR, GstGLMemoryPBOAllocatorClass))
#define GST_GL_MEMORY_PBO_ALLOCATOR(obj)                 (G_TYPE_CHECK_INSTANCE_CAST ((obj), GST_TYPE_GL_MEMORY_PBO_ALLOCATOR, GstGLMemoryPBOAllocator))
#define GST_GL_MEMORY_PBO_ALLOCATOR_CLASS(klass)         (G_TYPE_CHECK_CLASS_CAST ((klass), GST_TYPE_GL_MEMORY_PBO_ALLOCATOR, GstGLAllocatorClass))
#define GST_GL_MEMORY_PBO_ALLOCATOR_CAST(obj)            ((GstGLMemoryPBOAllocator *)(obj))

/**
 * GstGLMemoryPBO:
 *
 * Private instance
 */
struct _GstGLMemoryPBO
{
  GstGLMemory      mem;

  /* <private> */
  GstGLBuffer          *pbo;
};

/**
 * GST_GL_MEMORY_PBO_ALLOCATOR:
 *
 * The name of the GL Memory PBO allocator
 */
#define GST_GL_MEMORY_PBO_ALLOCATOR_NAME   "GLMemoryPBO"

void          gst_gl_memory_pbo_init_once               (void);
gboolean      gst_is_gl_memory_pbo                      (GstMemory * mem);

GstMemory *         gst_gl_memory_pbo_alloc             (GstGLContext * context,
                                                         GstGLTextureTarget target,
                                                         GstAllocationParams *params,
                                                         GstVideoInfo * info,
                                                         guint plane,
                                                         GstVideoAlignment *valign);
GstGLMemoryPBO *    gst_gl_memory_pbo_wrapped           (GstGLContext * context,
                                                         GstGLTextureTarget target,
                                                         GstVideoInfo * info,
                                                         guint plane,
                                                         GstVideoAlignment *valign,
                                                         gpointer data,
                                                         gpointer user_data,
                                                         GDestroyNotify notify);
GstGLMemoryPBO *    gst_gl_memory_pbo_wrapped_texture   (GstGLContext * context,
                                                         guint texture_id,
                                                         GstGLTextureTarget target,
                                                         GstVideoInfo * info,
                                                         guint plane,
                                                         GstVideoAlignment *valign,
                                                         gpointer user_data,
                                                         GDestroyNotify notify);

void          gst_gl_memory_pbo_download_transfer       (GstGLMemoryPBO * gl_mem);
void          gst_gl_memory_pbo_upload_transfer         (GstGLMemoryPBO * gl_mem);

gboolean      gst_gl_memory_pbo_copy_into_texture       (GstGLMemoryPBO *gl_mem,
                                                         guint tex_id,
                                                         GstGLTextureTarget target,
                                                         GstVideoGLTextureType tex_type,
                                                         gint width,
                                                         gint height,
                                                         gint stride,
                                                         gboolean respecify);

gboolean      gst_gl_memory_pbo_setup_buffer            (GstGLContext * context,
                                                         GstGLTextureTarget target,
                                                         GstAllocationParams * params,
                                                         GstVideoInfo * info,
                                                         GstVideoAlignment *valign,
                                                         GstBuffer * buffer);
gboolean      gst_gl_memory_pbo_setup_wrapped           (GstGLContext * context,
                                                         GstGLTextureTarget target,
                                                         GstVideoInfo * info,
                                                         GstVideoAlignment *valign,
                                                         gpointer data[GST_VIDEO_MAX_PLANES],
                                                         GstGLMemoryPBO *textures[GST_VIDEO_MAX_PLANES],
                                                         gpointer user_data,
                                                         GDestroyNotify notify);

/**
 * GstGLAllocator
 *
 * Opaque #GstGLAllocator struct
 */
struct _GstGLMemoryPBOAllocator
{
  GstGLMemoryAllocator parent;
};

/**
 * GstGLAllocatorClass:
 *
 * The #GstGLAllocatorClass only contains private data
 */
struct _GstGLMemoryPBOAllocatorClass
{
  GstGLMemoryAllocatorClass parent_class;
};

G_END_DECLS

#endif /* _GST_GL_MEMORY_PBO_H_ */
