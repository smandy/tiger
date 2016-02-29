import java.io.File

import scala.io.Source

sealed trait Direction

case object Left extends Direction
case object Right extends Direction
case class DirectedEdge(direction : Direction, parent : String, child : String)

object Graph {
  def printToFile(f: java.io.File)(op: java.io.PrintWriter => Unit) {
    val p = new java.io.PrintWriter(f)
    try { op(p) } finally { p.close() }
  }

  val simpleGraph = Source.fromInputStream(ClassLoader.getSystemResourceAsStream("example.gl")).getLines()

  def main( args : Array[String]) : Unit = {
    val directedEdges: List[DirectedEdge] = simpleGraph
      .filter( x => !x.startsWith("#"))
      .toList
      .map(x => x.split(" "))
      .filter(_.length == 3)
      .map {
        case Array(a, ">", b) => DirectedEdge(Right, a, b)
        case Array(a, "<", b) => DirectedEdge(Left, a, b)
        case x => { println(s"Cant match ${x.toList}"); require(false); null}
      }

    val g = new Graph(directedEdges)

    g.nodes.values
      .toList
      .sortBy(_.depth)
      .foreach(println)

    println(s"Have $g.graphIdentities")
    g.graphNodesToFile(g.nodes.map(_._2), "/home/andy/attempt1.dot")
    for {
      (lr, roots) <- g.graphIdentities
    } {
      val nodes = g.nodes.values.filter(_.roots.forall(lr.contains)).toList
      val mnemonic = lr.seq.map(_.s).toList.sorted.mkString("", "", "")
      val nodeMnemonic = nodes.map(_.s).toList.sorted.mkString("", "", "")
      println(s"Have ${nodes.size} for linked roots $mnemonic $nodeMnemonic")
      val fn = s"/home/andy/graph_$mnemonic.dot"
      g.graphNodesToFile(nodes, fn)
      println(s"Wrote $fn")
    }
  }
}

class Graph( edges : List[DirectedEdge]) {
  import Graph.printToFile

  var nodes = Map[String,TmpNode]()

  def getNode( s : String ) = nodes get s match {
    case Some(node) => node
    case None => {
      val ret = new TmpNode(s)
      nodes += ( s -> ret)
      ret
    }
  }

  for {
    de @ DirectedEdge(direction, parent, child) <- edges
  } {
    val pp = getNode(parent)
    val pc = getNode(child)
    require( !pc.canReach(pp), s"Directed edge $de introduces cyclic dependency between $parent <-> $child")
    pc.isRoot = false
    direction match {
      case Right => pp.rhs = Some(pc)
      case Left  => pp.lhs = Some(pc)
    }
  }

  val rootNodes = nodes.values.filter(_.isRoot)


  println( edges)
  println(s"Nodes are $edges")

  // Danger - mutation
  rootNodes.foreach(x => x.addRoot(x))

  println(s"Have ${rootNodes.size} root nodes" )
  println(s"Have ${rootNodes.size} root nodes" )

  lazy val graphIdentities = rootNodes.groupBy( _.linkedRoots)

  def graphNodesToFile( xs : Iterable[TmpNode], fn : String) {
    val quot = "\""
    printToFile(new File(fn)) { pw => {
      pw.println("digraph Foo { ")
      for {
        x <- xs
      } {
        x.rhs.map(rhs => pw.println(s"  ${x.s} -> ${rhs.s};"))
        x.lhs.map(lhs => pw.println(s"  ${x.s} -> ${lhs.s};"))
      }
      pw.println("}")
    }
    }
  }

  class TmpNode( val s : String) {
    def mnem( x : Option[TmpNode]) = x.map(_.s).getOrElse("None")

    var isRoot = true

    var rhs : Option[TmpNode] = None
    var lhs : Option[TmpNode] = None
    var roots = Set[TmpNode]()

    def canReach( x : TmpNode) : Boolean = {
      def reachable( side : Option[TmpNode]) : Boolean = side match {
        case None => false
        case Some(n) => x==n || n.canReach(x)
      }
      reachable(rhs) || reachable(lhs)
    }

    def addRoot(x : TmpNode) : Unit = {
      roots += x
      rhs.foreach( _.addRoot(x))
      lhs.foreach( _.addRoot(x))
    }

    lazy val linkedRoots : Set[TmpNode] = {
      def getLinkedRoots( x : Option[TmpNode] ) = x.map( _.linkedRoots).getOrElse( Set.empty[TmpNode])
      roots ++ getLinkedRoots(lhs) ++ getLinkedRoots(rhs)
    }

    lazy val linkedRootsList = linkedRoots.map(_.s)

    lazy val childNodes : List[TmpNode] = rhs.toList ++ lhs.toList

    lazy override val toString = s"TmpNode($s,isRoot=$isRoot,d=$depth,roots=${roots.size},l=${mnem(lhs)}, r=${mnem(rhs)},lr=${linkedRootsList} )"

    lazy val depth : Int = (rhs, lhs) match {
      case (None,None) => 1
      case x => childNodes.map(_.depth).max + 1
    }
  }
}
