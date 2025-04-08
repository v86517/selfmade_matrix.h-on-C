#include <check.h>

#include "s21_matrix.h"

START_TEST(create1) {
  matrix_t test;
  ck_assert_uint_eq(s21_create_matrix(7, 8, &test), OK);
  s21_remove_matrix(&test);
}
END_TEST

START_TEST(create2) {
  matrix_t test;
  ck_assert_uint_eq(s21_create_matrix(-8, 9, &test), MATERROR);
}
END_TEST

START_TEST(create3) {
  matrix_t test;
  ck_assert_uint_eq(s21_create_matrix(5, 0, &test), MATERROR);
}
END_TEST

START_TEST(remove1) {
  matrix_t test;
  s21_create_matrix(7, 8, &test);
  s21_remove_matrix(&test);
  ck_assert_int_eq(test.rows, 0);
  ck_assert_int_eq(test.columns, 0);
}
END_TEST

START_TEST(equal1) {
  matrix_t test1, test2;
  s21_create_matrix(3, 3, &test1);
  s21_create_matrix(3, 2, &test2);
  ck_assert_int_eq(s21_eq_matrix(&test1, &test2), FAILURE);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);
}
END_TEST

START_TEST(equal2) {
  matrix_t test1, test2;
  s21_create_matrix(3, 3, &test1);
  s21_create_matrix(2, 3, &test2);
  ck_assert_int_eq(s21_eq_matrix(&test1, &test2), FAILURE);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);
}
END_TEST

START_TEST(equal3) {
  matrix_t test1, test2;
  s21_create_matrix(3, 3, &test1);
  s21_create_matrix(3, 3, &test2);

  double fill_test1[] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};
  double fill_test2[] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};
  fill(&test1, fill_test1);
  fill(&test2, fill_test2);

  ck_assert_int_eq(s21_eq_matrix(&test1, &test2), SUCCESS);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);
}
END_TEST

START_TEST(equal4) {
  matrix_t test1, test2;
  s21_create_matrix(3, 3, &test1);
  s21_create_matrix(3, 3, &test2);

  double fill_test1[] = {1.1, 2.123456, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};
  double fill_test2[] = {1.1, 2.123457, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};
  fill(&test1, fill_test1);
  fill(&test2, fill_test2);

  ck_assert_int_eq(s21_eq_matrix(&test1, &test2), FAILURE);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);
}
END_TEST

START_TEST(equal5) {
  matrix_t test1, test2;
  s21_create_matrix(3, 3, &test1);
  s21_create_matrix(3, 3, &test2);
  test1.rows = -3;

  ck_assert_int_eq(s21_eq_matrix(&test1, &test2), FAILURE);
  test1.rows = 3;
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);
}
END_TEST

START_TEST(sum1) {
  matrix_t test1, test2, truth, result;
  s21_create_matrix(4, 3, &test1);
  s21_create_matrix(4, 3, &test2);
  s21_create_matrix(4, 3, &truth);

  double fill_test1[] = {1.1, 2.2, 3.3, 4.4,  5.5,  6.6,
                         7.7, 8.8, 9.9, 10.0, 11.1, 12.2};
  double fill_test2[] = {12.2, 11.1, 10.0, 9.9, 8.8, 7.7,
                         6.6,  5.5,  4.4,  3.3, 2.2, 1.1};
  double fill_truth[] = {13.3, 13.3, 13.3, 14.3, 14.3, 14.3,
                         14.3, 14.3, 14.3, 13.3, 13.3, 13.3};
  fill(&test1, fill_test1);
  fill(&test2, fill_test2);
  fill(&truth, fill_truth);

  ck_assert_uint_eq(s21_sum_matrix(&test1, &test2, &result), OK);
  ck_assert_uint_eq(s21_eq_matrix(&result, &truth), SUCCESS);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);
  s21_remove_matrix(&truth);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sum2) {
  matrix_t test1, test2, result;
  s21_create_matrix(3, 3, &test1);
  s21_create_matrix(3, 2, &test2);

  double fill_test1[] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};
  double fill_test2[] = {6.6, 5.5, 4.4, 3.3, 2.2, 1.1};
  fill(&test1, fill_test1);
  fill(&test2, fill_test2);

  ck_assert_uint_eq(s21_sum_matrix(&test1, &test2, &result), CALCERROR);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);
}
END_TEST

START_TEST(sum3) {
  matrix_t test1, test2, result;
  s21_create_matrix(4, 3, &test1);
  s21_create_matrix(4, 3, &test2);
  test1.rows = -4;

  ck_assert_uint_eq(s21_sum_matrix(&test1, &test2, &result), MATERROR);
  test1.rows = 4;
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);
}
END_TEST

START_TEST(sum4) {
  matrix_t test1, test2, result;
  s21_create_matrix(4, 3, &test1);
  s21_create_matrix(4, 3, &test2);
  test2.rows = -4;

  ck_assert_uint_eq(s21_sum_matrix(&test1, &test2, &result), MATERROR);
  test2.rows = 4;
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);
}
END_TEST

START_TEST(sub1) {
  matrix_t test1, test2, truth, result;
  s21_create_matrix(4, 3, &test1);
  s21_create_matrix(4, 3, &test2);
  s21_create_matrix(4, 3, &truth);

  double fill_test1[] = {1.1, 2.2, 3.3, 4.4,  5.5,  6.6,
                         7.7, 8.8, 9.9, 10.0, 11.1, 12.2};
  double fill_test2[] = {12.2, 11.1, 10.0, 9.9, 8.8, 7.7,
                         6.6,  5.5,  4.4,  3.3, 2.2, 1.1};
  double fill_truth[] = {-11.1, -8.9, -6.7, -5.5, -3.3, -1.1,
                         1.1,   3.3,  5.5,  6.7,  8.9,  11.1};

  fill(&test1, fill_test1);
  fill(&test2, fill_test2);
  fill(&truth, fill_truth);

  ck_assert_uint_eq(s21_sub_matrix(&test1, &test2, &result), OK);
  ck_assert_uint_eq(s21_eq_matrix(&result, &truth), SUCCESS);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);
  s21_remove_matrix(&truth);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sub2) {
  matrix_t test1, test2, result;
  s21_create_matrix(3, 3, &test1);
  s21_create_matrix(3, 2, &test2);

  double fill_test1[] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};
  double fill_test2[] = {6.6, 5.5, 4.4, 3.3, 2.2, 1.1};
  fill(&test1, fill_test1);
  fill(&test2, fill_test2);

  ck_assert_uint_eq(s21_sub_matrix(&test1, &test2, &result), CALCERROR);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);
}
END_TEST

START_TEST(sub3) {
  matrix_t test1, test2, result;
  s21_create_matrix(4, 3, &test1);
  s21_create_matrix(4, 3, &test2);
  test1.rows = -4;

  ck_assert_uint_eq(s21_sub_matrix(&test1, &test2, &result), MATERROR);
  test1.rows = 4;
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);
}
END_TEST

START_TEST(sub4) {
  matrix_t test1, test2, result;
  s21_create_matrix(4, 3, &test1);
  s21_create_matrix(4, 3, &test2);
  test2.rows = -4;

  ck_assert_uint_eq(s21_sub_matrix(&test1, &test2, &result), MATERROR);
  test2.rows = 4;
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);
}
END_TEST

START_TEST(mult_number1) {
  matrix_t test1, truth, result;
  s21_create_matrix(4, 3, &test1);
  s21_create_matrix(4, 3, &truth);

  double fill_test1[] = {1.1, 2.2, 3.3, 4.4,  5.5,  6.6,
                         7.7, 8.8, 9.9, 10.0, 11.1, 12.2};

  double fill_truth[] = {2.2,  4.4,  6.6,  8.8,  11.0, 13.2,
                         15.4, 17.6, 19.8, 20.0, 22.2, 24.4};
  fill(&test1, fill_test1);
  fill(&truth, fill_truth);

  ck_assert_uint_eq(s21_mult_number(&test1, 2, &result), OK);
  ck_assert_uint_eq(s21_eq_matrix(&result, &truth), SUCCESS);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&truth);
  s21_remove_matrix(&result);
}

END_TEST

START_TEST(mult_number2) {
  matrix_t test1, truth, result;
  s21_create_matrix(4, 3, &test1);
  s21_create_matrix(4, 3, &truth);

  double fill_test1[] = {1.1, 2.2, 3.3, 4.4,  5.5,  6.6,
                         7.7, 8.8, 9.9, 10.0, 11.1, 12.2};

  double fill_truth[] = {-2.2,  -4.4,  -6.6,  -8.8,  -11.0, -13.2,
                         -15.4, -17.6, -19.8, -20.0, -22.2, -24.4};
  fill(&test1, fill_test1);
  fill(&truth, fill_truth);

  ck_assert_uint_eq(s21_mult_number(&test1, -2, &result), OK);
  ck_assert_uint_eq(s21_eq_matrix(&result, &truth), SUCCESS);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&truth);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(mult_number3) {
  matrix_t test1, result;
  s21_create_matrix(4, 3, &test1);
  s21_create_matrix(4, 3, &result);
  test1.rows = -2;

  ck_assert_uint_eq(s21_mult_number(&test1, 7, &result), MATERROR);
  test1.rows = 4;
  s21_remove_matrix(&test1);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(mult_matrix1) {
  matrix_t test1, test2, truth, result;
  s21_create_matrix(3, 3, &test1);
  s21_create_matrix(3, 3, &test2);
  s21_create_matrix(3, 3, &truth);

  double fill_test1[] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};
  double fill_test2[] = {9.9, 8.8, 7.7, 6.6, 5.5, 4.4, 3.3, 2.2, 1.1};
  double fill_truth[] = {36.3,  29.04,  21.78,  101.64, 83.49,
                         65.34, 166.98, 137.94, 108.9};

  fill(&test1, fill_test1);
  fill(&test2, fill_test2);
  fill(&truth, fill_truth);

  ck_assert_uint_eq(s21_mult_matrix(&test1, &test2, &result), OK);
  ck_assert_uint_eq(s21_eq_matrix(&result, &truth), SUCCESS);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);
  s21_remove_matrix(&truth);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(mult_matrix2) {
  matrix_t test1, test2, truth, result;
  s21_create_matrix(4, 3, &test1);
  s21_create_matrix(3, 4, &test2);
  s21_create_matrix(4, 4, &truth);

  double fill_test1[] = {1.1, 2.2, 3.3, 4.4,  5.5,  6.6,
                         7.7, 8.8, 9.9, 10.0, 11.1, 12.2};
  double fill_test2[] = {12.2, 11.1, 10.0, 9.9, 8.8, 7.7,
                         6.6,  5.5,  4.4,  3.3, 2.2, 1.1};
  double fill_truth[] = {47.3,   40.04,  32.78,  26.62, 131.12, 112.97,
                         94.82,  81.07,  214.94, 185.9, 156.86, 135.52,
                         273.36, 236.73, 200.1,  173.47};

  fill(&test1, fill_test1);
  fill(&test2, fill_test2);
  fill(&truth, fill_truth);

  ck_assert_uint_eq(s21_mult_matrix(&test1, &test2, &result), OK);
  ck_assert_uint_eq(s21_eq_matrix(&result, &truth), SUCCESS);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);
  s21_remove_matrix(&truth);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(mult_matrix3) {
  matrix_t test1, test2, result;
  s21_create_matrix(1, 2, &test1);
  s21_create_matrix(3, 4, &test2);

  double fill_test1[] = {1.1, 2.2, 3.3, 4.4,  5.5,  6.6,
                         7.7, 8.8, 9.9, 10.0, 11.1, 12.2};
  double fill_test2[] = {12.2, 11.1, 10.0, 9.9, 8.8, 7.7,
                         6.6,  5.5,  4.4,  3.3, 2.2, 1.1};

  fill(&test1, fill_test1);
  fill(&test2, fill_test2);

  ck_assert_uint_eq(s21_mult_matrix(&test1, &test2, &result), CALCERROR);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);
}
END_TEST

START_TEST(mult_matrix4) {
  matrix_t test1 = {0}, test2 = {0}, result = {0};
  s21_create_matrix(4, 4, &test1);
  s21_create_matrix(4, 4, &test2);
  test1.columns = -7;

  ck_assert_uint_eq(s21_mult_matrix(&test1, &test2, &result), MATERROR);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(transpose1) {
  matrix_t test1, truth, result;
  s21_create_matrix(3, 4, &test1);
  s21_create_matrix(4, 3, &truth);

  double fill_test1[] = {1.1, 2.2, 3.3, 4.4,  5.5,  6.6,
                         7.7, 8.8, 9.9, 10.0, 11.1, 12.2};
  double fill_truth[] = {1.1, 5.5, 9.9,  2.2, 6.6, 10.0,
                         3.3, 7.7, 11.1, 4.4, 8.8, 12.2};
  fill(&test1, fill_test1);
  fill(&truth, fill_truth);

  ck_assert_uint_eq(s21_transpose(&test1, &result), OK);
  ck_assert_uint_eq(s21_eq_matrix(&result, &truth), SUCCESS);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&truth);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(transpose2) {
  matrix_t test1, result;
  s21_create_matrix(1, 1, &test1);
  s21_create_matrix(1, 1, &result);
  test1.columns = 0;

  ck_assert_int_eq(s21_transpose(&test1, &result), MATERROR);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(complements1) {
  matrix_t test1, truth, result;
  s21_create_matrix(5, 5, &test1);
  s21_create_matrix(5, 5, &truth);

  double fill_test1[] = {0, -2, 3, 4, 2, 0, 0, 6, 3, 2, -7, 8, 9,
                         2, 2,  1, 2, 3, 4, 2, 2, 2, 2, 2,  2};
  double fill_truth[] = {-140, -84,  -108, -16, 348, 112,  -28, 168, -28,
                         -224, -56,  14,   -16, -20, 78,   84,  98,  24,
                         268,  -474, 0,    0,   -68, -204, 510};
  fill(&test1, fill_test1);
  fill(&truth, fill_truth);

  ck_assert_int_eq(s21_calc_complements(&test1, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &truth), SUCCESS);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&truth);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(complements2) {
  matrix_t test1, result;
  s21_create_matrix(4, 3, &test1);

  ck_assert_int_eq(s21_calc_complements(&test1, &result), CALCERROR);
  s21_remove_matrix(&test1);
}
END_TEST

START_TEST(complements3) {
  matrix_t test1, truth, result;
  s21_create_matrix(1, 1, &test1);
  s21_create_matrix(1, 1, &truth);

  test1.matrix[0][0] = -7.7;
  truth.matrix[0][0] = -7.7;

  ck_assert_int_eq(s21_calc_complements(&test1, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &truth), SUCCESS);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&truth);
  s21_remove_matrix(&result);
}

END_TEST

START_TEST(determinant1) {
  matrix_t test1;
  double result, truth = 7.77;
  s21_create_matrix(1, 1, &test1);

  test1.matrix[0][0] = 7.77;

  ck_assert_uint_eq(s21_determinant(&test1, &result), OK);
  ck_assert_float_eq_tol(result, truth, 1e-7);
  s21_remove_matrix(&test1);
}
END_TEST

START_TEST(determinant2) {
  matrix_t test1;
  double result, truth = -2;
  s21_create_matrix(2, 2, &test1);

  double fill_test1[] = {1, 2, 3, 4};
  fill(&test1, fill_test1);

  ck_assert_uint_eq(s21_determinant(&test1, &result), OK);
  ck_assert_float_eq_tol(result, truth, 1e-7);
  s21_remove_matrix(&test1);
}
END_TEST

START_TEST(determinant3) {
  matrix_t test1;
  double result, truth = 0;
  s21_create_matrix(3, 3, &test1);

  double fill_test1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  fill(&test1, fill_test1);

  ck_assert_uint_eq(s21_determinant(&test1, &result), OK);
  ck_assert_float_eq_tol(result, truth, 1e-7);
  s21_remove_matrix(&test1);
}
END_TEST

START_TEST(determinant4) {
  matrix_t test1;
  double result, truth = 0;
  s21_create_matrix(5, 5, &test1);

  double fill_test1[] = {0, 0, 0, 0, 0, 2, 0, 6, 3, 2, -7, 8, 9,
                         2, 2, 1, 2, 3, 4, 2, 2, 2, 2, 2,  2};
  fill(&test1, fill_test1);
  ck_assert_uint_eq(s21_determinant(&test1, &result), OK);
  ck_assert_float_eq_tol(result, truth, 1e-7);
  s21_remove_matrix(&test1);
}
END_TEST

START_TEST(determinant5) {
  matrix_t test1;
  double result, truth = 392;
  s21_create_matrix(5, 5, &test1);

  double fill_test1[] = {1, -2, 3,  4, 2, 2, 0, 6, 3, 2, -7, 8, 9,
                         2, 2,  -1, 2, 3, 4, 2, 2, 2, 2, 2,  2};
  fill(&test1, fill_test1);
  ck_assert_uint_eq(s21_determinant(&test1, &result), OK);
  ck_assert_float_eq_tol(result, truth, 1e-7);
  s21_remove_matrix(&test1);
}
END_TEST

START_TEST(determinant6) {
  matrix_t test1;
  double result, truth = 476;
  s21_create_matrix(5, 5, &test1);

  double fill_test1[] = {0, -2, 3, 4, 2, 0, 0, 6, 3, 2, -7, 8, 9,
                         2, 2,  1, 2, 3, 4, 2, 2, 2, 2, 2,  2};
  fill(&test1, fill_test1);
  ck_assert_uint_eq(s21_determinant(&test1, &result), OK);
  ck_assert_float_eq_tol(result, truth, 1e-7);
  s21_remove_matrix(&test1);
}
END_TEST

START_TEST(determinant7) {
  matrix_t test1;
  double result;
  s21_create_matrix(4, 5, &test1);
  ck_assert_uint_eq(s21_determinant(&test1, &result), CALCERROR);
  s21_remove_matrix(&test1);
}
END_TEST

START_TEST(determinant8) {
  matrix_t test1;
  double result, truth = 0;
  s21_create_matrix(5, 5, &test1);

  double fill_test1[] = {0, -2, 3, 4, 2, 0, 0, 6, 3, 2, 0, 8, 9,
                         2, 2,  0, 2, 3, 4, 2, 0, 2, 2, 2, 2};
  fill(&test1, fill_test1);
  ck_assert_uint_eq(s21_determinant(&test1, &result), OK);
  ck_assert_float_eq_tol(result, truth, 1e-7);
  s21_remove_matrix(&test1);
}
END_TEST

START_TEST(inverse1) {
  matrix_t test1 = {0}, truth = {0}, result = {0};
  s21_create_matrix(3, 3, &test1);
  s21_create_matrix(3, 3, &truth);
  double fill_test1[] = {2, 5, 7, 6, 3, 4, 5, -2, -3};
  double fill_truth[] = {1, -1, 1, -38, 41, -34, 27, -29, 24};

  fill(&test1, fill_test1);
  fill(&truth, fill_truth);

  ck_assert_int_eq(s21_inverse_matrix(&test1, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &truth), SUCCESS);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&truth);
}
END_TEST

START_TEST(inverse2) {
  matrix_t test1, result;
  s21_create_matrix(2, 3, &test1);

  ck_assert_uint_eq(s21_inverse_matrix(&test1, &result), CALCERROR);
  s21_remove_matrix(&test1);
}
END_TEST

START_TEST(inverse3) {
  matrix_t test1 = {0};
  matrix_t result = {0};
  s21_create_matrix(3, 3, &test1);

  ck_assert_int_eq(s21_inverse_matrix(&test1, &result), CALCERROR);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(inverse4) {
  matrix_t test1 = {0};
  matrix_t result = {0};
  s21_create_matrix(3, 3, &test1);
  test1.rows = 0;

  ck_assert_int_eq(s21_inverse_matrix(&test1, &result), MATERROR);
  test1.rows = 3;
  s21_remove_matrix(&test1);
  s21_remove_matrix(&result);
}
END_TEST

Suite *s21_create_suite(void) {
  Suite *s = suite_create("************create**********");
  TCase *tc = tcase_create("matrix");

  tcase_add_test(tc, create1);
  tcase_add_test(tc, create2);
  tcase_add_test(tc, create3);

  suite_add_tcase(s, tc);

  return s;
}

Suite *s21_remove_suite(void) {
  Suite *s = suite_create("************remove**********");
  TCase *tc = tcase_create("matrix");

  tcase_add_test(tc, remove1);

  suite_add_tcase(s, tc);

  return s;
}

Suite *s21_equal_suite(void) {
  Suite *s = suite_create("************equal***********");
  TCase *tc = tcase_create("matrix");

  tcase_add_test(tc, equal1);
  tcase_add_test(tc, equal2);
  tcase_add_test(tc, equal3);
  tcase_add_test(tc, equal4);
  tcase_add_test(tc, equal5);

  suite_add_tcase(s, tc);

  return s;
}

Suite *s21_sum_suite(void) {
  Suite *s = suite_create("*************sum************");
  TCase *tc = tcase_create("matrix");

  tcase_add_test(tc, sum1);
  tcase_add_test(tc, sum2);
  tcase_add_test(tc, sum3);
  tcase_add_test(tc, sum4);

  suite_add_tcase(s, tc);

  return s;
}

Suite *s21_sub_suite(void) {
  Suite *s = suite_create("*************sub************");
  TCase *tc = tcase_create("matrix");

  tcase_add_test(tc, sub1);
  tcase_add_test(tc, sub2);
  tcase_add_test(tc, sub3);
  tcase_add_test(tc, sub4);

  suite_add_tcase(s, tc);

  return s;
}

Suite *s21_mult_number_suite(void) {
  Suite *s = suite_create("*********mult_number********");
  TCase *tc = tcase_create("matrix");

  tcase_add_test(tc, mult_number1);
  tcase_add_test(tc, mult_number2);
  tcase_add_test(tc, mult_number3);

  suite_add_tcase(s, tc);

  return s;
}

Suite *s21_mult_matrix_suite(void) {
  Suite *s = suite_create("*********mult_mutrix********");
  TCase *tc = tcase_create("matrix");

  tcase_add_test(tc, mult_matrix1);
  tcase_add_test(tc, mult_matrix2);
  tcase_add_test(tc, mult_matrix3);
  tcase_add_test(tc, mult_matrix4);

  suite_add_tcase(s, tc);

  return s;
}

Suite *s21_transpose_suite(void) {
  Suite *s = suite_create("**********transpose*********");
  TCase *tc = tcase_create("matrix");

  tcase_add_test(tc, transpose1);
  tcase_add_test(tc, transpose2);

  suite_add_tcase(s, tc);

  return s;
}

Suite *s21_calc_complements_suite(void) {
  Suite *s = suite_create("*******calc_complements*****");
  TCase *tc = tcase_create("matrix");

  tcase_add_test(tc, complements1);
  tcase_add_test(tc, complements2);
  tcase_add_test(tc, complements3);

  suite_add_tcase(s, tc);

  return s;
}

Suite *s21_determinant_suite(void) {
  Suite *s = suite_create("*********determinant********");
  TCase *tc = tcase_create("matrix");

  tcase_add_test(tc, determinant1);
  tcase_add_test(tc, determinant2);
  tcase_add_test(tc, determinant3);
  tcase_add_test(tc, determinant4);
  tcase_add_test(tc, determinant5);
  tcase_add_test(tc, determinant6);
  tcase_add_test(tc, determinant7);
  tcase_add_test(tc, determinant8);

  suite_add_tcase(s, tc);

  return s;
}

Suite *s21_inverse_suite(void) {
  Suite *s = suite_create("***********inverse**********");
  TCase *tc = tcase_create("matrix");

  tcase_add_test(tc, inverse1);
  tcase_add_test(tc, inverse2);
  tcase_add_test(tc, inverse3);
  tcase_add_test(tc, inverse4);

  suite_add_tcase(s, tc);

  return s;
}

int s21_matrix_tests(Suite *s) {
  int failed_count;
  SRunner *runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);

  failed_count = srunner_ntests_failed(runner);
  srunner_free(runner);

  if (failed_count != 0) {
    failed_count = 1;
  }

  return failed_count;
}

int main(void) {
  int result = 0;

  result += s21_matrix_tests(s21_create_suite());
  result += s21_matrix_tests(s21_remove_suite());
  result += s21_matrix_tests(s21_equal_suite());
  result += s21_matrix_tests(s21_sum_suite());
  result += s21_matrix_tests(s21_sub_suite());
  result += s21_matrix_tests(s21_mult_number_suite());
  result += s21_matrix_tests(s21_mult_matrix_suite());
  result += s21_matrix_tests(s21_transpose_suite());
  result += s21_matrix_tests(s21_calc_complements_suite());
  result += s21_matrix_tests(s21_determinant_suite());
  result += s21_matrix_tests(s21_inverse_suite());

  printf("Failed tests: %d\n", result);

  return 0;
}
