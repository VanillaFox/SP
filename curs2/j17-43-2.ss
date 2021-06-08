(define x 1)
(define y 2)
(set! x (cond( (func? 1 #f) 10)(else 20)))
(set! y (cond((func? #t 2) (+ y x))(else 0))
