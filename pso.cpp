#include <cstring>
#include <iostream>
#include <math.h>
#include <algorithm>
#include <ctime>
#include <array>




using namespace std;

//Khoi tao cac gia tri mac dinh

const int Max_Interation = 200;
const int Population_Size = 5;
const int Variable_Count = 2;

//const int x_min = -5;
//const int x_max = 5;

//const int v_min = 0;
//const int v_max = 1;

double X[Population_Size][Variable_Count]; /*= {
	{3.1472, -4.0246},
	{4.0579, -2.2150},
	{-3.7301, 0.4688},
	{4.1338, 4.5751},
	{1.3236, 4.6489}
};*/
double V[Population_Size][Variable_Count]; /*= {
	{0.2194, 0.2449},
	{0.1908, 0.2228},
	{0.3828, 0.3232},
	{0.3976, 0.3547},
	{0.0934, 0.3773}
};*/
double Fx[Population_Size];
double Fx_old[Population_Size];
double Fx_new[Population_Size];
double Pbest[Population_Size][Variable_Count];
double Gbest[Population_Size];

double Randoom(int min, int max){
	double r = min + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(max-min)));
	return r ;
}

double func(double x1, double x2)
{
    return pow(x1,2) - x1*x2 + pow(x2,2) + 2*x1 + 4*x2 + 3;
}

void initialize()
{
	for(int i=0; i<Population_Size; i++)
	{
		for(int j=0; j<Variable_Count; j++)
		{
			
			X[i][j] = Randoom(-10, 10);

			V[i][j] = Randoom(0, 1) ;
			
			Pbest[i][j] = X[i][j];
		}
	}
	
}

void out_initialize()
{
	cout<<"\nX{}\tGia tri X trong khoang [-5,5] :"<<endl;
	//cout<<"                x1\t\tx2"<<endl;
	for(int i=0; i<Population_Size; i++)
	{
		cout<<"\tCon chim "<<i<<": ";
		for(int j=0; j<Variable_Count; j++)
		{
			
			cout<<"[ "<<X[i][j]<<" ]\t";
		}
		cout<<endl;
	}
	cout<<"\nV{}\tGia tri V trong khoang [0,1] :"<<endl;
	//cout<<"                v1\t\tv2"<<endl;
	for(int i=0; i<Population_Size; i++)
	{
		cout<<"\tCon chim "<<i<<": ";
		for(int j=0; j<Variable_Count; j++)
		{
			cout<<"[ "<<V[i][j]<<" ]\t";
		}
		cout<<endl;
	}
}


void f()
{
	for (int i=0; i<Population_Size; i++)
	{
			Fx_new[i] = func(X[i][0], X[i][1]);
			Fx[i] = Fx_new[i];
	}
	
}

double gbest()
{
	//double minF = Fx_new[0];
	double maxF = Fx_new[0];
	int pos = 0;
	for (int i=0; i<Population_Size; i++)
	{
		/*
		if (minF > Fx_new[i])
		{
			minF = Fx_new[i];
			pos = i;
		}
		*/
		
		if (maxF < Fx_new[i])
		{
			maxF = Fx_new[i];
			pos = i;
		}
		
		
	}
	for (int j=0; j<Variable_Count; j++)
		{
			Gbest[j] = X[pos][j];
		}
	
	return maxF;
}

void out_Pbest()
{
	cout<<"\nPbest{}\tGia tri Pbest:"<<endl;
	//cout<<"             x1\t\t   x2"<<endl;
	for(int i=0; i<Population_Size; i++)
	{
		cout<<"\tCon chim "<<i<<": ";
		for(int j=0; j<Variable_Count; j++)
		{
			
			cout<<"[ "<<Pbest[i][j]<<" ]\t";
		}
		cout<<endl;
	}
}

void out_Gbest()
{
	cout<<"\nGbest{} => Gia tri GBest: ";
	for(int i=0; i<Variable_Count; i++)
	{
		cout<<"[ "<<Gbest[i]<<" ]\t";
	}
}

void out_F()
{
	cout<<"\nf{}\tGia tri cua ham f(x):"<<endl;
	cout<<"\t\t        f(x)"<<endl;
	for(int i=0; i<Population_Size; i++)
	{
		cout<<"\tCon chim "<<i<<":\t";
		cout<<"[ "<<Fx_new[i]<<" ]\t";
		cout<<endl;
	}
}

void update_V()
{
	double r1 = 0.5949; //Randoom(0,1); 
	double r2 = 0.0855; //Randoom(0,1);
	
	double Vnew[Population_Size][Variable_Count];
	
	
	//Cap nhat V
	for (int i=0; i<Population_Size; i++)
		{
			for (int j=0; j<Variable_Count; j++)
			{
				Vnew[i][j] = 0.9*V[i][j] + 1.5*r1*(Pbest[i][j] - X[i][j]) + 1.5*r2*(Gbest[j] - X[i][j]);	
			}
		}
	//Cap nhat	
	for (int i=0; i<Population_Size; i++)
		{
			for (int j=0; j<Variable_Count; j++)
			{
				V[i][j] = Vnew[i][j];
			}
		}
	
}

void update_X()
{
	double Xnew[Population_Size][Variable_Count];
		
	//Cap nhat X
	for (int i=0; i<Population_Size; i++)
		{
			for (int j=0; j<Variable_Count; j++)
			{
				Xnew[i][j] = X[i][j] + V[i][j];
			}
		}
		
		for (int i=0; i<Population_Size; i++)
		{
			for (int j=0; j<Variable_Count; j++)
			{
				if(Xnew[i][j]>10)
				{
					Xnew[i][j] = 10.00000;
				}
				else if(Xnew[i][j]<-10)
				{
					Xnew[i][j] = -10.00000;
				}	
			}
		}
	
	//Cap nhat	
	for (int i=0; i<Population_Size; i++)
		{
			for (int j=0; j<Variable_Count; j++)
			{
				X[i][j] = Xnew[i][j];
			}
		}
	
}

void update_FGP()
{
	int pos = 0;
	
	//double Pbest_new[Population_Size][Variable_Count];
	//double Gbest_new[Population_Size];
	
	//Cap nhat gia tri ham muc tieu f(x)
	for (int i=0; i<Population_Size; i++)
	{
			Fx_old[i] = Fx[i];
	}
	for (int i=0; i<Population_Size; i++)
	{
			Fx_new[i] = func(X[i][0], X[i][1]);
			Fx[i] = Fx_new[i];
	}
	
	//Cap nhat Gbest
	gbest();
	/*
	//Cap nhat Pbest max
	for (int i=0; i<Population_Size; i++)
	{
		if (Fx_new[i] > Fx_old[i])
		{
			pos = i;
			for (int j=0; j<Variable_Count; j++)
			{
				Pbest[pos][j] = X[pos][j];
			}
		}
	}	
	*/
	//Cap nhat Pbest min
	for (int i=0; i<Population_Size; i++)
	{
		if (Fx_new[i] > Fx_old[i])
		{
			pos = i;
			for (int j=0; j<Variable_Count; j++)
			{
				Pbest[pos][j] = X[pos][j];
			}
		}
	}	
}


void PSO()
{
	cout<<"\t\t\t******************";
	cout<<"\n\t\t\t*                *";
	cout<<"\n\t\t\t* THUAT TOAN PSO *";
	cout<<"\n\t\t\t*                *";
	cout<<"\n\t\t\t******************\n\n";
	int inter = 0;
	cout<<"\tTim max f(x) = (x1)^2 - (x1)*(x2) + (x2)^2 + 2*(x1) + 4*(x2) + 3";
	initialize();

	while(inter < Max_Interation)
	{
		f();
		
		gbest();
		cout<<"\n\n\n=============================================================> ";
		cout<<"Lan lap thu "<<inter<<": ";
		
		out_initialize();
		out_F();
		out_Pbest();
		out_Gbest();
		
		cout<<"=> max f(x) = "<<gbest()<<"\t";
		
		update_V();
		update_X();
		update_FGP();
		
		
			
		inter += 1;
	}
}

int main()
{
    PSO();
    return 0;
}
