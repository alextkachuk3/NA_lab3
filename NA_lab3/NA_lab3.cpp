#include <iostream>
#include <iomanip>
#include <memory>

using namespace std;

void F(const double& x, const double& y, double** matrix)
{
    matrix[0][0] = tan(x * y + 0.1) - pow(x, 2.0);
    matrix[1][0] = pow(x, 2.0) + 2 * pow(y, 2.0) - 1;
}

void A(const double& x, const double& y, double** matrix)
{    
    matrix[0][0] = y * pow(1 / cos(x * y + 0.1), 2.0) - 2 * x;
    matrix[0][1] = x * pow(1 / cos(x * y + 0.1), 2.0);
    matrix[1][0] = 2 * x;
    matrix[1][1] = 4 * y;
}

double det2x2(double** matrix)
{
    return (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]);
}

void inverse2x2(double** input_matrix, double** output_matrix)
{
    double k = 1.0 / det2x2(input_matrix);
    output_matrix[0][0] = k * input_matrix[1][1];
    output_matrix[0][1] = -k * input_matrix[0][1];
    output_matrix[1][0] = -k * input_matrix[1][0];
    output_matrix[1][1] = k * input_matrix[0][0];
}

 

int main()
{
    double** x_current = new double* [2];
    double** x_prev = new double* [2];
    double** F_x = new double* [2];
    double** matrix_A = new double* [2];
    double** matrix_A_inv = new double* [2];

    for (int i = 0; i < 2; i++)
    {
        x_current[i] = new double[1];
        x_prev[i] = new double[1];
        matrix_A[i] = new double[2];
        matrix_A_inv[i] = new double[2];
        F_x[i] = new double[1];
    }

    x_current[0][0] = -0.5;
    x_current[1][0] = -0.5;

    double norm = 1.0;
    double eps = 1e-3;    

    A(x_current[0][0], x_current[1][0], matrix_A);

    cout << "     " << setw(10) <<  matrix_A[0][0] << " " << setw(10) << matrix_A[0][1] << endl;
    cout << "A = " << endl;
    cout  << "     " << setw(10) << matrix_A[1][0] << " " << setw(10) << matrix_A[1][1] << endl << endl;

    inverse2x2(matrix_A, matrix_A_inv);

    cout << "     " << setw(10) << matrix_A_inv[0][0] << " " << setw(10) << matrix_A_inv[0][1] << endl;
    cout << "A^-1 = " << endl;
    cout << "     " << setw(10) << matrix_A_inv[1][0] << " " << setw(10) << matrix_A_inv[1][1] << endl;

    int iter = 1;

    while (norm > eps)
    {
        cout << "Iter:" << iter << endl;
        iter++;

        x_prev[0][0] = x_current[0][0];
        x_prev[1][0] = x_current[1][0];

        F(x_prev[0][0], x_prev[1][0], F_x);

        cout << "     " << setw(12) << F_x[0][0] << endl;
        cout << "F = " << endl;
        cout << "     " << setw(12) << F_x[1][0] << endl << endl;

        x_current[0][0] = x_prev[0][0] - (matrix_A_inv[0][0] * F_x[0][0] + matrix_A_inv[0][1] * F_x[1][0]);
        x_current[1][0] = x_prev[1][0] - (matrix_A_inv[1][0] * F_x[0][0] + matrix_A_inv[1][1] * F_x[1][0]);

        cout << "     " << setw(10) << x_current[0][0] << endl;
        cout << "x" << iter << " = " << endl;
        cout << "     " << setw(10) << x_current[1][0] << endl << endl;

        norm = 0.0;
        for (int i = 0; i < 2; i++)
        {
            double cur = abs(x_current[i][0] - x_prev[i][0]);
            if (cur > norm)
            {
                norm = cur;
            }
        }
    }

    for (int i = 0; i < 2; i++)
    {
        delete[] matrix_A[i];
        delete[] matrix_A_inv[i];
        delete[] x_current[i];
        delete[] x_prev[i];
    }

    delete[] matrix_A;
    delete[] matrix_A_inv;
    delete[] x_current;
    delete[] x_prev;
}