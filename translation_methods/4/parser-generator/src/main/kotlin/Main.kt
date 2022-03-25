import org.antlr.v4.runtime.CharStreams
import org.antlr.v4.runtime.CommonTokenStream
import java.io.File

fun main() {
    val name = readLine()!!

    val inputStream = CharStreams.fromFileName("src/test/kotlin/$name")
    val lexer  = CodeLexer(inputStream)
    val tokens = CommonTokenStream(lexer)
    val parser = CodeParser(tokens)
    val tree   = parser.header()

    val grammarName = tree.grammarName.text
    val packageName = "generated"

    val terminals    = tree.terms()
    val nonterminals = tree.rules()

    val genLexer  = LexerGenerator(grammarName, terminals, packageName).generate()
    val genParser = ParserGenerator(grammarName, nonterminals, packageName).generate()

    File("src/test/kotlin/$packageName/${grammarName}Lexer.kt").writeText(genLexer)
    File("src/test/kotlin/$packageName/${grammarName}Parser.kt").writeText(genParser)

    println("Hello, parsers!")
}