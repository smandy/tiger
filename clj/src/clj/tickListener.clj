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


(defn makeuuid [] (.toString (java.util.UUID/randomUUID)) )

;; (defn adapter []
;;   (let [ comm (communicator) ]
;;     (.createObjectAdapterWithEndpoints comm (makeuuid) "tcp")))

(defn adapter [comm]
    (.createObjectAdapterWithEndpoints comm (makeuuid) "tcp"))

(adapter (communicator))

(let [prx (.stringToProxy (communicator) "plant")
      ticker (argo.TickerPlantPrx/checkedCast prx)
      ret (.sayHello ticker)]
  ret)

(defn makeimpl [] (reify argo.TickListener
                    (onTick [this ticks current]
                      (printf "Got a tick woot %s\n" ticks)
                      )
                    ))

(defn doit []
  (let [
        comm (communicator)
        adp (adapter comm)
        my_prx (argo.TickListenerPrx/checkedCast (.addWithUUID adp (makeimpl)))
        prx (argo.TickerPlantPrx/checkedCast (.stringToProxy comm "plant"))
        ]
    (.activate adp)
    (.subscribe prx my_prx)))

(doit)
(makeimpl)

(let [ adp (adapter) ]
  adapter)


