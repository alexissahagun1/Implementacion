//Creado por:
//Alexis Sahagún
//Jesús Palomino
//Jaime López-Hidalgo

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//-----------------------------variables globales:-------------------------------------
vector<vector<string>> table;
vector<string> frags;
vector<string> categories;

int k = 1;
int typeCol=0;

//-----------------------------funciones auxiliares:-------------------------------------

//Complejidad - O(n^2)
void displayTable(){
    for (int i=0; i<table.size(); i++) {
        for (int j=0; j<table[i].size(); j++) {
            if (j!=table[i].size()-1) {
                cout<<table[i][j]<<",";
            }else{
                cout<<table[i][j]<<endl;
            }
        }
    }
}

//Complejidad - O(n)
long indOf(char c){
    vector<string> sigma=table[0];
    for (int i=0; i<sigma.size(); i++) {
        if (sigma[i].find(c)!=string::npos) {
            return i;
        }
    }
    return -1;
}

//Complejidad - O(n)
void displayFragsWithCategories(){
    for (int i=0; i<frags.size(); i++) {
        cout<<frags[i]<<"   "<<categories[i]<<endl;
    }
}


//Complejidad - O(n)
void fragsHtml(string fileName){
string inicio, fin;

inicio = "<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><title>Document</title><style>:root{--variable:  #3cb44b;--error:  #e6194B;--simbolo:  #469990;--operador:  #911eb4;--numero:  #ffe119;--especial:  #9A6324;--reservada:  #f032e6;--comentario:  #808000;--logico:  #4363d8;}span {white-space: pre-wrap;}.variable{color: var(--variable);}.error{color: var(--error);}.simbolo{color: var(--simbolo);}.operador{color: var(--operador);}.numero{color: var(--numero);}.especial{color: var(--especial);}.reservada{color: var(--reservada);}.comentario{color: var(--comentario);}.logico{color: var(--logico);}body {background-color: rgb(27, 27, 29);}</style></head><body>";
fin = "</body></html>";

for (int i=0; i<4; i++) {
    fileName.pop_back();
}
ofstream htmlFile(fileName+".html");

htmlFile << inicio;
for (int i=0; i<frags.size(); i++) {
        htmlFile<<"<span class=\""<<categories[i]<<"\">"<<frags[i] << "</span>";
    }
htmlFile << fin;
htmlFile.close();

}

//Complejidad O(n)
long getStateInd(string state){
    long qInd;
    if (state!="p") {
        qInd=state.find('q');
        state=state.substr(qInd+1,state.size()-1);
        return stoi(state)+k;
    }
    return table.size()-1;
}

//Complejidad O(1)
string getCurrentCategory(string state){
    return table[getStateInd(state)][typeCol];
}


//Complejidad O(1)
bool charIsValid(char c){
    return indOf(c)!=-1;
}

//Complejidad O(n)
string advanceState(string currentState, char c){
    long cInd;
    string nextState;
    vector<string> currRow;
    
    currRow=table[getStateInd(currentState)]; //obtenemos renglón actual
    if(!charIsValid(c)){
        nextState="p";
    }else{
        cInd=indOf(c);//obtenemos índice de c en la tabla
        nextState=currRow[cInd]; //obtenemos el estado al que nos llevaría c
    }
    
    return nextState;
}


//Complejidad O(n)
string getFragCategory(string frag){
    char c;
    string category;
    string currentState="q0";
    
    for (int i=0; i<frag.size(); i++) {
        c=frag[i];
        currentState=advanceState(currentState, c);
        category=getCurrentCategory(currentState);
    }
    return category;
}


//Complejidad O(1)
bool mustBeIndividual(char c){
    string alwaysIndividualChars = "=+*/^()'; \t\n";
    return (alwaysIndividualChars.find(c) != string::npos);
}


//Complejidad - O(n)
void parseError(string frag){
    //Separar el error por signos de menos ('-'):
    
    char c;
    string word;
    string currentState="q0";
    string wordCategory;
    bool fragEnded;
    
    for (int i=0; i<frag.size(); i++) {
        c=frag[i];
        fragEnded = (i==frag.size()-1);
        if (c=='-') {//checar si es '-'
            if(frag.size()){//si la palabra contiene algo
                frags.push_back(word); //almacenar la palabra actual
                wordCategory=getFragCategory(word); //obtener su categoría final
                categories.push_back(wordCategory); //almacenar su categoría final
                word.clear();
            }
            fragEnded=true;
        }
        word.push_back(c);
        
        if(fragEnded){
            frags.push_back(word); //almacenar la palabra actual
            wordCategory=getFragCategory(word); //obtener su categoría final
            categories.push_back(wordCategory); //almacenar su categoría final
            word.clear();
        }
    }
}

//Complejidad - O(n)
void loadFragAndCat(string frag, string currentCategory){
    if (frag.size()) {//si frag tiene caracteres almacenados
        if(currentCategory=="error"){//checar si frag terminó en error
            parseError(frag);
        }else{
            frags.push_back(frag);
            categories.push_back(currentCategory);
        }
    }
}

//Complejidad - O(n)
long distanceToNext(string file, int i, string delims){
    string fileCopy = file.substr(i,file.size()-i);
    long nextDelim = fileCopy.find_first_of(delims);
    if (nextDelim==-1) {
        nextDelim=fileCopy.size();
    }
    return nextDelim;
}

//-----------------------------funciones principales:-------------------------------------

//Complejidad - O(n)
void processFile(string fileName){
    fstream ifile("lexerContent/srcTxtFiles/"+fileName); //abrir archivo de entrada
    
    if(!ifile.fail()){
        char c;
        string file;
        string frag;
        string currentState="q0";
        string currentCategory;
        bool fragEnded;
        
        //Convertir el archivo en un string:
        while (ifile >> noskipws >> c) {
            file+=c;
        }
        
        for (int i=0; i<file.size(); i++) {//por cada caracter en 'file'
            c=file[i];
            fragEnded=(i==file.size()-1);
            if(mustBeIndividual(c)){//checar si es caracter individual
                fragEnded=true;
            }else{
                //todos los demás caracteres (flujo normal):
                currentState=advanceState(currentState, c);
                currentCategory=getCurrentCategory(currentState);
                frag.push_back(c);
            }
        
            if(fragEnded){
                loadFragAndCat(frag, currentCategory);
                frag.clear();
                if(mustBeIndividual(c)){
                    frag.push_back(c);
                    currentState="q0";
                    currentCategory=getCurrentCategory(advanceState(currentState, c)); //obtener la categoría del caracter actual (operador, especial, o comentario)
                    if (c==' ' or c=='\n' or c=='\t') { //checar si el caracter es delimitador
                        if(c==' '){
                            frag = "&nbsp;";
                        }
                        else if(c=='\n'){
                            frag = "<br>";
                        }
                        else{
                            frag = "&emsp;";
                        }
                        currentCategory.clear(); //tienen categoría vacía
                    }else if (c==';' or c=='\'') { //checar si c es ; o '
                        long dist=distanceToNext(file, i, "; \t\n");
                        if(c==';'){
                            dist=distanceToNext(file, i, "\n");
                        }
                        frag=file.substr(i,dist);
                        i+=(dist-1);
                    }
                    loadFragAndCat(frag, currentCategory);
                    frag.clear();
                }
                fragEnded=false;
            }
        }
        ifile.close(); //cerrar archivo de entrada
        fragsHtml(fileName);
    }else{
        cout<<"Archivo '"<<fileName<<"' no encontrado"<<endl;
        //extra:
        ofstream ofile;
        ofile.open("errores.txt");
        ofile<<"Archivo '"<<fileName<<"' no encontrado"<<endl;
    }
}


//Complejidad - O(n*m)
void loadTable(string tablefileName, string txtFileName){
    fstream ifile("lexerContent/"+tablefileName);
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
            table.push_back(matRow);
        }
        ifile.close(); //cerrar archivo de entrada
        processFile(txtFileName);
    }else{
        cout<<"Archivo '"<<tablefileName<<"' no encontrado"<<endl;
        //extra:
        ofstream ofile;
        ofile.open("errores.txt");
        ofile<<"Archivo '"<<tablefileName<<"' no encontrado"<<endl;
    }
}

void lexerAritmetico(string txtFileName){
    loadTable("tablaEstados.csv", txtFileName);
}

int main(int argc, const char * argv[]) {
    lexerAritmetico(argv[1]);
    return 0;
}
