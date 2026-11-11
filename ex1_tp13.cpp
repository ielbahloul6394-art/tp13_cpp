
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

template <class T>
class ArrayDyn {
private:
    T* data;
    size_t taille;
    size_t capacite;

public:
    // Constructeur par defaut
    ArrayDyn() : data(nullptr), taille(0), capacite(0) {}

    // Constructeur avec capacite
    ArrayDyn(size_t cap) : taille(0), capacite(cap) {
        data = (capacite > 0) ? new T[capacite] : nullptr;
    }

    // Constructeur de copie
    ArrayDyn(const ArrayDyn& autre)
        : taille(autre.taille), capacite(autre.capacite) {
        data = (capacite > 0) ? new T[capacite] : nullptr;

        for (size_t i = 0; i < taille; i++) {
            data[i] = autre.data[i];
        }
    }

    // Operateur d'affectation
    ArrayDyn& operator=(const ArrayDyn& autre) {
        if (this != &autre) {
            T* nouveau = (autre.capacite > 0)
                ? new T[autre.capacite] : nullptr;

            for (size_t i = 0; i < autre.taille; i++) {
                nouveau[i] = autre.data[i];
            }

            delete[] data;

            data = nouveau;
            taille = autre.taille;
            capacite = autre.capacite;
        }
        return *this;
    }

    // Destructeur
    ~ArrayDyn() {
        delete[] data;
    }

    // Agrandir la capacite
    void agrandir() {
        size_t nouvelleCapacite = (capacite == 0) ? 2 : capacite * 2;
        T* nouveau = new T[nouvelleCapacite];

        for (size_t i = 0; i < taille; i++) {
            nouveau[i] = data[i];
        }

        delete[] data;
        data = nouveau;
        capacite = nouvelleCapacite;
    }

    // Ajouter un element
    void push_back(const T& valeur) {
        if (taille == capacite) {
            agrandir();
        }

        data[taille] = valeur;
        taille++;
    }

    // Supprimer le dernier element
    void pop_back() {
        if (taille == 0) {
            throw out_of_range("Le tableau est vide");
        }
        taille--;
    }

    // Acces aux elements
    T& operator[](size_t index) {
        if (index >= taille) {
            throw out_of_range("Indice invalide");
        }
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= taille) {
            throw out_of_range("Indice invalide");
        }
        return data[index];
    }

    // Iterateur interne
    class Iterator {
    private:
        T* ptr;

    public:
        Iterator(T* p = nullptr) : ptr(p) {}

        T& operator*() const {
            return *ptr;
        }

        Iterator& operator++() {
            ++ptr;
            return *this;
        }

        Iterator& operator--() {
            --ptr;
            return *this;
        }

        bool operator!=(const Iterator& autre) const {
            return ptr != autre.ptr;
        }
    };

    // Debut et fin
    Iterator begin() {
        return Iterator(data);
    }

    Iterator end() {
        return Iterator(data + taille);
    }

    size_t getTaille() const {
        return taille;
    }
};

// Classe Produit
class Produit {
private:
    string nom;
    double prix;

public:
    Produit(string n, double p) : nom(n), prix(p) {}

    void afficher() const {
        cout << nom << " : " << prix << " DH" << endl;
    }
};

// Fonction principale
int main() {

    cout << "=== TEST INT ===" << endl;

    ArrayDyn<int> nombres;
    nombres.push_back(10);
    nombres.push_back(20);
    nombres.push_back(30);

    for (auto& e : nombres) {
        cout << e << " ";
    }

    cout << endl;

    cout << "\n=== TEST STRING ===" << endl;

    ArrayDyn<string> textes;
    textes.push_back("Java");
    textes.push_back("C++");
    textes.push_back("Python");

    for (auto& e : textes) {
        cout << e << endl;
    }

    cout << "\n=== TEST PRODUIT ===" << endl;

    ArrayDyn<Produit> produits;
    produits.push_back(Produit("Ordinateur", 5000));
    produits.push_back(Produit("Clavier", 150));

    for (auto& e : produits) {
        e.afficher();
    }

    cout << "\n=== TEST POP_BACK ===" << endl;

    nombres.pop_back();

    for (auto& e : nombres) {
        cout << e << " ";
    }

    cout << endl;

    cout << "\n=== TEST COPIE ===" << endl;

    ArrayDyn<int> copie(nombres);

    for (auto& e : copie) {
        cout << e << " ";
    }

    cout << endl;

    cout << "\n=== TEST OPERATOR[] ===" << endl;
    cout << nombres[0] << endl;

    return 0;
}
