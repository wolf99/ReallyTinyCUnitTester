# ReallyTinyCUnitTester
A minimal unit tester for C.

Currently output is to the windows standard output console only.

##Example usage
A test suite is created by coding the tests and a test runner relating to a particular module.

In file test_my_foo.c:

```C
  #include<tester.h>  /* Include the tester. */
  #include<myfoo.h>   /* Include the module to be tested. */
    
  static void set_up(void) { } /* This will be run before every unit test. In this example it does nothing. */
  
  static void tear_down(void) { } /* This will be run after every unit test. In this example it does nothing. */
    
  /* Lets write a quick test... */
  static void unit_test_foo_intialisation(void) {
    foo_object * foo_handle = foo_init(void); /* We want to test the initialisation of the module. */
    TEST_NOT_NULL(foo_handle); /* Check the handle is valid. */
    TEST_EQUAL_INT(foo_handle->some_integer_member, 0); /* Check one of the integer type members holds the correct value. */
    TEST_TRUE(foo_handle->some_boolean_member); /* Check one of the boolean type members  holds the correct value. */
  }
   
  /* Lets write a function to run the test suite for the module under test... */
  void foo_test_suite(void) {
    RUN_TEST(unit_test_foo_intialisation); /* run the test we created above. */
    /* If there were more tests to run on this module they would be added here. */
  }
```

In file test_my_foo.h:

```C
  #ifndef TEST_MY_FOO_H_
  #define TEST_MY_FOO_H_
  void foo_test_suite(void);  /* Make the test suite function public. */
  #endif
```

And in then file containing main() we can call each of the test suites:

```C
  #include<tester.h> /* Include the tester again. */
  #include<test_my_foo.h> /* include our test suite. */
  
  static void set_up(void) { } /* This will be run before every suite. In this example it does nothing. */
  
  static void tear_down(void) { } /* This will be run after every suite. In this example it does nothing. */
  
  int main(int argc, char * argv[]) {
    INIT_TESTER;  /* Initialise the tester. */
    RUN_SUITE(foo_test_suite, "foo"); /* Run the suite we created using the runner, we also give it a pretty string name, "foo" for the results display. */
    /* If there were more suites to run they would be added here. */
    return (0);
  }
```

Thats it!

##Tests
The current tests available consist of the following:

- TEST_TRUE(test); - Passes if `test` evaluates to `true`
- TEST_FALSE(test); - Passes if `test` evaluates to `false`
- TEST_NULL(ptr); - Passes if `ptr` is `NULL`
- TEST_NOT_NULL(ptr); - Passes if `ptr` is not `NULL`
- TEST_EQUAL_INT(x, y); - Passes if `x` is equal to `y`
- TEST_NOT_EQUAL_INT(x, y); - Passes if `x` is not euqal to `y`
- TEST_EQUAL_INT_TOLERANCE(x, y, z); - Passes if `x` is equal to `y` with a tolerance of ±`z`. `x` may be an expression, but `y` and `z` should constants or constant-expressions else side-effects may occur.

##Output
Currently output is solely to the Windows standard output. This can be changed by adding and selecting an `OUTPUT_*` interface to the output selecter at the top of `tester.h`. for an example, please see the `tester.h` file code and comments

