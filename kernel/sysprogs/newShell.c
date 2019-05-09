/*                    The Quest Operating System
 *  Copyright (C) 2005-2010  Richard West, Boston University
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

#include "syscall.h"
#include <drivers/uart/uart.h>


void
_start ()
{

  char line[80];
  char *command_line_args = line;
  char *p;
  unsigned child_pid;

  while (1) {

    /* The shell prompt */

    uart_puts(">");

    /* Wait for command line input */
    /* --??-- Assume user has entered command via keyboard */

    if (uart_getc (line)) {      /* Got input */
      /* --??-- Parse input and verify it is meaningful */

      if (*line == '\0')
        continue;

      /* Fork new process */
//       if ((child_pid = fork ())) {      /* Parent */

// #if DEBUG
//         for (p = "parent!\n"; *p; p++)
//           putchar (*p);
// #endif
//         /* switch_to( child_pid ); */
//         waitpid (child_pid);
//       } else {                  /* Child */

// #if DEBUG
//         for (p = "child!\n"; *p; p++)
//           putchar (*p);
// #endif
//         exec (line, &command_line_args);

//         /* Got here due to exec failing on an ext2fs_dir call  */
//         for (p = "Error: file not found\n"; *p; p++)
//           putchar (*p);

//         _exit (1);
//       }
    }
  }
}

/* 
 * Local Variables:
 * indent-tabs-mode: nil
 * mode: C
 * c-file-style: "gnu"
 * c-basic-offset: 2
 * End: 
 */

/* vi: set et sw=2 sts=2: */
