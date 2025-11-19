/*
 * Copyright (c) 2000-2019 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 *
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */
 
/*
 */
 
/*
 * Bit manipulation functions
 */
#define mask(width)                     (width >= 64 ? -1ULL : (BIT(width) - 1))
#define extract(x, shift, width)        ((((uint64_t)(x)) >> (shift)) & mask(width))
#define bits(x, hi, lo)                 extract((x), (lo), (hi) - (lo) + 1)

#define bit_assign(x, b, e)             ((x) = (((x) & ~BIT(b))) | ((((uint64_t) (!!(e)))) << (b)))
#define bit_set(x, b)                   ((x) |= BIT(b))
#define bit_clear(x, b)                 ((x) &= ~BIT(b))
#define bit_test(x, b)                  ((bool)((x) & BIT(b)))

inline static uint64_t
bit_ror64(uint64_t bitmap, uint n)
{
	return __builtin_rotateright64(bitmap, n);
}

inline static uint64_t
bit_rol64(uint64_t bitmap, uint n)
{
	return __builtin_rotateleft64(bitmap, n);
}

/* Non-atomically clear the bit and returns whether the bit value was changed */
#define bit_clear_if_set(bitmap, bit) \
({ \
	int _n = (bit); \
	__auto_type _map = &(bitmap); \
	bool _bit_is_set = bit_test(*_map, _n); \
	bit_clear(*_map, _n); \
	_bit_is_set; \
})

/* Non-atomically set the bit and returns whether the bit value was changed */
#define bit_set_if_clear(bitmap, bit) \
({ \
	int _n = (bit); \
	__auto_type _map = &(bitmap); \
	bool _bit_is_set = bit_test(*_map, _n); \
	bit_set(*_map, _n); \
	!_bit_is_set; \
})

/* If n is a power of 2, bit_log2(n) == bit_floor(n) == bit_ceiling(n) */
#define bit_log2(n)             bit_floor((uint64_t)(n))

typedef uint64_t                bitmap_t;

#define BITMAP_LEN(n)   (((uint)(n) + 63) >> 6)         /* Round to 64bit bitmap_t */
#define BITMAP_SIZE(n)  (size_t)(BITMAP_LEN(n) << 3)            /* Round to 64bit bitmap_t, then convert to bytes */
#define bitmap_bit(n)   bits(n, 5, 0)
#define bitmap_index(n) bits(n, 63, 6)
