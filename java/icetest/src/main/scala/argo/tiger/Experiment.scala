package argo.tiger

import org.apache.logging.log4j.LogManager

object Experiment {
  val log = LogManager.getLogger(Experiment.getClass)

  def main(args : Array[String]) : Unit = {
    log.info("Woot " + args.mkString("[",",","]"))
    val communicator = Ice.Util.initialize(args)
    log.info("Communicator setup")
    val adapter = communicator.createObjectAdapter("SimpleJavaApp")
    adapter.activate()
    communicator.waitForShutdown()
    adapter.destroy()
    communicator.destroy()
    log.info("Exiting")
  }
}
