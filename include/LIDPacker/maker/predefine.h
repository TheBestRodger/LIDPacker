#pragma once
/*!
********************************************************
*	@file predefine.h
*   @author Kalikin D.M. - dep.106
*	@date   28.06.2023
*	@brief Хранит переменные под особенности опертативной системы 
**********************************************************
*/

#ifndef __SYS_PUBLIC__
#define __SYS_PUBLIC__


/*
===============================================================================

	Non-portable system services.

===============================================================================
*/
// Win32
#define ANSI							"Windows-1251"
#define UTF8							"UTF-8"
#if defined(WIN32) || defined(_WIN32)


#define	BUILD_STRING					"win-x86"
#define BUILD_OS_ID						0
#define	CPUSTRING						"x86"
#define CPU_EASYARGS					1

#define ALIGN16( x )					__declspec(align(16)) x
#define PACKED

#define _alloca16( x )					((void *)((((int)_alloca( (x)+15 )) + 15) & ~15))

#define PATHSEPERATOR_STR				"\\"
#define PATHSEPERATOR_CHAR				'\\'

#define ID_INLINE						__forceinline
#define ID_STATIC_TEMPLATE				static

#define assertmem( x, y )				assert( _CrtIsValidPointer( x, y, true ) )

#define CODEC							"Windows-1251"


#endif


// Mac OSX
#if defined(MACOS_X) || defined(__APPLE__)

#define BUILD_STRING				"MacOSX-universal"
#define BUILD_OS_ID					1
#ifdef __ppc__
#define	CPUSTRING					"ppc"
#define CPU_EASYARGS				0
#elif defined(__i386__)
#define	CPUSTRING					"x86"
#define CPU_EASYARGS				1
#endif

#define ALIGN16( x )					x __attribute__ ((aligned (16)))

#ifdef __MWERKS__
#define PACKED
#include <alloca.h>
#else
#define PACKED							__attribute__((packed))
#endif

#define _alloca							alloca
#define _alloca16( x )					((void *)((((int)alloca( (x)+15 )) + 15) & ~15))

#define PATHSEPERATOR_STR				"/"
#define PATHSEPERATOR_CHAR				'/'

#define __cdecl
#define ASSERT							assert

#define ID_INLINE						inline
#define ID_STATIC_TEMPLATE

#define assertmem( x, y )

#define CODEC							"UTF-8"

#endif


// Linux
#ifdef __linux__

#ifdef __i386__
#define	BUILD_STRING				"linux-x86"
#define BUILD_OS_ID					2
#define CPUSTRING					"x86"
#define CPU_EASYARGS				1
#elif defined(__ppc__)
#define	BUILD_STRING				"linux-ppc"
#define CPUSTRING					"ppc"
#define CPU_EASYARGS				0
#endif

#define _alloca							alloca
#define _alloca16( x )					((void *)((((int)alloca( (x)+15 )) + 15) & ~15))

#define ALIGN16( x )					x
#define PACKED							__attribute__((packed))

#define PATHSEPERATOR_STR				"/"
#define PATHSEPERATOR_CHAR				'/'

#define __cdecl
#define ASSERT							assert

#define ID_INLINE						inline
#define ID_STATIC_TEMPLATE

#define assertmem( x, y )

#define CODEC							"UTF-8"

#endif

#ifdef __GNUC__
#define id_attribute(x) __attribute__(x)
#else
#define id_attribute(x)  
#endif

#endif /* !__SYS_PUBLIC__ */