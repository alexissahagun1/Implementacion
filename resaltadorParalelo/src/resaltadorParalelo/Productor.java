package runtimetest;


import java.io.File;
import java.io.IOException;
import java.util.Enumeration;
import java.util.List;
import java.util.Random;
import java.util.Vector;
import java.util.logging.Level;
import java.util.logging.Logger;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author alejandro.degante
 */
public class Productor extends Thread{
    int id;
    Almacen almacen;
    boolean bandera;
    
    Productor(int id, Almacen almacen) {
        this.id = id;
        this.almacen = almacen;
        this.bandera = true;
    }
    
    List<String> getArchivos() {
     String archivo;
     List<String> ArchivosLista = new Vector<String>();
     try {
        
            String fileName = "lexerContent/srcTxtFiles";
            File folder = new File(fileName);
            try{ 
            File[] listOfFiles = folder.listFiles();
                for (int i = 0; i < listOfFiles.length; i++) {
                    if (listOfFiles[i].isFile()) {
                        archivo = listOfFiles[i].getName();
                        if (!archivo.equals(".DS_Store")){
//                            System.out.println("File " + archivo);
                            ArchivosLista.add(archivo);
                        }
                    } else if (listOfFiles[i].isDirectory()) {
                        System.out.println("Directory " + listOfFiles[i].getName());
                    }
                }
            }catch(NullPointerException exception){
               System.out.println("File " + fileName + " not found");
            }
        }catch (NumberFormatException ex) {
            Logger.getLogger(RuntimeTestVentana.class.getName()).log(Level.SEVERE, null, ex);
        }
     return ArchivosLista;
    }
    
    
    @Override
    public void run() {
        List<String> ArchivosLista = getArchivos();
        System.out.println("Productor " + this.id);

        String archivo;
        
        for (int i=0 ; i<ArchivosLista.size() ; i++) {
            archivo = ArchivosLista.get(i);
            this.almacen.producir(archivo);
            System.out.println("Produce (" + this.id + "): " + archivo);
        }
    }
    
    public void detener() {
        this.bandera = false;
    }
}
