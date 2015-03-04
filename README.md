# ReallyTinyCUnitTester
A minimal unit tester for C.

Currently output is to the windows standard output console only.

##Example usage
A test suite is created by coding the tests and a test runner relating to a particular module.

In file test_my_foo.c:

  #include<tester.h>  /* Include the tester */
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
   
  /* Lets write a test runner... */
  void foo_test_runner(void) {
    RUN_TEST(unit_test_foo_intialisation); /* run the test we created above. */
    /* If there were more tests to run they would be added here. */
  }

In file test_my_foo.h:

  #ifndef TEST_MY_FOO_H_
  #define TEST_MY_FOO_H_
  void foo_test_runner(void);
  #endif

And in then file containing main() we can call each of the test suites:

  #include<tester.h> /* Include the tester again. */
  #include<test_my_foo.h> /* include our test suite. */
  
  static void set_up(void) { } /* This will be run before every suite. In this example it does nothing. */
  
  static void tear_down(void) { } /* This will be run after every suite. In this example it does nothing. */
  
  int main(int argc, char * argv[]) {
    INIT_TESTER;  /* Initialise the tester. */
    RUN_SUITE(foo_test_runner, "foo"); /* Run the suite we created using the runner, we also give it a pretty string name, "foo" for the results display. */
    /* If there were more suites to run they would be added here. */
    return (0);
  }

Thats it!
