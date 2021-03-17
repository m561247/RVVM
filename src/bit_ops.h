/*
bit_ops.h - bit operations functions
Copyright (C) 2021  Mr0maks <mr.maks0443@gmail.com>
                    LekKit <github.com/LekKit>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef RISCV_BIT_OPS_H
#define RISCV_BIT_OPS_H

#include <stdint.h>
#include <stdbool.h>

// Simple math operations (sign-extend int bits, etc) for internal usage
// this entire header is cursed (though everything optimizes fine)

/*
* Sign-extend bits in the lower part of uint32_t into signed int32_t
* usage:
*     int32_t ext = sign_extend(val, 20);
*
*     [ext is now equal to signed lower 20 bits of val]
*/
inline int32_t sign_extend(uint32_t val, uint32_t bits)
{
    return ((int32_t)(val << (32 - bits))) >> (32 - bits);
}

// Generate bitmask of given size
inline uint32_t bit_mask(uint32_t count)
{
    return 0xFFFFFFFF >> (32 - count);
}

// Cut N bits from val at given position (from lower bit)
inline uint32_t bit_cut(uint32_t val, uint32_t pos, uint32_t count)
{
    return (val >> pos) & bit_mask(count);
}

// Replace N bits in val at given position (from lower bit) by p
inline uint32_t bit_replace(uint32_t val, uint32_t pos, uint32_t bits, uint32_t p)
{
    return (val & (~(bit_mask(bits) << pos))) | ((p & bit_mask(bits)) << pos);
}

// Check if Nth bit of val is 1
inline bool bit_check(uint32_t val, uint32_t pos)
{
    return (val >> pos) & 0x1;
}

// Reverse N bits in val (from lower bit), remaining bits are zero
inline uint32_t bit_reverse(uint32_t val, uint32_t bits)
{
    uint32_t ret = 0;

    for (uint32_t i=0; i<bits; ++i) {
        ret <<= 1;
        ret |= val & 0x1;
        val >>= 1;
    }

    return ret;
}

#endif
