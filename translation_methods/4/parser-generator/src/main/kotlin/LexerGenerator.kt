import CodeParser.*

private const val STRING_QUOTE = "'"
private const val REGEX_QUOTE = "\""

class LexerGenerator(private val grammarName: String,
                     terminalsCtx: TermsContext,
                     private val packageName: String) {
    private data class Token(val name: String, val value: String)

    private val tokens = terminalsCtx.term().map { Token(it.TERMINAL().text, it.expr.text) }

    fun generate(): String {
        val header = "package $packageName\n\n" +
                "import java.io.IOException\n" +
                "import java.io.InputStream\n" +
                "import java.lang.StringBuilder\n"
        val decl = "class ${grammarName}Lexer(private val input: InputStream) {\n"
        val except = "    class LexerException(message: String) : Exception(message)\n"
        val tokenEnum = "    enum class Token { ${tokens.joinToString { it.name }}, END }\n\n"

        val joinedTokens = tokens.joinToString {
            if (it.value.startsWith(REGEX_QUOTE)) {
                "null"
            } else {
                "\"${it.value.removeSurrounding(STRING_QUOTE)}\""
            }
        }
        val joinedRegexps = tokens.withIndex().filter { it.value.value.startsWith(REGEX_QUOTE) }.joinToString {
            "${it.index} to \"${it.value.value.removeSurrounding(REGEX_QUOTE)}\".toRegex()"
        }
        if (joinedRegexps.isEmpty() && joinedTokens.isEmpty())
            throw GeneratorException("Cannot create lexer without any tokens")

        val tokStrings = if (joinedTokens.isNotEmpty())
            "    private val tokenStrings = listOf(${joinedTokens})\n"
        else ""

        val tokRegexps = if (joinedRegexps.isNotEmpty())
            "    private val tokenRegexps = mutableMapOf(${joinedRegexps})\n"
        else ""

        val vars = "\n    private var curChar = -1\n" +
                "    private var curPos = 0\n\n" +
                "    lateinit var curTokenText: String\n        private set\n\n" +
                "    lateinit var curToken: Token\n        private set\n\n"

        val init = "    init {\n" +
                "        nextChar()\n" +
                "    }\n\n"

        val spaceSkipper = "    private fun skipSpaces() {\n" +
                "        while (curChar != -1 && curChar.toChar().isWhitespace()) {\n" +
                "            nextChar()\n" +
                "        }\n" +
                "    }\n\n"

        val nextChar = "    private fun nextChar() {\n" +
                "        try {\n" +
                "            curChar = input.read()\n" +
                "            curPos++\n" +
                "        } catch (e: IOException) {\n" +
                "            throw LexerException(\"Cannot read next char from input\")\n" +
                "        }\n" +
                "    }\n\n"

        val tokenIdStart = "    private fun tokenId(s: String): Int {\n" +
                "        for (i in tokenStrings.indices) {\n" +
                "            if (tokenStrings[i] != null) {\n" +
                "                if (tokenStrings[i] == s) {\n" +
                "                    return i\n" +
                "                }\n" +
                "            }"
        val tokenIdElse = if (tokRegexps.isNotEmpty())
                " else {\n" +
                "                for (p in tokenRegexps) {\n" +
                "                    if (p.value.matches(s)) {\n" +
                "                        return p.key\n" +
                "                    }\n" +
                "                }\n" +
                "            }\n"
        else "\n"
        val tokenIdEnd = "        }\n" + "        return -1\n" + "    }\n\n"
        val tokenId = tokenIdStart + tokenIdElse + tokenIdEnd

        val joinedWhens = tokens.withIndex()
            .joinToString(separator = "\n\t\t\t", postfix = "\n")
            { "${it.index} -> Token.${it.value.name}" }
        val nextToken = "    fun nextToken() {\n" +
                "        skipSpaces()\n" +
                "        if (curChar == -1) {\n" +
                "            curToken = Token.END\n" +
                "            return\n" +
                "        }\n" +
                "        val sb = StringBuilder()\n" +
                "        while (curChar != -1 && !curChar.toChar().isWhitespace()) {\n" +
                "            sb.append(curChar.toChar())\n" +
                "            nextChar()\n" +
                "        }\n" +
                "        curToken = when (tokenId(sb.toString())) {\n" +
                "            ${joinedWhens}\n" +
                "            else -> throw LexerException(\"Unexpected token '${'$'}{sb.toString()}' at pos ${'$'}curPos\")\n" +
                "        }\n" +
                "        curTokenText = sb.toString()\n" +
                "    }\n\n"
        val ender = "}\n"

        val text = header + decl + except + tokenEnum +
                tokStrings + tokRegexps + vars + init +
                spaceSkipper + nextChar +
                tokenId + nextToken + ender

        return text
    }
}