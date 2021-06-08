(define (f x0 y0)
    (cond((x? x0) (+ x0 1))(else x0))
    (cond((x? x0 y0) (+ x0 y0))(else x0))
)