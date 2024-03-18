import java.io.*;
import java.net.*;
import javax.crypto.*;
import javax.crypto.spec.*;
import java.security.Key;
import java.util.Base64;
import java.util.Scanner;

public class Client {
    private static final String SERVER_IP = "127.0.0.1";
    private static final int PORT = 12345;
    private static final String ALGORITHM = "AES";
    private static final byte[] keyValue = new byte[] { 'T', 'h', 'i', 's', 'I', 's', 'A', 'S', 'e', 'c', 'r','e', 't', 'K', 'e', 'y' };

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
            String encryptedMessage = "";
            try{
            encryptedMessage = encrypt(message);
            System.out.println("Encrypted message: " + encryptedMessage);
            }catch (Exception e){
            System.err.println("Error encrypting response message: " + e.getMessage());
            }

            // Send encrypted message to server
            out.println(encryptedMessage);

            // Receive response from server
            String response = in.readLine();
            System.out.println("Encrypted Server response: " + response);
            try{
            response = decrypt(response);
            System.out.println("Decrypted Server response: " + response);
            }catch(Exception e){
            System.err.println("Error encrypting response message: " + e.getMessage());
            }

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
    public static String encrypt(String data) throws Exception {
	    Key key = generateKey();//generation dinamic 
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

