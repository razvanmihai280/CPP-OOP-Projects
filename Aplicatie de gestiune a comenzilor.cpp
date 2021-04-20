#include<iostream>
#include<string>
#include<algorithm>
#include<fstream>
#include<vector>
#include<stdlib.h>
using namespace std;
class ExcepetieTratare :public exception
{

};
struct Ora
{
	int ore;
	int minute;
	int secunde;
	
};
struct Data
{
	int zi;
	int luna;
	int an;
	
};
class CalculComanda
{

public:
	virtual float CalculareComanda() = 0;
};
class Livrare
{
	 int id;
	string numeLivrator;
public:
	Livrare() 
	{
		this->id = 0;
		this->numeLivrator = "Necunoscut";
	}
	Livrare(int id, string numeLivrator) 
	{
		this->id = id;
		if (numeLivrator.size() >= 3)
		{
			this->numeLivrator = numeLivrator;
		}
		else
		{
			this->numeLivrator = "Necunoscut";
		}
	}
	Livrare(const Livrare& l):id(l.id)
	{
		this->id = l.id;
		if (l.numeLivrator.size() >= 3)
		{
			this->numeLivrator = l.numeLivrator;
		}
		else
		{
			this->numeLivrator = "Necunoscut";
		}
	}
	Livrare& operator=(const Livrare& l)
	{
		this->id = l.id;

		if (l.numeLivrator.size() >= 3)
		{
			this->numeLivrator = l.numeLivrator;
		}
		else
		{
			this->numeLivrator = "Necunoscut";
		}
		return *this;
	}
	~Livrare()
	{
		
	}
	friend ostream& operator<<(ostream& out, const Livrare& l)
	{
		out << "Id livrator= " << l.id << endl;
		out << "Nume livrator= " << l.numeLivrator << endl;
		return out;
	}
	friend istream& operator>>(istream& in, Livrare& l)
	{
		cout << "Id livrator= ";
		cin >> l.id;
		cout << "Nume livrator= ";
		getline(in, l.numeLivrator);
		return in;
	}
	friend ofstream& operator<<(ofstream& out, const Livrare& l)
	{
		out << l.id << endl;
		out  << l.numeLivrator << endl;
		return out;
	}
	friend ifstream& operator>>(ifstream& in, Livrare& l)
	{
		in >> l.id;
		in>>ws;
		getline(in, l.numeLivrator);
		return in;
	}
	bool operator ==(Livrare l)
	{
		return this->numeLivrator == l.numeLivrator;
	}

};
class Comanda:public CalculComanda
{
protected:
	const int idComanda;
	static int nrComanda;
	string numeClient;
	Ora oraComanda;
	Data comandaData;
	int nrProduse;
	string* vectorProduse;
	float* pretVectorProduse;
public:
	Ora getOra()
	{
		return this->oraComanda;
	}
	Data getData()
	{
		return this->comandaData;
	}
	Comanda() :idComanda(nrComanda++)
	{
		this->numeClient = "Anonim";
		this->oraComanda.ore = 0;
		this->oraComanda.minute = 0;
		this->oraComanda.secunde = 0;
		this->comandaData.zi = 1;
		this->comandaData.luna = 1;
		this->comandaData.an = 2020;
		this->nrProduse = 0;
		this->pretVectorProduse = NULL;
		this->vectorProduse = NULL;
	}
	const int getIdComanda()
	{
		return this->idComanda;
	}
	string getNumeClient()
	{
		return this->numeClient;
	}
	int getNrProduse()
	{
		return this->nrProduse;
	}
	string* getVectorProduse()
	{
		return this->vectorProduse;
	}
	float* getPretVectorProduse()
	{
		return this->pretVectorProduse;
	}
	void setNumeClient(string numeClient)
	{
		if (numeClient.size() > 2)
		{
			this->numeClient = numeClient;
		}
		else throw ExcepetieTratare();
	}
	void setProduse(int nrProduse, string* vectorProduse, float* pretVectorProduse)
	{
		if (nrProduse > 0 && vectorProduse != NULL && pretVectorProduse != NULL)
		{
			this->nrProduse = nrProduse;
			this->vectorProduse = new string[this->nrProduse];
			for (int i = 0; i < this->nrProduse; i++)
			{
				this->vectorProduse[i] = vectorProduse[i];
			}
			this->pretVectorProduse = new float[nrProduse];
			for (int i = 0; i < this->nrProduse; i++)
			{
				this->pretVectorProduse[i] = pretVectorProduse[i];
			}
		}
	}
	Comanda(string numeClient, Ora oraComanda, Data comandaData, int nrProduse, string* vectorProduse, float* pretVectorProduse) :idComanda(nrComanda++)
	{
		if (numeClient.size() > 2)
		{
			this->numeClient = numeClient;
		}
		else
		{
			this->numeClient = "Anonim";

		}

		this->oraComanda.ore = oraComanda.ore;
		this->oraComanda.minute = oraComanda.minute;
		this->oraComanda.secunde = oraComanda.secunde;
		if (comandaData.zi > 0 && comandaData.zi <= 31)
		{
			this->comandaData.zi = comandaData.zi;
		}
		else if (comandaData.zi <= 0)
		{
			this->comandaData.zi = 1;
		}
		else if (comandaData.zi > 31)
		{
			this->comandaData.zi = 31;
		}
		if (comandaData.luna > 0 && comandaData.luna <= 12)
		{
			this->comandaData.luna = comandaData.luna;
		}
		else if (comandaData.luna <= 0)
		{
			this->comandaData.luna = 1;
		}
		else if (comandaData.luna > 12)
		{
			this->comandaData.luna = 12;
		}
		if (comandaData.an >= 2000 && comandaData.an <= 2020)
		{
			this->comandaData.an = comandaData.an;
		}
		else if (comandaData.an < 2000)
		{
			this->comandaData.an = 2000;
		}
		else if (comandaData.an > 2020)
		{
			this->comandaData.an = 2020;
		}
		if (nrProduse > 0 && vectorProduse != NULL && pretVectorProduse != NULL)
		{
			this->nrProduse = nrProduse;
			this->vectorProduse = new string[this->nrProduse];
			for (int i = 0; i < this->nrProduse; i++)
			{
				this->vectorProduse[i] = vectorProduse[i];
			}
			this->pretVectorProduse = new float[nrProduse];
			for (int i = 0; i < this->nrProduse; i++)
			{
				this->pretVectorProduse[i] = pretVectorProduse[i];
			}
		}
		else
		{
			this->nrProduse = 0;
			this->vectorProduse = NULL;
			this->pretVectorProduse = NULL;
		}
	}
	Comanda(const Comanda& c) :idComanda(c.idComanda)
	{
		if (c.numeClient.size() > 2)
		{
			this->numeClient = c.numeClient;
		}
		else
		{
			this->numeClient = "Anonim";

		}

		this->oraComanda.ore = c.oraComanda.ore;
		this->oraComanda.minute = c.oraComanda.minute;
		this->oraComanda.secunde = c.oraComanda.secunde;
		if (c.comandaData.zi > 0 && c.comandaData.zi <= 31)
		{
			this->comandaData.zi = c.comandaData.zi;
		}
		else if (c.comandaData.zi <= 0)
		{
			this->comandaData.zi = 1;
		}
		else if (c.comandaData.zi > 31)
		{
			this->comandaData.zi = 31;
		}
		if (c.comandaData.luna > 0 && c.comandaData.luna <= 12)
		{
			this->comandaData.luna = c.comandaData.luna;
		}
		else if (comandaData.luna <= 0)
		{
			this->comandaData.luna = 1;
		}
		else if (comandaData.luna > 12)
		{
			this->comandaData.luna = 12;
		}
		if (c.comandaData.an >= 2000 && c.comandaData.an <= 2020)
		{
			this->comandaData.an = c.comandaData.an;
		}
		else if (c.comandaData.an < 2000)
		{
			this->comandaData.an = 2000;
		}
		else if (c.comandaData.an > 2020)
		{
			this->comandaData.an = 2020;
		}
		if (c.nrProduse > 0 && c.vectorProduse != NULL && c.pretVectorProduse != NULL)
		{
			this->nrProduse = c.nrProduse;
			this->vectorProduse = new string[this->nrProduse];
			for (int i = 0; i < this->nrProduse; i++)
			{
				this->vectorProduse[i] = c.vectorProduse[i];
			}
			this->pretVectorProduse = new float[nrProduse];
			for (int i = 0; i < this->nrProduse; i++)
			{
				this->pretVectorProduse[i] = c.pretVectorProduse[i];
			}
		}
		else
		{
			this->nrProduse = 0;
			this->vectorProduse = NULL;
			this->pretVectorProduse = NULL;
		}
	}
	~Comanda()
	{
		if (this->pretVectorProduse != NULL)
		{
			delete[]this->pretVectorProduse;
		}
		if (this->vectorProduse != NULL)
		{
			delete[]this->vectorProduse;
		}
		nrComanda--;
	}
	Comanda& operator=(const Comanda& c)
	{
		if (this != &c)
		{
			if (this->pretVectorProduse != NULL)
			{
				delete[]this->pretVectorProduse;
			}
			if (this->vectorProduse != NULL)
			{
				delete[]this->vectorProduse;
			}
			if (c.numeClient.size() > 2)
			{
				this->numeClient = c.numeClient;
			}
			else
			{
				this->numeClient = "Anonim";

			}

			this->oraComanda.ore = c.oraComanda.ore;
			this->oraComanda.minute = c.oraComanda.minute;
			this->oraComanda.secunde = c.oraComanda.secunde;
			if (c.comandaData.zi > 0 && c.comandaData.zi <= 31)
			{
				this->comandaData.zi = c.comandaData.zi;
			}
			else if (c.comandaData.zi <= 0)
			{
				this->comandaData.zi = 1;
			}
			else if (c.comandaData.zi > 31)
			{
				this->comandaData.zi = 31;
			}
			if (c.comandaData.luna > 0 && c.comandaData.luna <= 12)
			{
				this->comandaData.luna = c.comandaData.luna;
			}
			else if (comandaData.luna <= 0)
			{
				this->comandaData.luna = 1;
			}
			else if (comandaData.luna > 12)
			{
				this->comandaData.luna = 12;
			}
			if (c.comandaData.an >= 2000 && c.comandaData.an <= 2020)
			{
				this->comandaData.an = c.comandaData.an;
			}
			else if (c.comandaData.an < 2000)
			{
				this->comandaData.an = 2000;
			}
			else if (c.comandaData.an > 2020)
			{
				this->comandaData.an = 2020;
			}
			if (c.nrProduse > 0 && c.vectorProduse != NULL && c.pretVectorProduse != NULL)
			{
				this->nrProduse = c.nrProduse;
				this->vectorProduse = new string[this->nrProduse];
				for (int i = 0; i < this->nrProduse; i++)
				{
					this->vectorProduse[i] = c.vectorProduse[i];
				}
				this->pretVectorProduse = new float[nrProduse];
				for (int i = 0; i < this->nrProduse; i++)
				{
					this->pretVectorProduse[i] = c.pretVectorProduse[i];
				}
			}
			else
			{
				this->nrProduse = 0;
				this->vectorProduse = NULL;
				this->pretVectorProduse = NULL;
			}
		}
		return *this;
	}
	friend ostream& operator<<(ostream& out, const Comanda& c)
	{
		out << "idComanda: " << c.idComanda << endl;
		out << "NumeClient: " << c.numeClient << endl;
		out << "DataComanda(Zi/Luna/An): " << c.comandaData.zi << "/" << c.comandaData.luna << "/" << c.comandaData.an << endl;
		out << "OraComanda(Ora/Minute/Secunde): " << c.oraComanda.ore << ":" << c.oraComanda.minute << ":" << c.oraComanda.secunde << endl;
		out << "Numar produse: " << c.nrProduse << endl;
		for (int i = 0; i < c.nrProduse; i++)
		{
			out << "Nume Produs | Pret(in lei): " << c.vectorProduse[i] << " | " << c.pretVectorProduse[i] << endl;
		}
		return out;
	}
	friend istream& operator>>(istream& in, Comanda& c)
	{
		delete[]c.vectorProduse;
		delete[] c.pretVectorProduse;
		cout << "NumeClient: ";
		in >> ws;
		getline(in, c.numeClient);
		cout << "Zi comanda: ";
		in >> c.comandaData.zi;
		cout << "Luna comanda: ";
		in >> c.comandaData.luna;
		cout << "An comanda: ";
		in >> c.comandaData.an;
		cout << "OraComanda: ";
		in >> c.oraComanda.ore;
		cout << "Minute: ";
		in >> c.oraComanda.minute;
		cout << "Secunde: ";
		in >> c.oraComanda.secunde;
		cout << "Numar produse: ";
		in >> c.nrProduse;
		c.vectorProduse = new string[c.nrProduse];
		c.pretVectorProduse = new float[c.nrProduse];
		for (int i = 0; i < c.nrProduse; i++)
		{
			cout << " Nume Produs: ";
			in >> ws;
			getline(in, c.vectorProduse[i]);
			cout << " Pret Produs: ";
			in >> c.pretVectorProduse[i];
		}
		return in;
	}
	friend ofstream& operator<<(ofstream& out, const Comanda& c)
	{
		out  << c.numeClient << endl;
		out  << c.comandaData.zi << " " << c.comandaData.luna << " " << c.comandaData.an << endl;
		out  << c.oraComanda.ore << " " << c.oraComanda.minute << " " << c.oraComanda.secunde << endl;
		out  << c.nrProduse << endl;
		for (int i = 0; i < c.nrProduse; i++)
		{
			out << c.vectorProduse[i] << endl;
		}
		for (int i = 0; i < c.nrProduse; i++)
		{
			out << c.pretVectorProduse[i] << endl;
		}
		return out;
	}
	friend ifstream& operator>>(ifstream& in, Comanda& c)
	{
		delete[]c.vectorProduse;
		delete[] c.pretVectorProduse;
		in >> ws;
		getline(in, c.numeClient);
		in >> c.comandaData.zi;
		in >> c.comandaData.luna;
		in >> c.comandaData.an;
		in >> c.oraComanda.ore;
		in >> c.oraComanda.minute;
		in >> c.oraComanda.secunde;
		in >> c.nrProduse;
		c.vectorProduse = new string[c.nrProduse];
		c.pretVectorProduse = new float[c.nrProduse];
		for (int i = 0; i < c.nrProduse; i++)
		{
			in >> ws;
			getline(in, c.vectorProduse[i]);
		
		}
		for (int i = 0; i < c.nrProduse; i++)
		{
			
			in >> c.pretVectorProduse[i];
		}
		return in;
	}
	float pretComandaFaraTVA()
	{
		float suma = 0;
		for (int i = 0; i < nrProduse; i++)
		{
			suma += pretVectorProduse[i];
		}
		suma = suma - (19 * suma) / 100.0;
		return suma;
	}
	float sumaPreturi()
	{
		float suma = 0;
		for (int i = 0; i < nrProduse; i++)
		{
			suma += pretVectorProduse[i];
		}
		return suma;
	}
	explicit operator float()
	{
		float suma = 0;
		for (int i = 0; i < nrProduse; i++)
		{
			suma += pretVectorProduse[i];
		}
		return suma;
	}
	string& operator [](int index)
	{
		if (index >= 0 && index < this->nrProduse)
		{
			return this->vectorProduse[index];
		}
		else throw ExcepetieTratare();
	}
	void adaugaProdus(string numeProdus, float pretProdus)
	{
		Comanda sursa = *this;
		delete[]this->vectorProduse;
		delete[]this->pretVectorProduse;
		this->nrProduse++;
		this->vectorProduse = new string[this->nrProduse];
		this->pretVectorProduse = new float[this->nrProduse];
		for (int i = 0; i < sursa.nrProduse; i++)
		{
			this->vectorProduse[i] = sursa.vectorProduse[i];
		}
		for (int i = 0; i < sursa.nrProduse; i++)
		{
			this->pretVectorProduse[i] = sursa.pretVectorProduse[i];
		}
		this->vectorProduse[this->nrProduse - 1] = numeProdus;
		this->pretVectorProduse[this->nrProduse - 1] = pretProdus;
	}
	Comanda& operator-=( string numeProdus)
	{
		int numarator = 0;
		for (int i = 0; i < this->nrProduse; i++)
		{
			if (vectorProduse[i] == numeProdus)
			{
				numarator++;
			}
		}
		Comanda sursa = *this;
		this->nrProduse = this->nrProduse - numarator;
		int index = 0;
		delete[]this->vectorProduse;
		delete[]this->pretVectorProduse;
		this->vectorProduse = new string[this->nrProduse];
		this->pretVectorProduse = new float[this->nrProduse];
		for (int i = 0; i < sursa.nrProduse; i++)
		{
			if (sursa.vectorProduse[i] != numeProdus)
			{
				this->vectorProduse[index] = sursa.vectorProduse[i];
				this->pretVectorProduse[index] = sursa.pretVectorProduse[i];
				index++;
			}
		}
		return *this;
	}
	Comanda operator +(const Comanda& c)
	{
		Comanda sursa = *this;
		delete[]sursa.vectorProduse;
		delete[]sursa.pretVectorProduse;
		sursa.nrProduse = this->nrProduse + c.nrProduse;
		sursa.vectorProduse = new string[sursa.nrProduse];
		sursa.pretVectorProduse = new float[sursa.nrProduse];
		for (int i = 0; i < this->nrProduse; i++)
		{
			sursa.vectorProduse[i] = this->vectorProduse[i];
		}
		for (int i = 0; i < this->nrProduse; i++)
		{
			sursa.pretVectorProduse[i] = this->pretVectorProduse[i];
		}
		for (int i = this->nrProduse; i < sursa.nrProduse; i++)
		{
			sursa.vectorProduse[i] = c.vectorProduse[i - this->nrProduse];
		}
		for (int i = this->nrProduse; i < sursa.nrProduse; i++)
		{
			sursa.pretVectorProduse[i] = c.pretVectorProduse[i - this->nrProduse];
		}
		return sursa;
	}
	float CalculareComanda()
	{
		float transport = 7.5;
		float suma = 0;
		for (int i = 0; i < nrProduse; i++)
		{
			suma += pretVectorProduse[i];
		}
		if (suma < 50)
		{
			suma += transport;
		}
		return suma;
	}
	bool operator<(Comanda c)
	{
		return this->nrProduse < c.nrProduse;
	}
	bool operator>(Comanda c)
	{
		return (float)*this > (float)c;
	}
};
int Comanda::nrComanda = 1;
class ComandaCuReducere: public Comanda
{
	float discount;
public:
	ComandaCuReducere() :Comanda()
	{
		this->discount = 0;
	}
	ComandaCuReducere(string numeClient, Ora oraComanda, Data comandaData, int nrProduse, string* vectorProduse, float* pretVectorProduse,float discount) :Comanda(numeClient,oraComanda,comandaData,nrProduse,vectorProduse,pretVectorProduse)
	{
		this->discount = discount;
	}
	ComandaCuReducere(const ComandaCuReducere& c) :Comanda(c)
	{
		this->discount = c.discount;

	}
	ComandaCuReducere& operator=(const ComandaCuReducere& c)
	{
		Comanda::operator=(c);
		this->discount = c.discount;
		return *this;
	}
	friend ostream& operator<<(ostream& out, const ComandaCuReducere& c)
	{
		out << (Comanda&)c;
		out << "Discount: "<<c.discount;
		return out;
	}
	friend istream& operator>>(istream& in,  ComandaCuReducere& c)
	{
		in >> (Comanda&)c;
		cout << "Discount: " ;
		in >> c.discount;
		return in;
	}
	friend ofstream& operator<<(ofstream& out, const ComandaCuReducere& c)
	{
		out << (Comanda&)c;
		out << c.discount;
		return out;
	}
	friend ifstream& operator>>(ifstream& in, ComandaCuReducere& c)
	{
		in >> (Comanda&)c;
		in >> c.discount;
		return in;
	}
	float CalculareComanda()
	{
		float transport = 7.5;
		float suma = 0;
		for (int i = 0; i < nrProduse; i++)
		{
			suma += pretVectorProduse[i];
		}
		if (suma < 50)
		{
			suma += transport;
		}
		suma += (discount * suma) / 100;
		return suma;
	}
	float pretComandaFaraTVA()
	{
		float suma = 0;
		for (int i = 0; i < nrProduse; i++)
		{
			suma += pretVectorProduse[i];
		}
		suma = suma - (19 * suma) / 100.0 - (discount * suma) / 100.0;
		return suma;
	}
};
class Restaurant
{
	string numeRestaurant;
	string adresa;
	int nrComenzi;
	Comanda** listaComenzi;
	int nrLivratori;
	Livrare** livratori;
public:
	Restaurant()
	{
		this->numeRestaurant = "Anonim";
		this->adresa = "Necunoscut";
		this->nrComenzi = 0;
		this->listaComenzi = NULL;
		this->nrLivratori = 0;
		this->livratori = NULL;
	}
	Restaurant(string numeRestaurant, string adresa, int nrComenzi, Comanda** listaComenzi, int nrLivratori, Livrare** livratori)
	{
		this->numeRestaurant = numeRestaurant;
		this->adresa = adresa;
		this->nrComenzi = nrComenzi;
		this->listaComenzi = new Comanda*[this->nrComenzi];
		for (int i = 0; i < nrComenzi; i++)
		{
			this->listaComenzi[i] = listaComenzi[i];
		}
		this->nrLivratori = nrLivratori;
		this->livratori = new Livrare*[this->nrLivratori];
		for (int i = 0; i < this->nrLivratori; i++)
		{
			this->livratori[i] = livratori[i];
		}
	}
	~Restaurant()
	{
		delete[]this->listaComenzi;
		delete[]this->livratori;
		
	}
	Restaurant(const Restaurant& r)
	{

		this->numeRestaurant = r.numeRestaurant;
		this->adresa = r.adresa;
		this->nrComenzi = r.nrComenzi;
		this->listaComenzi = new Comanda * [this->nrComenzi];
		for (int i = 0; i < r.nrComenzi; i++)
		{
			this->listaComenzi[i] = r.listaComenzi[i];
		}
		this->nrLivratori = r.nrLivratori;
		this->livratori = new Livrare * [this->nrLivratori];
		for (int i = 0; i < this->nrLivratori; i++)
		{
			this->livratori[i] = r.livratori[i];
		}
	}
	Restaurant& operator=(const Restaurant& r)
	{
		if (this != &r)
		{
			delete[]this->listaComenzi;
			delete[]this->livratori;
			this->numeRestaurant = r.numeRestaurant;
			this->adresa = r.adresa;
			this->nrComenzi = r.nrComenzi;
			this->listaComenzi = new Comanda * [this->nrComenzi];
			for (int i = 0; i < r.nrComenzi; i++)
			{
				this->listaComenzi[i] = r.listaComenzi[i];
			}
			this->nrLivratori = r.nrLivratori;
			this->livratori = new Livrare * [this->nrLivratori];
			for (int i = 0; i < this->nrLivratori; i++)
			{
				this->livratori[i] = r.livratori[i];
			}
		}
		return *this;
	}
	Restaurant& operator+=(Comanda &c)
	{
		Restaurant copie = *this;
		delete[]listaComenzi;
		this->nrComenzi++;
		this->listaComenzi = new Comanda * [this->nrComenzi];
		for (int i = 0; i < copie.nrComenzi; i++)
		{
			this->listaComenzi[i] = copie.listaComenzi[i];
		}
		this->listaComenzi[this->nrComenzi-1] = &c;
		return *this;
	}
	Restaurant& operator -=(Comanda& l)
	{
		int nr = 0;
		Restaurant copie = *this;
		for (int i = 0; i < this->nrComenzi; i++)
		{
			if (this->listaComenzi[i] == &l)
			{
				nr++;
			}
		}
		delete[]this->listaComenzi;
		this->nrComenzi = this->nrComenzi - nr;
		this->listaComenzi = new Comanda * [this->nrComenzi];
		int poz = 0;
		for (int i = 0; i < copie.nrComenzi; i++)
		{
			if (copie.listaComenzi[i] != &l)
			{
				this->listaComenzi[poz] = copie.listaComenzi[i];
				poz++;
			}
		}
		return *this;
	}
	void adaugaLivrator(Livrare& l)
	{
		Restaurant copie = *this;
		delete[]livratori;
		this->nrLivratori++;
		this->livratori = new Livrare * [this->nrLivratori];
		for (int i = 0; i < copie.nrLivratori; i++)
		{
			this->livratori[i] = copie.livratori[i];
		}
		this->livratori[this->nrLivratori - 1] = &l;
	
	}
	void eliminaLivrator(Livrare &l)
	{
		int nr = 0;
		Restaurant copie = *this;
		for (int i = 0; i < this->nrLivratori; i++)
		{
			if (this->livratori[i] == &l)
			{
				nr++;
			}
		}
		delete[]this->listaComenzi;
		this->nrLivratori = this->nrLivratori - nr;
		this->livratori = new Livrare * [this->nrLivratori];
		int poz = 0;
		for (int i = 0; i < copie.nrComenzi; i++)
		{
			if (copie.livratori[i] != &l)
			{
				this->livratori[poz] = copie.livratori[i];
				poz++;
			}
		}
		
	}
	friend ostream& operator<<(ostream& out, const Restaurant& r)
	{
		out << "Nume Restaurant: " << r.numeRestaurant << endl;
		out << "Adresa Restaurant: " << r.adresa << endl;
		

		if (r.nrComenzi == 0)
		{
			cout << "Restaurantul nu are nicio comanda inregistrata!"<<endl;
		}
		else
		{
			out << "Nr Comenzi Restaurant: " << r.nrComenzi << endl;
			out << " Comenzi Restaurant: " << endl << "--------------------" << endl;;
			for (int i = 0; i < r.nrComenzi; i++)
			{
				out << *r.listaComenzi[i] << endl << "--------------------" << endl;
			}
		}
		
		
		if (r.nrLivratori == 0)
		{
			cout << "Restaurantul nu are niciun livrator angajat!" << endl;
		}
		else
		{
			out << "Nr Livratori Restaurant: " << r.nrLivratori << endl;
			out << " Livratori Restaurant: " << endl;
			for (int i = 0; i < r.nrLivratori; i++)
			{
				out << *r.livratori[i] << " ";
			}
		}
		
		return out;
	}
	friend istream& operator>>(istream& in, Restaurant& r)
	{
		delete[]r.listaComenzi;
		delete[]r.livratori;
		cout << "Nume Restaurant: " ;
		in >> ws;
		getline(in, r.numeRestaurant);
		cout << "Adresa Restaurant: " ;
		in >> ws;
		getline(in, r.adresa);
		cout << "Nr Comenzi Restaurant: ";
		in >> r.nrComenzi;
		r.listaComenzi = new Comanda * [r.nrComenzi];
		cout << " Comenzi Restaurant: ";
		for (int i = 0; i < r.nrComenzi; i++)
		{
			Comanda pC;
			in >> pC;
			r.listaComenzi[i] = new Comanda(pC);
		}
		cout << "Nr livratori Restaurant: ";
		in >> r.nrLivratori;
		r.livratori = new Livrare * [r.nrLivratori];
		cout << " Livratori Restaurant: ";
		for (int i = 0; i < r.nrLivratori; i++)
		{
			Livrare pLiv;
			in >> pLiv;
			r.livratori[i] = new Livrare(pLiv);
		}
		return in;
	}
	friend ofstream& operator<<(ofstream& out, const Restaurant& r)
	{
		out  << r.numeRestaurant << endl;
		out << r.adresa << endl;
		out  << r.nrComenzi << endl;
		for (int i = 0; i < r.nrComenzi; i++)
		{
			out << *r.listaComenzi[i] ;
		}
		out  << r.nrLivratori <<endl;
		for (int i = 0; i < r.nrLivratori; i++)
		{
			out << *r.livratori[i];
		}

		return out;
	}
	friend ifstream& operator>>(ifstream& in, Restaurant& r)
	{
		delete[]r.listaComenzi;
		delete[]r.livratori;
		in >> ws;
		getline(in, r.numeRestaurant);
		in >> ws;
		getline(in, r.adresa);
		in >> r.nrComenzi;
		r.listaComenzi = new Comanda * [r.nrComenzi];
		for (int i = 0; i < r.nrComenzi; i++)
		{
			Comanda* pc= new Comanda();
			in >> *pc;
			r.listaComenzi[i]= new Comanda(*pc);
		
		}
		in >> r.nrLivratori;
		r.livratori = new Livrare * [r.nrLivratori];
		for (int i = 0; i < r.nrLivratori; i++)
		{
			Livrare pLiv;
			in >> pLiv;
			r.livratori[i] = new Livrare(pLiv);
		}
		return in;
	}
	int getNrComenzi()
	{
		return this->nrComenzi;
	}
	int getNrLivratori()
	{
		return this->nrLivratori;
	}
	Comanda** getComenzi()
	{
		return this->listaComenzi;
	}
	Livrare** getLivrare()
	{
		return this->livratori;
	}
	Comanda& operator[](int index)
	{
		if (index >= 0 && index < this->nrComenzi)
		{
			return *this->listaComenzi[index];
		}
		else throw ExcepetieTratare();
	}
	string getNumeRestaurant()
	{
		return this->numeRestaurant;
	}
};
template<typename COM>
class istoricComenzi
{
	int numar;
	COM* colectie;
public:
	istoricComenzi()
	{
		this->numar = 0;
		this->colectie = NULL;
	}
	istoricComenzi(int numar, COM* colectie)
	{
		this->numar = numar;
		this->colectie = new COM[this->numar];
		for (int i = 0; i < numar; i++)
		{
			this->colectie[i] = colectie[i];
		}
	}
	istoricComenzi(const istoricComenzi &c)
	{
		this->numar = c.numar;
		this->colectie = new COM[this->numar];
		for (int i = 0; i < c.numar; i++)
		{
			this->colectie[i] = c.colectie[i];
		}
	}
	istoricComenzi& operator =(const istoricComenzi& c)
	{
		if (this != &c)
		{
			delete[]c.colectie;
			this->numar = c.numar;
			this->colectie = new COM[this->numar];
			for (int i = 0; i < c.numar; i++)
			{
				this->colectie[i] = c.colectie[i];
			}
		}
		return *this;
	}
	istoricComenzi& operator+=(COM element)
	{
		istoricComenzi sursa = *this;
		delete[]colectie;
		this->numar++;
		this->colectie = new COM[this->numar];
		for (int i = 0; i < sursa.numar; i++)
		{
			this->colectie[i] = sursa.colectie[i];
		}
		this->colectie[this->numar - 1] = element;
		return *this;
	}
	~istoricComenzi()
	{
		delete[]colectie;
	}
	float valoareTotalaComenzi()
	{
		float val = 0;
		for (int i = 0; i < numar; i++)
		{
			val = val + (float)colectie[i];
		}
		return val;
	}
	friend ostream& operator<<(ostream& out, const istoricComenzi& c)
	{
		out << c.numar << endl;
		for (int i = 0; i < c.numar; i++)
		{
			out << endl << c.colectie[i] << endl;
		}
		return out;
	}
	int getNumar()
	{
		return this->numar;
	}
	COM* getCOM()
	{
		return this->colectie;
	}
};
template<typename clasa>
bool comparareNrProduse(clasa obj1, clasa obj2) {
	return obj1 < obj2;
}


template<typename cls>
bool compValoareCos(cls obj1, cls obj2) {
	return obj1 > obj2;
}
void meniuComenzi()
{
	cout << endl << endl << endl << endl;
	cout << "**************************************************" << endl;
	cout << "*   \t\t        Meniu  \t\t\t *" << endl;
	cout << "* 1.Adauga comanda\t\t\t\t *" << endl;
	cout << "* 2.Vizualizare comanda\t\t\t\t *" << endl;
	cout << "* 3.Eliminare comanda\t\t\t\t *" << endl;
	cout << "* 4.Creare raport text cu toate comenzile\t *" << endl;
	cout << "* 5.Vizualizare raport dupa zi\t\t\t *" << endl;
	cout << "* 6.Vizualizare raport dupa luna\t\t *" << endl;
	cout << "* 7.Vizualizare raport dupa an\t\t\t *" << endl;
	cout << "* 8.Vizualizare raport total\t\t\t *" << endl;
	cout << "* 9.Afisare comenzi crescator dupa produse  \t *" << endl;
	cout << "*10.Afisare comenzi descrescator dupa valoare  \t *" << endl;
	cout << "*11.Iesire meniu\t\t\t\t *" << endl;
	cout << "**************************************************" << endl;

	cout << endl << endl << endl << endl;


}
void main()
{
	
	Livrare l(101, "liviu");
	Livrare l1(102, "Silviu");
	Livrare l2(103, "Andrei");
	/*cout << l << endl;
	cin >> l;
	cout << l << endl;*/
	Data d1;
	d1.an = 2019;
	d1.zi = 23;
	d1.luna = 11;

	Data d2;
	d2.an = 2020;
	d2.zi = 29;
	d2.luna = 10;
	Data d3;
	d3.an = 2019;
	d3.zi = 23;
	d3.luna = 11;
	Ora o1;
	o1.minute = 34;
	o1.ore = 12;
	o1.secunde = 13;
	string vectProd[] = { "Crem brulle","Visine", "iaurt" };
	float pretProd[] = { 65.5,23.4,11.5 };
	Comanda c("Georgel", o1, d1, 3, vectProd, pretProd);
	Comanda c1("Georgel", o1, d2, 2, vectProd, pretProd);
	Comanda c99("Georgel", o1, d3, 1, vectProd, pretProd);

	//Comanda c1;
	//cin >> c1;
	//cout << c1 << endl;
	c.adaugaProdus("Tiramisu", 44.5);

	Comanda c2;
	c2 = c + c1;

	c2 -= "Visine";


	ComandaCuReducere cr1("Georgel", o1, d1, 3, vectProd, pretProd,12);

	ofstream f("comanda.txt", ios::out);
	f << c1;
	f << cr1;
	f.close();
	Comanda com1;
	ComandaCuReducere comr;
	ifstream iesire("comanda.txt", ios::in);
	iesire >> com1;
	iesire >> comr;
	iesire.close();
	Livrare** deliveryBoy = new Livrare * [3];
	deliveryBoy[0] = &l;
	deliveryBoy[1] = &l1;
	deliveryBoy[2] = &l2;
	Comanda** listCom = new Comanda * [3];
	listCom[0] = &c;
	listCom[1] = &c1;
	listCom[2] = &c2;
	Restaurant r1("Unirea", "Str.Unirii", 3, listCom, 3, deliveryBoy);
;

	system("Color F3");
	int meniu;
	do
	{
	
		meniuComenzi();
		cout << "Introduceti Valoarea!: ";
		cin >> meniu;
		if (meniu == 1)
		{
			Comanda* pc = new Comanda();
			cin >> *pc;
			r1 += *pc;
			
		}
		if (meniu == 2)
		{
			
			cout << r1;
		}
		if (meniu == 3)
		{
		
			cout << "In acest moment in restaurant sunt inregistrare " << r1.getNrComenzi()<< " comenzi"<<endl;
			cout << "Acestea sunt: " << endl;
			for (int i = 0; i < r1.getNrComenzi(); i++)
			{
				cout << *r1.getComenzi()[i]<<endl <<endl;
			}
			
			int index1;
			do
			{
				cout << "Introduceti pozitia dorita: ";
				cin >> index1;
				index1--;
				try
				{
					if (r1.getNrComenzi() == 0)
					{
						cout << "Nu avem comenzi inregistrate!" << endl;
					}
					else
					{
						cout << r1[index1];
						cout << r1.getNrComenzi() << endl;
					}
					
				}
				catch (ExcepetieTratare ex)
				{
					cout << "Pozitia introdusa este gresita! Va rugam introduceti alt valoare! " << endl;
				}
			} while (index1 < 0 || index1 >= r1.getNrComenzi()&& r1.getNrComenzi()!=0);
			if (r1.getNrComenzi() > 0)
			{
				r1 -= r1[index1];
			}
			
		}
		if (meniu == 4)
		{
			Restaurant r;
			string numeFisier = r1.getNumeRestaurant();
			numeFisier += ".txt";
			ofstream f(numeFisier ,ios::out);
			f << r1;
			f.close();
			cout << "Raportul text al tuturor comenzilor a fost creat!" << endl;
			ifstream g(numeFisier, ios::in);
			g >> r;
			g.close();
			cout << r;
		}
		if (meniu == 5)
		{
			int* data = new int[3];
			cout << "introduceti Ziua cautata: ";
			cin >> data[0];
			cout << "introduceti luna cautata: ";
			cin >> data[1];
			cout << "introduceti an cautata: ";
			cin >> data[2];
			float totalIncasari = 0;
			istoricComenzi<Comanda> istoric;
			string numeFis = "comanda" + to_string(data[0]) + to_string(data[1]) + to_string(data[2])+".txt";
			ofstream fil(numeFis, ios::out);
			for (int i = 0; i < r1.getNrComenzi(); i++)
			{
				istoric += *r1.getComenzi()[i];
			}
			cout << "-----------------" << endl;
			for (int i = 0; i < istoric.getNumar(); i++)
			{
				
				if (istoric.getCOM()[i].getData().zi == data[0] && istoric.getCOM()[i].getData().luna == data[1] && istoric.getCOM()[i].getData().an == data[2])
				{
					
					fil << istoric.getCOM()[i];
					totalIncasari += (float)istoric.getCOM()[i];
				}
				
			}
			if (totalIncasari > 0)
			{
				cout << "Valoare totala a comenzilor din " << data[0] << "/" << data[1] << "/" << data[2] << " este: " << totalIncasari << " de lei!" << endl;
				
			}
			else
			{
				cout << "Din pacate in acea zi nu s-au inregistrat comenzi!" << endl;
			}
			fil << "Valoare totala a comenzilor: " << totalIncasari << " de lei!";
			fil.close();
		}
		if (meniu == 6)
		{
			int* data = new int[2];
		
			cout << "introduceti luna cautata: ";
			cin >> data[0];
			cout << "introduceti an cautata: ";
			cin >> data[1];
			float totalIncasari = 0;
			istoricComenzi<Comanda> istoric;
			string numeFis = "comanda" + to_string(data[0]) + to_string(data[1])  + ".txt";
			ofstream fil(numeFis, ios::out);
			for (int i = 0; i < r1.getNrComenzi(); i++)
			{
				istoric += *r1.getComenzi()[i];
			}
			cout << "-----------------" << endl;
			for (int i = 0; i < istoric.getNumar(); i++)
			{

				if ( istoric.getCOM()[i].getData().luna == data[0] && istoric.getCOM()[i].getData().an == data[1])
				{

					fil << istoric.getCOM()[i];
					totalIncasari += (float)istoric.getCOM()[i];
				}

			}
			if (totalIncasari > 0)
			{
				cout << "Valoare totala a comenzilor din " << data[0] << "/" << data[1] << "/"  << " este: " << totalIncasari << " de lei!" << endl;

			}
			else
			{
				cout << "Din pacate  nu s-au inregistrat comenzi!" << endl;
			}
			fil << "Valoare totala a comenzilor: " << totalIncasari << " de lei!";
			fil.close();
		}
		if(meniu==7)
		{
			int data;
		
			cout << "introduceti an cautata: ";
			cin >> data;
			float totalIncasari = 0;
			istoricComenzi<Comanda> istoric;
			string numeFis = "comanda" + to_string(data) + ".txt";
			ofstream fil(numeFis, ios::out);
			for (int i = 0; i < r1.getNrComenzi(); i++)
			{
				istoric += *r1.getComenzi()[i];
			}
			cout << "-----------------" << endl;
			for (int i = 0; i < istoric.getNumar(); i++)
			{

				if (istoric.getCOM()[i].getData().an == data)
				{

					fil << istoric.getCOM()[i];
					totalIncasari += (float)istoric.getCOM()[i];
				}

			}
			if (totalIncasari > 0)
			{
				cout << "Valoare totala a comenzilor din " << data <<" este: " << totalIncasari << " de lei!" << endl;

			}
			else
			{
				cout << "Din pacate nu s-au inregistrat comenzi!" << endl;
			}
			fil << "Valoare totala a comenzilor: " << totalIncasari << " de lei!";
			fil.close();
		}
		if (meniu == 8)
		{
			int data;

			
			float totalIncasari = 0;
			istoricComenzi<Comanda> istoric;
			string numeFis = "totalIncasari";
			numeFis += ".txt";
			ofstream fil(numeFis, ios::out);
			for (int i = 0; i < r1.getNrComenzi(); i++)
			{
				istoric += *r1.getComenzi()[i];
			}
			cout << "-----------------" << endl;
			for (int i = 0; i < istoric.getNumar(); i++)
			{

					fil << istoric.getCOM()[i];
					totalIncasari += (float)istoric.getCOM()[i];
			

			}
			if (totalIncasari > 0)
			{
				cout << "Valoare totala a tuturor comenzilor este: " << totalIncasari << " de lei!" << endl;

			}
			else
			{
				cout << "Din pacate nu s-au inregistrat comenzi!" << endl;
			}
			fil << "Valoare totala a comenzilor: " << totalIncasari << " de lei!";
			fil.close();
		}
		if (meniu == 9)
		{
			vector<Comanda> vectComand;
			for (int i = 0; i < r1.getNrComenzi(); i++)
			{
				vectComand.push_back(*r1.getComenzi()[i]);
			}
			vector<Comanda>::iterator it;
			sort(vectComand.begin(), vectComand.end(), comparareNrProduse<Comanda>);

			for (it = vectComand.begin(); it != vectComand.end(); it++)
			{
				cout << *it << endl;
			}
		}
		if (meniu == 10)
		{
			vector<Comanda> vectComand;
			for (int i = 0; i < r1.getNrComenzi(); i++)
			{
				vectComand.push_back(*r1.getComenzi()[i]);
			}
			vector<Comanda>::iterator it;
			sort(vectComand.begin(), vectComand.end(), compValoareCos<Comanda>);

			for (it = vectComand.begin(); it != vectComand.end(); it++)
			{
				cout << *it;
				cout << "Valoare cos: "<< (float)*it << endl;
			}
		}

	} while (meniu > 0 && meniu <=10);
	cout << "Utilizatorul a fost deconectat! Va uram o zi frumoasa!" << endl;
	int valoare;

	
}
