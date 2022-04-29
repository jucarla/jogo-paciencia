//Trabalho semestral disciplina Algoritmo e estruturação de dados - engenharia de controle e automação
//Programa feito orgulhosamente por Mailson Filho, Juliana Carla e Tássio Andrade.
//Função descartar do monte funcionando
//Função mover entre pilhas funcionando
//Função do monte pra pilha funcionando
//Função verificação
//Loop configurado
//Interface configurada
//Pilhas finais inicializadas

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <windows.h>
#include <locale.h>
#include <malloc.h>

#define MAX 53



using namespace std;

/*-------------------------------------------------------------------------*/
//Criando a scruct da carta
typedef struct {
int naipe;// 3 = copas| 4 = ouros | 5 = paus | 6 = espadas;
int valor;// De 1 a 13;
int visivel;// 0=nao| 1=sim;
int cor;// 0= vermelho| 1=preto;
} carta;

typedef carta
	 tp_item;

typedef struct {
	int topo;
	tp_item item[MAX];
} tp_pilha;


//Função de imprimir nas coordenadas x,y do cmd, usada para imprimir o tabuleiro
void gotoxy(int x, int y){
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1,y-1});
}

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
//--------------------ALOCAÇÃO DINÂMICA----------------------------------
//Funções referentes à biblioteca de alocação dinâmica feita em sala. 
//Para não confundir com as funções de pilha não dinâmica, representamos com um "d" no final do nome de cada função.
typedef int tp_itemd;

typedef struct tp_no_aux {
  tp_item info;
  struct tp_no_aux *prox;
} tp_no;

typedef struct {
  tp_no *topo;
} tp_pilhad;

tp_pilhad *inicializa_pilhad (){
   tp_pilhad *pilha=(tp_pilhad*) malloc(sizeof(tp_pilhad));
   pilha->topo = NULL;
   return pilha;
}

tp_no *aloca() {
	tp_no* pt;
	pt=(tp_no*) malloc(sizeof(tp_no));
	return pt;
}

int pilha_vaziad (tp_pilhad *pilha){
 if (pilha->topo == NULL) return 1;
 return 0;
}

int pushd (tp_pilhad *pilha, tp_item e){
  tp_no *novo;
  novo=aloca();
  if (!novo) return 0;

  novo->info = e;
  if ( (pilha->topo == NULL) ) { //Se for o primeiro elemento da lista
     novo->prox = NULL;
     //pilha->topo = novo;
     }
  else {
     novo->prox = pilha->topo;
     //pilha->topo = novo;
     }
  pilha->topo = novo;
  return 1;
}

int popd (tp_pilhad *pilha, tp_item *e){
  tp_no *aux;

  if (pilha_vaziad(pilha)) return 0;
  *e=pilha->topo->info;
  aux=pilha->topo;
  pilha->topo=pilha->topo->prox;
  free(aux);
  return 1;
}

int topd (tp_pilhad *pilha, tp_item *e){
  tp_no *aux;

  if (pilha_vaziad(pilha)) return 0;
  *e=pilha->topo->info;
  return 1;
}

void imprime_pilhad(tp_pilhad *pilha) {

	 tp_no *atu=pilha->topo;

	 while (atu != NULL)
	       {
            printf("%d ", atu->info);
			atu= atu->prox;
            }

     printf("\n");
}

//--------------------PILHA SIMPLES----------------------------------

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

tp_pilha inverter(tp_pilha *p){
	tp_pilha aux;
	tp_item e;
	inicializa_pilha(&aux);

	while(!pilha_vazia(p)){
		pop(p, &e);
		push(&aux, e);
	}
	return aux;
}

void invertepilha(tp_pilha *p){
	*p = inverter(p);
}
void imprime_pilha1(tp_pilha p){ //Imprime a pilha normalmente
	tp_item e, lixo;
	printf("\n");

	top(&p, &e);
	
	if(e.visivel==0){
        e.visivel=1;
        pop(&p, &lixo);
        push(&p ,e);
	}
	//enquanto a pilha não estiver vazia, imprime a carta entre colchetes se a carta for indicada como visível.
	//Substitui os valores não numéricos do baralho (A, J, Q, K)
	while (pilha_vazia(&p)==0){
		 pop(&p, &e);
		 if(e.visivel==1){
                if(e.valor==1)
                    printf("[%c A]", e.naipe);
                else if(e.valor==11)
                    printf("[%c J]", e.naipe);
                else if(e.valor==12)
                    printf("[%c Q]", e.naipe);
                else if(e.valor==13)
                    printf("[%c K]", e.naipe);
                else
                    printf("[%c %d]", e.naipe, e.valor);
                cout << endl;
        }else{ //Caso não seja visível, imprime apenas o fundo da carta "[-]"
            printf("[-]");
            cout << endl;
		}
	}
}

//Função de impressão das pilhas simples
void imprime_pilha(tp_pilha p, int pilha){ //Recebe como parâmetro a pilha e o número da pilha (para setar a coordenada de impressão)
	tp_item e, lixo;
	printf("\n");

	//Configurando a coordenada x para cada pilha "começar em uma coluna" lado a lado no tabuleiro.
	int x, y;
	if (pilha==1) x = 13;
	if (pilha==2) x = 23;
	if (pilha==3) x = 33;
	if (pilha==4) x = 43;
	if (pilha==5) x = 53;
	if (pilha==6) x = 63;
	if (pilha==7) x = 73;

	//Na coordenada y, começa na linha 3;
	y = 3;
	top(&p, &e);

	if(e.visivel==0){
        e.visivel=1;
        pop(&p, &lixo);
        push(&p ,e);
	}


	
	while (pilha_vazia(&p)==0){
		gotoxy(x,2); //Imprime o cabeçalho que indica o número da pilha.
		printf("P%d", pilha);
		 pop(&p, &e);
		gotoxy(x,y);//Imprime nas coordenadas setadas.
		 if(e.visivel==1){
                if(e.valor==1)
                    printf("[%c A]", e.naipe);
                else if(e.valor==11)
                    printf("[%c J]", e.naipe);
                else if(e.valor==12)
                    printf("[%c Q]", e.naipe);
                else if(e.valor==13)
                    printf("[%c K]", e.naipe);
                else
                    printf("[%c %d]", e.naipe, e.valor);
                cout << endl;

        }else{
            printf("[-]");
            cout << endl;
		}  y++;
	}
}

//Função para imprimir a pilha visível do monte. 
void imprime_monte(tp_pilha p){
	tp_item e;


	printf("\n");
	for(int i = 0; i < 3; i++){ //Limita as cartas a serem imprimidas como as três do topo da pilha

		 pop(&p, &e);
		 if(e.visivel==1){
                if(e.valor==1)
                    printf("[%c A]", e.naipe);
                else if(e.valor==11)
                    printf("[%c J]", e.naipe);
                else if(e.valor==12)
                    printf("[%c Q]", e.naipe);
                else if(e.valor==13)
                    printf("[%c K]", e.naipe);
                else
                    printf("[%c %d]", e.naipe, e.valor);

                cout << endl;
        }else{
                printf("[-]");
                cout << endl;
		}
	}
}

/*-------------------------------------------------------------------------*/

int Monte_para_Final(tp_pilha *bvisivel, tp_pilhad *PF1, tp_pilhad *PF2, 
tp_pilhad *PF3, tp_pilhad *PF4, int *pontos){
/*Função que recebe como parametros as pilhas finais,monte,um valor que informa
o destino da carta que vai sair monte e um ponteiro que aponta para os pontos do jogo*/
	int destino;
	tp_item e, e1, e2;
	

    if(pilha_vazia(bvisivel)) return 0;// Se o monte estiver vazia finaliza a função
   	top(bvisivel,&e);//Verifica o elemento do topo 
   	//E dependendo do valor do naipe envia como paramentro a respectiva pilha final
   	if(e.naipe==3) destino = 1;
   	if(e.naipe==4) destino = 2;
   	if(e.naipe==5) destino = 3;
   	if(e.naipe==6) destino = 4;
   
    switch(destino){

        case 1: top(bvisivel, &e1);// Verifica o topo da monte
                topd(PF1, &e2);// Verifica o topo da Pilha final escolhida
                if(e1.naipe!=3) // Se o naipe da carta do monte for diferente retorna "0"  
                    return 0; //Retornando "0" é exibido a mensagem de jogada invalida
                if(pilha_vaziad(PF1)==1){// Se a pilha final estiver vazia 
                    if(e1.valor!=1) // E se o valor diferente de um "as" retorna "0"
                        return 0;
                    else{ // Se a função não for interrompida nos itens acima
                        pop(bvisivel, &e1);// Retira a carta do topo do monte 
                        pushd(PF1, e1); // E coloca no topo da pilha final 
                        *pontos+=1; // E adiciona um ponto para o jogador
                        return 1; // retorna 1 dizendo que o movimento é valido
                    }
                }
                if(e1.valor<=e2.valor)//Verifica se a carta está sendo colocada na ordem certa - decrescente.
                    return 0; //Caso uma carta maior esteja sendo colocada em cima de uma maior, retorna que o movimento é invalido.
                else{ //Caso esteja tudo ok, tira uma carta do monte e insere na pilha final;
                    pop(bvisivel, &e1);
                    pushd(PF1, e1);
                    *pontos+=1; //Adiciona 1 na pontuação para controle do loop.
                    return 1;
                }

	//Processo do Case 1 se repete, para a Pilha final 2
        case 2: top(bvisivel, &e1);
                topd(PF2, &e2);
                if(e1.naipe!=4)
                    return 0;
                if(pilha_vaziad(PF2)==1){
                    if(e1.valor!=1)
                        return 0;
                    else{
                        pop(bvisivel, &e1);
                        pushd(PF2, e1);
                        *pontos+=1;
                        return 1;
                    }
                }
                if(e1.valor<=e2.valor)
                    return 0;
                else{
                    pop(bvisivel, &e1);
                    pushd(PF2, e1);
                    *pontos+=1;
                    return 1;
                }

	//Processo do Case 1 se repete, para a Pilha final 3
        case 3: top(bvisivel, &e1);
                topd(PF3, &e2);
                if(e1.naipe!=5)
                    return 0;
                if(pilha_vaziad(PF3)==1){
                    if(e1.valor!=1)
                        return 0;
                    else{
                        pop(bvisivel, &e1);
                        pushd(PF3, e1);
                        *pontos+=1;
                        return 1;
                    }
                }
                if(e1.valor<=e2.valor)
                    return 0;
                else{
                    pop(bvisivel, &e1);
                    pushd(PF3, e1);
                    *pontos+=1;
                    return 1;
                }
	
	//Processo do Case 1 se repete, para a Pilha final 4
        case 4: top(bvisivel, &e1);
                topd(PF4, &e2);
                if(e1.naipe!=6)
                    return 0;
                if(pilha_vaziad(PF4)==1){
                    if(e1.valor!=1)
                        return 0;
                    else{
                        pop(bvisivel, &e1);
                        pushd(PF4, e1);
                        *pontos+=1;
                        return 1;
                    }
                }
                if(e1.valor<=e2.valor)
                    return 0;
                else{
                    pop(bvisivel, &e1);
                    pushd(PF4, e1);
                    *pontos+=1;
                    return 1;
                }

        default: return 0;
    }

}

int Final_para_Simples_2(tp_pilha *ps,tp_pilhad *pf,int *pontos){
/* Recebe como parametro da primeira função "Final_para_silmpes" a pilha para qual sera movida a carta, a pilha final de onde
a carta sera movida e o parametro ponto*/
	
	tp_item e1,e2;
	if(pilha_vaziad(pf)==1)// Se a pilha de onde a carta estiver vazia retorna "0" 
        return 0; // Retorna zero que significa que a jogada é invalida
    if(pilha_vazia(ps)==1){// Se a pilha estiver vazia não ha necessidade de verificar cartas
        popd(pf, &e1);// Retira a carta do topo da pilha final 
        push(ps, e1); // Coloca na pilha simples 
        *pontos-=1; // Retira um ponto do jogador
        return 1; // retorna 1, jogada valida
    }
    top(ps, &e1);//Verifica o top da pilha simples sem retirar a carta
    topd(pf, &e2);//verifica o top da pilha final sem retirar a carta
    if(e2.valor>=e1.valor) // Se o valor da carta for retirada for maior ou igual retorna 0
        return 0;
    if(e2.cor==0 && e1.cor==0)// Se as cores das cartas forem iguais retorna 0
        return 0;
    else if(e2.cor==1 && e1.cor==1) // Se as cores das cartas forem iguais retorna 0
        return 0;
    else if(e2.cor==0 && e1.cor==1){//Se as cores forem diferentes 
        popd(pf, &e1);// Retira a carta da pilha final
        push(ps, e1);// Coloca a carta na pilha simples
        *pontos-=1; // Retira um ponto do jogador
        return 1;// Retorna 1 jogada valida
        }
    else if(e2.cor==1 && e1.cor==0){//Se as cores forem diferentes
        popd(pf, &e1);// Retira a carta da pilha final
        push(ps, e1);// Coloca a carta na pilha simples
        *pontos-=1;// Retira um ponto do jogador
        return 1;// Retorna 1 jogada valida
        }
    else return 0;
}

int Final_para_Simples(tp_pilha *p1,tp_pilha *p2,tp_pilha *p3,tp_pilha *p4,
tp_pilha *p5,tp_pilha *p6,tp_pilha *p7,tp_pilhad *PF1,tp_pilhad *PF2,tp_pilhad *PF3,
tp_pilhad *PF4,int origem,int Destino, int *pontos){
	
    
	/*Função recebe como parametro todas as pilhas simples e finais assim como o
	valor da origem e o destino da carta junto com o parametro de pontos*/
	 
	if(origem==1){// Se a origem for 1 ir ser passado apenas a pilha final 1 de copas como parametro
        //Verifica os 7 destinos possiveis para a carta e passa como parametro a pilha respectiva//
		if(Destino==1)return Final_para_Simples_2(p1,PF1,pontos);
        else if(Destino==2)return Final_para_Simples_2(p2,PF1,pontos);
        else if(Destino==3)return Final_para_Simples_2(p3,PF1,pontos);
        else if(Destino==4)return Final_para_Simples_2(p4,PF1,pontos);
        else if(Destino==5)return Final_para_Simples_2(p5,PF1,pontos);
        else if(Destino==6)return Final_para_Simples_2(p6,PF1,pontos);
        else if(Destino==7)return Final_para_Simples_2(p7,PF1,pontos);
        else return 0;
    }
    else if(origem==2){// Se a origem for 2 ir ser passado apenas a pilha final 2 de ouros como parametro
        //Verifica os 7 destinos possiveis para a carta e passa como parametro a pilha respectiva//
		if(Destino==1)return Final_para_Simples_2(p1,PF2,pontos);
        else if(Destino==2)return Final_para_Simples_2(p2,PF2,pontos);
        else if(Destino==3)return Final_para_Simples_2(p3,PF2,pontos);
        else if(Destino==4)return Final_para_Simples_2(p4,PF2,pontos);
        else if(Destino==5)return Final_para_Simples_2(p5,PF2,pontos);
        else if(Destino==6)return Final_para_Simples_2(p6,PF2,pontos);
        else if(Destino==7)return Final_para_Simples_2(p7,PF2,pontos);
        else return 0;
    }
    else if(origem==3){// Se a origem for 3 ir ser passado apenas a pilha final 3 de paus como parametro
        //Verifica os 7 destinos possiveis para a carta e passa como parametro a pilha respectiva//
		if(Destino==1)return Final_para_Simples_2(p1,PF3,pontos);
        else if(Destino==2)return Final_para_Simples_2(p2,PF3,pontos);
        else if(Destino==3)return Final_para_Simples_2(p3,PF3,pontos);
        else if(Destino==4)return Final_para_Simples_2(p4,PF3,pontos);
        else if(Destino==5)return Final_para_Simples_2(p5,PF3,pontos);
        else if(Destino==6)return Final_para_Simples_2(p6,PF3,pontos);
        else if(Destino==7)return Final_para_Simples_2(p7,PF3,pontos);
        else return 0;
    }
    else if(origem==4){// Se a origem for 4 ir ser passado apenas a pilha final 4 de espadas como parametro
        //Verifica os 7 destinos possiveis para a carta e passa como parametro a pilha respectiva//
		if(Destino==1)return Final_para_Simples_2(p1,PF4,pontos);
        else if(Destino==2)return Final_para_Simples_2(p2,PF4,pontos);
        else if(Destino==3)return Final_para_Simples_2(p3,PF4,pontos);
        else if(Destino==4)return Final_para_Simples_2(p4,PF4,pontos);
        else if(Destino==5)return Final_para_Simples_2(p5,PF4,pontos);
        else if(Destino==6)return Final_para_Simples_2(p6,PF4,pontos);
        else if(Destino==7)return Final_para_Simples_2(p7,PF4,pontos);
        else return 0;
    }
    else return 0;
}

int Simples_para_Final_2(tp_pilha *ps,tp_pilhad *pf, int *pontos){
	/*Recebe como parametro a pilha final de qual a carta sera retirda junto com 
	a pilha simples para qual a carta ira e tambem um ponteiro que aponta para os pontos*/
    tp_item e1,e2;
    if(pilha_vaziad(pf)==1){//se a pilha final estiver vazia
        top(ps, &e1);//Verifica o elemento do topo sem retirar
        if(e1.valor!=1)//Se o valor do topo for diferente de 1 retorna que a jogada é invalida
            return 0;
        pop(ps, &e1);//Se a função não terminar no return anterior retira o elemento simples
        pushd(pf, e1);//Insere o elemento retirdao na pilha final
        *pontos+=1;// Adiciona um ponto
        return 1;//Finaliza a função
	}
    else{//Se a pilha não estiver vazia
    	top(ps, &e1);// Verifica o elemento do topo da pilha simples
    	topd(pf, &e2);// Verifica o elemento do topo da pilha final
    	if(e1.valor<=e2.valor)// Se o valor da pilha simples for menor ou igual ao da pilha final finaliza a função
            return 0;
        pop(ps, &e1);//Se a função não terminar no return acima retira o elemento da pilha simples
        pushd(pf, e1);//Insere o elemento na pilha final
        *pontos+=1;//Soma 1 um ponto ao jogador
        return 1;//Finaliza a função
		}
}

int Simples_para_Final(tp_pilha *p1,tp_pilha *p2,tp_pilha *p3,tp_pilha *p4,tp_pilha *p5,tp_pilha *p6,tp_pilha *p7,tp_pilhad *PF1,tp_pilhad *PF2,tp_pilhad *PF3,tp_pilhad *PF4,int origem, int *pontos){
   //Recebe como parametro as filas finais e simples, assim como um valor de origem e destino e um ponteiro para os pontos
   tp_item e;
   if(origem==1 ){//Se a origem for igual 1
    if(pilha_vazia(p1)) return 0;// Se a pilha 1 estiver vazia finaliza a função
   	top(p1,&e);//Verifica o elemento do topo 
   	//E se dependendo do valor do naipe envia como paramentro a respectiva pilha final
   	if(e.naipe==3)return Simples_para_Final_2(p1,PF1, pontos);
   	if(e.naipe==4)return Simples_para_Final_2(p1,PF2, pontos);
   	if(e.naipe==5)return Simples_para_Final_2(p1,PF3, pontos);
   	if(e.naipe==6)return Simples_para_Final_2(p1,PF4, pontos);
   }
   else if(origem==2 ){//Se a origem for igual 2
    if(pilha_vazia(p2)) return 0;// Se a pilha 2 estiver vazia finaliza a função
   	top(p2,&e);//Verifica o elemento do topo
	 //E se dependendo do valor do naipe envia como paramentro a respectiva pilha final   
   	if(e.naipe==3)return Simples_para_Final_2(p2,PF1, pontos);
   	if(e.naipe==4)return Simples_para_Final_2(p2,PF2, pontos);
   	if(e.naipe==5)return Simples_para_Final_2(p2,PF3, pontos);
   	if(e.naipe==6)return Simples_para_Final_2(p2,PF4, pontos);
   }
   else if(origem==3 ){//Se a origem for igual 3
    if(pilha_vazia(p3)) return 0;// Se a pilha 3 estiver vazia finaliza a função
   	top(p3,&e);//Verifica o elemento do topo 
   	//E se dependendo do valor do naipe envia como paramentro a respectiva pilha final
   	if(e.naipe==3)return Simples_para_Final_2(p3,PF1, pontos);
   	if(e.naipe==4)return Simples_para_Final_2(p3,PF2, pontos);
   	if(e.naipe==5)return Simples_para_Final_2(p3,PF3, pontos);
   	if(e.naipe==6)return Simples_para_Final_2(p3,PF4, pontos);
   }
   else if(origem==4 ){//Se a origem for igual 4
    if(pilha_vazia(p4)) return 0;// Se a pilha 4 estiver vazia finaliza a função
   	top(p4,&e);//Verifica o elemento do topo
	 //E se dependendo do valor do naipe envia como paramentro a respectiva pilha final   
   	if(e.naipe==3)return Simples_para_Final_2(p4,PF1, pontos);
   	if(e.naipe==4)return Simples_para_Final_2(p4,PF2, pontos);
   	if(e.naipe==5)return Simples_para_Final_2(p4,PF3, pontos);
   	if(e.naipe==6)return Simples_para_Final_2(p4,PF4, pontos);
   }
   else if(origem==5 ){//Se a origem for igual 5
    if(pilha_vazia(p5)) return 0;// Se a pilha 5 estiver vazia finaliza a função
   	top(p5,&e);//Verifica o elemento do topo 
   	//E se dependendo do valor do naipe envia como paramentro a respectiva pilha final
   	if(e.naipe==3)return Simples_para_Final_2(p5,PF1, pontos);
   	if(e.naipe==4)return Simples_para_Final_2(p5,PF2, pontos);
   	if(e.naipe==5)return Simples_para_Final_2(p5,PF3, pontos);
   	if(e.naipe==6)return Simples_para_Final_2(p5,PF4, pontos);
   }
   else if(origem==6 ){//Se a origem for igual 6
    if(pilha_vazia(p6)) return 0;// Se a pilha 6 estiver vazia finaliza a função
   	top(p6,&e);//Verifica o elemento do topo 
   	//E se dependendo do valor do naipe envia como paramentro a respectiva pilha final
   	if(e.naipe==3)return Simples_para_Final_2(p6,PF1, pontos);
   	if(e.naipe==4)return Simples_para_Final_2(p6,PF2, pontos);
   	if(e.naipe==5)return Simples_para_Final_2(p6,PF3, pontos);
   	if(e.naipe==6)return Simples_para_Final_2(p6,PF4, pontos);
   }
   else if(origem==7 ){//Se a origem for igual 7
    if(pilha_vazia(p7)) return 0;// Se a pilha 7 estiver vazia finaliza a função
   	top(p7,&e);//Verifica o elemento do topo
	   //E se dependendo do valor do naipe envia como paramentro a respectiva pilha final 
   	if(e.naipe==3)return Simples_para_Final_2(p7,PF1, pontos);
   	if(e.naipe==4)return Simples_para_Final_2(p7,PF2, pontos);
   	if(e.naipe==5)return Simples_para_Final_2(p7,PF3, pontos);
   	if(e.naipe==6)return Simples_para_Final_2(p7,PF4, pontos);
   }
   else return 0;
}

//Função para embaralhar o vetor inicial das cartas do baralho. Recebe como parâmetro o vetor, e o tamanho do vetor.
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

//Função para configurar a impressão do monte
void monte(tp_pilha *bvisivel, tp_pilha *binvisivel){
	tp_item e;
	
	//Se o monte virado acabar, imprime o colchete vazio como representação
	if(pilha_vazia(binvisivel) == 1)printf("[ ]");
	else printf("[-] "); //Se não, indica a presença de uma carta no topo
	if(altura_pilha(bvisivel) <= 3) imprime_pilha1 (*bvisivel); //Se a pilha de monte visível for menor que 3, imprime normalmente o monte virado
			else{
				imprime_monte (*bvisivel);//Se a pilha for maior que três, inicializa a função que limita a impressão às três do topo. 
			}

	if(pilha_vazia(binvisivel) == 1){//Se o monte virado acabar, retira as cartas do monte visível e coloca novamente no baralho virado (invisível)
		while(!pilha_vazia(bvisivel)){
			pop(bvisivel, &e);
			e.visivel = 0;
			push(binvisivel, e);
		}
	}
}

//Função que retorna o valor da carta no topo da pilha final. Usada na impressão da pilha final no tabuleiro.
int topopf(tp_pilhad *PilhaF){
	tp_item e;
	int PF;
	if(!pilha_vaziad(PilhaF)){
		topd(PilhaF, &e);
		PF = e.valor;
	} else PF = 0;
	return PF;
}

//Função que imprime todo o tabuleiro (O monte virado, o monte visível, as 7 pilhas simples, as pilhas finais e a pontuação. Recebe todos eles como parâmetro)
void imprimetabuleiro(tp_pilha *p1, tp_pilha *p2, tp_pilha *p3, tp_pilha *p4, tp_pilha *p5, tp_pilha *p6, tp_pilha *p7, tp_pilha *binicial, tp_pilha *bvisivel, tp_pilhad *PilhaF1, tp_pilhad *PilhaF2, tp_pilhad *PilhaF3, tp_pilhad *PilhaF4, int *pontos){
	int a = 3, b=4, c=5, d=6;
	tp_item e;
	
	//Imprime o monte virado e o monte visível.
	printf("\n-----\n");
	monte(bvisivel, binicial);
	printf("\n-----\n");
	int PF1, PF2, PF3, PF4;

	//Recebe o topo de cada pilha final para impressão.
	PF1 = topopf(PilhaF1);
	PF2 = topopf(PilhaF2);
	PF3 = topopf(PilhaF3);
	PF4 = topopf(PilhaF4);

	//Imprime as pilhas simples, enviando como parâmetro as pilhas e o número da pilha para a configuração da coordenada.
	imprime_pilha (*p1, 1);
	cout << endl;
	imprime_pilha (*p2, 2);
	cout << endl;
	imprime_pilha (*p3, 3);
	cout << endl;
	imprime_pilha (*p4, 4);
	cout << endl;
	imprime_pilha (*p5, 5);
	cout << endl;
	imprime_pilha (*p6, 6);
	cout << endl;
	imprime_pilha (*p7,7);
	cout << endl;

	printf("\n--------------------------\n");
	//Como a pilha final só imprime o topo, utiliza o valor da carta do topo recebido anteriormente e imprime.
	//Com exceção do casos especiais de cartas não numéricas, nos quais é feita a substitição.
	//O processo se repete para cada naipe, com suas respectivas variáveis (a - copas; b - ouros; c - paus; d - espadas).
	
	//Pilha final copas
	if (PF1 == 0) printf("[%c]", a);
    else if(PF1==1) printf("[%c A]", a);
    else if(PF1==11) printf("[%c J]", a);
    else if(PF1==12) printf("[%c Q]", a);
    else if(PF1==13) printf("[%c K]", a);
    else printf("[%c %d]", a, PF1);
	//Pilha final ouros
	if (PF2 == 0) printf("[%c]", b);
    else if(PF2==1) printf("[%c A]", b);
    else if(PF2==11) printf("[%c J]", b);
    else if(PF2==12) printf("[%c Q]", b);
    else if(PF2==13) printf("[%c K]", b);
    else printf("[%c %d]", b, PF2);
        //Pilha final paus
	if (PF3 == 0) printf("[%c]", c);
	else if(PF3==1) printf("[%c A]", c);
    else if(PF3==11) printf("[%c J]", c);
    else if(PF3==12) printf("[%c Q]", c);
    else if(PF3==13) printf("[%c K]", c);
    else printf("[%c %d]", c, PF3);
        //Pilha final espadas
    if (PF4 == 0) printf("[%c]", d);
	else if(PF4==1) printf("[%c A]", d);
    else if(PF4==11) printf("[%c J]", d);
    else if(PF4==12) printf("[%c Q]", d);
    else if(PF4==13) printf("[%c K]", d);
    else printf("[%c %d]", d, PF4);

    cout<<"         PONTUAÇÃO: "<< *pontos; //Imprime a pontuação (cada carta colocada em uma pilha final)
	printf("\n--------------------------\n");
	
}

int Monte_para_Simples_2 (tp_pilha *bvisivel, tp_pilha *destino){
    tp_pilha monte;
    tp_item e1, e2;
    inicializa_pilha(&monte);

    monte=*bvisivel;

	//Define o topo da pilha destino e a carta que vai ser tirada monte,para a verificação
    top(destino, &e1);
    top(bvisivel, &e2);

	//Se a pilha destino estiver vazia, não precisa de verificação.
    if(pilha_vazia(destino)==1) {
        pop(bvisivel, &e1);
        push(destino, e1);
        return 1;
    }


        if(e2.valor>=e1.valor) //Se a ordem tiver errada (decrescente) retorna 0 indicando que o movimento é inválido.
            return 0;
        if(e2.cor==0 && e1.cor==0) //Se for as duas cartas forem vermelhas, retorna movimento inválido.
            return 0;
        else if(e2.cor==1 && e1.cor==1)//Se for as duas cartas forem pretas, retorna movimento inválido.
            return 0;
        else{ //Caso toda verificação seja válida:
            pop(bvisivel, &e1); //Tira do monte
            push(destino, e1); //Coloca na pilha de destino
        }

    return 1;
}

int Monte_para_Simples (tp_pilha *p1, tp_pilha *p2, tp_pilha *p3, tp_pilha *p4, tp_pilha *p5, tp_pilha *p6, tp_pilha *p7,tp_pilha *bvisivel, int destino){
    if(pilha_vazia(bvisivel)) //Se a pilha estiver vazia, retorna movimento inválido.
        return 0;

    switch (destino){//De acordo com o destino, passa sua respectiva pilha na função do movimento, definida anteriormente.

    case 1: return (Monte_para_Simples_2(bvisivel, p1));
    case 2: return (Monte_para_Simples_2(bvisivel, p2));
    case 3: return (Monte_para_Simples_2(bvisivel, p3));
    case 4: return (Monte_para_Simples_2(bvisivel, p4));
    case 5: return (Monte_para_Simples_2(bvisivel, p5));
    case 6: return (Monte_para_Simples_2(bvisivel, p6));
    case 7: return (Monte_para_Simples_2(bvisivel, p7));
    default: return 0;
    }

}

int Simples_para_Simples_2 (tp_pilha *origem,tp_pilha *destino,int qntdd){
	int i;
	tp_item e1, e2;
	tp_pilha aux1, aux2, aux3, aux4, auxinv;
	inicializa_pilha(&aux1);
	inicializa_pilha(&aux2);
    inicializa_pilha(&aux3);
    inicializa_pilha(&auxinv);

	if(qntdd>altura_pilha(origem))
        return 0;

    auxinv=*origem;

    for(i=0; i<qntdd; i++){
        pop(&auxinv, &e1);
        if(e1.visivel==0)
            return 0;
    }

    if(pilha_vazia(destino)){
        inicializa_pilha(&aux1);

        for(; qntdd>0; qntdd--){
            pop(origem, &e1);
            push(&aux1, e1);
        }

        while(!pilha_vazia(&aux1)){
            pop(&aux1, &e1);
            push(destino, e1);
        }

        return 1;
    }

    aux3=*origem;

    while(!pilha_vazia(&aux3)){
        pop(&aux3, &e2);
        push(&aux1, e2);
    }

    for(i=altura_pilha(origem)-qntdd; i>0; i--)
        pop(&aux1, &e1);

    while(!pilha_vazia(&aux1)){
        pop(&aux1, &e1);
        push(&aux2, e1);
    }

    invertepilha(&aux2);

	inicializa_pilha(&aux1);

    aux1=*destino;

    while(!pilha_vazia(&aux2)){
        top(&aux1, &e1);
        top(&aux2, &e2);
        if(e2.valor>=e1.valor)
            return 0;
        if(e2.cor==0 && e1.cor==0)
            return 0;
        else if(e2.cor==1 && e1.cor==1)
            return 0;
        else if(e2.cor==0 && e1.cor==1){
            pop(&aux2, &e2);
            push(&aux1, e2);
        }
        else if(e2.cor==1 && e1.cor==0){
            pop(&aux2, &e2);
            push(&aux1, e2);
        }
    }

    inicializa_pilha(&aux1);

	for(; qntdd>0; qntdd--){
        pop(origem, &e1);
        push(&aux1, e1);
	}

	while(!pilha_vazia(&aux1)){
        pop(&aux1, &e1);
        push(destino, e1);
	}

    return 1;
}

int Simples_para_Simples (tp_pilha *p1, tp_pilha *p2, tp_pilha *p3, tp_pilha *p4, tp_pilha *p5, tp_pilha *p6, tp_pilha *p7, int origem, int destino, int qntdd){
    
    //De acordo com o valor que receber como pilha origem e pilha destino, faz uma combinação entre as possibilidades de movimento.
    //Para cada opção de origem, e de destino, inicia a função referente as pilhas origem-destino escolhidas.
    if(origem==1){
        if(destino==1)return 0;
        if(destino==2)return Simples_para_Simples_2(p1,p2,qntdd);
        if(destino==3)return Simples_para_Simples_2(p1,p3,qntdd);
        if(destino==4)return Simples_para_Simples_2(p1,p4,qntdd);
        if(destino==5)return Simples_para_Simples_2(p1,p5,qntdd);
        if(destino==6)return Simples_para_Simples_2(p1,p6,qntdd);
        if(destino==7)return Simples_para_Simples_2(p1,p7,qntdd);
        }

    else if(origem==2){
        if(destino==1)return Simples_para_Simples_2(p2,p1,qntdd);
        if(destino==2)return 0;
        if(destino==3)return Simples_para_Simples_2(p2,p3,qntdd);
        if(destino==4)return Simples_para_Simples_2(p2,p4,qntdd);
        if(destino==5)return Simples_para_Simples_2(p2,p5,qntdd);
        if(destino==6)return Simples_para_Simples_2(p2,p6,qntdd);
        if(destino==7)return Simples_para_Simples_2(p2,p7,qntdd);
        }

    else if(origem==3){
        if(destino==1)return Simples_para_Simples_2(p3,p1,qntdd);
        if(destino==2)return Simples_para_Simples_2(p3,p2,qntdd);
        if(destino==3)return 0;
        if(destino==4)return Simples_para_Simples_2(p3,p4,qntdd);
        if(destino==5)return Simples_para_Simples_2(p3,p5,qntdd);
        if(destino==6)return Simples_para_Simples_2(p3,p6,qntdd);
        if(destino==7)return Simples_para_Simples_2(p3,p7,qntdd);
        }

    else if(origem==4){
        if(destino==1)return Simples_para_Simples_2(p4,p1,qntdd);
        if(destino==2)return Simples_para_Simples_2(p4,p2,qntdd);
        if(destino==3)return Simples_para_Simples_2(p4,p3,qntdd);
        if(destino==4)return 0;
        if(destino==5)return Simples_para_Simples_2(p4,p5,qntdd);
        if(destino==6)return Simples_para_Simples_2(p4,p6,qntdd);
        if(destino==7)return Simples_para_Simples_2(p4,p7,qntdd);
        }

    else if(origem==5){
        if(destino==1)return Simples_para_Simples_2(p5,p1,qntdd);
        if(destino==2)return Simples_para_Simples_2(p5,p2,qntdd);
        if(destino==3)return Simples_para_Simples_2(p5,p3,qntdd);
        if(destino==4)return Simples_para_Simples_2(p5,p4,qntdd);
        if(destino==5)return 0;
        if(destino==6)return Simples_para_Simples_2(p5,p6,qntdd);
        if(destino==7)return Simples_para_Simples_2(p5,p7,qntdd);
        }

    else if(origem==6){
        if(destino==1)return Simples_para_Simples_2(p6,p1,qntdd);
        if(destino==2)return Simples_para_Simples_2(p6,p2,qntdd);
        if(destino==3)return Simples_para_Simples_2(p6,p3,qntdd);
        if(destino==4)return Simples_para_Simples_2(p6,p4,qntdd);
        if(destino==5)return Simples_para_Simples_2(p6,p5,qntdd);
        if(destino==6)return 0;
        if(destino==7)return Simples_para_Simples_2(p6,p7,qntdd);
        }

    else if(origem==7){
        if(destino==1)return Simples_para_Simples_2(p7,p1,qntdd);
        if(destino==2)return Simples_para_Simples_2(p7,p2,qntdd);
        if(destino==3)return Simples_para_Simples_2(p7,p3,qntdd);
        if(destino==4)return Simples_para_Simples_2(p7,p4,qntdd);
        if(destino==5)return Simples_para_Simples_2(p7,p5,qntdd);
        if(destino==6)return Simples_para_Simples_2(p7,p6,qntdd);
        if(destino==7)return 0;
        }
    else return 0;
}

void Mover(tp_pilha *p1, tp_pilha *p2, tp_pilha *p3, tp_pilha *p4, tp_pilha *p5, tp_pilha *p6, tp_pilha *p7, tp_pilha *binicial, tp_pilha *bvisivel, tp_pilhad *PF1,  tp_pilhad *PF2,  tp_pilhad *PF3,  tp_pilhad *PF4, int *pontos){

	int a=3, b=4, c=5, d=6;
	tp_item e, f, g, h, x;
	int origem, destino;
	int mov;

	//Chamada de interface para definição do movimento a ser realizado.
	printf("\n--------------------------\n");
	printf("Tipos de movimento:\n 1- Descartar do monte; \n 2- Do monte para uma pilha simples; \n 3- Do monte para uma pilha final\n");
	printf(" 4- Entre pilhas simples \n 5- Pilha simples para pilha final\n 6- Pilha final para simples\nQual movimento deseja realizar? ");
	scanf("%d", &mov);

	//Movimento 1 - descarta do monte virado e passa para o monte visível.
    if(mov== 1){
        //Descartar do monte
        if(!pilha_vazia(binicial)){
            pop(binicial, &g);
            g.visivel = 1;
            push(bvisivel, g);
        }
    }

    if(mov == 2){
        //Do monte pra Pilhas Simples.
        printf("-");
        printf("\nPara qual pilha vc quer mover? [1, 2, 3, 4, 5, 6, 7] "); //Configura a pilha para onde a carta será movida.
        scanf("%d", &destino);

		if(Monte_para_Simples(p1, p2, p3, p4, p5, p6, p7, bvisivel, destino)==0) //Inicializa a função desse movimento
            cout << "--------------- MOVIMENTO INVÁLIDO ------------"; //Caso a função retorne 0, indica que o movimento é inválido
        Sleep(1000); //Como as funções estão se repetindo em loop, utilizamos a função sleep para dar tempo para visualizar caso o movimento seja inválido.
		}

	if(mov == 3){
		//Do monte pra Pilha Final.
		//Quando colocar uma carta na pilha final setar um contador pra configurar o loop.
		//printf("-");printf("\nPara qual pilha vc quer mover? [1-COPAS, 2-OUROS, 3-PAUS, 4-ESPADAS] "); //Configura o destino
		//scanf("%d", &destino);
		if(Monte_para_Final(bvisivel, PF1, PF2, PF3, PF4, pontos)==0)//Inicializa a função desse movimento
            cout << "------------- MOVIMENTO INVÁLIDO ------------";//Caso a função retorne 0, indica que o movimento é inválido
        Sleep(1000);//Como as funções estão se repetindo em loop, utilizamos a fnção sleep para dar tempo de visualizar caso o movimento seja inválido.
		}

	if(mov == 4){
		//Entre Pilhas Simples.
        int qntdd;

		printf("\nDe qual pilha vc quer mover? [1, 2, 3, 4, 5, 6, 7] ");//Interface para definir de onde a carta será movida.
		scanf("%d", &origem);
		printf("\nPara qual pilha vc quer mover? [1, 2, 3, 4, 5, 6, 7] ");//Interface para definir para onde a carta será movida.
		scanf("%d", &destino);
		printf("\nQuantas cartas da pilha vai querer mover? [1, 2, 3, 4, 5, 6, 7] ");//Interface para definir quantas cartas serão movidas.
		scanf("%d", &qntdd);

		if(Simples_para_Simples(p1, p2, p3, p4, p5, p6, p7, origem, destino, qntdd)==0)//Inicializa a função desse movimento
            cout << "------------- MOVIMENTO INVÁLIDO ------------";//Caso a função retorne 0, indica que o movimento é inválido
        Sleep(1000);//Como as funções estão se repetindo em loop, utilizamos a fnção sleep para dar tempo de visualizar caso o movimento seja inválido.
        }

    if(mov == 5){
        //Pilha Simples para Pilha Final.
        printf("\nDe qual pilha vc quer mover? [1, 2, 3, 4, 5, 6, 7] ");//Interface para definir de qual pilha será movido.
        scanf("%d", &origem);
        if (Simples_para_Final(p1,p2,p3,p4,p5,p6,p7,PF1,PF2,PF3,PF4,origem, pontos)==0)//Inicializa a função desse movimento
            cout << "------------- MOVIMENTO INVÁLIDO ------------";//Caso a função retorne 0, indica que o movimento é inválido
        Sleep(1000);//Como as funções estão se repetindo em loop, utilizamos a fnção sleep para dar tempo de visualizar caso o movimento seja inválido.
        }

    if(mov==6){
        //Pilha Final para Pilha Simples.
        printf("\nDe qual pilha vc quer mover? [1-COPAS, 2-OUROS, 3-PAUS, 4-ESPADAS] ");//Interface para definir de qual pilha será movida a carta.
        scanf("%d", &origem);
        printf("\n Para qual pilha vc deseja mover? [1, 2, 3, 4, 5, 6, 7] ");//Interface para definir para onde pilha será movida
        scanf("%d",&destino);
        if(Final_para_Simples(p1,p2,p3,p4,p5,p6,p7,PF1,PF2,PF3,PF4,origem,destino,pontos)==0)//Inicializa a função desse movimento
            cout << "------------- MOVIMENTO INVÁLIDO ------------";//Caso a função retorne 0, indica que o movimento é inválido
        Sleep(1000);//Para visualização.
    }
}

int main(){
    //Definindo a cor do fundo, linguagem e a aleatoriedade.
    system("color 2F");
    setlocale (LC_ALL, "");
    srand(time(NULL));

    //Criação dos naipes
    carta copas[13];
    carta ouros[13];
    carta paus[13];
    carta espadas[13];
    carta baralho[52];//Baralho onde as cartas serão recebidas em posições aleatórias.
    int tam = 52;//Quantidade de cartas no total.

    //Zerando a pontuação (pontos = cartas nas pilhas finais).
    int pontos = 0;

    int vet[tam];
    int i;
    for(i=0; i<tam; i++){
        vet[i]=i+1;
    }

    //Função que embaralha os índices das cartas.
    embaralhar(vet, tam);

    //Caracterizando as cartas dos naipes.
    for (i=0; i<13; i++){
        copas[i].naipe= 3;
        copas[i].valor= i+1;
        copas[i].cor= 0;
        copas[i].visivel= 1;
        //Inserindo cartas com índices aleatórios no baralho.
        baralho[vet[i]-1]= copas[i];
    }

    for (i=0; i<13; i++){
        ouros[i].naipe= 4;
        ouros[i].valor= i+1;
        ouros[i].cor= 0;
        ouros[i].visivel= 1;
        //Inserindo cartas com índices aleatórios no baralho.
        baralho[vet[i+13]-1]= ouros[i];
    }

    for (i=0; i<13; i++){
        paus[i].naipe= 5;
        paus[i].valor= i+1;
        paus[i].cor= 1;
        paus[i].visivel= 1;
        //Inserindo cartas com índices aleatórios no baralho.
        baralho[vet[i+26]-1]= paus[i];
    }

    for (i=0; i<13; i++){
        espadas[i].naipe= 6;
        espadas[i].valor= i+1;
        espadas[i].cor= 1;
        espadas[i].visivel= 1;
        //Inserindo cartas com índices aleatórios no baralho.
        baralho[vet[i+39]-1]= espadas[i];
    }

    //Declarando e inicializando as pilhas Baralho Inicial, Baralho Visível e as pilhas de 1 a 7.
    tp_pilha baralho_inicial, baralhovisivel, p1, p2, p3, p4, p5, p6, p7;
    inicializa_pilha(&baralho_inicial);
    inicializa_pilha(&baralhovisivel);
    inicializa_pilha(&p1);
    inicializa_pilha(&p2);
    inicializa_pilha(&p3);
    inicializa_pilha(&p4);
    inicializa_pilha(&p5);
    inicializa_pilha(&p6);
    inicializa_pilha(&p7);

    //Declarando e inicializando as pilhas finais, que são pilhas simplesmente encadeadas.
    tp_pilhad *PF1; //Copas
    PF1=inicializa_pilhad();
    tp_pilhad *PF2; //Ouros
    PF2=inicializa_pilhad();
    tp_pilhad *PF3; //Paus
    PF3=inicializa_pilhad();
    tp_pilhad *PF4; //Espadas
    PF4=inicializa_pilhad();

    int cont;

    tp_item e;

    //Inserindo as cartas dos baralhos nas pilhas P1 a P7.
    for (cont=0; cont<52; cont++)
        push(&baralho_inicial, baralho[cont]);

    for (cont=0; cont<1; cont++){
        pop(&baralho_inicial, &e);
        push(&p1, e);
    }

    for (cont=1; cont<3; cont++){
        pop(&baralho_inicial, &e);
        if(cont>1)
            e.visivel=0;
        push(&p2, e);
    }

    for (cont=3; cont<6; cont++){
        pop(&baralho_inicial, &e);
        if(cont>3)
            e.visivel=0;
        push(&p3, e);
    }

    for (cont=6; cont<10; cont++){
        pop(&baralho_inicial, &e);
        if(cont>6)
            e.visivel=0;
        push(&p4, e);
    }

    for (cont=10; cont<15; cont++){
        pop(&baralho_inicial, &e);
        if(cont>10)
            e.visivel=0;
        push(&p5, e);
    }

    for (cont=15; cont<21; cont++){
        pop(&baralho_inicial, &e);
        if(cont>15)
            e.visivel=0;
        push(&p6, e);
    }

    for (cont=21; cont<28; cont++){
        pop(&baralho_inicial, &e);
        if(cont>21)
            e.visivel=0;
        push(&p7, e);
    }

    //Invertendo as pilhas para que sejam devidamente exibidas.
    invertepilha(&p2);
    invertepilha(&p3);
    invertepilha(&p4);
    invertepilha(&p5);
    invertepilha(&p6);
    invertepilha(&p7);

	//Função para imprimir o tabuleiro inicial.
    imprimetabuleiro(&p1,&p2,&p3,&p4,&p5,&p6,&p7, &baralho_inicial, &baralhovisivel, PF1, PF2, PF3, PF4, &pontos);

    printf("\n");

    //Loop do jogo, que apenas será interrompido caso todas as pilhas finais estejam completas.
    while(pontos != 52){
        system("cls");
        //Função de imprimir todo o tabuleiro, que será usada no final de cada rodada.
        imprimetabuleiro(&p1,&p2,&p3,&p4,&p5,&p6,&p7, &baralho_inicial, &baralhovisivel, PF1, PF2, PF3, PF4, &pontos);

        //Função em que o jogado escolhe 1 de 6 ações para realizar.
        Mover(&p1,&p2,&p3,&p4,&p5,&p6,&p7, &baralho_inicial, &baralhovisivel, PF1, PF2, PF3, PF4, &pontos);
    }
    //Caso saia do loop, a mensagem será exibida.
    printf ("\nParabéns você venceu!!\n");

    return 0;
}



