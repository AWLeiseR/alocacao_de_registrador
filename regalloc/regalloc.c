#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int totalReg = 0;
int numGrafo;
int tamanhoDaPilha;
int auxTotal;
int *testes;

typedef struct{
    int *a;
    int first;
    int ocupados;
    int tamanho;
}Pilha;

typedef struct{
    int numero;
    int cor;
    int tamAdjacentes;
    int tamanhoVetAdjacentes;
    int *adjacentes;
}Registrador;

typedef struct{
    Registrador *registradores;
    int tam;
    int ocupados;
}Grafo;

Pilha *p;
Pilha *cores;
Grafo *g;

Pilha* setaPilha(int tam){
    Pilha *pilha = (Pilha *) malloc(sizeof(Pilha));
    pilha->a = (int* ) malloc(sizeof(int)*tam);
    pilha->first = -1;
    pilha->tamanho = tam;
    pilha->ocupados = 0;
    return pilha;
}

void pushPilha(Pilha *pilha, int x){
    int aux = pilha->first;
    
    if(pilha->first <pilha->tamanho - 1){
        pilha->first++;
        pilha->ocupados ++;
        pilha->a[pilha->first] = x;
    }
}

int popPilha(){
    int aux = p->first;
    if(p->first > -1){
        
        p->first --;
        return p->a[aux];
    }else{
        return -1;
    }
}

int indexOf(Pilha *pilha, int x){
    int i;
    int *vet = pilha->a;
    
    for(i=0;i<pilha->ocupados;i++){
        
        if(vet[i]==x){
           
            return 1;
        }
    }
    return -1;
}

void montarGrafo(int tam){
    g = (Grafo*) malloc(sizeof(Grafo));
    g->tam = tam;
    g->registradores = (Registrador *) malloc(sizeof(Registrador)*tam);
    g->ocupados = 0;
}

void inserirRegistrador(int num, int tam, int *adjacentes){
    g->registradores[g->ocupados].numero = num;
    g->registradores[g->ocupados].tamAdjacentes = tam;
    g->registradores[g->ocupados].tamanhoVetAdjacentes = tam;
    g->registradores[g->ocupados].adjacentes = adjacentes ;
    g->registradores[g->ocupados].cor = -1;
    g->ocupados++;
}

void excluirRegistrador(int res){
    int i,j, registrador;
    Registrador aux;
    int* vet;
    int tamVet;
    
    for(i = 0;i < g->ocupados; i++){
        if(g->registradores[i].numero == res){
            registrador = i;
            vet = g->registradores[i].adjacentes;
            tamVet = g->registradores[i].tamanhoVetAdjacentes;
            break;
        }
    }
    
    for(i = 0; i<tamVet;i++ ){
        for(j=0;j<g->tam;j++){
            if(vet[i] == g->registradores[j].numero){
                g->registradores[j].tamAdjacentes--;
            }
        }
    }
    
    if(g->ocupados > 0){
        aux = g->registradores[g->ocupados-1];
        g->registradores[g->ocupados-1] =g->registradores[registrador];
        g->registradores[registrador] = aux;
        g->ocupados--;
    }
}

int RegistradorPush(){
    int i=1;
    if(g->ocupados > 0){
        if(g->registradores[0].tamAdjacentes < auxTotal){
            printf("Push: %d\n",g->registradores[0].numero);
            return g->registradores[0].numero;
        }else{
            while(g->registradores[g->ocupados-i].tamAdjacentes == g->registradores[g->ocupados-(i+1)].tamAdjacentes){
                i++;
            }
            printf("Push: %d *\n",g->registradores[g->ocupados-i].numero);
            return g->registradores[g->ocupados-i].numero;
        }
         
    }
    return-1;
  
}

int verificaCor(int reg){
    int i;
    
    for(i=0;i<g->ocupados;i++){
        
        if(g->registradores[i].numero == reg){
            //printf("%d->%d ",reg,g->registradores[i].cor);
            return g->registradores[i].cor;
        }
    }
    return -1;
}

int remontaGrafo(int reg){
    int i,j, corIgual=0,regFisico=0;
    int *vet;
    Registrador aux;
    int cor=0, auxcor;
    int tamVetAdjacente;
    cores = setaPilha(totalReg);
    for(i=0;i<g->tam;i++){
        
        if(reg == g->registradores[i].numero){
            aux = g->registradores[g->ocupados];
            g->registradores[g->ocupados] = g->registradores[i];
            g->registradores[i] = aux;
            g->ocupados ++;
        }
    }
    
    vet = g->registradores[g->ocupados-1].adjacentes;
    tamVetAdjacente = g->registradores[g->ocupados-1].tamanhoVetAdjacentes;
    for(i=0;i<tamVetAdjacente;i++){
        if(vet[i]<auxTotal){
            pushPilha(cores,vet[i]);
        }
    }
    // percorre as cores
    for(i=0;i<auxTotal;i++){
        //ve se o reg ja tem alguma cor utilizada
        if(indexOf(cores,i)==-1){
            //nao tem entao varre os adjacentes
            for(j=0;j<tamVetAdjacente;j++){
                //um reg ja possui essa cor
                if(verificaCor(vet[j])==i){
                    cor=0;
                    break;
                }else{
                    cor=1;
                }
            }
        }
        if(cor){
            g->registradores[g->ocupados-1].cor=i;
            break;
        }
           
    }
    if(cor == 0){
        printf("Pop: %d -> NO COLOR AVAILABLE\n",reg);
        testes[auxTotal-2] = 0;
        return 0;
    }else{
        printf("Pop: %d -> %d\n",reg,g->registradores[g->ocupados-1].cor);
        return 1;
    }
}

int compara(const void *p1, const void *p2){
    Registrador *r1 = (Registrador*) p1;
    Registrador *r2 = (Registrador*) p2;
    if(r1->tamAdjacentes > r2->tamAdjacentes){
        return 1;
    }else if( r1->tamAdjacentes == r2->tamAdjacentes && r1->numero > r2->numero){
        return 1;
    }
    return 0;
}

void ordenaGrafo(){
    qsort(g->registradores,g->ocupados,sizeof(Registrador), compara);
}

void imprimiCabecalho(){
    printf("Graph %d -> Physical Registers: %d\n",numGrafo,totalReg);
    printf("----------------------------------------\n");
}

int numLinhas(){
    int i=0;
    char comando;
    while (fscanf(stdin,"%c",&comando) != EOF ){
        if(comando == '\n'){
            i++;
        }
    }
    fseek(stdin,0,SEEK_SET);
    return i;
}

int numRegAdjacentes(char *str){
    char c;
    int i=0,tamAdjacentes = 0;
    while(sscanf(str+i,"%c",&c) != -1){
        if(c==' '){
            tamAdjacentes++;
        }
        i++;
    }
    return tamAdjacentes;
}

void lerArq(){
    char comando[10], str[5000];
    int aux,numRegistrador, i = 0, cursorAdjacentes=0;
    int tamAdjacentes=0;
    int cursorRegistrador=0;
    char c;
    int* vetAdjacentes;

    fscanf(stdin,"%s",comando);
    
    fscanf(stdin,"%d",&numGrafo);
    
    fscanf(stdin,"%s",comando);
    
    fscanf(stdin,"%s",comando); 
    

    totalReg = atoi(comando+(sizeof(char)*2));
   // printf("--%d-- \n\n\n",totalReg);
    tamanhoDaPilha = numLinhas();
    
    testes=(int*) malloc(sizeof(int)*(totalReg-1));
    
    
    p=setaPilha(tamanhoDaPilha);
    montarGrafo(tamanhoDaPilha);
    
    fgets( str, 5000, stdin );
    fgets( str, 5000, stdin );
    
    while(fscanf(stdin,"%d",&numRegistrador)!=EOF){
        //printf("%d ",numRegistrador);
        
        fscanf(stdin, "%s",comando);
        //printf("%s ",comando);
        fgets( str, 5000, stdin );
        tamAdjacentes = numRegAdjacentes(str);
        //printf("-%d \n",tamAdjacentes);
        vetAdjacentes = (int *) malloc(sizeof(int)*(tamAdjacentes));
        while(tamAdjacentes>cursorAdjacentes){
            sscanf(str+i,"%d",&aux);
           vetAdjacentes[cursorAdjacentes] = aux;
            //printf("%d \n",cursorAdjacentes);
            cursorAdjacentes++;
            
            if(aux>10){
                i+=3;
            }else{
                i+=2;
            }
        }
       //printf("\n");
        //printf("-> %d\n",tamAdjacentes);
        inserirRegistrador(numRegistrador,tamAdjacentes,vetAdjacentes);
        cursorAdjacentes = 0;
        i=0;
        tamAdjacentes = 0;        
    }
   
}

void pushRegistradores(){
    int menor;
    
    ordenaGrafo();
    menor = RegistradorPush();
    while(menor > -1){
        
        excluirRegistrador(menor);
        pushPilha(p,menor);
        ordenaGrafo();
        
        menor = RegistradorPush();
        
    }   
}

void popRegistradores(){
    int res = popPilha();

    while(res>-1){
        if(remontaGrafo(res) == 0){
            break;
        }
        
        res = popPilha();
    }
    

}

void recomecar(){
    int i;
    g->ocupados=g->tam;
    for(i=0;i<g->ocupados;i++){
        g->registradores[i].tamAdjacentes = g->registradores[i].tamanhoVetAdjacentes;
        g->registradores[i].cor=-1;
        popPilha();
    }
    
}

void imprimiGrafo(){
    int i,j;
    int *vet;
    
    for(i=0;i<g->ocupados;i++){
        printf("%d ->",g->registradores[i].numero);
        vet = g->registradores[i].adjacentes;
        for(j=0;j<g->registradores[i].tamanhoVetAdjacentes;j++){
            printf("%d ",g->registradores[i].adjacentes[j]);
        }
        printf("\n");
    }
}

void imprimiFinal(){
    int i;
    printf("----------------------------------------\n----------------------------------------\n");

    for(i=0;i<totalReg-1;i++){
        printf("Graph %d -> K = ",numGrafo);
        if(totalReg-i<10){
            printf(" ");
        }
        printf("%d: %s",totalReg-i,testes[totalReg-(i+2)]?"Successful Allocation":"SPILL");
        if(totalReg - i > 2){
            printf("\n");
        }
    }
}

int main(){
    int i;
    lerArq();
    for(i=0;i<totalReg-1;i++){
        testes[i]=1;
    }
    auxTotal=totalReg;
    imprimiCabecalho();
    while(auxTotal>1){
        printf("----------------------------------------\nK = %d\n\n",auxTotal);
        
        pushRegistradores();
        popRegistradores();
        
        auxTotal--;
        recomecar();
    }

    imprimiFinal();
    return 0;
}