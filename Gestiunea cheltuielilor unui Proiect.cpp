#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include <fstream>
#include<vector>
#include<algorithm>
using namespace std;

// Aplicatie pentru gestiunea unui proiect 
// constituit din activitati ce contin  drept atribute :
// cod, denumire, durată în zile, condiționări(codurile activităților imediat precedente).
// Aplicatia trebuie sa permita adaugarea unei activitati la proiect, identificarea
// activitatilor in desfasurare la un moment dat, afisarea tuturor activitatilor proiectului.
class CheltuieliProiect
{
public:
	virtual float cheltuieli(float sumaCheltuitaZilnic) = 0;
};
class Activitate :public CheltuieliProiect
{
protected:

	const int cod;
	static int numarator;
	string denumire = "";
	int durata = 0;//in zile;
	bool activitateInceputa = 0;//inseamna ca activitatea nu a inceput
public:
	Activitate() :cod(numarator++)
	{
		this->denumire = "";
		this->durata = 0;
		this->activitateInceputa = 0;
	}
	Activitate(string denumire, int durata) :cod(numarator++)
	{
		if (denumire.size() > 2)
		{
			this->denumire = denumire;

		}
		if (durata > 0)
		{
			this->durata = durata;

		}
		
	}
	Activitate(const Activitate& a) :cod(a.cod)
	{
		if (a.activitateInceputa == 0)
		{
			if (a.denumire.size() > 2)
			{
				this->denumire = a.denumire;

			}
			if (a.durata > 0)
			{
				this->durata = a.durata;

			}
			this->activitateInceputa = a.activitateInceputa;
		}

	}

	~Activitate()
	{

	}
	Activitate& operator =(const Activitate& a)
	{
		if (this != &a)
		{
			if (this->activitateInceputa == 0 && a.activitateInceputa == 0)
			{
				if (a.denumire.size() > 2)
				{
					this->denumire = a.denumire;

				}
				if (a.durata > 0)
				{
					this->durata = a.durata;

				}
				this->activitateInceputa = a.activitateInceputa;
			}
		}
		return *this;
	}
	string getDenumire()
	{
		return this->denumire;
	}
	int getCod()
	{
		return this->cod;
	}
	int getDurata()
	{
		return this->durata;
	}
	bool getActiviteInceputa()
	{
		return this->activitateInceputa;
	}
	void setDenumire(string denumire)
	{
		if (denumire.size() > 2)
		{
			this->denumire = denumire;

		}
		
	}
	void setDurata(int durata)
	{
		if (durata > 0)
		{
			this->durata = durata;

		}
	
	}
	void setActivitateInceputa(bool activitateInceputa)
	{
		this->activitateInceputa = activitateInceputa;
	}

	friend ostream& operator<<(ostream& out, const Activitate& a)
	{
		out << "Cod activitate: " << a.cod << endl;
		out << "Nume activitate: " << a.denumire << endl;
		out << "Durata activitate: " << a.durata << endl;
		out << "Stare activitate: ";
		if (a.activitateInceputa == 0)
		{
			out << "Activitate neinceputa/terminata !"<<endl;
		}
		else
		{
			out << "Activitate inceputa!" << endl;
		}
		return out;
	}
	friend istream& operator>>(istream& in, Activitate& a)
	{
		if (a.activitateInceputa == 0)
		{
			cout << "Nume activitate: ";
			in >> ws;
			getline(in, a.denumire);
			cout << "Durata activitate: ";
			in >> a.durata;
			a.activitateInceputa = 0;
			return in;
		}
		else
		{
			cout << "Din pacate nu putem modifica o activitate in executie" << endl;
		}
	}
	friend ofstream& operator<<(ofstream& out, const Activitate& a)
	{

		out  << a.denumire << endl;
		out  << a.durata << endl;
		out << a.activitateInceputa << endl;
		return out;
	}
	friend ifstream& operator>>(ifstream& in, Activitate& a)
	{
		
		in >> ws;
		getline(in, a.denumire);
		in >> a.durata;
		in>>a.activitateInceputa;
		return in;
	}
	bool durataPesteOSaptamana()
	{
		return durata >= 7;
	}
	bool operator >(Activitate a)
	{
		return this->durata > a.durata;
	}
	bool operator <(Activitate a)
	{
		return this->durata < a.durata;

	}
	bool operator ==(Activitate a)
	{
		return this->durata == a.durata;
	}
	Activitate operator +(Activitate a)
	{
		Activitate copie = *this;
		copie.durata = this->durata + a.durata;
		return copie;
	}
	Activitate operator +(int durata)
	{
		Activitate copie = *this;
		copie.durata = this->durata + durata;
		return copie;
	}
	Activitate& operator++()
	{
		this->durata++;
		return *this;
	}
	Activitate& operator--()
	{
		if(this->durata >1)
		this->durata--;
		return *this;
	}
	void ExtindeDurataProiect(int durata)
	{
		if(durata >0)
		this->durata += durata;

	}
	virtual int timpNecesarExecutieActivitate()
	{
		return this->durata;
	}
	void incepereActivitate()
	{
		this->activitateInceputa = 1;
		cout << "Activitatea a fost inceputa!" << endl << endl;

	}
	void incetareActivitate()
	{
		this->activitateInceputa = 0;
		cout << "Activitatea a fost incheiata!" << endl << endl;
	}
	float cheltuieli(float sumaCheltuitaZilnic)
	{
		return timpNecesarExecutieActivitate()* sumaCheltuitaZilnic;
	}
};

int Activitate::numarator = 1;
template<typename numeClasa>
bool comparaDurata(numeClasa a, numeClasa b)
{
	return a < b;
}
class ActivitateIntarizata :public Activitate
{
	int zileIntarziere = 0;
public:
	ActivitateIntarizata() :Activitate()
	{

	}
	ActivitateIntarizata(string denumire, int durata,int zileIntarziere) :Activitate(denumire, durata)
	{
		if (zileIntarziere > 0)
		{
			this->zileIntarziere = zileIntarziere;
		}
	}
	ActivitateIntarizata(const ActivitateIntarizata& a) :Activitate(a)
	{
		this->zileIntarziere = a.zileIntarziere;

	}
	~ActivitateIntarizata()
	{

	}
	ActivitateIntarizata &operator =(const ActivitateIntarizata& a)
	{
		if (this != &a)
		{
			Activitate::operator =(a);
			this->zileIntarziere = a.zileIntarziere;

		}
		return *this;
	}
	friend ostream& operator<<(ostream& out, const ActivitateIntarizata& a)
	{
		out << (Activitate)a;
		out << "Zile intarziere: " << a.zileIntarziere;
		out << endl;
		return out;
	}
	friend istream& operator>>(istream& in, ActivitateIntarizata& a)
	{
		in >> (Activitate&)a;
		cout << "Zile intarziere: ";
		in >> a.zileIntarziere;
		return in;
	}
	friend ofstream& operator<<(ofstream& out, const ActivitateIntarizata& a)
	{
		out << (Activitate)a;
		out  << a.zileIntarziere<<endl;
		out << endl;
		return out;

	}
	friend ifstream& operator>>(ifstream& in, ActivitateIntarizata& a)
	{
		in >> (Activitate&)a;
		in >> a.zileIntarziere;
		return in;
	}
	int getZileIntarziere()
	{
		return this->zileIntarziere;
	}
	void setZileIntarziere(int zileIntarziere)
	{
		if (zileIntarziere > 0)
		{
			this->zileIntarziere = zileIntarziere;
		}
	}
	int timpNecesarExecutieActivitate()
	{
		return this->durata+zileIntarziere;
	}
	float cheltuieli(float sumaCheltuitaZilnic)
	{
		return timpNecesarExecutieActivitate() * sumaCheltuitaZilnic;
	}
};
class Proiect
{
	string nume = "";
	int nrActivitati;
	Activitate** activitati;
public:
	Proiect()
	{
		this->nrActivitati = 0;
		this->activitati = NULL;

	}
	int getnrActivitati()
	{
		return this->nrActivitati;
	}
	Activitate** getactivitati()
	{
		return this->activitati;
	}
	Proiect(string nume, int nrActivitati, Activitate** activitati)
	{
		if (nume.size() >= 3)
		{
			this->nume = nume;
		}
		this->nrActivitati = nrActivitati;
		this->activitati = new Activitate * [this->nrActivitati];
		for (int i = 0; i < this->nrActivitati; i++)
		{
			if(activitati[i]->getActiviteInceputa()==0)
			this->activitati[i] = activitati[i];
			else
			{
				this->activitati[i] = new Activitate();
			}
		}
	}
	Proiect(const Proiect& a)
	{
		if (a.nume.size() >= 3)
		{
			this->nume = a.nume;
		}
		this->nrActivitati = a.nrActivitati;
		this->activitati = new Activitate * [this->nrActivitati];
		for (int i = 0; i < this->nrActivitati; i++)
		{
			if (a.activitati[i]->getActiviteInceputa() == 0)
				this->activitati[i] = a.activitati[i];
			else
			{
				this->activitati[i] = new Activitate();
			}

		}
	}
	~Proiect()
	{
		if (this->activitati != NULL)
		{
			delete[]this->activitati;
		}
	}
	Proiect& operator=(const Proiect& a)
	{
		if (this->activitati != NULL)
		{
			delete[]this->activitati;
		}
		this->nrActivitati = a.nrActivitati;
		this->activitati = new Activitate * [this->nrActivitati];
		for (int i = 0; i < this->nrActivitati; i++)
		{
			if (a.activitati[i]->getActiviteInceputa() == 0 && this->activitati[i]->getActiviteInceputa()==0)
				this->activitati[i] = a.activitati[i];
			else
			{
				this->activitati[i] = new Activitate();
			}
		}
	}
	Proiect& operator+=(Activitate& l)
	{
		if (l.getActiviteInceputa() == 0)
		{
			Proiect copie = *this;
			this->activitati = new Activitate * [this->nrActivitati + 1];
			for (int i = 0; i < this->nrActivitati; i++)
			{
				this->activitati[i] = copie.activitati[i];
			}
			this->activitati[this->nrActivitati] = new Activitate(l);
			this->nrActivitati++;
			return *this;
		}
		
	}


	Proiect& operator -=(Activitate& l)
	{
		if (l.getActiviteInceputa() == 0)
		{
			Proiect copie = *this;
			this->activitati = new Activitate * [this->nrActivitati];
			int i = 0;
			int j = 0;
			while ((i < this->nrActivitati) && (j < this->nrActivitati))
			{
				if (copie.activitati[i] != &l)//daca obiectul din vector este diferit de cel introdus ca parametru nu il stergem
				{
					this->activitati[j] = copie.activitati[i];
					j++;
				}

				i++;
			}
			this->nrActivitati = j;
			return *this;
		}
		
	}
	void adaugaActivitate(Activitate& l)
	{
		(*this) += l;
	}

	friend ostream& operator<<(ostream& out, const Proiect& a)
	{
		out << "Nume Proiect: " << a.nume << endl;
		out << "Nr activitati: " << a.nrActivitati << endl;
		out << "activitati: " << endl;
		for (int i = 0; i < a.nrActivitati; i++)
		{
			out << *a.activitati[i] << endl;
		}

		return out;
	}
	friend ofstream& operator<<(ofstream& out, const Proiect& a)
	{
		out  << a.nume << endl;
		out << a.nrActivitati << endl;
		for (int i = 0; i < a.nrActivitati; i++)
		{
			out << *a.activitati[i] << endl;
		}

		return out;
	}
	void incepereActivitate(int index)
	{
		if (index >= 0 && index < this->nrActivitati)
		{
			if (this->activitati[index]->getActiviteInceputa() == 0)
			{
				this->activitati[index]->setActivitateInceputa(1);
				cout << "Activitatea a inceput!" << endl;
			}
			else
			{
				cout << "Activitatea este deja in curs de executie!" << endl;

			}
		}
	}
	void incetareActivitate(int index)
	{
		if (index >= 0 && index < this->nrActivitati)
		{
			if (this->activitati[index]->getActiviteInceputa() == 1)
			{
				this->activitati[index]->setActivitateInceputa(0);
				cout << "Activitatea a fost terminata!" << endl;
			}
			else
			{
				cout << "Activitatea este deja terminata!" << endl;

			}
		}
	}
	string getNume()
	{
		return this->nume;
	}
	void setNume(string nume)
	{
		if (nume.size() >= 3)
		{
			this->nume = nume;
		}
	}
	float durataTotalaProiect()
	{
		float suma = 0;
		for (int i = 0; i < this->nrActivitati; i++)
		{
			suma += this->activitati[i]->timpNecesarExecutieActivitate();
		}
		return suma;
	}
	int getNrActivitati()
	{
		return this->nrActivitati;
	}
	Activitate** getActivitate()
	{
		return this->activitati;
	}
};
int main()
{
	Activitate a;
	Activitate a1("Turnat Fundatie", 5);
	a1.incepereActivitate();
	Activitate a2("Ridicat Pereti", 3);
	a2.incepereActivitate();
	a2.incetareActivitate();
	cout<<a1.getCod() << endl;
	cout<<a1.getDenumire() << endl;
	cout<<a1.getDurata() << endl;
	cout<<a1.getActiviteInceputa() << endl;
	a.setActivitateInceputa(1);
	a.setDenumire("Cumparat Balast");
	a.setDurata(10);
	cout << a.getCod() << endl;
	cout << a.getDenumire() << endl;
	cout << a.getDurata() << endl;
	cout << a.getActiviteInceputa() << endl;
	Activitate a3 = a1;
	cout << a3 << endl;
	Activitate a4 = a2;
	cout << a4 << endl;
	a = a4;
	cout << a << endl;

	++a;
	cout << a << endl;
	--a;
	cout << a << endl;
	Activitate a5 = a4 + a2;
	a5.setDenumire("Rdicare stalpi rezistenta casa");
	cout << a5 << endl;
	a5 = a5 + 6;
	cout << a5 << endl;

	if (a.durataPesteOSaptamana())
	{
		cout << "Activitatea necesita mai mult de o saptamana pentru finalizare!" << endl;
	}
	else
	{
		cout << "Activitatea nu necesita mai mult de o saptamana pentru finalizare!" << endl;
	}
	if (a == a1)
	{
		cout << "Cele doua activitati au aceeasi durata!" << endl;
	}
	else
	{
		cout << "Cele doua activitati nu  au aceeasi durata!" << endl;

	}
	if (a5 > a4)
	{
		cout << "Activitatea " << a5.getDenumire() << " are durata mai mare decat " << a4.getDenumire() << endl;
	}
	else
	{
		cout << "Activitatea " << a5.getDenumire() << " nu are durata mai mare decat " << a4.getDenumire() << endl;

	}
	cout << endl;
	cin >> a1;
	cout << endl;
	Activitate a6;
	/*cin >> a6;*/
	cout << endl;
	cout << a6 << endl<<endl;
	ofstream fisAct("activitate.txt", ios::out);
	fisAct << a1;
	fisAct.close();
	ifstream fisAct1("activitate.txt", ios::in);
	fisAct1 >> a6;
	fisAct1.close();
	cout << a6 << endl;
	cout << "Timpul necesar finalizarii activitati este de : " << a1.timpNecesarExecutieActivitate() << " zile." << endl;
	cout << endl << endl;
	ActivitateIntarizata ai;
	ActivitateIntarizata ai1("Finisare", 9, 2);
	cout<<ai1.getZileIntarziere()<<endl;
	ai.setZileIntarziere(10);
	cout << ai.getZileIntarziere() << endl;
	ActivitateIntarizata ai2 = ai1;
	ai = ai1;

	cout << ai << endl;
	cout << ai1 << endl;
	cout << ai2 << endl;

	/*cin >> ai;*/
	cout << ai << endl << endl;
	ActivitateIntarizata ai4;
	ofstream fisActI("activitateIntarziata.txt", ios::out);
	fisActI << ai1;
	fisActI.close();
	ifstream fisActI1("activitateIntarziata.txt", ios::in);
	fisActI1 >> ai4;
	fisActI1.close();
	cout << ai4 << endl << endl;


	cout << "Timpul necesar finalizarii activitati este de : " << a1.timpNecesarExecutieActivitate() << " zile." << endl;
	cout << "Timpul necesar finalizarii activitati este de : " << ai1.timpNecesarExecutieActivitate() << " zile." << endl;

	ActivitateIntarizata ai8("Finisare", 9, 2);

	Activitate* pa;
	ActivitateIntarizata* pai = new ActivitateIntarizata(ai8);
	pa = pai;

	cout << "Timpul necesar finalizarii activitati este de : " << pa->timpNecesarExecutieActivitate() << " zile." << endl;
	cout << "Timpul necesar finalizarii activitati este de : " << pai->timpNecesarExecutieActivitate() << " zile." << endl;

	cout << "Pentru aceasta activitatea s-au cheltuit: " << a1.cheltuieli(100) << " lei" << endl;
	cout << "Pentru aceasta activitatea s-au cheltuit: " << ai1.cheltuieli(100) << " lei" << endl;
	cout << "Timpul necesar finalizarii activitati este de : " << pa->cheltuieli(100) << " zile." << endl;
	cout << "Timpul necesar finalizarii activitati este de : " << pai->cheltuieli(100) << " zile." << endl;
	cout << endl << endl;

	Activitate a7("Daramat vechituri", 18);
	Activitate* vectActivitati[2];
	vectActivitati[0] = &a5;
	vectActivitati[1] = &a6;
	Proiect p;
	Proiect p1("Ridicarea unui Bloc", 2, vectActivitati);
	Proiect p2 = p1;
	cout << p1 << endl;
	cout << "-----------------------------" << endl;
	cout << p2 << endl;
	cout << "-----------------------------" << endl;


	p.setNume("Construire Hotel");
	cout << endl << p << endl << endl;
	cout << "-----------------------------" << endl;
	p2 += a7;
	cout << p2 << endl;
	p2.incepereActivitate(0);
	cout << "-----------------------------" << endl;
	cout << p2 << endl;
	p2.incepereActivitate(1);
	p2.incetareActivitate(0);
	cout << "-----------------------------" << endl;
	cout << p2 << endl;
	cout << "-----------------------------" << endl;
	p2 -= a6;
	cout << p2 << endl;

	cout << "Proiectul " << p2.getNume() << " se va finaliza in  " << p2.durataTotalaProiect() << " zile." << endl;

	vector<Activitate> vectorActivitate;
	
	vectorActivitate.push_back(a5);
	vectorActivitate.push_back(a1);
	vectorActivitate.push_back(a6);
	vectorActivitate.push_back(a2);
	vectorActivitate.push_back(a3);
	vectorActivitate.push_back(a7);
	
	cout << "------------------------------------" << endl;


	sort(vectorActivitate.begin(), vectorActivitate.end(), comparaDurata<Activitate>);


	for (int i = 0; i < vectorActivitate.size(); i++)
	{
		cout << vectorActivitate[i] << endl; 
	}

}