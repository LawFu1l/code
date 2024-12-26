#include <vector>
#include <iostream>
#include <ostream>
#include <format>

using namespace std;

/*  학습 범위: 선형 대수
 *  학습 목표: 행렬의 연산 전 과정 연습
 */

// 계수들의 배열
using Matrix = vector<vector<double>>;
using Vector = vector<double>;

// GaussJordan
class GaussJordan
{

public:
    // 계수에 대한 배열, 변수에 대한 배열을 받는다.
    // 계수 2차원 배열, 변수 2차원 배열을 준비하자.

    GaussJordan(const Matrix& coeff, const Vector& constant)
    {
        augmented_matrix = make_augmented_system(coeff, constant);

        row_count = augmented_matrix.size();
        col_count = augmented_matrix[0].size();
    }

    Matrix make_augmented_system(const Matrix& coeff, const Vector& constant)  // 6 4
    {
        auto augmented = init(coeff, 0.0);

        const int col_count = coeff[0].size() + 1;
        for (int i = 0; i < constant.size(); i++)
            for (int j = 0; j < col_count; j++)
                augmented[i][j] = j < col_count - 1 ? coeff[i][j] : constant[i];

        return augmented;
    }

    static auto init(const Matrix& input, double val=0.0) -> Matrix
    {
        Matrix result;
        const int row_count = input.size();
        const int col_count = input[0].size() + 1;

        for (int i = 0; i < row_count; i++)
            result.emplace_back(col_count, val);

        return result;
    }

    // Remark
    // Algorithm of Gauss Jordan Elimination. 
    // works only for the equations with actual answer,
    //
    void solve()
    {
        forward_elimination();

        make_leading1();

        backward_elimination();
    }

private:
    void forward_elimination()
    {
        for (int i = 0; i < col_count - 1; i++)
        {
            for (int j = i+1; j < row_count; j++)
            {
                const double ratio = augmented_matrix[j][i] / augmented_matrix[i][i];
                for (int k = i; k < col_count; k++)
                    augmented_matrix[j][k] -= ratio * augmented_matrix[i][k];
            }
        }
    }

    void backward_elimination()
    {
        for (int i = col_count - 2; i > 0; i--)
        {
            for (int j = i-1; j >= 0; j--)
            {
                const double ratio = augmented_matrix[j][i] / augmented_matrix[i][i];
                for (int k = i ; k < col_count; k++)
                    augmented_matrix[j][k] -= ratio * augmented_matrix[i][k];
            }
        }
    }

    void make_leading1()
    {
        for (int i = 0; i < row_count; i++)
        {
            for (int j = 0; j < col_count; j++)
            {
                auto cur = augmented_matrix[i][j];
                if (cur == 1) break;
                if (cur == 0) continue;;

                const double ratio = 1 / cur;
                for (int k = j; k < col_count; k++)
                    augmented_matrix[i][k] *= ratio;

                break;
            }
        }
    }

    friend ostream& operator << (ostream& os, const GaussJordan& m)
    {
        for (int i = 0; i < m.row_count; i++)
        {
            os << "{ " ;
            for (int j = 0; j < m.col_count - 1; j++)
                os << format("{: .2f} ", m.augmented_matrix[i][j]);

            os << format(" | {: .2f} ", m.augmented_matrix[i][m.col_count-1]);

            os << " }" << endl;
        }

        return os;
    }

private:
    // Dimension of given matrix
    int row_count, col_count;

    // Augmentation of matrix and constant
    Matrix augmented_matrix;
};

int main()
{
    const auto coeff1 = vector<double>{  2,   1, -1};
    const auto coeff2 = vector<double>{ -3,   1,  2};
    const auto coeff3 = vector<double>{ -2,   1,  2};
    Matrix Cy{coeff1, coeff2, coeff3};

    auto con = vector<double>{  8, -11, -3};
    GaussJordan y(Cy, con);
    cout << y << endl;

    y.solve();

    cout << y << endl;

    return 0;
}
