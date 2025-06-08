#include <iostream>
#include <conio.h>
#include <string>
#include <cctype> //validaciones de entrada
#define MAX 20    // maximo de clientes y citas
using namespace std;

struct cliente
{
    int id;
    string name;
    string apPat;
    string apMat;
    string correo;
    string tel;
    string direccion;
};
struct cliente cli[MAX];

struct mascota
{
    string name;
    string raza;
    string color;
    int edad;
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
struct servicios serv[5];

struct cita
{
    string inHora;   // formato hh:mm
    string inFecha;  // formato dd/mm/yyyy
    string outHora;  // formato hh:mm
    string outFecha; // formato dd/mm/yyyy
    cliente *duenio;
    mascota *mascota;
    servicios *serv[5];
};
struct cita cita[MAX];

// Function prototypes
// int agendarCita(cliente* cli, mascota* mas, servicios* serv);
int NewClient(cliente cli[MAX]);
void Mostrar();
void subMenu(); // Prototipo de la función subMenu

// variables globales
int op;

int main()
{
    cout << "\t\t\t\tESTETICA HUELLITAS FELICES\n\n\n";
    cout << "\tBienvenido/a a su estetica favorita.\n\n\n";
    do
    {
        cout << "\tMenu de opciones.\n\n";
        cout << "\t\t1. Agendar una cita\n";
        cout << "\t\t2. Consultar datos de una cita\n";//modificar datos de una cita y cancelar una cita
        cout << "\t\t3. Soy cliente nuevo\n";//pendiente
        cout << "\t\t4. Salir\n\n";
        cout << "\tElija una opcion: ";
        cin >> op;
        // Validación de entrada
        if (cin.fail() || op < 1 || op > 4)
        {
            cin.clear();            // Limpia el error
            cin.ignore(1000, '\n'); // Descarta la entrada incorrecta
            system("cls");          // Limpia la pantalla (en Windows)
            cout << "\t\t\t\tESTETICA HUELLITAS FELICES\n\n\n";
            cout << "\tBienvenido/a a su veterinaria favorita.\n\n\n";
            cout << "Opción inválida, intente nuevamente.\n\n";
            continue;
        }
        switch (op)
        {
        case 1:
            system("cls");
            cout << "\tAgendar una cita\n";
            break;
        case 2:
            cout << "\tConsultar datos de una cita\n";
            // llamada a la función para consultar datos de una cita, modificar o borrar
            break;
        case 3:
            cout << "\thaciendoloooooooooooooooooooooooooo\n";
            // llamada a la función para modificar datos de una cita
            break;
        case 4:
            cout << "\tSalir\n";
            // llamada a la función para cancelar una cita
            break;
        case 5:
            cout << "\tGracias por usar el programa\n";
            break;
        default:
            cout << "\n";
            break;
        }
    } while (op != 5);
    return 0;
}


