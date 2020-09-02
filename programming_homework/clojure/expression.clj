;-------------------HW 10-----------------------------------
(defn constant [value]
  (fn [nameMap] (double value))
  )

(defn variable [name]
  (fn [nameMap] (double (nameMap (str name))))
  )

(defn operation [f & elements] (fn [nameMap] (apply f (mapv #(double (%1 nameMap)) elements))))

(defn add [& elements] (apply (partial operation +) elements))

(defn subtract [& elements] (apply (partial operation -) elements))

(defn multiply [& elements] (apply (partial operation *) elements))

(defn divide
  ([first & elements] (fn [nameMap] (let [numer (double (first nameMap))
                                          denomin (double (reduce * 1 (mapv #(%1 nameMap) elements)))]
                                      (/ numer denomin))))
  ([first] (fn [nameMap] (/ 1.0 (double (first nameMap)))))
  )

(defn negate [& elements] (apply (partial operation -) elements))

(def clojmin clojure.core/min)
(def clojmax clojure.core/max)
(defn min [& elements] (apply (partial operation clojmin) elements))
(defn max [& elements] (apply (partial operation clojmax) elements))
(defn expo [element] (fn [nameMap] (Math/exp (double (element nameMap)))))
(defn sumexp [& elements] (apply add (mapv expo elements)))
(defn softmax [& elements] (divide (expo (first elements)) (apply sumexp elements)))

(defn parseFunction [line]
  (let [expr (read-string line)]
    (letfn [(parseOp [value] (get {'+       add
                                   '-       subtract
                                   '*       multiply
                                   '/       divide
                                   'negate  negate
                                   'min     min
                                   'max     max
                                   'sumexp  sumexp
                                   'softmax softmax} value))
            (parse [value] (cond
                             (number? value) (constant value)
                             (contains? #{"x", "y", "z"} (str value)) (variable value)
                             (coll? value) (apply
                                             (parseOp (peek value))
                                             (mapv parse (pop value)))))
            ]
      (parse expr))))
;---------------------HW 11----------------------------------
; -------------<Korneev's code>--------------------------------
(defn proto-get [obj key]
  (cond
    (contains? obj key) (obj key)
    (contains? obj :prototype) (proto-get (obj :prototype) key)
    :else nil))

(defn proto-call [this key & args]
  (apply (proto-get this key) this args))

(defn field [key]
  (fn [this] (proto-get this key)))

(defn method [key]
  (fn [this & args] (apply proto-call this key args)))

(defn constructor [ctor prototype]
  (fn [& args] (apply ctor {:prototype prototype} args)))
; -------------</Korneev's code>--------------------------------
(def evaluate (method :evaluate))
(def toString (method :toString))
(def diff (method :diff))
(def _value (field :value))
(def _name (field :name))
(def _function (field :function))
(def _functionChar (field :functionChar))
(def _arguments (field :arguments))

(def CommonPrototype {
                      :evaluate nil
                      :toString nil
                      :diff     nil
                      })

(def Constant)
(def ConstantPrototype (assoc CommonPrototype
                         :evaluate (fn [expression vars] (_value expression))
                         :diff (fn [expression var] (Constant 0.0))
                         :toString (fn [expression] (str (format "%.1f" (_value expression))))))
(defn ConstantConstructor [this value] (assoc this
                                         :value value))
(def Constant (constructor ConstantConstructor ConstantPrototype))
(def ZEROCONST (Constant 0.0))
(def ONECONST (Constant 1.0))

(def VariablePrototype (assoc CommonPrototype
                         :evaluate (fn [expression vars] (double (vars (str (_name expression)))))
                         :diff (fn [expression var] (if (= var (str (_name expression)))
                                                      ONECONST
                                                      ZEROCONST))
                         :toString (fn [expression] (str (_name expression)))))
(defn VariableConstructor [this name] (assoc this
                                        :name name))
(def Variable (constructor VariableConstructor VariablePrototype))


(def OperationPrototype (assoc CommonPrototype
                          :evaluate (fn [expression vars] (apply (_function expression) (mapv #(evaluate %1 vars) (_arguments expression))))
                          :toString (fn [expression] (str "("
                                                          (_functionChar expression)
                                                          (apply str (mapv #(str " " (toString %1)) (_arguments expression)))
                                                          ")"))))
(defn OperationConstructor [this & arguments] (assoc this
                                                :arguments arguments))

(def Negate)
(def NegatePrototype (assoc OperationPrototype
                       :function -
                       :functionChar "negate"
                       :diff (fn [expression var] (Negate (diff (first (_arguments expression)) var)))))
(def Negate (constructor OperationConstructor NegatePrototype))

(def Add)
(def AddPrototype (assoc OperationPrototype
                    :function +
                    :functionChar "+"
                    :diff (fn [expression var] (apply Add (mapv #(diff %1 var) (_arguments expression))))))
(def Add (constructor OperationConstructor AddPrototype))

(def Subtract)
(def SubtractPrototype (assoc OperationPrototype
                         :function -
                         :functionChar "-"
                         :diff (fn [expression var] (apply Subtract (mapv #(diff %1 var) (_arguments expression))))))
(def Subtract (constructor OperationConstructor SubtractPrototype))

(def Multiply)
(defn complexDiff [diffFunction] (fn [expr & arguments]
                                   (let [expFunc (partial diffFunction expr)]
                                     (if (= 2 (count arguments))
                                       (apply expFunc arguments)
                                       (expFunc (first arguments) (apply Multiply (rest arguments)))))))

(def MultiplyPrototype (assoc OperationPrototype
                         :function *
                         :functionChar "*"
                         :diff (fn [expression var] (apply
                                                      (partial (complexDiff (fn [var left right]
                                                                              (Add
                                                                                (Multiply (diff left var) right)
                                                                                (Multiply left (diff right var)))))
                                                               var)
                                                      (_arguments expression)))))
(def Multiply (constructor OperationConstructor MultiplyPrototype))

(def Divide)
(def DividePrototype (assoc OperationPrototype
                       :function (fn [numer & other] (/ numer (double (reduce * other))))
                       :functionChar "/"
                       :diff (fn [expression var] (apply
                                                    (partial (complexDiff (fn [var left right]
                                                                            (Divide
                                                                              (Subtract
                                                                                (Multiply (diff left var) right)
                                                                                (Multiply left (diff right var)))
                                                                              (Multiply right right))))
                                                             var)
                                                    (_arguments expression)))))
(def Divide (constructor OperationConstructor DividePrototype))
(def Exp)
(def ExpPrototype (assoc OperationPrototype
                    :function (fn [argument] (#(Math/exp %) argument))
                    :functionChar "exp"
                    :diff (fn [expression var] (Multiply
                                                 (diff (first (_arguments expression)) var)
                                                 (Exp (first (_arguments expression)))))))
(def Exp (constructor OperationConstructor ExpPrototype))

(def SumexpPrototype (assoc OperationPrototype
                       :function (fn [& arguments] (apply + (mapv #(Math/exp %) arguments)))
                       :functionChar "sumexp"
                       :diff (fn [expression var] (apply Add
                                                         (mapv #(Multiply
                                                                  (diff % var)
                                                                  (Exp %))
                                                               (_arguments expression))))
                       ))
(def Sumexp (constructor OperationConstructor SumexpPrototype))

(def SoftmaxPrototype (assoc OperationPrototype
                        :function (fn [& arguments] (/
                                                      (Math/exp (first arguments))
                                                      (apply (_function SumexpPrototype) arguments)))
                        :functionChar "softmax"
                        :diff (fn [expression var] (let [expr (Divide
                                                                 (Exp (first (_arguments expression)))
                                                                 (apply Sumexp (_arguments expression)))]
                                                     (diff expr var)))
                        ))
(def Softmax (constructor OperationConstructor SoftmaxPrototype))

(def Pw)
(def Ln)
(def PwPrototype (assoc OperationPrototype
                   :diff (fn [expression var] (let [left (first (_arguments expression))
                                                    right (first (rest (_arguments expression)))
                                                    diffLeft (diff left var)
                                                    diffRight (diff right var)
                                                    diffA (Pw left (Subtract right ONECONST))
                                                    diffB (Add
                                                            (Multiply right diffLeft)
                                                            (Multiply
                                                              (Multiply left (Ln left))
                                                              diffRight))
                                                    ]
                                                (Multiply diffA diffB)))
                   :function (fn [left right] (Math/pow left right))
                   :functionChar "pw"))
(def Pw (constructor OperationConstructor PwPrototype))

(def Lg)
(def LgPrototype (assoc OperationPrototype
                   :diff (fn [expression var] (let [left (Ln (first (_arguments expression)))
                                                    right (Ln (first (rest (_arguments expression))))]
                                                (diff (Divide right left) var)))
                   :function (fn [^Double left ^Double right] (/ (Math/log (Math/abs right)) (Math/log (Math/abs left))))
                   :functionChar "lg"))
(def Lg (constructor OperationConstructor LgPrototype))

(def LnPrototype (assoc OperationPrototype
                   :title "Ln"
                   :diff (fn [expression var] (Divide (diff (first (_arguments expression)) var) (first (_arguments expression))))
                   :functionChar "ln"
                   :function (fn [^Double arg] (Math/log (Math/abs arg)))))
(def Ln (constructor OperationConstructor LnPrototype))


(defn parseObject [line]
  (let [expr (read-string line)]
    (letfn [(parseOp [value] (get {'+       Add
                                   '-       Subtract
                                   '*       Multiply
                                   '/       Divide
                                   'negate  Negate
                                   'min     min
                                   'max     max
                                   'softmax Softmax
                                   'sumexp  Sumexp
                                   'pw      Pw
                                   'lg      Lg} value))
            (parse [value] (cond
                             (number? value) (Constant value)
                             (contains? #{"x", "y", "z"} (str value)) (Variable value)
                             (coll? value) (apply
                                             (parseOp (peek value))
                                             (mapv parse (pop value)))))
            ]
      (parse expr))))