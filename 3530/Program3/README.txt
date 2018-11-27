Read Me - Jose Salazar - CSCE3530 - Fall 2018 - Program 3
================================================================================
PROGRAM 3
================================================================================
=>REQUIREMENTS

  *User must have access to Linux system.
  *User must open at least 2 command line programs.
  *User must have access to cse0X.cse.unt.edu (X can be any value 1-6).
  *Bundle must be complete (see next section).

NOTE: These requirements have been tested successfully under all cse servers.
================================================================================
=>IN THIS BUNDLE

This project includes a multi program execution. The following files should be
located inside this directory:

  *client.cpp
  *server.cpp
  *README.txt
  *screenshots.pdf

  NOTE: IPaddress.txt will be automatically created, no import is required!
        See the OTHER INFORMATION section for issues with this file if there
        is an early termination of server program.

If any of these files are missing, please contact me at:
  e-mail: jose.salazar@untsystem.edu
================================================================================
=>FEATURES [SERVER]

  *Connects/Disconnects to/the client(s)
  *Supports file creation (IPaddress.txt), if none is imported.
  *Maintains and updates the IPaddress.txt
  *Removes assigned IP addresses from the available list.
  *Sends the client appropriate responses
  *Warns next client if there are no more available IP addresses available.
  *Displays session details when terminating.
  *Cleans IPaddress.txt during graceful termination.

================================================================================
=>FEATURES [CLIENT]

  *Connects/Disconnects to/from the server.
  *Auto Input
  *Displays server messages
  *Displays error when server is out of IP Addresses.
  *Displays session details when disconnecting from the server.

================================================================================
=>HOW TO COMPILE THE BUNDLE



The following steps must be completed before executing this bundle:

  -To compile server.cpp:         g++ -std=c++11 -o server server.cpp

  -To compile client.cpp:         g++ -std=c++11 -o client client.cpp



================================================================================
=>EXECUTING THIS BUNDLE



server and client executables are required to be executed in different servers.




  *server - must be executed in cse01.cse.unt.edu

    To execute:     ./server <port number>  where port number can be 3000-3005



  *client - must be executed in any cse server EXCEPT cse01.cse.unt.edu

    To execute:   ./client 129.120.151.94 <port number>





NOTE: port number must be the same on both client and server in order for them
      communicate successfully.

      IMPORTANT: CLIENT MUST HAVE IPADDRESS ENTERED.

================================================================================
=>USAGE:

The basic usage is:

  1. execute server first
  2. then execute client next (all client programs self terminate.)
  3. execute next client program (can be same server as previous client
      or any other cse server that isn't cse01.cse.unt.edu)
  4. server will auto terminate when it is out of IP addresses and new client
      attempts to connect!

This will disconnect the client from the server and let it know to close the
communication.

================================================================================
=>OTHER INFORMATION

  *IPaddress.txt file will be automatically created.
  *server.cpp deletes IPaddress.txt file after all ip's are used.
  *Sample output screenshots will be provided in this bundle.

  NOTE: EARLY TERMINATION OF SERVER WILL PREVENT IPaddress.txt file from being
        deleted properly. If you need to terminate early, please run:

          rm IPaddress.txt
