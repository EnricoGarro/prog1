#include<iostream>
#include<cstdlib>
#include<typeinfo>
#include<cmath>
#include<sstream>
#include <climits>

using namespace std;

class A {
	private:
		string w;
	public:
		A(string s):w(s) {}
		int getSum() {
			int accumulatore = 1;
			for (unsigned int i=0;  i<w.length(); i++) {
				if(w[i]=='a' || w[i]=='e' || w[i]=='i' || w[i]=='o' || w[i]=='u' ||
				   w[i]=='A' || w[i]=='E' || w[i]=='I' || w[i]=='O' || w[i]=='U')
					accumulatore += (int) (w[i]);
			}
			return accumulatore;
		}

		virtual float* values() = 0;

		virtual ostream &put(ostream &stream) const{
		  return stream << "Class "<<typeid(*this).name()<<" w=\""<<this->w<<"\"";
		}
};

ostream & operator<<(ostream &stream, const A &a){
  return a.put(stream);
}

class B : public A {
	private:
		string s;
		int l;
	public:
		B(string s1, string s2, short n) : A(s1.substr(s1.length()-n)+s2.substr(0,s2.length()-n)){
			this->s="";
			for(unsigned int i=0; i<s1.length() && i<s2.length();i++){
			  this->s+=toupper(s2[i]);
			  this->s+=tolower(s1[i]);
			}
			//cout << "L(w)=" << getS().length() << ", n=" << n << endl;
			this->l = this->s.length();
		}

		float *values(){
			float *out = new float[l];
			for(int i=0; i<l; i++){
			  out[i] = ((int)s[i])/(float)getSum();
			 // cout << out[i] << ", " << endl;
			}
			return out;
		}

		double res(){
			float *array = values();
			double ret = 0;
			for (int i=0; i<l; i++)
			  ret+=pow((double) array[i],2.0);
			return sqrt(ret);
		}

		ostream& put(ostream &stream) const{
			return A::put(stream) << " s=\""<<s<<"\"" << ", l=" << l;
		}
};

class C : public A {
	private:
		string t;
		int len;
	public:
		C(string s, int n, int k): A(s.substr(0,n-1)+s.substr(s.length()-k)){
			this->t = "";
			for(unsigned int i=0; i<s.length(); i++)
				if(tolower(s[i])==s[i])
				  this->t+=toupper(s[i]);
				else
				  this->t+=tolower(s[i]);
			this->len=t.length();
		}

		float *values() {
			float *out = new float[this->len];
			for(int i=0; i<this->len;i++){
			  out[i]=sin(((float) getSum())/len*(i+1));
			}
			return out;
		}

		short moreThan05() {
			float *array = values();
			int count=0;
			for (int i=0; i<len; i++)
				if (array[i]>=0.5)
					count++;
			return count;
		}
		
		ostream& put(ostream &stream)  const {
			return A::put(stream) << " t=\""<<t<<"\"" << ", len=" << len;
		}
};


int main() {
	
	const int DIM = 30;
	A *vett[DIM];

	srand(111222333);

	for(int i=0; i<DIM; i++){
			string str1 = ""; string str2 = "";
			if(rand()%2==0){
			  short l1 = rand()%5+3; short l2 = rand()%5+6;
			  for(int j=0; j<l1; j++)
			    str1+=((char) ('a' + rand()%25));
			  for(int j=0; j<l2; j++)
			    str2+=((char) ('a' + rand()%25));
			  short n = rand()%3+1;
			  vett[i] = new B(str1, str2, n);
			}
			else {
			  for(int j=0; j<10; j++){
			    int r = rand(); 
			    if(r%2==0)
			      str1+=((char) ('0' + rand()%9));
			    else if(r%3==0)
			      str1+=((char) ('a' + rand()%25));
			    else
			      str1+=((char) ('A' + rand()%25));
			  }
			  vett[i] = new C(str1, rand()%3+1, rand()%6+1); 
			}		      
  	}

	for(int i=0; i<DIM; i++){
	  cout << i << ")" << *vett[i] << ", getSum()=" << vett[i]->getSum() << endl;
	  if(typeid(*vett[i])==typeid(B))
	    cout << "\t res()=" << ((B*)vett[i])->res() << endl;
	  else	    
	    cout << "\t moreThan05()=" << ((C*)vett[i])->moreThan05() << endl;
	}


	cout << endl<<"Punto I (res(): 9 and 17): " << ((B*)vett[9])->res()+((B*)vett[16])->res()<<endl;

	cout << "Punto II (i: moreThan05()>=5): "; 
	for(int i=0; i<DIM; i++)
	  if(typeid(*vett[i])==typeid(C) && ((C*)vett[i])->moreThan05()>=5)
	    cout << i <<" ";
	cout << endl;

	cout << "Punto III (getSum() min, max, avg):"; 
	int min=INT_MAX;
	int max=-1;
	int c=0;
	float avg=0.0;
	for(int i=0; i<DIM; i++)
	  if(typeid(*vett[i])==typeid(B)){
	    min=(min<vett[i]->getSum() ? min : vett[i]->getSum());
	    max=(max>vett[i]->getSum() ? max : vett[i]->getSum());
	    avg+=vett[i]->getSum();
	    c++;
	  }

	cout << "min=" << min << ", max=" << max << ", avg=" << (avg/c) << endl;
}
