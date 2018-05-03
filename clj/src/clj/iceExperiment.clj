(ns argo.icetest)

(import com.zeroc.Ice.Current)
(import com.zeroc.Ice.Util)
(import com.zeroc.Ice.InitializationData)

(import argo.Foo)
(import argo.FooPrx)

(def communicator
  (let [iid (new com.zeroc.Ice.InitializationData)
        props (doto (com.zeroc.Ice.Util/createProperties)
          (.setProperty "Ice.Plugin.IceLocatorDiscovery"  "com.zeroc.IceLocatorDiscovery.PluginFactory")
          ;; (.setProperty "IceLocatorDiscovery.InstanceName" "tiger1")
          ;; (.setProperty "Ice.Trace.Network"  "2")
          ;; (.setProperty "Ice.Trace.Protocol" "3")
          ;;(.setProperty "Ice.Default.EndpointSelection" "Ordered")
          )]
     (set! (. iid properties) props)
     (com.zeroc.Ice.Util/initialize iid)))

(defn getFoo [communicator strPrx]
  (let [prx (.stringToProxy communicator strPrx )
        ret (FooPrx/checkedCast prx)]
    ret))

(defn foo [] (print "Woot"))

(.doit (getFoo communicator "foo@SimpleCppApp" ))
(.doit (getFoo communicator "foo@SimpleApp"    ))
(.doit (getFoo communicator "foo@SimpleJavaApp"))
(.doit (getFoo communicator "foo@SimpleDApp"))

;; (def x (getFoo communicator "foo@SimpleJavaApp") )

(def myFoo2 (getFoo communicator "foo@SimpleCppApp" ) )
(def res  (.begin_doitAgain myFoo2))

(.end_doitAgain   myFoo2 res )

(.doitAgain (getFoo communicator "foo@SimpleApp"    ))
(.doitAgain (getFoo communicator "foo@SimpleJavaApp"))

(-> communicator
    (.stringToProxy "foo@SimpleApp")
    (.ice_ping))
