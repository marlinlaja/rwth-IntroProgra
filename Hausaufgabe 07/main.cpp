#include <iostream>
#include <array>
#include <vector>


template<std::size_t I>
std::vector<std::vector<double>> tensor_vector_kont_3_1(const std::vector<std::vector<std::array<double, I>>>& T,const std::vector<double>& w)
{
    // TODO 4: Tensor-Vektor Kontraktion
    //         Tensorkontraktion auf 3. Dimension von T mit 1. Dimension von w - mittels Iteratoren.
    //         Tipp: Überlege zuerst, welche Dimensionen das Ergebnis hat.
    std::vector<std::vector<double>> C(T.size(), std::vector<double>(T[0].size()));
    auto it_C_i = C.begin();

    for (auto cit_T_i = T.cbegin(); cit_T_i != T.cend(); cit_T_i++, it_C_i++)
    {
        auto it_C_j = it_C_i->begin();
        for (auto cit_T_j  = cit_T_i->cbegin(); cit_T_j != cit_T_i->cend(); cit_T_j++, it_C_j++)
        {
            auto cit_w = w.cbegin();
            for (auto cit_T_k  = cit_T_j->cbegin(); cit_T_k != cit_T_j->cend(); cit_T_k++, cit_w++)
            {
                *it_C_j += (*cit_w) * (*cit_T_k);
            }
        }
    }
    return C;
}


template<std::size_t I> 
std::vector<double> tensor_matrix_kont_23_12(const std::vector<std::vector<std::array<double, I>>>& T, const std::vector<std::vector<double>>& M) 
{
    // TODO 5:  Tensor-Matrix Kontraktion
    //          Tensorkontraktion auf 2. und 3. Dimension von T mit 1. und 2. Dimension von M - mittels Iteratoren.
    //          Tipp: Überlege zuerst, welche Dimensionen das Ergebnis hat.
    std::vector<double> z(T.size());
    auto it_z = z.begin();

    for (auto cit_T_i = T.cbegin(); cit_T_i != T.cend(); cit_T_i++, it_z++)
    {
        auto cit_M_i = M.cbegin();
        for (auto cit_T_j  = cit_T_i->cbegin(); cit_T_j != cit_T_i->cend(); cit_T_j++, cit_M_i++)
        {
            auto cit_M_j = cit_M_i->cbegin();
            for (auto cit_T_k = cit_T_j->cbegin(); cit_T_k != cit_T_j->cend(); cit_T_k++, cit_M_j++)
            {
                *it_z += (*cit_M_j) * (*cit_T_k);
            }
        }
    }
    return z;
}


void fillMatrix(std::vector<std::vector<double>>& matrix)
{
    for (size_t i = 0; i < matrix.size(); i++)
    {
        for (size_t j = 0; j < matrix[i].size(); j++)
        {
            if (i == j) {
                matrix[i][j] = 2;
            } else {
                matrix[i][j] = 1;
            }
        }
    }
}


template<std::size_t I> 
void fillTensor(std::vector<std::vector<std::array<double, I>>>& tensor)
{      
    for (size_t i = 0; i < tensor.size(); i++)
    {
        for (size_t j = 0; j < tensor[i].size(); j++)
        {
            for (size_t k = 0; k < I; k++)
            {
                if (i == j && i == k) {
                    tensor[i][j][k] = 2;
                } else {
                    tensor[i][j][k] = 1;
                }
            } 
        }
    }
}


void printVector(const std::vector<double> vector)
{   
    std::cout << "[";
    for (size_t i = 0; i < vector.size(); i++)
    {
        std::cout << vector[i];
        if (i < vector.size()-1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}


void printMatrix(const std::vector<std::vector<double>> matrix)
{
    for (size_t i = 0; i < matrix.size(); i++)
    {
        printVector(matrix[i]);
    }
}


int main()
{
    // TODO 1: Welche Dimensionen hat Q ?
    // Q element aus R^d1xd3 => dim(Q) = 2


    // TODO 2: T, M, S initialisieren. Legen Sie "?" passend fest.
    std::vector<double> w(4, 1);
    std::vector<std::vector<double>> M(2, std::vector<double>(3));
    std::vector<std::vector<double>> S(3, std::vector<double>(4));
    std::vector<std::vector<std::array<double, 4>>> T(2, std::vector<std::array<double, 4>>(3));


    // TODO 3: T, M, S mit Einträgen füllen
    fillMatrix(M);
    fillMatrix(S);
    fillTensor(T);


    // (TODO 4+5 sind in den Funktionen oben im Code)


    // TODO 6: Aufrufen und auf der Kommandozeile ausgeben:
    std::cout << "Tw:" << std::endl;
    std::vector<std::vector<double>> C = tensor_vector_kont_3_1(T, w);
    printMatrix(C);

    std::cout << "TS:" << std::endl;
    std::vector<double> z = tensor_matrix_kont_23_12(T, S);
    printVector(z);
}