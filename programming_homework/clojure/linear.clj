(defn v+ [left, right]
  (mapv + left right)
  )

(defn v- [left, right]
  (mapv - left right)
  )

(defn v* [left, right]
  (mapv * left right)
  )

(defn scalar [left, right]
  (reduce + (v* left right))
  )

(defn s+ [left, right]
  (if (and (vector? left) (vector? right))
      (mapv s+ left right)
      (+ left right))
  )

(defn s- [left, right]
  (if (and (vector? left) (vector? right))
    (mapv s- left right)
    (- left right))
  )

(defn s* [left, right]
  (if (and (vector? left) (vector? right))
    (mapv s* left right)
    (* left right))
  )

(defn det [x11, x12, x21, x22]
  (- (* x11 x22) (* x12 x21))
  )

(defn vect [left, right]
  (vector
    (det (nth left 1) (nth left 2) (nth right 1) (nth right 2))
    (- (det (nth left 0) (nth left 2) (nth right 0) (nth right 2)))
    (det (nth left 0) (nth left 1) (nth right 0) (nth right 1))
    )
  )

(defn v*s [vec, num]
  (mapv (partial * num) vec)
  )

(defn m+ [left, right]
  (mapv v+ left right)
  )

(defn m- [left, right]
  (mapv v- left right)
  )

(defn m* [left, right]
  (mapv v* left right)
  )

(defn m*s [matrix, num]
  (mapv (fn [vec] (v*s vec num)) matrix)
  )

(defn m*v [matrix, vec]
  (mapv (partial scalar vec) matrix)
  )

(defn transpose [matrix]
  (apply mapv vector matrix)
  )

(defn m*m [left, right]
  (transpose (mapv (fn [vec] (mapv (partial scalar vec) left)) (transpose right)))
  )