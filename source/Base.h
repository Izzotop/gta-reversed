/*
    Plugin-SDK (Grand Theft Auto) SHARED header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#define VALIDATE_SIZE(struc, size) static_assert(sizeof(struc) == size, "Invalid structure size of " #struc)
#define VALIDATE_OFFSET(struc, member, offset) \
	static_assert(offsetof(struc, member) == offset, "The offset of " #member " in " #struc " is not " #offset "...")

VALIDATE_SIZE(bool, 1);
VALIDATE_SIZE(char, 1);
VALIDATE_SIZE(short, 2);
VALIDATE_SIZE(int, 4);
VALIDATE_SIZE(float, 4);
VALIDATE_SIZE(long long, 8);

// Basic types for structures describing
typedef int bool32;

#define _IGNORED_
#define _CAN_BE_NULL_

#if (defined(__GNUC__) || defined(__GNUG__) || defined(__clang__))
#define _NOINLINE_
#elif (defined(_MSC_VER))
#define _NOINLINE_ __declspec(noinline)
#else
#define _NOINLINE_
#endif
