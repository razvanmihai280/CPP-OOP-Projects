#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;
class Produs 
{
protected:
	const int idProdus;
	static int numarator;
	char* numeProdus;
	float cantitate;
	float pretUnitar;
public:
	Produs() :idProdus(numarator++)
	{
		this->numeProdus = new char[strlen("Necunoscut") + 1];
		strcpy(this->numeProdus, "Necunoscut");
		this->cantitate = 0;
		this->pretUnitar = 0;

	}

	Produs(const char* numeProdus,float cantitate, float pretUnitar) :idProdus(numarator++)
	{
		if (strlen(numeProdus) >= 3)
		{
			this->numeProdus = new char[strlen(numeProdus) + 1];
			strcpy(this->numeProdus, numeProdus);
		}
		else
		{
			this->numeProdus = new char[strlen("Necunoscut") + 1];
			strcpy(this->numeProdus, "Necunoscut");
		}
		if (pretUnitar > 0)
		{
			this->pretUnitar = pretUnitar;
		}
		else
		{
			this->pretUnitar = 0;
		}
		this->cantitate = cantitate;
	}

	virtual float pretCuDiscount()
	{
		return this->pretUnitar;
	}
	float pretInEuroProdus()
	{
		return this->pretUnitar / 4.8;
	}
	char* getNumeProdus()
	{
		return this->numeProdus;
	}
	const int getIdProdus()
	{
		return this->idProdus;
	}
	float getpretUnitar()
	{
		return this->pretUnitar;
	}
	float getCantitate()
	{
		return this->cantitate;
	}
	void setNumeProdus(const char* numeProdus)
	{
		if (strlen(numeProdus) >= 3)
		{
			this->numeProdus = new char[strlen(numeProdus) + 1];
			strcpy(this->numeProdus, numeProdus);
		}
	}
	void setpretUnitar(float pretUnitar)
	{
		if (pretUnitar > 0)
		{
			this->pretUnitar = pretUnitar;
		}
	}
	void setCantitate(float cantitate)
	{
		if (cantitate > 0)
		{
			this->cantitate = cantitate;
		}
	}
	Produs(const Produs& p) :idProdus(p.idProdus)
	{
		if (strlen(p.numeProdus) >= 3)
		{
			this->numeProdus = new char[strlen(p.numeProdus) + 1];
			strcpy(this->numeProdus, p.numeProdus);
		}
		else
		{
			this->numeProdus = new char[strlen("Necunoscut") + 1];
			strcpy(this->numeProdus, "Necunoscut");
		}
		if (p.cantitate > 0)
		{
			this->cantitate = p.cantitate;
		}
		else
		{
			this->cantitate = 0;
		}
		if (p.pretUnitar > 0)
		{
			this->pretUnitar = p.pretUnitar;
		}
		else
		{
			this->pretUnitar = 0;
		}
	}
	 ~Produs()
	{
		if (this->numeProdus != nullptr)
			delete[]this->numeProdus;
	}
	Produs& operator=(const Produs& p)
	{
		if (this != &p)
		{
			if (this->numeProdus != nullptr)
				delete[]this->numeProdus;
			if (strlen(p.numeProdus) >= 3)
			{
				this->numeProdus = new char[strlen(p.numeProdus) + 1];
				strcpy(this->numeProdus, p.numeProdus);
			}
			else
			{
				this->numeProdus = new char[strlen("Necunoscut") + 1];
				strcpy(this->numeProdus, "Necunoscut");
			}
			if (p.pretUnitar > 0)
			{
				this->pretUnitar = p.pretUnitar;
			}
			else
			{
				this->pretUnitar = 0;
			}
			if (p.cantitate > 0)
			{
				this->cantitate = p.cantitate;
			}
			else
			{
				this->cantitate = 0;
			}
		}
		return *this;
	}
	
	bool operator==(const Produs& p)
	{
		return this->cantitate == p.cantitate;
	}

	bool operator<(const Produs& p)
	{
		return this->pretUnitar < p.pretUnitar;
	}

	Produs& operator+=(float valoare)
	{
		this->pretUnitar += valoare;
		return *this;
	}
	Produs& operator-=(float cantitate)
	{
		this->cantitate += cantitate;
		return *this;
	}
	friend ostream& operator<<(ostream& out, const Produs& p)
	{

		out << p.idProdus << " " << p.numeProdus << " " << p.cantitate << " " << p.pretUnitar << endl;
		return out;
	}
	friend ofstream& operator<<(ofstream& out, const Produs& p)
	{
		out << p.numeProdus << endl << p.pretUnitar <<endl<< p.cantitate <<endl;
		return out;
	}
	friend istream& operator>>(istream& in, Produs& p)
	{
		delete[]p.numeProdus;
		cout << "Introduceti numele Produsului: ";
		char aux[100];
		in >> ws;
		in.getline(aux, 99);
		p.numeProdus = new char[strlen(aux) + 1];
		strcpy(p.numeProdus, aux);
		cout << "Introduceti pretul Produsului: ";
		in >> p.pretUnitar;
		cout << "Introduceti cantitatea Produsului: ";
		in >> p.cantitate;
		return in;
	}
	friend ifstream& operator>>(ifstream& in, Produs& p)
	{
		delete[]p.numeProdus;
		char aux[100];
		in >> ws;
		in.getline(aux, 99);
		in >> ws;
		p.numeProdus = new char[strlen(aux) + 1];
		strcpy(p.numeProdus, aux);
		in >> p.pretUnitar;
		in >> p.cantitate;
		return in;
	}
};
int Produs::numarator = 1;
class ProdusPromotional :public Produs
{
	string promotie;
	float discount;
public:
	ProdusPromotional() :Produs()
	{
		this->promotie = "Necunoscut";
		this->discount = 0;
	}
	ProdusPromotional(const char* numeProdus,float cantitate, float pretProdus, string promotie, float discount) :Produs(numeProdus, cantitate,pretProdus)
	{
	
			this->promotie = promotie;
		
	
		if (discount >= 0 && discount <= 100)
		{
			this->discount = discount;
		}
		else if (discount < 0)
		{
			this->discount = 0;
		}
		else if (discount > 100)
		{
			throw new exception("Valoare discountului a depasit 100!");
		}
	}
	ProdusPromotional(const ProdusPromotional& p) :Produs(p)
	{
		
			this->promotie = p.promotie;

			this->discount = p.discount;
		
	}
	ProdusPromotional(const Produs& p) :Produs(p)
	{
		this->promotie = "Nu are";
		this->discount = 0;
	}
	~ProdusPromotional()
	{

	}
	float pretCuDiscount()
	{
		float pretCuDiscount = this->pretUnitar - this->pretUnitar * discount / 100.0;
		return pretCuDiscount - - 19 * pretCuDiscount / 100.0;
	}
	ProdusPromotional& operator=(const ProdusPromotional& p)
	{
		if (this != &p)
		{
			Produs::operator =(p);
			this->promotie = p.promotie;

			this->discount = p.discount;
		}
		return *this;
	}
	float getDiscount()
	{
		return this->discount;
	}
	string getpromotie()
	{
		return this->promotie;
	}
	void setDiscount(float discount)
	{
		this->discount = discount;
	}
	void setpromotie(string promotie)
	{
		if (promotie.size() > 3)
		{
			this->promotie = promotie;
		}
	}
	bool operator>(const ProdusPromotional& p)
	{
		if (discount >= 0 && discount <= 100)
		{
			this->discount = discount;
		}
	}

	friend ostream& operator<<(ostream& out, const ProdusPromotional& p)
	{
		out << (Produs&)p;
		string spatiu = "\t\t\t";
		out << p.promotie << spatiu << p.discount << endl;
		return out;
	}

	friend istream& operator>>(istream& in, ProdusPromotional& p)
	{
		in >> (Produs&)p;
		cout << "Introduceti promotia Produsului: ";
		in >> ws;
		getline(in, p.promotie);
		cout << "Introduceti discountul Produsului: ";
		in >> p.discount;
		return in;
	}

	friend ofstream& operator<<(ofstream& out, const ProdusPromotional& p)
	{
		out << (Produs&)p;
		out << p.promotie << endl << p.discount << endl;
		return out;
	}

	friend ifstream& operator>>(ifstream& in, ProdusPromotional& p)
	{
		in >> (Produs&)p;
		in >> ws;
		getline(in, p.promotie);
		in >> p.discount;
		return in;
	}

};
class Vanzare
{
	int zi = 1;
	int luna = 1;
	int an = 2020;
	int nrProduse;
	Produs** produse;

public:

	Vanzare()
	{
		this->nrProduse = 0;
		this->produse = nullptr;
	}
	Vanzare(int zi, int luna, int an, int nrProduse, Produs** produse)
	{
		this->zi = zi;
		this->luna = luna;
		this->an = an;
		if (nrProduse > 0 && produse != nullptr)
		{
			this->nrProduse = nrProduse;
			this->produse = new Produs * [this->nrProduse];
			for (int i = 0; i < nrProduse; i++)
			{
				this->produse[i] = produse[i];
			}
		}
		else
		{
			this->nrProduse = 0;
			this->produse = nullptr;
		}
	}
	int getZi()
	{
		return this->zi;
	}
	int getLuna()
	{
		return this->luna;

	}
	int getAn()
	{
		return this->an;
	}
	void setZi(int zi)
	{
		this->zi = zi;
	}
	void setLuna(int luna)
	{
		this->luna = luna;

	}
	void setAn(int an)
	{
		this->an = an;
	}
	void setProduse(int nrProduse, Produs** produse)
	{
		if (nrProduse > 0 && produse != nullptr)
		{
			this->nrProduse = nrProduse;
			this->produse = new Produs * [this->nrProduse];
			for (int i = 0; i < nrProduse; i++)
			{
				this->produse[i] = produse[i];
			}
		}
	}
	~Vanzare()
	{
		if (this->produse != nullptr)
		{
			delete[]this->produse;
		}
	}
	Vanzare(const Vanzare& c)
	{

		this->zi = c.zi;
		this->luna = c.luna;
		this->an = c.an;
		if (c.nrProduse > 0 && c.produse != nullptr)
		{
			this->nrProduse = c.nrProduse;
			this->produse = new Produs * [this->nrProduse];
			for (int i = 0; i < c.nrProduse; i++)
			{
				this->produse[i] = c.produse[i];
			}
		}
		else
		{
			this->nrProduse = 0;
			this->produse = nullptr;
		}
	}
	Vanzare& operator=(const Vanzare& c)
	{
		if (this != &c)
		{
			this->zi = c.zi;
			this->luna = c.luna;
			this->an = c.an;
			if (this->produse != nullptr)
			{
				delete[]this->produse;
			}
			if (c.nrProduse > 0 && c.produse != nullptr)
			{
				this->nrProduse = c.nrProduse;
				this->produse = new Produs * [this->nrProduse];
				for (int i = 0; i < c.nrProduse; i++)
				{
					this->produse[i] = c.produse[i];
				}
			}
			else
			{
				this->nrProduse = 0;
				this->produse = nullptr;
			}
		}
		return *this;
	}
	friend ostream& operator<<(ostream& out, Vanzare c)
	{
		out << "Data: " << c.zi << "/" << c.luna << "/" << c.an << endl;
		out << "Numar produse: " << c.nrProduse << endl;
		out << "Produse: " << endl;
		for (int i = 0; i < c.nrProduse; i++)
		{
			out << *c.produse[i];
		}
		return out;
	}
	friend ofstream& operator<<(ofstream& file, const Vanzare& c)
	{
		file << c.zi << " " << c.luna << " " << c.an << endl;
		file << c.nrProduse << endl << endl;
		for (int i = 0; i < c.nrProduse; i++)
		{
			file << *c.produse[i] << endl;
		}
		return file;
	}

	friend istream& operator>>(istream& in, Vanzare& c)
	{
		delete[]c.produse;
		cout << "Introduceti ziua: ";
		in >> c.zi;
		cout << "Introduceti luna: ";
		in >> c.luna;
		cout << "Introduceti an: ";
		in >> c.an;
		cout << "Introduceti numarul de produse: ";
		in >> c.nrProduse;
		c.produse = new Produs * [c.nrProduse];
		cout << "Introduceti produsele: " << endl;
		for (int i = 0; i < c.nrProduse; i++)
		{
			c.produse[i] = new Produs();
			in >> *c.produse[i];
		}
		return in;
	}
	friend ifstream& operator>>(ifstream& in, Vanzare& c)
	{
		delete[]c.produse;
		in >> c.zi;
		in >> c.luna;
		in >> c.an;
		in >> c.nrProduse;
		c.produse = new Produs * [c.nrProduse];
		for (int i = 0; i < c.nrProduse; i++)
		{
			c.produse[i] = new Produs();
			in >> *c.produse[i];
		}
		return in;
	}
	Vanzare& operator+=(Produs& p)
	{
		Vanzare copie = *this;
		delete[]produse;
		this->nrProduse++;
		this->produse = new Produs * [this->nrProduse];
		for (int i = 0; i < copie.nrProduse; i++)
		{
			this->produse[i] = copie.produse[i];
		}
		this->produse[this->nrProduse - 1] = &p;
		return *this;
	}
	Vanzare& operator -=(Produs& p)
	{
		int nr = 0;
		Vanzare copie = *this;
		for (int i = 0; i < this->nrProduse; i++)
		{
			if (this->produse[i] == &p)
			{
				nr++;
			}
		}
		delete[]this->produse;
		this->nrProduse = this->nrProduse - nr;
		this->produse = new Produs * [this->nrProduse];
		int poz = 0;
		for (int i = 0; i < copie.nrProduse; i++)
		{
			if (copie.produse[i] != &p)
			{
				this->produse[poz] = copie.produse[i];
				poz++;
			}
		}
		return *this;
	}

	Produs& operator[](int index)
	{
		if (index >= 0 && index < this->nrProduse)
		{
			return *this->produse[index];
		}
	}
	Produs** getProdus()
	{
		return this->produse;
	}
	int getNrProduse()
	{
		return this->nrProduse;
	}
	explicit operator float()
	{
		float suma = 0;
		for (int i = 0; i < this->nrProduse; i++)
		{
			suma += this->produse[i]->getpretUnitar();
		}
		return suma;
	}
};
class Alimentara
{
	static string numeAlimentara;
	int nrProduse;
	Produs** produse;
	int nrVanzari;
	Vanzare**  vanzari;
public:
	Alimentara()
	{
		this->nrProduse = 0;
		this->produse = nullptr;
		this->nrVanzari = 0;
		this-> vanzari = nullptr;
	}
	Alimentara(int nrProduse, Produs** produse, int nrVanzari, Vanzare**  vanzari)
	{
		if (nrProduse > 0 && produse != nullptr)
		{
			this->nrProduse = nrProduse;
			this->produse = new Produs * [this->nrProduse];
			for (int i = 0; i < nrProduse; i++)
			{
				this->produse[i] = produse[i];
			}
		}
		else
		{
			this->nrProduse = 0;
			this->produse = nullptr;
		}
		if (nrVanzari > 0 &&  vanzari != nullptr)
		{
			this->nrVanzari = nrVanzari;
			this-> vanzari = new Vanzare * [this->nrVanzari];
			for (int i = 0; i < nrVanzari; i++)
			{
				this-> vanzari[i] =  vanzari[i];
			}
		}
		else
		{
			this->nrVanzari = 0;
			this-> vanzari = nullptr;
		}
	}
	Produs** getProdus()
	{
		return this->produse;
	}
	int getNrProduse()
	{
		return this->nrProduse;
	}
	Vanzare** getVanzare()
	{
		return this->vanzari;
	}
	int getnrVanzari()
	{
		return this->nrVanzari;
	}
	static string getNume()
	{
		return numeAlimentara;
	}
	void setProduse(int nrProduse, Produs** produse)
	{
		if (nrProduse > 0 && produse != nullptr)
		{
			this->nrProduse = nrProduse;
			this->produse = new Produs * [this->nrProduse];
			for (int i = 0; i < nrProduse; i++)
			{
				this->produse[i] = produse[i];
			}
		}
	}
	void setVanzari(int nrVanzari, Vanzare**  vanzari)
	{
		if (nrVanzari > 0 &&  vanzari != nullptr)
		{
			this->nrVanzari = nrVanzari;
			this-> vanzari = new Vanzare * [this->nrVanzari];
			for (int i = 0; i < nrVanzari; i++)
			{
				this-> vanzari[i] =  vanzari[i];
			}
		}
	}
	~Alimentara()
	{
		if (this->produse != nullptr)
		{
			delete[]this->produse;
		}
		if (this-> vanzari != nullptr)
		{
			delete[]this-> vanzari;
		}
	}
	Alimentara(const Alimentara& c)
	{
		if (c.nrProduse > 0 && c.produse != nullptr)
		{
			this->nrProduse = c.nrProduse;
			this->produse = new Produs * [this->nrProduse];
			for (int i = 0; i < c.nrProduse; i++)
			{
				this->produse[i] = c.produse[i];
			}
		}
		else
		{
			this->nrProduse = 0;
			this->produse = nullptr;
		}
		if (c.nrVanzari > 0 && c. vanzari != nullptr)
		{
			this->nrVanzari = c.nrVanzari;
			this-> vanzari = new Vanzare * [this->nrVanzari];
			for (int i = 0; i < c.nrVanzari; i++)
			{
				this-> vanzari[i] = c. vanzari[i];
			}
		}
		else
		{
			this->nrVanzari = 0;
			this-> vanzari = nullptr;
		}
	}
	Alimentara& operator=(const Alimentara& c)
	{
		if (this != &c)
		{
			if (this->produse != nullptr)
			{
				delete[]this->produse;
			}
			if (this-> vanzari != nullptr)
			{
				delete[]this-> vanzari;
			}
			if (c.nrProduse > 0 && c.produse != nullptr)
			{
				this->nrProduse = c.nrProduse;
				this->produse = new Produs * [this->nrProduse];
				for (int i = 0; i < c.nrProduse; i++)
				{
					this->produse[i] = c.produse[i];
				}
			}
			else
			{
				this->nrProduse = 0;
				this->produse = nullptr;
			}
			if (c.nrVanzari > 0 && c. vanzari != nullptr)
			{
				this->nrVanzari = c.nrVanzari;
				this-> vanzari = new Vanzare * [this->nrVanzari];
				for (int i = 0; i < c.nrVanzari; i++)
				{
					this-> vanzari[i] = c. vanzari[i];
				}
			}
			else
			{
				this->nrVanzari = 0;
				this-> vanzari = nullptr;
			}
		}
		return *this;
	}
	void adaugaVanzare(Vanzare& p)
	{
		Alimentara copie = *this;
		delete[] vanzari;
		this->nrVanzari++;
		this->vanzari = new Vanzare * [this->nrVanzari];
		for (int i = 0; i < copie.nrVanzari; i++)
		{
			this->vanzari[i] = copie.vanzari[i];
		}
		this->vanzari[this->nrVanzari - 1] = new Vanzare(p);

	}
	void EliminaVanzare(Vanzare& p)
	{
		int nr = 0;
		Alimentara copie = *this;
		for (int i = 0; i < this->nrVanzari; i++)
		{
			if (this->vanzari[i] == &p)
			{
				nr++;
			}
		}
		delete[]this->vanzari;
		this->nrVanzari = this->nrVanzari - nr;
		this->vanzari = new Vanzare * [this->nrVanzari];
		int poz = 0;
		for (int i = 0; i < copie.nrVanzari; i++)
		{
			if (copie.vanzari[i] != &p)
			{
				this->vanzari[poz] = copie.vanzari[i];
				poz++;
			}
		}

	}
	Alimentara& operator+=(Produs& p)
	{
		Alimentara copie = *this;
		delete[]produse;
		this->nrProduse++;
		this->produse = new Produs * [this->nrProduse];
		for (int i = 0; i < copie.nrProduse; i++)
		{
			this->produse[i] = copie.produse[i];
		}
		this->produse[this->nrProduse - 1] = new Produs(p);
		return *this;
	}
	Alimentara& operator -=(Produs& p)
	{
		int nr = 0;
		Alimentara copie = *this;
		for (int i = 0; i < this->nrProduse; i++)
		{
			if (this->produse[i] == &p)
			{
				nr++;
			}
		}
		delete[]this->produse;
		this->nrProduse = this->nrProduse - nr;
		this->produse = new Produs * [this->nrProduse];
		int poz = 0;
		for (int i = 0; i < copie.nrProduse; i++)
		{
			if (copie.produse[i] != &p)
			{
				this->produse[poz] = copie.produse[i];
				poz++;
			}
		}
		return *this;
	}
	friend ostream& operator<<(ostream& out, Alimentara c)
	{
		out << "Numar Produse in Alimentara: " << c.nrProduse << endl << endl;
		out << " Produse in Alimentara: "<<endl;
		for (int i = 0; i < c.nrProduse; i++)
		{
			out << *c.produse[i] << endl;
		}
		out << "Numar vanzari : " << c.nrVanzari << endl << endl;
		out << "Vanzari:" << endl<<endl;
		for (int i = 0; i < c.nrVanzari; i++)
		{
			out << *c.vanzari[i] << endl << endl;
		}
		return out;
	}
	friend ofstream& operator<<(ofstream& file, const Alimentara& c)
	{
		file << c.nrProduse << endl << endl;
		for (int i = 0; i < c.nrProduse; i++)
		{
			file << *c.produse[i] << endl;
		}

		file << c.nrVanzari << endl << endl;
		for (int i = 0; i < c.nrVanzari; i++)
		{
			file << *c. vanzari[i] << endl;


		}
		return file;
	}
	friend istream& operator>>(istream& in, Alimentara& c)
	{
		delete[]c.produse;
		delete[]c. vanzari;
		cout << "Introduceti numarul de produse: ";
		in >> c.nrProduse;
		c.produse = new Produs * [c.nrProduse];
		cout << "Introduceti produsele: " << endl;
		for (int i = 0; i < c.nrProduse; i++)
		{
			c.produse[i] = new Produs();
			in >> *c.produse[i];
		}
		cout << "Introduceti numarul de  vanzari: ";
		in >> c.nrVanzari;
		c. vanzari = new Vanzare * [c.nrVanzari];
		cout << "Introduceti  vanzarile: " << endl;
		for (int i = 0; i < c.nrVanzari; i++)
		{
			c. vanzari[i] = new Vanzare();
			in >> *c. vanzari[i];
		}
		return in;
	}
	friend ifstream& operator>>(ifstream& in, Alimentara& c)
	{
		delete[]c.produse;
		in >> c.nrProduse;
		c.produse = new Produs * [c.nrProduse];
		for (int i = 0; i < c.nrProduse; i++)
		{
			c.produse[i] = new Produs();
			in >> *c.produse[i];
		}
		delete[]c. vanzari;
		in >> c.nrVanzari;
		c. vanzari = new Vanzare * [c.nrVanzari];
		for (int i = 0; i < c.nrVanzari; i++)
		{
			c. vanzari[i] = new Vanzare();
			in >> *c. vanzari[i];
		}
		return in;
	}
	

	
};


int main()
{

	Produs p1("Faina", 500, 25);
	Produs p2("Coca-Cola", 500, 3);
	Produs p3("Biscuiti Oreo", 500, 6);


	cout << "Getteri: " << endl<<endl;
	cout << p1.getIdProdus() << endl;
	cout << p1.getNumeProdus() << endl;
	cout << p1.getpretUnitar() << endl;
	cout << p1.getCantitate() << endl;
	cout << endl << endl;

	cout << "Setteri: " << endl << endl;
	p1.setNumeProdus("Ciocolata");
	p1.setpretUnitar(200.5);
	p1.setCantitate(300);
	cout << p1.getNumeProdus() << endl;
	cout << p1.getpretUnitar() << endl;
	cout << p1.getCantitate() << endl;
	cout << endl << endl;


	cout << "Constructor de copiere" << endl << endl;
	Produs p4 = p1;
	cout << p4 << endl;
	cout << endl << endl << endl;


	cout << "Operator =" << endl << endl;
	p1 = p3;
	cout << p1 << endl;
	cout << p3 << endl;
	cout << endl << endl << endl;

	cout << "Metode" << endl << endl;
	cout <<"Pret fara tva : "<< p1.pretCuDiscount() << endl;
	cout << "Pret in euro produs: " << p1.pretInEuroProdus() << endl;


	cout << "Operator +=" << endl << endl;
	p1 += 500;
	cout << p1 << endl;
	cout << endl << endl << endl;


	

	cout << "Operator -=" << endl << endl;
	p1 -= 50;
	cout << p1 << endl;
	cout << endl << endl << endl;

	cout << "Operator ==" << endl << endl;
	if (p1 == p4)
	{
		cout << "Cele doua produse au aceeasi cantitate " << endl;
	}
	else
	{
		cout << "Cele doua produse nu au aceeasi cantitate " << endl;

	}
	cout << endl << endl << endl;


	cout << "Operator <" << endl << endl;
	if (p1 < p2)
	{
		cout << "Produsul p2 are pretul mai mare decat p1" << endl;
	}
	else
	{
		cout << "Produsul p1 are pretul mai mare decat p2" << endl;

	}

	cout << endl << endl << endl;


	cout << "Operator << si >>" << endl << endl;
	/*cin >> p4;*/
	cout << p4 << endl;
	cout << endl << endl << endl;

	cout << "Fisiere text " << endl << endl;
	Produs p6;
	ofstream f("produs.txt");
	f << p4 << endl;
	f.close();
	ifstream g("produs.txt");
	g >> p6;
	cout << p6 << endl;
	cout << endl << endl << endl;

	cout << "Clasa derivata";
	cout << endl << endl << endl;
	ProdusPromotional pp("Bere Heineken", 500, 23, "Reduceri Beri", 10);
	ProdusPromotional pp1 = pp;
	ProdusPromotional pp2;
	pp2 = pp1;

	cout<<pp1.getDiscount() << endl;
	cout<<pp1.getpromotie() << endl;

	cout << "Pretul fara tva al unui produs promotional este: " << pp.pretCuDiscount() << endl;

	cout << pp1 << endl;
	cout << pp2 << endl;
	cout << pp << endl;
	//
	//cin >> pp;
	cout << pp;


	cout << "Fisiere text " << endl << endl;
	Produs pp6;
	ofstream f1("produsPromotional.txt");
	f1 << pp2 << endl;
	f1.close();
	ifstream g1("produsPromotional.txt");
	g1 >> pp6;
	cout << pp6 << endl;
	cout << endl << endl << endl;



	cout << endl << endl << endl;

	cout << "Clasa Vanzari!" << endl << endl;
	Produs* vanzareProd[2];
	vanzareProd[0] = &p1;
	vanzareProd[1] = &p2;
	Vanzare v(22, 11, 2020, 2, vanzareProd);
	Vanzare v1(27, 11, 2020, 2, vanzareProd);
	Vanzare v2;
	v2 = v1;
	Vanzare v3 = v2;

	Vanzare v4;
	v3 += pp;
	cout << v3 << endl;
	//cin >> v2;
	cout << v2 << endl;
	cout << "Fisiere text " << endl << endl;
	ofstream fv1("vanzari.txt");
	fv1 << v2 << endl;
	fv1.close();
	ifstream gv1("vanzari.txt");
	gv1 >> v4;
	cout << v4 << endl;
	cout << endl << endl << endl;

	cout << v << endl;


	cout << "Clasa Alimentara " << endl << endl;

	Produs** listaProd = new Produs * [4];
	listaProd[0] = &p1;
	listaProd[1] = &p2;
	listaProd[2] = &p3;
	listaProd[3] = &p4;
	Vanzare* vecVanzari[4];
	vecVanzari[0] = &v;
	vecVanzari[1] = &v1;
	vecVanzari[2] = &v2;
	vecVanzari[3] = &v3;
	Alimentara a(4, listaProd, 3, vecVanzari);
	cout << a << endl;
	Alimentara a1 = a;
	Alimentara a2;
	a2 = a;
	cout << a1 << endl;
	cout << a2 << endl;
	cout << "Adauga produs si comanda "<< endl << endl;
	a.adaugaVanzare(v3);
	a += p6;
	cout << a << endl;
	cout << endl << endl << endl;


	/*cin >> a;*/
	cout << a << endl;

	Alimentara a3;
	ofstream fa1("alimentara.txt");
	fa1 << a << endl;
	fa1.close();
	ifstream ga1("alimentara.txt");
	ga1 >> a3;
	cout << a3;
	cout << "Meniu" << endl;
	cout << "1.Vizualizare produse" << endl;
	cout << "2.Vizualizare Comenzi" << endl;
	cout << "Selectati optiunea!" << endl;
	int comandaMeniu;
	cin >> comandaMeniu;
	if (comandaMeniu == 1)
	{
		for (int i = 0; i < a.getNrProduse(); i++)
		{
			cout << *a.getProdus()[i] << endl;
		}
	}
	if (comandaMeniu == 2)
	{
		for (int i = 0; i < a.getnrVanzari(); i++)
		{
			cout << *a.getVanzare()[i] << endl;
		}
	}
	else
	{
		cout << "Valoarea selectata nu este introdusa in meniu!" << endl;
	}

}