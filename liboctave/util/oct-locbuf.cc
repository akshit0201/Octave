/*

Copyright (C) 2008-2017 Jaroslav Hajek

This file is part of Octave.

Octave is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

Octave is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Octave; see the file COPYING.  If not, see
<http://www.gnu.org/licenses/>.

*/

#if defined (HAVE_CONFIG_H)
#  include "config.h"
#endif

#include <iostream>

#include "lo-error.h"
#include "oct-locbuf.h"

// FIXME: Maybe we should querying for available physical memory?

#if ! defined (OCTAVE_LOCBUF_CHUNKSIZE_MB)
#  define OCTAVE_LOCBUF_CHUNKSIZE_MB 32
#endif

namespace octave
{
// Each chunk will be at least this big.

  const size_t octave::chunk_buffer::chunk_size =
    static_cast<size_t> (OCTAVE_LOCBUF_CHUNKSIZE_MB) << 20;

  char *chunk_buffer::top = nullptr;
  char *chunk_buffer::chunk = nullptr;
  size_t chunk_buffer::left = 0;
  size_t chunk_buffer::active = 0;

  chunk_buffer::chunk_buffer (size_t size) : cnk (0), dat (0)
  {
    // Alignment mask.  The size of double or long int, whichever is
    // greater.  All data will be aligned to this size.  If it's not
    // enough for a type, that type should not be declared as POD.

    static const size_t align_mask = (sizeof (long) < sizeof (double)
                                      ? sizeof (double)
                                      : sizeof (long)) - 1;

    // Always allocate, even for zero-size buffers so that local buffers
    // always have valid addresses, same as for directly using operator
    // new.

    active++;

    // Align size.  Note that size_t is unsigned, so size-1 must correctly
    // wrap around.

    size = ((size - 1) | align_mask) + 1;

    if (size > left)
      {
        // Big buffers (> 1/8 chunk) will be allocated as stand-alone and
        // won't disrupt the chain.

        if (size > chunk_size >> 3)
          {
            // Use new [] to get std::bad_alloc if out of memory.

            dat = new char [size];
            return;
          }

        dat = new char [chunk_size];
        chunk = top = dat;
        left = chunk_size;
      }

    // Now allocate memory from the chunk and update state.

    cnk = chunk;
    dat = top;
    left -= size;
    top += size;
  }

  chunk_buffer::~chunk_buffer (void)
  {
    active--;

    if (cnk == chunk)
      {
        // Our chunk is still the active one.  Just restore the state.

        left += top - dat;
        top = dat;
      }
    else
      {
        if (cnk)
          {
            // Responsible for deletion.

            delete [] chunk;
            chunk = cnk;
            top = dat;

            // FIXME: the following calcuation of remaining data will
            //        only work if each chunk has the same chunk_size.

            left = chunk_size - (dat - cnk);
          }
        else
          {
            // We were a stand-alone buffer.

            delete [] dat;
          }
      }
  }

  // Clear the final chunk of allocated memory.

  void
  chunk_buffer::clear (void)
  {
    if (active == 0)
      {
        delete [] chunk;
        chunk = 0;
        top = 0;
        left = 0;
      }
    else
      {
        // FIXME: Doesn't this situation represent a programming error of
        // some kind?  If so, maybe this should be a fatal error?

        (*current_liboctave_warning_with_id_handler)
          ("Octave:local-buffer-inconsistency",
           "chunk_buffer::clear: %d active allocations remain!",
           active);
      }
  }
}
