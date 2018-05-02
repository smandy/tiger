
; andy@raffles:/mnt/hdd/andy/repos/tiger/discovery$ ./Server --Ice.Config=config.server
(import com.zeroc.Ice.Current)
(import com.zeroc.Ice.Util)
(import com.zeroc.Ice.InitializationData)

(import argo.FooPrx)
(import argo.TickListener)

(def communicator
    (Util/initialize (into-array String ["--Ice.Config=/home/andy/repos/tiger/clj/clojure.properties"])))

(def PROXY "plant")

(-> communicator
    (.stringToProxy PROXY)
    (.ice_ping))

(defn make-listener []
  (reify argo.TickListener
    (onTick [this ticks current] (println "onTick"))

    (onImage [this image current] (println "onImage"))
    ))

(make-listener)

(defn adapter [communicator]
  (doto (.createObjectAdapterWithEndpoints communicator "" "tcp")
    (.activate)))

(adapter communicator)

(.ice_ping (.stringToProxy communicator "plant"))

(let [
      my-adapter (adapter communicator)
      my-listener (make-listener)
      ident (.addWithUUID my-adapter my-listener)
      my-prx (argo.TickListenerPrx/checkedCast ident)
      prx (argo.TickerPlantPrx/checkedCast (.stringToProxy communicator "plant"))
      ]  (.subscribe prx my-prx))






      














