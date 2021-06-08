(define (func? func? )
    func?
)
(define a (cond((func? #t) 1)(else 10)))
a