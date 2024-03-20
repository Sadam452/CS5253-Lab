# Mid Semester Questions

## Question 1: Railway Signalling System

### Overview
Implement a Railway Signalling system as a client-server model using socket programming. The communication between the station master and the platform needs to be encrypted and decrypted using the DES algorithm. If you are using C, use the encryption library routines that are part of OpenSSL. If you are using Java, use the library routines in the Java Cryptography Extension.

### Tasks
1. **Informing Train Arrival:**
   - The station master informs the platform about the arrival of a train.

2. **Changing Signal to Red:**
   - The platform changes the signal to red and communicates the same to the station master.

3. **Order of Compartments:**
   - The station master sends the order of the compartments in the train to the platform, which is displayed on the platform.

4. **Platform Occupied Notification:**
   - Once the train has arrived, the platform informs the station master that the platform is occupied.

### Implementation Details
- Use socket programming to establish communication between the station master and the platform.
- Implement encryption and decryption using the DES algorithm.
- Ensure proper synchronization between the station master and the platform for smooth train operations.

---

## Question 2: Client-Server Program with Stream Cipher

### Overview
Implement a client-server program where the client encrypts using a stream cipher, and the server decrypts accordingly. Additionally, provide the stream cipher algorithm.

### Stream Cipher Algorithm
Any stream cipher(Say RC4).

### Implementation Details
- Develop a client-server program using socket programming.
- The client encrypts the data using the stream cipher algorithm and sends it to the server.
- The server decrypts the received data using the same stream cipher algorithm.
- Ensure proper error handling and synchronization between the client and server for reliable communication.

---
