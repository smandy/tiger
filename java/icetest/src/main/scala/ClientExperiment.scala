import argo.FooPrx
import com.zeroc.Ice.Util

object ClientExperiment {
  def main(args: Array[String]): Unit = {
    val iid = new com.zeroc.Ice.InitializationData
    val props = Util.createProperties
    props.setProperty("Ice.Plugin.IceLocatorDiscovery", "com.zeroc.IceLocatorDiscovery.PluginFactory")
    iid.properties = props
    val communicator = Util.initialize(iid)

    val results = for {
      app <- List("CppApp", "App", "DApp", "JavaApp")
    } yield {
      val prx = FooPrx.uncheckedCast(communicator.stringToProxy(s"foo@Simple$app"))
      val ret = prx.add(2, 3)
      (prx.doit(), prx.doitAgain(), prx.add(2, 3))
    }
    println(s"""results are ${results.mkString("[", "\n", "]")}""")

    // Need destroy to shut down the client side functionality apparently
    println("Destroying")
    communicator.destroy()
    println("destroyed")
    //communicator.waitForShutdown()
    //println("Have shutdown")
    //communicator.destroy()
    import scala.collection.JavaConverters._
    val xxx = Thread.getAllStackTraces.keySet.asScala foreach println
  }
}
