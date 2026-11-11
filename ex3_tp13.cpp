
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

// Exception StackOverflow
class StackOverflow : public exception {
public:
    const char* what() const noexcept override {
        return "Erreur : la pile est pleine !";
    }
};

// Exception StackUnderflow
class StackUnderflow : public exception {
public:
    const char* what() const noexcept override {
        return "Erreur : la pile est vide !";
    }
};

// Classe Stack generique
template <typename T>
class Stack {
private:
    unique_ptr<T[]> data;
    size_t capacity;
    size_t top;

public:
    // Constructeur avec capacite par defaut
    Stack(size_t cap = 100)
        : data(new T[cap > 0 ? cap : 1]),
          capacity(cap > 0 ? cap : 1),
          top(0) {
    }

    // Constructeur avec iterateurs
    template <typename Iterator>
    Stack(Iterator begin, Iterator end)
        : data(nullptr), capacity(0), top(0) {

        size_t count = 0;

        for (Iterator it = begin; it != end; ++it) {
            count++;
        }

        capacity = (count > 0) ? count : 1;
        data.reset(new T[capacity]);

        for (Iterator it = begin; it != end; ++it) {
            push(*it);
        }
    }

    // Ajouter un element
    void push(const T& valeur) {
        if (top >= capacity) {
            throw StackOverflow();
        }

        data[top] = valeur;
        top++;
    }

    // Supprimer le sommet
    void pop() {
        if (empty()) {
            throw StackUnderflow();
        }

        top--;
    }

    // Consulter le sommet
    const T& peek() const {
        if (empty()) {
            throw StackUnderflow();
        }

        return data[top - 1];
    }

    // Verifier si la pile est vide
    bool empty() const {
        return top == 0;
    }

    // Nombre d'elements
    size_t size() const {
        return top;
    }

    // Capacite
    size_t getCapacity() const {
        return capacity;
    }
};

// Programme principal
int main() {

    cout << "===== TEST STACK INT =====" << endl;

    Stack<int> pile(5);

    try {
        pile.push(10);
        pile.push(20);
        pile.push(30);

        cout << "Sommet : " << pile.peek() << endl;

        pile.pop();

        cout << "Apres pop, sommet : " << pile.peek() << endl;

        pile.push(40);
        pile.push(50);
        pile.push(60);

        // Test StackOverflow
        pile.push(70);

    }
    catch (const StackOverflow& e) {
        cout << e.what() << endl;
    }

    cout << "\n===== TEST STACK STRING =====" << endl;

    Stack<string> textes(3);

    textes.push("Java");
    textes.push("C++");
    textes.push("Python");

    cout << "Sommet : " << textes.peek() << endl;

    textes.pop();

    cout << "Nouveau sommet : " << textes.peek() << endl;


    cout << "\n===== TEST ITERATEURS =====" << endl;

    vector<int> nombres = {1, 2, 3, 4, 5};

    Stack<int> pile2(nombres.begin(), nombres.end());

    cout << "Sommet : " << pile2.peek() << endl;
    cout << "Nombre d'elements : " << pile2.size() << endl;


    cout << "\n===== TEST STACKUNDERFLOW =====" << endl;

    Stack<int> pileVide(3);

    try {
        pileVide.pop();
    }
    catch (const StackUnderflow& e) {
        cout << e.what() << endl;
    }


    cout << "\n===== TEST GRAND NOMBRE D'OBJETS =====" << endl;

    Stack<int> grandePile(100000);

    for (int i = 0; i < 100000; i++) {
        grandePile.push(i);
    }

    cout << "Nombre d'elements : " << grandePile.size() << endl;
    cout << "Sommet : " << grandePile.peek() << endl;

    cout << "\nProgramme termine avec succes !" << endl;

    return 0;
}
