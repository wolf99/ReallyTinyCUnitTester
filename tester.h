/*   Copyright 2014 Toby Mole
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */
#ifndef TESTER_H_
#define TESTER_H_
	#include <stdio.h>
	#ifdef __cplusplus
		extern "C" {
	#endif
	int suite_fail; /* Count of tests failed within the current suite. */
	int test_fail;  /* Total count of all failed tests. */
	/* ======= SELECT THE OUTPUT INTERFACE TO USE. ======= */
	#define OUTPUT_STD_IO_WINDOWS /* Comment this out to use a different output. */
	//#define OUTPUT_CSV /* Un-comment this to use this output. This is shown as an example only and is not yet implemented. */
	/* ======= IMPLEMENT THE OUTPUT INTERFACES. ======= */
	#if defined(OUTPUT_STD_IO_WINDOWS)
		#include <windows.h>
		HANDLE hConsole;    /* Handle for windows standard output console. */
		#define OUTPUT_INIT { \
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE); \
			/* Set the test colour to the default. */ \
			SetConsoleTextAttribute(hConsole, 7); \
		}
		#define OUTPUT_SUITE_START(suite_name) { \
			/* Print out a notification of the start of the suite. */ \
			printf("\nRunning %s test suite\n", (suite_name)); \
		}
		#define OUTPUT_SUITE_PASS(suite_name) { \
			/* Set the text colour to green. */ \
			SetConsoleTextAttribute(hConsole, 10); \
			/* Print out a suite passed notification. */ \
			printf("Yay, all tests passed!\n"); \
			/* Set the text colour back to the default. */ \
			SetConsoleTextAttribute(hConsole, 7); \
		}
		#define OUTPUT_SUITE_FAIL(suite_name) {}
		#define OUTPUT_TEST_PASS {}
		#define OUTPUT_TEST_FAIL { \
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE); \
			/* Set the text colour to red. */ \
			SetConsoleTextAttribute(hConsole, 12); \
			/* Print out a test failed notification */ \
			printf("# %d. %s failed at ln# %d in %s\n", test_fail, __func__, __LINE__, __FILE__); \
			/* Set the text colour back to the default. */ \
			SetConsoleTextAttribute(hConsole, 7); \
		}
	#elif defined(OUTPUT_CSV) /* A second output interface is added here. */
		/* An example handle variable. */
		FILE * fp;
		/* An example path object-like macro. */
		#define CSV_PATH "C:\\Users\\myname\\testresults.csv"
		/* This is called by TEST_INIT() which should be called by the user at the start of main(). */
		#define OUTPUT_INIT {}
		/* This is called at the start of every suite run, before the set_up(). suite_name is the string argument passed to RUN_SUITE. */
		#define OUTPUT_SUITE_START(suite_name) {}
		/* This is called at the end of a failed suite run, after the tear_down(). suite_name is the string argument passed to RUN_SUITE. */
		#define OUTPUT_SUITE_PASS(suite_name)  {}
		/* This is called at the end of a successful suite run, after the tear_down(). suite_name is the string argument passed to RUN_SUITE. */
		#define OUTPUT_SUITE_FAIL(suite_name)  {}
		/* This is called at the end of a successful test run, after the tear_down(). */
		#define OUTPUT_TEST_PASS {}
		/* This is called at the end of a failed test run, after the tear_down(). */
		#define OUTPUT_TEST_FAIL {}
	#endif
	/* ======= THE TESTER. ======= */
	#define INIT_TESTER { \
		suite_fail = 0; \
		test_fail = 0;  \
		OUTPUT_INIT;    \
	}
	#define RUN_SUITE(suite, suite_name) { \
		OUTPUT_SUITE_START(suite_name); \
		set_up();               \
		suite_fail = 0;         \
		suite();                \
		tear_down();            \
		if (suite_fail == 0) {  \
			OUTPUT_SUITE_PASS(suite_name); \
		} else {                \
			OUTPUT_SUITE_FAIL(suite_name); \
		}                       \
	}
	#define RUN_TEST(test) { \
		set_up();   \
		test();     \
		tear_down();\
	}
	#define TEST_FAIL {     \
		++suite_fail;       \
		++test_fail;        \
		OUTPUT_TEST_FAIL;   \
	}
	#define TEST_PASS { \
		OUTPUT_TEST_PASS; \
	}
	#define TEST_TRUE(test)          {if ((test) != false) { TEST_PASS; } else { TEST_FAIL; }}
	#define TEST_FALSE(test)         {if ((test) == false) { TEST_PASS; } else { TEST_FAIL; }}
	#define TEST_NULL(ptr)           {if ((ptr) == NULL)   { TEST_PASS; } else { TEST_FAIL; }}
	#define TEST_NOT_NULL(ptr)       {if ((ptr) != NULL)   { TEST_PASS; } else { TEST_FAIL; }}
	#define TEST_EQUAL_INT(x, y)     {if ((x) == (y))      { TEST_PASS; } else { TEST_FAIL; }}
	#define TEST_NOT_EQUAL_INT(x, y) {if ((x) != (y))      { TEST_PASS; } else { TEST_FAIL; }}
	#define TEST_EQUAL_INT_TOLERANCE(x, y, z) { \
		int _x = (x), _y = (y), _z = (z); \
		if ((_x <= (_y + _z)) && (_x >= (_y - _z))) { \
			TEST_PASS;  \
		} else {        \
			TEST_FAIL;  \
		}               \
	}
	#define TEST_EQUAL_INT_T(T, x, y) { \
		/* Save values to temp vars */ \
		uintmax_t _x = (x), _y = (y); \
		if (((x) == (y)) /* Check if values are equal*/ \
		   && (sizeof(x) == sizeof(T)) /* Check if type sizes match */ \
		   && (sizeof(y) == sizeof(T)) \
		   && ((x) = -1, (y) = -1, \
				((((T)(-1)) < 0) && ((x) < 0) && ((y) < 0)) /* Check if type signedness match */ \
				|| ((((T)(-1)) > 0) && ((x) > 0) && ((y) > 0)))) \
		{ TEST_PASS; } else { TEST_FAIL; } \
		/* Reset values from temp vars */ \
		(x) = _x, (y) = _y; \
	}
	#define TEST_EQUAL_STRING(s1, s2) { \
		if (!strcmp((s1), (s2))) { TEST_PASS; } else { TEST_FAIL; } \
	}
	#ifdef __cplusplus
		}
	#endif
#endif
