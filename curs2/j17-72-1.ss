(define (func? x?)
    (not (x?))
)

(define (func? y? x)
    (= 0 (cond((not (y?)) 0)(else 1))) 
)