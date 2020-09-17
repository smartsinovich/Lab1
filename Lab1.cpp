//#include "bits/stdc++.h"
#include <iostream>
#include <fstream>
#include <ios>
using namespace std;

#define MY_TYPE double

template <typename T>
class Matrix
{
//private:
public:
    T **Matr;
    int m;
    int n;

    void Create()
        {
            Matr = new T*[m];
            for (int z=0; z<m; z++)
                Matr[z] = new T[n];
        }

    Matrix(int i): m(i), n(i) { Create(); }
    Matrix(int i, int j): m(i), n(j) { Create(); }
    ~Matrix()
    {
        for (int z=0; z<m; z++)
            delete[] Matr[z];
        delete[] Matr;
    }

    //возвращает элемент
    T& Element(int i, int j)
    {
        if (i<m && j<n)
            return Matr[i][j];
        else
            cerr << "Error: 1" <<endl;
    }

    //вывод матрицы в консоль
    void Display()
    {
        for(int i=0; i<m; i++)
        {
            for(int j=0; j<n; j++)
            {
                cout.width(4);
                cout << Matr[i][j];
            }
            cout << endl;
        }
    }

};


// Вычисляет определитель матрицы M размерности N
MY_TYPE Determinant(MY_TYPE **M, int N)
{
  MY_TYPE det;
  int sub_j, s;
  MY_TYPE **subM;    // Субматрица как набор ссылок на исходную матрицу
  switch (N)
  {
  case 1:
    return M[0][0];
  case 2:
    return M[0][0] * M[1][1] - M[0][1] * M[1][0];
  default:
    if (N < 1) {
        cerr << "Determinant cannot be found!"<< endl;
        return 0;  // Некорректная матрица
    }
    subM = new double*[N-1];  // Массив ссылок на столбцы субматрицы
    det = 0;
    s = 1;        // Знак минора
    for (int i = 0; i < N; i++)  // Разложение по первому столбцу
    {
      sub_j = 0;
      for (int j = 0; j < N; j++)// Заполнение субматрицы ссылками на исходные столбцы
        if (i != j)      // исключить i строку
          subM[sub_j++] = M[j] + 1;  // здесь + 1 исключает первый столбец

      det = det + s * M[i][0] * Determinant(subM, N-1);
      s = -s;
    };
    delete[] subM;
    return det;
  };
};

//умножение матриц: только для квадратных!!!
Matrix <MY_TYPE> Mult(Matrix <MY_TYPE> matr1, Matrix <MY_TYPE> matr2) {
    if (matr1.n!=matr1.m || matr2.n!=matr2.m || matr1.n!=matr2.n) {
        cerr << "Error: function Mult" << endl;
        return 0;
    }

    int size = matr1.n;

    Matrix <MY_TYPE> result(size); 

    for(int k=0; k<size; k++) {
        for(int i=0; i<size; i++){
            for(int j=0; j<size; j++) 
                result.Matr[k][i]+= matr1.Matr[k][j] * matr2.Matr[j][i];
        }
    }  
    return result;
}


int main ( int argc, char *argv[] )
{
    string file_name = "";
    cin >> file_name;
    file_name +=".TXT";
	ifstream in_file(file_name);
	// Если мы не можем открыть файл для чтения его содержимого
	if (!in_file)
	{
		cerr << "Uh oh, Input.txt could not be opened for reading!" << endl;
		exit(1);
	}

    int n=0;
    in_file >> n;
    Matrix <MY_TYPE> A(n);
    Matrix <MY_TYPE> B(n,1);

    for (int i=0; i<n; i++) {
        MY_TYPE el;
        for (int j=0; j<n; j++) {
            MY_TYPE el;
            in_file>>el;
            A.Element(i,j)=el;
        }
        in_file>>el;
        B.Element(i,0)=el;
    }
    A.Display();
    cout<<endl;
    B.Display();

    cout<<"A.Determinant() = "<<Determinant(A.Matr, A.n)<<endl;
    Mult(A,A).Display();

    return 0;
}
