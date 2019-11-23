#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

ifstream f("CYK.in");
ofstream g("CYK.out");

void break_grammar(string a, vector <vector <string> > &G, int poz)
{
	unsigned int i;
	while (a.size())
	{
		i = a.find("|");
		if (i>a.size())
		{
			G[poz].push_back(a);
			a = "";
		}
		else
		{
			G[poz].push_back(a.substr(0, i));
			a = a.substr(i + 1, a.size());
		}
	}

}
void read_grammar(vector <vector <string> > &G, int np)
{
	for (int i = 0; i<np; i++)
	{
		string a;
		f >> a;
		int pt = a.find("->");
		G[i].push_back(a.substr(0, pt));
		a = a.substr(pt + 2, a.size());
		break_grammar(a, G, i);
	}
}
int main()
{
	int np;
	string cuvant;
	f >> np;

	vector < vector <string> > Grammar(np);
	read_grammar(Grammar, np);
	f >> cuvant;
	int cs = cuvant.size();
	cuvant.push_back('a');
	rotate(cuvant.begin(), cuvant.begin() +cuvant.size()-1, cuvant.end());
	vector <vector <string> > Matrix(cs+1, vector<string>(cs+1, ""));
	for (int i = 1; i <= cs; i++)
	{
		string aux = "";
		for (auto j : Grammar)
		{
			vector <string>::iterator it;
			string s(1, cuvant[i]);
			it = find(j.begin(), j.end(), s);
			if (it != j.end())
				aux = aux + (*j.begin());
		}
		Matrix[1][i] += aux;
	}
	for (int l = 2; l <= cs; l++)
	{
		for (int s = 1; s <= cs - l + 1; s++)
		{
			for (int p = 1; p <= l - 1; p++)
			{
				for (auto i : Grammar)
				{
					for (auto j : i)
					{
						if (j.size() == 2)
						{
							int w = 0;
							unsigned int ok = Matrix[p][s].find(j[0]);
							if (ok != string::npos) w++;
							ok = Matrix[l - p][s + p].find(j[1]);
							if (ok != string::npos) w++;
							if (w == 2)
                            {
								ok = Matrix[l][s].find(i[0][0]);
								if (ok == string::npos ) Matrix[l][s] += i[0];
							}
						}
					}
				}
			}
		}
	}
	unsigned int ok=Matrix[5][1].find('S');
	if (ok!=string::npos)   g<<"Gramatica accepta cuvantul!";
	else g<<"Gramatica nu accepta cuvantul!";
	return 0;
}
