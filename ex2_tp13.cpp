
#include <iostream>
using namespace std;

template <typename T, int N, int M>
class Matrice {
private:
    T data[N][M];

public:
    // Constructeur par defaut
    Matrice() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                data[i][j] = 0;
            }
        }
    }

    // Constructeur avec liste d'initialisation
    Matrice(const T valeurs[N][M]) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                data[i][j] = valeurs[i][j];
            }
        }
    }

    // Acces a un element
    T& operator()(int i, int j) {
        return data[i][j];
    }

    const T& operator()(int i, int j) const {
        return data[i][j];
    }

    // Addition de deux matrices
    Matrice operator+(const Matrice& autre) const {
        Matrice resultat;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                resultat.data[i][j] = data[i][j] + autre.data[i][j];
            }
        }

        return resultat;
    }

    // Multiplication de matrices
    template <int P>
    Matrice<T, N, P> operator*(const Matrice<T, M, P>& autre) const {
        Matrice<T, N, P> resultat;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < P; j++) {
                resultat(i, j) = 0;

                for (int k = 0; k < M; k++) {
                    resultat(i, j) += data[i][k] * autre(k, j);
                }
            }
        }

        return resultat;
    }

    // Operateur d'affichage
    friend ostream& operator<<(ostream& os, const Matrice& matrice) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                os << matrice.data[i][j] << "\t";
            }
            os << endl;
        }

        return os;
    }
};

// Programme principal
int main() {

    // Test avec les entiers
    cout << "===== MATRICES INT =====" << endl;

    Matrice<int, 2, 2> A;
    A(0, 0) = 1;
    A(0, 1) = 2;
    A(1, 0) = 3;
    A(1, 1) = 4;

    Matrice<int, 2, 2> B;
    B(0, 0) = 5;
    B(0, 1) = 6;
    B(1, 0) = 7;
    B(1, 1) = 8;

    cout << "Matrice A :" << endl << A;
    cout << "Matrice B :" << endl << B;

    Matrice<int, 2, 2> C = A + B;

    cout << "Addition A + B :" << endl << C;

    Matrice<int, 2, 2> D = A * B;

    cout << "Multiplication A * B :" << endl << D;


    // Test avec double
    cout << "\n===== MATRICES DOUBLE =====" << endl;

    Matrice<double, 2, 2> X;
    X(0, 0) = 1.5;
    X(0, 1) = 2.5;
    X(1, 0) = 3.5;
    X(1, 1) = 4.5;

    Matrice<double, 2, 2> Y;
    Y(0, 0) = 1.0;
    Y(0, 1) = 2.0;
    Y(1, 0) = 3.0;
    Y(1, 1) = 4.0;

    cout << "Matrice X :" << endl << X;
    cout << "Matrice Y :" << endl << Y;

    Matrice<double, 2, 2> Z = X + Y;

    cout << "Addition X + Y :" << endl << Z;

    Matrice<double, 2, 2> W = X * Y;

    cout << "Multiplication X * Y :" << endl << W;

    return 0;
}
