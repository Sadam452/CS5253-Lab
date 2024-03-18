import java.io.*;
import java.net.*;
import javax.crypto.*;
import javax.crypto.spec.*;
import java.util.Base64;
import java.util.Scanner;

class Server{
	private static final int port = 12345;
	public static void main(String[] args){
	
	try{
	ServerSocket sskt = new ServerSocket(port);
	System.out.println("Server is Live!");
	while(true){
		Socket skt = sskt.accept();
		System.out.println("Server-client connection established.");
		BufferedReader in = new BufferedReader(new InputStreamReader(skt.getInputStream()));
		PrintWriter out = new PrintWriter(skt.getOutputStream(), true);
		
		String rMsg = in.readLine();
		System.out.println("Received message: "+ rMsg);
		System.out.print("Enter message(exit to quit)");
		Scanner s = new Scanner(System.in);
		String msg = s.nextLine();
		
		out.println(msg);
		if(msg.equals("exit")) break;
		
		}
		}catch(IOException e){
		e.printStackTrace();
		}
	
	}
}
