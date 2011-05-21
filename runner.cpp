#include <cstdio>
#include <vector>
#include <pthread.h>

#include "2011/Qual/C.cpp"

const char* FILE_NAME = "C-large-practice";

// Global vars
FILE *f_input, *f_output;
size_t first_unsolved;
std::vector<Test> tests;

// Thead safety? What thread safety? Haven't heard about it.
void* solver_thread(void*)
{
  int num_solved = 0;
  while (first_unsolved < tests.size()) {
    tests[first_unsolved++].solve();
    num_solved++;
  }

  fprintf(stderr, "Thread finished solving %d tests.\n", num_solved);
}

void assign_file_pointers()
{
  char in_file_name[1024];
  snprintf(in_file_name, sizeof(in_file_name), "%s.in", FILE_NAME);
  f_input = fopen(in_file_name, "rt");

  char out_file_name[1024];
  snprintf(out_file_name, sizeof(out_file_name), "%s.out", FILE_NAME);
  f_output = fopen(out_file_name, "wt");
}

void read_input()
{
  int num_tests;
  fscanf(f_input, "%d", &num_tests);
  tests.resize(num_tests);
  for (int i = 0; i < num_tests; i++)
    tests[i].read_input(f_input);
}

void run_single_test(int num_test)
{
  Test& test = tests[num_test-1];
  test.solve();
  fprintf(f_output, "Case #%d: ", num_test);
  test.print_answer(f_output);
}

void run_all_tests(int num_threads)
{
  // Create and start num_threads threads
  std::vector<pthread_t> solvers;
  first_unsolved = 0;
  for (int i = 0; i < num_threads; i++) {
    pthread_t solver;
    pthread_create(&solver, NULL, solver_thread, NULL);
    solvers.push_back(solver);
  }

  // Wait until all of them will finish
  for (size_t i = 0; i < solvers.size(); i++)
    pthread_join(solvers[i], NULL);

  // Print answers to all tests
  for (size_t i = 0; i < tests.size(); i++) {
    fprintf(f_output, "Case #%lu: ", i+1);
    tests[i].print_answer(f_output);
  }
}

int main()
{
  assign_file_pointers();
  read_input();
  run_all_tests(8);

  return 0;
}
