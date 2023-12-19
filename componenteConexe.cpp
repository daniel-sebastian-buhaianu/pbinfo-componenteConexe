#include <fstream>
using namespace std;
int main()
{
  // citesc datele de intrare
  ifstream f("componenteconexe.in");
  int n, i, j;
  f >> n;
  int** a = new int*[n];
  for (i = 0; i < n; i++)
  {
    a[i] = new int[n];
    for (j = 0; j < n; j++) a[i][j] = 0;
  }
  while (f >> i >> j) a[i-1][j-1] = a[j-1][i-1] = 1;
  f.close();
  // initializez vectorul caracteristic
  // vizitat[i] = 1, daca nodul i a fost vizitat deja sau 0 altfel
  int* vizitat = new int[n];
  for (i = 0; i < n; i++) vizitat[i] = 0;
  // initializez matricea de solutii
  // cc[i][0] = nr. de noduri ce formeaza componenta conexa de ordin i
  int** cc = new int*[n];
  for (i = 0; i < n; i++)
  {
    cc[i] = new int[n+1];
    cc[i][0] = 0;
  }
  // construiesc matricea de solutii
  int nr = 0;
  for (i = 0; i < n; i++)
    if (!vizitat[i])
    {
      nr++;
      for (int k = i; !vizitat[k];)
      {
        vizitat[k] = 1;
        cc[nr-1][++cc[nr-1][0]] = k;
        for (j = 0; j < n && (vizitat[j] || !a[k][j]); j++);
        if (j < n) k = j;
        else break;
      }
    }
  // sortez matricea de solutii
  for (i = 0; i < nr; i++)
    for (j = 1; j < cc[i][0]; j++)
      for (int k = j+1; k <= cc[i][0]; k++)
        if (cc[i][j] > cc[i][k])
          swap(cc[i][j], cc[i][k]);
  // afisez solutia
  ofstream g("componenteconexe.out");
  g << nr << '\n';
  for (i = 0; i < nr; i++)
  {
    for (j = 1; j <= cc[i][0]; j++)
      g << cc[i][j]+1 << ' ';
    g << '\n';
  }
  g.close();
  return 0;
}
