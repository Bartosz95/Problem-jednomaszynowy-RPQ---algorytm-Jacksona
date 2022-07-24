#include "stdafx.h"
#include "Job.h"
#include <iostream>

using namespace std;
Job::Job()
{
	r = p = q = 0;
}


Job::~Job()
{
}

Job::Job(int in_r, int in_p, int in_q)
{
	this->r = in_r;
	this->p = in_p;
	this->q = in_q;
}
void Job::display()
{
	cout << " " << r << " " << p << " " << q << endl;
}