// wiTi.cpp: Okreœla punkt wejœcia dla aplikacji konsoli.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>  
#include "Job.h"

using namespace std;

vector<Job> Read(string); // funkcja czytajaca
void display(vector<Job> processing); // wyswietlanie
void sort_by_p(vector<Job>& process); // sortowanie wzgledem p (niepotrzebne)
int wiTi(vector<Job>); // algorytm wiTi B&B

int main()
{
	string nazwa = "9"; //<--- numer partii danych do wybrania od 1 do 10
	typedef vector<Job> processList;
	processList process = Read("przyklady/wiTi_" + nazwa + "_in.txt");
	
	// print result
	cout << "Obliczona wartosc to: " << wiTi(process) << endl;
	fstream plik("przyklady/wiTi_" + nazwa + "_out.txt");
	int poprawna;
	plik >> poprawna;
	cout << "Poprawna wartosc to: " << poprawna << endl;
	plik.close();
	cin.get();
	return 0;
}
vector<Job> Read(string file_name) {
	fstream plik(file_name);
	vector<Job> process;
	// read input
	if (plik.good()) { // n - liczba zadañ
		int n;
		plik >> n;
		for (int i = 0; i < n; i++) {
			int p, w, d;
			plik >> p >> w >> d;
			Job JOB(p, w, d);
			process.push_back(JOB);
		}
		plik.close();
	}
	else {
		cout << "Error: Can not open the file" << endl;
		cin.get();
		exit(0);
	}
	return process;
}
void display(vector<Job> processing) {
	cout << "p   w   d" << endl;
	for (unsigned i = 0; i < processing.size(); i++) {
		processing[i].display();
	}
}
void sort_by_p(vector<Job>& process) {
	sort(process.begin(), process.end(),
		[](const Job & a, const Job & b)->bool {
		return (a.p < b.p);
	});
}
int wiTi(vector<Job> process) {
	int cMax, j, i, x, n = process.size(), k = 1 << n, *tab = new int[k];

	for (i = 1, tab[0] = 0; i<k; i++) {
		for (j = 1, x = 0, cMax = 0; j<k; j = j << 1, x++) {
			if (i&j) {
				cMax = cMax + process[x].p;
			}
		}
		for (j = 1, x = 0, tab[i] = 2147483647; x<n; j=j<<1, x++) {
			if (i&j) {
				tab[i] = min(tab[i], max((cMax - process[x].d)*process[x].w, 0) + tab[i&(~j)]);
			}
		}
	}
	//delete tab;
	return tab[k - 1];
	}