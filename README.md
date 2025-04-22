Project Overview: Public Transport Career Management System
The goal of this project is to create a public transport career management system, enabling the definition and querying of stations (stops), routes, and connections between stops. The system interacts with the user through commands, each having a specific number of arguments based on the operation being executed.

Key Features of the Project:
Careers (Bus Lines): A career (left, right, or middle in the diagram) is identified by a name, origin stop, destination stop, the number of stops, total cost, and total duration. Each career may have a series of stops and connections.

Stops: A stop is identified by a name, latitude, and longitude, and may be part of multiple careers. Stops may include spaces or tabs in their names, in which case the name should be enclosed in quotes.

Connections: Connections define the relationship between two stops within a career, including cost and duration. These connections may form a circular route, where the last stop connects to the first, thus creating a loop.

Command-Based Interaction:
The program interacts through a set of commands, each with a different number of arguments, to define and query the system:

q: Terminates the program.

c: Adds and lists careers. It can list all careers, or display the stops of a specific career. An optional "inverse" argument lists the stops in reverse order.

p: Adds and lists stops. It can list all stops, show the coordinates of a particular stop, or create a new stop with given coordinates.

l: Adds connections between stops. A connection is linked to a career, indicating the origin and destination stops, as well as cost and duration.

i: Lists intersections between careers, i.e., stops that are shared by multiple careers.

Input and Output Format:
Command c:

c → Lists all careers.

c <career-name> → Lists the stops of the specified career.

c <career-name> inverse → Lists the stops of the career in reverse order.

c <new-career-name> → Creates a new career.

Command p:

p → Lists all stops.

p <stop-name> → Shows the latitude and longitude of the specified stop.

p <stop-name> <latitude> <longitude> → Creates a new stop with the given coordinates.

Command l:

l <career-name> <origin-stop> <destination-stop> <cost> <duration> → Adds a connection to the career.

Command i:

i → Lists stops that are common to more than one career.

Constraints and Error Handling:
Careers have names up to 20 bytes, and stops have names up to 50 bytes.

Each connection between stops must have a valid career, stops, cost, and duration. Errors include non-existing careers or stops, negative cost or duration, and invalid connections.

The program handles errors, displaying only the first encountered error when multiple issues arise.