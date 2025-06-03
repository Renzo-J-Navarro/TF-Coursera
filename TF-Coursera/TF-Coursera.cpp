#include <iostream>
#include "pch.h"
#include "Curso.hpp"
#include "ListaCurso.hpp"
#include "Boleta.hpp"

using namespace std;

void menuCursoAdmin() {
    cout << "\n====== MENU CURSO ======\n";
    cout << "1. Agregar curso\n";
    cout << "2. Mostrar cursos\n";
    cout << "3. Buscar por código\n";
    cout << "4. Buscar por categoría\n";
    cout << "5. Buscar por precio\n";
    cout << "6. Ordenar por precio (asc)\n";
    cout << "7. Ordenar por duración (desc)\n";
    cout << "8. Eliminar curso\n";
    cout << "9. Comprar cursos\n";
    cout << "10. Mostrar boleta\n";
    cout << "11. Salir\n";
    cout << "Seleccione una opción: ";
}
void menuUsuarioAdmin() {
	cout << "\n====== MENU USUARIO ADMIN ======\n";
	cout << "1. Agregar usuario\n";
	cout << "2. Mostrar usuarios\n";
	cout << "3. Buscar usuario por correo\n";
	cout << "4. Buscar usuario por nombre\n";
	cout << "5. Eliminar usuario\n";
	cout << "6. Modificar usuario\n";
	cout << "7. Activar Premium\n";
	cout << "8. Desactivar Premium\n";
	cout << "9. Salir\n";
	cout << "Seleccione una opción: ";
}
void menuCompraAdmin() {
	cout << "\n====== MENU COMPRAS ADMIN ======\n";
	cout << "1. Mostrar compras\n";
	cout << "2. Buscar compra por ID\n";
	cout << "3. Buscar compra por usuario\n";
	cout << "4. Buscar compra por curso\n";
	cout << "5. Eliminar compra\n";
	cout << "6. Salir\n";
	cout << "Seleccione una opción: ";
}
void menuAdmin() {
	cout << "\n====== MENU ADMINISTRADOR ======\n";
	cout << "1. Administrar cursos\n";
	cout << "2. Administrar usuarios\n";
    cout << "3. Administrar Compras\n";
	cout << "4. Salir\n";
	cout << "Seleccione una opción: ";
}
void menuPrograma() {
	cout << "\n====== MENU PRINCIPAL ======\n";
	cout << "1. Ingresar como usuario\n";
    cout << "2. Beneficios Premium y Certificados\n";
    cout << "3. Creditos\n";
	cout << "4. Salir\n";
	cout << "Seleccione una opción: ";
}
void menuSesion() {
    cout << "\n====== INICIO SESION ======\n";
    cout << "1. Ingresar usuario\n";
    cout << "2. Crear Usuario\n";
    cout << "3. Salir\n";
    cout << "Seleccione una opcion: ";
}
void menuUser() {
    cout << "\n====== MENU USUARIO ======\n";
    cout << "1. Modificar datos usuario\n";
    cout << "2. Eliminar cuenta usuario\n";
	cout << "3. Activar Plan Premium\n";
	cout << "4. Desactivar Plan Premium\n";
    cout << "5. Salir\n";
    cout << "Seleccione una opcion: ";
}
void menuUserCurso() {
    cout << "\n====== MENU CURSOS ======\n";
    cout << "1. Buscar por codigo\n";
    cout << "2. Buscar por categoria\n";
    cout << "3. Buscar por precio\n";
    cout << "4. Ordenar por precio (asc)\n";
    cout << "5. Ordenar por duracion (desc)\n";
    cout << "6. Comprar cursos\n";
    cout << "7. Salir\n";
    cout << "Seleccione una opcion: ";  
}

void cargarDatos(ListaCurso<Curso<string>>& listaCurso) {
    ifstream archivoCurso("ListaCurso/cursos.txt");
    if (archivoCurso.is_open()) {
        string linea;
        int cargados = 0, duplicados = 0;
        while (getline(archivoCurso, linea)) {
            Curso<string> curso = Curso<string>::cargarLineas(linea);
            if (!listaCurso.existeCodigo(curso.getCodigo())) {
                listaCurso.agregarCurso(curso);
                cargados++;
            }
            else {
                duplicados++;
            }
        }
        archivoCurso.close();
        cout << "\tCursos cargados del archivo: " << cargados << endl;
        if (duplicados > 0) {
            cout << "\tCursos duplicados no cargados: " << duplicados << endl;
        }
    }
    else
    {
        cout << "\n\tNo se pudo abrir el archivo.\n";
    }
}

int main() {
    ListaCurso<Curso<string>> lista;
    cargarDatos(lista);
    int opcion;
    do {
        menuUserCurso();
        while (!(cin >> opcion)) {
            cin.clear(); // limpia el estado de error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // limpia el buffer
            cout << "\n\tEntrada invalida. Ingrese valores numericos !!! \n";
        }
        cin.ignore();
        switch (opcion) {
        case 1: {
            system("cls");
            int cod;
            cout << "Código del curso a buscar: ";
            cin >> cod;
			Curso<string>* resultado = lista.buscarCursoPorCodigo(cod);
            if (resultado) resultado->mostrarCurso();
			else cout << "Curso no encontrado.\n";
            break;
        }
        case 2: {
            system("cls");
            string cat;
            cout << "Categoria a buscar: ";
            getline(cin, cat);
			lista.buscarCategoria(cat);
            break;
        }
        case 3: {
            system("cls");
            float precio;
            cout << "Precio maximo: ";
            cin >> precio;
            lista.buscarPrecio(precio);
            break;
        }
        case 4: {
            system("cls");
            lista.ordenarPorPrecio();
			lista.mostrarCursos();
            break;
        }
        case 5: {
            system("cls");
            lista.ordenarPorDuracion();
            lista.mostrarCursos();
            break;
        }
        case 6: {
            system("cls");
            if (lista.getInicio() == nullptr) {
                cout << "No hay cursos disponibles para comprar.\n";
                break;
            }
            cout << "Comprando cursos...\n";
            lista.mostrarCursos();
            Curso<string>* seleccionaCurso;
            vector<DetalleCurso> detalles;
            bool cancelaCompra = false;
            string input;
            int codigo, cant;

            cout << "Ingrese el codigo del curso y cantidad que quiere comprar (finalizar con 'f' y proceder con 'c'): ";
            cout << endl;
            while (true) {
                cout << "\t";
                cin >> input;
                if (input == "c" || input == "C") {
                    cout << "Procediendo con el pago...." << endl;
                    break;
                }
                if (input == "f" || input == "F") {
                    cout << "Compra Cancelada" << endl;
                    detalles.clear();
                    cancelaCompra = true;
                    break;
                }
                try {
                    codigo = stoi(input);
                }
                catch (...) {
                    cout << "Codigo Invalido. Intente de nuevo" << endl;
                    continue;
                }
                cin >> cant;
                if (cant <= 0)
                {
                    cout << "\nCantidad de cursos invalido. Intente de nuevo." << endl;
                    continue;
                }
                seleccionaCurso = lista.buscarCursoPorCodigo(codigo);
                if (!seleccionaCurso) {
                    cout << "Curso no encontrado.\n";
                    break;
                }
                
                string codigoCursoStr = to_string(seleccionaCurso->getCodigo());
                detalles.push_back(DetalleCurso(codigoCursoStr, seleccionaCurso->getCurso(),
                    seleccionaCurso->getCategoria(), static_cast<float>(seleccionaCurso->getPrecio()),
                    cant
                ));

                if (detalles.empty()) {
                    cout << "No se compro ningun curso.\n";
                    break;
                }
            }
            if (cancelaCompra) {
               break;
            }

            string metodoPago;
            int opcionPago;
            cout << "\n\t--- Seleccione el metodo de pago ---\n";
            cout << "1. Tarjeta Debito." << endl;
            cout << "2. Tarjeta Credito." << endl;
            cout << "3. Yape" << endl;
            cout << "4. Plin" << endl;
            cout << "Selecione una opcion: ";
            cin >> opcionPago;
            cin.ignore();
            switch (opcionPago) {
            case 1:
                metodoPago = "Tarjeta Debito";
                break;
            case 2:
                metodoPago = "Tarjeta Credito";
                break;
            case 3:
                metodoPago = "Yape";
                break;
            case 4:
                metodoPago = "Plin";
                break;
            default:
                metodoPago = "Otro";
                break;
            }

            int mes = rand() % 12 + 1;
            int dia = rand() % 30 + 1;
            int horaInt = rand() % 24;
            int minuto = rand() % 60;

            string numOperacion = "B00" + to_string(rand() % 10) + "-" + to_string(rand() % 100000);
            string fecha = "2025-" + (mes < 10 ? "0" + to_string(mes) : to_string(mes)) + "-" +
                (dia < 10 ? "0" + to_string(dia) : to_string(dia));
            string hora = (horaInt < 10 ? "0" + to_string(horaInt) : to_string(horaInt)) + ":" +
                (minuto < 10 ? "0" + to_string(minuto) : to_string(minuto));

            Boleta boletaCurso("Coursera", numOperacion, fecha, hora,
                metodoPago, "correo", "nombreCliente", detalles);
            boletaCurso.mostrarBoletaCurso();

            string ruta = boletaCurso.generarNombreArchivo();
            boletaCurso.guardarBoletaEnArchivo(ruta);

            cout << "\nCursos comprados con exito !!!\n";
            break;
        }
        case 7: {
            cout << "Saliendo del programa...\n";
            break;
        }
        default:
            cout << "Opción inválida. Intente de nuevo.\n";
        }
    } while (opcion != 7);

    return 0;
}
