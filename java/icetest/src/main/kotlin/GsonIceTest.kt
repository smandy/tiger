package foo

import Demo.TestObject
import com.google.gson.Gson

fun main() {
    val myJson = """
        |{
        |     'hello' : 'there',
        |     'xs' : 10,
        |     'strings' : ['foo','bar','baz'],
        |     'ints' : { 10 : 'ten',
        |                20 : 'twenty' }
        |}
    """.trimMargin()

    val gson = Gson()
    val myObj = gson.fromJson(myJson, TestObject::class.java)
    println("Obj is ${myObj.hello} ${myObj.xs} ${myObj.strings.joinToString(",", "[","]")} ${myObj.ints}")
}
