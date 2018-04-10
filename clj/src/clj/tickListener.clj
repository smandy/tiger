(ns argo.icetest)

; andy@raffles:/mnt/hdd/andy/repos/tiger/discovery$ ./Server --Ice.Config=config.server

(import com.zeroc.Ice.Current)
(import com.zeroc.Ice.Util)
(import com.zeroc.Ice.InitializationData)

(import argo.TickListenerPrx)
(import argo.TickListener))

(defn communicator []
  (let [iid (new InitializationData)
        props (doto (Util/createProperties)
                (.setProperty "Ice.Plugin.IceDiscovery"  "IceDiccovery:com.zeroc.IceDiscovery.PluginFactory")
                ;;(.setProperty "Ice.Default.EndpointSelection" "Ordered")
                ;;(.setProperty "Ice.Warn.Connections" "0")
                (.setProperty "Ice.Trace.Network"  "1")
                ;;(.setProperty "Ice.Trace.Protocol"  "0"))
                ;;(.setProperty "IceDiscovery.DomainId"  "argo"))
                )] 
    (set! (. iid properties) props)
    (Util/initialize iid)))

(defn adapter []
  (let [ comm (communicator) ]
    (.createObjectAdapterWithEndpoints comm "tcp")))

(adapter)

(let [prx (.stringToProxy (communicator) "plant")
      ticker (argo.TickerPlantPrx/checkedCast prx)
      ret (.sayHello ticker)]
  ret)

(defn makeimpl [] (reify argo.TickListener
                    (onTick [this ticks current]
                      (println "Got a tick woot")
                      )
                    ))

(defn doit []
  (let [
        adp (adapter)
        prx (argo.TickListenerPrx/checkedCast (.addWithUUID adp (makeimpl)))
        ] ) )

(doit)

(makeimpl)


(let [ adp (adapter) ]
  adapter)


