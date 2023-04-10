#include <iostream>
#include <string>
#include <iomanip>
#include <Windows.h>

using namespace std;

enum Specialnist { Kn, In, Me, PhI, Tn };
enum Kurs { I = 1, II, III, IV, V, VI };
string specialnistStr[]{ "Комп'ютерні науки", "Інформатика" ,  "Математика та економіка" , "Фізика та інформатика" , "Трудове навчання" };

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
	cout << "Введіть кількість студентів: ";
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
		cout << "Виберіть дію:" << endl << endl;
		cout << " [1] - введення даних з клавіатури" << endl;
		cout << " [2] - вивід даних на екран" << endl;
		cout << " [3] - фізичне впорядкування даних" << endl << endl;
		cout << " [4] - бінарний пошук студента за спеціальністю, прізвищем та оцінок"<< endl << endl;
		cout << " [5] - індексне впорядкування та вивід даних"<< endl << endl;
		cout << " [0] - вихід та завершення роботи програми" << endl << endl;
		cout << "Введіть значення: "; cin >> menuItem;
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
			cout << "Введіть ключі пошуку:" << endl;
			cout << " Спеціальність ( 0 - Комп'ютерні науки , 1 - Інформатика, 2 - Математика та економіка, 3 - Фізика та інформатика, 4 - Трудове навчання): ";
			cin >> ispecialnist;
			specialnist = (Specialnist)ispecialnist;
			cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
			cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок

			cout << " прізвище: "; getline(cin, prizv);
			cout << " Оцінка з фізики: "; cin >> physichs;
			cout << endl;
			
			if ((found = BinSearch(p, N, prizv, specialnist, physichs)) != -1)
				cout << "Знайдено студента в позиції " << found + 1 << endl;
			else
				cout << "Шуканого студента не знайдено" << endl;
			break;
		case 5:
			PrintIndexSorted(p, IndexSort(p, N), N);
			break;
		case 0:
			break;
		default:
			cout << "Ви ввели помилкове значення! "
				"Слід ввести число - номер вибраного пункту меню" << endl;
		}
	} while (menuItem != 0);

	return 0;
}

void Create(Student* p, const int N)
{
	int specialnist, kurs;
	for (int i = 0; i < N; i++)
	{
		cout << "Студент № " << i + 1 << ":" << endl;
		cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
		cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок

		cout << " прізвище: "; getline(cin, p[i].prizv);

		cout << "курс (1-6): ";
		cin >> kurs;
		p[i].kurs = (Kurs)kurs;

		cout << "Оцінка з фізики: ";
		cin >> p[i].physichs;

		cout << "Оцінка з математики: ";
		cin >> p[i].Math;

		cout << " Спеціальність ( 0 - Комп'ютерні науки , 1 - Інформатика, 2 - Математика та економіка, 3 - Фізика та інформатика, 4 - Трудове навчання): ";
		cin >> specialnist;
		p[i].specialnist = (Specialnist)specialnist;
		switch (p[i].specialnist)
		{
		case Kn:
			cout << " Оцінка з програмування: "; cin >> p[i].programming;
			break;
		case In:
			cout << " Оцінка з чисельних методів: "; cin >> p[i].chusel_methods;
			break;
		case Me:
		case PhI:
		case Tn:
			cout << " Оцінка з педагогіки: "; cin >> p[i].pedagog;
			break;
		}
		cout << endl;
	}
}

void Print(Student* p, const int N)
{
	cout << "==========================================================================================================================="
		<< endl;
	cout << "| № | Прізвище    | Курс |      Спеціальність      | Фізика | Математика |  Програмування  | Чисельні методи | Педагогіка |"
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
	int* I = new int[N]; // створили індексний масив
	for (int i = 0; i < N; i++)
		I[i] = i; // заповнили його початковими даними
	int i, j, value; 
	for (i = 1; i < N; i++) // починаємо сортувати масив індексів
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
	cout << "| № | Прізвище    | Курс |      Спеціальність      | Фізика | Математика |  Програмування  | Чисельні методи | Педагогіка |"
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