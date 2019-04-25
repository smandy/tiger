package foo

class Graph {
    inner class Node(val name : String) {
        var valid : Boolean = false

        override fun toString() = "Node($name)"

        val children: List<Node>
            get() = edges
                    .filter { it.from.name == name }
                    .map { it.to }

        fun canFind(other: String, depth: Int = 0): Int? {
            println("${this}.canFind $other $depth")
            return if (other == name) {
                depth
            } else {
                children
                        .mapNotNull { it.canFind(other) }
                        .min()
                        ?.let { it + 1 }
            }
        }

        fun canFind2(other : String, depth : Int = 0, visited : MutableMap<Node,List<Int>> = mutableMapOf()) : MutableMap<Node,List<Int>> {
            println("${this}.canFind2( $other, $depth, $visited")
            val otherNode = getNode(other)
            if ( other == name) {
                visited[otherNode] = visited[otherNode]?.let { it + depth } ?: listOf(depth)
            } else {
                children.forEach { it.canFind2(other, depth + 1, visited)}
            }
            return visited
        }

        fun invalidate() {
            valid = false
            children.forEach { it.invalidate() }
        }
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
    g.getOrCreateEdge("a", "c")

/*
    println(g.getNode("a").canFind("a"))
    println(g.getNode("a").canFind("b"))
    println(g.getNode("a").canFind("c"))
    println(g.getNode("a").canFind("d"))
    println(g.getNode("a").canFind("e"))
*/

    val g2 = Graph()
    g.getOrCreateEdge("a", "z")
    g.getOrCreateEdge("a", "b")
    g.getOrCreateEdge("b", "c")
    g.getOrCreateEdge("c", "d")
    g.getOrCreateEdge("d", "z")
    println(g2.getNode("a").canFind2("z"))
}
