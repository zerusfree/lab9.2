#include <iostream>
#include <string>
#include <iomanip>
#include <Windows.h>

using namespace std;

enum Specialnist { Kn, In, Me, PhI, Tn };
enum Kurs { I = 1, II, III, IV, V, VI };
string specialnistStr[]{ "����'����� �����", "�����������" ,  "���������� �� ��������" , "Գ���� �� �����������" , "������� ��������" };

struct Student
{
	string prizv;
	Kurs kurs;
	Specialnist specialnist;
	int physichs;
	int Math;
	union
	{
		int programming;
		int chusel_methods;
		int pedagog;
	};
};

void Create(Student* p, const int N);
void Print(Student* p, const int N);
void Sort(Student* p, const int N);
int BinSearch(Student* p, const int N, const string prizv, const Specialnist specialnist, const int physichs);
int* IndexSort(Student* p, const int N);
void PrintIndexSorted(Student* p, int* I, const int N);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int N;
	cout << "������ ������� ��������: ";
	cin >> N;

	Student* p = new Student[N];
	
	int menuItem;
	int ispecialnist;
	Specialnist specialnist;
	string prizv;
	int found;
	int physichs;

	do {
		cout << endl << endl << endl;
		cout << "������� ��:" << endl << endl;
		cout << " [1] - �������� ����� � ���������" << endl;
		cout << " [2] - ���� ����� �� �����" << endl;
		cout << " [3] - ������� ������������� �����" << endl << endl;
		cout << " [4] - ������� ����� �������� �� ������������, �������� �� ������"<< endl << endl;
		cout << " [5] - �������� ������������� �� ���� �����"<< endl << endl;
		cout << " [0] - ����� �� ���������� ������ ��������" << endl << endl;
		cout << "������ ��������: "; cin >> menuItem;
		cout << endl << endl << endl;
		switch (menuItem)
		{
		case 1:
			Create(p, N);
			break;
		case 2:
			Print(p, N);
			break;
		case 3:
			Sort(p,N);
			break;
		case 4:
			cout << "������ ����� ������:" << endl;
			cout << " ������������ ( 0 - ����'����� ����� , 1 - �����������, 2 - ���������� �� ��������, 3 - Գ���� �� �����������, 4 - ������� ��������): ";
			cin >> ispecialnist;
			specialnist = (Specialnist)ispecialnist;
			cin.get(); // ������� ����� ��������� � �� ����������� �������
			cin.sync(); // "����� �����", �� �� ����� ������ ��������� ������� �����

			cout << " �������: "; getline(cin, prizv);
			cout << " ������ � ������: "; cin >> physichs;
			cout << endl;
			
			if ((found = BinSearch(p, N, prizv, specialnist, physichs)) != -1)
				cout << "�������� �������� � ������� " << found + 1 << endl;
			else
				cout << "�������� �������� �� ��������" << endl;
			break;
		case 5:
			PrintIndexSorted(p, IndexSort(p, N), N);
			break;
		case 0:
			break;
		default:
			cout << "�� ����� ��������� ��������! "
				"��� ������ ����� - ����� ��������� ������ ����" << endl;
		}
	} while (menuItem != 0);

	return 0;
}

void Create(Student* p, const int N)
{
	int specialnist, kurs;
	for (int i = 0; i < N; i++)
	{
		cout << "������� � " << i + 1 << ":" << endl;
		cin.get(); // ������� ����� ��������� � �� ����������� �������
		cin.sync(); // "����� �����", �� �� ����� ������ ��������� ������� �����

		cout << " �������: "; getline(cin, p[i].prizv);

		cout << "���� (1-6): ";
		cin >> kurs;
		p[i].kurs = (Kurs)kurs;

		cout << "������ � ������: ";
		cin >> p[i].physichs;

		cout << "������ � ����������: ";
		cin >> p[i].Math;

		cout << " ������������ ( 0 - ����'����� ����� , 1 - �����������, 2 - ���������� �� ��������, 3 - Գ���� �� �����������, 4 - ������� ��������): ";
		cin >> specialnist;
		p[i].specialnist = (Specialnist)specialnist;
		switch (p[i].specialnist)
		{
		case Kn:
			cout << " ������ � �������������: "; cin >> p[i].programming;
			break;
		case In:
			cout << " ������ � ��������� ������: "; cin >> p[i].chusel_methods;
			break;
		case Me:
		case PhI:
		case Tn:
			cout << " ������ � ���������: "; cin >> p[i].pedagog;
			break;
		}
		cout << endl;
	}
}

void Print(Student* p, const int N)
{
	cout << "==========================================================================================================================="
		<< endl;
	cout << "| � | �������    | ���� |      ������������      | Գ���� | ���������� |  �������������  | ������� ������ | ��������� |"
		<< endl;
	cout << "---------------------------------------------------------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(1) << right << i + 1 << " ";
		cout << "| " << setw(12) << left << p[i].prizv
			<< "| " << setw(4) << right << p[i].kurs << " "
			<< "| " << setw(24) << left << specialnistStr[p[i].specialnist]
			<< "| " << setw(7) << right << p[i].physichs
			<< "| " << setw(11) << right << p[i].Math;

		switch (p[i].specialnist)
		{
		case Kn:
			cout << "| " << setw(15) << p[i].programming << right << " | " << setw(18) << " | " << setw(12) << " |" << endl;
			break;
		case In:
			cout << "| " << setw(18) << " | " << setw(15) << p[i].chusel_methods << right << " | " << setw(12) << " |" << endl;
			break;
		case Me:
		case PhI:
		case Tn:
			cout << "| " << setw(18) << " | " << setw(18) << " | " << setw(10) << p[i].pedagog << right << " |" << endl;
			break;
		}
	}
	cout << "==========================================================================================================================="
		<< endl;
	cout << endl;
}

void Sort(Student* p, const int N)
{
	Student tmp;
	for(int i0=0; i0<N; i0++)
	for(int i1=0; i1<N-i0-1; i1++)
	{
		if (p[i1].physichs < p[i1+1].physichs 
			||
			(p[i1].physichs == p[i1 + 1].physichs && p[i1].specialnist > p[i1+1].specialnist)
			||
			(p[i1].physichs == p[i1 + 1].physichs && p[i1].specialnist == p[i1 + 1].specialnist && p[i1].prizv > p[i1 + 1].prizv))
		{
			tmp = p[i1];
			p[i1] = p[i1 + 1];
			p[i1 + 1] = tmp;
		}
	}
}

int BinSearch(Student* p, const int N,const string prizv, const Specialnist specialnist, const int physichs)
{
	int L = 0, R = N - 1, m;
	do {
		m = (L + R) / 2;
		if (p[m].specialnist == specialnist && p[m].prizv == prizv && p[m].physichs == physichs)
			return m;
		if ((p[m].specialnist < specialnist)
			||
			(p[m].specialnist == specialnist && p[m].prizv < prizv)
			||
			(p[m].specialnist == specialnist && p[m].prizv == prizv && p[m].physichs < physichs))
		{
			L++;
		}
		else
		{
			R--;
		}
	} while (L <= R);
	return -1;
}

int* IndexSort(Student* p, const int N)
{
	int* I = new int[N]; // �������� ��������� �����
	for (int i = 0; i < N; i++)
		I[i] = i; // ��������� ���� ����������� ������
	int i, j, value; 
	for (i = 1; i < N; i++) // �������� ��������� ����� �������
	{
		value = I[i];
		for (j = i - 1;
			j >= 0 && (p[I[j]].physichs < p[value].physichs
				||
				(p[I[j]].physichs == p[value].physichs && p[I[j]].specialnist > p[value].specialnist)
				||
				(p[I[j]].physichs == p[value].physichs && p[I[j]].specialnist == p[value].specialnist && p[I[j]].prizv > p [value].prizv));
			j--)
				
		{
			I[j + 1] = I[j];
		}
		I[j + 1] = value;
	}
	return I;
}

void PrintIndexSorted(Student* p, int* I, const int N)
{
	cout << "==========================================================================================================================="
		<< endl;
	cout << "| � | �������    | ���� |      ������������      | Գ���� | ���������� |  �������������  | ������� ������ | ��������� |"
		<< endl;
	cout << "---------------------------------------------------------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(1) << right << i + 1 << " ";
		cout << "| " << setw(12) << left << p[I[i]].prizv
			<< "| " << setw(4) << right << p[I[i]].kurs << " "
			<< "| " << setw(24) << left << specialnistStr[p[I[i]].specialnist]
			<< "| " << setw(7) << right << p[I[i]].physichs
			<< "| " << setw(11) << right << p[I[i]].Math;

		switch (p[I[i]].specialnist)
		{
		case Kn:
			cout << "| " << setw(15) << p[I[i]].programming << right << " | " << setw(18) << " | " << setw(12) << " |" << endl;
			break;
		case In:
			cout << "| " << setw(18) << " | " << setw(15) << p[I[i]].chusel_methods << right << " | " << setw(12) << " |" << endl;
			break;
		case Me:
		case PhI:
		case Tn:
			cout << "| " << setw(18) << " | " << setw(18) << " | " << setw(10) << p[I[i]].pedagog << right << " |" << endl;
			break;
		}
	}
	cout << "==========================================================================================================================="
		<< endl;
	cout << endl;
}