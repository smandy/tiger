(ns argo.icetest)

(import Ice.Util)
(import Demo.Hello)
(import Demo.HelloPrx)
(import Demo.HelloPrxHelper)

(def communicator
  (let [iid (new Ice.InitializationData)
        props (doto (Ice.Util/createProperties)
          (.setProperty "Ice.Plugin.Discovery"  "IceLocatorDiscovery:IceDiscovery.PluginFactory")
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

(def hello (getHello communicator "hello"))

(def xs (map (fn [x] (.sayHello hello (format "Wayhey %s" x)) ) (range 1 10)) )

(map println xs)
