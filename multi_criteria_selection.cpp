#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>

std::vector<double> Normal_form(const std::vector<double>& matrix)
{
    std::vector<double> _matrix(4);
    double s = 0;
    for (auto i : matrix)
        s += i;
    for (int i = 0; i < 4; i++)
        _matrix[i] = matrix[i] / s;
    return _matrix;
}

std::vector<std::vector<double>> Normal_form(const std::vector<std::vector<double>>& matrix)
{
    std::vector<double> sum(4);
    std::vector<std::vector<double>> _matrix(4, std::vector<double>(4));
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            sum[i] += matrix[j][i];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            _matrix[j][i] = matrix[j][i] / sum[i];
    return _matrix;
}

void sort(std::vector<std::vector<double>>& matrix)
{
    double tmp;
    for (auto i = 0; i < 4; i++)
        for (auto j = 0; j <= 3; j++)
            for (auto c = j; c <= 3; c++)
                if (matrix[j][i] > matrix[c][i])
                {
                    tmp = matrix[j][i];
                    matrix[j][i] = matrix[c][i];
                    matrix[c][i] = tmp;
                }
}

std::vector<double> summa(const std::vector<std::vector<double>>& matrix)
{
    std::vector<double> sum(4);
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            sum[i] += matrix[i][j];
    return sum;
}

std::vector<std::vector<double>> MethodZamena(const std::vector<std::vector<double>>& matrix, const int& critery)
{
    std::vector<std::vector<double>> matrix1 = matrix;
    sort(matrix1);
    std::vector<std::vector<double>> matrix2(4, std::vector<double>(4));

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            if (i != critery)
                matrix2[j][i] = (matrix[j][i] - matrix1[0][i]) / (matrix1[3][i] - matrix1[0][i]);
            else
                matrix2[j][i] = matrix[j][i];
        }
    return matrix2;
}

double MethodParreto_U(const std::vector<std::vector<double>>& matrix, const int& critery)
{
    std::vector<double> _matrix(4);
    for (int i = 0; i < 4; i++)
        _matrix[i] = matrix[i][critery];
    sort(begin(_matrix), end(_matrix));
    return _matrix[3];
}

double MethodParreto_E(const std::vector<std::vector<double>>& matrix, const double& ut1, const double& ut2, const int& critery1, const int& critery2, const int& critery3)
{
    double dist;
    dist = sqrt(pow(ut1 - matrix[critery3][critery1], 2) + pow(ut2 - matrix[critery3][critery2], 2));
    return dist;
}

std::vector<double> Vector_Weight(const std::vector<double>& critery)
{
    std::vector<double> vec_critery(4);
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (i != j)
            {
                if (critery[i] > critery[j])
                    vec_critery[i]++;
                if (critery[i] == critery[j])
                    vec_critery[i] += 0.5;
            }
    return vec_critery;
}

std::vector<double> Method_of_weight_and_unification(const std::vector<std::vector<double>>& matrix, const std::vector<double>critery)
{
    std::vector<double> _matrix(4);
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            _matrix[i] += matrix[i][j] * critery[j];
    return _matrix;
}

std::vector<std::vector<double>> MethodHierarchyAnalysis(const std::vector<std::vector<double>>& matrix, const int& critery)
{
    std::vector<std::vector<double>> _matrix(4, std::vector<double>(4));
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            if (matrix[i][critery] == matrix[j][critery])
                _matrix[i][j] = 1;
            if (matrix[i][critery] > matrix[j][critery])
            {
                if (matrix[i][critery] - matrix[j][critery] == 1)
                    _matrix[i][j] = 3;
                if (matrix[i][critery] - matrix[j][critery] == 2)
                    _matrix[i][j] = 5;
                if (matrix[i][critery] - matrix[j][critery] == 3)
                    _matrix[i][j] = 7;
                if (matrix[i][critery] - matrix[j][critery] == 4)
                    _matrix[i][j] = 9;
            }
            if (matrix[i][critery] < matrix[j][critery])
            {
                if (matrix[j][critery] - matrix[i][critery] == 1)
                    _matrix[i][j] = 1.0 / 3;
                if (matrix[j][critery] - matrix[i][critery] == 2)
                    _matrix[i][j] = 1.0 / 5;
                if (matrix[j][critery] - matrix[i][critery] == 3)
                    _matrix[i][j] = 1.0 / 7;
                if (matrix[j][critery] - matrix[i][critery] == 4)
                    _matrix[i][j] = 1.0 / 9;
            }
        }
    return _matrix;
}

std::vector<std::vector<double>> MethodHierarchyAnalysis_criteryerions(const std::vector<double>& critery)
{
    std::vector<std::vector<double>> _matrix(4, std::vector<double>(4));
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            if (critery[i] == critery[j])
                _matrix[j][i] = 1;
            if (critery[i] > critery[j])
            {
                if (critery[i] - critery[j] == 1)
                    _matrix[j][i] = 3;
                if (critery[i] - critery[j] == 2)
                    _matrix[j][i] = 5;
                if (critery[i] - critery[j] == 3)
                    _matrix[j][i] = 7;
                if (critery[i] - critery[j] == 4)
                    _matrix[j][i] = 9;
            }
            if (critery[i] < critery[j])
            {
                if (critery[j] - critery[i] == 1)
                    _matrix[j][i] = 1.0 / 3;
                if (critery[j] - critery[i] == 2)
                    _matrix[j][i] = 1.0 / 5;
                if (critery[j] - critery[i] == 3)
                    _matrix[j][i] = 1.0 / 7;
                if (critery[j] - critery[i] == 4)
                    _matrix[j][i] = 1.0 / 8;
            }
        }
    return _matrix;
}

void print(const std::vector<double>& matrix)
{
    for (auto i : matrix) std::cout << i << " ";
    std::cout << std::endl;
}

void print(const std::vector<std::vector<double>>& matrix)
{
    std::cout << "     1     2     3    4" << std::endl;
    std::cout << "A  ";
    for (int i = 0; i < 4; i++) std::cout << std::fixed << std::setprecision(2) << matrix[0][i] << "  ";
    std::cout << std::endl << "B  ";
    for (int i = 0; i < 4; i++) std::cout << matrix[1][i] << "  ";
    std::cout << std::endl << "C  ";
    for (int i = 0; i < 4; i++) std::cout << matrix[2][i] << "  ";
    std::cout << std::endl << "D  ";
    for (int i = 0; i < 4; i++) std::cout << matrix[3][i] << "  ";
    std::cout << std::endl;
}

void print(const std::vector<std::vector<double>>& matrix, const std::vector<double>& sum, const std::vector<double>& normsum)
{
    std::cout << "     A      B      C      D     sum   NormSum" << std::endl;
    std::cout << "A  ";
    for (int i = 0; i <= 3; i++)
        std::cout << std::fixed << std::setprecision(2) << std::setw(5) << matrix[0][i] << "  ";
    std::cout << std::setw(5) << sum[0] << "  " << normsum[0];
    std::cout << std::endl << "B  ";
    for (auto i = 0; i <= 3; i++)
        std::cout << std::setw(5) << matrix[1][i] << "  ";
    std::cout << std::setw(5) << sum[1] << "  " << normsum[1];
    std::cout << std::endl << "C  ";
    for (auto i = 0; i <= 3; i++)
        std::cout << std::setw(5) << matrix[2][i] << "  ";
    std::cout << std::setw(5) << sum[2] << "  " << normsum[2];
    std::cout << std::endl << "D  ";
    for (auto i = 0; i <= 3; i++)
        std::cout << std::setw(5) << matrix[3][i] << "  ";
    std::cout << std::setw(5) << sum[3] << "  " << normsum[3];
    std::cout << std::endl;
}


int main()
{
    std::vector<std::vector<double>> matrix = { {7,7,3,6},{9,4,2,8},{3,6,8,7},{6,8,6,4} };
    std::vector<double> critery = { 6,4,2,8 };
    std::vector<double> norm_critery = Normal_form(critery);
    print(matrix);
    print(norm_critery);

    std::cout << std::endl << "Method zameny kriteriev limitations: " << std::endl;
    std::vector<std::vector<double>> matrix1 = MethodZamena(matrix, 3);
    print(matrix1);

    std::cout << std::endl << "Method Pareto to Euclid distance: " << std::endl;
    double ut1 = MethodParreto_U(matrix, 1);
    double ut2 = MethodParreto_U(matrix, 2);
    std::cout << "Utopias " << ut1 << " " << ut2 << std::endl;
    std::cout << "A: " << MethodParreto_E(matrix, ut1, ut2, 1, 2, 0) << std::endl;
    std::cout << "B: " << MethodParreto_E(matrix, ut1, ut2, 1, 2, 1) << std::endl;
    std::cout << "C: " << MethodParreto_E(matrix, ut1, ut2, 1, 2, 2) << std::endl;
    std::cout << "D: " << MethodParreto_E(matrix, ut1, ut2, 1, 2, 3) << std::endl;

    std::cout << std::endl << "Method_of_weight_and_unification: " << std::endl;
    std::vector<std::vector<double>> matrix2 = Normal_form(matrix);
    print(matrix2);
    std::vector<double> vec_critery;
    std::vector<double> norm_vec_critery;
    vec_critery = Vector_Weight(critery);
    norm_vec_critery = Normal_form(vec_critery);
    print(norm_vec_critery);
    vec_critery = Method_of_weight_and_unification(matrix2, norm_vec_critery);
    std::cout << "Znacheniya kritery: ";
    print(vec_critery);
    std::cout << std::endl << std::endl;


    std::cout << "Method ierarchy: " << std::endl;
    std::vector<double> _matrix0(4), _matrix1(4), _matrix2(4), _matrix3(4), _matrix(4);
    std::vector <double> matrix0sum(4), matrix1sum(4), matrix2sum(4), matrix3sum(4), matrixsum(4);

    matrix2 = MethodHierarchyAnalysis(matrix, 0);
    matrix0sum = summa(matrix2);
    _matrix0 = Normal_form(matrix0sum);
    std::cout << std::endl << "Appearence: " << std::endl;
    print(matrix2, matrix0sum, _matrix0);

    matrix2 = MethodHierarchyAnalysis(matrix, 1);
    matrix1sum = summa(matrix2);
    _matrix1 = Normal_form(matrix1sum);
    std::cout << std::endl << "Financial requets: " << std::endl;
    print(matrix2, matrix1sum, _matrix1);

    matrix2 = MethodHierarchyAnalysis(matrix, 2);
    matrix2sum = summa(matrix2);
    _matrix2 = Normal_form(matrix2sum);
    std::cout << std::endl << "Thriftiness: " << std::endl;
    print(matrix2, matrix2sum, _matrix2);

    matrix2 = MethodHierarchyAnalysis(matrix, 3);
    matrix3sum = summa(matrix2);
    _matrix3 = Normal_form(matrix3sum);
    std::cout << std::endl << "Personality: " << std::endl;
    print(matrix2, matrix3sum, _matrix3);

    matrix2 = MethodHierarchyAnalysis_criteryerions(critery);
    matrixsum = summa(matrix2);
    _matrix = Normal_form(matrixsum);
    std::cout << std::endl << "Priority of criteryerions: " << std::endl;
    print(matrix2, matrixsum, _matrix);
    std::cout << std::endl;

    for (int i = 0; i < 4; i++)
    {
        matrix2[i][0] = _matrix0[i];
        matrix2[i][1] = _matrix1[i];
        matrix2[i][2] = _matrix2[i];
        matrix2[i][3] = _matrix3[i];
    }
    for (auto i : matrix2)
    {
        for (auto j : i)
            std::cout << j << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
    vec_critery = Method_of_weight_and_unification(matrix2, _matrix);
    print(vec_critery);
}
