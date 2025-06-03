#include <iostream>
#include <string>
#define MAX 20//maximo de clientes y citas

struct cliente{
    char* name;
    char* apPat;
    char* apMat;
    char* correo;
    char* tel;
    char* direccion;
}; struct cliente cli[];

struct mascota{
    char* name;
    char* raza;
    char* color;
    int* edad;
    int* peso;
    int* tamaño;
    char* sexo;
    cliente* cli;
}; struct mascota mas[];

struct servicios{
    bool bano;
    bool cortePelo;
    bool corteUñas;
    bool limpiezaOidos;
    bool lavadoDientes;
}; struct servicios serv[];

struct cita{
    char* inHora;//formato hh:mm
    char* inFecha;//formato dd/mm/yyyy
    char* outHora;//formato hh:mm
    char* outFecha;//formato dd/mm/yyyy
    cliente* duenio;
    mascota* mascota;
    servicios* serv[5];
}; struct cita cita[MAX];

using namespace std;

int main(){
    int op;
    cout<<"\t\t\tVETERINARIA HUELLITAS FELICES\n\n";
    cout<<"Bienvenido/a a su veterinaria favorita.\n\n";
    cout<<"Menu de opciones:\n";
    cout<<"1. Agendar una cita\n";
    cout<<"2. Consultar datos de una cita\n";
    cout<<"3. Modificar datos de una cita\n";
    cout<<"4. Cancelar una cita\n";
    cout<<"5. Primer visita\n";
    cout<<"6. Salir\n\n";
    cout<<"Por favor, elija una opcion: "; cin>>op;
    switch (op)
    {
    case 1:
        cout<<"Agendar una cita\n";
        //llamada a la función para agendar una cita
        break;
    case 2:
        cout<<"Consultar datos de una cita\n";
        //llamada a la función para consultar datos de una cita
        break;
    case 3:
        cout<<"Modificar datos de una cita\n";
        //llamada a la función para modificar datos de una cita
        break;
    case 4:
        cout<<"Cancelar una cita\n";
        //llamada a la función para cancelar una cita
        break;
    case 5:
        cout<<"Primer visita\n";
        //llamada a la función para registrar una primera visita
        break;
    default:
        cout<<"Opción no valida, intente nuevamente.\n";
        break;
    }

    return 0;
}