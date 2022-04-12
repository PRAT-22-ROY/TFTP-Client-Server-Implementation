
# TFTP-Client-Server-Implementation

The scope of the project is to provide implementation of TFTP Service (UDP based) involving a client and a server. The server handles the client's ftp request and performs file download after validation. Server may optionally handle multiple client ftp requests simultaneously. The protocol implemented shall follow the RFC1350 specification.

## Authors

- [Sravanthi Desham](https://github.com/sravanthi-123)
- [Sumit Tomar](https://github.com/sumit-beep)
- [Puja Kumari](https://github.com/puja-pearl)
- [Jaya Naga Sai Jaswanth Kuricheti](https://github.com/Jaswanthk17)
- [Pratik Roy](https://github.com/PRAT-22-ROY)

## Requirements

1. The implementation will follow RFC 1350 (i.e ftp using UDP)
2. The client and server shall be configurable application which can run over network
3. Client should be able to download a file from server.
4. Server should be able to provide upload file to client.
5. Data transfer will be done in chunks of block size of 512 bytes. A data packet of less than 512 bytes signals termination of a transfer.
6. Each data packet contains one block of data, and must be acknowledged by an acknowledgment packet before the next packet can be sent.
7. If a packet gets lost in the   network, the intended recipient will timeout and may retransmit his last packet (which may be data or an acknowledgment).
8. Should handle error cases namely file not found, access violation and packet loss.
9. File transfers will be restricted to a single configured directory on server.
10. Server should maintain a log of all upload requests from client.
11.  Server will be an iterative server to handle multiple clients.
12. Standard error codes to be used to indicate specific error cases as in RFC.
13. Should include debug log messages  with atleast 4 levels (FATA, INFO, WARNING, DEBUG).

 


## To run the project
1. Open two seperate terminals

2. To run the server 

* Open TFTP_Server `cd TFTP_Server`
* Go to make directory and then `make`
* Move to bin diretory and then `./main`


3. To run the client 

* Open TFTP_Client `cd TFTP_Client`
* Go to make directory and then `make`
* For RRQ (Read request) downlaoding files from server
```bash
  ./main PUT yourIP fileName
```
* For WRQ (Write request) uploading files to server
```bash
  ./main GET serverIP fileName
```
## Outputs

The outputs can be found here [Results](https://github.com/PRAT-22-ROY/TFTP-Client-Server-Implementation/tree/master/Results)

