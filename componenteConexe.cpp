#include <fstream>
using namespace std;
#define NMAX 100
int n, nr;
int a[NMAX][NMAX], cc[NMAX][NMAX+1];
bool viz[NMAX];
void citire();
void compcon(int);
void sortare();
void afisare();
int main()
{
  citire();
  for (int i = 0; i < n; i++)
    if (!viz[i])
    {
      nr++;
      compcon(i);
    }
  sortare();
  afisare();
  return 0;
}
void afisare()
{
  ofstream g("componenteConexe.out");
  g << nr << '\n';
  for (int i = 0; i < nr; i++)
  {
    for (int j = 1; j <= cc[i][0]; j++)
      g << cc[i][j]+1 << ' ';
    g << '\n';
  }
  g.close();
}
void sortare()
{
  for (int i = 0; i < nr; i++)
    for (int j = 1; j < cc[i][0]; j++)
      for (int k = j+1; k <= cc[i][0]; k++)
        if (cc[i][j] > cc[i][k])
          swap(cc[i][j], cc[i][k]);
}
void compcon(int vf)
{
  viz[vf] = 1;
  cc[nr-1][++cc[nr-1][0]] = vf;
  for (int i = 0; i < n; i++)
    if (!viz[i] && a[vf][i])
      compcon(i);
}
void citire()
{
  ifstream f("componenteConexe.in");
  f >> n;
  for (int i, j; f >> i >> j;)
    a[i-1][j-1] = a[j-1][i-1] = 1;
  f.close();
}
 
