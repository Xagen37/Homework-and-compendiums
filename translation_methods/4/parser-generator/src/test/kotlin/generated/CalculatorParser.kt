package generated

import generated.CalculatorLexer.Token.*class CalculatorParser(private val lexer: CalculatorLexer) {
    class ParserException(message: String) : Exception(message)

    init {
        lexer.nextToken()
    }

    open class Tree(val nodeName: String) {
         val children = mutableListOf<Tree>()
    }
    class TerminalNode(nodeName: String, val text: String) : Tree(nodeName)

    fun parse (): StartContext {
        val res = start()

        if (lexer.curToken == END) {
            return res
        } else {
            throw ParserException("Unexpected ${lexer.curToken} at the end of the input")
        }
    }    

    class StartContext(name: String): Tree(name) {
            var result: Int? = null
            var expr: ExprContext? = null
    }        


    fun start(): StartContext {
        val _localctx = StartContext("start")
        
        when (lexer.curToken) {
            SUB, LBR, NUM, LSQ -> {
				val expr = expr()

                _localctx.expr = expr
                _localctx.children.add(expr)

				_localctx.result = _localctx.expr!!.value
				return _localctx
			}

            else -> throw ParserException("${lexer.curToken} unexpected in start")

        }
    }



    class ExprContext(name: String): Tree(name) {
            var value: Int? = null
            var term: TermContext? = null
		var exprP: ExprPContext? = null
    }        


    fun expr(): ExprContext {
        val _localctx = ExprContext("expr")
        
        when (lexer.curToken) {
            SUB, LBR, NUM, LSQ -> {
				val term = term()

                _localctx.term = term
                _localctx.children.add(term)

				val exprP = exprP(term.value!!)

                _localctx.exprP = exprP
                _localctx.children.add(exprP)

				_localctx.value = _localctx.exprP!!.res
				return _localctx
			}

            else -> throw ParserException("${lexer.curToken} unexpected in expr")

        }
    }



    class ExprPContext(name: String, val i: Int): Tree(name) {
            var res: Int? = null
            var lastOrderOp: LastOrderOpContext? = null
		var term: TermContext? = null
		var exprP: ExprPContext? = null
    }        


    fun exprP(i: Int): ExprPContext {
        val _localctx = ExprPContext("exprP", i)
        
        when (lexer.curToken) {
            ADD, SUB -> {
				val lastOrderOp = lastOrderOp()

                _localctx.lastOrderOp = lastOrderOp
                _localctx.children.add(lastOrderOp)

				val term = term()

                _localctx.term = term
                _localctx.children.add(term)

				_localctx.res = if (_localctx.lastOrderOp!!.ADD != null) _localctx.i + _localctx.term!!.value!! else _localctx.i - _localctx.term!!.value!!
				val exprP = exprP(_localctx.res!!)

                _localctx.exprP = exprP
                _localctx.children.add(exprP)

				_localctx.res = _localctx.exprP!!.res
				return _localctx
			}
			END, RBR, COMMA, RSQ -> {
				_localctx.res = _localctx.i
				return _localctx
			}

            else -> throw ParserException("${lexer.curToken} unexpected in exprP")

        }
    }



    class TermContext(name: String): Tree(name) {
            var value: Int? = null
            var fact: FactContext? = null
		var termP: TermPContext? = null
    }        


    fun term(): TermContext {
        val _localctx = TermContext("term")
        
        when (lexer.curToken) {
            SUB, LBR, NUM, LSQ -> {
				val fact = fact()

                _localctx.fact = fact
                _localctx.children.add(fact)

				val termP = termP(fact.value!!)

                _localctx.termP = termP
                _localctx.children.add(termP)

				_localctx.value = _localctx.termP!!.res
				return _localctx
			}

            else -> throw ParserException("${lexer.curToken} unexpected in term")

        }
    }



    class TermPContext(name: String, val i: Int): Tree(name) {
            var res: Int? = null
            var firstOrderOp: FirstOrderOpContext? = null
		var fact: FactContext? = null
		var termP: TermPContext? = null
    }        


    fun termP(i: Int): TermPContext {
        val _localctx = TermPContext("termP", i)
        
        when (lexer.curToken) {
            MUL, DIV -> {
				val firstOrderOp = firstOrderOp()

                _localctx.firstOrderOp = firstOrderOp
                _localctx.children.add(firstOrderOp)

				val fact = fact()

                _localctx.fact = fact
                _localctx.children.add(fact)

				_localctx.res = if (_localctx.firstOrderOp!!.MUL != null) _localctx.i * _localctx.fact!!.value!! else _localctx.i / _localctx.fact!!.value!!
				val termP = termP(_localctx.res!!)

                _localctx.termP = termP
                _localctx.children.add(termP)

				_localctx.res = _localctx.termP!!.res
				return _localctx
			}
			END, ADD, SUB, RBR, COMMA, RSQ -> {
				_localctx.res = _localctx.i
				return _localctx
			}

            else -> throw ParserException("${lexer.curToken} unexpected in termP")

        }
    }



    class FactContext(name: String): Tree(name) {
            var value: Int? = null
            var SUB: TerminalNode? = null
		var fact_expr: Fact_exprContext? = null
    }        


    fun fact(): FactContext {
        val _localctx = FactContext("fact")
        
        when (lexer.curToken) {
            SUB -> {

        if (lexer.curToken != SUB) {
            throw ParserException("${lexer.curToken} unexpected in fact")
        }
    
        val SUB = TerminalNode("SUB", lexer.curTokenText)
        _localctx.SUB = SUB
        _localctx.children.add(SUB)

		lexer.nextToken()
				val fact_expr = fact_expr()

                _localctx.fact_expr = fact_expr
                _localctx.children.add(fact_expr)

				_localctx.value = - _localctx.fact_expr!!.value!!
				return _localctx
			}
LBR, NUM, LSQ -> {
				val fact_expr = fact_expr()

                _localctx.fact_expr = fact_expr
                _localctx.children.add(fact_expr)

				_localctx.value = _localctx.fact_expr!!.value
				return _localctx
			}

            else -> throw ParserException("${lexer.curToken} unexpected in fact")

        }
    }



    class Fact_exprContext(name: String): Tree(name) {
            var value: Int? = null
            var LBR: TerminalNode? = null
		var expr: ExprContext? = null
		var RBR: TerminalNode? = null
		var NUM: TerminalNode? = null
		var binom: BinomContext? = null
    }        


    fun fact_expr(): Fact_exprContext {
        val _localctx = Fact_exprContext("fact_expr")
        
        when (lexer.curToken) {
            LBR -> {

        if (lexer.curToken != LBR) {
            throw ParserException("${lexer.curToken} unexpected in fact_expr")
        }
    
        val LBR = TerminalNode("LBR", lexer.curTokenText)
        _localctx.LBR = LBR
        _localctx.children.add(LBR)

		lexer.nextToken()
				val expr = expr()

                _localctx.expr = expr
                _localctx.children.add(expr)


        if (lexer.curToken != RBR) {
            throw ParserException("${lexer.curToken} unexpected in fact_expr")
        }
    
        val RBR = TerminalNode("RBR", lexer.curTokenText)
        _localctx.RBR = RBR
        _localctx.children.add(RBR)

				_localctx.value = _localctx.expr!!.value
		lexer.nextToken()
				return _localctx
			}
NUM -> {

        if (lexer.curToken != NUM) {
            throw ParserException("${lexer.curToken} unexpected in fact_expr")
        }
    
        val NUM = TerminalNode("NUM", lexer.curTokenText)
        _localctx.NUM = NUM
        _localctx.children.add(NUM)

				_localctx.value = _localctx.NUM!!.text.toInt()
		lexer.nextToken()
				return _localctx
			}
LSQ -> {
				val binom = binom()

                _localctx.binom = binom
                _localctx.children.add(binom)

				_localctx.value = _localctx.binom!!.res
				return _localctx
			}

            else -> throw ParserException("${lexer.curToken} unexpected in fact_expr")

        }
    }



    class BinomContext(name: String): Tree(name) {
            var res: Int? = null
            var LSQ: TerminalNode? = null
		var expr: ExprContext? = null
		var COMMA: TerminalNode? = null
		var expr1: ExprContext? = null
		var RSQ: TerminalNode? = null
    }        


    fun binom(): BinomContext {
        val _localctx = BinomContext("binom")
        
        when (lexer.curToken) {
            LSQ -> {

        if (lexer.curToken != LSQ) {
            throw ParserException("${lexer.curToken} unexpected in binom")
        }
    
        val LSQ = TerminalNode("LSQ", lexer.curTokenText)
        _localctx.LSQ = LSQ
        _localctx.children.add(LSQ)

		lexer.nextToken()
				val expr = expr()

                _localctx.expr = expr
                _localctx.children.add(expr)


        if (lexer.curToken != COMMA) {
            throw ParserException("${lexer.curToken} unexpected in binom")
        }
    
        val COMMA = TerminalNode("COMMA", lexer.curTokenText)
        _localctx.COMMA = COMMA
        _localctx.children.add(COMMA)

		lexer.nextToken()
				val expr1 = expr()

                _localctx.expr1 = expr1
                _localctx.children.add(expr1)


        if (lexer.curToken != RSQ) {
            throw ParserException("${lexer.curToken} unexpected in binom")
        }
    
        val RSQ = TerminalNode("RSQ", lexer.curTokenText)
        _localctx.RSQ = RSQ
        _localctx.children.add(RSQ)

				val __nfac = (1.._localctx.expr!!.value!!).reduce(Int::times)
                                                    val __kfac = (1.._localctx.expr1!!.value!!).reduce(Int::times)
                                                    val __nmkfac = (1..(_localctx.expr!!.value!! - _localctx.expr1!!.value!!)).reduce(Int::times)
                                                    _localctx.res = __nfac / (__kfac * __nmkfac)
		lexer.nextToken()
				return _localctx
			}

            else -> throw ParserException("${lexer.curToken} unexpected in binom")

        }
    }



    class LastOrderOpContext(name: String): Tree(name) {
            
            var ADD: TerminalNode? = null
		var SUB: TerminalNode? = null
    }        


    fun lastOrderOp(): LastOrderOpContext {
        val _localctx = LastOrderOpContext("lastOrderOp")
        
        when (lexer.curToken) {
            ADD -> {

        if (lexer.curToken != ADD) {
            throw ParserException("${lexer.curToken} unexpected in lastOrderOp")
        }
    
        val ADD = TerminalNode("ADD", lexer.curTokenText)
        _localctx.ADD = ADD
        _localctx.children.add(ADD)

		lexer.nextToken()
				return _localctx
			}
SUB -> {

        if (lexer.curToken != SUB) {
            throw ParserException("${lexer.curToken} unexpected in lastOrderOp")
        }
    
        val SUB = TerminalNode("SUB", lexer.curTokenText)
        _localctx.SUB = SUB
        _localctx.children.add(SUB)

		lexer.nextToken()
				return _localctx
			}

            else -> throw ParserException("${lexer.curToken} unexpected in lastOrderOp")

        }
    }



    class FirstOrderOpContext(name: String): Tree(name) {
            
            var MUL: TerminalNode? = null
		var DIV: TerminalNode? = null
    }        


    fun firstOrderOp(): FirstOrderOpContext {
        val _localctx = FirstOrderOpContext("firstOrderOp")
        
        when (lexer.curToken) {
            MUL -> {

        if (lexer.curToken != MUL) {
            throw ParserException("${lexer.curToken} unexpected in firstOrderOp")
        }
    
        val MUL = TerminalNode("MUL", lexer.curTokenText)
        _localctx.MUL = MUL
        _localctx.children.add(MUL)

		lexer.nextToken()
				return _localctx
			}
DIV -> {

        if (lexer.curToken != DIV) {
            throw ParserException("${lexer.curToken} unexpected in firstOrderOp")
        }
    
        val DIV = TerminalNode("DIV", lexer.curTokenText)
        _localctx.DIV = DIV
        _localctx.children.add(DIV)

		lexer.nextToken()
				return _localctx
			}

            else -> throw ParserException("${lexer.curToken} unexpected in firstOrderOp")

        }
    }

 }
