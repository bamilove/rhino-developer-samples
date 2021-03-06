/*----------------------------------------------------------------------
 *  si.h -- SpaceWare input library header
 *
 *  $Id: si.h,v 1.22 1998/03/12 11:07:03 mfarr Exp $
 *
 *  SpaceWare input library
 *
 *----------------------------------------------------------------------
 *
 * (C) 1998-2001 3Dconnexion. All rights reserved. 
 * Permission to use, copy, modify, and distribute this software for all
 * purposes and without fees is hereby grated provided that this copyright
 * notice appears in all copies.  Permission to modify this software is granted
 * and 3Dconnexion will support such modifications only is said modifications are
 * approved by 3Dconnexion.
 *
 */


#ifndef _SI_H_
#define _SI_H_

static char incFileNameCvsId[]="(C) 1996 Spacetec IMC Corporation: $Id: si.h,v 1.22 1998/03/12 11:07:03 mfarr Exp $";

#include "spwmacro.h"
#include "spwdata.h"

#ifdef OS_DEFINED
#undef OS_DEFINED
#endif

#ifdef OS_WIN32
#define OS_DEFINED
#include <windows.h>
#endif

#ifndef OS_DEFINED
#ifdef WIN32
#pragma message ("ERROR: an OS type must be defined -- e.g. OS_WIN32")
#endif
ERROR: an OS type must be defined -- e.g. OS_WIN32
#endif

#include <stdio.h>
#include "spwerror.h"

/*
 * UI modes 
 */
#define SI_UI_ALL_CONTROLS    0xffffffffL
#define SI_UI_NO_CONTROLS     0x00000000L

/*
 *  These UI modes are left here for legacy applications.
 */
#define SI_UI_FILTERS         0x00000001L
#define SI_UI_FUNC_BUTTONS    0x00000002L
#define SI_UI_RESET_BUTTONS   0x00000004L
#define SI_UI_SENSITIVITY     0x00000008L
#define SI_UI_TUNING          0x00000010L
#define SI_UI_DIALOG_POPUP    0x00000020L

/*
 * Device types and classes 
 */
typedef enum
   {
   SI_ALL_TYPES           = -1,
   SI_UNKNOWN_DEVICE      =  0,
   SI_SPACEBALL_2003      =  1,
   SI_SPACEBALL_3003      =  2,
   SI_SPACE_CONTROLLER    =  3,
   SI_AVENGER             =  4,
   SI_SPACEORB_360        =  5,
   SI_NAVIGATOR           =  6,
   SI_SPACEBALL_2003A     =  7,
   SI_SPACEBALL_2003B     =  8,
   SI_SPACEBALL_2003C     =  9,
   SI_SPACEBALL_3003A     =  10,
   SI_SPACEBALL_3003B     =  11,
   SI_SPACEBALL_3003C     =  12,
   SI_SPACEBALL_4000      =  13,
   SI_SPACEMOUSE_CLASSIC  =  14, 
   SI_SPACEMOUSE_PLUS     =  15,
   SI_SPACEMOUSE_XT       =  16,
   SI_PUCKMAN             =  17,
   SI_CADMAN              =  18,
   SI_NUM_DEV_TYPES  /* Leave this last, add before it */
   } SiDevType;

/*
 *  These defintions of device classes are left in for legacy applications.
 */
#define SI_HIGH_END           63
#define SI_MED_END            62
#define SI_LOW_END            61

/*
 * Data retrieval mode, only SI_EVENT is currently supported.
 */
#define SI_EVENT              0x0001
#define SI_POLL               0x0002

/*
 * Get event flags
 */
#define SI_AVERAGE_EVENTS     0x0001

/*
 * This is an INTERNAL flag used by the polling mechanism, user applications
 * should NOT send this flag.
 */
#define SI_POLLED_REQUEST     0x0100 

/*
 * SpaceWare event types
 */
typedef enum
   {
   SI_BUTTON_EVENT = 1,
   SI_MOTION_EVENT,
   SI_COMBO_EVENT, /* Not implemented */
   SI_ZERO_EVENT,
   SI_EXCEPTION_EVENT,
   SI_OUT_OF_BAND,
   SI_ORIENTATION_EVENT,
   SI_KEYBOARD_EVENT,
   SI_LPFK_EVENT
   } SiEventType;

/*
 * Data modes
 */
#define SI_MODE_NORMALIZE     0x0001
#define SI_MODE_COMPRESS      0x0002
#define SI_MODE_SENSITIVITY   0x0004
#define SI_MODE_TUNING        0x0008

/*
 * Motion data offsets
 */
#define SI_TX                 0              /* Translation X value */
#define SI_TY                 1              /* Translation Y value */
#define SI_TZ                 2              /* Translation Z value */
#define SI_RX                 3              /* Rotation X value */
#define SI_RY                 4              /* Rotation Y value */
#define SI_RZ                 5              /* Rotation Z value */

/*
 * Reserved buttons
 */

#define SI_RESET_BIT          0x00000001L
#define SI_PICK_BIT           0x80000000L
#define SI_DIALOG_BIT         0x40000000L

#define SI_RESET_BUTTON       0
#define SI_PICK_BUTTON        31
#define SI_DIALOG_BUTTON      30

/*
 * Miscellaneous
 */
#define SI_END_ARGS           0
#define SI_NO_HANDLE          ((SiHdl) NULL)
#define SI_ALL_HANDLES        ((SiHdl) NULL)
#define SI_ANY_HANDLE         ((SiHdl) NULL)
#define SI_NO_TRANSCTL        ((SiTransCtl) NULL)
#define SI_NO_MASK            ((SiTypeMask *) NULL)
#define SI_ANY_DEVICE         -1
#define SI_NO_DEVICE          -1
#define SI_NO_TYPE            -1
#define SI_NO_LIST            -1
#define SI_NO_BUTTON          -1
#define SI_STRSIZE            128
#define SI_MAXBUF             128
#define SI_KEY_MAXBUF         5120

typedef int SiDevID;          /* Device ID */
typedef void *SiHdl;          /* SpaceWare handle */
typedef void *SiTransCtl;     /* SpaceWare transport control handle */

typedef struct                /* Open data */
   {

   HWND hWnd;               /* Window handle for SpaceWare messages.        */
   SiTransCtl transCtl;     /* SpaceWare transport control handle. Reserved */
                            /* for the s80 transport mechanism.             */
   DWORD processID;         /* The process ID for this application.         */
   char exeFile[MAX_PATH];  /* The executable name of the process.          */
   SPWint32 libFlag;        /* Library version flag.                        */
   } SiOpenData;

typedef struct                /* Get event Data */
   {

   UINT msg;
   WPARAM wParam;
   LPARAM lParam;
   } SiGetEventData;

typedef struct                /* Device type mask */
   {
   unsigned char mask[8];
   } SiTypeMask;

typedef struct                /* Device port information */
   {
   SiDevID devID;             /* Device ID */
   int devType;               /* Device type */
   int devClass;              /* Device class */
   char devName[SI_STRSIZE];  /* Device name */
   char portName[SI_STRSIZE]; /* Port name */
   } SiDevPort;

typedef struct                /* Device information */
   {
   char firmware[SI_STRSIZE]; /* Firmware version */
   int devType;               /* Device type */
   int numButtons;            /* Number of buttons */
   int numDegrees;            /* Number of degrees of freedom */
   SPWbool canBeep;           /* Device beeps */
   int majorVersion;          /* Major version number */
   int minorVersion;          /* Minor version number */
   } SiDevInfo;

typedef struct                /* Version information */
   {
   int major;                 /* Major version number */
   int minor;                 /* Minor version number */
   int build;                 /* Build number */
   char version[SI_STRSIZE];  /* Version string */
   char date[SI_STRSIZE];     /* Date string */
   } SiVerInfo;

typedef struct                /* Sensitivity parameters */
   {
   char dummy;
   } SiSensitivity;

typedef struct                /* Tuning parameters */
   {
   char dummy;
   } SiTuning;

typedef struct
   {
   SPWuint8 code;                 /* Out of band message code */
   SPWuint8 message[SI_MAXBUF-1]; /* The actual message       */
   } SiSpwOOB;

typedef struct
   {
   SPWuint8 string[SI_KEY_MAXBUF];  /* String for keyboard data */
   } SiKeyboardData;

typedef struct
   {
   SPWuint32 lpfk;            /* LPFK number to send */
   } SiLpfkData;

typedef enum
   {
   SI_LEFT = 0,
   SI_RIGHT
   } SiOrientation;

typedef struct                /* Bitmasks of button states */
   {
   SPWuint32 last;            /* Buttons pressed as of last event */
   SPWuint32 current;         /* Buttons pressed as of this event */
   SPWuint32 pressed;         /* Buttons pressed this event */
   SPWuint32 released;        /* Buttons released this event */
   } SiButtonData;

typedef struct                /* SpaceWare data */
   {
   SiButtonData bData;        /* Button data */
   long mData[6];             /* Motion data (index via SI_TX, etc) */
   long period;               /* Period (milliseconds) */
   } SiSpwData;

typedef struct                /* SpaceWare event */
   {
   int type;                  /* Event type */
   union
      {
      SiSpwData spwData;           /* Button, motion, or combo data        */
      SiSpwOOB spwOOB;             /* Out of band message                  */
      SiOrientation spwOrientation;/* Which hand orientation is the device */
      char exData[SI_MAXBUF];      /* Exception data                       */
      SiKeyboardData spwKeyData;   /* String for keyboard data             */
      SiLpfkData spwLpfkData;      /* LPFK data                            */
      } u;
   } SiSpwEvent;

typedef struct                /* Event handler (for SiDispatch) */
   {
   int (*func) (SiOpenData *, SiGetEventData *, SiSpwEvent *, void *);
   void *data;
   } SiEventHandler;

typedef struct                /* SpaceWare event handlers */
   {
   SiEventHandler button;     /* Button event handler */
   SiEventHandler motion;     /* Motion event handler */
   SiEventHandler combo;      /* Combo event handler */
   SiEventHandler zero;       /* Zero event handler */
   SiEventHandler exception;  /* Exception event handler */
   } SiSpwHandlers;

#ifdef __cplusplus
extern "C" {
#endif


enum SpwRetVal SiAndTypeMask (SiTypeMask *pTMaskA, SiTypeMask *pTMaskB);
int SiGetPortList (SiDevPort **ppPort);
void SiFreePortList (SiDevPort *pPort);
void SiTune2003 (SiSpwEvent *pEvent);
void SiTuneSC (SiSpwEvent *pEvent);



#ifdef __cplusplus
}
#endif

#endif   /* _SI_H_ */
