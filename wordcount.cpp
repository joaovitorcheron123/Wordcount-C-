/*Joao Vitor Cheron
178321*/

#include<iostream>
#include<list>
#include<fstream>
#include<string.h>

using namespace std;

struct palavra{
    string p;
    int n;
};

//funcoes para ordenacao
bool alfab(palavra& v1, palavra& v2){
    return v1.p < v2.p;
}
bool decr(palavra& v1, palavra& v2){
    return v1.n > v2.n;
}
bool cresc(palavra& v1, palavra& v2){
    return v1.n < v2.n;
}

int main(int argc, char *argv[]){    
    list<palavra>lista;
    ifstream entrada;
    ofstream saida;
    char ordem = 'd'; //char para comando de ordenacao
    char formato = 'c'; //char para comando de formato
    string word;
    string nEntrada = argv[argc-2];//parametros para entrada
    string nSaida = argv[argc-1]; //parametros para saida

    entrada.open(nEntrada);
    if(!entrada){ //verifica se o arquivo existe
        cout << "[ERRO] O arquivo " << nEntrada << " nao foi encontrado!" << endl;
        return 1;
    }

    while(entrada >> word){
        for(int i = 0; i<word.length(); i++) { //percorre a palavra e converte caracteres para lowercase
            word[i] = tolower(word[i]);
        }
        if(lista.empty()) 
            lista.push_back({word, 1}); //manda para o final da lista
        else {
            bool igual = false;
            for(auto it = lista.begin(); it != lista.end(); ++it) {
                if(it->p == word){
                    it->n++;
                    igual = true;
                    break;
                }
            }
            if(igual == false)
                lista.push_back({word, 1});
        }
    }
    entrada.close();

    if(argc < 3){ //comando help
        if(!strcmp(argv[1], "--help")) {
            cout << "\nUso: wordcount [OPÇÕES] [ENTRADA] [SAIDA]\n\n"
            "ENTRADA: Nome e formato do arquivo a ser inserido na entrada.\n"
            "SAIDA: Nome e formato do arquivo de saída.\n\n"
            "OPÇÕES DO PROGRAMA: \n"
            "-c: Ordena a saída em ordem crescente da contagem de ocorrências.\n"
            "-d: Ordena a saída em ordem decrescente da contagem de ocorrências.\n"
            "-p: Ordena a saída em ordem alfabética.\n"
            "--help: Exibe na tela um texto de ajuda sobre uso do programa.\n"
            "-html: Formato de saída = Gera um arquivo HTML contendo uma tabela com os dados.\n"
            "-csv: Formato de saída = Gera um arquivo CSV (formato de saída default).\n";
            return 1;
        }
        cout << "[ERRO] Comando invalido!\nUse o comando --help para ajuda.\n";
        return 1;
    }

    if(argc > 3){ //parametros para os comandos
        for(int i=1; i < argc-2; i++){
            string arg = argv[i];
            if(arg == "-p")
                ordem = 'p';
            else if(arg == "-c")
                ordem = 'c';
            else if(arg == "-d")
                ordem = 'd';
            else if(arg == "-html")
                formato = 'h';
            else if(arg == "-csv")
                formato = 'c';
            else{
                cout << "[ERRO] Comando invalido!\nUse o comando --help para ajuda.\n";
                return 1;
            }
        }
    }

    if(ordem == 'p') //ordenacao
        lista.sort(alfab);
    else if(ordem == 'c'){
        lista.sort(alfab);
        lista.sort(cresc);
    }else if(ordem == 'd' ){
        lista.sort(alfab);
        lista.sort(decr);
    }

    if(formato == 'c'){ //csv
        saida.open(nSaida);
        saida << "Palavra;Ocorrencias\n";
        for(auto s: lista) //percorre a lista e organiza as colunas
            saida << s.p << ";" << s.n << "\n"; //
        saida.close();
        return 0;
    }

    if(formato == 'h'){ //html
        saida.open(nSaida);
        saida << "<!DOCTYPE html>\n<html>\n<head>\n";
        saida << "<meta charset='utf-8'>\n";
        saida << "<title>Wordcount</title>\n";
        saida << "<style>\ntable, tr, td, th{border: 1px solid black;background-color: #e6e6ff;font-family:courier,arial,helvetica;}\n</style>\n";
        saida << "</head>\n<body>\n<table>\n";
        saida << "<tr>\n<th>Palavra</th>\n<th>Ocorrencias</th>\n</tr>\n";
        for(auto s: lista) //percorre a lista e organiza as colunas
            saida << "<tr>\n<td>" << s.p << "</td>\n<td>" << s.n << "</td>\n</tr>\n";
        saida << "</table>\n</body>\n</html>";
        saida.close();
        return 0;
    }
}