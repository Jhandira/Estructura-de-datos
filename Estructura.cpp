#include <iostream>
#include <string>
using namespace std;

// Estructura para un proceso
struct Proceso {
    int id;
    string nombre;
    string estado;
    int prioridad;
    Proceso* siguiente;  // <-- espacio corregido aquí
};

// Clase para Cola de Procesos (FIFO)
class ColaProcesos {
private:
    Proceso* frente;
    Proceso* final;
public:
    ColaProcesos() : frente(NULL), final(NULL) {}
    
    // Encolar proceso
    void encolar(Proceso* proceso) {
        proceso->siguiente = NULL;
        if (final == NULL) {
            frente = final = proceso;
        } else {
            final->siguiente = proceso;
            final = proceso;
        }
        proceso->estado = "En cola";
        cout << "Proceso " << proceso->id << " encolado.\n";
    }
    
    // Desencolar proceso
    Proceso* desencolar() {
        if (frente == NULL) return NULL;
        Proceso* temp = frente;
        frente = frente->siguiente;
        if (frente == NULL) final = NULL;
        temp->estado = "Desencolado";
        return temp;
    }
// Mostrar cola
    void mostrarCola() {
        Proceso* actual = frente;
        while (actual != NULL) {
            cout << "ID: " << actual->id << " - " << actual->nombre << endl;
            actual = actual->siguiente;
        }
    }
};
// Clase para Pila de Procesos (LIFO)
class PilaProcesos {
private:
    Proceso* tope;
public:
    PilaProcesos() : tope(NULL) {}
    
    // Apilar proceso
    void apilar(Proceso* proceso) {
        proceso->siguiente = tope;
        tope = proceso;
        proceso->estado = "En pila";
        cout << "Proceso " << proceso->id << " apilado.\n";
    }
    
    // Desapilar proceso
    Proceso* desapilar() {
        if (tope == NULL) return NULL;
        Proceso* temp = tope;
        tope = tope->siguiente;
        temp->estado = "Desapilado";
        return temp;
    }
    
    // Mostrar pila
    void mostrarPila() {
        Proceso* actual = tope;
        while (actual != NULL) {
            cout << "ID: " << actual->id << " - " << actual->nombre << endl;
            actual = actual->siguiente;
        }
    }
};
