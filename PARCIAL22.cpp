#include <iostream>
using namespace std;

struct Nodo {
    int dato;
    int prioridad;
    Nodo* siguiente;
};

struct NodoL {
    int dato;
    NodoL* siguiente;
};

struct nodoA {
    int nro;
    struct nodoA *izq, *der;
};

typedef struct nodoA *Arbol;

Arbol crearNodo(int x) {
    Arbol nuevoNodo = new(struct nodoA);
    nuevoNodo->nro = x;
    nuevoNodo->izq = NULL;
    nuevoNodo->der = NULL;
    return nuevoNodo;
}

void agregarProceso(Nodo*& pila, int dato, int prioridad);
void atenderProceso(Nodo*& pila);
void imprimirProcesos(Nodo* pila);
void agregarProcesocol(Nodo*& cola, int dato, int prioridad);
void atenderProcesocol(Nodo*& cola);
void imprimirProcesoscol(Nodo* cola);

void convertirPilaLista(Nodo* pila);
void convertirColaLista(Nodo* cola);
void convertirPilaArbol(Nodo* pila);
void convertirColaArbol(Nodo* cola);

int main() {
    Nodo* cola = NULL;
    Nodo* pila = NULL;
    int dato, prioridad;
    char opcion, opcion_menu_inicial;

    do {
        cout << "\nMENU INICIAL\n";
        cout << "1. Ingresar datos a cola\n";
        cout << "2. Ingresar datos a pila\n";
        cout << "3. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion_menu_inicial;

        switch (opcion_menu_inicial) {
            case '1':
                do {
                    cout << "\nMENU COLA\n";
                    cout << "1. Agregar proceso\n";
                    cout << "2. Atender procesos\n";
                    cout << "3. Volver al menu inicial\n";
                    cout << "4. Convertir Cola a Lista\n";
                    cout << "5. Convertir Cola a Arbol\n";
                    cout << "Seleccione una opcion: ";
                    cin >> opcion;

                    switch (opcion) {
                        case '1':
                            cout << "Ingrese el numero del proceso: ";
                            cin >> dato;
                            cout << "Ingrese la prioridad del proceso (1, 2, o 3): ";
                            cin >> prioridad;
                            agregarProcesocol(cola, dato, prioridad);
                            break;
                        case '2':
                            atenderProcesocol(cola);
                            break;
                        case '3':
                            cout << "Volviendo al menu inicial.\n";
                            break;
                        case '4':
                            convertirColaLista(cola);
                            break;
                        case '5':
                            convertirColaArbol(cola);
                            break;
                        default:
                            cout << "Opcion invalida. Por favor seleccione una opcion valida.\n";
                    }
                } while (opcion != '3');
                break;
            case '2':
                do {
                    cout << "\nMENU PILA\n";
                    cout << "1. Agregar proceso\n";
                    cout << "2. Atender procesos\n";
                    cout << "3. Volver al menu inicial\n";
                    cout << "4. Convertir a Lista\n";
                    cout << "5. Convertir a Arbol\n";
                    cout << "Seleccione una opcion: ";
                    cin >> opcion;

                    switch (opcion) {
                        case '1':
                            cout << "Ingrese el numero del proceso: ";
                            cin >> dato;
                            cout << "Ingrese la prioridad del proceso (1, 2, o 3): ";
                            cin >> prioridad;
                            agregarProceso(pila, dato, prioridad);
                            break;
                        case '2':
                            atenderProceso(pila);
                            break;
                        case '3':
                            cout << "Volviendo al menu inicial.\n";
                            break;
                        case '4':
                            convertirPilaLista(pila);
                            break;
                        case '5':
                            convertirPilaArbol(pila);
                            break;
                        default:
                            cout << "Opcion invalida. Por favor seleccione una opcion valida.\n";
                    }
                } while (opcion != '3');
                break;
            case '3':
                cout << "Saliendo del programa.\n";
                break;
            default:
                cout << "Opcion invalida. Por favor seleccione una opcion valida.\n";
        }
    } while (opcion_menu_inicial != '3');

    while (cola != NULL) {
        Nodo* aux = cola;
        cola = cola->siguiente;
        delete aux;
    }

    while (pila != NULL) {
        Nodo* aux = pila;
        pila = pila->siguiente;
        delete aux;
    }

    return 0;
}

void agregarProceso(Nodo*& pila, int dato, int prioridad) {
    if (prioridad < 1 || prioridad > 3) {
        cout << "Error: La prioridad debe ser 1, 2 o 3.\n";
        return;
    }

    Nodo* nuevo_nodo = new Nodo();
    nuevo_nodo->dato = dato;
    nuevo_nodo->prioridad = prioridad;
    nuevo_nodo->siguiente = pila;
    pila = nuevo_nodo;

    cout << "Proceso agregado correctamente a la pila.\n";
}

void atenderProceso(Nodo*& pila) {
    if (pila == NULL) {
        cout << "No hay procesos en espera en la pila.\n";
        return;
    }

    Nodo* aux = pila;
    pila = pila->siguiente;

    cout << "Atendiendo proceso: " << aux->dato << " de prioridad " << aux->prioridad << endl;
    delete aux;

    cout << "Numeros restantes en la pila:\n";
    imprimirProcesos(pila);
}

void imprimirProcesos(Nodo* pila) {
    Nodo* aux = pila;
    while (aux != NULL) {
        cout << aux->dato << " - Prioridad: " << aux->prioridad << endl;
        aux = aux->siguiente;
    }
    cout << endl;
}

void agregarProcesocol(Nodo*& cola, int dato, int prioridad) {
    if (prioridad < 1 || prioridad > 3) {
        cout << "Error: La prioridad debe ser 1, 2 o 3.\n";
        return;
    }

    Nodo* nuevo_nodo = new Nodo();
    nuevo_nodo->dato = dato;
    nuevo_nodo->prioridad = prioridad;
    nuevo_nodo->siguiente = NULL;

    if (cola == NULL) {
        cola = nuevo_nodo;
    } else {
        Nodo* aux = cola;
        while (aux->siguiente != NULL) {
            aux = aux->siguiente;
        }
        aux->siguiente = nuevo_nodo;
    }

    cout << "Proceso agregado correctamente a la cola.\n";
}

void atenderProcesocol(Nodo*& cola) {
    if (cola == NULL) {
        cout << "No hay procesos en espera en la cola.\n";
        return;
    }

    Nodo* aux = cola;
    cola = cola->siguiente;

    cout << "Atendiendo proceso: " << aux->dato << " de prioridad " << aux->prioridad << endl;
    delete aux;

    cout << "Numeros restantes en la cola:\n";
    imprimirProcesoscol(cola);
}

void imprimirProcesoscol(Nodo* cola) {
    Nodo* aux = cola;
    while (aux != NULL) {
        cout << aux->dato << " - Prioridad: " << aux->prioridad << endl;
        aux = aux->siguiente;
    }
    cout << endl;
}


void insertarLista(NodoL*& lista, int dato) {
    NodoL* nuevoNodo = new NodoL();
    nuevoNodo->dato = dato;
    nuevoNodo->siguiente = NULL;

    if (lista == NULL) {
        lista = nuevoNodo;
    } else {
        NodoL* temp = lista;
        while (temp->siguiente != NULL) {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevoNodo;
    }
}

void insertarArbol(Arbol& arbol, int dato) {
    if (arbol == NULL) {
        arbol = crearNodo(dato);
    } else {
        if (dato < arbol->nro) {
            insertarArbol(arbol->izq, dato);
        } else {
            insertarArbol(arbol->der, dato);
        }
    }
}
void convertirPilaLista(Nodo* pila) {
    NodoL* lista = NULL;
    while (pila != NULL) {
        insertarLista(lista, pila->dato);
        Nodo* temp = pila;
        pila = pila->siguiente;
        delete temp;
    }
    cout << "La pila se ha convertido en una lista correctamente.\n";
}

void convertirColaLista(Nodo* cola) {
    NodoL* lista = NULL;
    while (cola != NULL) {
        insertarLista(lista, cola->dato);
        Nodo* temp = cola;
        cola = cola->siguiente;
        delete temp;
    }
    cout << "La cola se ha convertido en una lista correctamente.\n";
}



void convertirPilaArbol(Nodo* pila) {
    Arbol arbol = NULL;
    while (pila != NULL) {
        insertarArbol(arbol, pila->dato);
        Nodo* temp = pila;
        pila = pila->siguiente;
        delete temp;
    }
    cout << "La pila se ha convertido en un arbol correctamente.\n";
}

void convertirColaArbol(Nodo* cola) {
    Arbol arbol = NULL;
    while (cola != NULL) {
        insertarArbol(arbol, cola->dato);
        Nodo* temp = cola;
        cola = cola->siguiente;
        delete temp;
    }
    cout << "La cola se ha convertido en un arbol correctamente.\n";
}






