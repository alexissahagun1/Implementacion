(define(fahrenheit-to-celsius F)
    (cond
        ((number? F)
            (exact->inexact (* (- F 32) 5/9))
        )
        (else 
            'error
        )
    )
)

; Esta funcion toma como parámetro único a F, el cual, en caso de ser valor numérico, convierte su valor en Fahrenheit a su equivalente en Celsius. En caso de no ser numérico, regresa "error".