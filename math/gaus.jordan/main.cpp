#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

typedef vector<vector<double>> matrix;

class MatrixOperation
{
  protected:

    matrix combine(const matrix& input, const matrix& id)
    {
        matrix result;
        int size = input.size();

        for (int i = 0; i < size; i++)
        {
            vector<double> line;
            for (int j = 0; j < size; j++)
                line.push_back(input[i][j]);

            for (int j = 0; j < size; j++)
                line.push_back(id[i][j]);

            result.push_back(line);
        }

        return result;
    }

    matrix init(int row_count, int col_count)
    {
        matrix result;

        for (int i = 0; i < row_count; i++)
        {
            vector<double> row;
            for (int j = 0; j < col_count; j++)
                row.push_back(0);

            result.push_back(row);
        }

        return result;
    }

    matrix make_leading1(matrix& input)
    {
        int row_count = input.size();
        int col_count = input[0].size();

        for (int i = 0; i < row_count; i++)
        {
            for (int j = 0; j < col_count; j++)
            {
                if (input[i][j] == 1)
                    break;

                if (input[i][j] != 0)
                {
                    double t = 1 / input[i][j];
                    for (int k = j; k< col_count;k++)
                        input[i][k] *= t;

                    break;
                }
            }
        }

        return input;
    }

    matrix forward_elimination(matrix& input)
    {
        int col_count = input[0].size();
        int row_count = input.size();

        for (int i = 0; i < row_count; i++)
        {
            for (int j = 0; j < col_count; j++)
            {
                double tmp = input[j][i] / input[i][i];

                for (int k = i; k < col_count; k++)
                    input[j][k] -= tmp * input[i][k];
            }
        }

        return input;
    }

    matrix backward_elimination(matrix& input)
    {
        int col_count = input[0].size();
        int row_count = input.size();

        for (int i = col_count - 2; i > 0; i--) // 2 1
        {
            for (int j = i-1; j >= 0; j--) // 1 0 //
            {
                double t = input[j][i] / input[i][i];
                for (int k = i ; k < col_count; i++) // 2 3 // 1 2 3
                    input[j][k] -= t * input[j][k];
            }
        }

        return input;
    }

    tuple<matrix,matrix > scatter(const matrix& input)
    {
        tuple<matrix ,matrix > result;

        int col_count = input[0].size();
        int row_count = input.size();
        matrix m1,m2;
        m1 = init(row_count , col_count / 2);
        m2 = init(row_count , col_count / 2);

        for (int i = 0; i < row_count; i++)
        {
            for (int j = 0; j < row_count; j++)
            {
                // 최초입력 : 초기 행렬
                m1[i][j] = input[i][j];
                // 최초입력 : 단위행렬
                m2[i][j] = input[i][j+row_count];
            }
        }

        return make_tuple(m1,m2);
    }
};

class GausJordan : MatrixOperation
{
  public:
    tuple<matrix, matrix> elimitate(const matrix& left, const matrix& right)
    {
        tuple<matrix ,matrix > result;

        matrix combined = MatrixOperation::combine(left,right) ;
        int row_count = combined.size();
        int col_count = combined[0].size();

        // forward elimination
        combined = MatrixOperation::forward_elimination(combined);

        // make leading 1 function
        combined = MatrixOperation::make_leading1(combined);

        // backward elimination
        combined = MatrixOperation::backward_elimination(combined);

        result = scatter(combined);

        return result;
    }
};

class Matrix : public GausJordan
{
  public:
    Matrix(const matrix& in)
    {
        input = in;
        size = in.size();
        identity_matrix = make_id_matrix();
    }

    //역행렬을 구하고 반환해준다.
    matrix get_inverted()
    {
        matrix in = this->input;
        matrix id = this->identity_matrix;

        //오른쪽 값이 가우스-조던 소거법이 적용된 단위행렬이 된다.
        tuple<matrix, matrix> calculated = GausJordan::elimitate(in,id);
        matrix result = get<1>(calculated);

        return result;
    }

  private:
    matrix init_id_matrix()
    {
        matrix result;

        for (int i = 0; i < size; i++)
        {
            vector<double> line;
            for (int j = 0; j < size; j++)
                line.push_back(0);

            result.push_back(line);
        }

        return result;
    }

    // 단위 행렬 만들기
    matrix make_id_matrix()
    {
        matrix result = init_id_matrix();

        for (int i = 0; i < size; i++)
            result[i][i] = 1;

        return result;
    }

  private:
    int size;
    matrix input;
    matrix identity_matrix{};
};

void printMatrix(const matrix& input)
{
    int size = input.size();
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
            cout << input[i][j] << " " ;

        cout << endl;
    }
}

int main()
{
    matrix m1 = {{1,2},{1,3}};
    //matrix m2 = {{3,2},{2,2}};
    //result = 3 -2
    //         -1 1

    Matrix A(m1);
    matrix inverse_m1 = A.get_inverted();

    printMatrix(inverse_m1);

    return 0;
}
