#include<iostream>
#include<cstdlib>
#include<typeinfo>

using namespace std;

class A {
	private:
		string s;
	public:
		A(string s) {
			this->s = s;
		}
		string getS() {
			return s;
		}

		virtual bool lunga() {
			return s.length()>3;
		}

		virtual string estrai() = 0;

		virtual string classname() const {
			return "A";
		}

		virtual ostream& put(ostream &stream) const {
			stream << "Class "<<classname() << " s=\"" << s <<"\"";
			return stream;
		}
};

ostream& operator<<(ostream& stream, const A &a) {
	return a.put(stream);
}

class B : public A {
	private:
		int y;
	public:
		B(string s, int y) : A(s) {
			this->y = y;
		}

		bool lunga() {
			return getS().length()>y;
		}

		string estrai() {
			int l = y-5;
			string out = "";
			for(int i=0; i<l; i++)
				out+="*";
			return out;
		}
		
		virtual string classname() const {
			return "B";
		}
		
		virtual ostream& put(ostream &stream) const {
			A::put(stream);
			stream << " y="<<y;
			return stream;
		}
};

class C : public A {
	private:
		char c;
	public:
		C(string s, char c) : A(s) {
			this->c = c;
		}

		string estrai(short x) {
			string s = getS();
			if (x<s.length())
				return s.substr(x,x+1);
			else
				return s.substr(s.length()-3);
		}

		virtual string classname() const {
			return "C";
		}
		
		virtual ostream& put(ostream &stream) const {
			A::put(stream);
			stream << " c='"<<c<<"'";
			return stream;
		}
};

class D : public C {
	private:
		int z;
	public:
		D(string s, char c, int z) : C(s,c) {
			this->z=z;
		}

		string estrai() {
			string s = getS();
			if(z<s.length())
				return s.substr(z,z+1);
			else
				return s.substr(0,2);
		}
		
		virtual string classname() const {
			return "D";
		}
		
		virtual ostream& put(ostream &stream) const {
			C::put(stream);
			stream << " z="<<z<<"";
			return stream;
		}
};

int main() {
	const int DIM = 30;
	A* vett[DIM];
	int lunghi = 0;
	string str1 = "";
	string str2 = "";
	
	srand(111222333);
	for(int i=0; i<DIM; i++){
		int p = rand()%10+3;
		string str = "";
		for (int j=0; j<p; j++) str+=(char) ('A' + rand()%26);
		int a = rand()%15;
		if (rand()%2==1)
			vett[i] = new D(str, (char)('A'+rand()%26),a);
		else
			vett[i] = new B(str,a);
	}

	for (int i=0; i<DIM; i++) {
		cout << *vett[i] << endl;
		if(vett[i]->lunga())
			lunghi++;

		str1 += vett[i]->estrai();

		if(typeid(*vett[i])==typeid(D))
			str2+=((C*)vett[i])->estrai(4);
	}

	cout << "Punto 1: lunghi="<<lunghi<<" estrai=\""<<str1<<"\""<<endl;
	cout << "Punto 2: estrai(4)=\""<<str2<<"\""<<endl;
}
