#include <iostream>
#include <string>
#include <cctype>//validaciones de entrada
#define MAX 20//maximo de clientes y citas

struct cliente{
    char* name;
    char* apPat;
    char* apMat;
    char* correo;
    char* tel;
    char* direccion;
}; struct cliente cli[MAX];

struct mascota{
    char* name;
    char* raza;
    char* color;
    int* edad;
    int* peso;
    int* tamaño;
    char* sexo;
    cliente* cli;
}; struct mascota mas[MAX];

struct servicios{
    bool bano;
    bool cortePelo;
    bool corteUñas;
    bool limpiezaOidos;
    bool lavadoDientes;
}; struct servicios serv[MAX];

struct cita{
    char* inHora;//formato hh:mm
    char* inFecha;//formato dd/mm/yyyy
    char* outHora;//formato hh:mm
    char* outFecha;//formato dd/mm/yyyy
    cliente* duenio;
    mascota* mascota;
    servicios* serv[5];
}; struct cita cita[MAX];

// Function prototypes
void menu();

using namespace std;

int main(){
        cout<<"\t\t\t\tVETERINARIA HUELLITAS FELICES\n\n\n";
        cout<<"\tBienvenido/a a su veterinaria favorita.\n\n\n";
        menu();


    return 0;
}

void menu(){
        int op;
        do{
        cout<<"\tMenu de opciones.\n\n";
        cout<<"\t\t1. Agendar una cita\n";
        cout<<"\t\t2. Consultar datos de una cita\n";
        cout<<"\t\t3. Modificar datos de una cita\n";
        cout<<"\t\t4. Cancelar una cita\n";
        cout<<"\t\t5. Primer visita\n";
        cout<<"\t\t6. Salir\n\n";
        cout<<"\tElija una opcion: "; cin>>op;
        // Validación de entrada
        if(cin.fail() || op < 1 || op > 6){
            cin.clear(); // Limpia el error
            cin.ignore(1000, '\n'); // Descarta la entrada incorrecta
            system("cls"); // Limpia la pantalla (en Windows)
            cout<<"\t\t\t\tVETERINARIA HUELLITAS FELICES\n\n\n";
            cout<<"\tBienvenido/a a su veterinaria favorita.\n\n\n";
            cout<<"Opción inválida, intente nuevamente.\n\n";
            continue;
        }
        switch (op)
        {
        case 1:
            system("cls"); // Limpia la pantalla (en Windows)
            cout<<"\tAgendar una cita\n";
            //llamada a la función para agendar una cita
            break;
        case 2:
            cout<<"\tConsultar datos de una cita\n";
            //llamada a la función para consultar datos de una cita
            break;
        case 3:
            cout<<"\tModificar datos de una cita\n";
            //llamada a la función para modificar datos de una cita
            break;
        case 4:
            cout<<"\tCancelar una cita\n";
            //llamada a la función para cancelar una cita
            break;
        case 5:
            cout<<"\tPrimer visita\n";
            //llamada a la función para registrar una primera visita
            break;
        case 6:
            cout<<"\tGracias por usar el programa\n";
            break;
        default:
            cout<<"\n";
            break;
        }
    }while(op != 6);
}