#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std;

int const tmax = 40;

void menu(char campo[][tmax], char cbomba[][tmax]);
void menu_jogo(char campo[][tmax], char cbomba[][tmax]);
char menu_opcao(int& cont);
void preenche_campo(char campo[][tmax], int l, int c);
void coloca_bomba(char cbomba[][tmax], int l, int c, int cb);
void bomba_vizinhaca(char cbomba[][tmax], int l, int c);
void exibe_campo(char campo[][tmax], int l, int c);
void exibe_gameover(char campo[][tmax], char cbomba[][tmax], int l, int c);
void descobre_quadrado(char campo[][tmax], char cbomba[][tmax], int li, int co, int l, int c);
int verifica_campo(char campo[][tmax], int l, int c, int cnt);
void verifica_opcao(char op, char campo[][tmax], char cbomba[][tmax], int l, int c, int li, int co, int& cont);
void jogo_iniciante(char campo[][tmax], char cbomba[][tmax], int l, int c);
void jogo_intermediario(char campo[][tmax], char cbomba[][tmax], int l, int c);
void jogo_personalizado(char campo[][tmax], char cbomba[][tmax]);


int main(){
    char campo[tmax][tmax], cbomba[tmax][tmax];

    srand(time(NULL));

    menu(campo,cbomba);

    return 0;
}

void menu(char campo[][tmax], char cbomba[][tmax]){
    int opm;
    do{
        cout<<"1 - Novo Jogo \n";
        cout<<"2 - Melhores tempos \n";
        cout<<"3 - Sair \n";
        cin>>opm;
    }while(opm<=0 || opm>3);

    system("CLS");

    if(opm==1){
        menu_jogo(campo,cbomba);
    }
    if(opm==2){
        //melhores_tempos();
    }
    if(opm==3){
        exit(0);
    }
}

void menu_jogo(char campo[][tmax], char cbomba[][tmax]){
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
        jogo_iniciante(campo,cbomba,8,8);
    }
    if(op==2){
        jogo_intermediario(campo,cbomba,16,16);
    }
    if(op==3){
        jogo_personalizado(campo,cbomba);
    }
    if(op==4){
        menu(campo,cbomba);
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
                if(cbomba[i][j+1]=='$'){
                    cb++;
                }
                if(cbomba[i][j-1]=='$'){
                    cb++;
                }
                if(cbomba[i+1][j]=='$'){
                    cb++;
                }
                if(cbomba[i-1][j]=='$'){
                    cb++;
                }
                if(cbomba[i+1][j+1]=='$'){
                    cb++;
                }
                if(cbomba[i-1][j-1]=='$'){
                    cb++;
                }
                if(cbomba[i+1][j-1]=='$'){
                    cb++;
                }
                if(cbomba[i-1][j+1]=='$'){
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

void exibe_campo(char campo[][tmax], int l, int c){
    /*cout<<"    ";
    for(int j = 0; j<c; j++){
            cout<<j<<" ";
    }*/
    cout<<endl;

    for(int i = 0; i<l; i++){
        if(i<10){
            cout<<i<<"   ";
        }else{
            cout<<i<<"  ";
        }
        for(int j = 0; j<c; j++){
            cout<<campo[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

void exibe_gameover(char campo[][tmax], char cbomba[][tmax], int l, int c){
    for(int i = 0; i<l; i++){
        cout<<i<<" ";
        for(int j = 0; j<c; j++){
            if(cbomba[i][j]=='$' && campo[i][j]!='M'){
                campo[i][j]='*';
            }
            if(campo[i][j]=='M' && cbomba[i][j]!='$'){
                campo[i][j]='#';
            }
            cout<<campo[i][j]<<" ";
        }
        cout<<endl;
    }
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

void verifica_opcao(char op, char campo[][tmax], char cbomba[][tmax], int l, int c, int li, int co, int& cont){
    if(op=='D' || op=='d'){
        do{
            cout<<"digite as coordenadas: \n";
            cin>>li>>co;
        }while(li<0 || li>=l || co<0 || co>=c);

        if(cbomba[li][co]=='$'){
            cout<<"perdeu \n";
            exibe_gameover(campo,cbomba,l,c);
            exit(0);
        }

        descobre_quadrado(campo,cbomba,li,co,l,c);

    }

    if(op=='M' || op=='m'){
        do{
            cout<<"digite as coordenadas: \n";
            cin>>li>>co;
        }while(li<0 || li>=l || co<0 || co>=c);
            campo[li][co]='M';
            cont--;
    }

    if(op=='T' || op=='t'){
        do{
            cout<<"digite as coordenadas: \n";
            cin>>li>>co;
        }while(li<0 || li>=l || co<0 || co>=c);

        campo[li][co]='?';
    }

    if(op=='L' || op=='l'){
        do{
            cout<<"digite as coordenadas: \n";
            cin>>li>>co;
        }while(li<0 || li>=l || co<0 || co>=c);

        campo[li][co]='.';
        cont++;
    }

    if(op=='S' || op=='s'){
        exit(0);
    }
}

void jogo_iniciante(char campo[][tmax], char cbomba[][tmax], int l, int c){
    bool mina = true;
    char op;
    int li, co, cont = 10, contcampo = 0, cb = 10, contquad = ((l*c)-10);
    preenche_campo(campo,l,c);
    preenche_campo(cbomba,l,c);
    coloca_bomba(cbomba,l,c,cb);
    bomba_vizinhaca(cbomba,l,c);
    int tempo, inicio = time(0), fim = time(0);

    while(mina){
        tempo = fim - inicio;
        cout<<"Tempo: "<<tempo<<" segundo(s)"<<endl;

        contcampo = verifica_campo(campo,l,c);
        if(contcampo==contquad){
            cout<<"voce ganhou! \n";

            for(int i = 0; i<l; i++){
                cout<<i<<" ";
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
            }
            exit(0);
        }
        contcampo = 0;

        exibe_campo(campo,l,c);
        //exibe_campo(cbomba,l,c);

        op = menu_opcao(cont);

        verifica_opcao(op,campo,cbomba,l,c,li,co,cont);

        system("CLS");

        fim = time(0);
    }
}

void jogo_intermediario(char campo[][tmax], char cbomba[][tmax], int l, int c){
    bool mina = true;
    char op;
    int li, co, cont = 40, contcampo = 0, cb = 40, contquad = ((l*c)-40);
    preenche_campo(campo,l,c);
    preenche_campo(cbomba,l,c);
    coloca_bomba(cbomba,l,c,cb);
    bomba_vizinhaca(cbomba,l,c);
    int tempo, inicio = time(0), fim = time(0);

    while(mina){
        tempo = fim - inicio;
        cout<<"Tempo: "<<tempo<<" segundo(s)"<<endl;

        contcampo = verifica_campo(campo,l,c);
        if(contcampo==contquad){
            cout<<"voce ganhou! \n";

            for(int i = 0; i<l; i++){
                cout<<i<<" ";
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
            }
            exit(0);
        }
        contcampo = 0;

        exibe_campo(campo,l,c);
        //exibe_campo(cbomba,l,c);

        op = menu_opcao(cont);

        verifica_opcao(op,campo,cbomba,l,c,li,co,cont);

        system("CLS");

        fim = time(0);
    }
}

void jogo_personalizado(char campo[][tmax], char cbomba[][tmax]){
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
            cout<<"voce ganhou! \n";
            for(int i = 0; i<l; i++){
                cout<<i<<" ";
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
            }
            exit(0);
        }
        contcampo = 0;

        exibe_campo(campo,l,c);
        //exibe_campo(cbomba,l,c);

        op = menu_opcao(cont);

        verifica_opcao(op,campo,cbomba,l,c,li,co,cont);

        system("CLS");

        fim = time(0);
    }
}

