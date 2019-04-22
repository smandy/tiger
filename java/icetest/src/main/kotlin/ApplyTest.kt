package foo

import com.google.gson.reflect.TypeToken
import com.zeroc.Ice.Util
import kotlin.reflect.KProperty

class Foo2 {
    var x : Int = 0
    var y : Int = 0
}

class DodgyInt {
    var _value = 10

    operator fun getValue(nothing: Nothing?, property: KProperty<*>): Int {
        println("getValue $nothing $property")
        return _value
    }

    operator fun setValue(nothing: Nothing?, property: KProperty<*>, i: Int) {
        println("setValue $nothing $property $i")
        _value = i
    }
}

fun main() {

    val f = Foo2()
    var myInt2 : Int by DodgyInt()
    println("myInt is $myInt2")
    myInt2 = 23
    println("myInt2 is $myInt2")
    f.apply {
        x = 10
        y = 20
    }

    val x = Util.initialize(emptyArray()).let {
        it.createObjectAdapter("")
        2
    }

    val x2 = Util.initialize(emptyArray()).run {
        createObjectAdapter("")
        2
    }

    val x3 = Util.initialize(emptyArray()).apply {
        createObjectAdapter("")
    }

    val x4 = Util.initialize(emptyArray()).also {
        println("Woot it is $it")
    }

    val myInt : Int by lazy {
        10
    }
}


