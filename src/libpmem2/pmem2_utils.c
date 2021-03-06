/*
 * Copyright 2019, Intel Corporation
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in
 *       the documentation and/or other materials provided with the
 *       distribution.
 *
 *     * Neither the name of the copyright holder nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * pmem2_utils.c -- libpmem2 utilities functions
 */

#include <errno.h>
#include "alloc.h"
#include "libpmem2.h"
#include "out.h"
#include "pmem2_utils.h"
#include "util.h"

/*
 * pmem2_malloc -- allocate buffer and handle error
 */
void *
pmem2_malloc(size_t size, int *err)
{
	void *ptr = Malloc(size);
	*err = 0;

	if (ptr == NULL) {
		ERR("!malloc(%zu)", size);
		*err = PMEM2_E_ERRNO;
	}

	return ptr;
}

int
pmem2_err_to_errno(int err)
{
	if (err > 0)
		FATAL("positive error code is a bug in libpmem2");

	err = -err;
	if (err < PMEM2_E_UNKNOWN)
		return err;

	return EINVAL;
}

#ifdef _WIN32
/*
 * converts windows error codes to pmem2 error
 */
int
pmem2_lasterror_to_err()
{
	int err = util_lasterror_to_errno(GetLastError());

	if (err == -1)
		return PMEM2_E_UNKNOWN;

	return -err;
}
#endif
