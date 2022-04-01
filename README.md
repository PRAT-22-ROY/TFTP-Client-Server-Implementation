# TFTP-Client-Server-Implementation
The scope of the project is to provide implementation of TFTP Service (UDP based) involving a client and a server. The server handles the client's ftp request and performs file download after validation. Server may optionally handle multiple client ftp requests simultaneously. The protocol implemented shall follow the RFC1350 specification.

:black_medium_small_square: TFTP_01	The implementation will follow RFC 1350 (i.e ftp using UDP) 

:black_medium_small_square: TFTP_02	The client and server shall be configurable application which can run over network. 

:black_medium_small_square: TFTP_03	Client should be able to download a file from server. 

:black_medium_small_square: TFTP_04	Server should be able to provide upload file to client. 

:black_medium_small_square: TFTP_05	Data transfer will be done in chunks of block size of 512 bytes. A data packet of less than 512 bytes signals termination of a transfer. 

:black_medium_small_square: TFTP_06	Each data packet contains one block of data, and must be acknowledged by an acknowledgment packet before the next packet can be sent. 

:black_medium_small_square: TFTP_07	If a packet gets lost in the   network, the intended recipient will timeout and may retransmit his last packet (which may be data or an acknowledgment), thus causing the sender of the lost packet to retransmit that lost packet.	 

:black_medium_small_square: TFTP_08	Should handle error cases namely file not found, access violation and packet loss. 

:black_medium_small_square: TFTP_09	File transfers will be restricted to a single configured directory on server. 

:black_medium_small_square: TFTP_10	Server should maintain a log of all upload requests from client. 

:black_medium_small_square: TFTP_11	Server will be an iterative server to handle multiple clients.

:black_medium_small_square: TFTP_12	Standard error codes to be used to indicate specific error cases as in RFC.

:black_medium_small_square: TFTP_13	"Should include debug log messages  with atleast 4 levels (FATA, INFO, WARNING, DEBUG) 

##Team members Group 5
###1️⃣ Sravanthi Desham
###2️⃣ Sumit Tomar
###3️⃣ Puja Kumari
###4️⃣ Jaya Naga Sai Jaswanth Kuricheti
###5️⃣ Pratik Roy
