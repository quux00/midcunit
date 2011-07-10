#include "minmax.h"
#include "midcunit.h"
 

/* optional additional setup teardown methods, if needed */
static void initial_setup(void);
static void setup(void);
static void teardown(void);
static void final_teardown(void);

/* --- TESTS --- */

static char * test_max(void) {
  md_assert(max(10,20) == 20);    /* will fail */
  md_assert(max(-10,-20) == -10); /* will not execute */
  return 0;
}

static char * test_min(void) {
  md_assert(min(10,20) == 10);
  md_assert(min(-10,-20) == -20);
  return 0;
}

/* --- RUN ALL TESTS --- */

static void all_tests(void) {
  initial_setup();

  setup();
  md_run_test(test_max);
  teardown();

  setup();
  md_run_test(test_min);
  teardown();

  final_teardown();  /* see note below as to why this should be here */
}

int main() {
  RUN_TESTS(all_tests);
  /* note - RUN_TESTS has an embedded return, so nothing after it will run
     so put any "final_teardown" type methods in the all_tests() method */
}

/* --- HELPER METHODS --- */

static void initial_setup(void) {
  puts("ISU");
}

static void setup(void) {
  puts("SU");
}

static void teardown(void) {
  puts("TD");
}

static void final_teardown(void) {
  puts("FTD");
}
