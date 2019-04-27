package argo

import io.grpc.ManagedChannelBuilder
import io.grpc.examples.helloworld.GreeterGrpc
import io.grpc.examples.helloworld.HelloRequest

fun main() {
    val mc = ManagedChannelBuilder
            .forAddress("localhost", PORT)
            .usePlaintext().build()
    val bs = GreeterGrpc.newBlockingStub(mc)

    val request = HelloRequest.newBuilder()
            .apply {
                name = "Andy"
            }
            .build()

    val response = bs.sayHello(request)
    println("Greeting ${response.message}")
}