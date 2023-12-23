CMPUT 379 ASSIGNMENT 3
DANIEL CHU

==========================================================================================================================================
FILE LISTING:
    README.txt:                 This readme file
    makefile:                   makefile for the whole assignment. run make to build both client and server
    /Client:                    directory containing everything that is exlcusive to the client 
        client.c                main source file for client
        client.h                header for client
        clientStats.c           functions for generating client specific stats for logfile
    /Server                     directory containing everything that is exlcusive to the server
        server.c                main source file for server
        server.h                server header
        clientsList.c           code for server to keep track of clients
        serverStats.c           functions for generating server specific stats for logfile
    /common                     direction containing everything that is shared between both server and client
        common.h                header containing definitions used by both server and client
        commonStats.c           code for generating stats that are shared by both server and client
        tands.c                 job related code given as part of the assignment
        utils.c                 shared ultility functions
    /man                        directory containing everything related to man pages for server and client
        clientManSource.ms      groff source for the client man page
        serverManSource.ms      groff source for the server man page
==========================================================================================================================================
Assumptions:
    -   By using the timeout method that I chose, I am assuming that there will never be an issue with
        the accept() system call

    -   Assumed that input will be exactly as given

    -   Assumed that there will be never any more client connections than MAX_CLIENTS 50

    -   Assumed that you do not want text output on the terminal

    -   Assumed that the code in tands.c given by the prof/class will work 
==========================================================================================================================================
Summary:
        I chose to take a very quick and dirty aproach with this assignment. I tried to get a working solution rather than a
    perfectly structed one. I chose to take the prof at his word and implemented all the sockets as simple strings. Based on
    the wording of the assignment, I assumed that he wanted this. Personally I would have liked to serialize a struct and set
    that instead of simple strings. I have some messy job structs that are leftovers of this. The server code is much less
    structed than the client code because splitting the code into functions seemed like a pain with recieving messages from sockets. 
    The message to the server contains the client name so that it can be tracked by server.
==========================================================================================================================================
Build Instructions:
    run `make` from the projects root directory to build the project. The server and client executables will be moved to the root directory so
    you can run them from there.

    if make states that "make: Nothing to be done for 'default'." then run `make clean` to remove the old executables and then re run-make.

    To build the man page .pdfs for the server and client, run make serverMan and clientMan respectively. They will be placed in the 
    man directory.