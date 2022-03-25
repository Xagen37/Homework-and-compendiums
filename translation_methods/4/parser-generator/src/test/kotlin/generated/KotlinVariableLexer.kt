package generated

import java.io.IOException
import java.io.InputStream
import java.lang.StringBuilder
class KotlinVariableLexer(private val input: InputStream) {
    class LexerException(message: String) : Exception(message)
    enum class Token { VAL, VAR, COL, SEMICOL, EQ, NAME, TYPE, NUM, END }

    private val tokenStrings = listOf("val", "var", ":", ";", "=", null, null, null)
    private val tokenRegexps = mutableMapOf(5 to "[a-z][a-zA-Z0-9_]*".toRegex(), 6 to "[A-Z][a-zA-Z0-9_]*".toRegex(), 7 to "[0-9]+".toRegex())

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
            0 -> Token.VAL
			1 -> Token.VAR
			2 -> Token.COL
			3 -> Token.SEMICOL
			4 -> Token.EQ
			5 -> Token.NAME
			6 -> Token.TYPE
			7 -> Token.NUM

            else -> throw LexerException("Unexpected token '${sb.toString()}' at pos $curPos")
        }
        curTokenText = sb.toString()
    }

}
