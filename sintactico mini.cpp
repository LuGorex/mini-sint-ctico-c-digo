#include <iostream>
#include <stack>
#include <string>

using namespace std;

// Declaración de los arreglos globales
int idReglas[2] = {2, 2};
int lonReglas[2] = {3, 0};

class Pila {
private:
    stack<int> pila;
public:
    void push(int valor) {
        pila.push(valor);
    }

    int pop() {
        int valor = pila.top();
        pila.pop();
        return valor;
    }

    int top() {
        return pila.top();
    }

    void muestra() {
        stack<int> temp = pila;
        while (!temp.empty()) {
            cout << temp.top() << " ";
            temp.pop();
        }
        cout << endl;
    }
};

class Lexico {
private:
    string entrada;
    int indice;
public:
    int tipo;
    char simbolo;

    Lexico(string cadena) : entrada(cadena), indice(0) {}

    bool terminado() {
        return indice >= entrada.size();
    }

    void sigSimbolo() {
        if (!terminado()) {
            simbolo = entrada[indice++];
            if (isalpha(simbolo))
                tipo = 0; // tipo para identificador
            else if (simbolo == '+')
                tipo = 1; // tipo para '+'
            else
                tipo = 2; // tipo para '$'
        } else {
            simbolo = '$'; // símbolo de fin de cadena
            tipo = 2;
        }
    }
};

// Tabla LR(1) para los ejercicios
int tablaLR[5][3] = {
    {2, 0, 1},
    {0, -1, 0},
    {2, 3, -2},
    {2, 0, 4},
    {0, -1, 0}
};

// Ejemplo 1
void ejemplo1() {
    Pila pila;
    pila.push(2);
    pila.push(3);
    pila.push(4);
    pila.push(5);
    pila.muestra();

    cout << pila.top() << endl;
    cout << pila.top() << endl;

    cout << pila.pop() << endl;
    cout << pila.pop() << endl;
}

// Ejemplo 2
void ejemplo2() {
    Lexico lexico("+-+");
    while (!lexico.terminado()) {
        lexico.sigSimbolo();
        cout << lexico.simbolo << endl;
    }
}

// Ejercicio 1
void ejercicio1() {
    Lexico lexico("a+b");
    while (!lexico.terminado()) {
        lexico.sigSimbolo();
        cout << lexico.simbolo << endl;
    }
}

// Ejercicio 2
void ejercicio2() {
    Pila pila;
    int fila, columna, accion;
    bool aceptacion = false;
    Lexico lexico("a+b");

    pila.push(2); // PESOS
    pila.push(0);
    lexico.sigSimbolo();

    while (!aceptacion) {
        fila = pila.top();
        columna = lexico.tipo;
        accion = tablaLR[fila][columna];

        pila.muestra();
        cout << "entrada: " << lexico.simbolo << endl;
        cout << "accion: " << accion << endl;

        if (accion > 0) { // desplazamiento
            pila.push(lexico.tipo);
            pila.push(accion);
            lexico.sigSimbolo();
        } else if (accion < 0) { // reducción
            int regla = -accion - 1;
            int idNoTerminal = idReglas[regla];
            int longitud = lonReglas[regla];

            for (int i = 0; i < 2 * longitud; ++i) {
                pila.pop();
            }

            fila = pila.top();
            columna = idNoTerminal;
            accion = tablaLR[fila][columna];

            pila.push(idNoTerminal);
            pila.push(accion);
        } else { // error
            cout << "Error: acción inválida." << endl;
            break;
        }

        aceptacion = accion == -1;
        if (aceptacion) {
            cout << "aceptación" << endl;
        }
    }
}

int main() {
    //ejemplo1();
    //ejemplo2();

    // Ejecutar ejercicios
    cout << "ejercicio 1"<< endl;
    ejercicio1();
    cout << "ejercicio 1"<< endl;
    ejercicio2();

    return 0;
}
