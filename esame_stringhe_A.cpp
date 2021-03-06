#include <string>
#include <iostream>
#include <cctype>
#include <cstdlib>
#include <sstream>
#include <climits>
#include <typeinfo>


using namespace std;

class A{
  private: 
    string w;
  
  public:
    A(string s):w(s){};

    int getSum(){
      int sum = 1;
      int c;
      int mark[w.length()];

      for(unsigned int i=0; i<w.length()-1; i++)
		mark[i]=0;

      for(unsigned int i=0; i<w.length()-1; i++){
		if(mark[i]==0){
	  mark[i]=1;
	  c=0;
	  for(unsigned int j=i+1; j<w.length(); j++)
	    if(w[i]==w[j]){
	      mark[j]=1;
	      c++; 
	    }
	  if(c>0)
	    sum+=(int) w[i]; 
	}
      }
      return sum;
    }
    
    virtual int *values()= 0;

    virtual ostream &put(ostream &os) const{
      return os << "Class " << typeid(*this).name() << ": w=" << w;
      }

    };

    ostream &operator << (ostream &left, const A &obj){
      return obj.put(left);
    }

class B: public A{
    private:
      string s;
      int l;
    public:
 
    B(string s1, string s2, short n): A(s1.substr(0,n)+s2.substr(n)){
      unsigned int i=0;
      s="";
      while(i<s1.length() && i<s2.length()){
	s+=s1[i];
	s+=s2[i];
	i++; 
      }

      this->l=s.length();
    }

    int *values() {
      int *ret=new int[this->l];
      for(int i=0; i<this->l; i++)
	ret[i] = ((int) s[i]) % 10;
      return ret;
    }

    float res() {
      int *v = values();
      int sum = 0;
      for(int i=0; i<this->l; i++)
	sum+= v[i];
      return (float) sum/getSum();
    }

    ostream &put(ostream &os) const{
      return A::put(os) << "{ s=" << s << ", l=" << l << "}"; 
    }
};

class C: public A{
    private:
      string t;
      int n;
 
    public: 
    C(string s): A(s){
      t="";
      for(unsigned int i=0; i<s.length(); i++){
	if(tolower(s[i])==s[i])
	  t+=toupper(s[i]);
	else
	  t+=tolower(s[i]);
      this->n = (this->t).length();     
      }
    }

    int *values(){
      int *ret=new int[this->n];
      for(int i=0; i<this->n; i++){
	if(((int) this->t[i]) >= '0' && ((int)this->t[i]) <='9')
	  ret[i] = 0;
	else
	  ret[i] = 1;
      }
      return ret;
    }

    short zeros(){
      int *v = values();
      short cum = 0;
      for(int i=0; i<this->n; i++)
	if(v[i]==0)
	  cum++;
      return cum;
    }
   
    ostream &put(ostream &os) const{
      return A::put(os) << "{ t=" << t << ", n=" << n << "}";
    }         
};

int main(){
  const int DIM = 30;
  srand(111222333);
  A *vett[DIM];
    
  for(int i=0; i<DIM; i++){
    string str1 = ""; string str2 = "";
    if(rand()%2==0){
      short l1 = rand()%5+3; short l2 = rand()%5+6;
      for(int j=0; j<l1; j++)
	str1+=((char) ('a' + rand()%25));
      for(int j=0; j<l2; j++)
	str2+=((char) ('a' + rand()%25));
      short n = rand()%3+1;
      //cout << "i=" << i << ", Str1: " << str1 << ", Str2: " << str2 <<  ", n=" << n <<", new B()"<< endl << flush;
      vett[i] = new B(str1, str2, n);
    }
    else{      
      for(int j=0; j<10; j++){
	  int r = rand(); 
	  if(r%2==0)
	      str1+=((char) ('0' + rand()%9));
	  else if(r%3==0)
	      str1+=((char) ('a' + rand()%25));
	  else
	      str1+=((char) ('A' + rand()%25));
      }
      vett[i] = new C(str1);
    }
  }

  for(int i=0; i<DIM; i++){      
      cout << i << ")" << *vett[i] << ", getSum()=" << vett[i]->getSum() << endl;
      if(typeid(*vett[i])==typeid(B))
	cout << "\t res()=" << ((B*) vett[i])->res() << endl;
      else
	cout << "\t zeros()=" << ((C*) vett[i])->zeros() << endl;
  }

  cout << endl << "Punto I (res(), (0)+(17)):" << ((B*) vett[0])->res() + ((B*)vett[17])->res() << endl;

  cout << endl << "Punto II:"; 
  for(int i=0; i<DIM; i++)
    if(typeid(*vett[i])==typeid(C) && ((C*) vett[i])->zeros()>=7)
      cout << i << " "; 
  cout << endl;

  cout << endl << "Punto III:"; 
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

  cout << " min=" << min << ", max=" << max << ", avg=" << (avg/c) << endl;
}

