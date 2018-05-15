package argo.tiger

import java.util.concurrent.{CompletableFuture, CompletionStage}

import argo.{Foo, FooPrx}
import com.zeroc.Ice.Current
import org.apache.logging.log4j.LogManager
import org.joda.time.DateTime
import com.zeroc.Ice

object MyFoo {
  val log = LogManager.getLogger( MyFoo.getClass)
}

class MyFoo extends Foo {
  import MyFoo._

  override def addAsync( a : Int, b : Int, x : Current) : CompletionStage[Integer] = {
    CompletableFuture.completedFuture( a + b )
  }

  override def doitAsync( __current: Current): CompletionStage[String] = {
    log.info("Hello from scala")
    CompletableFuture.completedFuture(s"Hello from scala!! ${new DateTime}")
  }

  override def doitAgainAsync(__current: Current): CompletionStage[String] = {
    log.info("Doit again")
    //cb.ice_response( s"Doit from scala agani ${new DateTime}")
    CompletableFuture.completedFuture( s"Doit from scala agani ${new DateTime}")
  }
}

object Experiment {
  val log = LogManager.getLogger(Experiment.getClass)

  def main(args : Array[String]) : Unit = {
    log.info("args are " + args.mkString("[",",","]"))

    val communicator = com.zeroc.Ice.Util.initialize(args)
    log.info("Communicator setup")
    val adapter = communicator.createObjectAdapter("SimpleJavaApp")
    val foo = new MyFoo()
    adapter.add( foo, Ice.Util.stringToIdentity("foo"))
    log.info("Activate adapter")
    adapter.activate()

    log.info("Wait for shutdown")
    communicator.waitForShutdown()

    log.info("Destroy adapter")
    adapter.destroy()

    val x = FooPrx.checkedCast(communicator.stringToProxy("foo@SimpleApp"))

    val x2 = x.doitAsync()
    val x4 = x2.get()

    log.info("Destroy communicator")
    communicator.destroy()
    log.info("Exiting")
  }
}
