import java.io.*;
import java.net.*;
import javax.crypto.*;
import javax.crypto.spec.*;
import java.util.Base64;
import java.util.Scanner;

class Client{
	private static final String server_ip = "127.0.0.1";
	private static final int port = 12345;
	public static void main(String[] args){
	try{
	while(true){
		Socket skt = new Socket(server_ip, port);
		System.out.println("Connected to server.");
		BufferedReader in = new BufferedReader(new InputStreamReader(skt.getInputStream()));
		PrintWriter out = new PrintWriter(skt.getOutputStream(), true);
		
		System.out.print("Enter message(exit to quit)");
		Scanner s = new Scanner(System.in);
		String msg = s.nextLine();
		out.println(msg);
		
		String rMsg = in.readLine();
		System.out.println("Received message: "+ rMsg);
		
		if(msg.equals("exit")) break;
		
		}
		}catch(IOException e){
		e.printStackTrace();
		}
	
	}
}
