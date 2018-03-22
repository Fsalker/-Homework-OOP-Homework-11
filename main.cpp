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
        double x,y;
    protected:

    public:

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
            res.x = this->x * other.x - this->y * other.y;
            res.y = this->x * other.y + this->y * other.x;

            return res;
        }

        complexNumber operator/(complexNumber other){
            if(other.x * other.x + other.y * other.y == 0)
                throw "Cannot divide by 0.";
            complexNumber res;
                res.x = (this->x * other.x + this->y * other.y) / (other.x * other.x + other.y * other.y);
                res.y = (this->y * other.x - this->x * other.y) / (other.x * other.x + other.y * other.y);;

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

        friend istream& operator>>(istream& in, complexNumber& nr){
            in>>nr.x>>nr.y;
        }

        friend ostream& operator<<(ostream& out, complexNumber nr){
            out<<nr.x<<" "<<nr.y<<" ";
        }

        friend ifstream& operator>>(ifstream& in, complexNumber& nr){
            in>>nr.x>>nr.y;
        }

        friend ofstream& operator<<(ofstream& out, complexNumber nr){
            out<<nr.x<<" "<<nr.y<<" ";
        }
};

template<typename T> class matrix{
    friend class complexNumber;
    private:
    protected:
    public:
        int height, width;
        T **data;

        matrix(const matrix& other){
            height = other.height;
            width = other.width;

            data = new complexNumber*[height];
            for(int i=0; i<height; ++i)
            {
                data[i] = new complexNumber[width];
                for(int j=0; j<width; ++j)
                    data[i][j] = other.data[i][j];
            }
        }

        matrix(){
        }

        ~matrix(){
            for(int i=0; i<this->height; ++i)
            {
                //cout<<"i = "<<i<<", height = "<<this->height<<"\n";
                //cout<<"deleting "<<data[i]<<"\n";
                //delete &(data[i]);

                //delete[] data[i];
            }
            //delete[] data;
        }

        bool operator==(matrix other){
            if(height != other.height) return 0;
            if(width != other.width) return 0;

            for(int i=0; i<height; ++i)
                for(int j=0; j<width; ++j)
                    if(data[i][j] != other.data[i][j])
                        return 0;

            return 1;
        }

        bool operator!=(matrix other){
            return !(*this == other);
        }

        bool operator<(matrix other){
            return height < other.height;
        }

        matrix operator=(matrix other){
            this->height = other.height;
            this->width = other.width;
            this->data = new complexNumber*[height];
            for(int i=0; i<this->height; ++i)
            {
                this->data[i] = new complexNumber[width];
                for(int j=0; j<this->width; ++j)
                    this->data[i][j] = other.data[i][j];
            }
            return *this;
        }

        matrix operator+(matrix other){
            matrix res;

            res.height = min(height, other.height);
            res.width = min(width, other.width);
            res.data = new complexNumber*[height];
            for(int i=0; i<res.height; ++i)
            {
                res.data[i] = new complexNumber[width];
                for(int j=0; j<res.width; ++j)
                    res.data[i][j] = data[i][j] + other.data[i][j];
            }

            return res;
        }

        matrix operator-(matrix other){
            matrix res;

            res.height = min(height, other.height);
            res.width = min(width, other.width);
            res.data = new complexNumber*[height];
            for(int i=0; i<res.height; ++i)
            {
                res.data[i] = new complexNumber[width];
                for(int j=0; j<res.width; ++j)
                    res.data[i][j] = data[i][j] - other.data[i][j];
            }

            return res;
        }

        matrix operator*(matrix other){
            if(width == other.height){
                matrix res;

                res.height = height;
                res.width = other.width;
                res.data = new complexNumber*[height];
                for(int i=0; i<res.height; ++i)
                {
                    res.data[i] = new complexNumber[width];
                    for(int j=0; j<res.width; ++j)
                    {
                        res.data[i][j] = *(new complexNumber(0, 0));
                        for(int offset = 0; offset < res.width; ++offset)
                            res.data[i][j] = res.data[i][j] + data[i][offset] * other.data[offset][j];
                    }
                }

                return res;
            }
        }

        matrix stripSubmatrix(int stripRow, int stripCol){
            matrix smallerMatrix;

            smallerMatrix.height = height - 1;
            smallerMatrix.width = width - 1;
            smallerMatrix.data = new complexNumber*[height-1];
            int crtSmallRow = 0;
            for(int row = 0; row < height; ++row)
            {
                if(row == stripRow) continue; /// Skip the row we're currently stripping
                smallerMatrix.data[crtSmallRow] = new complexNumber[width-1];
                int crtSmallCol = 0;
                for(int col=0; col<width; ++col)
                {
                    if(col == stripCol) continue; /// Skip the column we're currently stripping

                    smallerMatrix.data[crtSmallRow][crtSmallCol] = data[row][col];
                    ++crtSmallCol;
                }
                ++crtSmallRow;
            }

            return smallerMatrix;
        }

        complexNumber determinant(){
            if(height == width){
                if(height == 1)
                    return data[0][0];
                else if(height == 2)
                    return data[0][0] * data[1][1] - data[1][0] * data[0][1];
                else{
                    complexNumber res(0, 0);
                    complexNumber opposite(-1, 0);
                    for(int stripCol = 0; stripCol < width; ++stripCol)
                    {
                        matrix smallerMatrix = stripSubmatrix(0, stripCol);
                        complexNumber crtDeterminant = smallerMatrix.determinant();
                        if(stripCol % 2 == 1)
                            crtDeterminant = crtDeterminant * opposite;
                        res = res + data[0][stripCol]*crtDeterminant;
                    }
                    return res;
                }
            }
        }

        matrix inverseMatrix(){
            complexNumber det = determinant();
            complexNumber one(1, 0);
            complexNumber opposite(-1, 0);
            complexNumber inverseDeterminant = one / det;

            matrix res;
            res.height = height;
            res.width = width;
            res.data = new complexNumber*[height];
            for(int row=0; row<height; ++row)
                res.data[row] = new complexNumber[width];
            for(int row=0; row<height; ++row)
            {
                for(int col=0; col<width; ++col)
                {
                    matrix A_star = stripSubmatrix(row, col);
                    complexNumber A_star_det = A_star.determinant();
                    res.data[col][row] = A_star_det * inverseDeterminant; /// [col][row] for transposition
                    if((col+row)%2 == 1)
                        res.data[col][row] = res.data[col][row] * opposite;
                }
            }
            return res;
        }

        friend istream& operator>>(istream& in, matrix<T>& A){
            in>>A.height>>A.width;
            A.data = new complexNumber*[A.height];
            for(int i=0; i<A.height; ++i)
            {
                A.data[i] = new complexNumber[A.width];
                for(int j=0; j<A.width; ++j)
                    in>>A.data[i][j];
            }
            return in;
        }

        friend ifstream& operator>>(ifstream& in, matrix<T>& A){
            in>>A.height>>A.width;
            A.data = new complexNumber*[A.height];
            for(int i=0; i<A.height; ++i)
            {
                A.data[i] = new complexNumber[A.width];
                for(int j=0; j<A.width; ++j)
                    in>>A.data[i][j];
            }
            return in;
        }

        friend ostream& operator<<(ostream& out, matrix<T> A){
            //out<<A.height<<" "<<A.width<<"\n";
            for(int i=0; i<A.height; ++i)
            {
                for(int j=0; j<A.width; ++j)
                    out<<A.data[i][j]<<" ";
                out<<"\n";
            }
            return out;
        }

        friend ofstream& operator<<(ofstream& out, matrix<T> A){
            //out<<A.height<<" "<<A.width<<"\n";
            for(int i=0; i<A.height; ++i)
            {
                for(int j=0; j<A.width; ++j)
                    out<<A.data[i][j]<<" ";
                out<<"\n";
            }
            return out;
        }
};

void unitTest_complexNumber(){
    complexNumber a(3, 5);
    complexNumber b(-2, 7);
    complexNumber equals(3, 5);
    complexNumber sum(1, 12);
    complexNumber diff(5, -2);
    complexNumber product(-41, 11);
    complexNumber div(29 / 53.0, -31 / 53.0);
    complexNumber c(4, 7);

    //assert(a.x == 3);
    //assert(a.y == 5);
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

void unitTest_matrix(){
    /*ifstream in("matrixTest.in");
    matrix A,B;
    in>>A;
    in>>B;
    */
}

void unitTest(){
    unitTest_complexNumber();
    //unitTest_matrix();
}

int main()
{
    /// Testing
    unitTest();

    /// Common Task #1 ("citirea informatiilor complete a n obiecte, memorarea si afisarea acestora")
    /// Task #1
    complexNumber v[20];
    int n;

    ifstream in("sortData.in");
    in>>n;
    for(int i=0; i<n; ++i) in>>v[i];
    cout<<"Before sorting\n";
    for(int i=0; i<n; ++i) cout<<v[i]<<"\n"; cout<<"\n"; /// Input data
    sort(v, v+n);
    cout<<"After sorting\n";
    for(int i=0; i<n; ++i) cout<<v[i]<<"\n"; cout<<"\n"; /// Sorted Input data
    in.close();

    /// Task #2
    matrix<complexNumber> A,B;
    ifstream in2("homeworkData.in");
    in2>>A;
    in2>>B;
    cout<<"A = \n"; cout<<A; cout<<"\n";
    cout<<"B = \n"; cout<<B; cout<<"\n";
    matrix<complexNumber> AAA = A;
    matrix<complexNumber> AAAA(A);
    cout<<"AAA = \n"; cout<<AAA; cout<<"\n";
    cout<<"AAAA = \n"; cout<<AAAA; cout<<"\n";
    assert(A == AAA);
    assert(A == AAAA);
    assert( !(A != AAA) );
    cout<<"Checking A<B: "; cout<< (A<B); cout<<" \n";
    /// + - *
    matrix<complexNumber> C,D,E;
    C = A+B;
    D = A-B;
    E = A*B;
    cout<<"A+B = \n"; cout<<C; cout<<"\n";
    cout<<"A-B = \n"; cout<<D; cout<<"\n";
    cout<<"A*B = \n"; cout<<E; cout<<"\n";
    in2.close();

    /// Determinant
    cout<<"A's Determinant = "; cout<<A.determinant(); cout<<"\n";

    /// Inverse
    matrix<complexNumber> AA;
    AA = A.inverseMatrix();
    cout<<"A's inverse matrix = \n"; cout<<AA; cout<<"\n";

    /// A * AA
    matrix<complexNumber> P;
    P = A * AA;
    cout<<"A * AA = \n"; cout<<P; cout<<"\n";

    return 0;
}
