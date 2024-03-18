#include <netinet/in.h>  
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <sys/socket.h>  
#include <unistd.h>  
#include <stdlib.h>
#define PORT 8080  
static unsigned char pc1[56] = { 57, 49, 41, 33, 25, 17, 9, //Permuted Choice 1
 1, 58, 50, 42, 34, 26, 18,
 10, 2, 59, 51, 43, 35, 27,
 19, 11, 3, 60, 52, 44, 36,
 63, 55, 47, 39, 31, 23, 15,
 7, 62, 54, 46, 38, 30, 22,
 14, 6, 61, 53, 45, 37, 29,
 21, 13, 5, 28, 20, 12, 4};
static unsigned char pc2[48] = { 14, 17, 11, 24, 1, 5, //Permuted Choice 2
 3, 28, 15, 6, 21, 10,
 23, 19, 12, 4, 26, 8,
 16, 7, 27, 20, 13, 2,
 41, 52, 31, 37, 47, 55,
 30, 40, 51, 45, 33, 48,
 44, 49, 39, 56, 34, 53,
 46, 42, 50, 36, 29, 32};
static unsigned char ip[64] = { 58, 50, 42, 34, 26, 18, 10, 2,//Initial Permutation
 60, 52, 44, 36, 28, 20, 12, 4,
 62, 54, 46, 38, 30, 22, 14, 6,
 64, 56, 48, 40, 32, 24, 16, 8,
 57, 49, 41, 33, 25, 17, 9, 1,
 59, 51, 43, 35, 27, 19, 11, 3,
 61, 53, 45, 37, 29, 21, 13, 5,
 63, 55, 47, 39, 31, 23, 15, 7};
static unsigned char ep[48] = { 32, 1, 2, 3, 4, 5, //Expansion Permutation
 4, 5, 6, 7, 8, 9,
 8, 9, 10, 11, 12, 13,
 12, 13, 14, 15, 16, 17,
 16, 17, 18, 19, 20, 21,
 20, 21, 22, 23, 24, 25,
 24, 25, 26, 27, 28, 29,
 28, 29, 30, 31, 32, 1};
static unsigned char s[8][4][16] = {
 { {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,},//S1
 {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,},
 {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,},
 {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13,},},
 { {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,},//S2
 { 3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,},
 { 0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,},
 {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9,},},
 { {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,},//S3
 {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,},
 {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,},
 { 1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12,},},
 { { 7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,},//S4
 {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,},
 {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,},
 { 3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14,},},
{ { 2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,},//S5
 {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,},
 { 4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,},
 {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3,},},
{ {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,},//S6
 {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,},
 { 9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,},
 { 4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13,},},
{ { 4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,},//S7
 {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,},
 { 1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,},
 { 6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12,},},
{ {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,},//S8
 { 1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,},
 { 7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,},
 { 2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}}};
static unsigned char p[32] = { 16, 7, 20, 21, //Permutation
 29, 12, 28, 17,
 1, 15, 23, 26,
 5, 18, 31, 10,
 2, 8, 24, 14,
 32, 27, 3, 9,
 19, 13, 30, 6,
 22, 11, 4, 25};
static unsigned char iip[64] = { 40, 8, 48, 16, 56, 24, 64, 32,//Inverse Permutation
 39, 7, 47, 15, 55, 23, 63, 31,
 38, 6, 46, 14, 54, 22, 62, 30,
 37, 5, 45, 13, 53, 21, 61, 29,
 36, 4, 44, 12, 52, 20, 60, 28,
 35, 3, 43, 11, 51, 19, 59, 27,
 34, 2, 42, 10, 50, 18, 58, 26,
 33, 1, 41, 9, 49, 17, 57, 25};

void encrypt(unsigned long long key, unsigned long long iv, char flag, unsigned long long *ciphertext, unsigned long long *plaintext){
    unsigned long long k[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, cd = 0, temp = 0, ep_out48 = 0;
    unsigned int l = 0, r = 0, c0 = 0, d0 = 0, sb_out32 = 0, p_out32 = 0;
    unsigned char sdata = 0, row = 0, col = 0;
    int j = 0, i = 0, round = 0;
    
    //Generating subkeys.
    for (j=27; j>=0;j--) //Permuted Choice 1
    {
     c0 = c0 ^ (((key >> (64-pc1[(27-j)])) & 0x1) << j);
     d0 = d0 ^ (((key >> (64-pc1[(55-j)])) & 0x1) << j);
    }
    
    for (i=1; i<=16;i++)
    {
   	 if ((i==1) | (i==2) | (i==9) | (i==16))
   	 {
   		 c0 = ((c0 << 1) | (c0 >> 27)) & 0x0FFFFFFF;
   		 d0 = ((d0 << 1) | (d0 >> 27)) & 0x0FFFFFFF;
   	 }
   	 else
   	 {
   		 c0 = ((c0 << 2) | (c0 >> 26)) & 0x0FFFFFFF;
   		 d0 = ((d0 << 2) | (d0 >> 26)) & 0x0FFFFFFF;
   	 }
   	 cd = 0; // initiallizing for new value
   	 cd = ((cd ^ c0) << 28) ^ d0;
   	 for (j=47; j>=0;j--) //Permuted Choice 2
   		 k[i-1] = k[i-1] ^ (((cd >> (56-pc2[(47-j)])) & 0x1) << j);
    }
    
    if(flag == 'd')
    *plaintext = *ciphertext;//in decryption, starting from ciphertext
    *plaintext = *plaintext ^ iv; //xor of plaintext and initial vector

    //Computing Initial Permutation
    for (j=31; j>=0;j--)
    {
   	 l = l ^ (((*plaintext >> (64-ip[(31-j)])) & 0x1) << j);
   	 r = r ^ (((*plaintext >> (64-ip[(63-j)])) & 0x1) << j);
    }
    
    //for 16 rounds.
    for (round=0; round<16; round++)
    {
    
   	 //Fiestal function step 1; Expansion: the 32-bit half-block is expanded to 48 bits using the expansion permutation
   	 ep_out48 = 0;
   	 for (j=47; j>=0;j--)
   		 ep_out48 = ep_out48 ^ ((long long)((r >> (32-ep[(47-j)])) & 0x1) << j);
   	 
   	 //xor for encryption
   	 if (flag == 'e') ep_out48 = ep_out48 ^ k[round];
   	 //xor for decryption
   	 if (flag == 'd') ep_out48 = ep_out48 ^ k[15-round];  
   	 
   	 //sbox reduction  
   	 sb_out32 = 0;
   	 for (i=7; i>=0;i--)
   	 {
   		 row = 0;
   		 col = 0;
   		 sdata = 0;
   		 sdata = (ep_out48>>(i*6)) & 0x3F;//From MSB, access 6 bits
   		 row = row ^ (sdata & 0x1);
   		 row = row ^ (((sdata >> 5) & 0x1) << 1);
   		 col = (sdata >>1) & 0x0F;
   	 	sb_out32= sb_out32 ^ ((int)(s[7-i][row][col] << (4*i)));
   	 }
   	 
   	 //permutation
   	 p_out32 = 0;
   	 for (j=31; j>=0;j--)
   		 p_out32 = p_out32 ^ (((sb_out32 >> (32-p[(31-j)])) & 0x1) << j);
   		 p_out32 = p_out32 ^ l;
   		 l = r; r = p_out32;
    }
    
    temp = 0; temp = ((temp ^ r) << 32) ^ l;
    //inverse of initial permutation
    *ciphertext = 0;
    for (j=63; j>=0;j--)
   	 *ciphertext = *ciphertext ^ (((temp >> (64-iip[(63-j)])) & 0x1) << j);
    *ciphertext = *ciphertext ^ iv; //xor of ciphertext and initial vector
} 	 
unsigned long long stringToHex(const char *input) {
	unsigned long long result = 0;
	while (*input) {
    	result = (result << 8) | *input;
    	input++;
	}
	return result;
}

char* hexToString(unsigned long long hexValue) {
	int length = snprintf(NULL, 0, "%llx", hexValue);
	char *result = (char*)malloc(length + 1);
	snprintf(result, length + 1, "%llx", hexValue);

	return result;
}
unsigned long long hexStringToULL(const char *hexString) {
	unsigned long long result = 0;
	while (*hexString) {
    	char digit = *hexString;

    	if (digit >= '0' && digit <= '9') {
        	result = (result << 4) | (digit - '0');
    	} else if (digit >= 'a' && digit <= 'f') {
        	result = (result << 4) | (digit - 'a' + 10);
    	} else if (digit >= 'A' && digit <= 'F') {
        	result = (result << 4) | (digit - 'A' + 10);
    	} else {
        	// Invalid character in the hexadecimal string
        	fprintf(stderr, "Invalid character in the hexadecimal string: %c\n", digit);
        	exit(EXIT_FAILURE);
    	}

    	hexString++;
	}
	return result;
}
char* hexToASCIIString(unsigned long long hexValue) {
	int size = sizeof(unsigned long long);
	char *result = (char*)malloc(size + 1);

	for (int i = size - 1; i >= 0; i--) {
    	result[size - 1 - i] = (hexValue >> (8 * i)) & 0xFF;
	}

	result[size] = '\0'; // Null-terminate the string

	return result;
}
	int main(int argc, char const* argv[])  
	{  
       	int server_fd, new_socket, valread;  
       	struct sockaddr_in address;  
       	int opt = 1;  
       	int addrlen = sizeof(address);  
       	char buffer[1024] = { 0 };  
       	char* hello = "HiClient";
       	 
       	unsigned long long plaintext = stringToHex(hello);
       	unsigned long long key, iv, ciphertext;

       	key = 0xeabc4532;
       	iv = 0xabb4562e;
       	//printf("Plaintext:%llx ", plaintext);
       	encrypt(key, iv, 'e', &ciphertext, &plaintext);
       	//printf("Cipher:%llx ", ciphertext);
       	hello = hexToString(ciphertext);
       	//printf("\ncipher string:%s", hello);
 	 
       	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {  
               	perror("socket failed");  
               	exit(EXIT_FAILURE);  
       	}  
 
       	if (setsockopt(server_fd, SOL_SOCKET,  
                               	SO_REUSEADDR | SO_REUSEPORT, &opt,  
                               	sizeof(opt))) {  
               	perror("setsockopt");  
               	exit(EXIT_FAILURE);  
       	}  
       	address.sin_family = AF_INET;  
       	address.sin_addr.s_addr = INADDR_ANY;  
       	address.sin_port = htons(PORT);  
 	 

       	if (bind(server_fd, (struct sockaddr*)&address,  
                       	sizeof(address))  
               	< 0) {  
               	perror("bind failed");  
               	exit(EXIT_FAILURE);  
       	}  
       	if (listen(server_fd, 3) < 0) {  
               	perror("listen");  
               	exit(EXIT_FAILURE);  
       	}  
       	if ((new_socket  
               	= accept(server_fd, (struct sockaddr*)&address,  
                               	(socklen_t*)&addrlen))  
               	< 0) {  
               	perror("accept");  
               	exit(EXIT_FAILURE);  
       	}  
       	valread = read(new_socket, buffer, 1024);  
       	//decrypt the received message
       	ciphertext = hexStringToULL(buffer);
       	encrypt(key, iv, 'd', &ciphertext, &plaintext);
       	char* mess = hexToASCIIString(ciphertext);
      	 
       	printf("Received Message From Client: %s\n", mess);  
       	send(new_socket, hello, strlen(hello), 0);  
       	printf("Message sent from server.\n");  
 	 
       	// closing the connected socket  
       	close(new_socket);  
       	// closing the listening socket  
       	shutdown(server_fd, SHUT_RDWR);  
       	return 0;  
	} 
