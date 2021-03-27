#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//-----------------------------variables globales:-------------------------------------
vector<vector<string>> mat;
vector<string> frags;
int k = 1;
string possIndChars = "-+*/^()=";
int typeCol=0;
int endStateCol=1;
vector<vector<string>> operadores = {
  {"-","+","*","/", "^", "(",")", "="},
  {"resta", "suma", "multiplicación", "división", "potencia", "paréntesis que abre", "paréntesis que cierra", "asignación"}
};
string sp="          ";

//-----------------------------funciones auxiliares:-------------------------------------
//Display de los tokens que fueron cargados
void dispFrags(){
    for (int i=0; i<frags.size(); i++) {
        cout<<frags[i]<<endl;
    }
}


//Determinar si el char dado es valido dentro del DFA y regresar su posición si es encontrado
long indOf(char c){
    vector<string> sigma = mat[0];
    for (int i=0; i<sigma.size(); i++) {
        if (sigma[i].find(c)!=string::npos) {
            return i;
        }
    }
    return -1;
}

//Verificar si el char dado es valido a partir de la función indOf
bool charIsValid(char c){
    return indOf(c)!=-1;
}

//Return del indice de fila del estado dado como parametro
int getStateInd(string state){
    long qInd;
    qInd=state.find('q');
    if (qInd!=string::npos){
        state=state.substr(qInd+1,state.size()-1);
        return stoi(state)+k;
    }
    return -1;
}

bool isPosIndChar(char c){
  //Intentar eliminar esta función al verifciar los estados en vez de los simbolos
    return possIndChars.find(c)!=string::npos;
}

//Verificar si el estado dado como parametro es final
bool stateIsFinal(string state){
    int ind=getStateInd(state);
    string endState=mat[ind][endStateCol];
    return endState=="f";
}

//return del tipo de estado que es el dado como parametro
string getStateType(string state){
    int ind=getStateInd(state);
    return mat[ind][typeCol];
}

//imprimir el operador dado como parametro junto con su tipo
void printOperador(char c) {
    string op;
    op.push_back(c);
    for(int i = 0; i < operadores[0].size(); i++) {
        if(operadores[0][i] == op) {
            cout<<op<<sp<<operadores[1][i]<<endl;
        }
    }
}

//Diaplay de matriz de tabla de estados
void disp(){
    for (int i=0; i<mat.size(); i++) {
        for (int j=0; j<mat[i].size(); j++) {
            if (j!=mat[i].size()-1) {
                cout<<mat[i][j]<<",";
            }else{
                cout<<mat[i][j]<<endl;
            }
        }
    }
}

//-----------------------------funciones principales:-------------------------------------

//Cargar tabla de estados en matriz desde un archivo
void loadMat(string fileName){
    fstream ifile(fileName);
    string row;
    vector<string> matRow;
    long nextComma;

    if (!ifile.fail()) {
        while (getline(ifile,row,'\n')) {
            row=row.substr(0,row.size()-1);
            matRow.clear();
            while (row.size()>0) {
                nextComma = row.find(',');
                if (nextComma!=string::npos) {
                    matRow.push_back(row.substr(0,nextComma));
                    row.erase(0,nextComma+1);
                }else{
                    matRow.push_back(row);
                    row.clear();
                }
            }
            mat.push_back(matRow);
        }
    }else{
        cout<<"Archivo "<<fileName<<" no encontrado"<<endl;
    }
}

//Creación de vector de tokens dados como input
void loadFragments(string fileName){
    //vars
    char c;
    string row;
    fstream ifile(fileName);
    string frag;
    bool onWord;
    
    if (!ifile.fail()) {
        while (getline(ifile,row,'\n')) {
//            frag.clear();
            for (int i=0; i<row.size(); i++) {
                c=row[i];
                if (c!=' ') {
                    if (c=='/' and i<row.size() and row[i+1]=='/') {
                        frag=row.substr(i,row.size());
                        frags.push_back(frag);
                        frag.clear();
                        break;
                    }else if(i==row.size()-1){
                        frag.push_back(c);
                        frags.push_back(frag);
                        frag.clear();
                    }else{
                        frag.push_back(c);
                    }
                }else if(frag.size()>0){
                    frags.push_back(frag);
                    frag.clear();
                }
            }
        }
    }else{
        cout<<"Archivo "<<fileName<<" no encontrado"<<endl;
    }
}

void processFrags(){
    //vars
    string frag;
    string word;
    char c;
    long cInd;
    string currState = "q0";
    string nextState;
    vector<string> currRow=mat[getStateInd(currState)];
    vector<string> nextRow;
    string type;
    string cat;
    
    bool endOfWord;
    
    //por cada fragmento
    for (int i=0; i<frags.size(); i++) {
        frag=frags[i];
        //por cada caracter en un fragmento
        for (int j=0; j<frag.size(); j++) {
            c = frag[j];
            word.push_back(c);
            cInd = indOf(c);
            endOfWord = (j == frag.size()-1);

            //si c existe
            if (currState == "p"){
              if (isPosIndChar(c)) {
                                            //si palabra no está vacía
                      word.pop_back();
                          //imprimimos resultado de la palabra previa
                        cout<<word<<sp<<type<<endl;
                        printOperador(c); //imprimir operador y tipo
                        //eliminamos la palabra y reseteamos estado
                        word.clear();
                        currState = "q0";
                        endOfWord = false;
                }
            }

            else if (charIsValid(c)) {
              currRow = mat[getStateInd(currState)];
              currState = currRow[cInd];
                //c sí existe
                if (isPosIndChar(c)) {
                    //es operador o parentesis

                  if(currState == "q11" or currState == "q14"){ // signo '-'
                    printOperador(c);
                    currState = "q0";
                    endOfWord = false;
                    word.clear();
                  }
                  else if(currState == "q9" or currState == "q5"){
                    continue;
                  }

                  else if (currState != "q12" and currState != "q13"){
                    if(word.size()>1){
                          //quitar ultimo caracter
                      word.pop_back();
                          //imprimimos resultado de la palabra previa
                      cout<<word<<sp<<type<<endl;
                    }
                    word.clear();
                    currState = "q0";
                    endOfWord = false;
                    j--;
                  }

                  else if(currState == "q13" or currState == "q12"){ // signo '/'
                    if(endOfWord == false){
                      char nextC;
                      string nextCurrState;
                      long nextCInd;
                      if(charIsValid(frag[j + 1])){
                        nextC = frag[j + 1];
                        nextCInd = indOf(nextC);
                        nextRow = mat[getStateInd(currState)];
                        nextCurrState = nextRow[nextCInd];


                        if(nextCurrState == "q15"){
                          word=word+frag.substr(j+1,frag.size());
                          endOfWord = true;
                          type=getStateType(nextCurrState);
                        }
                
                        else if(nextCurrState == "q3"){
                          continue;
                        }

                        else{
                          printOperador(c);
                          currState = "q0";
                          endOfWord = false;
                          word.clear();
                        }
                      }

                      else{
                        printOperador(c);
                        currState = "q0";
                        endOfWord = false;
                        word.clear();
                      }

                    }
                    else{
                      printOperador(c);
                        currState = "q0";
                        endOfWord = false;
                        word.clear();
                    }
                  }

                  

                }else{
                    //no es operador o paréntesis
                    //si nos manda al pozo
                    if (currState!="p") {
                        //si el estado es final
                        if (stateIsFinal(currState)) {
                            //el estado es final
                            type=getStateType(currState);
                        }else{
                            //el estado no es final
                            type="error";
                        }
                    }else{
                        //si nos manda al pozo
                        type="error";
                        currState = "p";
                        //endOfWord=true;
                    }
                    
                    
                }
            }else{
                //c no existe
                //invCharFound=true;
                type="error";
                currState = "p";
                //endOfWord=true;
                //word=word+frag.substr(j+1,frag.size()-1);
            }
            
            //cada que termine una palabra
            if(endOfWord){
                cout<<word<<sp<<type<<endl;
                word.clear();
                currState="q0";
                j=frag.size();
            }
            //siguiente caracter>>
        }
        
    }
}

void lexerAritmetico(string archivo){
    loadMat("tablaEstados.csv");
//    disp();
    loadFragments(archivo);
//    dispFrags();
    processFrags();
}

int main(int argc, const char * argv[]) {
    lexerAritmetico("lex.txt");
    return 0;
}
