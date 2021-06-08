(define (f x y)
    (cond((func? x y) (+ x y))(else (- x y)))
)

(define (func? z?)
    (not z?)
)