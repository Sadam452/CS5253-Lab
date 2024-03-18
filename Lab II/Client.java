import java.io.*;
import java.net.*;
import javax.crypto.*;
import javax.crypto.spec.*;
import java.util.Base64;
import java.util.Scanner;

public class Client {
    private static final String SERVER_IP = "127.0.0.1";
    private static final int PORT = 12345;
    private static final String SECRET_KEY = "12345678";

    public static void main(String[] args) {
        try {
        while(true){
            Socket socket = new Socket(SERVER_IP, PORT);
            System.out.println("Connected to server");

            //streams for communication
            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            PrintWriter out = new PrintWriter(socket.getOutputStream(), true);

            //String message = "Hello from client";
            Scanner scanner = new Scanner(System.in);
	    System.out.print("Enter a message(exit to stop): ");
            String message = scanner.nextLine();
            // Encrypt message
            String encryptedMessage = encryptMessage(message);
            System.out.println("Encrypted message: " + encryptedMessage);

            // Send encrypted message to server
            out.println(encryptedMessage);

            // Receive response from server
            String response = in.readLine();
            System.out.println("Encrypted Server response: " + response);
            response = decryptMessage(response);
            System.out.println("Decrypted Server response: " + response);

            in.close();
            out.close();
            socket.close();
            if (message.equals("exit")) {
		    break;
		}
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static String encryptMessage(String message) {
        try {
            SecretKeySpec key = new SecretKeySpec(SECRET_KEY.getBytes(), "DES");
            Cipher cipher = Cipher.getInstance("DES/ECB/PKCS5Padding");
            cipher.init(Cipher.ENCRYPT_MODE, key);
            byte[] encryptedBytes = cipher.doFinal(message.getBytes());
            return Base64.getEncoder().encodeToString(encryptedBytes);
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }
        private static String decryptMessage(String encryptedMessage) {
        try {
            SecretKeySpec key = new SecretKeySpec(SECRET_KEY.getBytes(), "DES");
            Cipher cipher = Cipher.getInstance("DES/ECB/PKCS5Padding");
            cipher.init(Cipher.DECRYPT_MODE, key);
            byte[] decryptedBytes = cipher.doFinal(Base64.getDecoder().decode(encryptedMessage));
            return new String(decryptedBytes);
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }
}

