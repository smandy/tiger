package argo.tiger

import Ice.Current
import argo._FooDisp
import org.apache.logging.log4j.LogManager


object MyFoo {
  val log = LogManager.getLogger( MyFoo.getClass)
}

class MyFoo extends _FooDisp {
  import MyFoo._

  override def doit(__current: Current): String = {
    log.info("doit from scala")
    "Doit from scala"
  }

  override def doitAgain(__current: Current): String = {
    log.info("doitAgain from scala")
    "doitAgain from scala"
  }
}

object Experiment {
  val log = LogManager.getLogger(Experiment.getClass)

  def main(args : Array[String]) : Unit = {
    log.info("args are " + args.mkString("[",",","]"))
    val communicator = Ice.Util.initialize(args)
    log.info("Communicator setup")
    val adapter = communicator.createObjectAdapter("SimpleJavaApp")
    val foo = new MyFoo()
    adapter.add( foo, communicator.stringToIdentity("foo"))
    log.info("Activate adapter")
    adapter.activate()

    log.info("Wait for shutdown")
    communicator.waitForShutdown()

    log.info("Destroy adapter")
    adapter.destroy()

    log.info("Destroy communicator")
    communicator.destroy()
    log.info("Exiting")
  }
}
