/**
  test/components/video/omxvideocapnplay.h

  Test application that uses a OpenMAX component, a generic video decoder.
  The application receives an video stream (.m4v or .264) decoded by a multiple format decoder component.
  The decoded output is seen by a yuv viewer.

  Copyright (C) 2007-2009 STMicroelectronics
  Copyright (C) 2007-2009 Nokia Corporation and/or its subsidiary(-ies).

  This library is free software; you can redistribute it and/or modify it under
  the terms of the GNU Lesser General Public License as published by the Free
  Software Foundation; either version 2.1 of the License, or (at your option)
  any later version.

  This library is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
  FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
  details.

  You should have received a copy of the GNU Lesser General Public License
  along with this library; if not, write to the Free Software Foundation, Inc.,
  51 Franklin St, Fifth Floor, Boston, MA
  02110-1301  USA

*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>
#include <ctype.h>

#include <OMX_Core.h>
#include <OMX_Component.h>
#include <OMX_Types.h>
#include <OMX_Video.h>

#include <bellagio/tsemaphore.h>
#include <user_debug_levels.h>

/* Application's private data */
typedef struct appPrivateType{
  tsem_t* sourceEventSem;
  tsem_t* eofSem;
  tsem_t* colorconvEventSem;
  tsem_t* fbdevSinkEventSem;
  OMX_HANDLETYPE videosrchandle;
  OMX_HANDLETYPE colorconv_handle;
  OMX_HANDLETYPE fbdev_sink_handle;
}appPrivateType;

#define BUFFER_IN_SIZE 4096

/** Specification version*/
#define VERSIONMAJOR    1
#define VERSIONMINOR    1
#define VERSIONREVISION 0
#define VERSIONSTEP     0

/* Callback prototypes for video source */
OMX_ERRORTYPE videosrcEventHandler(
  OMX_HANDLETYPE hComponent,
  OMX_PTR pAppData,
  OMX_EVENTTYPE eEvent,
  OMX_U32 Data1,
  OMX_U32 Data2,
  OMX_PTR pEventData);

OMX_ERRORTYPE videosrcFillBufferDone(
  OMX_HANDLETYPE hComponent,
  OMX_PTR pAppData,
  OMX_BUFFERHEADERTYPE* pBuffer);

/** callback prototypes for color converter */
OMX_ERRORTYPE colorconvEventHandler(
  OMX_HANDLETYPE hComponent,
  OMX_PTR pAppData,
  OMX_EVENTTYPE eEvent,
  OMX_U32 Data1,
  OMX_U32 Data2,
  OMX_PTR pEventData);

OMX_ERRORTYPE colorconvEmptyBufferDone(
  OMX_HANDLETYPE hComponent,
  OMX_PTR pAppData,
  OMX_BUFFERHEADERTYPE* pBuffer);

OMX_ERRORTYPE colorconvFillBufferDone(
  OMX_HANDLETYPE hComponent,
  OMX_PTR pAppData,
  OMX_BUFFERHEADERTYPE* pBuffer);

/** callback prototypes for sink */
OMX_ERRORTYPE fb_sinkEventHandler(
  OMX_HANDLETYPE hComponent,
  OMX_PTR pAppData,
  OMX_EVENTTYPE eEvent,
  OMX_U32 Data1,
  OMX_U32 Data2,
  OMX_PTR pEventData);

OMX_ERRORTYPE fb_sinkEmptyBufferDone(
  OMX_HANDLETYPE hComponent,
  OMX_PTR pAppData,
  OMX_BUFFERHEADERTYPE* pBuffer);

/** function prototype declaration */

/** display general help  */
void display_help();

/**  Try to determine resolution based on filename */
int find_resolution(char* searchname);

/** this function sets the color converter and video sink port characteristics
  * based on the video decoder output port settings
  */
int setPortParameters();


