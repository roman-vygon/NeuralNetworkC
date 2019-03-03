#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <time.h>
#include <cmath>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
using namespace std;
class Neuron
{
	double weight;
	double gamma;
	vector <double> sin;


public:
	void changeWeight(double x) //функция изменения веса нейрона
	{
		weight = x;
	}
	double getSin(int i) //функция получения значения  i-ого синапсиса нейрона
	{
		return sin[i];
	}
	double getGamma() //возвращает гамма значение нейрона (значение ошибки для перерасчета коэффициентов)
	{
		return gamma;
	}
	void changeGamma(double x) //изменяет гамма значение
	{
		gamma = x;
	}
	void changeSin(double x, int i) //изменяет значение i-ого синапсиса нейрона
	{
		sin[i] = x;
	}
	void pushSin(double x) //добавляет синапсис нейрону
	{
		sin.push_back(x);
	}
	int getSinSize() //возвращает кол-во синапсисов нейрона
	{
		return sin.size();
	}

	double getWeight() //возвращает вес нейрона
	{
		return weight;
	}
	double normalize(double x) //функция нормализации
	{		
		return 1 / (1 + pow(M_E, -2*x));
	}
	void gatherWeight(vector <Neuron> lastLayer) //собирает все веса с предыдущего слоя нейронов
	{
		changeWeight(0);
		int xxx = 0;
		for (int i = 0; i < lastLayer.size(); i++)
		{
			double xx = lastLayer[i].getWeight();
			double yy = getSin(i);
			weight += xx*yy;


		}
		weight = normalize(weight);
	}
public:
	Neuron() {};
};
class NeuronNet
{
	vector <vector <Neuron>> Network;
	double alpha;
	double  beta = 1;
	double normalize(double x) //функция нормализации
	{
		if (x >= 1)
			return 1;
		return 1 / (1 + pow(M_E, -1 * x));
	}
	Neuron createNeuron(int x) //Создание случайного нейрона
	{
		Neuron a;

		for (int i = 0; i < x; i++)
		{
			double weight = rand() % 1e2 / 1e3;
			a.pushSin(weight);
		}


		return a;
	}
	Neuron createNeuron(double x, bool j) //Создание определенного нейрона
	{

		Neuron a;
		a.changeWeight(x);
		return a;
	}
	void updateNetwork() //изменение весов всей нейронной сети
	{
		for (int i = 1; i < Network.size(); i++)
			for (int j = 0; j < Network[i].size(); j++)
				Network[i][j].gatherWeight(Network[i - 1]);
	}
	void ML(vector <double> answer) //обучение
	{
		for (int i = 0; i < Network[Network.size() - 1].size(); i++)
		{
			double o = Network[Network.size() - 1][i].getWeight();
			Network[Network.size() - 1][i].changeGamma(-2 * o * (1 - o) * (answer[i] - o));				
		}
		for (int i = Network.size() - 2; i > 0; i--)
			for (int j = 0; j < Network[i].size(); j++)
			{  double Sum = 0;
				for (int k = 0; k < Network[i + 1].size(); k++)
				{
					Sum += Network[i + 1][k].getGamma() * Network[i + 1][k].getSin(j);
				}
				Network[i][j].changeGamma(2* Network[i][j].getWeight() * (1 - Network[i][j].getWeight()) * Sum);			
			}
		
		for (int i = Network.size() - 1; i > 0; i--)
			for (int j = 0; j < Network[i].size(); j++)
			{
				for (int l = 0; l < Network[i][j].getSinSize(); l++)
				{
					Network[i][j].changeSin((-1 * beta * Network[i][j].getGamma() * Network[i-1][l].getWeight()) + Network[i][j].getSin(l), l);
				}
			}
	}

public:
	void InSource()
	{
		
		for (int i = 0; i < Network.size(); i++)
			for (int j = 0; j < Network[i].size(); j++)
				for (int k = 0; k < Network[i][j].getSinSize(); k++)
				{
					
					double x;
					cin >> x;
					Network[i][j].changeSin(x,k);
				}
		

	}
	void OutSource()
	{
		freopen("output1.txt", "w", stdout);
		for (int i = 0; i < Network.size(); i++)
			for (int j = 0; j < Network[i].size(); j++)
				for (int k = 0; k < Network[i][j].getSinSize(); k++)
					cout << Network[i][j].getSin(k) << ' ';
	}
	void Output()
	{
		ifstream myfile;
		myfile.open("input1.txt");
		
		
		for (int i = 0; i < Network[0].size(); i++)
		{
			int x;
			myfile >> x;
						if (x==1)
				Network[0][i].changeWeight(1);
			else
				Network[0][i].changeWeight(0);
		}
		updateNetwork();
		double maxn = 0;
		int answer = 0;
		for (int i = 0; i < Network[Network.size() - 1].size(); i++)
		{
			cout << Network[Network.size() - 1][i].getWeight() << endl;
			if (Network[Network.size() - 1][i].getWeight() > maxn)
			{
				answer = i;
				maxn = Network[Network.size() - 1][i].getWeight();
				
			}
		}
		cout << answer;
		myfile.close();

	}
	void Learn(vector <double> question, vector <double> answer) //input
	{
		for (int i = 0; i < Network[0].size(); i++)
		{
			if (question[i])
				Network[0][i].changeWeight(1);
			else
				Network[0][i].changeWeight(0);
		}
		updateNetwork();
	for (int i = 0; i < 10; i++)
			if (answer[i])
				cout << i << ':' << endl;
		for (int i = 0; i < 10; i++)
			cout << Network[Network.size() - 1][i].getWeight() << ' ';
		cout << endl;
		ML(answer);
		
	
	




	}
	int getAnswer(vector <bool> q) //почему бы и нет
	{
		int answer;
		return answer;
	}
	void createNetwork(int a, int b, int c, int d, double alph) //Создание сети, заполненной случайными нейронами
	{
		alpha = alph;
		vector <Neuron> Layer;
		for (int i = 0; i < c; i++)		//создание входного слоя
		{

			
			Layer.push_back(createNeuron(0));
		}
		Network.push_back(Layer);

		for (int i = 0; i < a; i++) // создание промежуточных слоев
		{

			Layer.clear();
			if (i != 0)
			{
				for (int i = 0; i < b; i++)
					Layer.push_back(createNeuron(b));
			}
			else
				for (int i = 0; i < b; i++)
					Layer.push_back(createNeuron(c));
			Network.push_back(Layer);
		}
		Layer.clear();
		for (int i = 0; i < d; i++) //создание выходного слоя
		{
			if (b == 0)
				Layer.push_back(createNeuron(c));
			else
			Layer.push_back(createNeuron(b));
		}
		Network.push_back(Layer);
	}


};

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int a, b, c, d;
	double alpha;
	cin >> c >> a >> b >> d >> alpha;
	NeuronNet Network;
	vector <double> q;
	vector <double> t;
	int go;
	cin >> go;
	Network.createNetwork(a, b, c, d, alpha);
	
	
	for (int k = 0; k < go; k++)
	{
		q.clear();
		t.clear();
		for (int i = 0; i < c; i++)
		{
			int x;
			cin >> x;
			q.push_back(x);
		}
		for (int i = 0; i < d; i++)
		{
			int x;
			cin >> x;
			t.push_back(x);
		}


		Network.Learn(q, t);

	}
	Network.OutSource();
	//Network.InSource();
//	Network.Output();

}