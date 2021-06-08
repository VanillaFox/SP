(define (func? x y z)
    (= 0 (cond((< x y) 1)(else
        (cond((< z y) 1)(else 0))
    )))
)
(define a 10)
(set! a (cond((func? 11 #t 10) a)(else (+ 10 a)))