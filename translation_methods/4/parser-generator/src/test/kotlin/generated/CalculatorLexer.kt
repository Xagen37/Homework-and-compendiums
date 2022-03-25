package generated

import java.io.IOException
import java.io.InputStream
import java.lang.StringBuilder
class CalculatorLexer(private val input: InputStream) {
    class LexerException(message: String) : Exception(message)
    enum class Token { ADD, SUB, MUL, DIV, LBR, RBR, LSQ, RSQ, COMMA, NUM, END }

    private val tokenStrings = listOf("+", "-", "*", "/", "(", ")", "[", "]", ",", null)
    private val tokenRegexps = mutableMapOf(9 to "[0-9]+".toRegex())

    private var curChar = -1
    private var curPos = 0

    lateinit var curTokenText: String
        private set

    lateinit var curToken: Token
        private set

    init {
        nextChar()
    }

    private fun skipSpaces() {
        while (curChar != -1 && curChar.toChar().isWhitespace()) {
            nextChar()
        }
    }

    private fun nextChar() {
        try {
            curChar = input.read()
            curPos++
        } catch (e: IOException) {
            throw LexerException("Cannot read next char from input")
        }
    }

    private fun tokenId(s: String): Int {
        for (i in tokenStrings.indices) {
            if (tokenStrings[i] != null) {
                if (tokenStrings[i] == s) {
                    return i
                }
            } else {
                for (p in tokenRegexps) {
                    if (p.value.matches(s)) {
                        return p.key
                    }
                }
            }
        }
        return -1
    }

    fun nextToken() {
        skipSpaces()
        if (curChar == -1) {
            curToken = Token.END
            return
        }
        val sb = StringBuilder()
        while (curChar != -1 && !curChar.toChar().isWhitespace()) {
            sb.append(curChar.toChar())
            nextChar()
        }
        curToken = when (tokenId(sb.toString())) {
            0 -> Token.ADD
			1 -> Token.SUB
			2 -> Token.MUL
			3 -> Token.DIV
			4 -> Token.LBR
			5 -> Token.RBR
			6 -> Token.LSQ
			7 -> Token.RSQ
			8 -> Token.COMMA
			9 -> Token.NUM

            else -> throw LexerException("Unexpected token '${sb.toString()}' at pos $curPos")
        }
        curTokenText = sb.toString()
    }

}
