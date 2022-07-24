// Schrange_z_podzia³ami.cpp: Okreœla punkt wejœcia dla aplikacji konsoli.
//

#include "stdafx.h"
#include <iostream>
#include <queue>
#include <iomanip>
#include <fstream>
#include <algorithm>    // std::max
#include "Job.h"

using namespace std;


priority_queue<Job, vector<Job>, CompareJob_r> Read(string file_name) {
	priority_queue<Job, vector<Job>, CompareJob_r> QUE;
	fstream plik(file_name);
	int ilosc, r, p, q;
	if (plik.good()) {
		plik >> ilosc;
		while (ilosc--) {
			plik >> r;
			plik >> p;
			plik >> q;
			Job zadanie(r, p, q);
			QUE.push(zadanie);
		}
		plik.close();
	}
	else {
		cout << "Error: Can not open the file" << endl;
		plik.close();
		exit(0);
	}
	return QUE;
}
void dis(priority_queue<Job, vector<Job>, CompareJob_r> k) {
	while (k.size() != 0) {
		Job A = k.top();
		A.display();
		k.pop();
	}
}
void dis(priority_queue<Job, vector<Job>, CompareJob_q> k) {
	while (k.size() != 0) {
		Job A = k.top();
		A.display();
		k.pop();
	}
}
int main() {


	string nazwa = "przyklady/schrage_9_"; //<--- numer partii danych 


	int t = 0, k = 0, Cmax = 0, t_roz; //1
	priority_queue<Job, vector<Job>, CompareJob_r> rQUE = Read(nazwa + "in.txt");
	priority_queue<Job, vector<Job>, CompareJob_q> qQUE;
	Job e = rQUE.top(); //aktualne wykonywanie zadanie

						//l.q = INFINITY;

	t = e.r; //czas jest rowny najmniejszej wartosci r
	while ((rQUE.size() != 0) && (e.r <= t)) { qQUE.push(e); rQUE.pop(); if (rQUE.size() != 0) { e = rQUE.top(); } }
	//_________________________________________________________

	Job l = qQUE.top(); //zadanie pomocnicze
	while ((rQUE.size() != 0) || (qQUE.size() != 0)) { //2
		if (rQUE.size() != 0) { e = rQUE.top(); }

		while ((rQUE.size() != 0) && (rQUE.top().r <= t)) { //3
			qQUE.push(e);  rQUE.pop(); //4

			if (e.q > l.q) {
				l.p = t - e.r;  t = e.r;	if (l.p > 0) { qQUE.push(l); } //5

			}
			if (rQUE.size() != 0) { e = rQUE.top(); }
		}

		if (qQUE.size() == 0) {  //6

			if (rQUE.size() != 0) { e = rQUE.top(); } t = e.r;//7

		}
		else {
			e = qQUE.top(); qQUE.pop(); //8

			l = e;	t = t + e.p;	Cmax = max(Cmax, t + e.q); //9

		}
	}
	cout << "Cmax=" << Cmax << endl;
	fstream plik(nazwa + "out.txt");
	int poprawna;
	plik >> poprawna;
	cout << "Poprawna wartosc to: " << poprawna << endl;
	plik.close();
	cin.get();
	return 0;
}
