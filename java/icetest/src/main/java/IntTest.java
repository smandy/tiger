import java.util.ArrayList;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.ScheduledExecutorService;

public class IntTest {
    public static void main(String[] args) throws InterruptedException, ExecutionException {
        new IntTest().doWork();
    }

    volatile Integer i = 0;

    private void doWork() throws InterruptedException, ExecutionException {
        ScheduledExecutorService scheduledExecutorService = Executors.newScheduledThreadPool(10);
        ArrayList<Future> tasks = new ArrayList<>();
        for(int j = 0 ; j < 1_000_000;j++) {
            tasks.add(scheduledExecutorService.submit(() -> {
                i += 1;
                if (i % 1000 ==0) {
                    System.out.println("I is " + i);
                }
            }) );
        }

        for( Future task : tasks) {
            int recv = 0;
            task.get();
            if (++recv % 1000 == 0) {
                System.out.println("Received " + recv);
            }
        }
        System.out.println(" I us " + i);
    }
}

