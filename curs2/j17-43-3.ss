(define a 10)
(define (func? x)
    (= 1 (cond((< x 1) 1)(else 0)))
)

(set! a (cond((func? 10 20 #f) 1)
    (else (* a 10)))