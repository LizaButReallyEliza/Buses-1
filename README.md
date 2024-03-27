We are building a new city, which obviously will have buses. We want to understand the optimal pathings for the buses that’s why we are asking
you to write a program that will help us to do that. The city can be represented as an unordered graph with N vertices as crossroads and M edges as the
streets, where each street has an assigned number to it - the time it takes to drive through that street in minutes. The program should support several operations:

1. Construct the shortest pathing for a new bus starting at crossroad A and with destination at crossroad B. The operation should have O(1) complexity.
2. Add a new street between crossroads A and B. All existing paths for buses should be updated accordingly and the operation should have O(N^2) complexity.
3. Give a detailed path breakdown for the i-th bus. The operation should have O(N^2 + M)  complexity.

Input:
On the first line of the input you will get N and M, the number of crossroads and streets accordingly. Next M lines will contain u, v, and k,
where u and v indicates the street between crossroads and k is the duration in minutes required to drive through the street.
After that your program should continuously receive and process the mentioned operations. Initial list of buses is empty:
“add_bus A B”:  Add the new bus and assign it the next available integer (starting from 0). After processing this operation your program should output
the minimum time required for the bus to reach from crossroad A to crossroad B.
“construct_street A B”: Construct a street between crossroads A and B and recalculate the shortest paths for all buses.
After this operation your program should output the minimum durations for all buses.
“details I”: lists the crossroads that the I-th bus should cross to get from crossroad A to crossroad B in the fastest way.
If there are multiple such paths, output any of them.

Requirements: Use Floyd-Warshall’s algorithms for operations 1 and 2. Use Dijkstra’s algorithms for operation 3. Use “Adjacency Matrix” to store the graph.
