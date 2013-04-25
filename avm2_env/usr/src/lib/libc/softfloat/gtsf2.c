/* $NetBSD: gtsf2.c,v 1.1 2000/06/06 08:15:06 bjh21 Exp $ */

/*
 * Written by Ben Harris, 2000.  This file is in the Public Domain.
 */

#include "softfloat-for-gcc.h"
#include "milieu.h"
#include "softfloat.h"

#include <sys/cdefs.h>
__FBSDID("$FreeBSD: src/lib/libc/softfloat/gtsf2.c,v 1.1.22.1.6.1 2010/12/21 17:09:25 kensmith Exp $");

flag __gtsf2(float32, float32);

flag
__gtsf2(float32 a, float32 b)
{

	/* libgcc1.c says a > b */
	return float32_lt(b, a);
}
