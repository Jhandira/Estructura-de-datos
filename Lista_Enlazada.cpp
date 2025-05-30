#include <iostream>
#include <string>

using namespace std;

class ListaEnlazada {
private:
    struct Elemento {
        int id;
        string nombre;
        int prioridad;
        Elemento* siguiente;

        Elemento(int id, string nombre, int prioridad)
            : id(id), nombre(nombre), prioridad(prioridad), siguiente(NULL) {}
    };

    Elemento* inicio;
    Elemento* fin;
    int idContador;

public:
    ListaEnlazada() : inicio(NULL), fin(NULL), idContador(1) {}

    ~ListaEnlazada() {
        eliminarTodo();
    }

    void insertar(string nombre, int prioridad) {
        Elemento* nuevo = new Elemento(idContador++, nombre, prioridad);

        if (inicio == NULL) {
            inicio = fin = nuevo;
        } else {
            fin->siguiente = nuevo;
            fin = nuevo;
        }
    }

    void mostrar() {
        if (inicio == NULL) {
            cout << "Lista vacía\n";
            return;
        }

        Elemento* actual = inicio;
        while (actual != NULL) {
            cout << "ID: " << actual->id
                 << ", Nombre: " << actual->nombre
                 << ", Prioridad: " << actual->prioridad << "\n";
            actual = actual->siguiente;
        }
    }

    Elemento* buscar(int id) {
        Elemento* actual = inicio;
        while (actual != NULL) {
            if (actual->id == id) {
                return actual;
            }
            actual = actual->siguiente;
        }
        return NULL;
    }

    bool modificar(int id, string nuevoNombre, int nuevaPrioridad) {
        Elemento* proceso = buscar(id);
        if (proceso == NULL) {
            cout << "Error: Proceso no encontrado\n";
            return false;
        }
        proceso->nombre = nuevoNombre;
        proceso->prioridad = nuevaPrioridad;
        return true;
    }

    bool eliminar(int id) {
        if (inicio == NULL) return false;

        if (inicio->id == id) {
            Elemento* temp = inicio;
            inicio = inicio->siguiente;
            if (inicio == NULL) fin = NULL;
            delete temp;
            return true;
        }

        Elemento* anterior = inicio;
        Elemento* actual = inicio->siguiente;

        while (actual != NULL) {
            if (actual->id == id) {
                anterior->siguiente = actual->siguiente;
                if (actual == fin) fin = anterior;
                delete actual;
                return true;
            }
            anterior = actual;
            actual = actual->siguiente;
        }

        return false;
    }

    void eliminarTodo() {
        Elemento* actual = inicio;
        while (actual != NULL) {
            Elemento* siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        }
        inicio = fin = NULL;
    }

    void mostrarPorPrioridad(int prioridad) {
        Elemento* actual = inicio;
        bool encontrado = false;

        while (actual != NULL) {
            if (actual->prioridad == prioridad) {
                cout << "ID: " << actual->id
                     << ", Nombre: " << actual->nombre
                     << ", Prioridad: " << actual->prioridad << "\n";
                encontrado = true;
            }
            actual = actual->siguiente;
        }

        if (!encontrado) {
            cout << "No hay procesos con prioridad " << prioridad << "\n";
        }
    }

    void mostrarProceso(int id) {
        Elemento* proceso = buscar(id);
        if (proceso != NULL) {
            cout << "Encontrado proceso " << id << ": " << proceso->nombre << "\n";
        } else {
            cout << "Proceso " << id << " no encontrado\n";
        }
    }
};

int main() {
    ListaEnlazada lista;

    lista.insertar("Proceso A", 1);
    lista.insertar("Proceso B", 2);
    lista.insertar("Proceso C", 3);
    lista.insertar("Proceso D", 2);

    cout << "=== Todos los procesos ===\n";
    lista.mostrar();
    cout << "\n";

    cout << "=== Procesos con prioridad 2 ===\n";
    lista.mostrarPorPrioridad(2);
    cout << "\n";

    if (lista.modificar(2, "Proceso B Modificado", 5)) {
        cout << "=== Después de modificar ===\n";
        lista.mostrar();
        cout << "\n";
    }

    if (lista.eliminar(3)) {
        cout << "Proceso 3 eliminado con éxito\n";
    } else {
        cout << "No se encontró el proceso 3\n";
    }
    cout << "=== Lista después de eliminar ===\n";
    lista.mostrar();
    cout << "\n";

    lista.mostrarProceso(1);

    return 0;
}

