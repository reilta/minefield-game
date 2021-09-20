#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std;

int const tmax = 40;
int melhores_t[4]={0,0,0,0};
char jogadores[4][100];

void menu();
void menu_jogo();
char menu_opcao(int& cont);
void preenche_campo(char campo[][tmax], int l, int c);
void coloca_bomba(char cbomba[][tmax], int l, int c, int cb);
void bomba_vizinhaca(char cbomba[][tmax], int l, int c);
void exibe_campo(char campo[][tmax], int l, int c);
void exibe_gameover(char campo[][tmax], char cbomba[][tmax], int l, int c);
void exibe_winner(char campo[][tmax], char cbomba[][tmax], int l, int c);
void descobre_quadrado(char campo[][tmax], char cbomba[][tmax], int li, int co, int l, int c);
int verifica_campo(char campo[][tmax], int l, int c, int cnt);
void verifica_opcao(char op, char campo[][tmax], char cbomba[][tmax], int l, int c, int li, int co, int& cont, int tempo);
void jogo_iniciante(int l, int c);
void jogo_intermediario(int l, int c);
void jogo_personalizado();
void escreve_arquivo(char nomearq[50]);
void ler_arquivo(char nomearq[50]);
void verifica_tempo();
void troca(int a, int b);
void escreve_vetor(char nomearq[50]);
void melhores_tempos();
void opcao();
void bemvindo();
void espaco_coluna(int c);
void espaco_linha(int i);

int main(){

    srand(time(NULL));
    bemvindo();
    menu();

    return 0;
}

void menu(){
    int opm;
    cout<<"           CAMPO MINADO         "<<endl;
    do{
        cout<<"1 - Novo Jogo \n";
        cout<<"2 - Melhores tempos \n";
        cout<<"3 - Sair \n";
        cin>>opm;
    }while(opm<=0 || opm>3);

    system("CLS");

    if(opm==1){
        menu_jogo();
    }
    if(opm==2){
        melhores_tempos();
        opcao();
    }
    if(opm==3){
        exit(0);
    }
}

void menu_jogo(){
    int op;

    do{
        cout<<"1 - Jogo Iniciante \n";
        cout<<"2 - Jogo Intermediario \n";
        cout<<"3 - Jogo Personalizado \n";
        cout<<"4 - Voltar \n";
        cin>>op;
    }while(op<1 || op >4);

    system("CLS");

    if(op==1){
        char nomearq[] = "iniciante.txt";
        escreve_vetor(nomearq);
        jogo_iniciante(8,8);
    }
    if(op==2){
        char nomearq[] = "intermediaria.txt";
        escreve_vetor(nomearq);
        jogo_intermediario(16,16);
    }
    if(op==3){
        jogo_personalizado();
    }
    if(op==4){
        menu();
    }
}

char menu_opcao(int& cont){
    char op;
    cout<<"Minas a marcar: "<<cont<<endl;
    cout<<"D - Descobrir quadrado \n";
    cout<<"M - Marcar mina \n";
    cout<<"T - Talvez mina \n";
    cout<<"L - Limpar marcação \n";
    cout<<"S - Sair \n";

    cin>>op;

    return op;
}

void preenche_campo(char campo[][tmax], int l, int c){
    for(int i = 0; i<l; i++){
        for(int j = 0; j<c; j++){
            campo[i][j]='.';
        }
    }
}

void coloca_bomba(char cbomba[][tmax], int l, int c, int cb){
    int li, co, cont = 0;
    do{
        li = rand()%l;
        co = rand()%c;

        if(cbomba[li][co]=='.'){
            cbomba[li][co]='$';
            cont++;
        }
    }while(cont<cb);
}

void bomba_vizinhaca(char cbomba[][tmax], int l, int c){
    int cb = 0;

    for(int i = 0; i<l; i++){
        for(int j = 0; j<c;j++){
            if(cbomba[i][j]!='$'){
                if(cbomba[i][j+1]=='$' && (j+1)<c){
                    cb++;
                }
                if(cbomba[i][j-1]=='$' && (j-1)>=0){
                    cb++;
                }
                if(cbomba[i+1][j]=='$' && (i+1)<l){
                    cb++;
                }
                if(cbomba[i-1][j]=='$' && (i-1)>=0){
                    cb++;
                }
                if(cbomba[i+1][j+1]=='$' && (i+1)<l && (j+1)<c){
                    cb++;
                }
                if(cbomba[i-1][j-1]=='$' && (i-1)>=0 && (j-1)>=0){
                    cb++;
                }
                if(cbomba[i+1][j-1]=='$' && (i+1)<l && (j-1)>=0){
                    cb++;
                }
                if(cbomba[i-1][j+1]=='$' && (i-1)>=0 && (j+1)<c){
                    cb++;
                }
                cbomba[i][j] = cb+'0';
            }
            cb = 0;
        }
    }
}

void descobre_quadrado(char campo[][tmax], char cbomba[][tmax], int li, int co, int l, int c){
        if(li<0 || li>l-1 || co<0 || co>c-1){
            return;
        }
        if(cbomba[li][co]=='0'){
            campo[li][co]='_';
            cbomba[li][co]='.';

            if((li>=0 && li<l) && (co>=0 && co<c)){
                descobre_quadrado(campo,cbomba,li,co+1,l,c);
                descobre_quadrado(campo,cbomba,li+1,co+1,l,c);
                descobre_quadrado(campo,cbomba,li+1,co,l,c);
                descobre_quadrado(campo,cbomba,li,co-1,l,c);
                descobre_quadrado(campo,cbomba,li-1,co-1,l,c);
                descobre_quadrado(campo,cbomba,li-1,co,l,c);
                descobre_quadrado(campo,cbomba,li-1,co+1,l,c);
                descobre_quadrado(campo,cbomba,li+1,co-1,l,c);
            }

        }if(cbomba[li][co]!='$' && cbomba[li][co]!='.'){
            campo[li][co]=cbomba[li][co];
        }
}

void espaco_coluna(int c){
    cout<<"    ";

    for(int j = 0; j<c; j++){
        if(j<9){
            cout<<j+1<<"  ";
        }else{
            cout<<j+1<<" ";
        }
    }

    cout<<endl;
    cout<<endl;
}

void espaco_linha(int i){
    if(i<9){
            cout<<i+1<<"   ";
        }else{
            cout<<i+1<<"  ";
        }
}

void exibe_campo(char campo[][tmax], int l, int c){

    espaco_coluna(c);

    for(int i = 0; i<l; i++){
        espaco_linha(i);
        for(int j = 0; j<c; j++){
            cout<<campo[i][j]<<"  ";
        }
        cout<<endl;
        cout<<endl;
    }

    cout<<endl;
}

void exibe_gameover(char campo[][tmax], char cbomba[][tmax], int l, int c){

    espaco_coluna(c);

    for(int i = 0; i<l; i++){
        espaco_linha(i);

        for(int j = 0; j<c; j++){
            if(cbomba[i][j]=='$' && campo[i][j]!='M'){
                campo[i][j]='*';
            }
            if(campo[i][j]=='M' && cbomba[i][j]!='$'){
                campo[i][j]='#';
            }
            cout<<campo[i][j]<<"  ";
        }
        cout<<endl;
        cout<<endl;
    }
    cout<<endl;
}

void exibe_winner(char campo[][tmax], char cbomba[][tmax], int l, int c){

    espaco_coluna(c);

    for(int i = 0; i<l; i++){
        espaco_linha(i);

        for(int j = 0; j<c; j++){
            if(cbomba[i][j]=='$' && campo[i][j]!='M'){
                campo[i][j]='$';
            }
            if(cbomba[i][j]=='$' && campo[i][j]=='M'){
                campo[i][j]='M';
            }
            cout<<campo[i][j]<<" ";
        }
        cout<<endl;
        cout<<endl;
    }
    cout<<endl;
}

int verifica_campo(char campo[][tmax], int l, int c){
    int cont = 0;
    for(int i = 0; i<l; i++){
        for(int j = 0; j<c; j++){
            if(campo[i][j]!='.' && campo[i][j]!='M'){
                cont++;
            }
        }
    }
    return cont;
}

void verifica_opcao(char op, char campo[][tmax], char cbomba[][tmax], int l, int c, int li, int co, int& cont, int tempo){
    if(op=='D' || op=='d'){
        do{
            cout<<"digite as coordenadas: \n";
            cin>>li>>co;
        }while(li<1 || li>l || co<1 || co>c);

        if(cbomba[li-1][co-1]=='$'){
            cout<<"Tempo: "<<tempo<<" segundo(s)"<<endl;
            cout<<"PERDEU! \n";
            exibe_gameover(campo,cbomba,l,c);
            opcao();
        }

        descobre_quadrado(campo,cbomba,li-1,co-1,l,c);
    }

    if(op=='M' || op=='m'){
        do{
            cout<<"digite as coordenadas: \n";
            cin>>li>>co;
        }while(li<1 || li>l || co<1 || co>c);
            campo[li-1][co-1]='M';
            cont--;
    }

    if(op=='T' || op=='t'){
        do{
            cout<<"digite as coordenadas: \n";
            cin>>li>>co;
        }while(li<1 || li>l || co<1 || co>c);

        if(campo[li-1][co-1]=='.'){
            campo[li-1][co-1]='?';
        }
    }

    if(op=='L' || op=='l'){
        do{
            cout<<"digite as coordenadas: \n";
            cin>>li>>co;
        }while(li<1 || li>l || co<1 || co>c);

        campo[li-1][co-1]='.';
        cont++;
    }

    if(op=='S' || op=='s'){
        exit(0);
    }
}

void troca(int a, int b){
    int aux;
    char auxn[100];

    aux = melhores_t[a];
    melhores_t[a] = melhores_t[b];
    melhores_t[b] = aux;

    strcpy(auxn,jogadores[a]);
    strcpy(jogadores[a],jogadores[b]);
    strcpy(jogadores[b], auxn);
}

void verifica_tempo(){
    int minimo;
    for (int i=0; i<3; i++){
        minimo = i;
        for (int j=i+1; j<4 ; j++){
            if(melhores_t[j]<melhores_t[minimo]){
                minimo = j;
            }
        }
        troca(i,minimo);
    }
}

void jogo_iniciante(int l, int c){
    char campo[tmax][tmax], cbomba[tmax][tmax];
    bool mina = true;
    char op;
    int li, co, cont = 10, contcampo = 0, cb = 10, contquad = ((l*c)-10);
    preenche_campo(campo,l,c);
    preenche_campo(cbomba,l,c);
    coloca_bomba(cbomba,l,c,cb);
    bomba_vizinhaca(cbomba,l,c);
    int tempo, inicio = time(0), fim = time(0);
    char nomearq[50] = "iniciante.txt";

    while(mina){
        tempo = fim - inicio;
        cout<<"Tempo: "<<tempo<<" segundo(s)"<<endl;

        contcampo = verifica_campo(campo,l,c);
        if(contcampo==contquad){
            cout<<"VOCE GANHOU! \n";
            exibe_winner(campo,cbomba,l,c);
            if(tempo<melhores_t[2]){
                cout<<"digite seu nome: \n";
                cin>>jogadores[3];
                melhores_t[3] = tempo;
                verifica_tempo();
                escreve_arquivo(nomearq);
                cout<<"TEMPOS RECORDES \n";
                cout<<endl;
                ler_arquivo(nomearq);
            }else{
                cout<<"Nao foi um dos tres melhores tempos!"<<endl;
                ler_arquivo(nomearq);
            }
            opcao();
        }
        contcampo = 0;

        exibe_campo(campo,l,c);
        //exibe_campo(cbomba,l,c);

        op = menu_opcao(cont);

        verifica_opcao(op,campo,cbomba,l,c,li,co,cont,tempo);

        system("CLS");

        fim = time(0);
    }
}

void jogo_intermediario(int l, int c){
    char campo[tmax][tmax], cbomba[tmax][tmax];
    bool mina = true;
    char op;
    int li, co, cont = 40, contcampo = 0, cb = 40, contquad = ((l*c)-40);
    preenche_campo(campo,l,c);
    preenche_campo(cbomba,l,c);
    coloca_bomba(cbomba,l,c,cb);
    bomba_vizinhaca(cbomba,l,c);
    int tempo, inicio = time(0), fim = time(0);
    char nomearq[50] = "intermediaria.txt";

    while(mina){
        tempo = fim - inicio;
        cout<<"Tempo: "<<tempo<<" segundo(s)"<<endl;

        contcampo = verifica_campo(campo,l,c);
        if(contcampo==contquad){
            cout<<"VOCE GANHOU! \n";
            exibe_winner(campo,cbomba,l,c);
            if(tempo<melhores_t[2]){
                cout<<"digite seu nome: \n";
                cin>>jogadores[3];
                melhores_t[3] = tempo;
                verifica_tempo();
                escreve_arquivo(nomearq);
                ler_arquivo(nomearq);
            }else{
                cout<<"Nao foi um dos tres melhores tempos!"<<endl;
                ler_arquivo(nomearq);
            }
            opcao();
        }
        contcampo = 0;

        exibe_campo(campo,l,c);
        //exibe_campo(cbomba,l,c);

        op = menu_opcao(cont);

        verifica_opcao(op,campo,cbomba,l,c,li,co,cont, tempo);

        system("CLS");

        fim = time(0);
    }
}

void jogo_personalizado(){
    char campo[tmax][tmax], cbomba[tmax][tmax];
    int l, c, bombas, t;
    do{
        cout<<"informe o tamanho do campo (linha e coluna): \n";
        cin>>l>>c;
        t = (l*c)-10;
    }while(t<10);

    do{
        cout<<"digite a quantidade de bombas: \n";
        cin>>bombas;
        t = (l*c)-10;
    }while(bombas<0 || bombas>t);

    system("CLS");

    bool mina = true;
    char op;
    int li, co, cont = bombas, contcampo = 0, contquad = ((l*c)-bombas);
    preenche_campo(campo,l,c);
    preenche_campo(cbomba,l,c);
    coloca_bomba(cbomba,l,c,bombas);
    bomba_vizinhaca(cbomba,l,c);
    int tempo, inicio = time(0), fim = time(0);

    while(mina){
        tempo = fim - inicio;
        cout<<"Tempo: "<<tempo<<" segundo(s)"<<endl;

        contcampo = verifica_campo(campo,l,c);
        if(contcampo==contquad){
            cout<<"VOCE GANHOU! \n";
            exibe_winner(campo,cbomba,l,c);
            opcao();
        }
        contcampo = 0;

        exibe_campo(campo,l,c);
        //exibe_campo(cbomba,l,c);

        op = menu_opcao(cont);

        verifica_opcao(op,campo,cbomba,l,c,li,co,cont,tempo);

        system("CLS");

        fim = time(0);
    }
}

void escreve_arquivo(char nomearq[50]){
    ofstream arquivo(nomearq);
    if(!arquivo.is_open()){
        cout<<"Falha ao abrir arquivo! \n";
        exit(0);
    }else{
        for(int i = 0; i<3; i++){
            arquivo<<melhores_t[i]<<" "<<jogadores[i]<<endl;
        }
    }
    arquivo.close();
}

void escreve_vetor(char nomearq[50]){
    ifstream arquivo(nomearq);
    int i = 0;

    if (arquivo.is_open()){
        while(!arquivo.eof()){
            arquivo>>melhores_t[i];
            //arquivo>>jogadores[i];
            arquivo.getline(jogadores[i],100);
            i++;
        }
        arquivo.close();
    }
    else{
        cout<<"Falha ao abrir arquivo! \n";
    }
}

void ler_arquivo(char nomearq[50]){
    //ifstream arquivo("melhorestempos.txt");
    ifstream arquivo(nomearq);
    int i = 0;

    if (arquivo.is_open()){
        for(int i = 0; i<3; i++){
            arquivo>>melhores_t[i];
            //arquivo>>jogadores[i];
            arquivo.getline(jogadores[i],100);
            cout<<i+1<<"º "<<melhores_t[i]<<" "<<jogadores[i]<<endl;
        }
        arquivo.close();
    }
    else{
        cout<<"Falha ao abrir arquivo! \n";
    }
}

void melhores_tempos(){
    char nomearq1[50] = "iniciante.txt";
    escreve_vetor(nomearq1);
    cout<<"                 RECORDES              "<<endl;
    cout<<"              NIVEL INICIANTE           "<<endl;
    cout<<endl;
    ler_arquivo(nomearq1);

    cout<<endl;

    char nomearq2[50] = "intermediaria.txt";
    escreve_vetor(nomearq2);
    cout<<"            NIVEL INTERMEDIARIO          "<<endl;
    cout<<endl;
    ler_arquivo(nomearq2);

    cout<<endl;
}

void opcao(){
    int op;
    do{
        cout<<"Deseja sair do jogo? \n";
        cout<<"1 - Sim \n";
        cout<<"2 - Nao \n";
        cin>>op;
    }while(op!=1 && op!=2);

    system("CLS");

    if(op==1){
        exit(0);
    }else{
        menu();
    }
}

void bemvindo(){
    cout<<"         BEM-VINDO AO JOGO       "<<endl;
}
