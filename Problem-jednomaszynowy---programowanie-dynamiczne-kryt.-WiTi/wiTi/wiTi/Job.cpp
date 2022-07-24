#include "stdafx.h"
#include "Job.h"
#include "iostream"
#include <iomanip>

using namespace std;

Job::Job(int in_p, int in_w, int in_d) {
	this->p = in_p; 
	this->w = in_w;
	this->d = in_d;
}
void Job::display() {
	cout << p << "   " << w << "   " << d << endl;
}
Job::~Job()
{
}