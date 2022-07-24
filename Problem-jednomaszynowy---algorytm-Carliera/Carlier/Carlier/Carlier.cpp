// Carlier.cpp: Okreœla punkt wejœcia dla aplikacji konsoli.
//

#include "stdafx.h"
#include <iostream>
#include <queue>
#include <fstream>
#include <algorithm>
#include <tuple>
#include <limits>
#include "Job.h"

using namespace std;

priority_queue<Job, vector<Job>, CompareJob_r> Read(string); // funkcja czytajaca
priority_queue<Job, vector<Job>, CompareJob_r> convert(vector<Job> &queue); // Konwertuje kolejke priorytetow¹ "vector<Job>" na "priority_queue<Job, vector<Job>, CompareJob_r>"
vector<Job> convert(priority_queue<Job, vector<Job>, CompareJob_r> &queue); // Konwertuje kolejke priorytetow¹"priority_queue<Job, vector<Job>, CompareJob_r>" na "vector<Job>"
vector<Job> schrage_S(vector<Job> jobs); // Schrange bez podzia³ów
int eval(vector<Job> permutation); //liczenie cMax z permutacji
int schrage_prmtS(std::vector<Job> jobs); // Schrage z podzialami, zwraca cMax
tuple<int, int, int> block(vector<Job> permutation); // liczenie i zwracanie bloku abc
void carlier(std::vector<Job> jobs, int& ub); // Carlier, przyjmuje wektor zadan oraz gorne oszacowanie (ub) ktore na koniec jest poszukiwanym cMax

int main()
{
	string nazwa = "przyklady/carlier_5_"; //<--- numer partii danych 
	int UB = numeric_limits<int>::max();

	// process
	carlier(convert(Read(nazwa + "in.txt")), UB); // wywo³anie carliera ze standardowym wejœciem 

												  // print result
	cout << "Znaleziona wartosc to: " << UB << endl;
	fstream plik(nazwa + "out.txt");
	int poprawna;
	plik >> poprawna;
	cout << "Poprawna wartosc to: " << poprawna << endl;
	plik.close();
	cin.get();

	return 0;
}

priority_queue<Job, vector<Job>, CompareJob_r> Read(string file_name) {

	priority_queue<Job, vector<Job>, CompareJob_r> QUE;
	fstream plik(file_name);
	int ilosc, r, p, q;
	if (plik.good())
	{
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
	}
	return QUE;
}
vector<Job> convert(priority_queue<Job, vector<Job>, CompareJob_r> &queue) {
	vector<Job> re;
	while (!queue.empty()) {
		re.push_back(queue.top());
		queue.pop();
	}
	return re;
}
vector<Job> schrage_S(vector<Job> jobs) {
	vector<Job> permutation;
	int t = 0, k = 0, Cmax = 0; //1
	priority_queue<Job, vector<Job>, CompareJob_r> rQUE;
	priority_queue<Job, vector<Job>, CompareJob_q> qQUE;
	while (!jobs.empty()) {
		rQUE.push(jobs.back());
		jobs.pop_back();
	}
	Job e = rQUE.top(); //ustawienie 'e' na poczatek kolejki zaleznej od r
						/*
						ustawia argument by "qQUE =! 0"
						*///______________________________________________________
	t = e.r; //czas jest rowny najmniejszej wartosci r
	while ((rQUE.size() != 0) && (e.r <= t)) {
		qQUE.push(e);
		rQUE.pop();
		if (rQUE.size() != 0) {
			e = rQUE.top();
		}
	}
	//_________________________________________________________
	while ((rQUE.size() != 0) || (qQUE.size() != 0)) { //2
		if (rQUE.size() != 0) {
			e = rQUE.top();
		}
		while ((rQUE.size() != 0) && (e.r <= t)) { //3
			qQUE.push(e); //4
			rQUE.pop();
			if (rQUE.size() != 0) {
				e = rQUE.top();
			}
		}
		if (qQUE.size() == 0) {  //5
			t = e.r;	 //6
		}
		else {
			e = qQUE.top();
			qQUE.pop();	//7
			k = k + 1; // 8
			permutation.push_back(e);
			t = t + e.p;
			Cmax = max(Cmax, t + e.q);
		}
	}
	return permutation;
}
int eval(vector<Job> permutation) {
	int cMax = -1;
	int t = 0;
	for (unsigned i = 0; i < permutation.size(); i++) {
		t = max(t, permutation[i].r);
		t += permutation[i].p;
		cMax = max(cMax, t + permutation.at(i).q);
	}
	return cMax;
}
int schrage_prmtS(std::vector<Job> jobs) // Schrage z podzialami, zwraca cMax
{
	int t = 0, k = 0, Cmax = -1; //1
	priority_queue<Job, vector<Job>, CompareJob_r> rQUE;;
	priority_queue<Job, vector<Job>, CompareJob_q> qQUE;
	while (!jobs.empty()) {
		rQUE.push(jobs.back());
		jobs.pop_back();
	}
	Job e = rQUE.top(); //aktualne wykonywanie zadanie
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
	return Cmax;
}
tuple<int, int, int> block(vector<Job> permutation) // liczenie bloku a, b, c na podstawie permutacji
{
	int a = numeric_limits<int>::infinity();
	int b = -1;
	int c = -1;
	int t = 0, cMax = -1;
	//sprawdzenie cMax dla emementu "b"
	for (unsigned j = 0; j < permutation.size(); j++) {
		t = max(t, permutation[j].r);
		t += permutation[j].p;
		if (cMax < t + permutation[j].q) {
			b = j;
			cMax = t + permutation[j].q;
		}
	}
	// wyliczenie elementu b

	for (unsigned int j = 0; j < permutation.size(); j++) {
		cMax = permutation[j].r;
		for (int s = j; s <= b; s++) {
			cMax += permutation[s].p;
		}
		cMax += permutation[b].p;
		if (cMax <= a) {
			a = cMax;
		}
	}
	for (int j = a; j <= b; j++) {
		if (permutation[j].q < permutation[b].q) {
			c = j;
		}
	}
	return make_tuple(a, b, c);
}
void carlier(std::vector<Job> jobs, int& UB) {
	int r_1 = numeric_limits<int>::max(),
		p_1 = 0,
		q_1 = numeric_limits<int>::max();
	vector<Job> PI_1;

	vector<Job> PI = schrage_S(jobs);//1
	int U = eval(PI);

	if (U < UB) { //2
		UB = U;
		PI_1 = PI;
	}
	auto bl = block(PI); //3
	int a = get<0>(bl);
	int b = get<1>(bl);
	int c = get<2>(bl);
	if (c == -1) { //4
		cout << "KONIEC" << endl;
	}
	else {
		for (int j = c + 1; j <= b; j++) { // 5
			if (PI[j].r <= r_1) { // r_1 min PI
				r_1 = PI[j].r;
			}
			if (PI[j].q <= q_1) {  // q_1 min PI
				q_1 = PI[j].q;
			}
			p_1 += PI[j].p;  // sum p PI
		}
		int old_C_r = PI[c].r;
		PI[c].r = max(PI[c].r, r_1 + p_1); // 6

		int LB = schrage_prmtS(PI); // 7
		if (LB < UB) // 8
			carlier(PI, UB); // 9
		PI[c].r = old_C_r; // 10

		int old_C_q = PI[c].q;
		PI[c].q = max(PI[c].q, q_1 + p_1); // 11

		LB = schrage_prmtS(PI); // 12

		if (LB < UB) { // 13
			carlier(PI, UB); // 14
		}
		PI[c].q = old_C_q;
	}
}

