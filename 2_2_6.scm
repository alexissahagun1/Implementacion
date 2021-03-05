(define (invert a b)
    (cond 
        ((null? b)
            a
        )
        ((not (list? b))
            (list b)
        )
        (else
            (if (list? (car b))
                (invert (append (list (invert '() (car b))) a) (cdr b))
                (invert (append (invert '() (car b)) a) (cdr b))
            )
        )
    )
)
(define (deep-reverse lst)
    (invert '() lst)
)

; La función "deep-reverse" llama a la función "invert" pasándole 2 listas: la primera una lista vacía, y la segunda la lista de entrada. Básicamente, lo que hace la función "invert" es:
; 1) Sacar el primer elemento de la lista 2, invertirlo (si no es lista se queda igual) y meterlo al comienzo de la lista 2
; 3) Volver a llamar "invert" pasando como primer parámetro la nueva lista 1, y segundo parámetro la lista 2 restante (sin su antiguo primer elemento)
; 4) Repetir hasta que la lista 2 esté vacía