#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
// Base class doctor
class doctor
{
protected:
	string firstname; // firstname
	string lastname; // lastname
	int thesis; // thesis quantity
public:
	doctor(string = "justname", string = "justlastname", int = 2010);
	~doctor();
	void printinfo()const;
};
// Second base class Researcher
class Researcher
{
protected:
	int publications; // publications quantity
	int projects; // projects quantity
public:
	Researcher(int = 25, int = 23);
	~Researcher();
	void printinfo()const;
};
// Derived class Lecturer
class Lecturer :public doctor, public Researcher
{
private:
	string highSchool; // highSchool
	int courses; // courses quantity
public:
	Lecturer(string = "justname", string = "justlastname", int = 2010, int = 25, int = 23, string = "just hightschool", int = 75);
	~Lecturer();
	Lecturer(istream&);
	friend ostream& operator << (ostream&, const Lecturer&);
	friend istream& operator >> (istream&, Lecturer&);
	bool operator < (const Lecturer&);
	void printinfo(ostream&)const;
};
// Doctor class implementation
doctor::doctor(string a, string b, int c) : firstname(a), lastname(b), thesis(c) {}
doctor::~doctor() = default;
void doctor::printinfo()const
{
	cout << "First name is: " << firstname << ", last name is: " << lastname
		<< " and the year thesis was written: " << thesis << endl;
}
// Researcher class implementation
Researcher::Researcher(int d, int e) : publications(d), projects(e) {}
Researcher ::~Researcher() = default;
void Researcher::printinfo()const
{
	cout << "Publications cunatity is: " << publications << " and projects cunatity is: " << projects << endl;
}
// Lecturer class implementation
Lecturer::Lecturer(string a, string b, int c, int d, int e, string f, int g) :
	doctor(a, b, c), Researcher(d, e), highSchool(f), courses(g) {}
Lecturer::~Lecturer() = default;
Lecturer::Lecturer(istream & in)
{
	in >> firstname >> lastname >> thesis >> publications >> projects >> highSchool >> courses;
}
void Lecturer::printinfo(ostream & out = cout)const
{
	cout << "First name is: " << firstname << ", last name is: " << lastname
		<< "the year thesis was written: " << thesis << ", Publications cunatity is: "
		<< publications << ", projects cunatity is: " << projects << ", High school name is: "
		<< highSchool << " and courses cuantity is: " << courses << endl;
}
ostream& operator << (ostream & out, const Lecturer & x)
{
	cout << "Enter school name and course cunatity: " << endl;
	return out << x.highSchool << x.courses;
}
istream& operator >> (istream & in, Lecturer & x)
{
	return in >> x.highSchool >> x.courses;
}
bool Lecturer::operator < (const Lecturer & x)
{
	return this->publications > x.publications;
}
// Data fills from file
int fill(Lecturer * F)
{
	ifstream ifs("teachers.txt");
	int i = 0;
	while (!ifs.eof())
	{
		Lecturer L(ifs);
		F[i++] = L;
	}
	return i; // returns data quantity from file
}
// print function
void print(Lecturer * x, int& size)
{
	cout << "\nSorted by Decreasing publications:\n\n\n";
	for (int i = 0; i < size; i++)
	{
		x[i].printinfo();
	}
}
int main()
{
	static doctor A;
	static Researcher B;
	cout << "Doctor info: " << endl;
	A.printinfo();
	cout << "\nScientist info: " << endl;
	B.printinfo();
	int cunatity = 800;
	Lecturer* array = new(nothrow) Lecturer[cunatity]; // Creating a dynamic array
	int size = fill(array);
	sort(array, array + size);
	print(array, size);
	delete[] array; // Deleting a dynamic array
	array = nullptr;
}