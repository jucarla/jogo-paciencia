//Programa feito orgulhosamente por Mailson Filho, Juliana Carla e Tássio Andrade.
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#define MAX 53
using namespace std;

/*-------------------------------------------------------------------------*/

typedef struct {
int naipe;// 3 = copas| 4 = ouros | 5 = paus | 6 = espadas
int valor;
int visivel;// 0=nao| 1=sim
int cor;// 0= vermelho| 1=preto
} carta;

typedef carta
	 tp_item;

typedef struct {
	int topo;
	tp_item item[MAX];
} tp_pilha;


//Inicializa a pilha
void inicializa_pilha(tp_pilha *p) {
   p->topo = -1;
}
//Verifica se a pilha está vazia
int pilha_vazia(tp_pilha *p){
	if (p->topo == -1) return 1; //TRUE
	return 0;  //FALSE
}
//Verifica se a pilha está cheia
int pilha_cheia(tp_pilha *p){
	if (p->topo == MAX-1) return 1; //TRUE
	return 0;  //FALSE
}
//Insere um elemento na pilha
int push(tp_pilha *p, tp_item e){
	if (pilha_cheia(p)==1) return 0; // Insucesso
	p->topo++;
	p->item[p->topo]=e;
	return 1;  //Sucesso
}
//Remove um elemento da pilha
int pop(tp_pilha *p, tp_item *e){
	if (pilha_vazia(p)==1) return 1; //Insucesso
	*e=p->item[p->topo];
	p->topo--;
	return 1; //Sucesso
}
//Verifica o elemento que está no topo sem desempilhar
int top(tp_pilha *p, tp_item *e){
	if (pilha_vazia(p)==1) return 0;
	*e=p->item[p->topo];
	return 1;
}

int altura_pilha(tp_pilha *p){
	return p->topo+1;
}

void imprime_pilha(tp_pilha p){
	tp_item e;
	printf("\n");
	while (pilha_vazia(&p)==0){
		 pop(&p, &e);
		 if(e.visivel==1){
            printf("[%c %d]", e.naipe, e.valor);
		cout << endl;
        }else{
            printf("[-]");
		cout << endl;
		}
	}
}


/*-------------------------------------------------------------------------*/


void embaralhar(int *vet, int vetSize)
{
	for (int i = 0; i < vetSize; i++)
	{

		int r = rand() % vetSize;

		int temp = vet[i];
		vet[i] = vet[r];
		vet[r] = temp;
	}
}

int main(){
srand(time(NULL));
carta copas[13];
carta ouros[13];
carta paus[13];
carta espadas[13];
carta baralho[52];

int tam = 52;

int vet[tam];

int i;

for(i=0; i<tam; i++){
	vet[i]=i+1;
}

embaralhar(vet, tam);

for (i=0; i<13; i++){
copas[i].naipe= 3;
copas[i].valor= i+1;
copas[i].cor= 0;
copas[i].visivel= 1;

baralho[vet[i]-1]= copas[i];
}

	for (i=0; i<13; i++){
ouros[i].naipe= 4;
ouros[i].valor= i+1;
ouros[i].cor= 0;
ouros[i].visivel= 1;

baralho[vet[i+13]-1]= ouros[i];
}

	for (i=0; i<13; i++){
paus[i].naipe= 5;
paus[i].valor= i+1;
paus[i].cor= 1;
paus[i].visivel= 1;

baralho[vet[i+26]-1]= paus[i];
}

	for (i=0; i<13; i++){
espadas[i].naipe= 6;
espadas[i].valor= i+1;
espadas[i].cor= 1;
espadas[i].visivel= 1;

baralho[vet[i+39]-1]= espadas[i];

}
tp_pilha p1, p2, p3, p4, p5, p6, p7;

inicializa_pilha(&p1);
inicializa_pilha(&p2);
inicializa_pilha(&p3);
inicializa_pilha(&p4);
inicializa_pilha(&p5);
inicializa_pilha(&p6);
inicializa_pilha(&p7);

int cont;

for (cont=0; cont<1; cont++)
    push(&p1, baralho[cont]);

for (cont=1; cont<3; cont++){
    if(cont>1)
        baralho[cont].visivel=0;
    push(&p2, baralho[cont]);
}

for (cont=3; cont<6; cont++){
    if(cont>3)
        baralho[cont].visivel=0;
    push(&p3, baralho[cont]);
}

for (cont=6; cont<10; cont++){
    if(cont>6)
        baralho[cont].visivel=0;
    push(&p4, baralho[cont]);
}

for (cont=10; cont<15; cont++){
    if(cont>10)
        baralho[cont].visivel=0;
    push(&p5, baralho[cont]);
}

for (cont=15; cont<21; cont++){
    if(cont>15)
        baralho[cont].visivel=0;
    push(&p6, baralho[cont]);
}

for (cont=21; cont<28; cont++){
    if(cont>21)
        baralho[cont].visivel=0;
    push(&p7, baralho[cont]);
}

imprime_pilha (p1);
cout << endl;
imprime_pilha (p2);
cout << endl;
imprime_pilha (p3);
cout << endl;
imprime_pilha (p4);
cout << endl;
imprime_pilha (p5);
cout << endl;
imprime_pilha (p6);
cout << endl;
imprime_pilha (p7);
cout << endl;



}
