#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <string>
#include <map>
#include <iterator>

using namespace std;

typedef struct Notas{
        string cod_dis;
        int cod_curs;
        int nota;
        int carga_hor;
        int ano_sem;
}notas;

typedef struct Curso{
        int chtotal=0;
        int nota=0;
        int cod;
}curso;

ifstream abrirArquivo(){
    ifstream arquivo("datasets\\notas.csv");
    if(!arquivo.is_open()) cout << "Nao foi possivel abrir o arquivo\n";
     return arquivo;
}

notas read(char* linha){///lê cada linha e separa cada elemento dela
    notas aluno;

    aluno.cod_dis=strtok(linha,",");
    aluno.cod_curs=atoi(strtok(NULL,","));
    aluno.nota=atoi(strtok(NULL,","));
    aluno.carga_hor=atoi(strtok(NULL,","));
    aluno.ano_sem=atoi(strtok(NULL,","));

    return aluno;
}

int main(){

    string line;
    vector<notas>aluno[10001];
    char linha[1000];
    int matricula;
    int aux=0;
    int ch=0;
    int cr=0;
    int cont=0;
    map<int,curso> notacurso;

    ifstream arq = abrirArquivo();

    getline(arq,line); ///Ignora a primeira linha do arquivo (nome das colunas)


    while(arq >> matricula)
    {
        arq.get(linha,150,'\n');
        aluno[matricula].push_back(read(linha));
        if(aux==matricula)
        {
            cr+=aluno[matricula].back().nota*aluno[matricula].back().carga_hor;
            ch+=aluno[matricula].back().carga_hor;
            notacurso[aluno[matricula].back().cod_curs].chtotal+=ch;
            notacurso[aluno[matricula].back().cod_curs].nota+=cr;
            notacurso[aluno[matricula].back().cod_curs].cod=aluno[matricula].back().cod_curs;
        }
        else
        {
            if(cont>0) cout << ""<<aux<<" - "<<cr/ch<<endl;
            cr=aluno[matricula].back().nota*aluno[matricula].back().carga_hor;
            ch=aluno[matricula].back().carga_hor;
            notacurso[aluno[matricula].back().cod_curs].chtotal+=ch;
            notacurso[aluno[matricula].back().cod_curs].nota+=cr;
            notacurso[aluno[matricula].back().cod_curs].cod=aluno[matricula].back().cod_curs;
            cont++;
            aux=matricula;
        }
    }
    cout<<aux<<" - "<<cr/ch<<"\n"<<endl;

    map<int,curso>::iterator itr;

    for(itr = notacurso.begin();itr!=notacurso.end(); ++itr){
        cout << itr->second.cod <<" - "<< itr->second.nota/itr->second.chtotal << endl;
    }
}
