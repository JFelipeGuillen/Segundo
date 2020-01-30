#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include<string.h>
#include <ctype.h>

typedef struct nodo{
	char cedula[10];
	char nombre[30];
	char apellido[30];
	char direccion[50];
	char correo[35];
	char telefono[10];
	char diagnostico[30];
	char medicaciones[50];
	char tipo_consulta[20];
	int dia;
	int mes; 
	int anio;
	int edad;
	float pago_total;
	
	struct nodo *siguiente;
	struct nodo *anterior;
} tipoNodo;

typedef tipoNodo *pNodo, *lista;

pNodo Crear_nodo(void);
void Insertar_nodo(lista *lista);
void Presentar_lista(lista lista);
//void Consultar_paciente(lista *lista);
//void Eliminar_paciente(lista *lista);
//void Modificar(lista *lista);
float pago(int edad, char* consulta);
int Validar_numero(char numero[]);
int Validar_palabra(char palabra[]);


int main(){
	lista lista = NULL;
	int op;
	
	do{
	printf("________________MENU_________________");
	printf("\n 1. Ingresar paciente");
	printf("\n 2. Consultar datos de un paciente");
	printf("\n 3. Presentar lista de pacientes");
	printf("\n 4. Eliminar paciente");
	printf("\n 5. Modificar dato");
	printf("\n 6. Salir");
	printf("\n_____________________________________");
	printf("\n Ingrese una opcion: ");
	scanf("%d",&op);
	system("cls");
	
	switch(op){
		case 1:
			Insertar_nodo(&lista);
			getch();
			system("cls");
		break;
		case 2:
			//Consultar_paciente(&lista);
			system("cls");
		break;
		case 3:
			Presentar_lista(lista);
			getch();
			system("cls");
		break;
		case 4:
			//Eliminar_paciente(&lista);
			system("cls");
		break;
		case 5:
			//Modificar(&lista);
			getch();
			system("cls");
		break;
		case 6:
			printf("\n Gracias por usar nuestro sistema");
		break;
	}
	
	}while(op != 6);
	return 0;
}

pNodo Crear_nodo(void){
	pNodo nuevo;
	nuevo = (pNodo)malloc(sizeof(tipoNodo));
	int opcion;
	int validacion;
	
	char *general = "Medicina general";
	char *especial = "Especializacion";
	char *si = "Si";
	char *no = "No";
	
	
	if(nuevo != NULL){
		printf("________________________DATOS PERSONALES________________________");
		
		fflush(stdin);
		do
		{
		printf("\nIngrese el numero de cedula del paciente: ");
		gets(nuevo->cedula);
		validacion = Validar_numero(nuevo->cedula);
		}while(validacion == 0 || strlen(nuevo->cedula)>10);
		fflush(stdin);
		
		fflush(stdin);
		printf("Ingrese los nombres del paciente: ");
		gets(nuevo->nombre);
		fflush(stdin);
	
		fflush(stdin);
		printf("Ingrese los apellidos del paciente: ");
		gets(nuevo->apellido);
		fflush(stdin);
	
		fflush(stdin);	
		do{
		printf("Ingrese la edad del paciente: ");
		scanf("%d",&nuevo->edad);
		}while(nuevo->edad < 1);
		fflush(stdin);
		
		fflush(stdin);	
		do
		{
		printf("Ingrese el numero de telefono del paciente: ");
		scanf("%s", nuevo->telefono);
		validacion = Validar_numero(nuevo->telefono);
		}while(validacion == 0 || strlen(nuevo->telefono)>9);
		fflush(stdin);
		
		fflush(stdin);	
		printf("Ingrese el correo electronico del paciente: ");
		gets(nuevo->correo);
		fflush(stdin);
	
		fflush(stdin);	
		printf("Ingrese la direccion de domicilio del paciente: ");
		gets(nuevo->direccion);
		fflush(stdin);
		
		fflush(stdin);
		printf("El paciente ha sido diagnosticado de alguna enfermedad?");
		printf("\n1. Si");
		printf("\n2. No");
		do{
		printf("\nOpcion: ");
		scanf("%d",&opcion);
		}while(opcion<1 && opcion >2);	
		switch(opcion){
			case 1:
				strcpy(nuevo->diagnostico,si);
			break;
			case 2:
				strcpy(nuevo->diagnostico,no);
			break;
		}
		fflush(stdin);

		fflush(stdin);
		printf("El paciente toma algun medicamento?:");
		printf("\n1. Si");
		printf("\n2. No");
		do{
		printf("\nOpcion: ");
		scanf("%d",&opcion);
		switch(opcion){
			case 1:
				strcpy(nuevo->medicaciones,si);
			break;
			case 2:
				strcpy(nuevo->medicaciones,no);
			break;
		}
		}while(opcion<1 && opcion>2);
		fflush(stdin);
		
		system("cls");
		
		printf("\n___________________REGISTRO DE CONSULTA__________________");
		fflush(stdin);
		printf("\nIngrese el tipo de consulta que desea agendar");
		printf("\n1. Medicina general");
		printf("\n2. Especializacion\n");
		do{
		printf("\nOpcion: ");
		scanf("%d",&opcion);
		switch(opcion){
			case 1:
				strcpy(nuevo->tipo_consulta,general);
			break;
			case 2:
				strcpy(nuevo->tipo_consulta,especial);
			break;
		}
		}while(opcion<1 && opcion>2);
	
		fflush(stdin);
		printf("\nIngrese la fecha en la que desea agendar la consulta \n");
		do{
		printf("Dia: ");
		scanf("%d",&nuevo->dia);
		}while(nuevo->dia < 1 && nuevo->dia>31);
		fflush(stdin);
		
		fflush(stdin);
		do{
		printf("Mes: ");
		scanf("%d",&nuevo->mes);
		}while(nuevo->mes<1 && nuevo->mes>12);
		fflush(stdin);
		
		fflush(stdin);
		do{
		printf("Anio: ");
		scanf("%d",&nuevo->anio);
		}while(nuevo->anio<2019);
		fflush(stdin);
		
		nuevo->pago_total = pago(nuevo->edad,nuevo->tipo_consulta);
		
		return nuevo;
	}else{
		
		return NULL;
	}
}

void Insertar_nodo(lista *lista){
	pNodo nuevo, aux;
    nuevo=Crear_nodo();
	if(nuevo != NULL)
	{
		aux = *lista;
		if(aux!=NULL)
		{
			while(aux->anterior!=NULL)
			aux = aux->anterior;
		}
		if(aux==NULL || strcmp(aux->apellido,nuevo->apellido)>=0)
		{
			nuevo->siguiente = aux;			
      		nuevo->anterior = NULL;
	  		if(aux!=NULL)
	  		{
	  			aux->anterior = nuevo;
	  		}
      		if(*lista==NULL)
      		{
	  			*lista = nuevo;
	  		}
		}
		else
		{
			while((aux->siguiente!=NULL) && (strcmp(aux->siguiente->apellido,nuevo->apellido)<=0))
			{
				aux = aux->siguiente;
			}
			nuevo->siguiente = aux->siguiente;
      		aux->siguiente = nuevo;
      		nuevo->anterior = aux;
      		if(nuevo->siguiente != NULL)
      		{
			  nuevo->siguiente->anterior = nuevo;
			}
		}
	}
	else
	{
		printf("\n No se puede insertar ");
	}
}


void Presentar_lista(lista lista){
	pNodo aux = lista;
	
	if(lista == NULL){
		printf("\n No ha sido ingresado ningun paciente.\n");
	}else{
		while(aux->anterior!=NULL){
			aux = aux->anterior;
		}
		
		printf("\n                LISTA DE PACIENTES INGRESADOS\n");
		printf("\n____________________________________________________________");
		while(aux != NULL){
			printf("\n Apellido: %s",aux->apellido);
			printf("\n Nombre: %s",aux->nombre);	
			printf("\n Cedula: %d",aux->cedula);
			printf("\n Edad: %d",aux->edad);
			printf("\n Telefono: %d",aux->telefono);
			printf("\n Fecha de atencion: %d/%d/%d",aux->dia,aux->mes,aux->anio);
			printf("\n Direccion de domicilio: %s",aux->direccion);
			printf("\n Correo electronico: %s",aux->correo);
			printf("\n Enfermedad diagnosticada previamente: %s",aux->diagnostico);
			printf("\n Toma algun medicamento?: %s",aux->medicaciones);
			printf("\n Tipo de consulta agendada: %s",aux->tipo_consulta);
			printf("\n Pago total por la consulta: $ %.2f",aux->pago_total);
			printf("\n_____________________________________________________________");
			
			aux = aux->siguiente;
		}
	}
}

float pago(int edad, char* consulta){
	float ptotal;
	float descuento;
	float pago;
	
	if(strcmp(consulta,"Medicina general")==0){
		pago = 50;
		if(edad<18){
			descuento=(pago*0.30);
			ptotal=(pago-descuento);
		}else if(edad>50){
			descuento=(pago*0.50);
			ptotal=(pago-descuento);
		}else{
			ptotal=pago;
		}
	}else{
		pago = 70;
		if(edad<18){
			descuento=(pago*0.30);
			ptotal=(pago-descuento);
		}else if(edad>50){
			descuento=(pago*0.50);
			ptotal=(pago-descuento);
		}else{
			ptotal=pago;
		}
	}
	return ptotal;
}

/*void Consultar_paciente(lista *lista){
	pNodo aux;
	int ced;
	
	if(*lista!=NULL){
		fflush(stdin);
		do{
		printf("\nIngrese el numero de cedula del paciente: ");
		scanf("%d",&ced);
		}while(ced<1);
		system("cls");
		aux = *lista;
		fflush(stdin);
		
		if((aux!=NULL)&&(aux->cedula != ced)){
			aux=aux->siguiente;
		}
		if((aux!=NULL)&&(aux->cedula != ced)){
			aux=aux->anterior;
		}
		if(aux!=NULL){
			printf("            DATOS DEL PACIENTE ");
			printf("\n Apellido: %s",aux->apellido);
			printf("\n Nombre: %s",aux->nombre);	
			printf("\n Cedula: %d",aux->cedula);
			printf("\n Edad: %d",aux->edad);
			printf("\n Telefono: %d",aux->telefono);
			printf("\n Fecha de atencion: %d/%d/%d",aux->dia,aux->mes,aux->anio);
			printf("\n Direccion de domicilio: %s",aux->direccion);
			printf("\n Correo electronico: %s",aux->correo);
			printf("\n Enfermedad diagnosticada previamente: %s",aux->diagnostico);
			printf("\n Toma algun medicamento?: %s",aux->medicaciones);
			printf("\n Tipo de consulta agendada: %s",aux->tipo_consulta);
			printf("\n Pago total por la consulta: $ %.2f",aux->pago_total);
			getch();
		}
		else{
			system("cls");
			printf("\n No se encontro el cliente");
			getch();
		}
	}else{
		system("cls");
		printf("\n No se ha ingresado ningun cliente");
		getch();
	}	
}*/

/*void Eliminar_paciente(lista *lista){
	pNodo aux;
	int ced;
	
	if(*lista!=NULL){
		fflush(stdin);
		printf("\nIngrese el numero de cedula del paciente: ");
		scanf("%d",&ced);
		fflush(stdin);
		system("cls");
		aux = *lista;
		
		while((aux!=NULL)&&(aux->cedula!=ced)){
			aux = aux->siguiente;
		}
		while(aux!=NULL && aux->cedula!=ced){
			aux = aux->anterior;
		}
		if(aux == *lista)
		{
			if(aux->anterior)
			{
				*lista = aux->anterior;
			}
			else
			{
				*lista = aux->siguiente;
			}
		}
		if(aux->anterior!=NULL)
		{
			aux->anterior->siguiente = aux->siguiente;
		}
		if(aux->siguiente!=NULL)
		{
			aux->siguiente->anterior = aux->anterior;
		}
		free(aux);
		printf("\n Paciente eliminado");
		getch();
	}
	else
	{
		printf("\n No se ha ingresado a ningun paciente");
		getch();
	}
}*/

/*void Modificar(lista *lista){
	int opcion;
	int ced;
	pNodo aux;
	
	char *general="Medicina general";
	char *especial="Especializacion";
	char *si="Si";
	char *no="No";
	
		do{
		printf("\n Ingrese numero de cedula del paciente: ");
		scanf("%d",&ced);
		}while(ced<0);
		aux = *lista;
		while((aux!=NULL)&& (aux->cedula != ced)){
			aux = aux->siguiente;
		}
		while((aux!=NULL) && (aux->cedula!=ced)){
			aux = aux->anterior;
		}
		if(aux!=NULL){
			system("cls");
			do{
			printf("\nPaciente: %s %s",aux->apellido, aux->nombre);
			printf("\n\n Que dato desea modificar? ");
			printf("\n 1. Cedula");
			printf("\n 2. Nombre");
			printf("\n 3. Apellido");
			printf("\n 4. Edad");
			printf("\n 5. Direccion");
			printf("\n 6. Correo electronico");
			printf("\n 7. Telefono");
			printf("\n 8. Diagnostico previo");
			printf("\n 9. Medicacion");
			printf("\n 10. tipo de consulta");
			printf("\n 11 fecha de la consulta\n");
			printf("\n_________________________________");
			printf("\nOpcion:");
			scanf("%d", &opcion);
			system("cls");
			}while(opcion<1 && opcion>11);
			
			switch(opcion){
				case 1:
					fflush(stdin);
					
					printf("\n Ingrese el numero de cedula: ");
					gets(aux->cedula);
					
				break;
				case 2:
					fflush(stdin);
					printf("\n Ingrese los nombres del paciente: ");
					gets(aux->nombre);
				break;
				case 3:
					fflush(stdin);
					printf("\n Ingrese los apellidos del paciente: ");
					gets(aux->apellido);
				break;
				case 4: 
					fflush(stdin);
					do{
					printf("\n Ingrese la edad del paciente: ");
					scanf("%d",&aux->edad);
					}while(aux->edad<1);
					aux->pago_total = pago(aux->edad,aux->tipo_consulta);
				break;
				case 5:
					fflush(stdin);
					printf("\n Ingrese la direccion del paciente: ");
					gets(aux->direccion);
				break;
				case 6:
					fflush(stdin);
					printf("\n Ingrese el correo electronico del paciente: ");
					gets(aux->correo);
				break;
				case 7:
					fflush(stdin);
					do{
					printf("\n Ingrese el numero del telefono del paciente: ");
					scanf("%d", &aux->telefono);
					}while(aux->telefono<1 && aux->telefono > 999999999);
				break;
				case 8:
					fflush(stdin);
					printf("El paciente ha sido diagnosticado de alguna enfermedad?");
					printf("\n1. Si");
					printf("\n2. No");
					do{
					printf("\nOpcion: ");
					scanf("%d",&opcion);
					}while(opcion<1 && opcion >2);	
					switch(opcion){
					case 1:
					strcpy(aux->medicaciones,si);
					break;
					case 2:
					strcpy(aux->medicaciones,no);
					break;
					}
				break;
				case 9:
					fflush(stdin);
					printf("El paciente toma algun madecamento?:");
					printf("\n1. Si");
					printf("\n2. No");
					do{
					printf("\nOpcion: ");
					scanf("%d",&opcion);
					}while(opcion<1 && opcion>2);
					switch(opcion){
						case 1:
						strcpy(aux->medicaciones,si);
						break;
						case 2:
						strcpy(aux->medicaciones,no);
						break;
					}
				break;
				case 10:
					fflush(stdin);
					printf("\n Ingrese el tipo de consulta que angendo el paiente: ");
					printf("\n 1. Medicina general");
					printf("\n 2. Especializacion");
					do{
					printf("\nOpcion: ");
					scanf("%d",&opcion);
					}while(opcion<0 && opcion>2);
					switch(opcion){
						case 1:
							strcpy(aux->tipo_consulta,general);
						break;
						case 2:
							strcpy(aux->tipo_consulta,especial);
						break;
					}
					aux->pago_total = pago(aux->edad,aux->tipo_consulta);
				break;
				case 11:
					fflush(stdin);
					printf("\nIngrese la fecha en la que desea agendar la consulta: \n");
					do{
					printf("Dia: ");
					scanf("%d",&aux->dia);
					}while(aux->dia<1 && aux->dia>31);

					fflush(stdin);
					do{
					printf("Mes: ");
					scanf("%d",&aux->mes);
					}while(aux->mes<1 && aux->mes>12);
		
					fflush(stdin);
					do{
					printf("Anio: ");
					scanf("%d",&aux->anio);
					}while(aux->anio<2019);
			}
		}
}*/

int Validar_numero(char numero[]){
	for(int i=0;i<strlen(numero);i++){
		if(!(isdigit(numero[i]))){
			printf("\n Dato no valido! ");
			printf("\n Intente de nuevo: ");
			getch();
			return 0;
		}
	}
return 1;
}
