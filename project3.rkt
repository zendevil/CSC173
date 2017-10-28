#lang racket


;list functions

;my_append
(define (my_append lhs rhs)
  (if (empty? lhs)
      rhs
      (cons (first lhs) (my_append (rest lhs) rhs))))
;(my_append '(1 2 3) '(5 6 7))


;WARNING my_reverse this doesn't work if there are similar elements in the list
(define (my_reverse li)
  (if (empty? li)
      li
      (cons (last li) (my_reverse (remove (last li) li)))))

;(my_reverse '(1 4 3 4))

;map
(define (my_map x)
  (x ))


;math functions
;abs value
(define (abs x)
  (if (>= x 0)
      x
      (* -1 x)))
(abs -99)



;fibonacci
(define (fib x)
  (if(= x 0)
     0
  (if (= x 1)
      1
      (+ (fib(- x 1)) (fib(- x 2))))))

(fib 6)


;factorial 

(define (fact x)
  (if (<= x 1)
      1
      (* (fact (- x 1)) x)))

(fact 66)


