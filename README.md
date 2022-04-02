# client-server
**Description:**
-----------------

This project is test assignment for VK Internship. Client-server able to send file from client to server. 

**Compiling:**
---------------

First you need to compile the project executing `make`.

**Usage:**
-----------

In different terminal windows:\
- First start server using (without brackets):\
`./server [port number] [directory to save file]`

 - Then start client using (without brackets):\
`./client [address] [port number] [path to the file to send] [name to save file in server]`\
*_Last argument is optional._

For successful connection between client and server **port numbers must be same**, otherwise connection will be refused.
