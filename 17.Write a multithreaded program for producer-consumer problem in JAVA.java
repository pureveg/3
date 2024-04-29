import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;

public class ProducerConsumer {
    private static final int BUFFER_SIZE = 5;
    private static BlockingQueue<Integer> buffer = new ArrayBlockingQueue<>(BUFFER_SIZE);

    public static void main(String[] args) {
        Thread producerThread = new Thread(new Producer());
        Thread consumerThread = new Thread(new Consumer());

        producerThread.start();
        consumerThread.start();
    }

    static class Producer implements Runnable {
        @Override
        public void run() {
            try {
                int i = 0;
                while (true) {
                    buffer.put(i);
                    System.out.println("Produced: " + i);
                    i++;
                    Thread.sleep(1000); // Simulating some delay
                }
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    static class Consumer implements Runnable {
        @Override
        public void run() {
            try {
                while (true) {
                    int value = buffer.take();
                    System.out.println("Consumed: " + value);
                    Thread.sleep(2000); // Simulating some processing time
                }
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
