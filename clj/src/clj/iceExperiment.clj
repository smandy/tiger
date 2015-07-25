(ns argo.icetest)

(import Ice.Util)

(import argo.Foo)
(import argo.FooPrx)
(import argo.FooPrxHelper)

(def communicator
  (let [iid (new Ice.InitializationData)
        props (doto (Ice.Util/createProperties)
          (.setProperty
           "Ice.Plugin.IceLocatorDiscovery"  "IceLocatorDiscovery:IceLocatorDiscovery.PluginFactory")
          ;; (.setProperty "Ice.Trace.Network"  "2")
          ;; (.setProperty "Ice.Trace.Protocol" "3")
          (.setProperty "Ice.Default.EndpointSelection" "Ordered")
          )]
     (set! (. iid properties) props)
     (Ice.Util/initialize iid)))

(defn getFoo [communicator strPrx]
  (let [prx (.stringToProxy communicator strPrx )
        ret (FooPrxHelper/checkedCast prx)]
    ret))

(defn foo [] (print "Woot"))

(.doit (getFoo communicator "foo@SimpleCppApp" ))
(.doit (getFoo communicator "foo@SimpleApp"    ))
(.doit (getFoo communicator "foo@SimpleJavaApp"))

;; (def x (getFoo communicator "foo@SimpleJavaApp") )

(def myFoo2 (getFoo communicator "foo@SimpleCppApp" ) )
(def res  (.begin_doitAgain myFoo2))

(.end_doitAgain   myFoo2 res )

(.doitAgain (getFoo communicator "foo@SimpleApp"    ))
(.doitAgain (getFoo communicator "foo@SimpleJavaApp"))

(-> communicator
    (.stringToProxy "foo@SimpleApp")
    (.ice_ping))






