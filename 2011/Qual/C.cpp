#include <vector>
#include <numeric>

using namespace std;

int fn_xor(int a, int b) { return a^b; }

struct Test
{
  int N;
  vector<int> C;
  int answer;

  void read_input(FILE* f) {
    fscanf(f, "%d", &N);
    C.resize(N);
    for (int i = 0; i < N; i++)
      fscanf(f, "%d", &C[i]);
  }

  void solve() {
    int sum = accumulate(C.begin(), C.end(), 0);
    int _xor = accumulate(C.begin(), C.end(), 0, fn_xor);
    if (_xor == 0)
      answer = sum - *min_element(C.begin(), C.end()); else
      answer = -1;
  }

  void print_answer(FILE* f) {
    if (answer >= 0)
      fprintf(f, "%d\n", answer); else
      fprintf(f, "NO\n");
  }
};
