#pragma once
class Job
{
public:
	int r;
	int p;
	int q;
	Job();
	Job(int in_r, int in_p, int in_q);
	~Job();
	void display();

};
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
