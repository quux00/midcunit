#ifndef MIDCUNIT_H
#define MIDCUNIT_H

#include <stdio.h>

/*
 * midcunit is released under the GNU Lesser General Public License, version 3.0 (LGPL-3.0).
 * Copyright 2011 Michael D. Peterson
 * See the LICENSE file for details of the LGPL license.
 */

/* 
 * midcunit is based upon two other software programs
 * 1. the assert.h header of GNU/Linux glibc 2.13
 * 2. the minunit.h unit test framework from Jera Design:
 *    http://www.jera.com/techinfo/jtns/jtn002.html
 * 
 * Modifications by Michael Peterson
 * + I copied a preprocessor section from assert.h with minor modifications
 *   as described below
 *   _Relative to minut_
 * + Added three variable declarations/initializations
 * + Changed the mu_run_test assert to not return on a failure, since that causes
 *   all other tests after it NOT to run.  Instead it increments the nfails counter
 *   and lets the program proceed to the next test.  It was renamed to md_assertm.
 * + Added three new macro functions
 * + See the README for more complete details
 */

/* Code copied from the GNU/Linux glibc assert.h header 
 * I changed their __ASSERT_FUNCTION to MD_ASSERT_FUNC
 * to avoid any conflicts with the library headers.
 */
# if defined __cplusplus ? __GNUC_PREREQ (2, 6) : __GNUC_PREREQ (2, 4)
#   define MD_ASSERT_FUNC	__PRETTY_FUNCTION__
# else
#  if defined __STDC_VERSION__ && __STDC_VERSION__ >= 199901L
#   define MD_ASSERT_FUNC	__func__
#  else
#   define MD_ASSERT_FUNC	((__const char *) 0)
#  endif
# endif

#define MD_MAX_MSG_LEN 256

/* Variables for use in the macro functions.
 *   These are 'hidden' in the sense that the user does not need to declare or 
 *   reference them in the unit test itself.
 */
int  md_tests_run = 0;        /* number of tests run */
int  md_nfails    = 0;        /* number of tests that have failed */
char md_msg[MD_MAX_MSG_LEN];  /* buffer for internally generated error messages */


/* --- TEST MACRO FUNCTIONS --- */

#define md_run_test(test) do { char *msg = test(); md_tests_run++; if (msg) {md_nfails++; puts(msg); }} while (0)

#define md_assert(test) do { if (!(test)) { snprintf(md_msg, MD_MAX_MSG_LEN, "%s:%d: FAILED assert '%s'", MD_ASSERT_FUNC, __LINE__, #test); return md_msg;} } while (0)

#define md_assertm(msg, test) do { if (!(test)) { snprintf(md_msg, MD_MAX_MSG_LEN, "%s:%d: %s: FAILED assert '%s'", MD_ASSERT_FUNC, __LINE__, msg, #test); return md_msg;} } while (0)

#define RUN_TESTS(f) do { f(); if (md_nfails == 0) puts("ALL TESTS PASSED"); \
                               else printf("%d TEST%sFAILED\n", md_nfails, (md_nfails == 1 ? " " : "S ")); \
                               printf("Tests run: %d\n", md_tests_run); return md_nfails; } while (0)

#endif
