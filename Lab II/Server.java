import java.io.*;
import java.net.*;
import javax.crypto.*;
import javax.crypto.spec.*;
import java.util.Base64;
public class Server {
    private static final int PORT = 12345;
    private static final String SECRET_KEY = "12345678";

    public static void main(String[] args) {
        try {
            ServerSocket serverSocket = new ServerSocket(PORT);
            System.out.println("Server is running and listening on port " + PORT);

            while (true) {
                Socket clientSocket = serverSocket.accept();
                System.out.println("Client connected: " + clientSocket.getInetAddress().getHostAddress());

                //streams for communication
                BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
                PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);

                //encrypted message from client
                String encryptedMessage = in.readLine();
                System.out.println("Received encrypted message from client: " + encryptedMessage);

                // Decrypt message
                String decryptedMessage = decryptMessage(encryptedMessage);
                System.out.println("Decrypted message: " + decryptedMessage);

                //response back to client
                
                String message = "Message received.";
                message = encryptMessage(message);
                out.println(message);

                in.close();
                out.close();
                clientSocket.close();
                if(decryptedMessage.equals("exit")) break;
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
