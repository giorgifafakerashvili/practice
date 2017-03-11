#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>


void exit_with_error(const char* err) {
	perror(err); 
	exit(1); 
}



bool socketAddrsEqual(struct sockaddr* a, struct sockaddr* b) {
	return !memcpy(a, b, sizeof(a));
}


int main(int argc, char* argv[]) {

	

	if(argc < 3 || argc > 4) {
		// test for correct number of arguments 
		exit_with_error("parameter problem"); 
	}


	char* server = argv[1]; 				// First arg: server address/name 
	char* echo_string = argv[2]; 		// Second arg: word to echo 


	size_t echo_string_length = strlen(echo_string); 
	

	// Third arg (optional): server port/service 
	char* server_port = (argc == 4) ? (char*)argv[3] : (char*)"echo";

	// tell the system what kind(s) of addresses info we want 
	struct addrinfo hints; 
	memset(&hints, 0, sizeof(hints)); 
	hints.ai_family = AF_UNSPEC; 
	hints.ai_socktype = SOCK_DGRAM; 
	hints.ai_protocol = IPPROTO_UDP; // Only UDP protocol 

	// Get address (es) 
	int ret; 

	struct addrinfo* result; 
	ret = getaddrinfo(server, server_port, &hints, &result);

	if(ret != 0) {
		exit_with_error("getaddrinfo() failed");
	} 

	int socket_fd; 

	socket_fd = socket(result->ai_family, result->ai_socktype, result->ai_protocol); 

	if(socket_fd < 0) {
		exit_with_error("socket() error"); 
	} 

	// send the string to the server 
	ssize_t bytes_sent = sendto(socket_fd, echo_string, echo_string_length, 0, 
															result->ai_addr, result->ai_addrlen); 

	if(bytes_sent < 0) {
		exit_with_error("sendto() failed"); 
	} else if(bytes_sent != echo_string_length) {
		exit_with_error("sendto() failed: sent unexpected number of bytes"); 
	} 


	// receive a response 
	struct sockaddr_storage from_addr; 
	socklen_t from_addr_len = sizeof(from_addr); 
	char buffer[1024 + 1]; // IO buffer 
	int bytes_received; 

	bytes_received = recvfrom(socket_fd, buffer, 1024, 0, 
														(struct sockaddr*)&from_addr, &from_addr_len);

	if(bytes_received < 0) {
		exit_with_error("recvfrom() failed"); 
	} else if(bytes_received != echo_string_length) {
		exit_with_error("got unexpected number of bytes: recvfrom() "); 
	} 

	// verify reception from expected source 
	if(!socketAddrsEqual((struct sockaddr*)result->ai_addr, (struct sockaddr*)&from_addr)) {
		exit_with_error("recvfrom(), receiving a packet from uknown source"); 
	} 

	freeaddrinfo(result); 

	buffer[echo_string_length] = 0; 
	printf("received: %s\n", buffer); // print 



	return 0;
}