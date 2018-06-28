#include<iostream>
#include<cmath>
#include<sstream>
#include<cstdlib>
#include<climits>
#include<typeinfo>

using namespace std;

class C{
	private:
		float x;
	public:
		C(float x): x(x){}
		virtual double f()=0;
		float getX(){return x;}
		virtual ostream& out(ostream& os)const{
			return os<<":["<<x;
		}
};

class D:public C{
	private:
		char c;
	public:
		D(float x):C(x){
		c=(char)('a' + (int)(x*1000000000) % 20);
		}
		double f(){return sin(getX())*sin(getX());}
		char getC(){return c;}
		
		virtual ostream& out(ostream& os)const{
			return C::out(os)<<" c= "<<c<<"] ";
		}
};

class E:public C{
	private:
		int n;
	public:
		E(float x):C(x){n= (int)(x*1000000000)%10; }
		double f(){return cos(getX())*cos(getX());}
		char getN(){return n;}
		
		virtual ostream& out(ostream& os)const{
			return C::out(os)<<" n= "<<n<<"] ";
		}
};

ostream& operator << (ostream& stream, const C &z){
	return z.out(stream);
}

class A{
	protected:
		C* obj1;
		C* obj2;
	public:
		A(float x){
			obj1=new D(x);
			obj2=new E(x);
			
		}
		double g() const{
			return obj1->f()+obj2->f();
		}
		virtual ostream& out(ostream& stream)const{
			return stream<<"class "<<typeid(*this).name() <<*obj1<<"--"<<*obj2<<"\t g()= "<<g();
		}
};

class B: public A{
	public:
		B(float x):A(x){}
		string st() const{
			string s="";
			for	(int i=0; i<((E*)obj2)->getN(); i++)
             s+= ((D*)obj1)->getC();
             return s;	
		}
		ostream& out(ostream& stream)const{
			return A::out(stream)<<"\t st()= "<<B::st();
		}
};

ostream& operator << (ostream& stream, const A &a){
	return a.out(stream);
}

int main(){
	const int DIM=50;
	
	srand(328832748);
   	
	A * vett [DIM];
 		
   	for (int i=0; i<DIM; i++) {
	  if ( rand()%2 == 1 )    vett[i] = new A((float)rand()/INT_MAX);
				     else     vett[i] = new B((float)rand()/INT_MAX);
						
      cout << i << ") \t" << *(vett[i])<< endl << endl;
   	}	
}
