# FlightSimulator
We created a client that connects to a flight simulator server. 
The client is getting values and commands from the simulator, parsing them and changing their values. 
We created separate class for every command that execute it. 
The “Open data server” command and the “Connect command” are working on different threads and keep sending
and accepting information from the server and the client.

Yuval Sirotkin
Hadar Goldberger
