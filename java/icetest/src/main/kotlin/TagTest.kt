package foo

inline class MetaSyntactic( val value  : String)
fun doit(x : MetaSyntactic) {
    //x.toUpperCase()
}

fun main() {
    val xs : MetaSyntactic = "Foo" as MetaSyntactic
    val ys : MetaSyntactic = "Foo" as MetaSyntactic
    doit(xs)
    doit(ys)
}
