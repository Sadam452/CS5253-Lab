import java.io.*;
import java.net.*;
import java.util.Scanner;

public class Peer1 {

    private static final int PORT = 12345;

    public static void main(String[] args) {
        try {
            // Initialize socket for receiving messages
            DatagramSocket socket = new DatagramSocket(PORT);
            System.out.println("Peer1 is waiting for connection...");

            // Create a thread to handle incoming messages
            Thread receiveThread = new Thread(() -> {
                try {
                    while (true) {
                        byte[] buffer = new byte[1024];
                        DatagramPacket packet = new DatagramPacket(buffer, buffer.length);
                        socket.receive(packet);
                        String message = new String(packet.getData(), 0, packet.getLength());
                        System.out.println("Peer1: Message from " + packet.getAddress().getHostAddress() + ": " + message);
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                }
            });
            receiveThread.start();

            // Send messages to other peers
            Scanner scanner = new Scanner(System.in);
            while (true) {
                System.out.print("Peer1: Enter a message (exit to stop): ");
                String message = scanner.nextLine();
                byte[] buffer = message.getBytes();
                DatagramPacket packet = new DatagramPacket(buffer, buffer.length, InetAddress.getByName("0.0.0.0"), PORT);
                socket.send(packet);

                if (message.equals("exit")) {
                    break;
                }
            }

            // Close the socket
            socket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

