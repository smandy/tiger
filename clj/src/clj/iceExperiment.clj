(ns argo.icetest)

(import Ice.Util)

(import argo.Foo)
(import argo.FooPrx)
(import argo.FooPrxHelper)

(def communicator
  (let [iid (new Ice.InitializationData) 
        props
        (doto (Ice.Util/createProperties )
          (.setProperty
           "Ice.Plugin.IceLocatorDiscovery"
           "IceLocatorDiscovery:IceLocatorDiscovery.PluginFactory"
           )
          )
        ]
     (set! (. iid properties) props)
     (Ice.Util/initialize iid )
     )
  )

(defn getFoo [communicator strPrx]
  (let [
        prx (.stringToProxy communicator strPrx )
        ret (FooPrxHelper/checkedCast prx)
        ]
    ret) )

(.doit (getFoo communicator "foo@SimpleCppApp"))
(.doit (getFoo communicator "foo@SimpleApp"))
(.doit (getFoo communicator "foo@SimpleJavaApp"))

(-> communicator
    (.stringToProxy "foo@SimpleApp")
    (.ice_ping))






