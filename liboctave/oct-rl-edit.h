/*

Copyright (C) 2000 John W. Eaton

This file is part of Octave.

Octave is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2, or (at your option) any
later version.

Octave is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with Octave; see the file COPYING.  If not, write to the Free
Software Foundation, 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

#if !defined (octave_rl_edit_h)
#define octave_rl_edit_h 1

typedef void (*rl_startup_hook_fcn_ptr) (void);

typedef void (*rl_event_hook_fcn_ptr) (void);

typedef int (*rl_fcn_ptr) (int, int);

typedef char ** (*rl_attempted_completion_fcn_ptr) (const char *, int, int);

typedef char * (*rl_completer_fcn_ptr) (const char *, int);

#ifdef __cplusplus
extern "C"
{
#endif

extern int octave_rl_screen_height (void);

extern int octave_rl_screen_width (void);

extern void octave_set_rl_blink_matching_paren_flag (int);

extern int octave_get_rl_blink_matching_paren_flag (void);

extern void octave_rl_init (void);

extern void octave_rl_clear_screen (void);

extern void octave_rl_resize_terminal (void);

extern void octave_rl_restore_terminal_state (void);

extern void octave_rl_insert_text (const char *);

extern void octave_rl_newline (void);

extern void octave_rl_clear_undo_list (void);

extern void octave_rl_set_name (const char *);

extern char *octave_rl_readline (const char *);

extern void octave_rl_set_input_stream (FILE *);

extern FILE *octave_rl_get_input_stream (void);

extern void octave_rl_set_output_stream (FILE *);

extern FILE *octave_rl_get_output_stream (void);

extern void octave_rl_read_init_file (const char *);

extern void octave_rl_set_basic_quote_characters (const char *);

extern void octave_rl_set_completion_append_character (char);

extern void
octave_rl_set_completion_function (rl_attempted_completion_fcn_ptr);

extern void octave_rl_set_startup_hook (rl_startup_hook_fcn_ptr);

extern rl_startup_hook_fcn_ptr octave_rl_get_startup_hook (void);

extern void octave_rl_set_event_hook (rl_event_hook_fcn_ptr f);

extern rl_event_hook_fcn_ptr octave_rl_get_event_hook (void);

extern char **
octave_rl_completion_matches (const char *, rl_completer_fcn_ptr);

extern char octave_rl_prompt_start_ignore (void);

extern char octave_rl_prompt_end_ignore (void);

extern void octave_rl_add_defun (const char *, rl_fcn_ptr, char);

extern void octave_rl_set_terminal_name (const char *);

extern void octave_rl_initialize (void);

extern int octave_rl_history_search_forward (int, int);

extern int octave_rl_history_search_backward (int, int);

extern char octave_rl_ctrl (char);

extern char octave_rl_meta (char);

#ifdef __cplusplus
}
#endif

#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
