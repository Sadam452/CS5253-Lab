# Lab II: Secure Client-Server Communication with AES Encryption

## Description:

This lab assignment focuses on implementing a secure client-server communication using Java socket programming and encrypting the communication using the Advanced Encryption Standard (AES) algorithm.

## Features:

- **Client-Server Architecture:** The lab implements a client-server architecture where the client sends a message to the server, and the server receives and decrypts the message.
  
- **Socket Programming:** Java socket programming is used to establish communication between the client and server over the network.

- **AES Encryption:** The communication between the client and server is encrypted using the AES algorithm to ensure confidentiality.

## Files:

- **Client.java:** Contains the Java code for the client application. It establishes a connection with the server, sends an encrypted message, and receives the response.

- **Server.java:** Contains the Java code for the server application. It listens for incoming connections from clients, receives the encrypted message, decrypts it using AES, and sends back the response.

## Usage:

1. **Compile the Code:**
   ```
   javac Client.java
   javac Server.java
   ```

2. **Run the Server:**
   ```
   java Server
   ```

3. **Run the Client:**
   ```
   java Client
   ```

4. **Enter Message:**
   - After running the client, enter the message to be sent to the server.

5. **View Response:**
   - The server will decrypt the message, process it, and print it. The server will also send back the response, which will be displayed by the client.

## Requirements:

- Java Development Kit (JDK) installed on your system.
- Basic knowledge of Java programming and socket programming concepts.

## Contributing:

- Contributions to improve the implementation or fix any issues are welcome. Please fork the repository, make your changes, and submit a pull request.

## License:

- This project is licensed under the [MIT License](LICENSE).
