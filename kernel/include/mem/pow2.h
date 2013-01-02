/*                    The Quest Operating System
 *  Copyright (C) 2005-2012  Richard West, Boston University
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _POW2_H_
#define _POW2_H_
#include "types.h"

void pow2_init (void);
int pow2_alloc (uint32 size, uint8 ** ptr);
void pow2_free (uint8 * ptr);

static inline void* kmalloc(uint32_t size) {
  uint8* temp;
  pow2_alloc(size, &temp);
  return temp;
}

static inline void kfree(void* ptr)
{
  pow2_free(ptr);
}

static inline void* kzalloc(uint32_t size) {
  void* temp = kmalloc(size);
  if(temp) {
    memset(temp, 0, size);
  }
  return temp;
}

#endif

/* 
 * Local Variables:
 * indent-tabs-mode: nil
 * mode: C
 * c-file-style: "gnu"
 * c-basic-offset: 2
 * End: 
 */

/* vi: set et sw=2 sts=2: */
