package runtimetest;


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
public class Almacen {
    private String espacio;
    
    Almacen() {
        this.espacio = null;
    }
    
    synchronized String consumir() { 
        while (this.espacio == null) {
            try {
                wait();
            } catch (InterruptedException ex) {
                Logger.getLogger(Almacen.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
        
        String producto = this.espacio;
        this.espacio = null;
        notifyAll();
        return producto;
    }
    
    synchronized void producir(String producto) {
        while (this.espacio != null) {
            try {
                wait();
            } catch (InterruptedException ex) {
                Logger.getLogger(Almacen.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
        
        this.espacio = producto;
        notifyAll();
    }
}
