#include <iostream>
// const int  可以到 int 不能到 int& , 在参数传递中   // 
using namespace std;

int global (int& num){
	num = num + 2;	
}

class Int{
public :
		Int (int i) :i_(i){
			cout << "Int 's constructor Int(int i)" << endl;	
		}

		Int () {
			cout << "Int 's constructor Int()" << endl;	
		}

		int i (){
			return i_;	
		}

private :
		int i_;
};

class WY{
public :
		WY (int num) : num_(num) {
			cout << "WY's constructor WY(int num)" << endl;	
		}
		
		WY (Int& in) : in_(in) {
			cout << "WY's constructor WY(Int& in)" << endl;
			num_ = in.i();	
		}

		int get() const{
			cout << "int get() const" << endl;
			Int in(num_);
			WY w(in_);
			w.num_ = 7;
			global(num_);
			return num_;
		}

private :
		mutable int num_;
		mutable Int in_;
};


int main (){
	WY wy(5);
	int t = wy.get();
	cout << "t = " << t << endl;	
}
