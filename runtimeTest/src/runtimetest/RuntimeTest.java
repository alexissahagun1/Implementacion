/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package runtimetest;

import java.io.File;
import java.io.IOException;
import java.util.List;
import java.util.Vector;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author jaimelopez
 */
public class RuntimeTest {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws InterruptedException {
        List<String> ArchivosLista = new Vector<String>();
        
        String fileName = "lexerContent/srcTxtFiles";
        File folder = new File(fileName);
          
        File[] listOfFiles = folder.listFiles();
//        for (int i = 0; i < listOfFiles.length; i++) {
//            if (listOfFiles[i].isFile()) {
//                System.out.println("File " + listOfFiles[i].getName());
//            } else if (listOfFiles[i].isDirectory()) {
//                System.out.println("Directory " + listOfFiles[i].getName());
//            }
//        }
        try {
            //Inicia compilación
            Process build = Runtime.getRuntime().exec("g++ -std=c++11 -o b1 lexerContent/main.cpp");
            build.waitFor();
            //Termina compilación

            //Inicia proceso
            Process process = Runtime.getRuntime().exec("./b1 "+listOfFiles[0].getName());
            process.waitFor();
            //Termina proceso

            Process delete = Runtime.getRuntime().exec("rm b1"); //se borra el .exe		
        } catch (IOException e) {
            e.printStackTrace();
        }
   } 
}