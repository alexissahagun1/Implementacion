package runtimetest;


import java.io.IOException;
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
public class Consumidor extends Thread {
    int id;
    Almacen almacen;
    boolean bandera;
    
    Consumidor(int id, Almacen almacen) {
        this.id = id;
        this.almacen = almacen;
        this.bandera = true;
    }
    
    @Override
    public void run() {
        System.out.println("Consumidor " + this.id);
        String producto;
        for(int i = 0; i<10; i++){
            producto = this.almacen.consumir();
            System.out.println("Consume (" + this.id + "): " + producto);

            //Inicia proceso
            Process process = null;

                try {
                    process = Runtime.getRuntime().exec("./b1 "+ producto);
                } catch (IOException ex) {
                    Logger.getLogger(Consumidor.class.getName()).log(Level.SEVERE, null, ex);
                }

            try {
                process.waitFor();
                //Termina proceso
            } catch (InterruptedException ex) {
                Logger.getLogger(RuntimeTestVentana.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
        
    }
    
    public void detener() {
        this.bandera = false;
    }
}
