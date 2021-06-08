(define (f? x)
    (< 10 x)
)

(define (func? x? x0 y0)
    (<
        (cond(x? (+ 1 x0))(else (* 2 x0)))
        (cond(y? (* 2 y0))(else (* 2 x0)))
    )
)