#include "stdafx.h"
#include "Job.h"
#include "iostream"
#include <iomanip>
#include <fstream>

using namespace std;
Job::Job() { r = p = q = 0; }
Job::Job(int in_r, int in_p, int in_q) {
	this->r = in_r;
	this->p = in_p;
	this->q = in_q;
}
void Job::display() {
	cout << setw(3) << r << setw(3) << p << setw(3) << q << endl;
}

Job::~Job()
{
}
