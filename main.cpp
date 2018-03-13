#include<iostream> /// cin, cout
#include<iomanip> /// setw
#include<fstream> /// ifstream, ofstream
#include<cassert> /// assert
#include<algorithm> /// sort
using namespace std;

ifstream in("data.in");

const bool SUPPRESS_LOGS = 1;
const bool SUPPRESS_LOGS_SOFT = 1;

class complexNumber{
    private:
    protected:

    public:
        double x,y;

        complexNumber(double x, double y){
            this->x = x;
            this->y = y;
        }

        complexNumber(){
        }

        ~complexNumber(){
            if(!SUPPRESS_LOGS && !SUPPRESS_LOGS_SOFT)
                cout<<"Destructing!\n";
        }

        complexNumber operator=(complexNumber other){
            this->x = other.x;
            this->y = other.y;
        }

        bool operator==(complexNumber other){
            return (this->x == other.x) && (this->y == other.y);
        }
        bool operator!=(complexNumber other){
            return !(*this == other);
        }

        complexNumber operator+(complexNumber other){
            complexNumber res;
            res.x = this->x + other.x;
            res.y = this->y + other.y;

            return res;
        }

        complexNumber operator-(complexNumber other){
            complexNumber res;
            res.x = this->x - other.x;
            res.y = this->y - other.y;

            return res;
        }

        complexNumber operator*(complexNumber other){
            complexNumber res;
            res.x = this->x * other.x;
            res.y = this->y * other.y;

            return res;
        }

        complexNumber operator/(complexNumber other){
            if(other.x == 0 || other.y == 0)
                throw overflow_error("Cannot divide by 0.");
            complexNumber res;
                res.x = this->x / other.x;
                res.y = this->y / other.y;

                return res;

            /*try{
                if(other.x == 0 || other.y == 0)
                    throw overflow_error("Cannot divide by 0.");

                complexNumber res;
                res.x = this->x / other.x;
                res.y = this->y / other.y;

                return res;
            }
            catch (overflow_error e){
                cout<<"Exception caught: "<<e.what()<<"\n";
            }*/
        }

        bool operator<(complexNumber other){ /// Sort by 'x' (the first number)
            return this->x < other.x;
        }

        void print(){
            //cout<<"Number = "<<setw(3)<<this->x<<" + "<<setw(3)<<this->y<<"i\n";
            cout<<"Number = "<<this->x<<" + "<<this->y<<"i\n";
        }
};

istream& operator>>(istream& in, complexNumber& nr){
    in>>nr.x>>nr.y;
}

ostream& operator<<(ostream& out, complexNumber nr){
    out<<nr.x<<" "<<nr.y<<"\n";
}

ifstream& operator>>(ifstream& in, complexNumber& nr){
    in>>nr.x>>nr.y;
}

ofstream& operator<<(ofstream& out, complexNumber nr){
    out<<nr.x<<" "<<nr.y<<"\n";
}

void unitTest(){
    complexNumber a(3, 5);
    complexNumber b(-2, 7);
    complexNumber equals(3, 5);
    complexNumber sum(1, 12);
    complexNumber diff(5, -2);
    complexNumber product(-6, 35);
    complexNumber div(3 / (-2.0), 5/7.0);
    complexNumber c(4, 7);

    assert(a.x == 3);
    assert(a.y == 5);
    assert(a == equals);
    assert(a == a);
    assert(a != b);
    assert(a+b == sum);
    assert(a-b == diff);
    assert(a*b == product);
    assert(a/b == div);
    a = c;
    assert(a == c);

    complexNumber smallNumber(1, 1);
    complexNumber bigNumber(3, -2);
    assert(smallNumber < bigNumber);

    ofstream out("test.txt");
    out << a;
    out.close();
    ifstream in("test.txt");
    complexNumber a_copy;
    in >> a_copy;
    assert(a == a_copy);

    if(bool TESTING_DIVISION_BY_ZERO = false){
        complexNumber badDivisionNumber(5, 0);
        complexNumber x = a / badDivisionNumber; ///
    }

    if(!SUPPRESS_LOGS){
        a.print();
        b.print();
    }
}

int main()
{
    unitTest();

    /// Cerinta Comuna 1 (citirea informațiilor complete a n obiecte, memorarea și afisarea acestora)
    complexNumber v[20];
    int n;

    ifstream in("sortData.in");
    in>>n;
    for(int i=0; i<n; ++i) in>>v[i];
    for(int i=0; i<n; ++i) cout<<v[i]; cout<<"\n"; /// Input data
    sort(v, v+n);
    for(int i=0; i<n; ++i) cout<<v[i]; cout<<"\n"; /// Sorted Input data

    return 0;
}
