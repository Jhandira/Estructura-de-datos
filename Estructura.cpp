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

