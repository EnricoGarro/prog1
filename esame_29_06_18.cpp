#include <string>
#include <iostream>
#include <cctype>
#include <cstdlib>
#include <sstream>
#include <climits>
#include <typeinfo>
#include <cmath>

using namespace std;

class A{
    private:
        int* p;
        short l;
        float y;
    public:
        A(short i1,short i2){
            this->l=i1+i2;
            this->p=new int[l];
			
			short a=(i1<i2 ? i1:i2);
			short b=(i1<i2 ? i2:i1);

			
            for(int i=0;i<l;i++){
                p[i]=rand() %(b-a+1)+a;
            }
           y=log((i1+i2)/2);
        }
        virtual float f(short i,float x)=0;
        
		ostream & put(ostream &stream)const{
      		return stream << "Class " << typeid(*this).name() << ": p=[" << p<< "]: l=" << l<<" , y="<<y;
		}
		
    protected:
        int val (short j){
            for(int i=0;i<this->l;i++)
                if(p[i]==j)
                    return p[j];
                else
                    return p[(rand()%(this->l - 0))+0];
        }
};

class B:public A{
    private:
        string str;
    public:
        B(string w,short a, short b): A(a,b){
            str="";
            for(int i=0;i<w.length();i++){
                if(w[i]=='a'||w[i]=='e'||w[i]=='i'||w[i]=='o'||w[i]=='u')
                    str+=w[i];
            }
        }
         float f(short i,float x){return sin((float)val(i))*x;}
         
         virtual ostream & put(ostream &stream)const{
      		return A::put(stream)<< " {str=" << str<<"}";
		 }
};

class C:public A{
    private:
        float m;
    public:
        C(float z):A((int)z+0.5,(int)(z+0.5)*5){
            m=val(2*((int)(z*0.5)))/2;
        }
         float f(short i,float x){
             if(i%2==0)
                 if(i!=0)
                     return sin(val(i)*x);
                 else
                     return x;
                
        }
        float g(){return log(m);}
        virtual ostream & put(ostream &stream)const{
      		return A::put(stream)<< " {m=" << m<<"}";
		}
};

ostream& operator <<(ostream& stream, const A& a){
    return a.put(stream);
}
int main(){
    const int DIM=30;
      srand(111222333);
  A *vett[DIM];

  string w;
  short s1, s2;

  for(int i=0; i<DIM; i++){
        if(rand()%2==0){ //B
            w = "";
            s1 = rand()%20 + 5;
            s2 = rand()%20 + 5;
            short len = rand()%50 + 10;
            for(int j=0; j<len; j++)
                w+=((rand()%2) ? (char) (rand()%26 + 'a') : (char) (rand()%10 + '0'));
                vett[i] = new B(w, s1, s2);
    }
    else{ // C
            int max = 10;
            float z = ((float) rand())/INT_MAX * (rand()%max) + 1.0;
            vett[i] = new C(z);
   }
 }
   
}
