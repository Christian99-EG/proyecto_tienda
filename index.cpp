#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iomanip>

using namespace std;

/*Estructura principal*/
struct lista
{ //estructura lista
 int nro;
 struct lista *sgte;

 string plr;
 struct lista *sgteP;

};
/*fin de la estructura principal*/

typedef struct lista *ptrLista;
typedef struct lista *ptrListaS;

void agrega_productoC(ptrLista &p, int valor)
{ //agrega el precio del producto
  ptrLista aux;
  aux = new (struct lista);
  aux -> nro = valor;
  aux ->sgte = p;
  p = aux;
}

void agrega_productoN(ptrListaS &s,string palabra)
{ //agrega el nombre del producto

  ptrListaS auxs;
  auxs = new (struct lista);
  auxs -> plr = palabra;
  auxs -> sgteP = s;
  s = auxs;
}

void cancelar_productoC(ptrLista &p,int valor)
{//cancela los productos de manera individual (elimina el precio)
  ptrLista aux, antN;
  aux = p;
   if(p != NULL)
   {
     while(aux != NULL)
     {
       if(aux -> nro == valor)
       {
          if(aux == p)
           p = p -> sgte;
           else
            antN -> sgte = aux -> sgte;
            delete (aux);
            return;
       }
       antN = aux;
       aux = aux -> sgte;
     }
     cout<<"su lista de productos no tiene ningun producto Actualmente "<<endl;
   }
}

void cancelar_productoS(ptrListaS &s, string palabra)
{//cancela los productos de manera individual (elimina el nombre del producto)
  ptrListaS auxs, antP;
   auxs = s;
    if(s != NULL)
    {
      while(auxs != NULL)
      {
         if(auxs -> plr == palabra)
         {
           if(auxs == s)
           s = s -> sgteP;
           else
            antP -> sgteP = auxs -> sgteP;
            delete (auxs);
            return;
         }
         antP = auxs;
         auxs = auxs -> sgteP;
      }
      cout<<"no tiene Actualmente ningun producto en su carrito"<<endl;
    }
}

void lista_productosC(ptrLista &p, ptrListaS &s)
{//muestra el precio de los articulos
  ptrLista aux;
  ptrListaS auxs;

  aux = p;
  auxs = s;

  while(aux != NULL && auxs != NULL){
    cout<<"\t"<<auxs -> plr<<" ===============================  \t\t["<<aux -> nro<<"]"<<"\n";
    auxs = auxs -> sgteP;
    aux = aux -> sgte;
  }
}

int Sumar_costoT(ptrLista &p)
{ //suma el costo total de la compra
  int adition = 0;
   while(p != NULL){
    adition = adition + p -> nro;
    p = p -> sgte;
   }
   return adition;
}
float Sumar_costoT_descuento(ptrLista &p)
{
  int aditionDesc = 0, opDesc;
  cout<<"que tipo de descuento aplicara: ";
  cin>>opDesc;

  switch (opDesc) {
   case 1:{
      while(p != NULL){
        aditionDesc = aditionDesc + (p -> nro)*0.25;
        p = p ->sgte;
      }
      return aditionDesc;
      break;}
    case 2:{
      while(p != NULL){
        aditionDesc = aditionDesc + (p -> nro)*0.30;
        p = p ->sgte;
      }
      return aditionDesc;
      break;}

    case 3:{
      while(p != NULL){
        aditionDesc = aditionDesc + (p -> nro)*0.50;
        p = p ->sgte;
      }
      return aditionDesc;
      break;}

    case 4:{
      while(p != NULL){
        aditionDesc = aditionDesc + (p -> nro)*0.50;
        p = p ->sgte;
      }
      return aditionDesc;
      break;}
    case 5:{
      while(p != NULL){
        aditionDesc = aditionDesc + (p -> nro)*0.30;
        p = p ->sgte;
      }
      return aditionDesc;
      break;}
  }
}
class Tienda_matriz
{
  friend void agrega_productoC(ptrLista &p, int valor);
  friend void agrega_productoN(ptrListaS &s,string palabra);
  friend void cancelar_productoC(ptrLista &p, int valor);
  friend void cancelar_productoS(ptrListaS &s,string palabra);
  friend void lista_productosC(ptrLista &p,ptrListaS &s);
  friend int Sumar_costoT(ptrLista &p);
  friend float Sumar_costoT_descuento(ptrLista &p);
public:
  int codigo;       //atributo de tipo unidad (int) para cada articulo
  float costo;      //precio asignado para cada articulo
  float costoT;     //precio total de la compra (tambien puede aplicarse la compra al meyoreo)
  float T_pagar;    //total de articulos seleccionados
  float TC_descuento_Aplicado; //que descuento se esta aplicando a cada departamento y/o producto
  string nombre_producto;
  ptrLista p = NULL;
  ptrListaS s = NULL;
public:
  Tienda_matriz(); //CONSTRCUTOR ESTANDAR
  ~Tienda_matriz(); //DESTRUCTOR ESTANDAR
  virtual void Tipo_Articulo(); //QUE ARTICULO SE SELECCIONO POR CADA DEPARTAMENTO
  virtual void Cancelar_compra();
  virtual void CantidadT(); //cantidad total por todos los articulos
  //virtual int codigo_articulo(); //codigo por cada articulo
  virtual void oferta(); //que oferta se le dara al cliente, nota se despliega una lista de descuentos RECUERDALO
  virtual int descuento(); //aplica el descuento a cada articulo comprado
  //virtual void total_pagar_Descuento(); //CANTIDAD A PAGAR CON DESCUENTO APLICADO
  virtual void listaCompra();
}; //fin de mi clase Tienda_matriz


/*----------------------inicio de la declaracion de metodos de la funcion--------------------------*/
/*-------------------------------------junto con  constructores-----------------------------------*/

/*********** CONSTRUCTORES y DESTRUCTORES **************/
Tienda_matriz::Tienda_matriz(){}  //constructor estandar

Tienda_matriz::~Tienda_matriz(){} //destructor estandar
/******** FIN DE LOS CONSTRUCTORES  Y DESTRUCTORES ***********/


void Tienda_matriz::Tipo_Articulo()
{
  int agregar;

  do{
   cout<<"Que articulo va a agregar a su lista: ";
    cin>>nombre_producto;
    agrega_productoN(s,nombre_producto);
   cout<<"producto: "<<nombre_producto<<" agregado a su lista."<<endl;
   cout<<"precio: ";
    cin>>costo;
    agrega_productoC(p,costo);
   cout<<"desea agregar otro articulo a su lista: \n";
   cout<<"1. SI \n";
   cout<<"0. NO \n";
   cout<<"$> ";
    cin>>agregar;
 }while(agregar != 0);
}
void Tienda_matriz::Cancelar_compra()
{
   cout<<"que producto desea cancelar: ";
   cin>>nombre_producto;
   cancelar_productoS(s,nombre_producto);
   cout<<"costo del producto: ";
   cin>>costo;
   cancelar_productoC(p,costo);
}

void Tienda_matriz::oferta()
{

  cout<<"\t **************************************************"<<endl;
  cout<<"\t *                 DESCUENTOS DEL MES             *"<<endl;
  cout<<"\t **************************************************"<<endl;
  cout<<"\n \t sujeto a disponiblilidad"<<endl;
  cout<<"\n"<<endl;

  cout<<"\t\t _________________________________________________________ "<<endl;
  cout<<"\t\t| aplicable para             |           descuentos       |"<<endl;
  cout<<"\t\t|---------------------------------------------------------|"<<endl;
  cout<<"\t\t| 1. Estudiantes             |            [ 25 %]         |"<<endl;
  cout<<"\t\t|----------------------------|----------------------------|"<<endl;
  cout<<"\t\t| 2. ADULTOS MAYORES         |            [ 30 %]         |"<<endl;
  cout<<"\t\t|----------------------------|----------------------------|"<<endl;
  cout<<"\t\t| 3. ESTUDIANTES IPN         |            [ 50 %]         |"<<endl;
  cout<<"\t\t|----------------------------|----------------------------|"<<endl;
  cout<<"\t\t| 4. DOCTORES Y ENFERMER@S   |            [ 5O %]         |"<<endl;
  cout<<"\t\t|----------------------------|----------------------------|"<<endl;
  cout<<"\t\t| 5. MAESTR@S                |            [ 30 %]         |"<<endl;
  cout<<"\t\t-----------------------------------------------------------"<<endl;
}

int Tienda_matriz::descuento()
{ //verificar la funcionalidad de este metodo
  cout<<"el descuento se ha aplicado: \n";
  cout<<"el total a pagar es :"<<Sumar_costoT_descuento(p);
}

void Tienda_matriz::listaCompra()
{
  cout<<"su lista de compras total es: "<<endl;
  lista_productosC(p,s);
}

void Tienda_matriz::CantidadT()
{ //metodo que me muestra la cantidad total a pagar de la compra (es el ticket)
  cout<<"\t\t\t##############################################################################"<<endl;
  cout<<"\t\t\t#                             THE POWER RANGER                               #"<<endl;
  cout<<"\t\t\t#                             ticket de compra                               #"<<endl;
  cout<<"\t\t\t#                LA TIENDA OFICIAL DE E.S.I.M.E CULHUACAN                    #"<<endl;
  cout<<"\t\t\t#      Av. Sta. Ana 1000, Francisco Culhuacan CTM V, Coyoacan, 04440         #"<<endl;
  cout<<"\t\t\t#                           CIUDAD DE MEXICO, CDMX                           #"<<endl;
  cout<<"\t\t\t#                              TEL: 5556242000                               #"<<endl;
  cout<<"\t\t\t##############################################################################"<<endl;
  cout<<"\n \n"<<endl;

  cout<<"sus siguientes articulos son:"<<endl;
  lista_productosC(p,s);
  cout<<"\t\t\t el total a pagar sera de: "<<Sumar_costoT(p)<<endl;
  cout<<"\t\t\t gracias por su compra \n";
}

class Dep_General:public Tienda_matriz
{

friend void agrega_productoC(ptrLista &p, int valor);
friend void agrega_productoN(ptrListaS &s,string palabra);
friend void cancelar_productoC(ptrLista &p,int valor);
friend void cancelar_productoS(ptrListaS &s,string palabra);

private:
  float Costo_M; //costo por mayoreo
  int cantidad_articulos; //cantidad de articulos por volumen (mayoreo)
  float TVolumen; //total de articulos vendidos por vulumen
public:

  Dep_General();
  ~Dep_General();

  void CostoMayoreoT(); //total a pagar por mayoreo
  void Micronegocio(); //se comprara un volmen menor de productos y se le hara un descuento para Micronegocio

  //metodos miembro heredados
  //int CantidadT();
 // int codigo_articulo();  //aplicar a un codigo general por volumen de productos comprados
  //void oferta();          //verificar herencia y poliformismo
  //int descuento();        //descuento aplicable a un total de volumen de productos comprados
  //void total_pagar();    //total a pagar por volumen de productos comprados

  //se incluyen por un codigo mas entendible para demostrar la herencia y el poliformismo

};

Dep_General::Dep_General(){}
Dep_General::~Dep_General(){}

void Dep_General::CostoMayoreoT()
{ //metodo que me calcula el precio por cada articulo que se compra al mayoreo
  int unidades;

   cout<<"que producto va a comprar: ";
   cin>>nombre_producto;
     agrega_productoN(s,nombre_producto);
   cout<<"costo: ";
   cin>>costo;
   cout<<"cuantas unidades va a comprar:";
   cin>>unidades;
   costo = costo*unidades;
     agrega_productoC(p,costo);
  cout<<"se ha agregado la compra al mayoreo del producto: "<<nombre_producto<<" con un costo de: "<<costo<<" total";
}


void menu(void); //prototipo de la funcion menu

int main(void)
{
  menu();
return 0;
}

void menu(void)
{
  char letra = 164; //letra ñ en minuscula (ASCII)
  char letraM = 165; //letra Ñ en mayuscula (ASCII)

  Tienda_matriz objtiendaMatriz;
  int opcionP;
  do{
  cout<<"\t\t\t##############################################################################"<<endl;
  cout<<"\t\t\t#                             THE POWER RANGER                               #"<<endl;
  cout<<"\t\t\t#                LA TIENDA OFICIAL DE E.S.I.M.E CULHUACAN                    #"<<endl;
  cout<<"\t\t\t#      Av. Sta. Ana 1000, Francisco Culhuacan CTM V, Coyoacan, 04440         #"<<endl;
  cout<<"\t\t\t#                           CIUDAD DE MEXICO, CDMX                           #"<<endl;
  cout<<"\t\t\t#                              TEL: 5556242000                               #"<<endl;
  cout<<"\t\t\t##############################################################################"<<endl;
  cout<<"\n \n"<<endl;

  cout<<"\t\t\t\t\tSELECCIONE UN DEPARTAMENTO: "<<endl;
  cout<<"\t\t\t\t _____________________________________________"<<endl;
  cout<<"\t\t\t\t|  1. HOMBRE                                  |"<<endl;
  cout<<"\t\t\t\t|  2. MUJER                                   |"<<endl;
  cout<<"\t\t\t\t|  3. BEBES DE 0-24 MESES                     |"<<endl;
  cout<<"\t\t\t\t|  4. NI"<<letraM<<"OS Y NI"<<letraM<<"AS \t\t \t      |"<<endl;
  cout<<"\t\t\t\t|  5. ADOLESCENTES                            |"<<endl;
  cout<<"\t\t\t\t|  6. UNIFORMES PARA ESTUDIANTES              |"<<endl;
  cout<<"\t\t\t\t|  7. CUIDADO PERSONAL                        |"<<endl;
  cout<<"\t\t\t\t|  8. Electronica                             |"<<endl;
  cout<<"\t\t\t\t|  9. VARIOS   (COMPRA AL MAYOREO)            |"<<endl;
  cout<<"\t\t\t\t| 10. CANCELAR PRODUCTOS                      |"<<endl;
  cout<<"\t\t\t\t| 11. REALIZAR COMPRA                         |"<<endl;
  cout<<"\t\t\t\t| 12. VER LISTA DE COMPRAS                    |"<<endl;
  cout<<"\t\t\t\t|_____________________________________________|"<<endl;
  cout<<"\n"<<endl;

  cout<<"\t\t\t***********************************************************************"<<endl;
  cout<<"\t\t\t*                             ATENCION                                *"<<endl;
  cout<<"\t\t\t*  O bien ingrese la contrase"<<letra<<"a para acceder al area de control...    *"<<endl;
  cout<<"\t\t\t*      puede ingresar la contrase"<<letra<<"a en entrada de opcion \t      *"<<endl;
  cout<<"\t\t\t***********************************************************************"<<endl;

  cout<<"\t su opcion es $>: ";
  cin>>opcionP; //opcionP == opcion principal
  system("cls");
  switch (opcionP) {
    case 1:{

        cout<<"\t \t \t DEPARTAMENTO DE ROPA Y ACCESORIOS PARA HOMBRE \n";
        system("cls");
      break;}

    case 2:{
      cout<<"\t \t \t DEPARTAMENTO DE ROPA Y ACCESORIOS PARA MUJER \n";
      system("pause");
      system("cls");
      break;}

    case 3:{
      system("cls");
      cout<<"\t \t \t DEPARTAMENTO DE BEBES DE 0-24 MESES \n";
      system("pause");
      system("cls");
      break;}

    case 5:{

      break;}

    case 6:{
      break;}

    case 7:{
      break;}

    case 8:{
      break;}

    case 9:{
      objtiendaMatriz.Tipo_Articulo();
      break;}

  case 10:{
    objtiendaMatriz.CantidadT();
    system("pause");
    break;}

  case 11:{
    int aplicarDes;
  	system("cls");
  	objtiendaMatriz.CantidadT();
    cout<<"o bien, quiere plicar un descuento a su compra? : \n";
    cout<<" SI -> 1 \n NO -> 0"<<endl;
    cout<<"desea aplicar descuento: ";
    cin>>aplicarDes;
    if(aplicarDes == 1){
    objtiendaMatriz.oferta();
    cout<<"el total a pagar sera de : "<<objtiendaMatriz.descuento()<<endl;
    system("pause");
  }else{
    cout<<"entonces su compra seria de: ";
    objtiendaMatriz.CantidadT();
    system("pause");
  }
	break;}

  case 12:{
  	  system("cls");
      cout<<"\t \t \t LISTA DE COMPRAS \n";
      objtiendaMatriz.listaCompra();
      system("pause");
  break;}

  }
}while(opcionP != 0);
}
