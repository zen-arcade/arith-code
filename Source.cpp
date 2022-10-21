#include <iostream>
using namespace std;

struct table
{
	char sym;
	double prob, lc, hc;
};

void codage(table tab[], string seq)
{
	double Lc{ 0 }, Hc{ 1 }, taille{ 1 };
	for (int i = 0; i < seq.length(); i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (seq[i] == tab[j].sym)
			{
				Hc = Lc + taille * tab[j].hc;
				Lc = Lc + taille * tab[j].lc;
				taille = Hc - Lc;
			}
		}
	}
	cout << "La sequence peut etre codee par un reel entre " << Lc << " et " << Hc << '\n';
}

string decodage(table tab[], double code, int len)
{
	double Lc{ 0 }, Hc{ 1 }, taille{ 1 }, mc;
	string seq = "";
	for (int i = 0; i < len; i++)
	{
		mc = (code - Lc) / taille;
		for (int j = 0; j < 5; j++)
		{
			if (mc<tab[j].hc && mc >=tab[j].lc)
			{
				seq += tab[j].sym;
				Hc = Lc + taille * tab[j].hc;
				Lc = Lc + taille * tab[j].lc;
				taille = Hc - Lc;
			}
		}
	}
	return seq;
}

int main()
{
	table tab[5];
	tab[0].sym = 'A'; tab[1].sym = 'B'; tab[2].sym = 'C'; tab[3].sym = 'D'; tab[4].sym = 'E';
	tab[0].prob = 0.4; tab[1].prob = 0.2; tab[2].prob = 0.15; tab[3].prob = 0.15; tab[4].prob = 0.1;
	double tmp = 0;
	for (int i = 0; i < 5; i++)
	{
		tab[i].lc = tmp;
		tab[i].hc = tab[i].lc + tab[i].prob;
		tmp = tab[i].hc;
	}
	string seq;
	cout << "Entrez la sequence a coder: ";
	cin >> seq;
	codage(tab, seq);

	double code;
	int len;
	cout << "Entrez le reel a decoder: ";
	cin >> code;
	cout << "Entrez la longueur de sequence a decoder: ";
	cin >> len;
	cout << "La sequence decodee: " << decodage(tab, code, len)<<'\n';

	system("pause");
	return 0;
}