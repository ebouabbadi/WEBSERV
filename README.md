# WEBSERV
![Screenshot](https://miro.medium.com/v2/resize:fit:720/format:webp/1*AwGI1e13BoLvUd2wThmSLw.jpeg)

HTTP server in C++98


    struct sockaddr_in {
        short int sin_family;          // Address family (AF_INET)
        unsigned short int sin_port;   // Port number in network byte order
        struct in_addr sin_addr;       // IP address in network byte order
        unsigned char sin_zero[8];     // Padding to make struct the same size as sockaddr
    };
    
    The sockaddr_in struct contains the following members:

    sin_family: The address family, which is always AF_INET for IP addresses.
    sin_port: The port number, stored in network byte order (big-endian).
    sin_addr: The IP address, stored in network byte order (big-endian) as a struct in_addr.
    sin_zero: Padding to make the struct the same size as the generic sockaddr struct, which is used as a typecast to sockaddr_in in many socket API calls.
    You can use the sin_family, sin_port, and sin_addr members to specify the IP address and port number for a socket when calling the bind() function. You can also use them to connect to a remote server with the connect() function, or to retrieve the IP address and port number of a remote client that has connected to your server with the accept() function.

    The pollfd structure contains three fields:

    fd: the file descriptor to monitor
    events: the events to monitor for the file descriptor, which can include POLLIN for input readiness, POLLOUT for output readiness, POLLERR for error conditions, and POLLHUP for hang-up events.
    revents: the events that actually occurred for the file descriptor after the poll system call returns. This field is typically initialized to 0 by the caller and is filled in by the poll system call.


    # Creating socket file descriptor

    socket : Socket Programming is a method to connect two nodes over a network to establish a means of communication between those two nodes. A node represents a computer or a physical device with an internet connection. A socket is the endpoint used for connecting to a node. The signals required to implement the connection between two nodes are sent and received using the sockets on each node respectively.

    The C++ programming language provides a set of socket functions as part of the standard library that allows a program to create, bind, listen, connect, send, and receive data through a network socket.

    To use sockets in C++, a program typically follows these steps:

    1: Create a socket using the socket() function, which returns a file descriptor that represents the socket.
    2: Bind the socket to a specific IP address and port number using the bind() function, so that other programs can connect to it.
    3: Listen for incoming connections using the listen() function.
    4: Accept incoming connections using the accept() function, which returns a new file descriptor representing the connection.
    5: Send and receive data using the send() and recv() functions, respectively.
    In addition to the standard socket functions, C++ provides several classes and libraries for working with sockets, such as the std::net library introduced in C++20, which provides a more 
    
    modern and high-level interface for socket programming.


# Request Line
![Screenshot](https://miro.medium.com/v2/resize:fit:720/format:webp/1*Yqq-60D9mD4NVuhFd4IoFg.png)
 GET /home.html HTTP/1.1 

GET: this is Method The client requests a resource on the web server (Fetch a URL)
POST: The client submits data to a resource on the web server (Send form data to a URL and get a response back)
DELETE: The client deletes a resource on the web server (Delete a URL GET and POST (forms) are commonly used)
/home.html:  is the resource requested
HTTP 1.1: s the protocol used
HTTP methods:HTTP methods indicate the action that the client wishes to perform on the web server  

# HTTP Request Headers
There are various possibilities when including an HTTP header in the HTTP request.
A header is a case-insensitive name followed by a: and then followed by a value.
Example : 
    Host: example.com
    User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.9; rv:50.0) Gecko/20100101 Firefox/50.0
    Accept: */*
    Accept-Language: en
    Content-type: text/json

Host: header specifies the host of the server and indicates where the resource is requested from.
User-Agent: header informs the web server of the application that is making the request. It often includes.
Accept: header informs the web server what type of content the client will accept as the response.
Accept-Language: header indicates the language and optionally the locale that the client prefers.
Content-type: header indicates the type of content being transmitted in the request body.

# HTTP Request Body
HTTP requests can optionally include a request body. A request body is often included when using the HTTP POST and PUT methods to transmit data.

    POST /users HTTP/1.1
    Host: example.com
    {
        "key1":"value1",
        "key2":"value2",
        "array1":["value3","value4"]
    }

    PUT /users/1 HTTP/1.1
    Host: example.com
    Content-type: text/json
    {
        "key1":"value1"
    }

# HTTP Responses
![Screenshot](https://miro.medium.com/v2/resize:fit:720/format:webp/1*5QCrgA5LoA8AKR30ce6x5A.png)

When the web server is finished processing the HTTP request, it will send back an HTTP response.
The first line of the response is the status line. This line shows the client if the request was successful or if an error occurred.

HTTP/1.1 200 OK

The line begins with the HTTP protocol version, followed by the status code and a reason phrase. The reason phrase is a textual representation of the status code.

![Screenshot](https://miro.medium.com/v2/resize:fit:640/format:webp/1*JSnJtHpU7cWUnWIgGupu7w.png)

- Initially HTTP Client(i.e., web browser) sends a HTTP request to the HTTP Server.
- Server processes the request received and sends HTTP response to the HTTP client.

To display the page, browser fetches the file index.html from a web server.

- These 3 Headers are minimum required :

HTTP/1.1 200 OK -> This mentions what version of HTTP we are using, Status code and Status message.

Content-Type: text/plain -> This says that I’m (server) sending a plain text. There are many Content-Types. For example, for images we use this.

Content-Length: 12 -> It mentions how many bytes the server is sending to the client. The web-browser only reads how much we mention here.
