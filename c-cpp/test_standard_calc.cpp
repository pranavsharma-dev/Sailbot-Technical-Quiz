#include "stdio.h"
#include "cutest/CuTest.h"
#include "standard_calc.h"

/**************** Tests for bound_to_180() *******************/
void test_bound_basic1(CuTest *tc) {
    CuAssertDblEquals(tc, 0, bound_to_180(0), 0.0001);
}


void test_bound_already_in_bounds(CuTest *tc) {
    CuAssertDblEquals(tc, 135.0, bound_to_180(135), 0.0001);
    CuAssertDblEquals(tc, -90.0, bound_to_180(-90), 0.0001);
    CuAssertDblEquals(tc, 180.0, bound_to_180(180), 0.0001);
}

void test_bound_positive_wrapping(CuTest *tc) {
    CuAssertDblEquals(tc, -160.0, bound_to_180(200), 0.0001);
    CuAssertDblEquals(tc, 0.0, bound_to_180(360), 0.0001);
    CuAssertDblEquals(tc, 90.0, bound_to_180(450), 0.0001);
}


void test_bound_negative_wrapping(CuTest *tc) {
    CuAssertDblEquals(tc, 160.0, bound_to_180(-200), 0.0001);
    CuAssertDblEquals(tc, 0.0, bound_to_180(-360), 0.0001);
}

void test_bound_boundaries(CuTest *tc) {
    CuAssertDblEquals(tc, -180.0, bound_to_180(-180), 0.0001);
    CuAssertDblEquals(tc, 0.0, bound_to_180(720), 0.0001);
}


/**************** Tests for is_angle_between() *******************/
void test_between_basic1(CuTest *tc) {
    CuAssertTrue(tc, is_angle_between(0, 1, 2));
}


void test_between_docstring_examples(CuTest *tc) {
    CuAssertTrue(tc, is_angle_between(0, 45, 90));
    CuAssertIntEquals(tc, 0, is_angle_between(45, 90, 270));
}

void test_between_wrap_around(CuTest *tc) {
    CuAssertTrue(tc, is_angle_between(170, -180, -170));
    CuAssertTrue(tc, is_angle_between(-45, 0, 45));
    CuAssertTrue(tc, is_angle_between(170, 180, -170));
}

void test_between_boundaries(CuTest *tc) {
    CuAssertTrue(tc, is_angle_between(0, 0, 90));
    CuAssertTrue(tc, is_angle_between(0, 90, 90));
    CuAssertTrue(tc, is_angle_between(45, 45, 45));
}

void test_between_unbounded_inputs(CuTest *tc) {
    CuAssertTrue(tc, is_angle_between(0, 405, 90));
    CuAssertTrue(tc, is_angle_between(360, 45, 450));
}

void test_between_reflex_angle(CuTest *tc) {
    CuAssertIntEquals(tc, 0, is_angle_between(0, 180, 90));
    CuAssertIntEquals(tc, 0, is_angle_between(0, -90, 90));
}

int main(int argc, char const *argv[]) {
    CuString *output = CuStringNew();
    CuSuite *suite = CuSuiteNew();

    // bound_to_180 tests
    SUITE_ADD_TEST(suite, test_bound_basic1);
    SUITE_ADD_TEST(suite, test_bound_already_in_bounds);
    SUITE_ADD_TEST(suite, test_bound_positive_wrapping);
    SUITE_ADD_TEST(suite, test_bound_negative_wrapping);
    SUITE_ADD_TEST(suite, test_bound_boundaries);

    // is_angle_between tests
    SUITE_ADD_TEST(suite, test_between_basic1);
    SUITE_ADD_TEST(suite, test_between_docstring_examples);
    SUITE_ADD_TEST(suite, test_between_wrap_around);
    SUITE_ADD_TEST(suite, test_between_boundaries);
    SUITE_ADD_TEST(suite, test_between_unbounded_inputs);
    SUITE_ADD_TEST(suite, test_between_reflex_angle);

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);

    return suite->failCount > 0 ? 1 : 0;
}
