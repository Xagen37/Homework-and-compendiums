enum class ExpressionType {
    RULE, TOKEN, EPS
}

data class Expression(
    val name: String,
    var id: Int,
    val type: ExpressionType,
    val attributes: String,
    val code: String
)

data class Attribute(val type: String, val name: String)

data class Production(val expressions: List<Expression>)

data class Rule(
    val name: String,
    val attributes: List<Attribute>,
    val retAttributes: List<Attribute>,
    val prods: List<Production>,
    val first: MutableSet<String> = mutableSetOf(),
    val follow: MutableSet<String> = mutableSetOf()
)

class GeneratorException(message: String) : Exception(message)
