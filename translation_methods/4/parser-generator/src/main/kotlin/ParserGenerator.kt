import CodeParser.*

private const val EPS = "!EPS!"
private const val END = "END"
private const val START = "start"
private const val CTX_ACCESS = "$"

class ParserGenerator(private val grammarName: String,
                      rulesCtx: RulesContext,
                      private val packageName: String) {

    private fun extractRules(ctx: RulesContext) = ctx.oneRule().map {
        Rule(
            name = it.NONTERM().text,
            attributes = extractAttributes(it.ruleLeft().attributeList()),
            retAttributes = extractAttributes(it.ruleLeft().toReturn()?.attributeList()),
            prods = extractProductions(it.ruleRight())
        )
    }

    private fun extractAttributes(ctx: AttributeListContext?) = ctx?.attribute()?.map {
        Attribute(it.type.text, it.name.text)
    }.orEmpty()

    private fun extractProductions(ctx: RuleRightContext) = ctx.product().map { Production(extractRuleProduction(it)) }

    private fun extractRuleProduction(ctx: ProductContext): List<Expression> {
        val productions = ctx.statement().map { extractStatement(it) }

        for (i in productions.indices) {
            val curr = productions[i]
            if (curr.type != ExpressionType.EPS && curr.id == 0) {
                var cnt = 1
                for (j in (i + 1) until productions.size) {
                    if (productions[i].name == productions[j].name) {
                        productions[j].id = cnt++
                    }
                }
            }
        }

        return productions
    }

    private fun extractStatement(ctx: StatementContext): Expression {
        val attributes = ctx.ARGS()?.text.orEmpty()
        val code = ctx.CODE()?.text.orEmpty()

        return when {
            ctx.TERMINAL() != null -> Expression(ctx.TERMINAL().text, 0, ExpressionType.TOKEN, attributes, code)
            ctx.NONTERM()  != null -> Expression(ctx.NONTERM().text,  0, ExpressionType.RULE,  attributes, code)
            else                   -> Expression(ctx.EPS().text,      0, ExpressionType.EPS,   attributes, code)
        }
    }

    private val rules    = extractRules(rulesCtx)
    private val rulesMap = rules.associateBy { it.name }

    private fun ruleByName(name: String) = rulesMap[name] ?: throw GeneratorException("Unmapped rule name")

    private fun addEpsToFirst() {
        var changed = true

        while (changed) {
            changed = false

            for (rule in rules) {
                for (prod in rule.prods) {
                    val firstExpr = prod.expressions.first()
                    if ((firstExpr.type == ExpressionType.EPS ||
                        (firstExpr.type == ExpressionType.RULE && ruleByName(firstExpr.name).first.contains(EPS))) &&
                        !rule.first.contains(EPS)) {

                        rule.first.add(EPS)
                        changed = true
                    }
                }
            }
        }
    }

    private fun constructFirst() {
        val used = mutableSetOf<Rule>()
        for (rule in rules) {
            if (!used.contains(rule)) {
                firstDFS(rule, used)
            }
        }
    }

    private fun firstDFS(rule: Rule, used: MutableSet<Rule>) {
        used.add(rule)

        for (prod in rule.prods) {
            for (expr in prod.expressions) {
                if (expr.type == ExpressionType.EPS) {
                    break
                }

                if (expr.type == ExpressionType.TOKEN) {
                    rule.first.add(expr.name)
                    break
                }

                if (!used.contains(ruleByName(expr.name))) {
                    firstDFS(ruleByName(expr.name), used)
                }

                rule.first.addAll(ruleByName(expr.name).first)

                if (!ruleByName(expr.name).first.contains(EPS)) {
                    break
                }
            }
        }
    }

    private fun getFirst(expressions: List<Expression>): MutableSet<String> {
        val result = mutableSetOf<String>()

        for (expr in expressions) {
            if (expr.type == ExpressionType.EPS) {
                result.add(EPS)
                break
            }

            if (expr.type == ExpressionType.TOKEN) {
                result.add(expr.name)
                break
            }

            result.addAll(ruleByName(expr.name).first)

            if (!result.contains(EPS)) {
                break
            }
        }

        return result
    }

    private fun constructFollow() {
        ruleByName(START).follow.add(END)

        var changed = true
        while (changed) {
            changed = false

            for (rule in rules) {
                for (prod in rule.prods) {
                    for ((i, expr) in prod.expressions.withIndex()) {
                        if (expr.type != ExpressionType.RULE) {
                            continue
                        }

                        val exprRule = ruleByName(expr.name)

                        val oldSize = exprRule.follow.size

                        if (i == prod.expressions.size - 1) {
                            exprRule.follow.addAll(rule.follow)
                        } else {
                            val follow = getFirst(prod.expressions.drop(i + 1))

                            if (follow.contains(EPS)) {
                                exprRule.follow.addAll(rule.follow)
                            }

                            exprRule.follow.addAll(follow - EPS)
                        }

                        changed = exprRule.follow.size != oldSize
                    }
                }
            }
        }
    }

    private fun buildParser(): String {
        val header = "package $packageName\n\n" +
                     "import ${packageName}.${grammarName}Lexer.Token.*"

        val decl = "class ${grammarName}Parser(private val lexer: ${grammarName}Lexer) {\n"
        val except = "    class ParserException(message: String) : Exception(message)\n\n"

        val init = "    init {\n" +
                   "        lexer.nextToken()\n" +
                   "    }\n\n"

        val tree = "    open class Tree(val nodeName: String) {\n" +
                   "         val children = mutableListOf<Tree>()\n" +
                   "    }\n"

        val termNode = "    class TerminalNode(nodeName: String, val text: String) : Tree(nodeName)\n\n"

        val parseFuns = "    fun parse (${ruleByName(START).attributes.joinToString { "${it.name}: ${it.type}" }}): StartContext {\n" +
                         "        val res = start(${ruleByName(START).attributes.joinToString { it.name }})\n\n" +
                         "        if (lexer.curToken == END) {\n" +
                         "            return res\n" +
                         "        } else {\n" +
                         "            throw ParserException(\"Unexpected ${'$'}{lexer.curToken} at the end of the input\")\n" +
                         "        }\n" +
                         "    }" +
                         "    ${addRuleFunctions()}" +
                         " }\n"
        val text = header + decl + except +
                   init + tree + termNode +
                   parseFuns

        return text
    }

    private fun addRuleFunctions() = rules.joinToString(separator = "\n", postfix = "\n") { rule ->
"""
${addRuleClass(rule)}

    fun ${rule.name}(${rule.attributes.joinToString { "${it.name}: ${it.type}" }}): ${rule.name.replaceFirstChar(Char::titlecase)}Context {
        val _localctx = ${rule.name.replaceFirstChar(Char::titlecase)}Context("${rule.name}"${
            rule.attributes.joinToString(separator = "") { ", ${it.name}" }})
        
        when (lexer.curToken) {
            ${addWhen(rule)}
        }
    }
"""
    }

    private fun addRuleClass(rule: Rule): String {
        val rulesAndTokens = mutableSetOf<String>()
        for (prod in rule.prods) {
            for (expr in prod.expressions) {
                var decl = "var ${expr.name}"
                if (expr.id != 0)
                    decl += "${expr.id}"

                if (expr.type == ExpressionType.RULE) {
                    rulesAndTokens.add("$decl: ${expr.name.replaceFirstChar(Char::titlecase)}Context? = null")
                } else if (expr.type == ExpressionType.TOKEN) {
                    rulesAndTokens.add("$decl: TerminalNode? = null")
                }
            }
        }

return """
    class ${rule.name.replaceFirstChar(Char::titlecase)}Context(name: String${rule.attributes.joinToString(separator = "") { 
            ", val ${it.name}: ${it.type}" 
    }}): Tree(name) {
            ${rule.retAttributes.joinToString(separator = "\n\t\t") { "var ${it.name}: ${it.type}? = null" }}
            ${rulesAndTokens.joinToString(separator = "\n\t\t")}
    }        
"""
    }

    private fun addWhen(rule: Rule): String {
        val sb = StringBuilder()
        var code = ""
        var hasEPS = false

        for (prod in rule.prods) {
            val exprFirst = getFirst(prod.expressions)
            hasEPS = exprFirst.remove(EPS)

            if (exprFirst.isEmpty()) {
                if (prod.expressions.first().code.isNotEmpty()) {
                    code = prod.expressions.first().code
                }
                continue
            }

            sb.append(exprFirst.joinToString())
            sb.appendLine(" -> {")

            for (expr in prod.expressions) {
                if (expr.type == ExpressionType.TOKEN) {
                    val name = if (expr.id == 0) expr.name else expr.name + expr.id
                    sb.appendLine(
"""
        if (lexer.curToken != ${expr.name}) {
            throw ParserException("${'$'}{lexer.curToken} unexpected in ${rule.name}")
        }
    
        val $name = TerminalNode("${expr.name}", lexer.curTokenText)
        _localctx.$name = ${expr.name}
        _localctx.children.add(${expr.name})
"""
                    )

                    if (expr.code.isNotEmpty()) {
                        sb.appendLine("\t\t\t\t" + expr.code.drop(2).dropLast(2).replace(CTX_ACCESS, "_localctx."))
                    }
                    sb.appendLine("\t\tlexer.nextToken()")
                } else {
                    val name = if (expr.id == 0) expr.name else expr.name + expr.id
                    sb.append("\t\t\t\tval $name = ${expr.name}(")
                    if (expr.attributes.isNotEmpty()) {
                        sb.append(expr.attributes.drop(1).dropLast(1).replace(CTX_ACCESS, "_localctx."))
                    }
                    sb.appendLine(")")

                    sb.appendLine(
"""
                _localctx.$name = $name
                _localctx.children.add($name)
"""
                    )

                    if (expr.code.isNotEmpty()) {
                        sb.appendLine("\t\t\t\t" + expr.code.drop(2).dropLast(2).replace(CTX_ACCESS, "_localctx."))
                    }
                }
            }

            sb.appendLine("\t\t\t\treturn _localctx")
            sb.appendLine("\t\t\t}")
        }

        if (hasEPS) {
            sb.append("\t\t\t" + rule.follow.joinToString())
            sb.appendLine(" -> {")

            if (code.isNotEmpty()) {
                sb.appendLine("\t\t\t\t" + code.drop(2).dropLast(2).replace(CTX_ACCESS, "_localctx."))
            }

            sb.appendLine("\t\t\t\treturn _localctx")
            sb.appendLine("\t\t\t}")
        }

        sb.append(
"""
            else -> throw ParserException("${'$'}{lexer.curToken} unexpected in ${rule.name}")
"""
        )

        return sb.toString()
    }

    fun generate(): String {
        addEpsToFirst()
        constructFirst()
        constructFollow()

        return buildParser()
    }
}