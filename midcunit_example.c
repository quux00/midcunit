#include "midcunit.h"
 
int foo = 7;
int bar = 4;
 
static char * test_foo() {
  md_assert(foo == foo);
  md_assert(foo == 7);
  return 0;
}

static char * test_bar() {
  md_assert(bar == bar);
  md_assertm("foo should not equal bar", foo != bar);
  return 0;
}

static void all_tests() {
  md_run_test(test_foo);
  md_run_test(test_bar);
}

int main(int argc, char **argv) {
  RUN_TESTS(all_tests);
}
