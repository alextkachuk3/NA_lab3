#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main()
{
    ifstream matrix_file("matrix.txt");

    int size;

    matrix_file >> size;

    double** A = new double* [size];

    for (int i = 0; i < size; i++)
    {
        A[i] = new double[size];
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            matrix_file >> A[i][j];
        }
    }

    matrix_file.close();


    cout << fixed;
    cout << setprecision(4);

    for (int i = 0; i < size; i++)
    {
        if (i == size / 2)
        {
            cout << " A = ";
        }
        else
        {
            cout << "     ";
        }
        for (int j = 0; j < size; j++)
        {
            cout << setw(8) << A[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;

    double* x_current = new double[size];
    double* x_prev = new double[size];

    double lmd_current = 0.0;
    double lmd_prev = 0.0;

    double norm = 1.0;
    double eps = 1e-5;

    x_current[0] = 1;
    x_current[1] = 1;
    x_current[2] = 1;
    x_current[3] = 1;
    x_current[4] = 1;

    double* e = new double[size];

    double x_norm;

    int iter = 0;

    while (norm > eps)
    {
        iter++;
        cout << "Iter:" << iter << endl;

        for (int i = 0; i < size; i++)
        {
            x_prev[i] = x_current[i];
        }

        if (iter == 1)
        {
            for (int i = 0; i < size; i++)
            {
                x_current[i] = A[i][0] * x_prev[0];
                for (int j = 1; j < size; j++)
                {
                    x_current[i] += A[i][j] * x_prev[j];
                }
            }

            lmd_current = 0.0;

            for (int i = 0; i < size; i++)
            {
                lmd_current += x_current[i] * x_prev[i];
            }

            double temp = 0.0;

            for (int i = 0; i < size; i++)
            {
                temp += x_prev[i] * x_prev[i];
            }

            lmd_current /= temp;
        }
        else
        {
            x_norm = 0.0;

            for (int i = 0; i < size; i++)
            {
                if (abs(x_current[i]) > x_norm)
                {
                    x_norm = abs(x_current[i]);
                }
            }

            for (int i = 0; i < size; i++)
            {
                e[i] = x_current[i] / x_norm;
            }

            for (int i = 0; i < size; i++)
            {
                x_current[i] = A[i][0] * e[0];
                for (int j = 1; j < size; j++)
                {
                    x_current[i] += A[i][j] * e[j];
                }
            }

            lmd_prev = lmd_current;
            lmd_current = 0.0;

            for (int i = 0; i < size; i++)
            {
                lmd_current += x_current[i] * e[i];
            }

            double temp = 0.0;

            for (int i = 0; i < size; i++)
            {
                temp += e[i] * e[i];
            }

            lmd_current /= temp;

            norm = abs(lmd_current - lmd_prev);
        }


        for (int i = 0; i < size; i++)
        {
            if (i == size / 2)
            {
                cout << " x" << iter << "= ";
            }
            else
            {
                cout << "     ";
            }

            cout << x_current[i] << " ";

            cout << endl;
        }

        cout << "lmd" << iter << " = " << lmd_current << endl;
    }

    cout << "lmd_min = " << norm << endl;



    delete[] e;
    delete[] x_prev;
    delete[] x_current;
    for (int i = 0; i < size; i++)
    {
        delete[] A[i];
    }
    delete[] A;
}