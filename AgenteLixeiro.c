#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define QTDAG 2
#define QTDLX 2
#define QTDLIXO 12
#define TAMAMB 8

struct lixeira{
	
	struct lixeira *ant;
	int x,y;
	int tipo;
	int capacidade;
	struct lixeira *prox;
	
};

struct agente{
	
	struct agente *ant;
	int x,y;
	int posLX,posLY;
	int achoLixeira;
	int capSS,capSO;
	struct agente *prox;
	
};

struct lixo{
	
	struct lixo *ant;
	int x,y;
	int tipo;
	struct lixo *prox;
	
};
/*CRIA AS LIXEIRAS
1 == LIXEIRA SECA
2 == LIXEIRA ORGANICA
*/
int iniciaLixeira(struct lixeira **inicio,struct lixeira **fim,int posX,int posY,int tipo,int cap){
	
	struct lixeira *novo=NULL;
	
	novo=(struct lixeira *)malloc(sizeof(struct lixeira));
	
	if(novo==NULL){
		printf("\nNAO FOI POSSIVEL CRIAR LIXEIRA.\n");
	}else{
		novo->x=posX;
		novo->y=posY;
		novo->capacidade=cap;
		novo->tipo=tipo;
		novo->prox=NULL;
		novo->ant=*fim;
		if(*inicio==NULL){
			*inicio=novo;
		}else{
			(*fim)->prox=novo;
		}
		*fim=novo;
	}
}
/*CRIA OS AGENTES
5 == AGENTE
*/
int iniciaAgente(struct agente **inicio,struct agente **fim,int posX,int posY,int capSS,int capSO){
	
	struct agente *novo=NULL;
	
	novo=(struct agente *)malloc(sizeof(struct agente));
	
	if(novo==NULL){
		printf("\nNAO FOI POSSIVEL CRIAR AGENTE.\n");
	}else{
		novo->x=posX;
		novo->y=posY;
		novo->posLX=0;
		novo->posLY=0;
		novo->achoLixeira=0;
		novo->capSS=capSS;
		novo->capSO=capSO;
		novo->prox=NULL;
		novo->ant=*fim;
		if(*inicio==NULL){
			*inicio=novo;
		}else{
			(*fim)-> prox=novo;
		}
		*fim=novo;
	}
	
}
/*CRIA OS LIXOS
3 == LIXO SECO
4 == LIXO ORGANICO
*/
int iniciaLixo(struct lixo **inicio,struct lixo **fim,int posX,int posY,int tipo){
	
	struct lixo *novo=NULL;
	
	novo=(struct lixo *)malloc(sizeof(struct lixo));
	
	if(novo==NULL){
		printf("\nNAO FOI POSSIVEL CRIA LIXO\n");
	}else{
		novo->x=posX;
		novo->y=posY;
		novo->tipo=tipo;
		novo->ant=*fim;
		if(*inicio==NULL){
			*inicio=novo;
		}else{
			(*fim)->prox=novo;
		}
		*fim=novo;
	}
	
}

int iniciaAmbiente(struct agente **inicioA,struct agente **fimA,struct lixeira **inicioL,struct lixeira **fimL,struct lixo **inicioLX,struct lixo **fimLX,int amb[][TAMAMB],int tamamb,int qtdlx,int qtdag,int qtdlixo){
	
	int i,j,valorX,valorY,addok;
	
	/*
	0 == NADA
	1 == LIXEIRA SECA
	2 == LIXEIRA ORGANICA
	3 == LIXO SECO
	4 == LIXO ORGANICO
	5 == AGENTE
	*/
	srand(time(NULL));
	//INICIA O AMBIENTE
	for(i=0;i<tamamb;i++){
		for(j=0;j<tamamb;j++){
			amb[i][j]=0;
		}
	}
	//INICIA LIXOS
	for(i=0;i<qtdlixo;i++){
		valorX=rand()%tamamb;
		valorY=rand()%tamamb;
		if(amb[valorY][valorX]==0){
			if((i%2)==0){
				iniciaLixo(inicioLX,fimLX,valorX,valorY,4);
				amb[valorY][valorX]=4;	
			}else{
				iniciaLixo(inicioLX,fimLX,valorX,valorY,3);
				amb[valorY][valorX]=3;
			}			
		}else{
			i--;
		}
	}
	//INICIA AS LIXEIRAS	
	for(i=0;i<qtdlx;i++){
		addok=0;
		valorX=rand()%tamamb;
		valorY=rand()%tamamb;
		if(amb[valorY][valorX]==0){
			if(valorY==0){
				if(valorX==0){
					if(amb[valorY+1][valorX]==0||amb[valorY][valorX+1]==0){
						addok=1;
					}
				}else if(valorX==7){
					if(amb[valorY+1][valorX]==0||amb[valorY][valorX-1]==0){
						addok=1;
					}
				}else{
					if(amb[valorY+1][valorX]==0||amb[valorY][valorX-1]==0||amb[valorY][valorX+1]){
						addok=1;
					}
				}
			}else if(valorY==7){
				if(valorX==0){
					if(amb[valorY-1][valorX]==0||amb[valorY][valorX+1]==0){
						addok=1;
					}
				}else if(valorX==7){
					if(amb[valorY-1][valorX]==0||amb[valorY][valorX-1]==0){
						addok=1;
					}
				}else{
					if(amb[valorY-1][valorX]==0||amb[valorY][valorX-1]==0||amb[valorY][valorX+1]){
						addok=1;
					}
				}
			}else if(valorX==0){
				if(amb[valorY+1][valorX]==0||amb[valorY-1][valorX]==0||amb[valorY][valorX+1]){
					addok=1;
				}
			}else if(valorX==7){
				if(amb[valorY+1][valorX]==0||amb[valorY-1][valorX]==0||amb[valorY][valorX-1]){
					addok=1;
				}
			}else{
				if(amb[valorY+1][valorX]==0||amb[valorY-1][valorX]==0||amb[valorY][valorX-1]||amb[valorY][valorX+1]==0){
					addok=1;
				}				
			}
			if(addok==1){
				if((i%2)==0){
					iniciaLixeira(inicioL,fimL,valorX,valorY,2,6);
					amb[valorY][valorX]=2;
				}else{
					iniciaLixeira(inicioL,fimL,valorX,valorY,1,6);
					amb[valorY][valorX]=1;
				}
			}else{
				i--;
			}
		}else{
			i--;
		}
	}
	//INICIA OS AGENTES
	for(i=0;i<qtdag;i++){
		valorX=rand()%tamamb;
		valorY=rand()%tamamb;
		if(amb[valorY][valorX]==0){
			iniciaAgente(inicioA,fimA,valorX,valorY,3,3);
			amb[valorY][valorX]=5;		
		}else{
			i--;
		}
	}
	
}

int observaAmbiente(struct agente *a,int amb[][TAMAMB],int tamamb){
	
	int i=0,j=0;
	//SE TEM CAPACIDADE NAS BOLSAS	
	if(a->capSO>0&&a->capSS>0){
		i=a->x==0?0:-2;
		i=a->x==1?-1:i;
	
		while(i<=2){
			if(a->x+i<=tamamb&&a->x+i>=0&&(amb[a->y][a->x+i]==4||amb[a->y][a->x+i]==3)){
				//LIXO NO ALCANCE EM X
				if(a->capSS>0&&amb[a->y][a->x+i]==3){
					return(i);
				}else if(a->capSO>0&&amb[a->y][a->x+i]==4){
					return(i);
				}			
			}
			i++;
		}
	
		i=a->y==0?0:-2;
		i=a->y==1?-1:i;
	
		while(i<=2){
			if(a->y+i<=tamamb&&a->y+i>=0&&(amb[a->y+i][a->x]==4||amb[a->y+i][a->x]==3)){
				//LIXO NO ALCANCE EM Y
				if(a->capSS>0&&amb[a->y+i][a->x]==3){
					return(i*10);
				}else if(a->capSO>0&&amb[a->y+i][a->x]==4){
					return(i*10);	
				}
			}
			i++;
		}
	}else{//SE NÃO ESTA VAI ATRAS DA LIXEIRA MAIS PROXIMA
		if(a->achoLixeira==0){
			for(i=0;i<tamamb;i++){
				for(j=0;j<tamamb;j++){
					if(a->capSS==0){
						if(amb[i][j]==1){
							a->posLX=j;
							a->posLY=i;
						}
					}else if(a->capSO==0){
						if(amb[i][j]==2){
							a->posLX=j;
							a->posLY=i;
						}
					}
				}
			}
			a->achoLixeira=1;
		}else{
			if(a->x>a->posLX){
				if(amb[a->y][a->x-1]==0){
					return(-1);
				}
			}else if(a->x<a->posLX){
				if(amb[a->y][a->x+1]==0){
					return(+1);
				}
			}else if(a->y>a->posLY){
				if(amb[a->y-1][a->x]==0){
					return(-10);
				}
			}else if(a->y<a->posLY){
				if(amb[a->y+1][a->x]==0){
					return(+10);
				}	
			}
		}
	}
	return(0);
}

int coleta(struct agente *a,int npos){
	
	if(npos==3){
		a->capSS--;
	}else if(npos==4){
		a->capSO--;
	}
			
}

int movimentaAgente(struct agente **inicio,struct agente **fim,int amb[][TAMAMB],int tamamb){
	
	struct agente *aux=*inicio;
	int dir=0;
	
	while(aux!=NULL){
		if(dir==0){
			dir=observaAmbiente(aux,amb,tamamb);
		}		
		if(dir<=2&&dir>=1){
			if(aux->x+1<=7&&amb[aux->y][aux->x+1]==0||amb[aux->y][aux->x+1]==3||amb[aux->y][aux->x+1]==4){
				amb[aux->y][aux->x]=0;
				aux->x++;
				coleta(aux,amb[aux->y][aux->x]);
				amb[aux->y][aux->x]=5;
			}
		}else if(dir<=-1&&dir>=-2){
			if(aux->x-1>=0&&amb[aux->y][aux->x-1]==0||amb[aux->y][aux->x-1]==3||amb[aux->y][aux->x-1]==4){
				amb[aux->y][aux->x]=0;
				aux->x--;
				coleta(aux,amb[aux->y][aux->x]);
				amb[aux->y][aux->x]=5;
			}		
		}else if(dir<=20&&dir>=10){
			if(aux->y+1<=7&&amb[aux->y+1][aux->x]==0||amb[aux->y+1][aux->x]==3||amb[aux->y+1][aux->x]==4){
				amb[aux->y][aux->x]=0;
				aux->y++;
				coleta(aux,amb[aux->y][aux->x]);
				amb[aux->y][aux->x]=5;
			}
		}else if(dir<=-10&&dir>=-20){
			if(aux->y-1>=0&&amb[aux->y-1][aux->x]==0||amb[aux->y-1][aux->x]==3||amb[aux->y-1][aux->x]==4){
				amb[aux->y][aux->x]=0;
				aux->y--;
				coleta(aux,amb[aux->y][aux->x]);
				amb[aux->y][aux->x]=5;
			}
		}else{
			
			printf("\nWHAT\n");
		}
		printf("\nDIR %d\n",dir);
		dir=0;
		aux=aux->prox;
	}
	
}

int imprimeLixeira(struct lixeira **inicio){
	
	struct lixeira *aux=*inicio;
	
	while(aux!=NULL){
		printf("\n%d\t%d\t%d\t%d",aux->x,aux->y,aux->tipo,aux->capacidade);
		aux=aux->prox;
	}
	
}

int imprimeAgente(struct agente **inicio){
	
	struct agente *aux=*inicio;
	
	while(aux!=NULL){
		printf("\nXA:%d\tYA:%d\tCO:%d\tCS:%d\tLX:%d\tLY:%d",aux->x,aux->y,aux->capSO,aux->capSS,aux->posLX,aux->posLY);
		aux=aux->prox;
	}
	
}

int imprimeAmbiente(int amb[][TAMAMB],int tamamb){
	
	int i,j;
	
	for(i=0;i<tamamb;i++){
		for(j=0;j<tamamb;j++){
			if(amb[i][j]==0){
				printf("%4c",' ');
			}else if(amb[i][j]==1){
				printf("%2c%-2c",'L','S');
			}else if(amb[i][j]==2){
				printf("%2c%-2c",'L','O');
			}else if(amb[i][j]==3){
				printf("%4c",'S');
			}else if(amb[i][j]==4){
				printf("%4c",'O');
			}else if(amb[i][j]==5){
				printf("%4c",'A');
			}
		}
		printf("\n");
	}
	
}

int main(){
	
	struct agente *ptriAg=NULL;
	struct agente *ptrfAg=NULL;
	struct lixeira *ptriLixeira=NULL;
	struct lixeira *ptrfLixeira=NULL;
	struct lixo *ptriLixo=NULL;
	struct lixo *ptrfLixo=NULL;
	int ambiente[TAMAMB][TAMAMB];
	int i=0;
	
	iniciaAmbiente(&ptriAg,&ptrfAg,&ptriLixeira,&ptrfLixeira,&ptriLixo,&ptrfLixo,ambiente,TAMAMB,QTDLX,QTDAG,QTDLIXO);
	
	while(ptriLixo!=NULL){
		printf("LIXEIRA");
		imprimeLixeira(&ptriLixeira);
		printf("\n\nAGENTE");
		imprimeAgente(&ptriAg);	
		printf("\n\nAMBIENTE\n\n");
		imprimeAmbiente(ambiente,TAMAMB);
		movimentaAgente(&ptriAg,&ptrfAg,ambiente,TAMAMB);
		getchar();
		system("cls");
	}
}
