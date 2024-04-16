import java.io.*;
import java.net.*;
import java.util.Scanner;

public class Client {
    private static final String SERVER_IP = "127.0.0.1";
    private static final int PORT = 12345;

    public static void main(String[] args) {
        try {
            while (true) {
                Socket socket = new Socket(SERVER_IP, PORT);
                System.out.println("Connected to server");

                // Streams for communication
                BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                PrintWriter out = new PrintWriter(socket.getOutputStream(), true);

                // Get user input
                Scanner scanner = new Scanner(System.in);
                System.out.print("Enter a message (exit to stop): ");
                String message = scanner.nextLine();

                System.out.println("Client: Message: " + message);

                // Send encrypted message to server
                out.println(message);

                // Receive response from server
                String response = in.readLine();
                System.out.println("Client: Server response: " + response);

                // Close streams and socket
                in.close();
                out.close();
                socket.close();

                // Check if user wants to exit
                if (message.equals("exit")) {
                    break;
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

