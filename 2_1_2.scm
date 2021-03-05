(define (sign n)
    (cond 
        ((number? n) 
            (cond 
                ((> n 0) 
                    1
                )
                ((< n 0) 
                    (- 1)
                )
                (else 
                    0
                )
            )
        )
        (else 
            'error
        )
    )
)

; La función "sign" recibe como parámetro único a n, y primero determina si tiene valor numérico. De ser así, revisa si es negativo, 0, o positivo, y regresa el valor -1, 0, o 1, respectivamente. De no ser el caso, regresa "error".