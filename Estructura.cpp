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
// Clase para Lista Enlazada de Procesos
class ListaProcesos {
private:
    Proceso* cabeza;
    int contadorId;
public:
    ListaProcesos() : cabeza(NULL), contadorId(1) {}
    
    // Agregar proceso a la lista
    void agregarProceso(string nombre, int prioridad) {
        Proceso* nuevo = new Proceso;
        nuevo->id = contadorId++;
        nuevo->nombre = nombre;
        nuevo->prioridad = prioridad;
        nuevo->estado = "En espera";
        nuevo->siguiente = cabeza;
        cabeza = nuevo;
        cout << "Proceso creado con ID: " << nuevo->id << endl;
    }
    
    // Buscar proceso por ID
    Proceso* buscarProceso(int id) {
        Proceso* actual = cabeza;
        while (actual != NULL) {
            if (actual->id == id) return actual;
            actual = actual->siguiente;
        }
        return NULL;
    }
    
    // Mostrar todos los procesos
    void mostrarProcesos() {
        Proceso* actual = cabeza;
        while (actual != NULL) {
            cout << "\nID: " << actual->id 
                 << "\nNombre: " << actual->nombre 
                 << "\nEstado: " << actual->estado
                 << "\nPrioridad: " << actual->prioridad << endl;
            actual = actual->siguiente;
        }
    }
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
// Menú principal
void mostrarMenu() {
    cout << "\n=== GESTOR DE PROCESOS COMPLETO ===";
    cout << "\n1. Crear nuevo proceso";
    cout << "\n2. Listar todos los procesos";
    cout << "\n3. Apilar proceso";
    cout << "\n4. Desapilar proceso";
    cout << "\n5. Mostrar pila";
    cout << "\n6. Encolar proceso";
    cout << "\n7. Desencolar proceso";
    cout << "\n8. Mostrar cola";
    cout << "\n9. Cambiar estado de proceso";
    cout << "\n10. Salir";
    cout << "\nSeleccione opcion: ";
}
int main() {
    ListaProcesos lista;
    PilaProcesos pila;
    ColaProcesos cola;
    int opcion;
    
    do {
        mostrarMenu();
        cin >> opcion;
        cin.ignore(); // Limpiar buffer
        
        switch(opcion) {
            case 1: {
                string nombre;
                int prioridad;
                cout << "Nombre del proceso: ";
                getline(cin, nombre);
                cout << "Prioridad (1-5): ";
                cin >> prioridad;
                lista.agregarProceso(nombre, prioridad);
                break;
            }
            case 2: {
                cout << "\n=== LISTA DE PROCESOS ===";
                lista.mostrarProcesos();
                break;
            }
            case 3: {
                int id;
                cout << "ID del proceso a apilar: ";
                cin >> id;
                Proceso* p = lista.buscarProceso(id);
                if (p != NULL) {
                    pila.apilar(p);
                } else {
                    cout << "Proceso no encontrado.\n";
                }
                break;
            }
            case 4: {
                Proceso* p = pila.desapilar();
                if (p != NULL) {
                    cout << "Proceso " << p->id << " desapilado.\n";
                } else {
                    cout << "Pila vacia.\n";
                }
                break;
            }
            case 5: {
                cout << "\n=== CONTENIDO DE LA PILA ===";
                pila.mostrarPila();
                break;
            }
            case 6: {
                int id;
                cout << "ID del proceso a encolar: ";
                cin >> id;
                Proceso* p = lista.buscarProceso(id);
                if (p != NULL) {
                    cola.encolar(p);
                } else {
                    cout << "Proceso no encontrado.\n";
                }
                break;
            }
            case 7: {
                Proceso* p = cola.desencolar();
                if (p != NULL) {
                    cout << "Proceso " << p->id << " desencolado.\n";
                } else {
                    cout << "Cola vacia.\n";
                }
                break;
            }
            case 8: {
                cout << "\n=== CONTENIDO DE LA COLA ===";
                cola.mostrarCola();
                break;
            }
            case 9: {
                int id;
                string nuevoEstado;
                cout << "ID del proceso a actualizar: ";
                cin >> id;
                Proceso* p = lista.buscarProceso(id);
                if (p != NULL) {
                    cout << "Nuevo estado: ";
                    cin.ignore();
                    getline(cin, nuevoEstado);
                    p->estado = nuevoEstado;
                    cout << "Estado actualizado.\n";
                } else {
                    cout << "Proceso no encontrado.\n";
                }
                break;
            }
            case 10:
                cout << "Saliendo del sistema...\n";
                break;
            default:
                cout << "Opcion no valida.\n";
        }
    } while (opcion != 10);
    
    return 0;
}