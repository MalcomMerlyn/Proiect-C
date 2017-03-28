#pragma once

#include <limits.h>

#include <Utils.h>

#define MAXSIZE 10000000

/*
 *	Tester errors
 */
#define NOTNUMBER	128
#define STOP		129
#define INVCOMM		130

inline BOOL number(
	char c
)
{
	if ('0' <= c && c <= '9')
		return True;
	return False;
}

inline BOOL space(
	char c
)
{
	if (c == ' ' || c == '\t')
		return True;
	return False;
}

inline BOOL command(
	const char* comm,
	const char* real
)
{
	int c = -1;
	while (real[++c] != '\0' &&
		comm[c] == real[c]
		);
	if (real[c] == '\0' && (comm[c] == '\n' || comm[c] == '\0'))
		return True;
	else
		return False;
}

int readNumber(
	FILE* stream,
	int* elem
)
{
	char c; *elem = 0; char neg = '+'; long long nr = 0;
	while (space(c = (char)fgetc(stream)));
	if (c == '\n')
		return False;
	if (c == '-')
	{
		c = (char)fgetc(stream);
		neg = '-';
	}
	do {
		if (!number(c))
			return NOTNUMBER;
		nr = nr * 10 + (c - '0');
		if (nr > INT_MAX && neg == '+' || nr - 1 > INT_MAX && neg == '-')
			return INVCOMM;
		c = (char)fgetc(stream);
	} while (c != ' ' && c != '\t' && c != '\n' && !feof(stream));
	if (neg == '-')
		*elem = -(int)nr;
	else
		*elem = (int)nr;
	if (c == '\n'  || feof(stream))
		return STOP;
	return True;
}