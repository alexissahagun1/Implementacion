/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package javaapplication1;


/**
 *
 * @author jaimelopez
 */
public class MiHilo extends Thread {
    private int id;
    private boolean bandera;
    private long r1, r2;
    private long resultado;
    
    MiHilo(int id, boolean bandera, long r1, long r2) {
        this.id = id;
        this.bandera = bandera;
        this.r1 = r1;
        this.r2 = r2;
        this.resultado = 0;
    }
    
    @Override
    public void run() {
        for (long i = this.r1; i <= this.r2; i++) {
            if(isPrime(i)){
                this.resultado+=i;
            }
        }
    }
    
    public long getResultado() {
        return this.resultado;
    }
    
    public void detener() {
        this.bandera = false;
    }
    
    private boolean isPrime(long n){
        boolean noFactorFound=true;
        if(n>=2){
            for (int i=2; noFactorFound && i*i<=n; i++) {
                if(n%i==0){
                    noFactorFound=false;
                }
           } 
        }else{
            return false;
        }
        return noFactorFound;
    }
    
}
