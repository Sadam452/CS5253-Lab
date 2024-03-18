import java.io.*;
import java.net.*;
import javax.crypto.*;
import javax.crypto.spec.*;
import java.security.Key;
import java.util.Base64;
public class Server {
    private static final int PORT = 12345;
    private static final String ALGORITHM = "AES";
    private static final byte[] keyValue = new byte[] { 'T', 'h', 'i', 's', 'I', 's', 'A', 'S', 'e', 'c', 'r','e', 't', 'K', 'e', 'y' };

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
                String decryptedMessage;
                try {
                decryptedMessage = decrypt(encryptedMessage);
                System.out.println("Decrypted message: " + decryptedMessage);
                } catch (Exception e) {
                System.err.println("Error decrypting message: " + e.getMessage());
                continue; // Skip processing if decryption fails
                }

                //response back to client
                
                try {
                String message = "Message received.";
                message = encrypt(message);
                out.println(message);
                } catch (Exception e) {
                System.err.println("Error encrypting response message: " + e.getMessage());
                }

                in.close();
                out.close();
                clientSocket.close();
                if(decryptedMessage.equals("exit")) break;
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    
    public static String encrypt(String data) throws Exception {
	    Key key = generateKey(); 
	    Cipher c = Cipher.getInstance(ALGORITHM);
	    c.init(Cipher.ENCRYPT_MODE, key);
	    byte[] encVal = c.doFinal(data.getBytes());
	    return Base64.getEncoder().encodeToString(encVal);
    }
    private static Key generateKey() throws Exception {
    	return new SecretKeySpec(keyValue, ALGORITHM);
    }
    public static String decrypt(String encryptedData) throws Exception {
	    Key key = generateKey();
	    Cipher c = Cipher.getInstance(ALGORITHM);
	    c.init(Cipher.DECRYPT_MODE, key);
	    byte[] decodedValue = Base64.getDecoder().decode(encryptedData);
	    byte[] decVal = c.doFinal(decodedValue);
	    return new String(decVal);
    }
}
