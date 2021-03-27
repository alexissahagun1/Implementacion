//Creado por:
//Alexis Sahagún
//Jesús Palomino
//Jaime López-Hidalgo

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//-----------------------------variables globales:-------------------------------------
vector<vector<string>> mat;
vector<string> frags;
int k = 1;
int typeCol=0;
int endStateCol=1;
vector<vector<string>> individuales = {
  {"-","+","*","/", "^", "(",")", "="},
  {"resta", "suma", "multiplicación", "división", "potencia", "paréntesis que abre", "paréntesis que cierra", "asignación"}
};
string sp="          ";

//-----------------------------funciones auxiliares:-------------------------------------
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

long indOf(char c){
    vector<string> sigma=mat[0];
    for (int i=0; i<sigma.size(); i++) {
        if (sigma[i].find(c)!=string::npos) {
            return i;
        }
    }
    return -1;
}

void dispFrags(){
    for (int i=0; i<frags.size(); i++) {
        cout<<frags[i]<<endl;
    }
}

bool isPosIndChar(char c){
    string aux;
    aux.push_back(c);
    for(int i = 0; i < individuales[0].size(); i++) {
        if(individuales[0][i] == aux) {
            return true;
        }
    }
    return false;
}

int getStateInd(string state){
    long qInd;
    if (state!="p") {
        qInd=state.find('q');
        state=state.substr(qInd+1,state.size()-1);
        return stoi(state)+k;
    }
    return mat.size()-1;
}

bool stateIsFinal(string state){
    int ind=getStateInd(state);
    string endState=mat[ind][endStateCol];
    return endState=="f";
}

string getStateType(string state, char c){
    string type=mat[getStateInd(state)][typeCol];
    if (type=="operador" or type=="especial") {
        string aux;
        aux.push_back(c);
        for (int i=0; i<individuales[0].size(); i++) {
            if (individuales[0][i]==aux) {
                return individuales[1][i];
            }
        }
    }
    return type;
}



bool charIsValid(char c){
    return indOf(c)!=-1;
}

//-----------------------------funciones principales:-------------------------------------
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


void loadFragments(string fileName){
    //variables
    char c;
    string row;
    fstream ifile(fileName);
    string frag;
    bool onFrag;
    bool fragHasEnded;
    
    if (!ifile.fail()) {
        while (getline(ifile,row,'\n')) {//para cada renglón en el archivo
            onFrag=false;
            frag.clear();
            for (int i=0; i<row.size(); i++) {//para cada caracter en el renglón
                c=row[i];
                fragHasEnded=false;
                
                if (c!=' ') {//checar si c no es espacio
                    //c no es espacio
                    
                    fragHasEnded=(i==row.size()-1);//si estamos en el ultimo caracter del renglón
                    onFrag=true; //(por que ya estamos en un fragmento)
                    
                    //checar casos especiales:
                    if (c!='-' and isPosIndChar(c)) {//si c no es espacio pero es operador o paréntesis
                        //es un operador (no incluye -) o caracter especial
                        
                        if (frag.size()>0) {//si frag ya contenía algo
                            frags.push_back(frag);
                            frag.clear();
                        }
                        
                        if (c=='/' and i+1<row.size() and row[i+1]=='/') {//checar si es comentario
                            frags.push_back(row.substr(i,row.size())); //almacenar resto del renglón
                            break; //brincar al siguiente renglón
                        }
                        fragHasEnded=true; //para almacenar operador solito al final del for
                    }
                    frag.push_back(c);//metemos caracter al fragmento
                }else{
                    //c sí es espacio
                    
                    if (onFrag) {//checar si estábamos en un fragmento
                        //sí estábamos en un fragmento
                        fragHasEnded=true;
                    }
                }
                
                //al final de cada iteración:
                if (fragHasEnded) {//checar si el fragmento ya acabó
                    //ya acabó el fragmento
                    
                    //se almacena fragmento y se borra
                    frags.push_back(frag);
                    frag.clear();
                    onFrag=false;
                }
            }
        }
    }else{
        cout<<"Archivo "<<fileName<<" no encontrado"<<endl;
    }
}

void processFrags(){
    //variables
    string frag;
    string word;
    char c;
    long cInd;
    string currState = "q0";
    string nextState;
    vector<string> currRow;
    vector<string> nextRow;
    string type;
    bool endOfWord;
    bool containsInvalid;
    
    for (int i=0; i<frags.size(); i++) {//por cada fragmento
        frag=frags[i]; //fragmento actual
        word.clear(); //vaciar palabra
        containsInvalid=false;
        for (int j=0; j<frag.size(); j++) {//por cada caracter en un fragmento
            c=frag[j]; //caracter actual del fragmento
            endOfWord=(j==frag.size()-1); //checamos si estamos en el último caracter
            
            //-----------------------casos especiales--------------------------
            if (c=='-' and word.size()>0){//checamos que si c es '-', que exista algo antes
                //sí existe algo antes
                
                if (type=="variable" or type=="error") {//checamos que lo anterior sea variable o error
                    
                    //se imprime lo anterior y se separa la resta:
                    cout<<word<<sp<<type<<endl;
                    word.clear();
                    type="resta";
                    endOfWord=true;
                }else if(j+1<frag.size() and !isdigit(frag[j+1])){//si no, se checa si lo que sígue no sea dígito
                    
                    //se imprime lo anterior (como error) y se separa la resta:
                    cout<<word<<sp<<"error"<<endl;
                    word.clear();
                    type="resta";
                    endOfWord=true;
                }
            }else if((c=='/' and j+1<frag.size() and frag[j+1]=='/')){//checamos si el fragmento es comentario
                //fragmento sí es comentario
                type="comentario";
                cout<<frag<<sp<<type<<endl; //imprimir el comentario (todo el fragmento)
                break; //brincar al siguiente fragmento
            //------------------------------------------------------------------
            }else if(charIsValid(c) and !containsInvalid){
                //cualquier otro caracter válido y la palabra no contiene ningún inválido
                
                cInd=indOf(c);//obtenemos índice de c en la tabla
                currRow=mat[getStateInd(currState)]; //obtenemos renglón actual
                nextState=currRow[cInd]; //obtenemos el estado al que nos llevaría c
                nextRow=mat[getStateInd(nextState)]; //obtenemos el renglón al que nos llevaría el siguiente estado
                currRow=nextRow; //avanzamos renglón
                currState=nextState; //avanzamos estado
                if (currState!="p") {
                    //c no nos lleva al pozo
                    if (endOfWord and !stateIsFinal(currState)) {//checar si terminó en un estado no final
                        //terminó en un estado no final
                        type="error";
                    }else{
                        type=getStateType(currState, c);
                    }
                }else{
                    //c nos lleva al pozo
                    type="error";
                }
            }else{
                //es un caracter inválido
                type="error";
                containsInvalid=true;
            }
            //siempre:
            word.push_back(c);//metemos c en la palabra
            
            //cada que termine una palabra:
            if(endOfWord){
                //imprimir y resetear
                cout<<word<<sp<<type<<endl;
                word.clear();
                currState="q0";
                containsInvalid=false;
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
