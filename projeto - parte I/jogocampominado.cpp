#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std;

int const tmax = 40;

void menu(int opm, char campo[][tmax], char cbomba[][tmax], int l, int c);
void menu_jogo(int op, char campo[][tmax], char cbomba[][tmax], int l, int c);
void preenche_campo(char campo[][tmax], int l, int c);
void coloca_bomba(char cbomba[][tmax], int l, int c);
void bomba_vizinhaca(char cbomba[][tmax], int l, int c);
void exibe_campo(char campo[][tmax], int l, int c);
//void descobre_quadrado(char campo[][tmax], char cbomba[][tmax], int l, int c);
void jogo_iniciante(char campo[][tmax], char cbomba[][tmax], int l, int c);


int main(){
    char campo[tmax][tmax], cbomba[tmax][tmax];

    int l, c, opm;

    srand(time(NULL));

    menu(opm,campo,cbomba,l,c);

    return 0;
}

void menu(int opm, char campo[][tmax], char cbomba[][tmax], int l, int c){
    do{
        cout<<"1 - Novo Jogo \n";
        cout<<"2 - Melhores tempos \n";
        cout<<"3 - Sair \n";
        cin>>opm;
    }while(opm<=0 || opm>3);

    if(opm==1){
        menu_jogo(0,campo,cbomba,l,c);
    }
    if(opm==2){
        //melhores_tempos();
    }
    if(opm==3){
        exit(0);
    }
}

void menu_jogo(int op, char campo[][tmax], char cbomba[][tmax], int l, int c){
    do{
        cout<<"1 - Jogo Iniciante \n";
        cout<<"2 - Jogo Intermediario \n";
        cout<<"3 - Jogo Personalizado \n";
        cout<<"4 - Voltar \n";
        cin>>op;
    }while(op<1 || op >4);

    if(op==1){
        jogo_iniciante(campo,cbomba,8,8);
    }
    if(op==2){
        //jogo_intermediario();
    }
    if(op==3){
        //jogopersonalizado();
    }
    if(op==4){
        menu(0,campo,cbomba,l,c);
    }
}

void preenche_campo(char campo[][tmax], int l, int c){
    for(int i = 0; i<l; i++){
        for(int j = 0; j<c; j++){
            campo[i][j]='.';
        }
    }
}

void coloca_bomba(char cbomba[][tmax], int l, int c){
    int cont = 0;
    do{
        l = rand()%8;
        c = rand()%8;

        if(cbomba[l][c]=='.'){
            cbomba[l][c]='$';
            cont++;
        }
    }while(cont<10);
}

void bomba_vizinhaca(char cbomba[][tmax], int l, int c){
    int cb = 0;
    for(int i = 0; i<8; i++){
        for(int j = 0; j<8;j++){
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

/*void descobre_quadrado(char campo[][tmax], char cbomba[][tmax], int li, int co){

        if(cbomba[li][co]=='0'){
            campo[li][co]='_';
            //cbomba[li][co]='_';
            if((li>0 && li <7) && (co>0 && co<7)){
            descobre_quadrado(campo,cbomba,li,co+1);
            descobre_quadrado(campo,cbomba,li+1,co+1);
            descobre_quadrado(campo,cbomba,li+1,co);
            descobre_quadrado(campo,cbomba,li,co-1);
            descobre_quadrado(campo,cbomba,li-1,co-1);
            descobre_quadrado(campo,cbomba,li-1,co);
            descobre_quadrado(campo,cbomba,li-1,co+1);
            descobre_quadrado(campo,cbomba,li+1,co-1);
            }
        }if(cbomba[li][co]!='$'){
            campo[li][co]=cbomba[li][co];
        }
}*/

void exibe_campo(char campo[][tmax], int l, int c){
    for(int i = 0; i<l; i++){
        cout<<i<<"  ";
        for(int j = 0; j<c; j++){
            cout<<campo[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

void jogo_iniciante(char campo[][tmax], char cbomba[][tmax], int l, int c){
    bool mina = true;
    char op;
    int li, co, cont = 10;
    preenche_campo(campo,l,c);
    preenche_campo(cbomba,l,c);
    coloca_bomba(cbomba,l,c);
    bomba_vizinhaca(cbomba,l,c);

    while(mina){
        exibe_campo(campo,l,c);
        //exibe_campo(cbomba,l,c);


            cout<<"D - Descobrir quadrado \n";
            cout<<"M - Marcar mina \n";
            cout<<"T - Talvez mina \n";
            cout<<"L - Limpar marcação \n";
            cout<<"S - Sair \n";

            cout<<"Minas a marcar: "<<cont;
            cout<<endl;
            cin>>op;


        if(op=='D' || op=='d'){
            cout<<"digite as coordenadas: \n";
            cin>>li>>co;

            if(cbomba[li][co]=='$'){
                cout<<"perdeu \n";
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
                exit(0);
            }
            if(cbomba[li][co]!='0' && cbomba[li][co]!='$'){
                campo[li][co]=cbomba[li][co];
            }else{
                campo[li][co] ='_';
                //cbomba[li][co] = '_';
            }
            //descobre_quadrado(campo,cbomba,li,co);
        }

        if(op=='M' || op=='m'){
            cout<<"digite as coordenadas: \n";
            cin>>li>>co;
            campo[li][co]='M';
            cont--;
        }
        if(op=='T' || op=='t'){
            cout<<"digite as coordenadas: \n";
            cin>>li>>co;
            campo[li][co]='?';
        }
        if(op=='L' || op=='l'){
            cout<<"digite as coordenadas: \n";
            cin>>li>>co;
            campo[li][co]='.';
        }
        if(op=='S' || op=='s'){
            exit(0);
        }
    }
}

