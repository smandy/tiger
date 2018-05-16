(ns argo.icetest)

(import com.zeroc.Ice.Current)
(import com.zeroc.Ice.Util)
(import com.zeroc.Ice.InitializationData)

(import argo.Foo)
(import argo.FooPrx)

(defn communicator []
  (let [iid (new com.zeroc.Ice.InitializationData)
        props (doto (com.zeroc.Ice.Util/createProperties)
          (.setProperty "Ice.Plugin.IceLocatorDiscovery"  "com.zeroc.IceLocatorDiscovery.PluginFactory")
          ;; (.setProperty "IceLocatorDiscovery.InstanceName" "tiger1")
          ;; (.setProperty "Ice.Trace.Network"  "2")
          ;; (.setProperty "Ice.Trace.Protocol" "3")
          ;; (.setProperty "Ice.Default.EndpointSelection" "Ordered")
          )]
     (set! (. iid properties) props)
     (com.zeroc.Ice.Util/initialize iid)))

(defn getFoo [strPrx]
  (let [prx (.stringToProxy (communicator) strPrx )
        ret (FooPrx/checkedCast prx)]
    ret))

;; NB Don't mix icediscovery with locatoriscovery.  They seem to
;; conflict.  If you want to chat to the grid *only* use
;; icelocatordiscovery
(.doit (getFoo "foo@SimpleCppApp"))
(.doit (getFoo "foo@SimpleApp"))
(.doit (getFoo "foo@SimpleJavaApp"))
(.doit (getFoo "foo@SimpleDApp"))

(.add (getFoo "foo@SimpleCppApp") 20 30)
(.add (getFoo "foo@SimpleApp") 3 5) 
(.add (getFoo "foo@SimpleJavaApp") 10 20)
(.add (getFoo "foo@SimpleDApp") 10 50)

(defn multiadd [a b]
  (->>  (list "App"
             "CppApp"
             "JavaApp"
            "DApp")
       (map #(format "foo@Simple%s" %))
       (map getFoo)
       (map #(.add % a b))))

(defn betteradd [ a b ]
  (let
      [ comm (communicator) ]
    (->> (list "App"
               "App"
               "CppApp"
               "JavaApp"
               "DApp")
         (map #(format "foo@Simple%s" %))
         (pmap #(.stringToProxy comm %))
         (pmap #(FooPrx/uncheckedCast %))
         (pmap #(.add % a b)))))

(multiadd 12 22)
(betteradd 3 4)

(defn square [x] (* x x))

(->> (range 1 100)
     (map square)
     (filter #(> 50 %))
     (map #(format "Bla %s" %)))

(as-> (range 1 100) it
     (map square it)
     (filter #(> 50 %) it)
     (map #(format "Bla %s" %) it))

(def myFoo2 (getFoo "foo@SimpleCppApp"))
(def res (.begin_doitAgain myFoo2))
(.end_doitAgain myFoo2 res)

(.doitAgain (getFoo "foo@SimpleApp"))
(.doitAgain (getFoo "foo@SimpleJavaApp"))
(.doitAgain (getFoo "foo@SimpleDApp"))
(.doitAgain (getFoo "foo@SimpleCppApp"))

(-> (communicator)
    (.stringToProxy "foo@SimpleApp")
    (.ice_ping))
