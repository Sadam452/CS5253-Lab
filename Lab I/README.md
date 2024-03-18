# Lab I: Client-Server Communication

## Description:

This lab assignment focuses on implementing a simple client-server communication using Java socket programming.

## Features:

- **Client-Server Architecture:** The lab implements a client-server architecture where the client sends a message to the server, and the server receives and responds with reply message.
  
- **Socket Programming:** Java socket programming is used to establish communication between the client and server over the network.


## Files:

- **Client.java:** Contains the Java code for the client application. It establishes a connection with the server, sends the message, and receives the response.

- **Server.java:** Contains the Java code for the server application. It listens for incoming connections from clients, receives the message, and sends back the response.

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
   - After running the server, enter the message to be sent to the client.

5. **View Response:**
   - The server will receive the message from client and print it. The server will also send back the response, which will be displayed by the client.

## Requirements:

- Java Development Kit (JDK) installed on your system.
- Basic knowledge of Java programming and socket programming concepts.

## Contributing:

- Contributions to improve the implementation or fix any issues are welcome. Please fork the repository, make your changes, and submit a pull request.

## License:

- This project is licensed under the [MIT License](LICENSE).
