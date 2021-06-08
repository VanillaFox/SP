(define (f x y)
    (cond((func? x) (+ x y))(else (- x y)))
)

(define (func? z?)
    (< (not z?))
)