.TH CLIENT 1
.SH NAME
client - sends Transaction simulation requests to a server

.SH SYNOPSIS
.B client
<port_number>
.I [ip_address]

.SH ARGUMENTS
.IP port_number
The port number that the client will use.
.IP ip_address
The IP address that the client will connect to. Defaults to localhost if not given.
.SH DESCRIPTION
.I client
is a program that reads in commands from either stdin or redirected input from a text
file which contains either transaction requests 
.I T<n>
or sleep requests
.I S<n>
Sleep requests cause the client wait for 
.I n
seconds. Transaction requests are sent to the server for simluated processing. Once the
server finishes simulating the request, it responds with a 
.I D<n>
message where 
.I n
is the request ID. All transactions and sleep events are logged in a text file named
.I hostname.clientPID.

Written for Assignment 3 CMPUT379F21 at the University of Alberta.

.SH LOG FORMAT
Client log entries contain the following informating respectively
.IP LOG_TIMES
the time in Unix epoch seconds the logged event took place
.IP SYSTEM_CALL
the system call the event represents
.IP COMMAND
the command the event represents

.SH AUTHOR
Daniel Chu 
.UR https://github.com/Pegmode/ 
.UE 