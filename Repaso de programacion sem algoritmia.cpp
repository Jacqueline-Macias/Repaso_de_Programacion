#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class Paquete {
public:
    Paquete(int id, const std::string& origen, const std::string& destino, double peso)
        : id(id), origen(origen), destino(destino), peso(peso) {}

    int getId() const { return id; }
    const std::string& getOrigen() const { return origen; }
    const std::string& getDestino() const { return destino; }
    double getPeso() const { return peso; }

private:
    int id;
    std::string origen;
    std::string destino;
    double peso;
};

class Nodo {
public:
    Paquete paquete;
    Nodo* siguiente;

    Nodo(const Paquete& p) : paquete(p), siguiente(nullptr) {}
};

class ListaSimple {
public:
    ListaSimple() : primero(nullptr) {}

    void insertarAlInicio(const Paquete& paquete) {
        Nodo* nuevoNodo = new Nodo(paquete);
        nuevoNodo->siguiente = primero;
        primero = nuevoNodo;
    }

    void eliminarAlInicio() {
        if (primero) {
            Nodo* temp = primero;
            primero = primero->siguiente;
            delete temp;
        }
    }

    void mostrar() const {
        Nodo* actual = primero;
        while (actual) {
            std::cout << "ID: " << actual->paquete.getId() << ", Origen: " << actual->paquete.getOrigen()
                      << ", Destino: " << actual->paquete.getDestino() << ", Peso: " << actual->paquete.getPeso() << " kg\n";
            actual = actual->siguiente;
        }
    }

    void guardarEnArchivo(const std::string& nombreArchivo) const {
        std::ofstream archivo(nombreArchivo);
        if (archivo.is_open()) {
            Nodo* actual = primero;
            while (actual) {
                archivo << actual->paquete.getId() << ","
                        << actual->paquete.getOrigen() << ","
                        << actual->paquete.getDestino() << ","
                        << actual->paquete.getPeso() << "\n";
                actual = actual->siguiente;
            }
            archivo.close();
            std::cout << "Datos guardados en el archivo: " << nombreArchivo << std::endl;
        } else {
            std::cerr << "No se pudo abrir el archivo para escritura." << std::endl;
        }
    }

    void recuperarDeArchivo(const std::string& nombreArchivo) {
        std::ifstream archivo(nombreArchivo);
        if (archivo.is_open()) {
            std::string linea;
            while (std::getline(archivo, linea)) {
                std::istringstream iss(linea);
                int id;
                std::string origen, destino;
                double peso;
                char delimiter;
                if (iss >> id >> delimiter &&
                    std::getline(iss, origen, ',') &&
                    std::getline(iss, destino, ',') &&
                    iss >> peso) {
                    Paquete paquete(id, origen, destino, peso);
                    insertarAlInicio(paquete);
                }
            }
            archivo.close();
            std::cout << "Datos recuperados del archivo: " << nombreArchivo << std::endl;
        } else {
            std::cerr << "No se pudo abrir el archivo para lectura." << std::endl;
        }
    }

private:
    Nodo* primero;
};

int main() {
    ListaSimple paqueteria;
    int opcion;

    do {
        std::cout << "Menu:" << std::endl;
        std::cout << "1. Agregar paquete" << std::endl;
        std::cout << "2. Eliminar paquete" << std::endl;
        std::cout << "3. Mostrar" << std::endl;
        std::cout << "4. Guardar (Archivo)" << std::endl;
        std::cout << "5. Recuperar (Archivo)" << std::endl;
        std::cout << "6. Salir" << std::endl;
        std::cout << "Ingrese una opcion: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1: {
                int id;
                std::string origen, destino;
                double peso;
                std::cout << "Ingrese el ID: ";
                std::cin >> id;
                std::cin.ignore();
                std::cout << "Ingrese el origen: ";
                std::getline(std::cin, origen);
                std::cout << "Ingrese el destino: ";
                std::getline(std::cin, destino);
                std::cout << "Ingrese el peso: ";
                std::cin >> peso;
                Paquete nuevoPaquete(id, origen, destino, peso);
                paqueteria.insertarAlInicio(nuevoPaquete);
                break;
            }
            case 2: {
                paqueteria.eliminarAlInicio();
                std::cout << "Paquete eliminado del inicio." << std::endl;
                break;
            }
            case 3: {
                std::cout << "Lista de paquetes:" << std::endl;
                paqueteria.mostrar();
                break;
            }
            case 4: {
                std::string nombreArchivo;
                std::cout << "Ingrese el nombre del archivo para guardar: ";
                std::cin >> nombreArchivo;
                paqueteria.guardarEnArchivo(nombreArchivo);
                break;
            }
            case 5: {
                std::string nombreArchivo;
                std::cout << "Ingrese el nombre del archivo para recuperar: ";
                std::cin >> nombreArchivo;
                paqueteria.recuperarDeArchivo(nombreArchivo);
                break;
            }
            case 6: {
                std::cout << "Saliendo del programa." << std::endl;
                break;
            }
            default: {
                std::cout << "Opcion invalida. Intente de nuevo." << std::endl;
                break;
            }
        }
    } while (opcion != 6);

    return 0;
}

