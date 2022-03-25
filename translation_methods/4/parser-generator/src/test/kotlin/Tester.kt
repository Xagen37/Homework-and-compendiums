import generated.*
import org.junit.jupiter.api.assertDoesNotThrow

import kotlin.test.Test
import kotlin.test.assertEquals
import kotlin.test.assertFails

internal class Tester {
    private fun runCalculatorParser(input: String): Int {
        return CalculatorParser(CalculatorLexer(input.byteInputStream())).parse().result
            ?: throw Exception("Unexpected null")
    }

    private fun runVariableParser(input: String) {
        KotlinVariableParser(KotlinVariableLexer(input.byteInputStream())).parse()
    }

    @Test
    fun `Calculator tests`() {
        assertEquals(4, runCalculatorParser("2 + 2"))
        assertEquals(-100, runCalculatorParser("- 100"))
        assertEquals(-8, runCalculatorParser("1 - 2 - 3 - 4"))
        assertEquals(26, runCalculatorParser("5 + 6 + 7 + 8"))
        assertEquals(10, runCalculatorParser("- ( - 10 )"))
        assertEquals(1, runCalculatorParser("10 / 2 / 5 / 1"))
        assertEquals(8, runCalculatorParser("1 * 2 + 2 * 3"))
        assertEquals(12, runCalculatorParser("1 * ( 2 + 2 ) * 3"))
        assertEquals(2, runCalculatorParser("[ 2 , 1 ]"))
        assertEquals(30, runCalculatorParser("( [ 4 , 2 ] - 3 ) * 10"))
        assertEquals(4, runCalculatorParser("480 / [ 10 , 3 ]"))
    }

    @Test
    fun `Variable tests`() {
        assertDoesNotThrow {
            runVariableParser("val c : Int = 0 ;")
            runVariableParser("val abacaba : Int = 0 ;")
            runVariableParser("val value : Int = 0 ;")
            runVariableParser("var c : Int ;")
            runVariableParser("var c : String ;")
            runVariableParser("var abacaba : Int = 0 ;")
            runVariableParser("var variable : Int = 0 ;")
        }

        assertFails { runVariableParser("val c : Int ;") }
        assertFails { runVariableParser("val c : String ;") }
        assertFails { runVariableParser("") }
        assertFails { runVariableParser("val : Int ;") }
        assertFails { runVariableParser("val value :  = 13 ;") }
        assertFails { runVariableParser("val c Int ;") }
    }
}