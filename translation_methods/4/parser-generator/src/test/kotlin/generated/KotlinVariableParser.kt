package generated

import generated.KotlinVariableLexer.Token.*class KotlinVariableParser(private val lexer: KotlinVariableLexer) {
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
            
            var st: StContext? = null
		var SEMICOL: TerminalNode? = null
    }        


    fun start(): StartContext {
        val _localctx = StartContext("start")
        
        when (lexer.curToken) {
            VAL, VAR -> {
				val st = st()

                _localctx.st = st
                _localctx.children.add(st)


        if (lexer.curToken != SEMICOL) {
            throw ParserException("${lexer.curToken} unexpected in start")
        }
    
        val SEMICOL = TerminalNode("SEMICOL", lexer.curTokenText)
        _localctx.SEMICOL = SEMICOL
        _localctx.children.add(SEMICOL)

		lexer.nextToken()
				return _localctx
			}

            else -> throw ParserException("${lexer.curToken} unexpected in start")

        }
    }



    class StContext(name: String): Tree(name) {
            
            var v1: V1Context? = null
		var v2: V2Context? = null
    }        


    fun st(): StContext {
        val _localctx = StContext("st")
        
        when (lexer.curToken) {
            VAL -> {
				val v1 = v1()

                _localctx.v1 = v1
                _localctx.children.add(v1)

				return _localctx
			}
VAR -> {
				val v2 = v2()

                _localctx.v2 = v2
                _localctx.children.add(v2)

				return _localctx
			}

            else -> throw ParserException("${lexer.curToken} unexpected in st")

        }
    }



    class V1Context(name: String): Tree(name) {
            
            var VAL: TerminalNode? = null
		var b: BContext? = null
		var i: IContext? = null
    }        


    fun v1(): V1Context {
        val _localctx = V1Context("v1")
        
        when (lexer.curToken) {
            VAL -> {

        if (lexer.curToken != VAL) {
            throw ParserException("${lexer.curToken} unexpected in v1")
        }
    
        val VAL = TerminalNode("VAL", lexer.curTokenText)
        _localctx.VAL = VAL
        _localctx.children.add(VAL)

		lexer.nextToken()
				val b = b()

                _localctx.b = b
                _localctx.children.add(b)

				val i = i()

                _localctx.i = i
                _localctx.children.add(i)

				return _localctx
			}

            else -> throw ParserException("${lexer.curToken} unexpected in v1")

        }
    }



    class V2Context(name: String): Tree(name) {
            
            var VAR: TerminalNode? = null
		var b: BContext? = null
		var c: CContext? = null
    }        


    fun v2(): V2Context {
        val _localctx = V2Context("v2")
        
        when (lexer.curToken) {
            VAR -> {

        if (lexer.curToken != VAR) {
            throw ParserException("${lexer.curToken} unexpected in v2")
        }
    
        val VAR = TerminalNode("VAR", lexer.curTokenText)
        _localctx.VAR = VAR
        _localctx.children.add(VAR)

		lexer.nextToken()
				val b = b()

                _localctx.b = b
                _localctx.children.add(b)

				val c = c()

                _localctx.c = c
                _localctx.children.add(c)

				return _localctx
			}

            else -> throw ParserException("${lexer.curToken} unexpected in v2")

        }
    }



    class BContext(name: String): Tree(name) {
            
            var NAME: TerminalNode? = null
		var COL: TerminalNode? = null
		var TYPE: TerminalNode? = null
    }        


    fun b(): BContext {
        val _localctx = BContext("b")
        
        when (lexer.curToken) {
            NAME -> {

        if (lexer.curToken != NAME) {
            throw ParserException("${lexer.curToken} unexpected in b")
        }
    
        val NAME = TerminalNode("NAME", lexer.curTokenText)
        _localctx.NAME = NAME
        _localctx.children.add(NAME)

		lexer.nextToken()

        if (lexer.curToken != COL) {
            throw ParserException("${lexer.curToken} unexpected in b")
        }
    
        val COL = TerminalNode("COL", lexer.curTokenText)
        _localctx.COL = COL
        _localctx.children.add(COL)

		lexer.nextToken()

        if (lexer.curToken != TYPE) {
            throw ParserException("${lexer.curToken} unexpected in b")
        }
    
        val TYPE = TerminalNode("TYPE", lexer.curTokenText)
        _localctx.TYPE = TYPE
        _localctx.children.add(TYPE)

		lexer.nextToken()
				return _localctx
			}

            else -> throw ParserException("${lexer.curToken} unexpected in b")

        }
    }



    class CContext(name: String): Tree(name) {
            
            var i: IContext? = null
    }        


    fun c(): CContext {
        val _localctx = CContext("c")
        
        when (lexer.curToken) {
            EQ -> {
				val i = i()

                _localctx.i = i
                _localctx.children.add(i)

				return _localctx
			}
			SEMICOL -> {
				return _localctx
			}

            else -> throw ParserException("${lexer.curToken} unexpected in c")

        }
    }



    class IContext(name: String): Tree(name) {
            
            var EQ: TerminalNode? = null
		var NUM: TerminalNode? = null
    }        


    fun i(): IContext {
        val _localctx = IContext("i")
        
        when (lexer.curToken) {
            EQ -> {

        if (lexer.curToken != EQ) {
            throw ParserException("${lexer.curToken} unexpected in i")
        }
    
        val EQ = TerminalNode("EQ", lexer.curTokenText)
        _localctx.EQ = EQ
        _localctx.children.add(EQ)

		lexer.nextToken()

        if (lexer.curToken != NUM) {
            throw ParserException("${lexer.curToken} unexpected in i")
        }
    
        val NUM = TerminalNode("NUM", lexer.curTokenText)
        _localctx.NUM = NUM
        _localctx.children.add(NUM)

		lexer.nextToken()
				return _localctx
			}

            else -> throw ParserException("${lexer.curToken} unexpected in i")

        }
    }

 }
