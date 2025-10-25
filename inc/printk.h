#ifndef PRINTK_H
#define PRINTK_H

#include "writek.h"
#include "stdarg.h"
#include "libc.h"

int printk(int color, const char *s, ...);

enum LEVEL
{
	KERN_EMERG,
	KERN_ALERT,
	KERN_CRIT,
	KERN_ERR,
	KERN_WARNING,
	KERN_NOTICE,
	KERN_INFO,
	KERN_DEBUG
};

#endif
