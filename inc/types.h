#ifndef TYPES_H
#define TYPES_H

#define bool	int
#define true	1
#define false	0

#ifndef NULL
#define NULL ((void *)0)
#endif

typedef	unsigned char		uint8_t;
typedef	unsigned short		uint16_t;
typedef	unsigned int		uint32_t;
typedef	unsigned long long	uint64_t;

typedef	signed char			int8_t;
typedef	signed short		int16_t;
typedef	signed int			int32_t;
typedef	signed long long	int64_t;

typedef	char				*va_list;
#define	va_start(ap,parmn)	(void)((ap) = (char*)(&(parmn) + 1))
#define	va_end(ap) 			(void)((ap) = 0)
#define	va_arg(ap, type)	(((type*)((ap) = ((ap) + sizeof(type))))[-1])

#endif
