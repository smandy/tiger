(ns argo.icetest)

// andy@raffles:/mnt/hdd/andy/repos/tiger/discovery$ ./Server --Ice.Config=config.server

(import Ice.Util)
(import Demo.Hello)
(import Demo.HelloPrx)
(import Demo.HelloPrxHelper)

(def communicator
  (let [iid (new Ice.InitializationData)
        props (doto (Ice.Util/createProperties)
                (.setProperty "Ice.Plugin.Discovery"  "IceLocatorDiscovery:IceDiscovery.PluginFactory")
                (.setProperty "Ice.Trace.Network"  "2")
                (.setProperty "Ice.Trace.Protocol"  "2")

                (.setProperty "IceDiscovery.DomainId"  "argo")
                (.setProperty "IceDiscovery.Address"   "239.255.1.2")

                ;;(.setProperty "IceLocatorDiscovery.InstanceName" "tiger1")
                ;; (.setProperty "Ice.Default.EndpointSelection" "Ordered")
                )]
    (set! (. iid properties) props)
    (Ice.Util/initialize iid)))

(-> communicator
    (.stringToProxy "hello")
    (.ice_ping) )

(defn getHello [communicator strPrx]
  (let [prx (.stringToProxy communicator strPrx )
        ret (HelloPrxHelper/checkedCast prx)]
    ret))

(getHello communicator "hello")

;; (defn xs [foo]
;;   (doall (map (fn [x] (.sayHello hello foo) ) (range 1 2))))
;; (xs "Clojure3")

(.sayHello (getHello communicator "hello") "dude")




