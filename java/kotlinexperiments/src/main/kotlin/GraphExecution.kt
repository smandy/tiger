package foo

class Graph {

    inner class Node( val name : String) {
        override fun toString() = "Node($name)"

        val children : List<Node>
            get() = edges
                    .filter { it.from.name == name }
                    .map { it.to }


        fun canFind(other : String) : Boolean = other==name || children.any { it.canFind(other) }
    }

    inner class Edge(val from : Graph.Node, val to : Graph.Node)

    fun getNode(s : String) : Graph.Node = nodes[s] ?: run {
        val ret = Node(s)
        nodes[s] = ret
        return ret
    }

    fun getOrCreateEdge( from : String, to : String) : Edge {
        return edges.find { it.from.name==from && it.to.name==to } ?: run {
            val ret = Edge( getNode(from), getNode(to))
            edges += ret
            return ret
        }
    }

    val nodes = mutableMapOf<String, Graph.Node>()

    val edges = mutableListOf<Edge>()

    override fun toString() : String = """
        |Graph(nodes=
        |${nodes.entries.joinToString(",\n", "[\n", "\n]") }
        |edges=
        |${edges.joinToString("\n", "[\n", "\n]")}
        |)
        """.trimMargin()
}


fun main(args: Array<String>) {
    val g = Graph()
    g.getOrCreateEdge("a", "b")
    g.getOrCreateEdge("b", "c")
    g.getOrCreateEdge("c", "d")
    println( g.getNode("a").canFind("d"))
    println( g.getNode("a").canFind("e"))
    println(g)
}
