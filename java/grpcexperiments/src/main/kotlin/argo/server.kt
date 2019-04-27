package argo

import io.grpc.ServerBuilder
import io.grpc.examples.helloworld.GreeterGrpc
import io.grpc.examples.helloworld.HelloReply
import io.grpc.examples.helloworld.HelloRequest
import io.grpc.stub.StreamObserver
import java.util.concurrent.Executors
import java.util.concurrent.TimeUnit


val executor = Executors.newSingleThreadScheduledExecutor()

class MyGreeter : GreeterGrpc.GreeterImplBase() {
    override fun sayHello(request: HelloRequest?, responseObserver: StreamObserver<HelloReply>?) {
        val reply = HelloReply.newBuilder()
                .setMessage("Woohoo ya langer ${request?.name}")
                .build()
        responseObserver?.onNext(reply)
        responseObserver?.onCompleted()
    }

    override fun sayHelloAgain(request: HelloRequest?, responseObserver: StreamObserver<HelloReply>?) {
        val reply = HelloReply.newBuilder()
                .setMessage("You again ? ${request?.name}")
                .build()
        executor.schedule( {
            responseObserver?.onNext(reply)
            responseObserver?.onCompleted()
        }, 100, TimeUnit.MILLISECONDS)
    }
}

fun main() {
    /// TODO - logging
    println("Starting up")
    ServerBuilder
            .forPort(PORT)
            .addService(MyGreeter())
            .build()
            .start()
            .awaitTermination()
}