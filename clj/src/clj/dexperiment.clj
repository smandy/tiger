(ns argo.icetest)

; andy@raffles:/mnt/hdd/andy/repos/tiger/discovery$ ./Server --Ice.Config=config.server
(import com.zeroc.Ice.Current)
(import com.zeroc.Ice.Util)
(import com.zeroc.Ice.InitializationData)

(import argo.FooPrx)

(def communicator
  (let [iid (new InitializationData)
        props (Util/createProperties)]
    (set! (. iid properties) props)
    (Util/initialize iid)))

(def PROXY "foo:tcp -h ritz -p 1099")

(-> communicator
    (.stringToProxy PROXY)
    (.ice_ping))

(defn getFoo [communicator strPrx]
  (let [prx (.stringToProxy communicator strPrx )
        ret (FooPrx/checkedCast prx)]
    ret)) 

(getFoo communicator PROXY) 
;; (defn xs [foo]
;;   (doall (map (fn [x] (.sayHello hello foo) ) (range 1 2))))
;; (xs "Clojure3")

(.doit (getFoo communicator PROXY)) 
(.doitAgain (getFoo communicator PROXY))  




