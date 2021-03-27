(define (part n lst1 lst2)
    (cond 
        ((null? lst2)
            (append lst1 (cons n '()))
        )
        ((< n (car lst2))
            (append (append lst1 (cons n '())) lst2)
        )
        (else
            (part n (append lst1 (cons (car lst2) '())) (cdr lst2)) 
        )
    )
)
(define (insert n lst)
    (part n '() lst)
)

; La funcion "insert" simplemente se utiliza para llamar al metodo recursivo "part", el cual trabaja con 2 listas: inicialmente una vacía, y la lista original. Si el primer elemento de la lista original es menor o igual a n, inserta dicho elemento en la primer lista y lo remueve de la segunda. Así lo hace hasta encontrar algún numero mayor a n, o hasta que se vacía la lista 2. En estos casos, inserta n en su lugar correspondiente y regresa la primer lista.