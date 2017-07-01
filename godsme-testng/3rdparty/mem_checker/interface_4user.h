/*
 * Add by Chen Guodong <sinojelly@gmail.com>
 *
 * This file is included by user projects, can not be used in nvwa itself.
 */

/**
 * @file interface_4user.h
 *
 * Header file for checking leaks caused by unmatched new/delete or malloc/free.
 *
 * If not include this file(or any header of nvwa), you can check memory leak caused by new only, and on windows no file/line info.
 * If include this file, you can check memory leak caused by new and malloc, and it can show file/line on all platforms.
 *
 * Modify nvwa-0.8.2 to support xUnit. 
 *
 * @version 1.0, 2010/9/22
 * @author  sinojelly
 *
 */

#ifndef __INTERFACE_4USER_H__
#define __INTERFACE_4USER_H__

/**
 * NOTE: If some system header cause compiling error, include it(only the header user needed is enough).
 *       So as to avoid include them after new/malloc was replaced by macro, and avoid compiling error.
 */
#ifdef _MSC_VER

#include <crtdbg.h>
#include <stdlib.h>

#ifdef __cplusplus
#include <xdebug>
#include <xlocale>
#endif

#else

#ifdef __cplusplus
#include <string>
#include <algorithm>
#endif

#endif

#ifdef __cplusplus
#include <mem_checker/interface_4cxxuser.h>
#else
#include <mem_checker/interface_4cuser.h>
#endif


#endif

