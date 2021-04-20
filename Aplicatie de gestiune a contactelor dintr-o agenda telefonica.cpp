
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include <set>
#include <algorithm>
using namespace std;
class ExceptieAfisare {
private:
	string mesaj;
public:
	ExceptieAfisare(string mesaj) {
		this->mesaj = mesaj;
	}
	string getMesaj() {
		return mesaj;
	}
};

class Afisare
{
public:
	virtual void serializare(string numeFisier) = 0;
	virtual void deserializare(string numeFisier) = 0;
	virtual string TipContact() = 0;
};
string strUp(string& str)
{
	for (unsigned int i = 0; str[i] != 0; i++)
		str[i] = toupper(str[i]);
	return str;
}
class Factura
{
public:
	virtual float calculTarifDePlata() = 0;
};
class Contact:public Afisare
{
protected:
	string nume;
	string email;
	string nrTelefon;
	int nrApeluri;
	int* durataApeluri;//durata in minute 
	
public:
	string getNume()
	{
		return this->nume;
	}
	string getEmail()
	{
		return this->email;
	}
	string getNrTelefon()
	{
		return this->nrTelefon;
	}
	int getNrApeluri()
	{
		return this->nrApeluri;
	}
	int* getDurataApeluri()
	{
		return this->durataApeluri;
	}
	void setNume(string nume)
	{
		if (nume.size() >= 3)
		{
			this->nume = nume;
		}
		else
		{
			throw ExceptieAfisare("Nume incorect");
		}
	}
	void setEmail(string email)
	{
		if (email.size() >= 3)
		{
			this->email = email;
		}
		else
		{
			throw ExceptieAfisare("Email incorect");
		}
	}
	void setNrTelefon(string nrTelefon)
	{
		if (nrTelefon.size() == 10 || nrTelefon.size() == 13)
		{
			this->nrTelefon = nrTelefon;
		}
		else
		{
			throw ExceptieAfisare("Numar telefon incorect");
		}
	}
	void setDurataApeluri(int nrApeluri, int* durataApeluri)
	{
		if (nrApeluri > 0 && durataApeluri != NULL)
		{
			this->nrApeluri = nrApeluri;
			this->durataApeluri = new int[this->nrApeluri];
			for (int i = 0; i < this->nrApeluri; i++)
			{
				this->durataApeluri[i] = durataApeluri[i];
			}
		}
	}
	
	Contact()
	{
		this->nume = "Necunoscut";
		this->email = "Necunoscut";
		this->nrTelefon = "0123456789";
		this->nrApeluri = 0;
		this->durataApeluri = NULL;
	}
	Contact(string nume, string nrTelefon)
	{
		if (nume.size() >= 3)
		{
			this->nume = nume;
		}
		else
		{
			this->nume = "Necunoscut";
		}
		if (email.size() >= 3)
		{
			this->email = email;
		}
		else
		{
			this->email = "Necunoscut";
		}
		if (nrTelefon.size() == 10 || nrTelefon.size() == 13)
		{
			this->nrTelefon = nrTelefon;
		}
		else
		{
			this->nrTelefon = "0123456789";
		}
	
			this->nrApeluri = 0;
			this->durataApeluri = NULL;
		

	}
	Contact(string nume,string email, string nrTelefon, int nrApeluri, int* durataApeluri)
	{
		if (nume.size() >= 3)
		{
			this->nume = nume;
		}
		else
		{
			this->nume = "Necunoscut";
		}
		if (email.size() >= 3)
		{
			this->email = email;
		}
		else
		{
			this->email = "Necunoscut";
		}
		if (nrTelefon.size() == 10 || nrTelefon.size() == 13 || nrTelefon.size() == 12)
		{
			this->nrTelefon = nrTelefon;
		}
		else
		{
			this->nrTelefon = "0123456789";
		}
		if (nrApeluri > 0 && durataApeluri != NULL)
		{
			this->nrApeluri = nrApeluri;
			this->durataApeluri = new int[this->nrApeluri];
			for (int i = 0; i < this->nrApeluri; i++)
			{
				this->durataApeluri[i] = durataApeluri[i];
			}
		}
		else
		{
			this->nrApeluri = 0;
			this->durataApeluri = NULL;
		}
	
	}
	Contact(const Contact &c)
	{
		if (c.nume.size() >= 3)
		{
			this->nume = c.nume;
		}
		else
		{
			this->nume = "Necunoscut";
		}
		if (c.email.size() >= 3)
		{
			this->email = c.email;
		}
		else
		{
			this->email = "Necunoscut";
		}
		if (c.nrTelefon.size() == 10 || c.nrTelefon.size() == 13 || c.nrTelefon.size() == 12)
		{
			this->nrTelefon = c.nrTelefon;
		}
		else
		{
			this->nrTelefon = "0123456789";
		}
		if (c.nrApeluri > 0 && c.durataApeluri != NULL)
		{
			this->nrApeluri = c.nrApeluri;
			this->durataApeluri = new int[this->nrApeluri];
			for (int i = 0; i < this->nrApeluri; i++)
			{
				this->durataApeluri[i] = c.durataApeluri[i];
			}
		}
		else
		{
			this->nrApeluri = 0;
			this->durataApeluri = NULL;
		}

	}
	virtual ~Contact()
	{
		if (this->durataApeluri != NULL)
		{
			delete[]this->durataApeluri;
		}
	}
	Contact& operator=(const Contact& c)
	{
		if (this != &c)
		{
			if (this->durataApeluri != NULL)
			{
				delete[]this->durataApeluri;
			}
			if (c.nume.size() >= 3)
			{
				this->nume = c.nume;
			}
			else
			{
				this->nume = "Necunoscut";
			}
			if (c.email.size() >= 3)
			{
				this->email = c.email;
			}
			else
			{
				this->email = "Necunoscut";
			}
			if (c.nrTelefon.size() == 10 || c.nrTelefon.size() == 13 || c.nrTelefon.size() == 12)
			{
				this->nrTelefon = c.nrTelefon;
			}
			else
			{
				this->nrTelefon = "Numar-Gresit";
			}
			if (c.nrApeluri > 0 && c.durataApeluri != NULL)
			{
				this->nrApeluri = c.nrApeluri;
				this->durataApeluri = new int[this->nrApeluri];
				for (int i = 0; i < this->nrApeluri; i++)
				{
					this->durataApeluri[i] = c.durataApeluri[i];
				}
			}
			else
			{
				this->nrApeluri = 0;
				this->durataApeluri = NULL;
			}

		}
		return *this;
	}
	friend ostream& operator<<(ostream& out, const Contact& c)
	{
		out << "Nume: " << c.nume << endl;
		out << "Email: " << c.email << endl;
		out << "Numar Telefon: " << c.nrTelefon << endl;
		out << "Numar Apeluri: " << c.nrApeluri << endl;
		out << "Durata Apeluri: ";
		for (int i = 0; i < c.nrApeluri; i++)
		{
			out << c.durataApeluri[i] << " ";
		}
		 
		return out;
	}
	friend ofstream& operator<<(ofstream& out, const Contact& c)
	{
		out << c.nume << endl;
		out << c.email << endl;
		out  << c.nrTelefon << endl;
		out  << c.nrApeluri << endl;
		for (int i = 0; i < c.nrApeluri; i++)
		{
			out << c.durataApeluri[i] << " ";
		}

		return out;
	}
	friend istream& operator>>(istream& in, Contact& c)
	{
		delete[]c.durataApeluri;
		cout << "Nume: ";
		in >> ws;
		getline(in, c.nume);
		cout << "Email: ";
		in >> ws;
		getline(in, c.email);
		cout << "Numar Telefon: ";
		in >> ws;
		getline(in, c.nrTelefon);
		cout << "Numar Apeluri: ";
		in >> c.nrApeluri;
		cout << "Durata Apeluri: ";
		c.durataApeluri = new int[c.nrApeluri];
		for (int i = 0; i < c.nrApeluri; i++)
		{
			in >> c.durataApeluri[i];
		}
		return in;
	}
	friend ifstream& operator>>(ifstream& in, Contact& c)
	{
		delete[]c.durataApeluri;
		in >> ws;
		getline(in, c.nume);
		in >> ws;
		getline(in, c.email);
		in >> ws;
		getline(in, c.nrTelefon);
		in >> c.nrApeluri;
		c.durataApeluri = new int[c.nrApeluri];
		for (int i = 0; i < c.nrApeluri; i++)
		{
			in >> c.durataApeluri[i];
		}
		return in;
	}
	int durataTotalaApeluri()
	{
		int suma = 0;
		for (int i = 0; i < this->nrApeluri; i++)
		{
			suma += this->durataApeluri[i];
		}
		return suma;
	}
	float medieTotalaApeluri()
	{
		float suma = 0;
		for (int i = 0; i < this->nrApeluri; i++)
		{
			suma += this->durataApeluri[i];
		}
		return suma/this->nrApeluri;
	}
	int durataUltimApel()
	{
		return this->durataApeluri[this->nrApeluri-1];
	}
	int maximDurataApel()
	{
		int maxim = this->durataApeluri[0];
		for (int i = 0; i < this->nrApeluri; i++)
		{
			if (this->durataApeluri[i] > maxim)
			{
				maxim = this->durataApeluri[i];
			}
		}
		return maxim;
	}
	int minimDurata()
	{
		int minim = this->durataApeluri[0];
		for (int i = 0; i < this->nrApeluri; i++)
		{
			if (this->durataApeluri[i] < minim)
			{
				minim = this->durataApeluri[i];
			}
		}
		return minim;
	}
	void adaugaApel(int durata)
	{
		Contact copie = *this;
		delete[] this->durataApeluri;
		this->nrApeluri++;
		this->durataApeluri = new int[this->nrApeluri];
		for (int i = 0; i < this->nrApeluri; i++)
		{
			this->durataApeluri[i] = copie.durataApeluri[i];
		}
		this->durataApeluri[this->nrApeluri - 1] = durata;
	}
	Contact& operator+=(int durata)
	{
		Contact copie = *this;
		delete[] this->durataApeluri;
		this->nrApeluri++;
		this->durataApeluri = new int[this->nrApeluri];
		for (int i = 0; i < this->nrApeluri; i++)
		{
			this->durataApeluri[i] = copie.durataApeluri[i];
		}
		this->durataApeluri[this->nrApeluri - 1] = durata;
		return *this;
	}
	Contact& operator--()
	{
		Contact copie = *this;
		delete[] this->durataApeluri;
		this->nrApeluri--;
		for (int i = 0; i < this->nrApeluri; i++)
		{
			this->durataApeluri[i] = copie.durataApeluri[i];
		}
		return *this;
	}
	bool operator<(const Contact& c)
	{
		int suma1 = 0;
		int suma2 = 0;
		for (int i = 0; i < this->nrApeluri; i++)
		{
			suma1 += this->durataApeluri[i];
		}

		for (int i = 0; i < c.nrApeluri; i++)
		{
			suma2 += c.durataApeluri[i];
		}
		return suma1 < suma2;
	}
	bool operator>(const Contact& c)
	{
		return this->nrApeluri > c.nrApeluri;
	}
	bool contactStrainatate()
	{
		bool contactStrain = 0;
		string prefix = this->nrTelefon.substr(0, 3);
		string nr = this->nrTelefon.substr(0, 2);
		cout << prefix << endl;
		cout << nr << endl;
		if (prefix != "+40" && nr != "07")
		{
			contactStrain = 1;
		}
		return contactStrain;
	}
	void serializare(string numeFisier)
	{
		ofstream file(numeFisier, ios::out | ios::binary);
		//scrierea in binar pentru string
		int dimNume = this->nume.size();
		file.write((char*)&dimNume, sizeof(int));
		file.write(this->nume.c_str(), dimNume+1);
		//scrierea in binar pentru string
		int dimTelefon = this->nrTelefon.size();
		file.write((char*)&dimTelefon, sizeof(int));
		file.write(this->nrTelefon.c_str(), dimTelefon+1);
		//scrierea in binar pentru numerice(int,float,double,bool)
		file.write((char*)&this->nrApeluri, sizeof(int));
		//scrierea in binar pentru numerice*
		for (int i = 0; i < this->nrApeluri; i++)
		{
			file.write((char*)&this->durataApeluri[i], sizeof(int));
		}
	}
	void deserializare(string numeFisier)
	{
		ifstream file(numeFisier, ios::in | ios::binary);
		if (this->durataApeluri != NULL)
		{
			delete[] this->durataApeluri;
		}
		//citire din binar a unui string
		int dimNume;
		file.read((char*)&dimNume, sizeof(int));
		char* aux = new char[dimNume+1];
		file.read((char*)aux, dimNume+1);
		this->nume = aux;
		int dimTLF;
		file.read((char*)&dimTLF, sizeof(int));
		char* aux1 = new char[dimTLF + 1];
		file.read((char*)aux1, dimTLF+1);
		this->nrTelefon = aux1;
		//citire in binar pentru numerice(int,float,double,bool)
		file.read((char*)&this->nrApeluri, sizeof(int));
		this->durataApeluri = new int[this->nrApeluri];
		//citire in binar pentru numerice*
		for (int i = 0; i < this->nrApeluri; i++)
		{
			file.read((char*)&this->durataApeluri[i], sizeof(int));
		}

	}
	string TipContact()
	{
		return "Contact Personal";
	}
};
class ContactMunca:public Contact
{
	string numeFirma;
	string numarFirma;
public:
	ContactMunca() : Contact()
	{
		this->numeFirma = "Necunoscuta";
		this->numarFirma = "0123456789";
	}
	ContactMunca(string nume,string email, string nrTelefon, int nrApeluri, int* durataApeluri, string numeFirma, string numarFirma):Contact( nume, email, nrTelefon,  nrApeluri, durataApeluri)
	{
		this->numeFirma = numeFirma;
		this->numarFirma = numarFirma;
	}
	ContactMunca(const ContactMunca& c) :Contact(c)
	{
		this->numeFirma = c.numeFirma;
		this->numarFirma = c.numarFirma;
	}
	~ContactMunca()
	{

	}
	ContactMunca &operator= (const ContactMunca& c)
	{
		if (this != &c)
		{
			Contact::operator=(c);
			this->numeFirma = c.numeFirma;
			this->numarFirma = c.numarFirma;
		}
	}
	friend ostream& operator<<(ostream& out, const ContactMunca& c)
	{
		out << (Contact)c<<endl;
		out << "Nume firma: " << c.numeFirma << endl;
		out << "Numar Telefon firma : " << c.numarFirma << endl;
		return out;
	}
	friend istream& operator>>(istream& in, ContactMunca& c)
	{
		in >> (Contact&)c;
		cout << "Nume firma: ";
		getline(in, c.numeFirma);
		cout << "Numar Telefon firma : ";
		getline(in, c.numarFirma);
		return in;
	}
	void serializare(string numeFisier)
	{
		ofstream file(numeFisier, ios::out | ios::binary);
		//scrierea in binar pentru string
		int dimNume = this->nume.size();
		file.write((char*)&dimNume, sizeof(int));
		file.write(this->nume.c_str(), dimNume + 1);
		//scrierea in binar pentru string
		int dimTelefon = this->nrTelefon.size();
		file.write((char*)&dimTelefon, sizeof(int));
		file.write(this->nrTelefon.c_str(), dimTelefon + 1);
		//scrierea in binar pentru numerice(int,float,double,bool)
		file.write((char*)&this->nrApeluri, sizeof(int));
		//scrierea in binar pentru numerice*
		for (int i = 0; i < this->nrApeluri; i++)
		{
			file.write((char*)&this->durataApeluri[i], sizeof(int));
		}
		//scrierea in binar pentru string
		int dimNumeFirma = this->numeFirma.size();
		file.write((char*)&dimNumeFirma, sizeof(int));
		file.write(this->numeFirma.c_str(), dimNumeFirma + 1);
		//scrierea in binar pentru string
		int dimTelefonFirma= this->numarFirma.size();
		file.write((char*)&dimTelefonFirma, sizeof(int));
		file.write(this->numarFirma.c_str(), dimTelefonFirma + 1);
	}
	void deserializare(string numeFisier)
	{
		ifstream file(numeFisier, ios::in | ios::binary);
		if (this->durataApeluri != NULL)
		{
			delete[] this->durataApeluri;
		}
		//citire din binar a unui string
		int dimNume;
		file.read((char*)&dimNume, sizeof(int));
		char* aux = new char[dimNume + 1];
		file.read((char*)aux, dimNume + 1);
		this->nume = aux;
		int dimTLF;
		file.read((char*)&dimTLF, sizeof(int));
		char* aux1 = new char[dimTLF + 1];
		file.read((char*)aux1, dimTLF + 1);
		this->nrTelefon = aux1;
		//citire in binar pentru numerice(int,float,double,bool)
		file.read((char*)&this->nrApeluri, sizeof(int));
		this->durataApeluri = new int[this->nrApeluri];
		//citire in binar pentru numerice*
		for (int i = 0; i < this->nrApeluri; i++)
		{
			file.read((char*)&this->durataApeluri[i], sizeof(int));
		}
		//citire din binar a unui string
		int dimNumeFirma;
		file.read((char*)&dimNumeFirma, sizeof(int));
		char* aux2 = new char[dimNumeFirma + 1];
		file.read((char*)aux2, dimNumeFirma + 1);
		this->numeFirma = aux2;
		int dimTLFFirma;
		file.read((char*)&dimTLFFirma, sizeof(int));
		char* aux3 = new char[dimTLFFirma + 1];
		file.read((char*)aux3, dimTLFFirma + 1);
		this->numarFirma = aux3;
	}
	string TipContact()
	{
		return "Contact Munca";
	}
};
class AgendaTelefonica
{
	int nrContacte;
	Contact** contacte;
public:
	AgendaTelefonica()
	{
		this->nrContacte=0;
		this->contacte=NULL;

	}
	int getNrContacte()
	{
		return this->nrContacte;
	}
	Contact** getContacte()
	{
		return this->contacte;
	}
	AgendaTelefonica(int nrContacte, Contact** contacte)
	{
		this->nrContacte = nrContacte;
		this->contacte = new Contact * [this->nrContacte];
		for (int i = 0; i < this->nrContacte; i++)
		{
			this->contacte[i] = contacte[i];
		}
	}
	AgendaTelefonica(const AgendaTelefonica& a)
	{
		this->nrContacte = a.nrContacte;
		this->contacte = new Contact * [this->nrContacte];
		for (int i = 0; i < this->nrContacte; i++)
		{
			this->contacte[i] = a.contacte[i];
		}
	}
	~AgendaTelefonica()
	{
		if (this->contacte != NULL)
		{
			delete[]this->contacte;
		}
	}
	AgendaTelefonica& operator=(const AgendaTelefonica& a)
	{
		if (this->contacte != NULL)
		{
			delete[]this->contacte;
		}
		this->nrContacte = a.nrContacte;
		this->contacte = new Contact * [this->nrContacte];
		for (int i = 0; i < this->nrContacte; i++)
		{
			this->contacte[i] = a.contacte[i];
		}
	}
	AgendaTelefonica& operator+=( Contact &l)
	{
		AgendaTelefonica copie = *this;

		this->contacte = new Contact * [this->nrContacte + 1];
		for (int i = 0; i < this->nrContacte; i++)
		{
			this->contacte[i] = copie.contacte[i];
		}
		this->contacte[this->nrContacte] = new Contact(l);
		this->nrContacte++;
		return *this;
	}

	
	AgendaTelefonica& operator -=(Contact *l)
	{
		AgendaTelefonica copie = *this;
		this->contacte = new Contact * [this->nrContacte];
		int i = 0;
		int j = 0;
		while ((i < this->nrContacte) && (j < this->nrContacte))
		{
			if (copie.contacte[i] != l)//daca obiectul din vector este diferit de cel introdus ca parametru nu il stergem
			{
				this->contacte[j] = copie.contacte[i];
				j++;
			}

			i++;
		}
		this->nrContacte = j;
		return *this;
	}
	void adaugaContact(Contact & l)
	{
		(*this) += l;
	}
	
	friend ostream& operator<<(ostream& out, const AgendaTelefonica& a)
	{
		out << "Nr Contacte: " << a.nrContacte << endl; 
		out << "Contacte: " << endl;
		for (int i = 0; i < a.nrContacte; i++)
		{
			out << *a.contacte[i]<< endl;
		}

		return out;
	}
	friend ofstream& operator<<(ofstream& out, const AgendaTelefonica& a)
	{
		out  << a.nrContacte << endl;
		for (int i = 0; i < a.nrContacte; i++)
		{
			out << *a.contacte[i] << endl;
		}

		return out;
	}
	void serializare(string numeFisier)
	{
		ofstream file(numeFisier, ios::out | ios::binary);
		//scrierea in binar pentru string
		
		file.write((char*)&this->nrContacte, sizeof(int));
		//scrierea in binar pentru numerice*
		for (int i = 0; i < this->nrContacte; i++)
		{
			file.write((char*)&*this->contacte[i], sizeof(*contacte[i]));
		}
	}
	void deserializare(string numeFisier)
	{
		ifstream file(numeFisier, ios::in | ios::binary);
		if (this->contacte != NULL)
		{
			delete[] this->contacte;
		}
		
		//citire in binar pentru numerice(int,float,double,bool)
		file.read((char*)&this->nrContacte, sizeof(int));
		this->contacte = new Contact*[this->nrContacte];
		//citire in binar pentru numerice*
		for (int i = 0; i < this->nrContacte; i++)
		{
			this->contacte[i] = new Contact();
			file.read((char*)&*this->contacte[i], sizeof(*contacte[i]));
		}

	}
};
//functie template
template<class T>
bool compNrApeluri(T a, T b) {
	return a > b;
}
template<class T>
bool compDurataApeluri(T a, T b) {
	return a < b;
}
//clasa template
template <typename T>
class Gestiune
{
private:
	int nr;
	T* vector;
public:

	Gestiune(int nr, T* vector)// te gandesti la T* ca la int*
	{
		this->nr = nr;
		this->vector = new T[this->nr];

		for (int i = 0; i < this->nr; i++)
		{
			this->vector[i] = vector[i];
		}
	}
	~Gestiune()
	{
		if (this->vector)
			delete[]this->vector;
	}

	T* getVector()
	{
		return this->vector;
	}

	int getNumar()
	{
		return this->nr;
	}
	Gestiune &operator+=(const T &element) 
	{
		
		T*copie = new T[this->nr];
		for (int i = 0; i < this->nr; i++) {
			copie[i] = this->vector[i];
		}
		if (this->vector != NULL) {
			delete[]this->vector;
		}
		this->nr++;
		vector= new T[this->nr];
		for (int i = 0; i < this->nr-1; i++) {
			this->vector[i] = copie[i];
		}
		vector[this->nr-1] = element;
		return *this;
	}
		
	void adaugaElement(const T& element)
	{
		(*this) += element;
	}

};

int main()
{
	Contact c;
	int durata[] = { 8,9,110 };
	int durata1[] = { 2227,6,7 };
	int durata2[] = { 1135,5,25 };
	Contact c1("George Mihai", "ghemih@gmail.com","+400723000782", 3, durata);
	Contact c2("Viorel Toader", "vioTeo@gmail.com", "0726666542", 2, durata1);
	Contact c3("Gianina Iordache", "gianinaI@gmail.com", "0726881234", 1, durata2);
	Contact c4 = c3;
	c = c4;
	/*cout << c << endl;
	cout << "----------------------------" << endl;
	cout << c1 << endl;
	cout << "----------------------------" << endl;
	cout << c2 << endl;
	cout << "----------------------------" << endl;
	cout << c3 << endl;
	cout << "----------------------------" << endl;
	cout << c4 << endl;
	cout << "----------------------------" << endl;*/
	
	
	Contact** agendaTlfvect = new Contact * [5];
	agendaTlfvect[0] = &c;
	agendaTlfvect[1] = &c1;
	agendaTlfvect[2] = &c2;
	agendaTlfvect[3] = &c3;
	agendaTlfvect[4] = &c4;

	AgendaTelefonica agendaTlf(5, agendaTlfvect);
	int optiune;

	do
	{
		cout << "|||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
		cout << "Meniu:" << endl;
		cout << "1.Introduce numar de telefon in agenda." << endl;
		cout << "2.Cauta Contact dupa nume." << endl;
		cout << "3.Cauta Contact dupa numarul de telefon." << endl;
		cout << "4.Afiseaza toate contactele(doar numele si numarul de telefon)." << endl;
		cout << "5.Afiseaza toate contactele(incluzand apelurile)." << endl;
		cout << "6.Creati raport text cu toate contactele." << endl;
		cout << "7.Creati raport binar cu toate contactele." << endl;
		cout << "8.Sortati contactele dupa numarul de apeluri. " << endl;
		cout << "9.Sortati contactele dupa durata apelurilor. " << endl;
		cout << "10.Iesire din meniu. " << endl;
		cout << "|||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
		cout << endl;
		
		cout << "Va rugam selectati optiune: ";
		cin >> optiune;
		system("cls");
		if (optiune == 1)
		{
			
			Contact cAjut;
			cin >> cAjut;

			agendaTlf.adaugaContact(cAjut);
			cout << "Doriti sa efectuati alta operatiune?"<<endl;
			int val;
			cout << "1.Da" << endl;
			cout << "2.Nu" << endl;
			cout << "Introduceti cifra corespunzatoare: ";
			cin >> val;
		
			if (val == 1)
			{
				system("cls");
			}
			else
			{
				cout << "Compania DM Mobile va ureaza Sarbatori Fericite!" << endl;
				break;
			}
		}
	
	
		else if (optiune == 2)
		{

			string numePers;
			cout << "Va rugam sa introduceti numele persoanei: ";
			cin >> numePers;
			int nr = 0;
			for (int i = 0; i < agendaTlf.getNrContacte(); i++)
			{

				string numeCautat = agendaTlf.getContacte()[i]->getNume();
				if (strstr(strUp(numeCautat).c_str(), strUp(numePers).c_str()))
				{
					nr++;
					cout << agendaTlf.getContacte()[i]->getNume() << " - " << agendaTlf.getContacte()[i]->getNrTelefon() << endl;
					cout << "-----------------------------------" << endl;
					//agendaTlf -= agendaTlf.getContacte()[i]; -- ca sa eliminam

				}

			}
			if (nr == 0)
			{
				cout << "Nu am gasit niciun rezultat!" << endl;
			}
			cout << "Doriti sa efectuati alta operatiune?" << endl;
			int val;
			cout << "1.Da" << endl;
			cout << "2.Nu" << endl;
			cout << "Introduceti cifra corespunzatoare: ";
			cin >> val;

			if (val == 1)
			{
				system("cls");
			}
			else
			{
				cout << "Compania DM Mobile va ureaza Sarbatori Fericite!" << endl;
				break;
			}
		}
		

		else if (optiune == 3)
		{
		cout << "Va rugam sa introduceti numarul de telefon al persoanei: ";
		string nrTelefon;
		cin >> nrTelefon;
		for (int i = 0; i < agendaTlf.getNrContacte(); i++)
		{
			string cautat = agendaTlf.getContacte()[i]->getNrTelefon();
			if (strstr(strUp(cautat).c_str(), strUp(nrTelefon).c_str()))
			{
				cout << agendaTlf.getContacte()[i]->getNume() << " - " << agendaTlf.getContacte()[i]->getNrTelefon() << endl;
				cout << "-----------------------------------" << endl;
			}
			else
			{
				cout << "Nu am gasit niciun rezultat!" << endl;
			}
		}
			cout << "Doriti sa efectuati alta operatiune?" << endl;
			int val;
			cout << "1.Da" << endl;
			cout << "2.Nu" << endl;
			cout << "Introduceti cifra corespunzatoare: ";
			cin >> val;

			if (val == 1)
			{
				system("cls");
			}
			else
			{
				cout << "Compania DM Mobile va ureaza Sarbatori Fericite!" << endl;
				break;
			}
		}
		else if (optiune == 4)
		{
			for (int i = 0; i < agendaTlf.getNrContacte(); i++)
			{
				cout << agendaTlf.getContacte()[i]->getNume() << " - " << agendaTlf.getContacte()[i]->getNrTelefon() << endl;
			}
			cout << "Doriti sa efectuati alta operatiune?" << endl;
			int val;
			cout << "1.Da" << endl;
			cout << "2.Nu" << endl;
			cout << "Introduceti cifra corespunzatoare: ";
			cin >> val;

			if (val == 1)
			{
				system("cls");
			}
			else
			{
				cout << "Compania DM Mobile va ureaza Sarbatori Fericite!" << endl;
				break;
			}
		}
		else if (optiune == 5)
		{
			cout << agendaTlf << endl;
			cout << "Doriti sa efectuati alta operatiune?" << endl;
			int val;
			cout << "1.Da" << endl;
			cout << "2.Nu" << endl;
			cout << "Introduceti cifra corespunzatoare: ";
			cin >> val;

			if (val == 1)
			{
				system("cls");
			}
			else
			{
				cout << "Compania DM Mobile va ureaza Sarbatori Fericite!" << endl;
				break;
			}
		}
		else if (optiune == 6)
		{
			
			ofstream f("agenda.txt");
			f << agendaTlf;
			f.close();
			cout << "Doriti sa efectuati alta operatiune?" << endl;
			int val;
			cout << "1.Da" << endl;
			cout << "2.Nu" << endl;
			cout << "Introduceti cifra corespunzatoare: ";
			cin >> val;

			if (val == 1)
			{
				system("cls");
			}
			else
			{
				cout << "Compania DM Mobile va ureaza Sarbatori Fericite!" << endl;
				break;
			}
		}
		else if (optiune == 7)
		{
			agendaTlf.serializare("agendaTelefonica.bin");
			AgendaTelefonica ag1;
			ag1.deserializare("agendaTelefonica.bin");
			cout << ag1 << endl;
			cout << "Doriti sa efectuati alta operatiune?" << endl;
			int val;
			cout << "1.Da" << endl;
			cout << "2.Nu" << endl;
			cout << "Introduceti cifra corespunzatoare: ";
			cin >> val;

			if (val == 1)
			{
				system("cls");
			}
			else
			{
				cout << "Compania DM Mobile va ureaza Sarbatori Fericite!" << endl;
				break;
			}
		}
		else if (optiune == 8)
		{
			vector<Contact> vectorContact;
			for (int i = 0; i < agendaTlf.getNrContacte(); i++)
			{
				vectorContact.push_back(*agendaTlf.getContacte()[i]);
			}
			sort(vectorContact.begin(), vectorContact.end(), compNrApeluri<Contact>);
			for (int i = 0; i < vectorContact.size(); i++)
			{
				cout << vectorContact[i] << endl;
			}
			cout << "Doriti sa efectuati alta operatiune?" << endl;
			int val;
			cout << "1.Da" << endl;
			cout << "2.Nu" << endl;
			cout << "Introduceti cifra corespunzatoare: ";
			cin >> val;

			if (val == 1)
			{
				system("cls");
			}
			else
			{
				cout << "Compania DM Mobile va ureaza Sarbatori Fericite!" << endl;
				break;
			}
		}
		else if (optiune == 9)
		{
			vector<Contact> vectorContact1;
			for (int i = 0; i < agendaTlf.getNrContacte(); i++)
			{
				vectorContact1.push_back(*agendaTlf.getContacte()[i]);
			}
			sort(vectorContact1.begin(), vectorContact1.end(), compDurataApeluri<Contact>);
			for (int i = 0; i < vectorContact1.size(); i++)
			{
				cout << vectorContact1[i] << endl;
			}
			cout << "Doriti sa efectuati alta operatiune?" << endl;
			int val;
			cout << "1.Da" << endl;
			cout << "2.Nu" << endl;
			cout << "Introduceti cifra corespunzatoare: ";
			cin >> val;

			if (val == 1)
			{
				system("cls");
			}
			else
			{
				cout << "Compania DM Mobile va ureaza Sarbatori Fericite!" << endl;
				break;
			}
		}
		if (optiune == 10)
		{
		cout << "Compania DM Mobile va ureaza Sarbatori Fericite!" << endl;
		break;
		}
	}while(optiune >=1 && optiune <=10);
	/*
	cout << c1.contactStrainatate() << endl;
	if (c1.contactStrainatate())
	{
		cout << "Numarul de telefon este din afara Romaniei!" << endl;
	}
	else
	{
		cout << "Numarul de telefon este de pe teritoriul Romaniei!" << endl;
	}
	ContactMunca cm1("George Mihai", "+400723000782", 3, durata, "Bringo", "400723000782");
	cout<<cm1 << endl;
	AgendaTelefonica a1(4, agendaTlf);
	cout << a1 << endl;
	Contact c7("Catalin  ALin Cristea", "+40723344221");
	a1 += c7;
	a1 += c1;
	cout << a1 << endl;
	a1 -= c1;
	cout << a1 << endl;
	cout << "\n\n-----------------------TEMPLATE-----------------------------\n\n";
	Contact* contactVect = new Contact [5];
	contactVect[0] = c;
	contactVect[1] = c1;
	contactVect[2] = c2;
	contactVect[3] = c3;
	contactVect[4] = c4;
	Gestiune <Contact> gestContact(5,contactVect);
	gestContact.adaugaElement(c7);
	for (int i = 0; i < gestContact.getNumar(); i++)
	{
		cout << gestContact.getVector()[i] << endl;
	}
	cout << "\n\n---------------------------STL-------------------------\n\n";
	vector<Contact> vectorContact;
	vectorContact.push_back(c);
	vectorContact.push_back(c1);
	vectorContact.push_back(c2);
	vectorContact.push_back(c3);
	vectorContact.push_back(c4);
	vectorContact.push_back(c7);
	for (int i = 0; i < vectorContact.size(); i++)
	{
		cout << vectorContact[i] << endl;
	}
	sort(vectorContact.begin(), vectorContact.end(), compNrApeluri<Contact>);
	cout << "\n\n--------------------------DUPA NR APELURI--------------------------\n\n";
	for (int i = 0; i < vectorContact.size(); i++)
	{
		cout << vectorContact[i] << endl;
	}
	cout << "\n\n--------------------------DUPA DURATA APELURI APELURI--------------------------\n\n";
	sort(vectorContact.begin(), vectorContact.end(), compDurataApeluri<Contact>);
	for (int i = 0; i < vectorContact.size(); i++)
	{
		cout << vectorContact[i] << endl;
	}
	cout << "\n\n--------------------------FISIERE BINARE--------------------------\n\n";
	c2.serializare("contact.bin");
	cm1.serializare("contactMunca.bin");
	ContactMunca cm2;
	Contact c22;
	c22.deserializare("contact.bin");
	cm2.deserializare("contactMunca.bin");
	cout << c22 << endl << endl;
	cout << cm2 << endl << endl;
	string numeDeSetat;
	do
	{
		cout << "Introduceti numele de setat: "; 
		cin >> numeDeSetat;
		try
		{
			c2.setNume(numeDeSetat);
			cout << "Numele din agenda a fost modificat!" << endl;
		}
		catch ( ExceptieAfisare  ex)
		{
			cout << ex.getMesaj() << endl;
		}
	} while (numeDeSetat.size() < 3);
	string numarDeSetat;
	do
	{
		cout << "Introduceti numarul de telefon din 10 cifre(13 daca puneti si prefixul tarii): ";
		cin >> numarDeSetat;
		try
		{
			c2.setNrTelefon(numarDeSetat);
			cout << "Numele din agenda a fost modificat!" << endl;
		}
		catch (ExceptieAfisare  ex)
		{
			cout << ex.getMesaj() << endl;
		}
	} while (numarDeSetat.size() != 13 && numarDeSetat.size() != 10 && numarDeSetat.size() != 12);*/
	
}