#include <iostream>
#include <string>

using namespace std;

class ListaEnlazada {
private:
    class Elemento {  // Clase interna en lugar de struct
    public:
        int id;
        string nombre;
        int prioridad;
        Elemento* siguiente;
        
        Elemento(int id, string nombre, int prioridad) 
            : id(id), nombre(nombre), prioridad(prioridad), siguiente(NULL) {}  // Cambiado a NULL
    };

    Elemento* inicio;
    int idContador;

public:
    ListaEnlazada() : inicio(NULL), idContador(1) {}  // Cambiado a NULL

    void insertar(string nombre, int prioridad) {
        Elemento* nuevo = new Elemento(idContador++, nombre, prioridad);
        
        if (inicio == NULL) {  // Cambiado a NULL
            inicio = nuevo;
        } else {
            Elemento* actual = inicio;
            while (actual->siguiente != NULL) {  // Cambiado a NULL
                actual = actual->siguiente;
            }
            actual->siguiente = nuevo;
        }
    }

    void mostrar() {
        if (inicio == NULL) {  // Cambiado a NULL
            cout << "Lista vacía" << endl;
            return;
        }

        Elemento* actual = inicio;
        while (actual != NULL) {  // Cambiado a NULL
            cout << "ID: " << actual->id 
                 << ", Nombre: " << actual->nombre 
                 << ", Prioridad: " << actual->prioridad << endl;
            actual = actual->siguiente;
        }
    }

    void eliminar() {
        Elemento* actual = inicio;
        while (actual != NULL) {  // Cambiado a NULL
            Elemento* siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        }
        inicio = NULL;  // Cambiado a NULL
    }

    ~ListaEnlazada() {
        eliminar();
    }
};

int main() {
    ListaEnlazada lista;
    
    lista.insertar("Proceso A", 1);
    lista.insertar("Proceso B", 2);
    lista.insertar("Proceso C", 3);
    
    lista.mostrar();
    
    return 0;
}
