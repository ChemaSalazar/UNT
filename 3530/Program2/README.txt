Read Me - Jose Salazar - CSCE3530 - Fall 2018 - Program 2
================================================================================
PROGRAM 2
================================================================================
=>REQUIREMENTS

  *User must have access to Linux system.
  *User must open 2 command line programs.
  *User must have access to cse0X.cse.unt.edu (X can be any value 1-6).
  *telnet program must be installed in your Linux system.
  *Bundle must be complete (see next section).

NOTE: These requirements have been tested successfully under all cse servers.
================================================================================
=>IN THIS BUNDLE

This project includes a multi program execution. The following files should be
located inside this directory:

  *client.cpp
  *proxy.cpp
  *get-cmd.sh
  *README.txt
  *screenshots.pdf

If any of these files are missing, please contact me at:
  e-mail: jose.salazar@untsystem.edu
================================================================================
=>FEATURES [PROXY]

  *Connects/Disconnects to/the client
  *Supports file creation (list.txt), if none is imported.
  *Maintains and updates the list.txt
  *Removes old cached site
  *Displays current cached list
  *Executes shell script "get-cmd.sh"
  *Filters HTTP headers, if 200 OK, the client will output the website code.
  *Sends the client appropriate responses
  *Displays session details when terminating.

================================================================================
=>FEATURES [CLIENT]

  *Connects/Disconnects to/from the proxy.
  *Supports URL input
  *Supports file reading
  *Displays proxy messages (HTTP response codes)
  *Displays session details when disconnecting from the proxy.

================================================================================
=>HOW TO COMPILE THE BUNDLE



The following steps must be completed before executing this bundle:

  -To compile proxy.cpp:          g++ proxy.cpp -o proxy

  -To compile client.cpp:         g++ client.cpp -o client

  -Give get-cmd.sh permission:    chmod +x get-cmd.sh



IMPORTANT: Remember to give permission to the shell program to be able to run.

================================================================================
=>EXECUTING THIS BUNDLE



proxy and client executables are required to be executed in different servers.




  *proxy - must be executed in cse01.cse.unt.edu

    To execute:     ./proxy <port number>  where port number can be 2000-2005



  *client - must be executed in any cse server EXCEPT cse01.cse.unt.edu

    To execute:   ./client 129.120.151.94 <port number>


  *get-cmd.sh - will be executed by the proxy.




NOTE: port number must be the same on both client and server in order for them
      communicate successfully.

================================================================================
=>USAGE:

After executing both program on different servers, you will need to use the
client program to interact with the proxy. A small usage message will give you
the commands you need to use the program.

The basic usage is:

      Usage: x.y
      Replace 'x' with desired website name (e.g.: jamerson, loyalkng, twitter)
      Replace 'y' with desired domain name (e.g.:  .com, . net, .org)
      To end the program, type 'exit' or 'quit' without quotes.
      URL>

your input will be recorded when the URL> is printed:

      URL>


Under this prompt, you can type whatever website you desire, HOWEVER there are
some limitations so for this program, websites must ONLY be entered in using the
following format: sitename.domain for example:


      URL>jamerson.com


The server will then send an appropriate response to the client. If your website
is already cached, then this means it will exist in the list.txt file AND has
been downloaded to the server using the format: sitename.domain.html

In the case of our example: jamerson.com the file will be jamerson.com.html


At any point you may enter as many sites as you want, but if you decide that you
want to terminate the program, you must do so by typing 'exit' like this:


      URL>exit

This will disconnect the client from the server and let it know to close the
communication.

================================================================================
=>OTHER INFORMATION

  *This list contains websites that have
  been successfully used with 200 OK response. This list working
  as of 10-25-2018:

                    
                    loyalkng.com
                    has.com
                    jamerson.com
                    gottem.com
                    canihas.com


  *Note that importing a list will not generate the html files, ONLY by deleting
  the list.txt file or deleting an item on the list will the program generate
  the html file.



  *Sample output screenshots will be provided in this bundle.
