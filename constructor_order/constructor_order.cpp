/*-
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2018 Alex Richardson
 * All rights reserved.
 *
 * This software was developed by SRI International and the University of
 * Cambridge Computer Laboratory under DARPA/AFRL contract FA8750-10-C-0237
 * ("CTSRD"), as part of the DARPA CRASH research programme.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <cstdio>
#include <iostream>

// This file tests that iostream + constructors/destructors works


#ifndef _VADDR_T_DECLARED	// To allow running this on Linux/MacOS
typedef size_t vaddr_t;
#endif

#ifdef VALID_SHLIB
#define FILE_KIND "lib: "
#define GLOBAL_CLASS Class_Lib
#else
#define FILE_KIND "exe: "
#define GLOBAL_CLASS Class_Exe
#endif

#define __STRINGIFY(x) #x
#define STRINGIFY(x) __STRINGIFY(x)

class GLOBAL_CLASS {
public:
	GLOBAL_CLASS() {
		fprintf(stderr, FILE_KIND STRINGIFY(GLOBAL_CLASS) " ctor called\n");
	}
	~GLOBAL_CLASS() {
		fprintf(stderr, FILE_KIND STRINGIFY(GLOBAL_CLASS) " dtor called\n");
	}
};

GLOBAL_CLASS x;

#define INIT_FINI_ARRAY_ENTRY(name, func) \
	static void func() { fprintf (stderr, FILE_KIND "%s()\n", __func__); }	\
	extern const vaddr_t func##_entry_1					\
	__attribute__ ((section (name), aligned (sizeof (vaddr_t))));		\
	const vaddr_t func##_entry_1						\
	__attribute__ ((section (name), aligned (sizeof (vaddr_t)))) =		\
	(vaddr_t)&func;

INIT_FINI_ARRAY_ENTRY(".init_array", initarray);
INIT_FINI_ARRAY_ENTRY(".fini_array", finiarray);


// Add some entries with priorities:

INIT_FINI_ARRAY_ENTRY(".fini_array.1", finiarray_1);
INIT_FINI_ARRAY_ENTRY(".fini_array.99", finiarray_99);

INIT_FINI_ARRAY_ENTRY(".init_array.1", initarray_1);
INIT_FINI_ARRAY_ENTRY(".init_array.99", initarray_99);


// Now try .ctors and .dtors:
INIT_FINI_ARRAY_ENTRY(".ctors", ctors);
INIT_FINI_ARRAY_ENTRY(".dtors", dtors);
INIT_FINI_ARRAY_ENTRY(".ctors.99", ctors_99);
INIT_FINI_ARRAY_ENTRY(".ctors.1", ctors_1);
INIT_FINI_ARRAY_ENTRY(".dtors.99", dtors_99);
INIT_FINI_ARRAY_ENTRY(".dtors.1", dtors_1);


extern void exported_function();

#ifndef VALID_SHLIB
// .preinit_array is only allowed in executables
INIT_FINI_ARRAY_ENTRY(".preinit_array", preinitarray);
INIT_FINI_ARRAY_ENTRY(".preinit_array.1", preinitarray_1);
INIT_FINI_ARRAY_ENTRY(".preinit_array.99", preinitarray_99);

int
main()
{
	const char hello[] = "Hello World!";

	fprintf(stderr, "C printf: %s\n", hello);
	fflush(stdout);

	std::cerr << "std::cerr: " << hello << std::endl;
	std::cerr.flush();

	//std::cout << "std::cout: " << hello << std::endl;
	//std::cout.flush();

#ifdef USE_SHLIB
	exported_function();
#endif

	return (0);
}
#else

void exported_function() {
	printf("Function in shlib called!\n");
}
#endif

