//POP_2016_12_16_projekt_1_Julia_Wyka_EiT_165304 Dev C++ wercja 5.11

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int L_SEGM_X = 2;
const int L_SEGM_Y = 4;
const int ROZMIAR_SEGM = 5;
const int PLANSZA_X = L_SEGM_X * ROZMIAR_SEGM;
const int PLANSZA_Y = L_SEGM_Y * ROZMIAR_SEGM;
const int ILE_SEGM = 6;

struct wspolrzedne {
	int wspx;
	int wspy;
};

const char A[ROZMIAR_SEGM][ROZMIAR_SEGM] =
{
	{ (char)178,(char)178,' ',(char)178,(char)178 },
	{ (char)178,' ',' ',(char)178,(char)178 },
	{ ' ',' ',(char)178,' ',' ' },
	{ (char)178,' ',' ',' ',(char)178 },
	{ (char)178,(char)178,' ',(char)178,(char)178 }
};

const char B[ROZMIAR_SEGM][ROZMIAR_SEGM] =
{
	{ (char)178,(char)178,' ',' ',(char)178 },
	{ ' ',(char)178,(char)178,' ',(char)178 },
	{ ' ',' ',' ',' ',' ' },
	{ (char)178,' ',' ',' ',(char)178 },
	{ (char)178,(char)178,' ',' ',(char)178 }
};

const char C[ROZMIAR_SEGM][ROZMIAR_SEGM] =
{
	{ ' ',' ',' ',' ',' ' },
	{ ' ',' ',(char)178,' ',' ' },
	{ ' ',' ',(char)178,(char)178,' ' },
	{ (char)178,' ',(char)178,(char)178,(char)178 },
	{ (char)178,' ',' ',' ',' ' }
};

const char D[ROZMIAR_SEGM][ROZMIAR_SEGM] =
{
	{ (char)178,(char)178,' ',' ',' ' },
	{ (char)178,' ',' ',(char)178,' ' },
	{ ' ',' ',(char)178,' ',' ' },
	{ ' ',(char)178,' ',' ',(char)178 },
	{ (char)178,' ',' ',(char)178,(char)178 }
};

const char E[ROZMIAR_SEGM][ROZMIAR_SEGM] =
{
	{ ' ',' ',' ',(char)178,(char)178 },
	{ (char)178,' ',' ',' ',(char)178 },
	{ ' ',' ',(char)178,' ',' ' },
	{ ' ',' ',(char)178,' ',' ' },
	{ ' ',' ',' ',' ',(char)178 }
};

const char F[ROZMIAR_SEGM][ROZMIAR_SEGM] =
{
	{ (char)178,(char)178,' ',(char)178,(char)178 },
	{ (char)178,(char)178,' ',(char)178,(char)178 },
	{ ' ',' ',' ',' ',' ' },
	{ (char)178,(char)178,' ',(char)178,(char)178 },
	{ (char)178,(char)178,' ',(char)178,(char)178 }
};

int menu();
void losowanie(char plansza[][PLANSZA_Y]);
void generuj_plansze(char plansza[][PLANSZA_Y], int segmenty[][L_SEGM_Y]);
void skarby(char plansza[][PLANSZA_Y]);
void ustawienie_pionka(char plansza[][PLANSZA_Y], wspolrzedne* pionek);
int o_ograniczeniu(bool *ograniczenie, char literka[]);
int ruszanie_pionka(wspolrzedne *pionek, char plansza[][PLANSZA_Y], bool *ograniczenie);
void wyswietlanie_planszy(char plansza[][PLANSZA_Y]);
void rysuj(char plansza[][PLANSZA_Y], wspolrzedne *pionek, bool ograniczanie);
int inicjalizacja(bool ograniczanie);
void zasady();
void koniec_gry(int *wsk);

int main()
{
	srand(time(NULL));

	menu();

	return 0;
}

int menu() {
	char wybor[200];
	  cout<<"*********************\n"
        <<"*                   *\n"
        <<"*     LABIRYNT      *\n"
        <<"*                   *\n"
        <<"*********************\n";
	cout << "1. Start \n2. Zasady \n3. Wyjscie \nWybierz: ";
	cin >> wybor;
	bool ograniczanie = true;

	while (true) { 
		switch (wybor[0]) {
		case '1':system("cls"); inicjalizacja(&ograniczanie);
			break;
		case '2':system("cls"); zasady();
			break;
		case '3':exit(1);
		default: system("cls"); cout<<"Nie ma takiej opcji, wybierz jeszcze raz"<<endl; menu();
		}
   }
	return 0;
}

void zasady()
{
	cout<<"Do poruszania sie uzywaj: "<<endl;
	cout<<" w - w gore\n s - w dol \n a - w lewo \n d - w prawo"<<endl;
	cout<<"Aby wylaczyc ograniczenie wpisz off. Gdy chcesz wlaczyc je spowrotem wpisz on. "<<endl;
	cout<<"Gra polega na zebraniu 5 skarbow. "<<endl;
	cout<<"Skarb jest oznaczony 's' , a twoj pionek 'o'."<<endl;
	
	cout<<endl<<"Wybierz ponownie :";
	
	cout<<endl<<endl;
	menu();
}

int inicjalizacja(bool ograniczanie) {

	char plansza[PLANSZA_X][PLANSZA_Y];
	wspolrzedne pionek;
	int zebrane_skarby = 0;
	int ruchy = 0;
	int *wsk=&ruchy;
	losowanie(plansza);
	ustawienie_pionka(plansza, &pionek);
	skarby(plansza);

	while (true) {
		rysuj(plansza, &pionek, ograniczanie);  
		
		if (zebrane_skarby >= 5) {
			koniec_gry(wsk);
			return 0;
		}
		switch(ruszanie_pionka(&pionek, plansza, &ograniczanie)) 
		{
		case 1 :zebrane_skarby++;
		case 0:ruchy++;
		}	
		system("cls");
	}
}

int poruszenie(char plansza[][PLANSZA_Y], int xfrom, int yfrom, int xto, int yto) {

	if (xto<0 || xto>(PLANSZA_X * 2) -1 || yto<0 || yto>PLANSZA_Y - 1) return 3;

	else if (plansza[yto][xto] == (char)178) {
		return 3;
	}
	else if (plansza[yto][xto] == 's') {
		plansza[yfrom][xfrom] = ' ';
		plansza[yto][xto] = 'o';
		return 2;
	}
	else if (plansza[yto][xto] == ' ') {
		plansza[yfrom][xfrom] = ' ';
		plansza[yto][xto] = 'o';
		return 1;
	}
	else return 3;
}

void losowanie(char plansza[][PLANSZA_Y])
{
	int segmenty[L_SEGM_X][L_SEGM_Y];
	for (int i = 0; i<L_SEGM_X; i++)
	{
		for (int j = 0; j<L_SEGM_Y; j++)
		{
			int  m = rand() % ILE_SEGM;
			segmenty[i][j] = m;
		}
	}
	generuj_plansze(plansza, segmenty);
}


void generuj_plansze(char plansza[][PLANSZA_Y], int segmenty[][L_SEGM_Y])
{
	for (int i = 0; i<L_SEGM_X; i++)
	{
		for (int j = 0; j<L_SEGM_Y; j++)
		{
			for (int k = 0; k<ROZMIAR_SEGM; k++)
			{
				for (int l = 0; l<ROZMIAR_SEGM; l++)
				{
					switch (segmenty[i][j])
					{
					case 0:
						plansza[i*ROZMIAR_SEGM + k][j*ROZMIAR_SEGM + l] = A[k][l];
						break;
					case 1:
						plansza[i*ROZMIAR_SEGM + k][j*ROZMIAR_SEGM + l] = B[k][l];
						break;
					case 2:
						plansza[i*ROZMIAR_SEGM + k][j*ROZMIAR_SEGM + l] = C[k][l];
						break;
					case 3:
						plansza[i*ROZMIAR_SEGM + k][j*ROZMIAR_SEGM + l] = D[k][l];
						break;
					case 4:
						plansza[i*ROZMIAR_SEGM + k][j*ROZMIAR_SEGM + l] = E[k][l];
						break;
					case 5:
						plansza[i*ROZMIAR_SEGM + k][j*ROZMIAR_SEGM + l] = F[k][l];
						break;
					}
				}
			}
		}
	}
}


void skarby(char plansza[][PLANSZA_Y])
{
	int ile_skarbow = 0;

	while (ile_skarbow<5) {
		int i = rand() % 10;
		int j = rand() % 20;

		if (plansza[i][j] == ' ' && plansza[i][j] != 'o' && plansza[i][j] != 's')
		{
			plansza[i][j] = 's';

			ile_skarbow = ile_skarbow + 1;
		}
	}
}

void ustawienie_pionka(char plansza[][PLANSZA_Y], wspolrzedne *pionek)
{
	bool wyjscie = false;

	for (int j = 0; j<PLANSZA_Y; j++)
	{
		for (int i = 0; i<PLANSZA_X; i++)
		{
			if (plansza[i][j] == ' ')
			{
				plansza[i][j] = 'o';
				(*pionek).wspx = j;
				(*pionek).wspy = i;
				wyjscie = true;
				break;
			}
		}
		if (wyjscie == true) break;
	}	
}

int o_ograniczeniu(bool *ograniczenie, char literka[100])
{
		if (literka[0] == 'o' && literka[1] == 'f' &&literka[2] == 'f' ) {
		if (*ograniczenie==true) (*ograniczenie)= false;
		else 
		{
		cout<<"Przeciez ograniczenie jest wylaczone"<<endl;
		system("PAUSE"); }
		return 2;
	}
	if ( literka[0] == 'o' && literka[1] == 'n') {
		if (*ograniczenie==false) (*ograniczenie)= true;
		else 
		{
		cout<<"Przeciez ograniczenie jest wlaczone"<<endl;
		system("PAUSE"); }
		return 2;
	}
}


int ruszanie_pionka(wspolrzedne *pionek, char plansza[][PLANSZA_Y], bool *ograniczenie)
{
	cout << endl;
	char literka[100];
	
	cin >> literka;

	o_ograniczeniu(ograniczenie, literka);

	int zwrot;
	
	switch (literka[0]) {
	case 'a':
		zwrot = poruszenie(plansza, (*pionek).wspx, (*pionek).wspy, (*pionek).wspx - 1, (*pionek).wspy);
		if (zwrot != 3) (*pionek).wspx = (*pionek).wspx - 1;
		break;
	case 's':
		zwrot = poruszenie(plansza, (*pionek).wspx, (*pionek).wspy, (*pionek).wspx, (*pionek).wspy + 1);
		if (zwrot != 3) (*pionek).wspy = (*pionek).wspy + 1;
		break;
	case 'd':
		zwrot = poruszenie(plansza, (*pionek).wspx, (*pionek).wspy, (*pionek).wspx + 1, (*pionek).wspy);
		if (zwrot != 3) (*pionek).wspx = (*pionek).wspx + 1;
		break;
	case 'w':
		zwrot = poruszenie(plansza, (*pionek).wspx, (*pionek).wspy, (*pionek).wspx, (*pionek).wspy - 1);
		if (zwrot != 3) (*pionek).wspy = (*pionek).wspy - 1;
		break;
	default: if (literka[0]!='o' && literka[1]!='n' or literka[0]!='o' && literka[1]!='f' &&literka[2]!='f')
		{
		cout << "Bledny wpis"<<endl; 
		system("PAUSE");
		}
		
	}
	
	
	switch (zwrot)
	{
	case 3:
		cout << "Nie mozna wejsc w sciane" << endl; 
		system("PAUSE");
		return 0;
	case 1:        //zwykly ruch ( liczenie ruchow w funkcji inicjalizacja)
		return 0; 
	case 2:        //zebranie skarbu (liczenie skarbow w funkcji inicjalizacja)
		return 1;  
	default:
		return 0;
	}
}


void rysuj(char plansza[][PLANSZA_Y], wspolrzedne *pionek, bool ograniczenie)
{
	for (int i = 0; i<PLANSZA_X; i++)
	{
		cout << endl;

		for (int j = 0; j<PLANSZA_Y; j++)
		{
			if (ograniczenie==true && ((i>(*pionek).wspy + 2 || i<(*pionek).wspy - 2) || (j<(*pionek).wspx - 2 || j>(*pionek).wspx + 2))) 
			 cout << (char)177;                             
			else cout << plansza[i][j];
		}
	}
}

void koniec_gry(int *wsk)
{	system("cls");
	cout<<endl;	
	cout<<"Zebrales wszystkie 5 skarbow wykonujac: "<<*wsk<<" ruchy :)";
	cout<<endl<<endl;
	menu();
}
