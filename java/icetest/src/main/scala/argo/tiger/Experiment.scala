package argo.tiger

import Ice.Current
import argo.{AMD_Foo_doit, AMD_Foo_doitAgain, FooPrxHelper, _FooDisp}
import org.apache.logging.log4j.LogManager
import org.joda.time.DateTime

object MyFoo {
  val log = LogManager.getLogger( MyFoo.getClass)
}

class MyFoo extends _FooDisp {
  import MyFoo._



  override def doit_async(cb: AMD_Foo_doit, __current: Current): Unit = {
    log.info("Doit from scala")
    cb.ice_response( s"Doit from scala ${new DateTime}")
  }

  override def doitAgain_async(cb: AMD_Foo_doitAgain, __current: Current): Unit = {
    log.info("Doit again")
    cb.ice_response( s"Doit from scala agani ${new DateTime}")
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

    val x = FooPrxHelper.checkedCast( communicator.stringToProxy("foo@SimpleApp") )

    val x2 = x.begin_doit()
    val x4 = x.end_doit(x2)

    log.info("Destroy communicator")
    communicator.destroy()
    log.info("Exiting")
  }
}
