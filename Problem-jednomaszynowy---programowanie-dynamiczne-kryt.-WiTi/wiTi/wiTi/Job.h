#pragma once

class Job
{

public:
	int p; // czas wykonania zadania
	int w; // wspulczynnik kary za opoznienie zadania
	int d; // zadany termin zakonczenia zadania
	Job(int in_p=0, int in_w=0, int in_d=0);
	~Job();
	void display();
};
