//3.2 completed
#include <iostream>
template <typename T>
class Matrix
{
private:
    T *data;
    T *tmp=new T[1];
    int rows;
    int cols;
    int error;
    void resize(int rows,int cols)
    {
        delete[] data;
        data=new T[rows*cols];
    }
public:
    Matrix()
    {
        rows=2;
        cols=2;
        error=0;
        resize(rows,cols);
    }
    Matrix(int _rows_cols)
    {
        rows=_rows_cols;
        cols=_rows_cols;
        error=0;
        resize(rows,cols);
    }
    Matrix(int _rows,int _cols,T value)
    {
        rows=_rows;
        cols=_cols;
        error=0;
        resize(rows,cols);
        for(int i=0; i<rows*cols; i++) { data[i]=value; }
    }
    Matrix(Matrix &other)
    {
        rows=other.rows;
        cols=other.cols;
        error=0;
        resize(rows,cols);
        for(int i=0; i<rows*cols; i++) { data[i]=other.data[i]; }
    }
    ~Matrix() { delete[] data; delete[] tmp; }
    Matrix &operator=(Matrix &other)
    {
        rows=other.rows;
        cols=other.cols;
        error=0;
        resize(rows,cols);
        for(int i=0; i<rows*cols; i++) { data[i]=other.data[i]; }
        return *this;
    }
    Matrix &operator+(T number) { for(int i=0; i<rows*cols; i++) { data[i]+=number; } return *this; }
    Matrix &operator-(T number) { for(int i=0; i<rows*cols; i++) { data[i]-=number; } return *this; }
    Matrix &operator*(T number) { for(int i=0; i<rows*cols; i++) { data[i]*=number; } return *this; }
    Matrix &operator/(T number) { for(int i=0; i<rows*cols; i++) { data[i]/=number; } return *this; }
    Matrix &operator+=(T number) { for(int i=0; i<rows*cols; i++) { data[i]+=number; } return *this; }
    Matrix &operator-=(T number) { for(int i=0; i<rows*cols; i++) { data[i]-=number; } return *this; }
    Matrix &operator*=(T number) { for(int i=0; i<rows*cols; i++) { data[i]*=number; } return *this; }
    Matrix &operator/=(T number) { for(int i=0; i<rows*cols; i++) { data[i]/=number; } return *this; }
    bool operator>(const Matrix &other) const { return (rows*cols>other.rows*other.cols); }
    bool operator<(const Matrix &other) const { return (rows*cols<other.rows*other.cols); }
    bool operator==(const Matrix &other) const
    {
        if(rows!=other.rows||cols!=other.cols) { return false; }
        for(int i=0; i<rows*cols; ++i)
        {
            if(data[i]!=other.data[i]) { return false; }
        }
        return true;
    }
    int getRows() { return rows; }
    int getCols() { return cols; }
    int getError() { return error; }
    int getSize() { return rows*cols; }
    T &operator()(int i,int j)
    {
        if(i>=0&&i<rows&&j>=0&&j<cols) { return data[i*cols+j]; }
        else { error=1; return tmp[0]; }
    }
    void print()
    {
        for(int i=0;i<cols;i++)
        {
            for(int j=0;j<rows;j++)
            {
                cout<<data[i*rows+j]<<'\t';
            }
            cout<<endl;
        }
        cout<<endl;
    }
};

int task3()
{
    Matrix<float> mat1(3,4,1);
    mat1.print();
    mat1(1,2)+=3;
    mat1.print();
    mat1+=3;
    mat1.print();
    mat1*=3.0;
    mat1.print();
    Matrix<float> mat2(4,3,4);
    mat1=mat2;
    mat1+=5;
    if(mat1==mat2) { cout<<"mat1 == mat2"<<endl; }
    else { cout<<"mat1 != mat2"<<endl; }
    mat1=mat2;
    if(mat1==mat2) { cout<<"mat1 == mat2"<<endl; }
    else { cout<<"mat1 != mat2"<<endl; }
    return 0;
}

/*
Створити клас матриця.
Даний клас містить вказівник на float, розміри рядків і стовпців та стан помилки.

У класі визначити:
- конструктор без параметрів( виділяє місце для матриці 2 на 2 елемента та інінціалізує його в нуль);
- конструктор з одним параметром - розмір n матриці (виділяє місце для матриці n на n та інінціалізує матрицю значенням нуль);
- конструктор із трьома розміри матриці (n , m) та значення ініціалізації value (виділяє місце перші аргументи та інінціалізує значенням третього аргументу - value);
- конструктор копій та операцію присвоєння; // !!!
- деструктор звільняє пам'ять.
- визначити функцію, яка присвоює елементу масиву деяке значення (параметр за замовчуванням);
- функцію яка одержує деякий елемент матриці за індексами i та j;
- визначити функції друку, додавання, множення на скаляр, віднімання, які здійснюють ці арифметичні операції з даними цього класу;
- визначити функції порівняння: більше, менше або рівно, які повертають true або false.

У змінну стани встановлювати код помилки, коли не вистачає пам'яті, виходить за межі матриці.
Передбачити можливість підрахунку числа об'єктів даного типу.
Написати програму тестування всіх можливостей цього класу.
*/