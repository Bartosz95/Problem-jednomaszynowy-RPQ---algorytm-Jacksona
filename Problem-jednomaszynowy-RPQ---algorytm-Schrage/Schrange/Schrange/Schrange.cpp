// Schrange.cpp: Okreœla punkt wejœcia dla aplikacji konsoli.
//

#include "stdafx.h"
#include <iostream>
#include <queue>
#include <iomanip>
#include <fstream>
#include <algorithm>    // std::max

using namespace std;

class Job {
public:
	int r;
	int p;
	int q;
	Job() { r = p = q = 0; }
	Job(int in_r, int in_p, int in_q) {
		this->r = in_r;
		this->p = in_p;
		this->q = in_q;
	}
	void display() {
		cout << setw(3) << r << setw(3) << p << setw(3) << q << endl;
	}
};
//porownuje rosn¹co od 'r'
class CompareJob_r {
public:
	bool operator()(Job& t1, Job& t2)
	{
		if (t1.r > t2.r) return true;
		return false;
	}
};
//porownuje malejaco od 'q'
class CompareJob_q {
public:
	bool operator()(Job& t1, Job& t2)
	{
		if (t1.q < t2.q) return true;
		return false;
	}
};
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

int main()
{
	string nazwa = "przyklady/schrage_5_"; //<--- numer partii danych 
	int t = 0, k = 0, Cmax = 0; //1
	priority_queue<Job, vector<Job>, CompareJob_r> rQUE = Read(nazwa + "in.txt");
	priority_queue<Job, vector<Job>, CompareJob_q> qQUE;

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
			t = t + e.p;
			Cmax = max(Cmax, t + e.q);
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
