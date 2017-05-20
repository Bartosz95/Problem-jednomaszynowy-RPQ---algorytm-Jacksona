// Jackson.cpp: Okreœla punkt wejœcia dla aplikacji konsoli.
//

#include "stdafx.h"
#include <iostream>
#include <list>
#include <fstream>

using namespace std;

class process {
	int r;
	int p;
public:
	process() { r = 0; p = 0; }
	process(int in_r, int in_p) { r = in_r; p = in_p; }
	int get_r() { return r; }
	int get_p() { return p; }
};
/*
* NAJWIEKSZE ELEMENTY KOLEJKI SA NA JEJ POCZATKU
*
*/
class process_queue {

	list<process> que;
public:
	int size();
	void insert(process P);
	void insert(int in_r, int in_p);
	void display();
	process front();
	process back();
	void pop_front();
	void pop_back();
	void push_back(process P) { que.push_back(P); }

};

int oblicz_czas(process_queue kolejka) {
	int czas_ogolny = 0;
	while (kolejka.size() != 0) {
		if (kolejka.front().get_r()>czas_ogolny) {
			czas_ogolny++;
		}
		else {
			czas_ogolny += kolejka.front().get_p();
			kolejka.pop_front();
		}
	}
	return czas_ogolny;
}

process_queue wczytaj_z_pliku() {
	process_queue kolejka;
	int r, p;
	int ilosc;
	fstream plik("przyklady/jack_1_in.txt");
	plik >> ilosc;
	while (ilosc--) {
		plik >> r;
		plik >> p;
		kolejka.insert(r, p);
	}
	plik.close();
	return kolejka;
}

int main() {
	process_queue kolejka = wczytaj_z_pliku();
	kolejka.display();
	cout << endl << "Czas procesow to: " << oblicz_czas(kolejka) << endl;
	cin.get();
	return 0;
}


/*
* FUNKCJE
*/
int process_queue::size() {
	return que.size();
}
void process_queue::insert(process P) {
	if (que.size() == 0) {
		que.push_front(P);
	}
	else {
		list<process>::iterator iter = que.begin();
		for (unsigned int i = 0; i<que.size();) {
			if (P.get_r() >= iter->get_r()) {
				que.insert(iter, P); break;
			}
			else {
				i++;
				++iter;
				if (iter == que.end()) { que.push_back(P); break; }
			}
		}
	}
}
void process_queue::insert(int in_r, int in_p) {
	process P(in_r, in_p);
	if (que.size() == 0) {
		que.push_front(P);
	}
	else {
		list<process>::iterator iter = que.begin();
		for (unsigned int i = 0; i<que.size();) {
			if (P.get_r() >= iter->get_r()) {
				que.insert(iter, P); break;
			}
			else {
				i++;
				++iter;
				if (iter == que.end()) { que.push_back(P); break; }
			}
		}
	}
}
void process_queue::display() {
	for (list<process>::iterator iter = que.begin(); iter != que.end(); ++iter)
		cout << iter->get_r() << "	" << iter->get_p() << endl;

}
void process_queue::pop_front() {
	if (que.size() == 0) {
		cout << endl << "EMPTY QUEUE!" << endl;
	}
	else if (que.size()>0) {
		que.pop_back();
	}
	else {
		cout << endl << "ERROR: QUEUE SIZE IS < 0 !" << endl;
	}
}
void process_queue::pop_back() {
	if (que.size() == 0) {
		cout << endl << "EMPTY QUEUE!" << endl;
	}
	else if (que.size()>0) {
		que.pop_front();
	}
	else {
		cout << endl << "ERROR: QUEUE SIZE IS < 0 !" << endl;
	}
}
process process_queue::front() {
	return que.back();
}
process process_queue::back() {
	return que.front();
}
