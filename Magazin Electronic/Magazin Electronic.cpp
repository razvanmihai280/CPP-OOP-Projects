#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<algorithm>
#include <ctime>// sa luam data de azi

using namespace std;
string strUp(string& str)
{
	for (unsigned int i = 0; str[i] != 0; i++)
		str[i] = toupper(str[i]);
	return str;
}
class ExceptieMsj :public exception
{
public:
	string mesaj;
	ExceptieMsj(string mesaj)
	{
		this->mesaj = mesaj;
	}
};
class FisiereBinare
{
public:
	virtual void serializare(string numeFile) = 0;
	virtual void deserializare(string numeFile) = 0;
};
class Interfata
{
public:
	virtual string tipAdmin() = 0;
	virtual void MeniuAplicatie() = 0;
};
class Produs :FisiereBinare
{
protected:
	const int idProdus;
	static int contor;
	char* numeProdus;
	float pretProdus;
public:
	Produs() :idProdus(contor++)
	{
		this->numeProdus = new char[strlen("Necunoscut") + 1];
		strcpy(this->numeProdus, "Necunoscut");
		this->pretProdus = 0;
	}
	char* getNumeProdus()
	{
		return this->numeProdus;
	}
	const int getIdProdus()
	{
		return this->idProdus;
	}
	float getPretProdus()
	{
		return this->pretProdus;
	}
	void setNumeProdus(const char* numeProdus)
	{
		if (strlen(numeProdus) >= 3)
		{
			this->numeProdus = new char[strlen(numeProdus) + 1];
			strcpy(this->numeProdus, numeProdus);
		}
		else throw ExceptieMsj("Numele introdus este incorect!");
	}
	void setPretProdus(float pretProdus)
	{
		if (pretProdus > 0)
		{
			this->pretProdus = pretProdus;
		}
		else throw ExceptieMsj("Pretul introdus este incorect!");
	}

	Produs(const char* numeProdus, float pretProdus) :idProdus(contor++)
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
		if (pretProdus > 0)
		{
			this->pretProdus = pretProdus;
		}
		else
		{
			this->pretProdus = 0;
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
		if (p.pretProdus > 0)
		{
			this->pretProdus = p.pretProdus;
		}
		else
		{
			this->pretProdus = 0;
		}
	}
	virtual ~Produs()
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
			if (p.pretProdus > 0)
			{
				this->pretProdus = p.pretProdus;
			}
			else
			{
				this->pretProdus = 0;
			}
		}
		return *this;
	}
	friend ostream& operator<<(ostream& out, const Produs& p)
	{
		string spatiu = "\t\t\t";
		out << p.idProdus << spatiu << p.numeProdus << spatiu << p.pretProdus << spatiu;
		return out;
	}
	friend ofstream& operator<<(ofstream& out, const Produs& p)
	{
		out << p.numeProdus << endl << p.pretProdus << endl;
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
		in >> ws;
		in >> p.pretProdus;
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
		in >> p.pretProdus;
		return in;
	}
	Produs& operator++()
	{
		this->pretProdus++;
		return *this;
	}
	Produs operator++(int)
	{
		Produs copie = *this;
		this->pretProdus++;
		return copie;
	}
	bool operator<(const Produs& p)
	{
		return this->pretProdus < p.pretProdus;
	}

	Produs& operator+=(float valoare)
	{
		this->pretProdus += valoare;
		return *this;
	}
	void serializare(string numeFile)
	{
		ofstream f(numeFile, ios::out, ios::binary);

		int lungimeNumeProdus = strlen(this->numeProdus);
		f.write((char*)&lungimeNumeProdus, sizeof(int));
		f.write(this->numeProdus, lungimeNumeProdus + 1);
		f.write((char*)&this->pretProdus, sizeof(float));
		f.close();
	}
	void deserializare(string numeFile)
	{
		ifstream f(numeFile, ios::in, ios::binary);

		int lungimeNumeProdus = 0;
		f.read((char*)&lungimeNumeProdus, sizeof(int));
		delete[] this->numeProdus;
		this->numeProdus = new char[lungimeNumeProdus + 1];
		f.read(this->numeProdus, lungimeNumeProdus + 1);
		f.read((char*)&this->pretProdus, sizeof(float));
		f.close();
	}
	virtual float valoareColet()
	{
		float pretColet = 0;
		if (this->pretProdus < 150)
		{
			pretColet = pretProdus + 25;
		}
		else
		{
			pretColet = pretProdus;
		}
		return pretColet;
	}
};
template<typename Clasa>
bool compararePreturiProduse(Clasa a, Clasa b)
{
	return a < b;
}
int Produs::contor = 1;
class ProdusResigilat :public Produs
{
	string defect;
	float discount;
public:
	ProdusResigilat() :Produs()
	{
		this->defect = "Necunoscut";
		this->discount = 0;
	}
	ProdusResigilat(const char* numeProdus, float pretProdus, string defect, float discount) :Produs(numeProdus, pretProdus)
	{
		if (defect.size() > 3)
		{
			this->defect = defect;
		}
		else
		{
			string eroare = "Defect inexistent";
			throw eroare;
		}
		if (discount >= 0 && discount <= 100)
		{
			this->discount = discount;
		}
		else if (discount < 0)
		{
			float eroare = -1.6;
			throw eroare;
		}
		else if (discount > 100)
		{
			throw new exception("Valoare discountului a depasit 100!");
		}
	}
	ProdusResigilat(const ProdusResigilat& p) :Produs(p)
	{
		if (p.defect.size() > 3)
		{
			this->defect = p.defect;
		}
		else
		{
			string eroare = "Defect inexistent";
			throw eroare;
		}
		if (p.discount >= 0 && p.discount <= 100)
		{
			this->discount = p.discount;
		}
		else if (discount < 0)
		{
			float eroare = -1.6;
			throw eroare;
		}
		else if (discount > 100)
		{
			throw new exception("Valoare discountului a depasit 100!");
		}
	}
	ProdusResigilat(const Produs& p) :Produs(p)
	{
		this->defect = "Nu are";
		this->discount = 0;
	}
	~ProdusResigilat()
	{

	}

	ProdusResigilat& operator=(const ProdusResigilat& p)
	{
		if (this != &p)
		{
			Produs::operator =(p);
			if (p.defect.size() > 3)
			{
				this->defect = p.defect;
			}
			else
			{
				string eroare = "Defect inexistent";
				throw eroare;
			}
			if (p.discount >= 0 && p.discount <= 100)
			{
				this->discount = p.discount;
			}
			else if (discount < 0)
			{
				float eroare = -1.6;
				throw eroare;
			}
			else if (discount > 100)
			{
				throw new exception("Valoare discountului a depasit 100!");
			}
		}
		return *this;
	}
	float getDiscount()
	{
		return this->discount;
	}
	string getDefect()
	{
		return this->defect;
	}
	void setDiscount(float discount)
	{
		this->discount = discount;
	}
	void setDefect(string defect)
	{
		if (defect.size() > 3)
		{
			this->defect = defect;
		}
	}
	bool operator>(const ProdusResigilat& p)
	{
		if (discount >= 0 && discount <= 100)
		{
			this->discount = discount;
		}
	}
	void serializare(string numeFile)
	{
		ofstream f(numeFile, ios::out, ios::binary);

		int lungimeNumeProdus = strlen(this->numeProdus);
		f.write((char*)&lungimeNumeProdus, sizeof(int));
		f.write(this->numeProdus, lungimeNumeProdus + 1);
		f.write((char*)&this->pretProdus, sizeof(float));
		int lungimDefect = defect.size();
		f.write((char*)&lungimDefect, sizeof(int));
		f.write(this->defect.c_str(), lungimDefect + 1);
		f.write((char*)&this->discount, sizeof(float));
		f.close();
	}
	void deserializare(string numeFile)
	{
		ifstream f(numeFile, ios::in, ios::binary);

		int lungimeNumeProdus = 0;
		f.read((char*)&lungimeNumeProdus, sizeof(int));
		delete[] this->numeProdus;
		this->numeProdus = new char[lungimeNumeProdus + 1];
		f.read(this->numeProdus, lungimeNumeProdus + 1);
		f.read((char*)&this->pretProdus, sizeof(float));

		int lungimDefect = 0;
		f.read((char*)&lungimDefect, sizeof(int));
		char* aux = new char[lungimDefect + 1];
		f.read(aux, lungimDefect + 1);
		this->defect = aux;
		delete aux;
		f.read((char*)&this->discount, sizeof(float));
		f.close();
	}
	friend ostream& operator<<(ostream& out, const ProdusResigilat& p)
	{
		out << (Produs&)p;
		string spatiu = "\t\t\t";
		out << p.defect << spatiu << p.discount << endl;
		return out;
	}

	friend istream& operator>>(istream& in, ProdusResigilat& p)
	{
		in >> (Produs&)p;
		cout << "Introduceti defectul Produsului: ";
		in >> ws;
		getline(in, p.defect);
		cout << "Introduceti discountul Produsului: ";
		in >> p.discount;
		return in;
	}
	friend ofstream& operator<<(ofstream& out, const ProdusResigilat& p)
	{
		out << (Produs&)p;

		out << p.defect << endl << p.discount << endl;
		return out;
	}

	friend ifstream& operator>>(ifstream& in, ProdusResigilat& p)
	{
		in >> (Produs&)p;
		in >> ws;
		getline(in, p.defect);
		in >> p.discount;
		return in;
	}
	float valoareColet()
	{
		float pretColet = 0;
		if (this->pretProdus < 150)
		{
			pretColet = pretProdus + 25 - discount * pretProdus / 100;//cei 25 reprezinta transportul
		}
		else
		{
			pretColet = pretProdus - discount * pretProdus / 100;//cei 25 reprezinta transportul

		}
		return pretColet;
	}
};
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
	ProdusPromotional(const char* numeProdus, float pretProdus, string promotie, float discount) :Produs(numeProdus, pretProdus)
	{
		if (promotie.size() > 3)
		{
			this->promotie = promotie;
		}
		else
		{
			string eroare = "promotia inexistent";
			throw eroare;
		}
		if (discount >= 0 && discount <= 100)
		{
			this->discount = discount;
		}
		else if (discount < 0)
		{
			float eroare = -1.6;
			throw eroare;
		}
		else if (discount > 100)
		{
			throw new exception("Valoare discountului a depasit 100!");
		}
	}
	ProdusPromotional(const ProdusPromotional& p) :Produs(p)
	{
		if (p.promotie.size() > 3)
		{
			this->promotie = p.promotie;
		}
		else
		{
			string eroare = "promotia inexistent";
			throw eroare;
		}
		if (p.discount >= 0 && p.discount <= 100)
		{
			this->discount = p.discount;
		}
		else if (discount < 0)
		{
			float eroare = -1.6;
			throw eroare;
		}
		else if (discount > 100)
		{
			throw new exception("Valoare discountului a depasit 100!");
		}
	}
	ProdusPromotional(const Produs& p) :Produs(p)
	{
		this->promotie = "Nu are";
		this->discount = 0;
	}
	~ProdusPromotional()
	{

	}

	ProdusPromotional& operator=(const ProdusPromotional& p)
	{
		if (this != &p)
		{
			Produs::operator =(p);
			if (p.promotie.size() > 3)
			{
				this->promotie = p.promotie;
			}
			else
			{
				string eroare = "promotie inexistenta";
				throw eroare;
			}
			if (p.discount >= 0 && p.discount <= 100)
			{
				this->discount = p.discount;
			}
			else if (discount < 0)
			{
				float eroare = -1.6;
				throw eroare;
			}
			else if (discount > 100)
			{
				throw new exception("Valoare discountului a depasit 100!");
			}
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
	void serializare(string numeFile)
	{
		ofstream f(numeFile, ios::out, ios::binary);

		int lungimeNumeProdus = strlen(this->numeProdus);
		f.write((char*)&lungimeNumeProdus, sizeof(int));
		f.write(this->numeProdus, lungimeNumeProdus + 1);
		f.write((char*)&this->pretProdus, sizeof(float));
		int lungimpromotie = promotie.size();
		f.write((char*)&lungimpromotie, sizeof(int));
		f.write(this->promotie.c_str(), lungimpromotie + 1);
		f.write((char*)&this->discount, sizeof(float));
		f.close();
	}
	void deserializare(string numeFile)
	{
		ifstream f(numeFile, ios::in, ios::binary);

		int lungimeNumeProdus = 0;
		f.read((char*)&lungimeNumeProdus, sizeof(int));
		delete[] this->numeProdus;
		this->numeProdus = new char[lungimeNumeProdus + 1];
		f.read(this->numeProdus, lungimeNumeProdus + 1);
		f.read((char*)&this->pretProdus, sizeof(float));

		int lungimpromotie = 0;
		f.read((char*)&lungimpromotie, sizeof(int));
		char* aux = new char[lungimpromotie + 1];
		f.read(aux, lungimpromotie + 1);
		this->promotie = aux;
		delete aux;
		f.read((char*)&this->discount, sizeof(float));
		f.close();
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
	float valoareColet()
	{
		float pretColet = 0;
		if (this->pretProdus < 150)
		{
			pretColet = pretProdus + 25 - discount * pretProdus / 100;//cei 25 reprezinta transportul
		}
		else
		{
			pretColet = pretProdus - discount * pretProdus / 100;//cei 25 reprezinta transportul

		}
		return pretColet;
	}
};
class CosElectronic
{
	int nrProduse;
	Produs** produse;
public:
	CosElectronic()
	{
		this->nrProduse = 0;
		this->produse = nullptr;
	}
	CosElectronic(int nrProduse, Produs** produse)
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
	~CosElectronic()
	{
		if (this->produse != nullptr)
		{
			delete[]this->produse;
		}
	}
	CosElectronic(const CosElectronic& c)
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
	}
	CosElectronic& operator=(const CosElectronic& c)
	{
		if (this != &c)
		{
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
	friend ostream& operator<<(ostream& out,  CosElectronic c)
	{
		out << "NUMAR PRODUSE COS: " << c.nrProduse << endl << endl;
		string spatiu = "\t\t\t";
		out << "ID PRODUS:" << "\t\t\t" << "NUME PRODUS: " << "\t\t\t" << "PRET PRODUS" << endl;
		out << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
		for (int i = 0; i < c.nrProduse; i++)
		{
			out << *c.produse[i] << endl << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
		}
		return out;
	}
	friend ofstream& operator<<(ofstream& file,  const CosElectronic& c)
	{
		file << c.nrProduse << endl << endl;
		for (int i = 0; i < c.nrProduse; i++)
		{
			file << *c.produse[i] << endl;
		}
		return file;
	}

	friend istream& operator>>(istream& in, CosElectronic& c)
	{
		delete[]c.produse;
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
	friend ifstream& operator>>(ifstream& in, CosElectronic& c)
	{
		delete[]c.produse;
		in >> c.nrProduse;
		c.produse = new Produs * [c.nrProduse];
		for (int i = 0; i < c.nrProduse; i++)
		{
			c.produse[i] = new Produs();
			in >> *c.produse[i];
		}
		return in;
	}
	CosElectronic& operator+=(Produs& p)
	{
		CosElectronic copie = *this;
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
	CosElectronic& operator -=(Produs& p)
	{
		int nr = 0;
		CosElectronic copie = *this;
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
	void serializare(string numeFisier)
	{
		ofstream file(numeFisier, ios::out | ios::binary);
		//scrierea in binar pentru string

		file.write((char*)&this->nrProduse, sizeof(int));
		//scrierea in binar pentru numerice*
		for (int i = 0; i < this->nrProduse; i++)
		{
			file.write((char*)&*this->produse[i], sizeof(*produse[i]));
		}
	}
	void deserializare(string numeFisier)
	{
		ifstream file(numeFisier, ios::in | ios::binary);
		if (this->produse != nullptr)
		{
			delete[] this->produse;
		}

		//citire in binar pentru numerice(int,float,double,bool)
		file.read((char*)&this->nrProduse, sizeof(int));
		this->produse = new Produs * [this->nrProduse];
		//citire in binar pentru numerice*
		for (int i = 0; i < this->nrProduse; i++)
		{
			this->produse[i] = new Produs();
			file.read((char*)&*this->produse[i], sizeof(*produse[i]));
		}

	}
	Produs& operator[](int index)
	{
		if (index >= 0 && index < this->nrProduse)
		{
			return *this->produse[index];
		}
		else throw ExceptieMsj("Nu exista produs pe pozitia respectiva");
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
			suma += this->produse[i]->getPretProdus();
		}
		return suma;
	}
};

class Comanda
{
	const int idComanda;
	static int contor;
	int data[3];
	CosElectronic* cosElectronic;
public:
	bool operator >(Comanda& c)
	{
		return (float)*this->cosElectronic > (float)*c.cosElectronic;
	}
	
	const int getIdComanda()
	{
		return this->idComanda;
	}
	Comanda() :idComanda(contor++)
	{
		this->data[0] = 1;
		this->data[1] = 1;
		this->data[2] = 2020;
		this->cosElectronic = new CosElectronic();
	}
	Comanda(int data[3], CosElectronic* c) :idComanda(contor++)
	{
		this->data[0] = data[0];
		this->data[1] = data[1];
		this->data[2] = data[2];
		this->cosElectronic = new CosElectronic(*c);
	}
	Comanda(const Comanda& c) :idComanda(c.idComanda)
	{
		this->data[0] = c.data[0];
		this->data[1] = c.data[1];
		this->data[2] = c.data[2];
		this->cosElectronic = new CosElectronic(*c.cosElectronic);
	}
	Comanda& operator=(const Comanda& c)
	{
		if (this != &c)
		{

			delete cosElectronic;
			this->data[0] = c.data[0];
			this->data[1] = c.data[1];
			this->data[2] = c.data[2];
			this->cosElectronic = new CosElectronic(*c.cosElectronic);
		}
		return *this;
	}
	CosElectronic getCos()
	{
		return *this->cosElectronic;
	}
	int* getData()
	{
		return this->data;
	}
	void setCosElectronic(CosElectronic* c)
	{
		delete cosElectronic;
		this->cosElectronic = new CosElectronic(*c);
	}
	void setData(int data[3])
	{
		this->data[0] = data[0];
		this->data[1] = data[1];
		this->data[2] = data[2];
	}
	~Comanda()
	{
		delete cosElectronic;
	}
	friend ostream& operator<<(ostream& out, const Comanda& c)
	{
		out << "Id-ul comenzii este: " << c.idComanda << endl;
		out << "Data comenzii: " << c.data[0] << "/" << c.data[1] << "/" << c.data[2] << endl;
		out << "Cosul comenzii contine: " << endl << *c.cosElectronic << endl;
		return out;
	}
	friend ofstream& operator<<(ofstream& out, const Comanda& c)
	{

		out << c.data[0] << " " << c.data[1] << " " << c.data[2] << endl;
		out << *c.cosElectronic << endl;
		return out;
	}
	friend istream& operator >>(istream& in, Comanda& c)
	{
		delete c.cosElectronic;
		cout << "Introduceti ziua/luna/anul(pe rand, dupa fiecare apasati enter): ";
		in >> c.data[0];
		in >> c.data[1];
		in >> c.data[2];
		c.cosElectronic = new CosElectronic();
		in >> *c.cosElectronic;
		return in;
	}
	friend ifstream& operator >>(ifstream& in, Comanda& c)
	{
		delete c.cosElectronic;
		in >> c.data[0];
		in >> c.data[1];
		in >> c.data[2];
		CosElectronic aux;
		in >> aux;
		c.cosElectronic = new CosElectronic(aux);
		return in;
	}
	
	Comanda& operator+=(Produs& p)
	{
		*this->cosElectronic += p;
		return *this;
	}
	Comanda& operator-=(Produs& p)
	{
		*this->cosElectronic -= p;
		return *this;
	}
	explicit operator float()
	{
		return (float)*this->cosElectronic;
	}
	bool operator !=(Comanda& c)
	{
		if (this->data[2] == c.data[1])
		{
			if (this->data[1] == c.data[1])
			{
				return this->data[0] < this->data[1];
			}
			else
			{
				return this->data[1] < c.data[1];
			}
		}
		else
		{
			return this->data[2] < c.data[2];
		}


	}
	friend bool comparareDataCmd(Comanda& c1, Comanda& c)
	{
		if (c1.data[2] < c.data[2])
		{
			return true;
		}
		else if( c1.data[2]>c.data[1])
		{
			return false;
		}
		else if (c1.data[2] == c.data[2])
		{
		if (c1.data[1] < c.data[1])
			return true;
		else if (c1.data[1] == c.data[1])
		{
			if (c1.data[0] <= c.data[0])
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
		}
	}
};
int Comanda::contor = 1;
template<class Clasa>
bool comparareComandaData(Clasa a, Clasa b)
{
	return a != b;
}
template<typename Clasa>
bool comparareValoareComanda(Clasa a, Clasa b)
{
	return a > b;
}
class Client :public Interfata
{

	char* nume;
	string adresa;
	int nrComenzi;
	Comanda** listCom;
public:
	explicit operator float()
	{
		float valTotal = 0;
		for (int i = 0; i < this->nrComenzi; i++)
		{
			valTotal = (float)*listCom[i];
		}
		return valTotal;
	}
	void adaugaComanda(Comanda& p)
	{
		Client copie = *this;
		delete[]listCom;
		this->nrComenzi++;
		this->listCom = new Comanda * [this->nrComenzi];
		for (int i = 0; i < copie.nrComenzi; i++)
		{
			this->listCom[i] = copie.listCom[i];
		}
		this->listCom[this->nrComenzi - 1] = new Comanda(p);

	}
	void EliminaComanda(Comanda& p)
	{
		int nr = 0;
		Client copie = *this;
		for (int i = 0; i < this->nrComenzi; i++)
		{
			if (this->listCom[i] == &p)
			{
				nr++;
			}
		}
		delete[]this->listCom;
		this->nrComenzi = this->nrComenzi - nr;
		this->listCom = new Comanda * [this->nrComenzi];
		int poz = 0;
		for (int i = 0; i < copie.nrComenzi; i++)
		{
			if (copie.listCom[i] != &p)
			{
				this->listCom[poz] = copie.listCom[i];
				poz++;
			}
		}

	}
	Client()
	{
		this->nume = new char[strlen("Anonim") + 1];
		strcpy(this->nume, "Anonim");
		this->adresa = "Necunoscuta";
		this->nrComenzi = 0;
		this->listCom = nullptr;
	}
	Client(const char* nume, string adresa, int nrComenzi, Comanda** listCom)
	{
		this->nume = new char[strlen(nume) + 1];
		strcpy(this->nume, nume);
		this->adresa = adresa;
		this->nrComenzi = nrComenzi;
		this->listCom = new Comanda * [this->nrComenzi];
		for (int i = 0; i < this->nrComenzi; i++)
		{
			this->listCom[i] = listCom[i];
		}
	}
	Client(const Client& c)
	{
		this->nume = new char[strlen(c.nume) + 1];
		strcpy(this->nume, c.nume);
		this->adresa = c.adresa;
		this->nrComenzi = c.nrComenzi;
		this->listCom = new Comanda * [this->nrComenzi];
		for (int i = 0; i < this->nrComenzi; i++)
		{
			this->listCom[i] = c.listCom[i];
		}
	}
	Client& operator=(const Client& c)
	{
		if (this != &c)
		{
			delete[]this->listCom;
			delete[]this->nume;
			this->nume = new char[strlen(c.nume) + 1];
			strcpy(this->nume, c.nume);
			this->adresa = c.adresa;
			this->nrComenzi = c.nrComenzi;
			this->listCom = new Comanda * [this->nrComenzi];
			for (int i = 0; i < this->nrComenzi; i++)
			{
				this->listCom[i] = c.listCom[i];
			}
		}
		return *this;
	}
	void setNume(const char* nume)
	{
		delete[]this->nume;
		this->nume = new char[strlen(nume) + 1];
		strcpy(this->nume, nume);
	}
	void setAdresa(string adresa)
	{
		this->adresa = adresa;

	}
	void setComanda(int nrComenzi, Comanda** listCom)
	{
		if (this->listCom != nullptr)
			delete[]this->listCom;
		this->nrComenzi = nrComenzi;
		this->listCom = new Comanda * [this->nrComenzi];
		for (int i = 0; i < this->nrComenzi; i++)
		{
			this->listCom[i] = listCom[i];
		}
	}
	char* getNume()
	{
		return this->nume;
	}
	string getAdresa()
	{
		return this->adresa;
	}
	int getNrComenzi()
	{
		return this->nrComenzi;
	}
	Comanda** getComanda()
	{
		return this->listCom;
	}
	~Client()
	{
		delete[]this->listCom;
		delete[]this->nume;
	}
	friend ostream& operator<<(ostream& out, const Client& c)
	{
		out << "Numele clientului: " << c.nume << endl;
		out << "Adresa clientului: " << c.adresa << endl;
		out << "Numarul de comenzi efectuate: " << c.nrComenzi << endl;
		out << "Comenzile efectuate: " << endl;
		for (int i = 0; i < c.nrComenzi; i++)
		{
			out << *c.listCom[i] << endl << endl;
		}
		return out;
	}
	friend istream& operator>>(istream& in, Client& c)
	{
		delete[]c.nume;
		delete[]c.listCom;
		cout << "Numele clientului: ";
		char aux[100];
		in >> ws;
		in.getline(aux, 99);
		c.nume = new char[strlen(aux) + 1];
		strcpy(c.nume, aux);
		cout << "Adresa clientului: ";
		in >> ws;
		getline(in, c.adresa);
		cout << "Numarul de comenzi efectuate: ";
		in >> c.nrComenzi;
		cout << "Comenzi efectuate: " << endl;
		c.listCom = new Comanda * [c.nrComenzi];
		for (int i = 0; i < c.nrComenzi; i++)
		{
			Comanda comAux;
			in >> comAux;
			c.listCom[i] = new Comanda(comAux);
		}
		return in;
	}
	friend ifstream& operator>>(ifstream& in, Client& c)
	{
		delete[]c.nume;
		delete[]c.listCom;
		char aux[100];
		in >> ws;
		in.getline(aux, 99);
		c.nume = new char[strlen(aux) + 1];
		strcpy(c.nume, aux);
		in >> ws;
		getline(in, c.adresa);
		in >> c.nrComenzi;
		c.listCom = new Comanda * [c.nrComenzi];
		for (int i = 0; i < c.nrComenzi; i++)
		{
			Comanda comAux;
			in >> comAux;
			c.listCom[i] = new Comanda(comAux);
		}
		return in;
	}
	friend ofstream& operator<<(ofstream& out, const Client& c)
	{
		out << c.nume << endl;
		out << c.adresa << endl;
		out << c.nrComenzi << endl;
		for (int i = 0; i < c.nrComenzi; i++)
		{
			out << *c.listCom[i] << endl;
		}
		return out;
	}
	string tipAdmin()
	{
		return "client";
	}
	void MeniuAplicatie()
	{
		cout << "\t Bine ati venit in zona destinata clientilor!" << endl;
		cout << "Utilizati cifra corespunzatoare pentru a accesa optiunea dorita!" << endl;
		cout << "1.Afisare Produse din Magazin" << endl;
		cout << "2.Afisarea Produselor din Cos" << endl;
		cout << "3.Adauga Produselor din Cos" << endl;
		cout << "4.Eliminarea Produselor din Cos(DUPA ID)" << endl;
		cout << "5.Finalizare comanda" << endl;
	}
};
//class Magazin :public Interfata
//{
//	char* numeMagazin;
//	string locatie;
//	int nrProduse;
//	Produs** produse;
//	int nrComenzi;
//	Comanda** comenzi;
//public:
//	
//};
class Magazin :public Interfata
{
	static string numeMagazin ;
	int nrProduse;
	Produs** produse;
	int nrComenzi;
	Comanda** comenzi;
public:
	Magazin()
	{
		this->nrProduse = 0;
		this->produse = nullptr;
		this->nrComenzi = 0;
		this->comenzi = nullptr;
	}
	Magazin(int nrProduse, Produs** produse, int nrComenzi, Comanda** comenzi)
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
		if (nrComenzi > 0 && comenzi != nullptr)
		{
			this->nrComenzi = nrComenzi;
			this->comenzi = new Comanda * [this->nrComenzi];
			for (int i = 0; i < nrComenzi; i++)
			{
				this->comenzi[i] = comenzi[i];
			}
		}
		else
		{
			this->nrComenzi = 0;
			this->comenzi = nullptr;
		}
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
	void setcomenzi(int nrComenzi, Comanda** comenzi)
	{
		if (nrComenzi > 0 && comenzi != nullptr)
		{
			this->nrComenzi = nrComenzi;
			this->comenzi = new Comanda * [this->nrComenzi];
			for (int i = 0; i < nrComenzi; i++)
			{
				this->comenzi[i] = comenzi[i];
			}
		}
	}
	~Magazin()
	{
		if (this->produse != nullptr)
		{
			delete[]this->produse;
		}
		if (this->comenzi != nullptr)
		{
			delete[]this->comenzi;
		}
	}
	Magazin(const Magazin& c)
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
		if (c.nrComenzi > 0 && c.comenzi != nullptr)
		{
			this->nrComenzi = c.nrComenzi;
			this->comenzi = new Comanda * [this->nrComenzi];
			for (int i = 0; i < c.nrComenzi; i++)
			{
				this->comenzi[i] = c.comenzi[i];
			}
		}
		else
		{
			this->nrComenzi = 0;
			this->comenzi = nullptr;
		}
	}
	Magazin& operator=(const Magazin& c)
	{
		if (this != &c)
		{
			if (this->produse != nullptr)
			{
				delete[]this->produse;
			}
			if (this->comenzi != nullptr)
			{
				delete[]this->comenzi;
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
			if (c.nrComenzi > 0 && c.comenzi != nullptr)
			{
				this->nrComenzi = c.nrComenzi;
				this->comenzi = new Comanda * [this->nrComenzi];
				for (int i = 0; i < c.nrComenzi; i++)
				{
					this->comenzi[i] = c.comenzi[i];
				}
			}
			else
			{
				this->nrComenzi = 0;
				this->comenzi = nullptr;
			}
		}
		return *this;
	}
	friend ostream& operator<<(ostream& out, Magazin c)
	{
		out << "NUMAR PRODUSE in Magazin: " << c.nrProduse << endl << endl;
		string spatiu = "\t\t\t";
		out << "ID PRODUS:" << "\t\t\t" << "NUME PRODUS: " << "\t\t\t" << "PRET PRODUS" << endl;
		out << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
		for (int i = 0; i < c.nrProduse; i++)
		{
			out << *c.produse[i] << endl << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
		}
		out << endl << endl << endl << "COMENZI" << endl << endl << endl;
		out << "NUMAR comenzi : " << c.nrComenzi << endl << endl;

		out << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
		for (int i = 0; i < c.nrComenzi; i++)
		{
			out << *c.comenzi[i] << endl << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
		}
		return out;
	}
	friend ofstream& operator<<(ofstream& file, const Magazin& c)
	{
		file << c.nrProduse << endl << endl;
		for (int i = 0; i < c.nrProduse; i++)
		{
			file << *c.produse[i] << endl;
		}

		file << c.nrComenzi << endl << endl;
		for (int i = 0; i < c.nrComenzi; i++)
		{
			file << *c.comenzi[i] << endl;

		
		}
		return file;
	}
	friend istream& operator>>(istream & in,  Magazin & c)
	{
			delete[]c.produse;
			delete[]c.comenzi;
			cout << "Introduceti numarul de produse: ";
			in >> c.nrProduse;
			c.produse = new Produs * [c.nrProduse];
			cout << "Introduceti produsele: " << endl;
			for (int i = 0; i < c.nrProduse; i++)
			{
				c.produse[i] = new Produs();
				in >> *c.produse[i];
			}
			cout << "Introduceti numarul de comenzi: ";
			in >> c.nrComenzi;
			c.comenzi = new Comanda * [c.nrComenzi];
			cout << "Introduceti comenzile: " << endl;
			for (int i = 0; i < c.nrComenzi; i++)
			{
				c.comenzi[i] = new Comanda();
				in >> *c.comenzi[i];
			}
			return in;
	}
	friend ifstream& operator>>(ifstream & in, Magazin & c)
	{
			delete[]c.produse;
			in >> c.nrProduse;
			c.produse = new Produs * [c.nrProduse];
			for (int i = 0; i < c.nrProduse; i++)
			{
				c.produse[i] = new Produs();
				in >> *c.produse[i];
			}
			delete[]c.comenzi;
			in >> c.nrComenzi;
			c.comenzi = new Comanda * [c.nrComenzi];
			for (int i = 0; i < c.nrComenzi; i++)
			{
				c.comenzi[i] = new Comanda();
				in >> *c.comenzi[i];
			}
			return in;
	}
	Magazin& operator+=(Produs& p)
	{
			Magazin copie = *this;
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
	Magazin& operator -=(Produs & p)
	{
			int nr = 0;
			Magazin copie = *this;
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
	void adaugaComanda(Comanda & p)
		{
			Magazin copie = *this;
			delete[]comenzi;
			this->nrComenzi++;
			this->comenzi = new Comanda * [this->nrComenzi];
			for (int i = 0; i < copie.nrComenzi; i++)
			{
				this->comenzi[i] = copie.comenzi[i];
			}
			this->comenzi[this->nrComenzi - 1] = new Comanda(p);

	}
	void EliminaComanda(Comanda & p)
	{
			int nr = 0;
			Magazin copie = *this;
			for (int i = 0; i < this->nrComenzi; i++)
			{
				if (this->comenzi[i] == &p)
				{
					nr++;
				}
			}
			delete[]this->comenzi;
			this->nrComenzi = this->nrComenzi - nr;
			this->comenzi = new Comanda * [this->nrComenzi];
			int poz = 0;
			for (int i = 0; i < copie.nrComenzi; i++)
			{
				if (copie.comenzi[i] != &p)
				{
					this->comenzi[poz] = copie.comenzi[i];
					poz++;
				}
			}
		
	}
	void serializare(string numeFisier)
	{
			ofstream file(numeFisier, ios::out | ios::binary);
			//scrierea in binar pentru string

			file.write((char*)&this->nrProduse, sizeof(int));
			//scrierea in binar pentru numerice*
			for (int i = 0; i < this->nrProduse; i++)
			{
				file.write((char*)&*this->produse[i], sizeof(*produse[i]));
			}
			file.write((char*)&this->nrComenzi, sizeof(int));
			//scrierea in binar pentru numerice*
			for (int i = 0; i < this->nrComenzi; i++)
			{
				file.write((char*)&*this->comenzi[i], sizeof(*comenzi[i]));
			}
	}
	void deserializare(string numeFisier)
	{
			ifstream file(numeFisier, ios::in | ios::binary);
			if (this->produse != nullptr)
			{
				delete[] this->produse;
			}

			//citire in binar pentru numerice(int,float,double,bool)
			file.read((char*)&this->nrProduse, sizeof(int));
			this->produse = new Produs * [this->nrProduse];
			//citire in binar pentru numerice*
			for (int i = 0; i < this->nrProduse; i++)
			{
				this->produse[i] = new Produs();
				file.read((char*)&*this->produse[i], sizeof(*produse[i]));
			}
			if (this->comenzi != nullptr)
			{
				delete[] this->comenzi;
			}

			//citire in binar pentru numerice(int,float,double,bool)
			file.read((char*)&this->nrComenzi, sizeof(int));
			this->comenzi = new Comanda * [this->nrComenzi];
			//citire in binar pentru numerice*
			for (int i = 0; i < this->nrComenzi; i++)
			{
				this->comenzi[i] = new Comanda();
				file.read((char*)&*this->comenzi[i], sizeof(*comenzi[i]));
			}
	}
	Produs& operator[](int index)
	{
			if (index >= 0 && index < this->nrProduse)
			{
				return *this->produse[index];
			}
			else throw ExceptieMsj("Nu exista produs pe pozitia respectiva");
	}
	Comanda& operator()(int index)
	{
			if (index >= 0 && index < this->nrComenzi)
			{
				return *this->comenzi[index];
			}
			else throw ExceptieMsj("Nu exista Comanda pe pozitia respectiva");
	}
	Produs** getProdus()
	{
			return this->produse;
		}
		int getNrProduse()
		{
			return this->nrProduse;
		}
		Comanda** getComanda()
		{
			return this->comenzi;
		}
		int getnrComenzi()
		{
			return this->nrComenzi;
	}
	static string getNume()
	{
		return numeMagazin;
	}
	string tipAdmin()
	{
		return "magazin";
	}
	void MeniuAplicatie()
	{
		cout << "\t Bine ati venit in zona destinata administratorului de magazin!" << endl;
		cout << "Utilizati cifra corespunzatoare pentru a accesa optiunea dorita!" << endl;
		cout << "1.Afisare Produse" << endl;
		cout << "2.Adauga Produse" << endl;
		cout << "3.Elimina Produse(Dupa ID)" << endl;
		cout << "4.Cauta produs dupa nume " << endl;
		cout << "5.Cauta produs dupa id " << endl;
		cout << "6.Afisare Comenzi" << endl;
		cout << "7.Adauga Comenzi" << endl;
		cout << "8.Modifica Comanda" << endl;
		cout << "9.Cauta comanda dupa produs" << endl;
		cout << "10.Cauta comanda dupa data" << endl;
		cout << "11.Elimina Comanda(Dupa ID)" << endl;
		cout << "12.Creare raport comenzi dupa zi" << endl;
		cout << "13.Creare raport comenzi dupa luna" << endl;
		cout << "14.Creare raport comenzi dupa an" << endl;
		cout << "15.Creare raport comenzi totale" << endl;
		cout << "16.Modifica Produs" << endl;
		cout << "17.Afisare Produse crescator dupa Pret"<<endl;
		cout << "18.Afisati Comenzile descrescator dupa valoare" << endl;
		cout << " 19. Afisati Comenzile dupa data" << endl;
		cout << "20.Iesire din meniu" << endl;


	}
	void setComanda(int index, Comanda& c)
	{
		
		this->comenzi[index] = new Comanda(c);
	}
	void setProdus(int index, Produs& p)
	{
		
		this->produse[index] =new Produs(p);
	}
};
string Magazin::numeMagazin = "Altex";
template<typename COM>
class istoric
{
	int numar;
	COM* colectie;
public:
	istoric()
	{
		this->numar = 0;
		this->colectie = NULL;
	}
	istoric(int numar, COM* colectie)
	{
		this->numar = numar;
		this->colectie = new COM[this->numar];
		for (int i = 0; i < numar; i++)
		{
			this->colectie[i] = colectie[i];
		}
	}
	istoric(const istoric& c)
	{
		this->numar = c.numar;
		this->colectie = new COM[this->numar];
		for (int i = 0; i < c.numar; i++)
		{
			this->colectie[i] = c.colectie[i];
		}
	}
	istoric& operator =(const istoric& c)
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
	istoric& operator+=(COM element)
	{
		istoric sursa = *this;
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
	~istoric()
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
	friend ostream& operator<<(ostream& out, const istoric& c)
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

void main()
{
	/* int choice;
	 cout << "Pentru accesarea meniului se vor folosi numerele de la 1 la 3 in functie de cerinta: " << endl;
	 cout << "1.Client " << endl;
	 cout << "2.Administrator de magazin" << endl;
	 cout << "3.Iesire" << endl;
	 cin >> choice;

	 switch (choice) {
	 case 1:
		 cout << "CLIENT" << endl;
		 break;
	 case 2:
		 cout << "ADMIN" << endl;
		 break;
	 case 3:
		 cout << "Va uram o zi buna! Va mai asteptam!" << endl;
		 break;
		 cin.get();
	 }*/
	cout << endl << endl << endl << endl << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||TESTAT PRODUS ||||||||||||||||||||||||||||||||||||||||||||||||||||||||| " << endl << endl;
	cout << endl << "----------------------------------------GETTERI---------------------------------------- " << endl;
	Produs p;
	Produs p1("Televizor SAMSUNG HD", 5000);
	cout << p1.getIdProdus() << endl;
	cout << p1.getNumeProdus() << endl;
	cout << p1.getPretProdus() << endl;
	cout << endl << "----------------------------------------SETTERI---------------------------------------- " << endl;

	try {
		p.setNumeProdus("Ta");
	}
	catch (ExceptieMsj ex)
	{
		cout << ex.mesaj << endl;
	}

	try {
		p.setPretProdus(-800);
	}
	catch (ExceptieMsj ex)
	{
		cout << ex.mesaj << endl;
	}
	cout << p.getIdProdus() << endl;
	cout << p.getNumeProdus() << endl;
	cout << p.getPretProdus() << endl;
	cout << endl << "----------------------------------------Constructor Copiere ---------------------------------------- " << endl;
	Produs p2 = p1;
	cout << p2.getIdProdus() << endl;
	cout << p2.getNumeProdus() << endl;
	cout << p2.getPretProdus() << endl;
	cout << endl << "----------------------------------------Operator=  ---------------------------------------- " << endl;
	p = p1;
	cout << p.getIdProdus() << endl;
	cout << p.getNumeProdus() << endl;
	cout << p.getPretProdus() << endl;
	p.setNumeProdus("Monitor BENQ ZOWIE");
	p.setPretProdus(600);
	cout << endl << "----------------------------------------Operator+=  ---------------------------------------- " << endl;
	p += 700;
	cout << endl;
	cout << p.getIdProdus() << endl;
	cout << p.getNumeProdus() << endl;
	cout << p.getPretProdus() << endl;
	cout << endl << "----------------------------------------Operator++(pre si post incrementat)  ---------------------------------------- " << endl;
	p++;
	++p;
	cout << p << endl;
	cout << endl << "----------------------------------------Operator>  ---------------------------------------- " << endl;
	if (p < p1)
	{
		cout << "Pretul produsului " << p.getNumeProdus() << " nu este mai mare decat pretul produsului " << p1.getNumeProdus() << endl;
	}
	else
	{
		cout << "Pretul produsului " << p.getNumeProdus() << "  este mai mare decat pretul produsului " << p1.getNumeProdus() << endl;

	}
	cout << endl << "----------------------------------------Operator<<  ---------------------------------------- " << endl;
	cout << p << endl;
	cout << endl << "----------------------------------------Operator>> (E COMENTAT) ---------------------------------------- " << endl;
	/*Produs pDeCitit;
	cin >> pDeCitit;
	cout << pDeCitit<<endl;*/
	cout << endl << "----------------------------------------  Fisiere text ---------------------------------------- " << endl;
	Produs p5;
	ofstream f("produse.txt", ios::out);
	f << p1 << endl;
	f.close();
	ifstream g("produse.txt", ios::in);
	g >> p5;
	g.close();
	cout << p5 << endl;
	cout << endl << "----------------------------------------  Fisiere binare ---------------------------------------- " << endl;
	Produs pBinar;
	p5.serializare("prodBinare.bin");
	pBinar.deserializare("prodBinare.bin");
	cout << pBinar << endl;
	cout << endl << endl << endl << endl << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||TESTAT PRODUS RESIGILAT |||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl << endl;
	ProdusResigilat pr;
	ProdusResigilat pr1("Televizor SAMSUNG HD", 5000, "Colt ciobit", 25);
	try
	{
		ProdusResigilat pr2("Televizor SAMSUNG HD", 5000, "Co", 25);
	}
	catch (string mesajEroare)
	{
		cout << mesajEroare << endl;
	}
	catch (float codEroareFloat)
	{
		cout << codEroareFloat << endl;
	}
	catch (int codEroare)
	{
		cout << "Codul erorii provocate de  valoare gresita este: " << codEroare << endl;
	}

	catch (exception* ex)
	{
		cout << ex->what() << endl;
	}
	catch (...)
	{
		cout << "E din alta parte problema!" << endl;
	}
	try
	{
		ProdusResigilat pr3("Televizor SAMSUNG HD", 5000, "Colt Spart", 125);
	}
	catch (string mesajEroare)
	{
		cout << mesajEroare << endl;
	}
	catch (float codEroareFloat)
	{
		cout << codEroareFloat << endl;
	}
	catch (int codEroare)
	{
		cout << "Codul erorii provocate de  valoare gresita  este: " << codEroare << endl;
	}

	catch (exception* ex)
	{
		cout << ex->what() << endl;
	}
	catch (...)
	{
		cout << "E din alta parte problema!" << endl;
	}
	cout << endl << "----------------------------------------GETTERI---------------------------------------- " << endl;
	cout << pr1.getDefect() << endl;
	cout << pr1.getDiscount() << endl;
	cout << endl << "----------------------------------------SETTERI---------------------------------------- " << endl;
	pr.setDefect("Spart usor pe spate");
	pr.setDiscount(35);
	cout << pr.getDefect() << endl;
	cout << pr.getDiscount() << endl;
	cout << endl << "----------------------------------------Constructor Copiere ---------------------------------------- " << endl;
	ProdusResigilat pr5 = pr1;
	cout << pr5 << endl;
	cout << endl << "----------------------------------------Operator = ---------------------------------------- " << endl;
	pr = pr1;
	cout << pr;
	cout << endl << "----------------------------------------Operator<< ---------------------------------------- " << endl;
	cout << pr1 << endl;
	cout << endl << "----------------------------------------Operator >> ---------------------------------------- " << endl;
	//ProdusResigilat prCitit;
	//cin >> prCitit;
	//cout << prCitit;
	cout << endl << "----------------------------------------DOWN-CASTING (UP-CASTING SE FACE IMPLICIT) ---------------------------------------- " << endl;
	ProdusResigilat prDown = p1;
	cout << prDown;
	cout << endl << "----------------------------------------LATE-BINDING(VIRTUALIZARE) ---------------------------------------- " << endl;
	cout << "Valoare colet: " << p1.valoareColet() << endl;
	cout << "Valoare colet: " << pr1.valoareColet() << endl;
	cout << endl << "VIRTUALIZARE" << endl;
	Produs* ppointer;
	ProdusResigilat* ppr = new ProdusResigilat(pr1);
	ppointer = ppr;
	cout << "Valoare colet: " << ppointer->valoareColet() << endl;
	cout << "Valoare colet: " << ppr->valoareColet() << endl;

	cout << endl << "----------------------------------------  Fisiere text ---------------------------------------- " << endl;
	ProdusResigilat pr15;
	ofstream fr("produseResigilate.txt", ios::out);
	fr << pr1 << endl;
	fr.close();
	ifstream gr("produseResigilate.txt", ios::in);
	gr >> pr15;
	gr.close();
	cout << pr15 << endl;
	cout << endl << "----------------------------------------  Fisiere binare ---------------------------------------- " << endl;
	ProdusResigilat prBin;
	pr15.serializare("prodResigilateBinare.bin");
	prBin.deserializare("prodResigilateBinare.bin");
	cout << prBin;

	cout << endl << endl << endl << endl << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||TESTAT PRODUS PROMOTIONAL |||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl << endl;
	ProdusPromotional pp;
	ProdusPromotional pp1("Televizor SAMSUNG HD", 5000, "CyberMonday", 12);
	try
	{
		ProdusPromotional pp2("Televizor SAMSUNG HD", 5000, "Black Friday", 13);
	}
	catch (string mesajEroare)
	{
		cout << mesajEroare << endl;
	}
	catch (float codEroareFloat)
	{
		cout << codEroareFloat << endl;
	}
	catch (int codEroare)
	{
		cout << "Codul erorii provocate de  valoare gresita este: " << codEroare << endl;
	}

	catch (exception* ex)
	{
		cout << ex->what() << endl;
	}
	catch (...)
	{
		cout << "E din alta parte problema!" << endl;
	}
	try
	{
		ProdusPromotional pp3("Televizor SAMSUNG HD", 5000, "New Year's Sale", 125);
	}
	catch (string mesajEroare)
	{
		cout << mesajEroare << endl;
	}
	catch (float codEroareFloat)
	{
		cout << codEroareFloat << endl;
	}
	catch (int codEroare)
	{
		cout << "Codul erorii provocate de  valoare gresita este: " << codEroare << endl;
	}

	catch (exception* ex)
	{
		cout << ex->what() << endl;
	}
	catch (...)
	{
		cout << "E din alta parte problema!" << endl;
	}
	cout << endl << "----------------------------------------GETTERI---------------------------------------- " << endl;
	cout << pp1.getpromotie() << endl;
	cout << pp1.getDiscount() << endl;
	cout << endl << "----------------------------------------SETTERI---------------------------------------- " << endl;
	pp.setpromotie("Christmas Sales");
	pp.setDiscount(23);
	cout << pp.getpromotie() << endl;
	cout << pp.getDiscount() << endl;
	cout << endl << "----------------------------------------Constructor Copiere ---------------------------------------- " << endl;
	ProdusPromotional pp5 = pp1;
	cout << pp5 << endl;
	cout << endl << "----------------------------------------Operator = ---------------------------------------- " << endl;
	pp = pp1;
	cout << pp;
	cout << endl << "----------------------------------------Operator<< ---------------------------------------- " << endl;
	cout << pp << endl;
	cout << endl << "----------------------------------------Operator >> ---------------------------------------- " << endl;
	//ProdusPromotional ppCitit;
	//cin >> ppCitit;
	//cout << ppCitit;
	cout << endl << "----------------------------------------DOWN-CASTING (UP-CASTING SE FACE IMPLICIT) ---------------------------------------- " << endl;
	ProdusPromotional ppDown = p1;
	cout << ppDown;
	cout << endl << "----------------------------------------LATE-BINDING(VIRTUALIZARE) ---------------------------------------- " << endl;
	cout << "Valoare colet: " << p1.valoareColet() << endl;
	cout << "Valoare colet: " << pp1.valoareColet() << endl;
	cout << endl << "VIRTUALIZARE" << endl;
	Produs* prodPointer;
	ProdusPromotional* prodpromo = new ProdusPromotional(pp1);
	prodPointer = prodpromo;
	cout << "Valoare colet: " << prodpromo->valoareColet() << endl;
	cout << "Valoare colet: " << prodPointer->valoareColet() << endl;

	cout << endl << "----------------------------------------  Fisiere text ---------------------------------------- " << endl;
	ProdusPromotional pp15;
	ofstream fp("produsePromotionale.txt", ios::out);
	fp << pp1 << endl;
	fr.close();
	ifstream gp("produsePromotionale.txt", ios::in);
	gp >> pp15;
	gp.close();
	cout << pp15 << endl;
	cout << endl << "----------------------------------------  Fisiere binare ---------------------------------------- " << endl;
	ProdusPromotional ppBin;
	pp15.serializare("produsePromotionaleBinare.bin");
	ppBin.deserializare("produsePromotionaleBinare.bin");
	cout << ppBin;
	cout << endl << endl << endl << endl << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||TESTAT COS ELECTRONIC |||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl << endl;
	Produs pCevaNou("Laptop HP Pavilion 2x", 3500);
	Produs** vectPro = new Produs * [3];
	vectPro[0] = &p;
	vectPro[1] = &pCevaNou;
	vectPro[2] = &p2;
	CosElectronic c;
	CosElectronic c1(3, vectPro);
	cout << c1 << endl;
	cout << endl << "----------------------------------------Constructor de copiere ---------------------------------------- " << endl;

	Produs pNou = p2;
	cout << endl << endl << endl << endl << endl;
	cout << endl << "----------------------------------------Operator = ---------------------------------------- " << endl;
	c = c1;
	cout << c;
	cout << endl << "----------------------------------------Operator += ---------------------------------------- " << endl;
	c1 += pNou;
	cout << c1 << endl;
	cout << endl << endl << endl << endl << endl;
	cout << endl << "----------------------------------------Operator -= ---------------------------------------- " << endl;

	c1 -= p2;
	c1 -= pNou;
	cout << c1 << endl;
	cout << endl << "----------------------------------------  Fisiere text ---------------------------------------- " << endl;
	CosElectronic c5;
	ofstream fc("cosElectronic.txt", ios::out);
	fc << c1 << endl;
	fc.close();
	ifstream gc("cosElectronic.txt", ios::in);
	gc >> c5;
	gc.close();
	cout << c5 << endl;
	cout << endl << "----------------------------------------  Fisiere binare ---------------------------------------- " << endl;
	CosElectronic cBinar;
	c1.serializare("cosElectronicBinar.bin");
	cBinar.deserializare("cosElectronicBinar.bin");
	cout << cBinar;
	cout << endl << endl << endl << endl << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||TESTAT COMANDA |||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl << endl;
	int data[3] = { 22,11,2020 };
	int data1[3] = { 12,10,2020 };
	Comanda com(data, &cBinar);
	Comanda com5(data1, &cBinar);
	Comanda com67(data1, &cBinar);
	Comanda com77(data1, &cBinar);

	cout << com << endl;
	cout << endl << "----------------------------------------Cosntructor de copiere ---------------------------------------- " << endl;
	Comanda com0 = com;
	cout << com0 << endl;
	cout << endl << "----------------------------------------Operator = ---------------------------------------- " << endl;
	Comanda com2;
	com2 = com;
	cout << com2;
	cout << endl << "----------------------------------------Operator += ---------------------------------------- " << endl;
	com += pNou;
	cout << com << endl;
	cout << endl << "----------------------------------------Operator -= ---------------------------------------- " << endl;
	com -= pNou;
	cout << com << endl;
	cout << endl << "----------------------------------------Operator << ---------------------------------------- " << endl;
	cout << com << endl;
	cout << endl << "----------------------------------------Operator >> ---------------------------------------- " << endl;
	/*Comanda comCitita;
	cin >> comCitita;
	cout << comCitita<<endl;*/
	ofstream fComanda("comandaTest.txt", ios::out);
	fComanda << com << endl;
	fComanda.close();
	Comanda coDeCitit;
	ifstream gComanda("comandaTest.txt", ios::in);
	gComanda >> coDeCitit;
	gComanda.close();
	cout << coDeCitit << endl;
	cout << "MARR" << endl;
	cout << endl << endl << endl << endl << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||TESTAT Client |||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl << endl;
	Comanda** listC = new Comanda * [2];
	listC[0] = &com;
	listC[1] = &com5;
	Comanda** listCNoua = new Comanda * [2];
	listCNoua[0] = &com67;
	listCNoua[1] = &com77;
	Produs pAdunat("Laptop Lenovo Yoga 5200", 5400);
	Client client1("Ionel Tudor", "Strada Nucului nr15", 2, listC);

	*client1.getComanda()[1] += pAdunat;
	*client1.getComanda()[0] -= *client1.getComanda()[0]->getCos().getProdus()[0];
	cout << client1 << endl;
	cout << endl << "----------------------------------------  Fisiere text ---------------------------------------- " << endl;
	string numeFClienti = "comenzi_";
	numeFClienti = numeFClienti + client1.getNume() + ".csv";
	ofstream fClienti(numeFClienti, ios::out);
	fClienti << client1;
	fClienti.close();
	Client incercareCitire;
	ifstream gClienti(numeFClienti, ios::in);
	gClienti >> incercareCitire;
	cout << endl << "----------------------------------------  Fisiere CITIT ---------------------------------------- " << endl;
	cout << incercareCitire;
	cout << endl << endl << endl << endl << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||TESTAT Magazin |||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl << endl;
	Magazin m1(3, vectPro, 2, listC);
	cout << m1 << endl;
	string numeFisierMagazin = m1.getNume() + ".txt";
	ofstream fMagazin(numeFisierMagazin, ios::out);
	fMagazin << m1 << endl;
	fMagazin.close();
	Magazin mTestFisText;
	cout << endl << endl << endl << endl << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||Getteri|||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl << endl;
	cout << "Numar produse: " << m1.getNrProduse() << endl;
	for (int i = 0; i < m1.getNrProduse(); i++)
	{
		cout << *m1.getProdus()[i] << endl;
	}
	cout << endl << endl;
	cout << "Numar comenzi: " << m1.getnrComenzi() << endl;
	for (int i = 0; i < m1.getnrComenzi(); i++)
	{
		cout << *m1.getComanda()[i] << endl;
	}
	cout << endl << endl << endl << endl << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||Setteri|||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl << endl;
	Produs pMag("Iphone 11 128 GB", 3500);
	Produs p1Mag("Iphone 12 128 GB", 5500);
	Produs p2Mag("Iphone  X 128 GB", 2500);
	Produs** listProdMag = new Produs * [3];
	listProdMag[0] = &pMag;
	listProdMag[1] = &p1Mag;
	listProdMag[2] = &p2Mag;
	m1.setProduse(3, listProdMag);
	for (int i = 0; i < m1.getNrProduse(); i++)
	{
		cout << *m1.getProdus()[i] << endl;
	}
	m1.setcomenzi(2, listCNoua);
	cout << endl << endl;
	cout << "Numar comenzi: " << m1.getnrComenzi() << endl;
	for (int i = 0; i < m1.getnrComenzi(); i++)
	{
		cout << *m1.getComanda()[i] << endl;
	}
	cout << endl << endl;
	cout << endl << endl << endl << endl << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||Operator>> |||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl << endl;
	//Magazin mTestDeCitit;
	//cin >> mTestDeCitit;
	//cout << mTestDeCitit << endl;
	cout << endl << endl << endl << endl << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||Fisiere Text |||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl << endl;
	ifstream gMagazin(numeFisierMagazin, ios::in);
	gMagazin >> mTestFisText;
	gMagazin.close();
	cout << mTestFisText << endl;
	cout << endl << endl << endl << endl << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||Fisiere Binare |||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl << endl;
	m1.serializare("magazinBinar.bin");
	Magazin mTestFisierBinar;
	mTestFisierBinar.deserializare("magazinBinar.bin");
	cout << mTestFisierBinar << endl;


	cout << endl << endl << endl << endl << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||TESTAT TEMPLATE |||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl << endl;
	istoric<Comanda> istoricCom;
	for (int i = 0; i < m1.getnrComenzi(); i++)
	{
		istoricCom += *m1.getComanda()[i];
	}
	for (int i = 0; i < istoricCom.getNumar(); i++)
	{
		cout << istoricCom.getCOM()[i] << endl;
	}
	cout << endl << endl << endl << endl << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||TESTAT STL |||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl << endl;
	vector<Produs> vectorProduse;
	for (int i = 0; i < m1.getNrProduse(); i++)
	{
		vectorProduse.push_back(*m1.getProdus()[i]);
	}
	for (int i = 0; i < vectorProduse.size(); i++)
	{
		cout << vectorProduse[i] << endl;
	}
	cout << endl << endl << endl << endl << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||TESTAT STL SORTAT DESCRRESCATOR DUPA VALOARE |||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl << endl;

	sort(vectorProduse.begin(), vectorProduse.end(), compararePreturiProduse<Produs>);
	for (int i = 0; i < vectorProduse.size(); i++)
	{
		cout << vectorProduse[i] << endl;
	}
	/*cout << endl << "----------------------------------------Constructor Copiere ---------------------------------------- " << endl;
	cout << endl << "----------------------------------------Operator = ---------------------------------------- " << endl;
	cout << endl << "----------------------------------------Operator<< ---------------------------------------- " << endl;
	cout << endl << "----------------------------------------Operator >> ---------------------------------------- " << endl;
	cout << endl << "----------------------------------------  Fisiere text ---------------------------------------- " << endl;
	cout << endl << "----------------------------------------  Fisiere binare ---------------------------------------- " << endl;*/
	/*cout << "Produsele din magazin: " << endl;
	Produs pMerge("Play Station 5 1TB ", 6000);
	m1 += pMerge;
	for (int i = 0; i < m1.getNrProduse(); i++)
	{
		cout << *m1.getProdus()[i] << endl;
	}
	cout << "Comenzile din Magazin sunt: " << endl;
	int dataCom[] = { 5,1,2021 };
	Produs** prodPtCos = new Produs * [1];
	prodPtCos[0] = &pMerge;
	CosElectronic cPtMagazin(1, prodPtCos);
	Comanda comNouaBuna(dataCom, &cPtMagazin);
	m1.adaugaComanda(comNouaBuna);
	for (int i = 0; i < m1.getnrComenzi(); i++)
	{
		cout << *m1.getComanda()[i] << endl;
	}*/
	cout << endl << endl << endl << endl << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||| MENIU |||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl << endl;
	//cout << "\t\t\tBine ati venit in Magazinul " << m1.getNume() << endl;
	//cout << "Introduceti de la tastatura 'client' daca doriti sa accesati din postura de client." << endl;
	//cout << "Introduceti de la tastatura 'magazin' daca doriti sa accesati din postura de administrator de magazin." << endl;

	string optiuneAccesMeniu;
	Produs prodPtMagazinTest("Iphone XS 128GB", 3000);
	Produs prodPtMagazinTest1("MONITOR AOC GAMING", 2500);
	Produs prodPtMagazinTest2("EPILATOR LASER PHILLIPS", 2500);
	Produs prodPtMagazinTest3("PERIUTA ORAL-B MOTION", 1100);
	Produs prodPtMagazinTest4("TELEVIZOR SAMSUNG 4K SMART UHD", 5100);
	Produs prodPtMagazinTest5("TELEVIZOR LG SMART", 1600);
	Produs** listaProdusePtMeniu = new Produs * [6];
	listaProdusePtMeniu[0] = &prodPtMagazinTest;
	listaProdusePtMeniu[1] = &prodPtMagazinTest1;
	listaProdusePtMeniu[2] = &prodPtMagazinTest2;
	listaProdusePtMeniu[3] = &prodPtMagazinTest3;
	listaProdusePtMeniu[4] = &prodPtMagazinTest4;
	listaProdusePtMeniu[5] = &prodPtMagazinTest5;
	CosElectronic cCosPtMeniu(3, listProdMag);
	CosElectronic cCosPtClient(3, listProdMag);
	CosElectronic cCosPtMeniu1(5, listaProdusePtMeniu);
	CosElectronic cCosPtMeniu2(2, listaProdusePtMeniu);
	int dataTestCom[] = { 22,11,2019 };
	int dataTestCom1[] = { 12,11,2020 };
	int dataTestCom2[] = { 22,12,2020 };
	int dataTestCom3[] = { 22,11,2019 };
	int dataTestCom4[] = { 22,12,2019 };
	int dataTestCom5[] = { 25,12,2019 };
	Comanda comandaPtMeniuTesta(dataTestCom, &cCosPtMeniu);
	Comanda comandaPtMeniuTesta1(dataTestCom1, &cCosPtMeniu);
	Comanda comandaPtMeniuTesta2(dataTestCom2, &cCosPtMeniu1);
	Comanda comandaPtMeniuTesta3(dataTestCom3, &cCosPtMeniu1);
	Comanda comandaPtMeniuTesta4(dataTestCom4, &cCosPtMeniu2);
	Comanda comandaPtMeniuTesta5(dataTestCom5, &cCosPtMeniu2);
	Comanda** listComandaPtMeniu = new Comanda * [6];
	listComandaPtMeniu[0] = &comandaPtMeniuTesta;
	listComandaPtMeniu[1] = &comandaPtMeniuTesta1;
	listComandaPtMeniu[2] = &comandaPtMeniuTesta2;
	listComandaPtMeniu[3] = &comandaPtMeniuTesta3;
	listComandaPtMeniu[4] = &comandaPtMeniuTesta4;
	listComandaPtMeniu[5] = &comandaPtMeniuTesta5;
	Client cMenu;
	Magazin mMenu(6,listaProdusePtMeniu,6,listComandaPtMeniu);
	do
	{
		cout << "\t\t\tBine ati venit in Magazinul " << m1.getNume() << endl;
		cout << "Introduceti de la tastatura 'client' daca doriti sa accesati din postura de client." << endl;
		cout << "Introduceti de la tastatura 'magazin' daca doriti sa accesati din postura de administrator de magazin." << endl;
		cout << "Tip acces: ";
		cin >> optiuneAccesMeniu;
		cout << optiuneAccesMeniu << endl;
		int optiune;
		if (optiuneAccesMeniu == mMenu.tipAdmin())
		{
			do
			{
				
				cout << " Sunteti logat ca  administrator de magazin!" << endl;
				mMenu.MeniuAplicatie();
				cout << "Introduceti optiune: ";

				cin >> optiune;
				system("cls");
				if (optiune == 1)
				{
					system("cls");
					if (mMenu.getNrProduse() == 0)
					{
						cout << "Nu sunt produse disponibile in magazin!" << endl;
					}
					else
					{
						for (int i = 0; i < mMenu.getNrProduse(); i++)
						{
							cout << *mMenu.getProdus()[i] << endl;
						}
					}
					cout << endl << endl;
					cout << "Doriti sa efectuati alta operatiune?\n1.Da\n2.Nu: ";
					int altaOperatiune;
					cin >> altaOperatiune;
					if (altaOperatiune == 1)
					{
						system("cls");
					}
					else
					{
						break;
					}
				}
				if (optiune == 2)
				{
					Produs prodMagAdaugat;
					cin >> prodMagAdaugat;
					mMenu += prodMagAdaugat;
					cout << "Produsul a fost adaugat cu succes!" << endl << endl;
					cout << "Doriti sa efectuati alta operatiune?\n1.Da\n2.Nu: ";
					int altaOperatiune;
					cin >> altaOperatiune;
					if (altaOperatiune == 1)
					{
						system("cls");
					}
					else
					{
						break;
					}
				}
				if (optiune == 3)
				{
					if (mMenu.getNrProduse() == 0)
					{
						cout << "Nu sunt produse disponibile in magazin!" << endl;
					}
					else
					{
						for (int i = 0; i < mMenu.getNrProduse(); i++)
						{
							cout << *mMenu.getProdus()[i] << endl;
						}
					}
					cout << "Introduceti ID-ul produsului pe care doriti sa il scoateti din oferta: ";
					int idProdEliminat;
					cin >> idProdEliminat;
					for (int i = 0; i < mMenu.getNrProduse(); i++)
					{
						if (mMenu.getProdus()[i]->getIdProdus() == idProdEliminat)
						{
							mMenu -= *mMenu.getProdus()[i];
							cout << "Produsul a fost eliminat cu succes!" << endl << endl;
						}
						else
						{
							cout << "Id-ul produsului cautat nu exista!" << endl;
						}
					}
					cout << "Doriti sa efectuati alta operatiune?\n1.Da\n2.Nu: ";
					int altaOperatiune;
					cin >> altaOperatiune;
					if (altaOperatiune == 1)
					{
						system("cls");
					}
					else
					{
						break;
					}
				}
				if (optiune == 4)
				{
					string numeProd;
					cout << "Va rugam sa introduceti numele produsului: ";
					cin >> numeProd;
					int nr = 0;
					for (int i = 0; i < mMenu.getNrProduse(); i++)
					{

						string numeCautat = mMenu.getProdus()[i]->getNumeProdus();
						if (strstr(strUp(numeCautat).c_str(), strUp(numeProd).c_str()))
						{
							nr++;
							cout << mMenu.getProdus()[i]->getNumeProdus() << " - " << mMenu.getProdus()[i]->getPretProdus() << endl;
							cout << "-----------------------------------" << endl;
							//agendaTlf -= agendaTlf.getContacte()[i]; -- ca sa eliminam

						}

					}
					if (nr == 0)
					{
						cout << "Nu am gasit niciun rezultat!" << endl;
					}
					cout << "Doriti sa efectuati alta operatiune?\n1.Da\n2.Nu: ";
					int altaOperatiune;
					cin >> altaOperatiune;
					if (altaOperatiune == 1)
					{
						system("cls");
					}
					else
					{
						break;
					}
				}
				if (optiune == 5)
				{
					int idProd;
					cout << "Va rugam sa introduceti id-ul produsului: ";
					cin >> idProd;
					int nr = 0;
					for (int i = 0; i < mMenu.getNrProduse(); i++)
					{

						int idCautat = mMenu.getProdus()[i]->getIdProdus();
						if (idCautat == idProd)
						{
							nr++;
							cout << mMenu.getProdus()[i]->getIdProdus()<<" - " << mMenu.getProdus()[i]->getNumeProdus() << " - " << mMenu.getProdus()[i]->getPretProdus() << endl;
							cout << "-----------------------------------" << endl;

						}

					}
					if (nr == 0)
					{
						cout << "Produsul cautat nu mai face parte din oferta noastra!" << endl;
					}
					cout << "Doriti sa efectuati alta operatiune?\n1.Da\n2.Nu: ";
					int altaOperatiune;
					cin >> altaOperatiune;
					if (altaOperatiune == 1)
					{
						system("cls");
					}
					else
					{
						break;
					}
				}
				if (optiune == 6)
				{
					system("cls");
					if (mMenu.getnrComenzi() == 0)
					{
						cout << "Nu sunt produse disponibile in magazin!" << endl;
					}
					else
					{
						cout << "\t\t\tCOMENZIILE TOTALE DIN MAGAZIN: " << endl<<endl <<endl;
						for (int i = 0; i < mMenu.getnrComenzi(); i++)
						{
							cout << *mMenu.getComanda()[i] << endl;
						}
					}
					cout << endl << endl;
					cout << "Doriti sa efectuati alta operatiune?\n1.Da\n2.Nu: ";
					int altaOperatiune;
					cin >> altaOperatiune;
					if (altaOperatiune == 1)
					{
						system("cls");
					}
					else
					{
						break;
					}
				}
				if (optiune == 7)
				{
					Comanda comandaMagAdaugata;
					cin >> comandaMagAdaugata;
					mMenu.adaugaComanda(comandaMagAdaugata);
					cout << "Comanda a fost adaugat cu succes!" << endl << endl;
					cout << "Doriti sa efectuati alta operatiune?\n1.Da\n2.Nu: ";
					int altaOperatiune;
					cin >> altaOperatiune;
					if (altaOperatiune == 1)
					{
						system("cls");
					}
					else
					{
						break;
					}
				}
				if (optiune == 8)
				{
					system("cls");
					if (mMenu.getnrComenzi() == 0)
					{
						cout << "Nu sunt comenzi disponibile in magazin!" << endl;
					}
					else
					{
						cout << "\t\t\tCOMENZIILE TOTALE DIN MAGAZIN: " << endl << endl << endl;
						for (int i = 0; i < mMenu.getnrComenzi(); i++)
						{
							cout << *mMenu.getComanda()[i] << endl;
						}
					}
					int idCom;
					cout << "Va rugam sa introduceti id-ul produsului: ";
					cin >> idCom;
					int nr = 0;
					for (int i = 0; i < mMenu.getnrComenzi(); i++)
					{
						int idCautat = mMenu.getComanda()[i]->getIdComanda();
						if (idCautat == idCom)
						{
							nr++;
							Comanda cModificat;
							cin >> cModificat;
						
							mMenu.setComanda(i,cModificat);
							cout << "Comanda  a fost modificata!" << endl;
							cout << "-----------------------------------" << endl;

						}

					}
					if (nr == 0)
					{
						cout << "Produsul cautat nu mai face parte din oferta noastra!" << endl;
					}
					cout << "Doriti sa efectuati alta operatiune?\n1.Da\n2.Nu: ";
					int altaOperatiune;
					cin >> altaOperatiune;
					if (altaOperatiune == 1)
					{
						system("cls");
					}
					else
					{
						break;
					}
				}

				if (optiune == 9)
				{
					string numeProd;
					cout << "Va rugam sa introduceti numele produsului: ";
					cin >> numeProd;
					int nr = 0;
					for (int i = 0; i < mMenu.getnrComenzi(); i++)
					{
						int nrProdInCom = mMenu.getComanda()[i]->getCos().getNrProduse();
						
						for (int j = 0; j < nrProdInCom; j++)
						{
							string numeCautat = mMenu.getComanda()[i]->getCos().getProdus()[j]->getNumeProdus();
						if (strstr(strUp(numeCautat).c_str(), strUp(numeProd).c_str()))
						{
							nr++;
							cout << *mMenu.getComanda()[i] << endl;
							cout << "-----------------------------------" << endl;
							

						}
						}
					}
					if (nr == 0)
					{
						cout << "Nu am gasit niciun rezultat!" << endl;
					}
					cout << "Doriti sa efectuati alta operatiune?\n1.Da\n2.Nu: ";
					int altaOperatiune;
					cin >> altaOperatiune;
					if (altaOperatiune == 1)
					{
						system("cls");
					}
					else
					{
						break;
					}
				}
				if (optiune == 10)
				{
					int dataCautat[3];
					cout << "Va rugam introduceti data dupa care vreti sa cautati o comanda: ";
					cout << "Zi: ";
					cin >> dataCautat[0];
					cout << "Luna: ";
					cin >> dataCautat[1];
					cout << "An: ";
					cin >> dataCautat[2];
					int nr = 0;
					for (int i = 0; i < mMenu.getnrComenzi(); i++)
					{
						if (mMenu.getComanda()[i]->getData()[0] == dataCautat[0] && mMenu.getComanda()[i]->getData()[1] == dataCautat[1] && mMenu.getComanda()[i]->getData()[2] == dataCautat[2])
						{
							nr++;
							cout << *mMenu.getComanda()[i] << endl;
							cout << "-----------------------------------" << endl;
						}
					}
					if (nr == 0)
					{
						cout << "Nu am gasit niciun rezultat!" << endl;
					}
					cout << "Doriti sa efectuati alta operatiune?\n1.Da\n2.Nu: ";
					int altaOperatiune;
					cin >> altaOperatiune;
					if (altaOperatiune == 1)
					{
						system("cls");
					}
					else
					{
						break;
					}
				}
				if (optiune == 11)
				{
					if (mMenu.getnrComenzi() == 0)
					{
						cout << "Nu sunt comenzi efectuate in magazin!" << endl;
					}
					else
					{
						for (int i = 0; i < mMenu.getnrComenzi(); i++)
						{
							cout << *mMenu.getComanda()[i] << endl;
						}
					}
					cout << "Introduceti ID-ul produsului pe care doriti sa il scoateti din oferta: ";
					int idProdEliminat;
					cin >> idProdEliminat;
					for (int i = 0; i < mMenu.getnrComenzi(); i++)
					{
						if (mMenu.getComanda()[i]->getIdComanda() == idProdEliminat)
						{
							mMenu.EliminaComanda( *mMenu.getComanda()[i]);
							cout << "Produsul a fost eliminat cu succes!" << endl << endl;
						}
						else
						{
							cout << "Id-ul produsului cautat nu exista!" << endl;
						}
					}
					cout << "Doriti sa efectuati alta operatiune?\n1.Da\n2.Nu: ";
					int altaOperatiune;
					cin >> altaOperatiune;
					if (altaOperatiune == 1)
					{
						system("cls");
					}
					else
					{
						break;
					}
				}
				if (optiune == 12)
				{
					int* data = new int[3];
					cout << "introduceti Ziua cautata: ";
					cin >> data[0];
					cout << "introduceti luna cautata: ";
					cin >> data[1];
					cout << "introduceti an cautata: ";
					cin >> data[2];
					float totalIncasari = 0;
					istoric<Comanda> istoricCom;
					string numeFis = "comanda" + to_string(data[0]) + to_string(data[1]) + to_string(data[2]) + ".txt";
					ofstream fil(numeFis, ios::out);
					for (int i = 0; i < mMenu.getnrComenzi(); i++)
					{
						istoricCom += *mMenu.getComanda()[i];
					}
					cout << "-----------------" << endl;
					for (int i = 0; i < istoricCom.getNumar(); i++)
					{

						if (istoricCom.getCOM()[i].getData()[0] == data[0] && istoricCom.getCOM()[i].getData()[1] == data[1] && istoricCom.getCOM()[i].getData()[2] == data[2])
						{

							fil << istoricCom.getCOM()[i];
							totalIncasari += (float)istoricCom.getCOM()[i];
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
					fil.close();
					cout << "Doriti sa efectuati alta operatiune?\n1.Da\n2.Nu: ";
					int altaOperatiune;
					cin >> altaOperatiune;
					if (altaOperatiune == 1)
					{
						system("cls");
					}
					else
					{
						break;
					}
				}
				if (optiune == 13)
				{
					int* data = new int[3];
					data[0] = 1;;
					cout << "introduceti luna cautata: ";
					cin >> data[1];
					cout << "introduceti an cautata: ";
					cin >> data[2];
					float totalIncasari = 0;
					istoric<Comanda> istoricCom;
					string numeFis = "comanda" +  to_string(data[1]) + to_string(data[2]) + ".txt";
					ofstream fil(numeFis, ios::out);
					for (int i = 0; i < mMenu.getnrComenzi(); i++)
					{
						istoricCom += *mMenu.getComanda()[i];
					}
					cout << "-----------------" << endl;
					for (int i = 0; i < istoricCom.getNumar(); i++)
					{

						if ( istoricCom.getCOM()[i].getData()[1] == data[1] && istoricCom.getCOM()[i].getData()[2] == data[2])
						{

							fil << istoricCom.getCOM()[i];
							totalIncasari += (float)istoricCom.getCOM()[i];
						}

					}
					if (totalIncasari > 0)
					{
						cout << "Valoare totala a comenzilor din " << data[1] << "/" << data[2] << " este: " << totalIncasari << " de lei!" << endl;

					}
					else
					{
						cout << "Din pacate in acea zi nu s-au inregistrat comenzi!" << endl;
					}
					fil.close();
					cout << "Doriti sa efectuati alta operatiune?\n1.Da\n2.Nu: ";
					int altaOperatiune;
					cin >> altaOperatiune;
					if (altaOperatiune == 1)
					{
						system("cls");
					}
					else
					{
						break;
					}
				}
				if (optiune == 14)
				{
					int* data = new int[3];
					data[0] = 1;
					data[1] = 1;
					cout << "introduceti an cautata: ";
					cin >> data[2];
					float totalIncasari = 0;
					istoric<Comanda> istoricCom;
					string numeFis = "comanda"  + to_string(data[2]) + ".txt";
					ofstream fil(numeFis, ios::out);
					for (int i = 0; i < mMenu.getnrComenzi(); i++)
					{
						istoricCom += *mMenu.getComanda()[i];
					}
					cout << "-----------------" << endl;
					for (int i = 0; i < istoricCom.getNumar(); i++)
					{

						if ( istoricCom.getCOM()[i].getData()[2] == data[2])
						{

							fil << istoricCom.getCOM()[i];
							totalIncasari += (float)istoricCom.getCOM()[i];
						}

					}
					if (totalIncasari > 0)
					{
						cout << "Valoare totala a comenzilor din anul"  << data[2] << " este: " << totalIncasari << " de lei!" << endl;

					}
					else
					{
						cout << "Din pacate in acea zi nu s-au inregistrat comenzi!" << endl;
					}
					fil.close();
					cout << "Doriti sa efectuati alta operatiune?\n1.Da\n2.Nu: ";
					int altaOperatiune;
					cin >> altaOperatiune;
					if (altaOperatiune == 1)
					{
						system("cls");
					}
					else
					{
						break;
					}
				}
				if (optiune == 15)
				{
					
					float totalIncasari = 0;
					istoric<Comanda> istoricCom;
					string numeFis = "comanda" + to_string(data[2]) + ".txt";
					ofstream fil(numeFis, ios::out);
					for (int i = 0; i < mMenu.getnrComenzi(); i++)
					{
						istoricCom += *mMenu.getComanda()[i];
					}
					cout << "-----------------" << endl;
					for (int i = 0; i < istoricCom.getNumar(); i++)
					{

					

							fil << istoricCom.getCOM()[i];
							totalIncasari += (float)istoricCom.getCOM()[i];
						

					}
					if (totalIncasari > 0)
					{
						cout << "Valoare totala a comenzilor totale este: " << totalIncasari << " de lei!" << endl;

					}
					else
					{
						cout << "Din pacate in acea zi nu s-au inregistrat comenzi!" << endl;
					}
					fil.close();
					cout << "Doriti sa efectuati alta operatiune?\n1.Da\n2.Nu: ";
					int altaOperatiune;
					cin >> altaOperatiune;
					if (altaOperatiune == 1)
					{
						system("cls");
					}
					else
					{
						break;
					}
				}
				if (optiune == 16)
				{
					system("cls");
					if (mMenu.getProdus() == 0)
					{
						cout << "Nu sunt produse disponibile in magazin!" << endl;
					}
					else
					{
						cout << "\t\t\PRODUSELE DIN MAGAZIN: " << endl << endl << endl;
						for (int i = 0; i < mMenu.getNrProduse(); i++)
						{
							cout << *mMenu.getProdus()[i] << endl;
						}
					}
					int idCom;
					cout << "Va rugam sa introduceti id-ul produsului: ";
					cin >> idCom;
					int nr = 0;
					for (int i = 0; i < mMenu.getNrProduse(); i++)
					{
						int idCautat = mMenu.getProdus()[i]->getIdProdus();
						if (idCautat == idCom)
						{
							nr++;
							Produs pModificat;
							cin >> pModificat;

							mMenu.setProdus(i, pModificat);
							cout << "Produsul  a fost modificata!" << endl;
							cout << "-----------------------------------" << endl;

						}

					}
					if (nr == 0)
					{
						cout << "Produsul cautat nu mai face parte din oferta noastra!" << endl;
					}
					cout << "Doriti sa efectuati alta operatiune?\n1.Da\n2.Nu: ";
					int altaOperatiune;
					cin >> altaOperatiune;
					if (altaOperatiune == 1)
					{
						system("cls");
					}
					else
					{
						break;
					}
				}
				if (optiune == 17)
				{
					vector<Produs> vectSortProd;
					vector<Produs>::iterator it;
					for (int i = 0; i < mMenu.getNrProduse(); i++)
					{
						vectSortProd.push_back(*mMenu.getProdus()[i]);

					}
					cout << " Produsele sortate dupa pret crescator sunt: "<<endl;
					sort(vectSortProd.begin(), vectSortProd.end(), compararePreturiProduse<Produs>);
					for (it= vectSortProd.begin(); it != vectSortProd.end(); it++)
					{
						cout << *it << endl;
					}
					cout << "Doriti sa efectuati alta operatiune?\n1.Da\n2.Nu: ";
					int altaOperatiune;
					cin >> altaOperatiune;
					if (altaOperatiune == 1)
					{
						system("cls");
					}
					else
					{
						break;
					}
				}
				if (optiune == 18)
				{
					vector<Comanda> vectSortCom;
					vector<Comanda>::iterator it;
					for (int i = 0; i < mMenu.getnrComenzi(); i++)
					{
						vectSortCom.push_back(*mMenu.getComanda()[i]);

					}
					cout << " Produsele sortate dupa valoarea comenzii descrescator sunt: " << endl;
					sort(vectSortCom.begin(), vectSortCom.end(), comparareValoareComanda<Comanda>);
					for (it = vectSortCom.begin(); it != vectSortCom.end(); it++)
					{
						cout << *it << endl;
					}
					cout << "Doriti sa efectuati alta operatiune?\n1.Da\n2.Nu: ";
					int altaOperatiune;
					cin >> altaOperatiune;
					if (altaOperatiune == 1)
					{
						system("cls");
					}
					else
					{
						break;
					}
				}
				if (optiune == 19)
				{
					vector<Comanda> vectSortCom1;
					vector<Comanda>::iterator it1;
					for (int i = 0; i < mMenu.getnrComenzi(); i++)
					{
						vectSortCom1.push_back(*mMenu.getComanda()[i]);

					}
					cout << " Produsele sortate dupa data  sunt: " << endl;
					sort(vectSortCom1.begin(), vectSortCom1.end(), comparareComandaData<Comanda>);
					for (it1 = vectSortCom1.begin(); it1 != vectSortCom1.end(); it1++)
					{
						cout << *it1 << endl;
					}
					cout << "Doriti sa efectuati alta operatiune?\n1.Da\n2.Nu: ";
					int altaOperatiune;
					cin >> altaOperatiune;
					if (altaOperatiune == 1)
					{
						system("cls");
					}
					else
					{
						break;
					}
				}
				if (optiune == 20)
				{
					
					cout << "Doriti sa efectuati alta operatiune?\n1.Da\n2.Nu: ";
					int altaOperatiune;
					cin >> altaOperatiune;
					if (altaOperatiune == 1)
					{
						system("cls");
					}
					else
					{
						break;
					}
				}
				if (optiune<=0 || optiune > 20)
				{
					cout << "Comanda introdusa de dumneavoastra nu exista!" << endl;
					cout << "Doriti sa efectuati alta operatiune?\n1.Da\n2.Nu: ";
					int altaOperatiune;
					cin >> altaOperatiune;
					if (altaOperatiune == 1)
					{
						system("cls");
					}
					else
					{
						break;
					}
				}
			} while (optiune >0);
			
		}
		else if (optiuneAccesMeniu == cMenu.tipAdmin())
		{
		
			
			do
			{
				cout << " Sunteti logat in postura de client!" << endl;
				cMenu.MeniuAplicatie();
				cout << "Introduceti optiune: ";
				cin >> optiune;
				system("cls");
				if (optiune == 1)
				{
					if (mMenu.getNrProduse() == 0)
					{
						cout << "Nu sunt produse disponibile in magazin!" << endl;
					}
					else
					{
						cout << "Produsele din magazin: " << endl;
						for (int i = 0; i < mMenu.getNrProduse(); i++)
						{
							cout << *mMenu.getProdus()[i] << endl;
						}
					}
					cout << "Doriti sa efectuati alta operatiune?\n1.Da\n2.Nu: ";
					int altaOperatiune;
					cin >> altaOperatiune;
					if (altaOperatiune == 1)
					{
						system("cls");
					}
					else
					{
						break;
					}
				}
				
				if (optiune == 2)
				{
					if (cCosPtClient.getNrProduse() == 0)
					{
						cout << "Nu aveti niciun produs in cos" << endl;
					}
					else
					{
						cout << "Cosul dumneavoastra contine: " << endl;
						for (int i = 0; i < cCosPtClient.getNrProduse(); i++)
						{
							cout << *cCosPtClient.getProdus()[i] << endl;
						}
					}
					cout << "Doriti sa efectuati alta operatiune?\n1.Da\n2.Nu: ";
					int altaOperatiune;
					cin >> altaOperatiune;
					if (altaOperatiune == 1)
					{
						system("cls");
					}
					else
					{
						break;
					}
				}
				if (optiune == 3)
				{
					if (mMenu.getNrProduse() == 0)
					{
						cout << "Nu sunt produse disponibile in magazin!" << endl;
					}
					else
					{
						cout << "Produsele din magazin: " << endl;
						for (int i = 0; i < mMenu.getNrProduse(); i++)
						{
							cout << *mMenu.getProdus()[i] << endl;
						}
					}
					cout << "Introduceti id-ul produsului pe care doriti sa il adaugati in cos: ";
					int idProdAdaugat;
					cin >> idProdAdaugat;
					int nr = 0;
					for (int i = 0; i < mMenu.getNrProduse(); i++)
					{
						if (mMenu.getProdus()[i]->getIdProdus() == idProdAdaugat)
						{
							cCosPtClient += *mMenu.getProdus()[i];
							
							nr++;
						}
						
					}
					if (nr > 0)
					{
						cout << "Produsul a fost adaugat cu succes!" << endl << endl;
					}
					else
					{
						cout << "Id-ul produsului cautat nu exista!" << endl;
					}
					cout << "Doriti sa efectuati alta operatiune?\n1.Da\n2.Nu: ";
					int altaOperatiune;
					cin >> altaOperatiune;
					if (altaOperatiune == 1)
					{
						system("cls");
					}
					else
					{
						break;
					}
				}
				if (optiune == 4)
				{
					if (cCosPtClient.getNrProduse() == 0)
					{
						cout << "Nu sunt produse disponibile in magazin!" << endl;
					}
					else
					{
						for (int i = 0; i < cCosPtClient.getNrProduse(); i++)
						{
							cout << *cCosPtClient.getProdus()[i] << endl;
						}
					}
					cout << "Introduceti ID-ul produsului pe care doriti sa il scoateti din oferta: ";
					int idProdEliminat;
					cin >> idProdEliminat;
					for (int i = 0; i < cCosPtClient.getNrProduse(); i++)
					{
						if (cCosPtClient.getProdus()[i]->getIdProdus() == idProdEliminat)
						{
							cCosPtClient -= *cCosPtClient.getProdus()[i];
							cout << "Produsul a fost eliminat cu succes!" << endl << endl;
						}
						else
						{
							cout << "Id-ul produsului cautat nu exista!" << endl;
						}
					}
					cout << "Doriti sa efectuati alta operatiune?\n1.Da\n2.Nu: ";
					int altaOperatiune;
					cin >> altaOperatiune;
					if (altaOperatiune == 1)
					{
						system("cls");
					}
					else
					{
						break;
					}
				}
				if (optiune == 5)
				{
					time_t now = time(0);

					tm* ltm = localtime(&now);

					int dataComandaAzi[3];
					dataComandaAzi[0] = (int)ltm->tm_mday;
					dataComandaAzi[1] = (int)1+ltm->tm_mon;
					dataComandaAzi[2] = (int)1900+ltm->tm_year;
					//am cautat chestia asta cu data pe net pentru ca nu stiam ce data sa pun la comanda
					Comanda cClientVanzare(dataComandaAzi, &cCosPtClient);
					Client clientComTrimisa;
					cout << "Numele dvs: ";
					char numePers[100];
					cin >> ws;
					cin.getline(numePers,99);
					clientComTrimisa.setNume(numePers);
					cout << "Adresa dvs: ";
					string adrPers;
					getline(cin, adrPers);
					clientComTrimisa.setAdresa(adrPers);
					clientComTrimisa.adaugaComanda(cClientVanzare);
					string numeFisComandaClient = "comanda" + (string)clientComTrimisa.getNume()+".txt";
					ofstream fisierCom(numeFisComandaClient, ios::out);
					float valoareTotalaPlata = (float)clientComTrimisa;
					fisierCom << clientComTrimisa;
					fisierCom << "Valoarea totala a comenzii este: " << valoareTotalaPlata <<" lei"<< endl;
					fisierCom.close();
					cout << "Valoarea totala a comenzii este: " << valoareTotalaPlata << " lei" << endl;
					cout << "Comanda dvs a fost inregistrata!" << endl;
					cout << "Doriti sa efectuati alta operatiune?\n1.Da\n2.Nu: ";
					int altaOperatiune;
					cin >> altaOperatiune;
					if (altaOperatiune == 1)
					{
						system("cls");
					}
					else
					{
						break;
					}
				}
			} while (optiune > 0 && optiune < 10);
		
		}
		else
		{
			cout << "Nu ati introdus o valoare corecta! Magazinul " << m1.getNume() << " va ureaza o zi frumoasa!" << endl;
		}

	} while (optiuneAccesMeniu == "client" || optiuneAccesMeniu == "magazin");
}
