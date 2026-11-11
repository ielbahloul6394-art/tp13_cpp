
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <concepts>
using namespace std;

// Concept Sortable
template<typename T>
concept Sortable = requires(T a, T b) {
    { a < b } -> convertible_to<bool>;
};

// Comparateur croissant
template<typename T>
struct Asc {
    bool operator()(const T& a, const T& b) const {
        return a < b;
    }
};

// Comparateur decroissant
template<typename T>
struct Desc {
    bool operator()(const T& a, const T& b) const {
        return a > b;
    }
};

// Fonction QuickSort
template<Sortable T, typename Comp = less<T>>
void quickSort(vector<T>& v, Comp comp = Comp{}) {

    if (v.size() <= 1) {
        return;
    }

    T pivot = v[v.size() / 2];

    vector<T> gauche;
    vector<T> droite;
    vector<T> milieu;

    for (const T& element : v) {
        if (comp(element, pivot)) {
            gauche.push_back(element);
        }
        else if (comp(pivot, element)) {
            droite.push_back(element);
        }
        else {
            milieu.push_back(element);
        }
    }

    quickSort(gauche, comp);
    quickSort(droite, comp);

    v.clear();

    for (const T& element : gauche)
        v.push_back(element);

    for (const T& element : milieu)
        v.push_back(element);

    for (const T& element : droite)
        v.push_back(element);
}

// Structure utilisateur
struct Etudiant {
    string nom;
    int note;

    Etudiant(string n, int x) : nom(n), note(x) {}

    bool operator<(const Etudiant& autre) const {
        return note < autre.note;
    }

    bool operator>(const Etudiant& autre) const {
        return note > autre.note;
    }
};

// Fonction d'affichage pour les entiers et les chaines
template<typename T>
void afficher(const vector<T>& v) {
    for (const T& element : v) {
        cout << element << " ";
    }
    cout << endl;
}

// Test unitaire
template<typename T>
bool estTrie(const vector<T>& v) {
    for (size_t i = 1; i < v.size(); i++) {
        if (v[i] < v[i - 1]) {
            return false;
        }
    }
    return true;
}

// Affichage des etudiants
void afficherEtudiants(const vector<Etudiant>& v) {
    for (const Etudiant& e : v) {
        cout << e.nom << " : " << e.note << endl;
    }
}

int main() {

    cout << "===== TEST VECTOR INT =====" << endl;

    vector<int> nombres = {8, 3, 6, 1, 9, 2};

    quickSort(nombres, Asc<int>());

    afficher(nombres);

    cout << "Test croissant : "
         << (estTrie(nombres) ? "REUSSI" : "ECHEC") << endl;


    cout << "\n===== TEST VECTOR STRING =====" << endl;

    vector<string> mots = {"Python", "Java", "C++", "PHP"};

    quickSort(mots);

    afficher(mots);

    cout << "Test string : "
         << (estTrie(mots) ? "REUSSI" : "ECHEC") << endl;


    cout << "\n===== TEST DECROISSANT =====" << endl;

    vector<int> valeurs = {4, 9, 2, 7, 1};

    quickSort(valeurs, Desc<int>());

    afficher(valeurs);


    cout << "\n===== TEST ETUDIANTS =====" << endl;

    vector<Etudiant> etudiants = {
        Etudiant("Sara", 15),
        Etudiant("Imane", 18),
        Etudiant("Salma", 12),
        Etudiant("Nadia", 16)
    };

    quickSort(etudiants, Asc<Etudiant>());

    afficherEtudiants(etudiants);

    cout << "\n===== FIN DES TESTS =====" << endl;

    return 0;
}
