#include <iostream>
#include <conio.h>
#include <string>
#include <sstream>
#include <cctype> //validaciones de entrada
#include <math.h>
#include <ctime>
#include <cstdlib>
#include <regex>
#define MAX 20    // maximo de clientes, citas y servicios
using namespace std;

int tope; // tope para el arreglo de citas
struct cliente
{
    int idUser;
    string name;
    string apPat;
    string apMat;
    string correo;
    string tel;
    string direccion;
    string segundoEncargado;
};
struct cliente cli[MAX];

struct mascota
{
    string name;
    string raza;
    string color;
    float edad;
    float peso;
    float altura;
    char genero;// 'M' para macho, 'H' para hembra
    cliente *cli;
};
struct mascota mas[MAX];

struct servicios
{
    bool bano;
    bool cortePelo;
    bool corteGarras;
    bool limpiezaOidos;
    bool lavadoDientes;
};
struct servicios serv[MAX];

struct cita
{
    int id;
    string inHora;   // formato hh:mm
    string Fecha;  // formato dd/mm/yyyy
    string outHora;  // formato hh:mm
    cliente *duenio;
    mascota *mascota;
    servicios *serv[MAX];
};
struct cita cita[MAX];

// Para manejar la fecha y hora actual
time_t now = time(0);
tm *newtime = localtime(&now);

// Function prototypes
int agendarCita(cliente* cli, mascota* mas, servicios* serv);
int NewClient(cliente cli[MAX]);
int generateID();
void show();
void prueba();
void consultarCita();
void editarCita();
void eliminarCita();
bool validarFecha(string fecha);
bool validarHorario(string horario);
bool validarEmail(string email);
bool validarTelefono(string telefono);
bool validarNombreMascota(string nombre);
bool validarEdad(string edad);
bool validarPeso(string peso);
bool validarAltura(string altura);
bool validarServicio(char servicio);
bool esFechaActualOMayor(string fecha);
bool esHorarioActualOMayor(string fecha, string horario);
void mostrarCitasOrdenadas();
void mergeClientes(int indices[], int izq, int medio, int der, bool ascendente);
void mergeSortClientes(int indices[], int izq, int der, bool ascendente);

// variables globales
int op, dia, mes, anio, horas, minutos, numRanID;
string date, horario;
char separador1, separador2, separadorTime; // para '/'
int main()
{
    srand(time(0)); // Inicializar generador de números aleatorios
    prueba();
    cout << "\t\t\t\tESTETICA HUELLITAS FELICES\n\n\n";
    cout << "\tBienvenido/a a su estetica favorita.\n\n\n"
         << asctime(newtime);
    do
    {
        cout << "\tMenu de opciones.\n\n";
        cout << "\t\t1. Agendar una cita\n";
        cout << "\t\t2. Consultar datos de una cita\n";
        cout << "\t\t3. Soy cliente nuevo\n";
        cout << "\t\t4. Editar cita\n";
        cout << "\t\t5. Eliminar cita\n";
        cout << "\t\t6. Ver citas programadas (ordenadas)\n";
        cout << "\t\t7. Mostrar usuarios registrados\n";
        cout << "\t\t8. Salir\n\n";
        cout << "\tElija una opcion: ";
        cin >> op;

        if (cin.fail() || op < 1 || op > 8) {
            cin.clear();
            cin.ignore(1000, '\n');
            system("cls");
            cout << "\t\t\t\tESTETICA HUELLITAS FELICES\n\n\n";
            cout << "\tBienvenido/a a su estetica favorita.\n\n\n";
            cout << "Opción inválida, intente nuevamente.\n\n";
            continue;
        }

        switch (op)
        {
        case 1:
            system("cls");
            cout << "\tAgendar una cita\n";
            agendarCita(cli, mas, serv);
            break;
        case 2:
            system("cls");
            consultarCita();
            break;
        case 3:
            system("cls");
            NewClient(cli);
            break;
        case 4:
            system("cls");
            editarCita();
            break;
        case 5:
            system("cls");
            eliminarCita();
            break;
        case 6:
            system("cls");
            mostrarCitasOrdenadas();
            break;
        case 7:
            system("cls");
            show();
            break;
        case 8:
            cout << "\tGracias por usar el programa\n";
            break;
        default:
            cout << "\n";
            break;
        }
        if (op != 8) {
            cout << "\nPresione cualquier tecla para continuar...";
            getch();
            system("cls");
        }
    } while (op != 8);
    return 0;
}
// Validación para nombre de mascota - permite cualquier cosa excepto vacío
bool validarNombreMascota(string nombre) {
    if (nombre.empty()) {
        cout << "El nombre de la mascota no puede estar vacío.\n";
        return false;
    }
    return true;
}

bool validarEdad(string edad) {
    if (edad.empty()) {
        cout << "La edad no puede estar vacía.\n";
        return false;
    }

    int edadNum = stoi(edad);
    if (edadNum < 0 || edadNum > 30) {
        cout << "ERROR: La edad debe estar entre 0 y 30 años.\n";
        return false;
    }
    return true;
}

bool validarPeso(string peso) {
    if (peso.empty()) {
        cout << "El peso no puede estar vacío.\n";
        return false;
    }

    bool puntoEncontrado = false;
    for (char c : peso) {
        if (c == '.' && !puntoEncontrado) {
            puntoEncontrado = true;
        } else if (!isdigit(c)) {
            cout << "El peso solo puede contener números y un punto decimal.\n";
            return false;
        }
    }

    float pesoNum = stof(peso);
    if (pesoNum <= 0 || pesoNum > 100) {
        cout << "ERROR: El peso debe estar entre 0.1 y 100 kg.\n";
        return false;
    }
    return true;
}

bool validarAltura(string altura) {
    if (altura.empty()) {
        cout << "La altura no puede estar vacía.\n";
        return false;
    }

    bool puntoEncontrado = false;
    for (char c : altura) {
        if (c == '.' && !puntoEncontrado) {
            puntoEncontrado = true;
        } else if (!isdigit(c)) {
            cout << "La altura solo puede contener números y un punto decimal.\n";
            return false;
        }
    }

    float alturaNum = stof(altura);
    if (alturaNum <= 0 || alturaNum > 300) {
        cout << "ERROR: La altura debe estar entre 10 centimetros a 300 centimetros.\n";
        return false;
    }
    return true;
}

bool validarServicio(char servicio) {
    if (servicio != 'S' && servicio != 's' && servicio != 'N' && servicio != 'n') {
        cout << "Solo se acepta 'S' para Sí o 'N' para No.\n";
        return false;
    }
    return true;
}

bool esFechaActualOMayor(string fecha) {
    time_t now = time(0);
    tm *fechaActual = localtime(&now);

    int dia = stoi(fecha.substr(0,2));
    int mes = stoi(fecha.substr(3,2));
    int anio = stoi(fecha.substr(6,4));

    int diaActual = fechaActual->tm_mday;
    int mesActual = fechaActual->tm_mon + 1;
    int anioActual = fechaActual->tm_year + 1900;

    if (anio < anioActual) {
        cout << "La fecha no puede ser anterior al año actual.\n";
        return false;
    } else if (anio == anioActual) {
        if (mes < mesActual) {
            cout << "La fecha no puede ser anterior al mes actual.\n";
            return false;
        } else if (mes == mesActual && dia < diaActual) {
            cout << "La fecha no puede ser anterior al día actual.\n";
            return false;
        }
    }
    return true;
}

bool esHorarioActualOMayor(string fecha, string horario) {
    time_t now = time(0);
    tm *fechaActual = localtime(&now);

    int dia = stoi(fecha.substr(0,2));
    int mes = stoi(fecha.substr(3,2));
    int anio = stoi(fecha.substr(6,4));

    int diaActual = fechaActual->tm_mday;
    int mesActual = fechaActual->tm_mon + 1;
    int anioActual = fechaActual->tm_year + 1900;

    // Si es el mismo día, validar horario
    if (anio == anioActual && mes == mesActual && dia == diaActual) {
        int horas = stoi(horario.substr(0,2));
        int minutos = stoi(horario.substr(3,2));

        int horaActual = fechaActual->tm_hour;
        int minutoActual = fechaActual->tm_min;

        if (horas < horaActual || (horas == horaActual && minutos < minutoActual)) {
            cout << "El horario no puede ser anterior a la hora actual.\n";
            return false;
        }
    }
    return true;
}
// Función para registrar nuevo cliente - SIN validaciones para nombres
int NewClient(cliente cli[MAX]) {
    int i;
    // Buscar espacio disponible
    for (i = 0; i < MAX; i++) {
        if (cli[i].name.empty()) {
            break;
        }
    }

    if (i == MAX) {
        cout << "No hay espacio para más clientes.\n";
        return -1;
    }

    cout << "\t\t\t\tESTETICA HUELLITAS FELICES\n\n\n";
    cout << "\t\tREGISTRO DE NUEVO CLIENTE\n\n\n";

    cli[i].idUser = generateID();
    cout << "Su ID de cliente es: " << cli[i].idUser << "\n";
    cout << "Por favor, guarde este número para futuras citas.\n\n";

    cin.ignore(); // Limpiar buffer

    // SIN validación - permite acentos, ñ y cualquier carácter
    cout << "Ingrese su nombre(s): ";
    getline(cin, cli[i].name);

    // SIN validación - permite acentos, ñ y cualquier carácter
    cout << "Ingrese su apellido paterno: ";
    getline(cin, cli[i].apPat);

    // SIN validación - permite acentos, ñ y cualquier carácter
    cout << "Ingrese su apellido materno: ";
    getline(cin, cli[i].apMat);

    do {
        cout << "Ingrese su correo electrónico: ";
        getline(cin, cli[i].correo);
    } while (!validarEmail(cli[i].correo));

    do {
        cout << "Ingrese su teléfono (10 dígitos): ";
        getline(cin, cli[i].tel);
    } while (!validarTelefono(cli[i].tel));

    cout << "Ingrese su dirección: ";
    getline(cin, cli[i].direccion);

    cout << "Ingrese nombre del segundo encargado (opcional): ";
    getline(cin, cli[i].segundoEncargado);

    cout << "\nCliente registrado exitosamente!\n";
    cout << "ID del cliente: " << cli[i].idUser << "\n";

    return 0;
}

// Función para consultar citas
void consultarCita() {
    int idCita;
    cout << "\t\t\t\tESTETICA HUELLITAS FELICES\n\n\n";
    cout << "\t\tCONSULTAR CITA\n\n\n";
    cout << "Ingrese el ID de la cita: ";
    cin >> idCita;

    for (int i = 0; i < MAX; i++) {
        if (cita[i].id == idCita && cita[i].duenio != nullptr) {
            cout << "\n=== INFORMACIÓN DE LA CITA ===\n";
            cout << "ID de cita: " << cita[i].id << "\n";
            cout << "Fecha: " << cita[i].Fecha << "\n";
            cout << "Hora de entrada: " << cita[i].inHora << "\n";
            cout << "Hora de salida estimada: " << cita[i].outHora << "\n";
            cout << "Cliente: " << cita[i].duenio->name << " " << cita[i].duenio->apPat << "\n";
            cout << "Mascota: " << cita[i].mascota->name << "\n";
            cout << "Raza: " << cita[i].mascota->raza << "\n";

            cout << "\nServicios solicitados:\n";
            if (cita[i].serv[0]->bano) cout << "- Baño\n";
            if (cita[i].serv[0]->cortePelo) cout << "- Corte de pelaje\n";
            if (cita[i].serv[0]->corteGarras) cout << "- Corte de uñas\n";
            if (cita[i].serv[0]->limpiezaOidos) cout << "- Limpieza de oídos\n";
            if (cita[i].serv[0]->lavadoDientes) cout << "- Lavado de dientes\n";

            return;
        }
    }
    cout << "Cita no encontrada.\n";
}
// Función MEJORADA para editar cita con validación de citas existentes
void editarCita() {
    int idCita;
    cout << "\t\t\t\tESTETICA HUELLITAS FELICES\n\n\n";
    cout << "\t\tEDITAR CITA\n\n\n";
    
    // Verificar si hay citas registradas
    bool hayCitas = false;
    for (int i = 0; i < MAX; i++) {
        if (cita[i].id != 0 && cita[i].duenio != nullptr) {
            hayCitas = true;
            break;
        }
    }
    
    if (!hayCitas) {
        cout << "No hay citas disponibles para editar.\n";
        return;
    }
    
    cout << "Ingrese el ID de la cita a editar: ";
    cin >> idCita;

    for (int i = 0; i < MAX; i++) {
        if (cita[i].id == idCita && cita[i].duenio != nullptr) {
            cout << "Cita encontrada para: " << cita[i].mascota->name << "\n";
            cout << "¿Qué desea editar?\n";
            cout << "1. Fecha\n";
            cout << "2. Horario\n";
            cout << "3. Servicios\n";
            cout << "Opción: ";

            int opEdit;
            cin >> opEdit;

            switch(opEdit) {
                case 1: {
                    string nuevaFecha;
                    do {
                        cout << "Nueva fecha (dd/mm/aaaa): ";
                        cin >> nuevaFecha;
                    } while (!validarFecha(nuevaFecha) || !esFechaActualOMayor(nuevaFecha));
                    cita[i].Fecha = nuevaFecha;
                    cout << "Fecha actualizada.\n";
                    break;
                }
                case 2: {
                    string nuevoHorario;
                    do {
                        cout << "Nuevo horario de entrada (HH:MM): ";
                        cin >> nuevoHorario;
                    } while (!validarHorario(nuevoHorario) || !esHorarioActualOMayor(cita[i].Fecha, nuevoHorario));
                    cita[i].inHora = nuevoHorario;

                    // Calcular nueva hora de salida
                    int horas = stoi(nuevoHorario.substr(0,2));
                    int outHoras = horas + 2;
                    if (outHoras > 23) outHoras -= 24;
                    ostringstream oss;
                    oss << (outHoras < 10 ? "0" : "") << outHoras << ":" << nuevoHorario.substr(3,2);
                    cita[i].outHora = oss.str();
                    cout << "Horario actualizado.\n";
                    break;
                }
                case 3: {
                    cout << "Actualizar servicios (S/N):\n";
                    char op;
                    do {
                        cout << "Baño: "; cin >> op;
                    } while (!validarServicio(op));
                    cita[i].serv[0]->bano = (op == 'S' || op == 's');

                    do {
                        cout << "Corte de pelaje: "; cin >> op;
                    } while (!validarServicio(op));
                    cita[i].serv[0]->cortePelo = (op == 'S' || op == 's');

                    do {
                        cout << "Corte de uñas: "; cin >> op;
                    } while (!validarServicio(op));
                    cita[i].serv[0]->corteGarras = (op == 'S' || op == 's');

                    do {
                        cout << "Limpieza de oídos: "; cin >> op;
                    } while (!validarServicio(op));
                    cita[i].serv[0]->limpiezaOidos = (op == 'S' || op == 's');

                    do {
                        cout << "Lavado de dientes: "; cin >> op;
                    } while (!validarServicio(op));
                    cita[i].serv[0]->lavadoDientes = (op == 'S' || op == 's');

                    cout << "Servicios actualizados.\n";
                    break;
                }
                default:
                    cout << "Opción inválida.\n";
            }
            return;
        }
    }
    cout << "Cita no encontrada.\n";
}

// Función MEJORADA para eliminar cita con validación de citas existentes
void eliminarCita() {
    int idCita;
    cout << "\t\t\t\tESTETICA HUELLITAS FELICES\n\n\n";
    cout << "\t\tELIMINAR CITA\n\n\n";
    
    // Verificar si hay citas registradas
    bool hayCitas = false;
    for (int i = 0; i < MAX; i++) {
        if (cita[i].id != 0 && cita[i].duenio != nullptr) {
            hayCitas = true;
            break;
        }
    }
    
    if (!hayCitas) {
        cout << "No hay citas disponibles para eliminar.\n";
        return;
    }
    
    cout << "Ingrese el ID de la cita a eliminar: ";
    cin >> idCita;

    for (int i = 0; i < MAX; i++) {
        if (cita[i].id == idCita && cita[i].duenio != nullptr) {
            cout << "¿Está seguro de eliminar la cita de " << cita[i].mascota->name << "? (S/N): ";
            char confirmacion;
            cin >> confirmacion;

            if (confirmacion == 'S' || confirmacion == 's') {
                // Limpiar la cita
                cita[i].id = 0;
                cita[i].inHora = "";
                cita[i].Fecha = "";
                cita[i].outHora = "";
                cita[i].duenio = nullptr;
                cita[i].mascota = nullptr;
                cita[i].serv[0] = nullptr;

                cout << "Cita eliminada exitosamente.\n";
            } else {
                cout << "Eliminación cancelada.\n";
            }
            return;
        }
    }
    cout << "Cita no encontrada.\n";
}
// Funciones de validación originales
bool validarFecha(string fecha) {
    if (fecha.length() != 10 || fecha[2] != '/' || fecha[5] != '/') {
        cout << "Formato de fecha inválido. Use dd/mm/aaaa\n";
        return false;
    }

    // Verificar que solo contenga números en las posiciones correctas
    for (int i = 0; i < fecha.length(); i++) {
        if (i != 2 && i != 5) { // Saltar las posiciones de '/'
            if (!isdigit(fecha[i])) {
                cout << "La fecha solo puede contener números y /\n";
                return false;
            }
        }
    }

    int dia = stoi(fecha.substr(0,2));
    int mes = stoi(fecha.substr(3,2));
    int anio = stoi(fecha.substr(6,4));

    if (mes < 1 || mes > 12 || dia < 1 || dia > 31) {
        cout << "Fecha inválida.\n";
        return false;
    }
    return true;
}

bool validarHorario(string horario) {
    if (horario.length() != 5 || horario[2] != ':') {
        cout << "Formato de horario inválido. Use HH:MM\n";
        return false;
    }

    // Verificar que solo contenga números en las posiciones correctas
    for (int i = 0; i < horario.length(); i++) {
        if (i != 2) { // Saltar la posición de ':'
            if (!isdigit(horario[i])) {
                cout << "El horario solo puede contener números y :\n";
                return false;
            }
        }
    }

    int horas = stoi(horario.substr(0,2));
    int minutos = stoi(horario.substr(3,2));

    if (horas < 9 || horas > 17 || minutos < 0 || minutos >= 60) {
        cout << "Horario debe estar entre 09:00 y 17:00\n";
        return false;
    }
    return true;
}

bool validarEmail(string email) {
    if (email.find('@') == string::npos || email.find('.') == string::npos) {
        cout << "Email inválido. Debe contener @ y .\n";
        return false;
    }
    return true;
}

bool validarTelefono(string telefono) {
    if (telefono.length() != 10) {
        cout << "El teléfono debe tener 10 dígitos.\n";
        return false;
    }

    for (char c : telefono) {
        if (!isdigit(c)) {
            cout << "El teléfono solo debe contener números.\n";
            return false;
        }
    }
    return true;
}
// Función para agendar cita - modificada según requerimientos
int agendarCita(cliente *cli, mascota *mas, servicios *serv)
{
    int aux, i, k;
    string auxNom;
    system("cls");
    cout << "\t\t\t\tESTETICA HUELLITAS FELICES\n\n\n";
    cout << "\t\tAGENDAR CITA\n\n\n";
    cout << "Ingrese el ID del cliente: ";
    cin >> aux;
    if (cin.fail() || aux < 1) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "ID inválido, intente nuevamente.\n";
        return -1;
    }

    // Buscar cliente
    for (i = 0; i < MAX; i++) {
        if (cli[i].idUser == aux) {
            cout << "Bienvenido " << cli[i].apPat << " " << cli[i].apMat << " " << cli[i].name << "\n";
            cout << "Mascotas registradas:\n";
            for (k = 0; k < MAX; k++) {
                if (mas[k].cli == &cli[i]) {
                    cout << "- " << mas[k].name << "\n";
                }
            }
            cout << "Introduzca el nombre de la mascota a la que se agendará la cita: ";
            cin >> auxNom;

            // Buscar mascota
            for (k = 0; k < MAX; k++) {
                if (mas[k].cli == &cli[i] && mas[k].name == auxNom) {
                    cout << "     AGENDAR CITA PARA LA MASCOTA " << mas[k].name << "\n\n";
                    cout << "Servicios a realizar: \n";
                    cout << "Responda con S si desea el servicio, de lo contrario N\n\n";

                    char op;
                    do {
                        cout << "Servicio de baño: "; cin >> op;
                    } while (!validarServicio(op));
                    serv[k].bano = (op == 'S' || op == 's');

                    do {
                        cout << "Servicio de corte de pelaje: "; cin >> op;
                    } while (!validarServicio(op));
                    serv[k].cortePelo = (op == 'S' || op == 's');

                    do {
                        cout << "Servicio de corte de uñas/garras: "; cin >> op;
                    } while (!validarServicio(op));
                    serv[k].corteGarras = (op == 'S' || op == 's');

                    do {
                        cout << "Servicio de limpieza de oidos: "; cin >> op;
                    } while (!validarServicio(op));
                    serv[k].limpiezaOidos = (op == 'S' || op == 's');

                    do {
                        cout << "Servicio de lavado de dientes: "; cin >> op;
                    } while (!validarServicio(op));
                    serv[k].lavadoDientes = (op == 'S' || op == 's');

                    // Fecha con validaciones
                    cout << "FECHA PARA LA CITA\n";
                    string date;
                    do {
                        cout << "Fecha a realizarse la cita (dd/mm/aaaa): ";
                        cin >> date;
                    } while (!validarFecha(date) || !esFechaActualOMayor(date));
                    cita[k].Fecha = date;

                    // Horario con validaciones
                    string horario;
                    do {
                        cout << "Introduzca el horario de entrada (HH:MM): ";
                        cin >> horario;
                    } while (!validarHorario(horario) || !esHorarioActualOMayor(date, horario));

                    cita[k].inHora = horario;
                    int horas = stoi(horario.substr(0,2));
                    int outHoras = horas + 2;
                    if (outHoras > 23) outHoras -= 24;
                    ostringstream oss;
                    oss << (outHoras < 10 ? "0" : "") << outHoras << ":" << horario.substr(3,2);
                    cita[k].outHora = oss.str();

                    // Asignar datos de la cita
                    cita[k].id = generateID();
                    cita[k].duenio = &cli[i];
                    cita[k].mascota = &mas[k];
                    cita[k].serv[0] = &serv[k];

                    cout << "\n=== CITA AGENDADA EXITOSAMENTE ===\n";
                    cout << "ID de la cita: " << cita[k].id << "\n";
                    cout << "Mascota: " << mas[k].name << "\n";
                    cout << "Fecha: " << cita[k].Fecha << "\n";
                    cout << "Hora de entrada: " << cita[k].inHora << "\n";
                    cout << "Hora de salida estimada: " << cita[k].outHora << "\n";
                    return 0;
                }
            }

            // Si la mascota no existe, registrar nueva mascota
            cout << "Mascota no encontrada. ¿Desea registrar una nueva mascota? (S/N): ";
            char respuesta;
            cin >> respuesta;

            if (respuesta == 'S' || respuesta == 's') {
                for (k = 0; k < MAX; k++) {
                    if (mas[k].name.empty()) {
                        mas[k].cli = &cli[i];
                        cin.ignore(); // Limpiar buffer

                        // Nombre de mascota - permite cualquier cosa
                        do {
                            cout << "Ingrese el nombre de la mascota: ";
                            getline(cin, mas[k].name);
                        } while (!validarNombreMascota(mas[k].name));

                        // Raza - sin validación
                        cout << "Raza: ";
                        getline(cin, mas[k].raza);

                        // Color - sin validación
                        cout << "Color: ";
                        getline(cin, mas[k].color);

                        // Edad - CON validación estricta
                        string edadStr;
                        do {
                            cout << "Edad (Desde 0 a 30 años): ";
                            getline(cin, edadStr);
                        } while (!validarEdad(edadStr));
                        mas[k].edad = stoi(edadStr);

                        // Peso - CON validación estricta
                        string pesoStr;
                        do {
                            cout << "Peso (kg): ";
                            getline(cin, pesoStr);
                        } while (!validarPeso(pesoStr));
                        mas[k].peso = stof(pesoStr);

                        // Altura - CON validación estricta
                        string alturaStr;
                        do {
                            cout << "Altura (cm): ";
                            getline(cin, alturaStr);
                        } while (!validarAltura(alturaStr));
                        mas[k].altura = stof(alturaStr);
 
                        do {
                            cout << "Genero (H para hembra, M para macho): ";
                            cin >> mas[k].genero;
                        } while (mas[k].genero != 'H' && mas[k].genero != 'M');

                        cout << "Mascota registrada exitosamente.\n";
                        cout << "Ahora puede agendar la cita para " << mas[k].name << ".\n";
                        return 0;
                    }
                }
                cout << "No hay espacio para más mascotas.\n";
            }
            return -1;
        }
    }
    cout << "Cliente no encontrado. Por favor, regístrese primero como cliente nuevo.\n";
    return -1;
}
// NUEVA función de ordenamiento exponencial (merge sort implementado desde cero)
void mergeClientes(int indices[], int izq, int medio, int der, bool ascendente) {
    int n1 = medio - izq + 1;
    int n2 = der - medio;
    
    // Crear arreglos temporales
    int izqArr[n1], derArr[n2];
    
    // Copiar datos a arreglos temporales
    for (int i = 0; i < n1; i++)
        izqArr[i] = indices[izq + i];
    for (int j = 0; j < n2; j++)
        derArr[j] = indices[medio + 1 + j];
    
    // Fusionar los arreglos temporales de vuelta en indices[izq..der]
    int i = 0, j = 0, k = izq;
    
    while (i < n1 && j < n2) {
        bool condicion;
        if (ascendente) {
            condicion = cli[izqArr[i]].name <= cli[derArr[j]].name;
        } else {
            condicion = cli[izqArr[i]].name >= cli[derArr[j]].name;
        }
        
        if (condicion) {
            indices[k] = izqArr[i];
            i++;
        } else {
            indices[k] = derArr[j];
            j++;
        }
        k++;
    }
    
    // Copiar los elementos restantes de izqArr[], si los hay
    while (i < n1) {
        indices[k] = izqArr[i];
        i++;
        k++;
    }
    
    // Copiar los elementos restantes de derArr[], si los hay
    while (j < n2) {
        indices[k] = derArr[j];
        j++;
        k++;
    }
}

void mergeSortClientes(int indices[], int izq, int der, bool ascendente) {
    if (izq < der) {
        int medio = izq + (der - izq) / 2;
        
        // Ordenar primera y segunda mitad
        mergeSortClientes(indices, izq, medio, ascendente);
        mergeSortClientes(indices, medio + 1, der, ascendente);
        
        // Fusionar las mitades ordenadas
        mergeClientes(indices, izq, medio, der, ascendente);
    }
}

// NUEVA función show() que solo muestra usuarios ordenados
void show() {
    cout << "\t\t\t\tESTETICA HUELLITAS FELICES\n\n\n";
    cout << "\t\tUSUARIOS REGISTRADOS\n\n\n";
    
    // Contar clientes registrados
    int totalClientes = 0;
    for (int i = 0; i < MAX; i++) {
        if (!cli[i].name.empty()) {
            totalClientes++;
        }
    }
    
    if (totalClientes == 0) {
        cout << "No hay usuarios registrados.\n";
        return;
    }
    
    cout << "¿Cómo desea ver los usuarios ordenados por nombre?\n";
    cout << "1. Orden ascendente (A-Z)\n";
    cout << "2. Orden descendente (Z-A)\n";
    cout << "Opción: ";
    
    int opOrden;
    cin >> opOrden;
    
    if (opOrden != 1 && opOrden != 2) {
        cout << "Opción inválida.\n";
        return;
    }
    
    // Crear arreglo de índices para ordenar
    int indices[MAX];
    int count = 0;
    
    // Llenar arreglo de índices con clientes válidos
    for (int i = 0; i < MAX; i++) {
        if (!cli[i].name.empty()) {
            indices[count] = i;
            count++;
        }
    }
    
    // Aplicar ordenamiento exponencial (merge sort)
    bool ascendente = (opOrden == 1);
    mergeSortClientes(indices, 0, count - 1, ascendente);
    
    // Mostrar usuarios ordenados
    cout << "\n=== USUARIOS REGISTRADOS ===\n";
    cout << "ID\tNombre Completo\t\t\t\tTeléfono\tCorreo\n";
    cout << "--------------------------------------------------------------------------------\n";
    
    for (int i = 0; i < count; i++) {
        int idx = indices[i];
        cout << cli[idx].idUser << "\t" 
             << cli[idx].name << " " << cli[idx].apPat << " " << cli[idx].apMat << "\t\t"
             << cli[idx].tel << "\t" << cli[idx].correo << "\n";
    }
    
    cout << "\nTotal de usuarios registrados: " << count << "\n";
}
void mostrarCitasOrdenadas() {
    cout << "\t\t\t\tESTETICA HUELLITAS FELICES\n\n\n";
    cout << "\t\tVER CITAS PROGRAMADAS\n\n\n";

    // Contar citas activas
    int totalCitas = 0;
    for (int i = 0; i < MAX; i++) {
        if (cita[i].id != 0 && cita[i].duenio != nullptr) {
            totalCitas++;
        }
    }

    if (totalCitas == 0) {
        cout << "No hay citas programadas.\n";
        return;
    }

    cout << "¿Cómo desea ver las citas ordenadas por nombre de mascota?\n";
    cout << "1. Orden ascendente (A-Z)\n";
    cout << "2. Orden descendente (Z-A)\n";
    cout << "Opción: ";

    int opOrden;
    cin >> opOrden;

    if (opOrden != 1 && opOrden != 2) {
        cout << "Opción inválida.\n";
        return;
    }

    // Crear arreglo de índices para ordenar
    int indices[MAX];
    int count = 0;

    // Llenar arreglo de índices con citas válidas
    for (int i = 0; i < MAX; i++) {
        if (cita[i].id != 0 && cita[i].duenio != nullptr) {
            indices[count] = i;
            count++;
        }
    }

    // Ordenamiento burbuja por nombre de mascota
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            bool intercambiar = false;

            if (opOrden == 1) { // Ascendente
                if (cita[indices[j]].mascota->name > cita[indices[j+1]].mascota->name) {
                    intercambiar = true;
                }
            } else { // Descendente
                if (cita[indices[j]].mascota->name < cita[indices[j+1]].mascota->name) {
                    intercambiar = true;
                }
            }

            if (intercambiar) {
                int temp = indices[j];
                indices[j] = indices[j+1];
                indices[j+1] = temp;
            }
        }
    }

    // Mostrar citas ordenadas
    cout << "\n=== CITAS PROGRAMADAS ===\n";
    cout << "ID Cita\tMascota\t\tDueño\n";
    cout << "----------------------------------------\n";

    for (int i = 0; i < count; i++) {
        int idx = indices[i];
        cout << cita[idx].id << "\t"
             << cita[idx].mascota->name << "\t\t"
             << cita[idx].duenio->name << " " << cita[idx].duenio->apPat << "\n";
    }
}

void prueba(){
    // Cliente 1
    cli[0].idUser = 2712;
    cli[0].name = "Jesus Emmanuel";
    cli[0].apPat = "Alonso";
    cli[0].apMat = "Piedras";
    cli[0].correo = "elexdero12@gmail.com";
    cli[0].tel = "5567551960";
    cli[0].direccion = "Soledad 8, 09510, CDMX";

    // Mascota 1
    mas[0].name = "Bombon";
    mas[0].raza = "Schnauzer";
    mas[0].color = "Gris pimienta";
    mas[0].edad = 5;
    mas[0].peso = 13.2;
    mas[0].altura = 1.1;
    mas[0].genero = 'H';
    mas[0].cli = &cli[0];

    // Cliente 2
    cli[1].idUser = generateID();
    cli[1].name = "Mayra";
    cli[1].apPat = "Piedras";
    cli[1].apMat = "Guerrero\t";
    cli[1].correo = "may123@gmail.com";
    cli[1].tel = "5566767463";
    cli[1].direccion = "Soledad 8, 09510, CDMX";

    //mascota 2
    mas[1].name = "Rocko";
    mas[1].raza = "Boxer";
    mas[1].color = "Negro";
    mas[1].edad = 4;
    mas[1].peso = 15;
    mas[1].altura = 0.90;
    mas[1].genero = 'M';
    mas[1].cli = &cli[1];
    //mascota 3
    mas[2].name = "Spark";
    mas[2].raza = "Chihuahua";
    mas[2].color = "Cafe";
    mas[2].edad = 6;
    mas[2].peso = 6;
    mas[2].altura = 0.40;
    mas[2].genero = 'H';
    mas[2].cli = &cli[1];
    
    //cliente 3
    cli[2].idUser = generateID();
    cli[2].name = "emiliano";
    cli[2].apPat = "Galindo";
    cli[2].apMat = "Gonzalez";
    cli[2].correo = "emi123@gmail.com";
    cli[2].tel = "5566448810";
    cli[2].direccion = "Canal de San Juan CDMX";

    //mascota 4
    mas[3].name = "Buzz";
    mas[3].raza = "Maltes";
    mas[3].color = "Miel";
    mas[3].edad = 8;
    mas[3].peso = 12;
    mas[3].altura = 0.80;
    mas[3].genero = 'M';
    mas[3].cli = &cli[2];

    //cliente 4
    cli[3].idUser = generateID();
    cli[3].name = "Sharon";
    cli[3].apPat = "Perez";
    cli[3].apMat = "Guerrero\t";
    cli[3].correo = "sharon_medel123@gmail.com";
    cli[3].tel = "5552126355";
    cli[3].direccion = "Palmeras #256 CDMX";
    //mascota 5
    mas[4].name = "Skipper";
    mas[4].raza = "";
    mas[4].color = "Miel";
    mas[4].edad = 8;
    mas[4].peso = 12;
    mas[4].altura = 0.80;
    mas[4].genero = 'M';
    mas[4].cli = &cli[3];

    //mascota 6
    mas[5].name = "Max";
    mas[5].raza = "Labrador";
    mas[5].color = "Negro";
    mas[5].edad = 5;
    mas[5].peso = 25.3;
    mas[5].altura = 60.5;
    mas[5].genero = 'M';
    mas[5].cli = &cli[3];
    

    cli[5].idUser = generateID();
    cli[5].name = "Carlos";
    cli[5].apPat = "Ramírez";
    cli[5].apMat = "López\t";
    cli[5].correo = "carlos.ramirez@example.com";
    cli[5].tel = "5551234567";
    cli[5].direccion = "Av. Reforma 123, CDMX";
    //mascota 7
    mas[6].name = "Luna";
    mas[6].raza = "Poodle";
    mas[6].color = "Blanco";
    mas[6].edad = 3;
    mas[6].peso = 8.7;
    mas[6].altura = 50;
    mas[6].genero = 'H';
    mas[6].cli = &cli[5];

    cli[6].idUser = generateID();
    cli[6].name = "Lucía";
    cli[6].apPat = "Martínez";
    cli[6].apMat = "Cruz\t";
    cli[6].correo = "lucia.martinez@example.com";
    cli[6].tel = "5567894321";
    cli[6].direccion = "Calle Hidalgo 55, CDMX";
    //mascota 8
    mas[7].name = "Rocky";
    mas[7].raza = "Bulldog Francés";
    mas[7].color = "Atigrado";
    mas[7].edad = 4;
    mas[7].peso = 12.5;
    mas[7].altura = 32;
    mas[7].genero = 'M';
    mas[7].cli = &cli[6];

    cli[7].idUser = generateID();
    cli[7].name = "Andrés";
    cli[7].apPat = "Hernández";
    cli[7].apMat = "Gómez";
    cli[7].correo = "andres.hg@example.com";
    cli[7].tel = "5553332211";
    cli[7].direccion = "Col. Del Valle #78, CDMX";
    //mascota 9
    mas[8].name = "Nina";
    mas[8].raza = "Beagle";
    mas[8].color = "Tricoor";
    mas[8].edad = 2;
    mas[8].peso = 10.5;
    mas[8].altura = 40;
    mas[8].genero = 'H';
    mas[8].cli = &cli[7];


    cli[8].idUser = generateID();
    cli[8].name = "Valeria";
    cli[8].apPat = "Torres";
    cli[8].apMat = "Jiménez\t";
    cli[8].correo = "valeria.tj@example.com";
    cli[8].tel = "5544556677";
    cli[8].direccion = "Insurgentes Sur 890, CDMX";

    cli[9].idUser = generateID();
    cli[9].name = "Daniel";
    cli[9].apPat = "Sánchez";
    cli[9].apMat = "Moreno\t";
    cli[9].correo = "daniel.sanchez@example.com";
    cli[9].tel = "5588994455";
    cli[9].direccion = "Eje 6 Sur 66, Iztapalapa, CDMX";
    //mascota 10
    mas[9].name = "Simba";
    mas[9].raza = "Golden Retriever";   
    mas[9].color = "Dorado";
    mas[9].edad = 6;
    mas[9].peso = 30.0;
    mas[9].altura = 65.5;
    mas[9].genero = 'M';
    mas[9].cli = &cli[9];

    cli[10].idUser = generateID();
    cli[10].name = "Alejandro";
    cli[10].apPat = "Perez";
    cli[10].apMat = "Hernandez";
    cli[10].correo = "ale123@gmail.com";
    cli[10].tel = "5552126355";
    cli[10].direccion = "Bugambilias #256 CDMX";

    cli[11].idUser = generateID();
    cli[11].name = "Emilio";
    cli[11].apPat = "Galván";
    cli[11].apMat = "Vargas\t";
    cli[11].correo = "emilio.galvan@example.com";
    cli[11].tel = "5566778899";
    cli[11].direccion = "Pino Suárez 321, CDMX";

    cli[12].idUser = generateID();
    cli[12].name = "Alejandra";
    cli[12].apPat = "Flores";
    cli[12].apMat = "Ruiz\tx";
    cli[12].correo = "ale.flores@example.com";
    cli[12].tel = "5599887766";
    cli[12].direccion = "Roma Norte #102, CDMX";
    //mascota11
    mas[10].name = "Thor";
    mas[10].raza = "Husky Siberiano";
    mas[10].color = "Gris y blanco";
    mas[10].edad = 5;
    mas[10].peso = 28.4;
    mas[10].altura = 60.0;
    mas[10].genero = 'M';
    mas[10].cli = &cli[12];

}

int generateID(){
    numRanID = rand() % 9000 + 1000; // Genera números entre 1000-9999
    return numRanID;
}