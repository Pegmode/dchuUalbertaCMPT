.TH SERVER 1
.SH NAME
server - listens for Transaction simulation requests from a server

.SH SYNOPSIS
.B server
<port_number>

.SH ARGUMENTS
.IP port_number
The port number that the server will listen on for requests from clients.

.SH DESCRIPTION
.I server
is a program that listens for a Transaction simulation request on a particuar 
port from clients. Up to 50 clients may connect to the server. The server will
log all transactions in a text file with the format 
.I "hostname.serverPID". All transactions between the server and any clients with be logged in this file. 
Once 30 seconds has passed without any requests from any clients, the server will
automatically close and generate end summary statistics about the connections it made
while it was running. Times given in the logs are Unix epoch seconds.

Written for Assignment 3 CMPUT379F21 at the University of Alberta.

.SH LOG FORMAT
Server log entries contain the following informating respectively
.IP LOG_TIMES
the time in Unix epoch seconds the logged event took place
.IP TRANSACTION_ID
the ID used to track the current transaction
.IP COMMAND
the command the event represents
.IP SOURCE
the machine and process ID of the client making the transaction request

.SH AUTHOR
Daniel Chu 
.UR https://github.com/Pegmode/ 
.UE 