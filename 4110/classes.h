/*Created by Jose Salazar on 11/08/2017.
 * this program header is used in conjuction with main.cpp
 * this holds all the classes and methods for the generator,
 * Dijkstra, and FloydWarshall algorithms.
*/
#include <string>
#include <ctime>
#include <fstream>
#include <climits>
#ifndef PROJECT_CLASSES_H
#define PROJECT_CLASSES_H


/*Graph CLASS
 *
 * This class is the generator for our program.
 * Containing 4 patterns of generation: Linear, Reverse, Random, and External;
 * External is the user input file.
 * */
class Graph{
    int vertices;
    int** grid;
    int** path;
    std::string type;

public:

    //Constructor for Graph.
    Graph(int vertex,std::string typeOfGraph)
    {
        int counter = 0;

        if(typeOfGraph == "linear" || typeOfGraph == "reverse" || typeOfGraph == "random"){
            this->vertices = vertex;
            grid = new int*[vertex];
            for(int i=0; i < vertex; i++){
                grid[i] = new int[vertex];
            }
        }
        /*
         * EXTERNAL GRAPH
         * This graph uses data that has been provided by an external input file.
         * This method is similar to what is used with the other graph generations.
         * */
        else{
            this->type = "external";
            std::ifstream extFile;
            extFile.open(typeOfGraph.c_str());
            std::cout << "[Console]: Successfully opened external file." << std::endl;

            extFile >> vertex;
            this->vertices = vertex;
            grid = new int*[vertices];

            for(int i = 0; i < vertices; i++){
                grid[i] = new int[vertices];
            }
            for(int i = 0; i < vertices; i++){
                for(int k = 0; k < vertices; k++){
                    extFile >> counter;
                    grid[i][k] = counter;
                }
            }
            extFile.close();
            //std::cout << "[Console]: Closing external file." << std::endl;
        }

        /*
         * LINEAR GRAPH GENERATION
         * This generates a sequential graph in respect to the total number of
         * vertices previously determined.
         * */

        if(typeOfGraph == "linear"){
            this->type = "linear";
            //std::cout << "[Console]: Received task { Generate Graph Type = linear }" << std::endl;
            for(int i = 0; i < vertices; i++){
                for(int k = 0; k < vertices; k++){
                    if(i == k){
                        grid[i][k] = 0;
                        if(counter == 0){
                            counter++;
                        }
                    }
                    else{
                        grid[i][k] = counter;
                        grid[k][i] = counter;
                        counter++;
                    }
                }
            }
            //std::cout << "[Console]: Completed task { Generate Graph Type = linear }" << std::endl;
        }

        /*
         * REVERSE GRAPH GENERATION
         * This generates a reverse graph in respect to the total number of
         * vertices previously determined. We let counter be n(n-1)/2
         * we then let n be the vertex value.
         * */

        else if(typeOfGraph == "reverse"){
            this->type = "reverse";
            //std::cout << "[Console]: Received task { Generate Graph Type = reverse }" << std::endl;
            counter = vertex*((vertex-1)/2);
            for(int i = 0; i < vertex; i++){
                for(int k = 0; k < vertex; k++){
                    if(i == k){
                        grid[i][k] = 0;
                        if(counter == 0){
                            counter--;
                        }
                    }
                    else{
                        grid[i][k] = counter;
                        grid[k][i] = counter;
                        counter--;
                    }
                }
            }
            //std::cout << "[Console]: Completed task { Generate Graph Type = reverse }" << std::endl;
        }



         /*
         * RANDOM GRAPH GENERATION
         * This generates a reverse graph in respect to the total number of
         * vertices previously determined. We let counter be n(n-1)/2
         * we then let n be the vertex value.
         * */
        else if(typeOfGraph == "random"){
            this->type = "random";
            //std::cout << "[Console]: Received task { Generate Graph Type = random }" << std::endl;
            //srand(time(NULL));
            counter = rand();
            //counter = std::dis(std::gen);
            for(int i = 0; i < vertices; i++){
                for(int k = 0; k < vertices; k++){
                    if(i == k){
                        grid[i][k] = 0;
                        if(counter == 0){
                            counter++;
                        }
                    }
                    else{
                        grid[i][k] = counter;
                        grid[k][i] = counter;
                        //srand(time(NULL));
                        counter = rand();
                        //counter = std::dis(std::gen);
                    }
                }
            }
            //std::cout << "[Console]: Completed task { Generate Graph Type = random }" << std::endl;
        }

        path = new int*[vertices];

        //set the path.
        for(int i = 0; i < vertices; i++){
            path[i] = new int[vertices];
        }
    }

    /*
     * SETGRAPH GRAPH METHOD
     * We take in a string external which represents the output file.
     * We will open a stream and write the graph "grid" matrix into to
     * the specified external file.
     * */
    void setGraph(std::string external){

        std::ofstream extFile;
        extFile.open(external.c_str());
        //std::cout << "[Console]: Writing the Graph Data to an output file." << std::endl;
        extFile << this->vertices << '\n';

        for(int i = 0; i < vertices; i++){
            for(int k = 0; k < vertices; k++){
                extFile << this->grid[i][k] << ' ';
            }
            extFile << '\n';
        }
        //std::cout << "[Console]: Closing the output file." << std::endl;
        extFile.close();
    }


    /*FUNCTION: setTime
     *
     * We write the time results to an output file called time_records.txt, from
     * which users can open and analyse.
     * The function will take in the time variables, a string s which specifies
     * the kind of pattern. algorithmID will represent the algorithm this was
     * implemented on.
     * */


    void setTime(double time, std::string s, std::string alogithmID){

        std::ofstream clockfile;
        //std::cout << "[Console]: Writing time results { time_records.txt }." << std::endl;
        clockfile.open("time_records.txt", std::ofstream::app);

        clockfile.precision(10);
        clockfile << "Graph: " << s << std::endl << "Clock: " << time << std::endl << "TypeOfGraph: " << this->type << std::endl << "Algorithm used: " << alogithmID << '\n';
        clockfile << "Number of verticies: " << vertices << '\n';
        clockfile << "+++++" << std::endl << std::endl;

        //std::cout << "[Console]: Updating complete closing { time_records.txt }." << std::endl;
        clockfile.close();
    }

    /*
     * FUNCTION: setPath
     *
     * We write the path solutions to an output file called paths_data.txt from
     * which users will be able to open and analyse the results.
     *
     * */


    void setPath(std::string s, std::string algorithmID){

        std::ofstream paths;
        paths.open("paths_data.txt", std::ofstream::app);

        paths << "Graph: " << s << std::endl << "TypeOfGraph: " << this->type << std::endl << "Algorithm used: " << algorithmID << std::endl;
        paths << "Number of Vertices: " << vertices << std::endl;

        for(int i = 0; i < vertices; i++){
            paths << "Vertex = " << i << std::endl;
            for(int k = 0; k < vertices; k++){
                paths << "\t" << path[i][k];
            }
            paths << std::endl;
        }
        paths << "+++++" << std::endl;

        //std::cout << "[Console]: Updating complete, closing { paths_data.txt }." << std::endl;
        paths.close();
    }

    /*
     * FUNCTION: minDist
     *
     * We calculate the minimum distance that will be used in Dijkstra's algorithm.
     * minimum_index value will be returned where it is called.
     * */
    int minDist(int distance[], bool set[]){

        int minimum = INT_MAX;
        int minimum_index;

        for(int i = 0; i < vertices; i++){
            if(set[i] == false && distance[i] <= minimum){
                minimum = distance[i];
                minimum_index = i;
            }
        }
        return minimum_index;
    }


    void dijkstra(std::string s){

        std::string algorithmID = "Dijkstra";
        int distance[vertices];
        bool set[vertices];
        //srand(time(NULL));
        clock_t stopwatch;
        double difference;

        for(int i =0; i < vertices; i++){
            for(int k = 0; k < vertices; k++){
                distance[k] = INT_MAX;
                set[k] = false;
            }

            distance[i] = 0;
            //std::cout << "[Debug]: Started Stopwatch, the time will approximate the runtime of the next task ." <<std::endl;
            stopwatch = clock();
            //std::cout << "[Debug]: Running Task{ DIJKSTRA } on graph." <<std::endl;

            for(int j = 0; j < vertices-1; j++){
                int minimum = minDist(distance,set);
                set[minimum] = true;

                for(int n = 0; n < vertices; n++){
                    if(!set[n] && grid[minimum][n] && distance[minimum] != INT_MAX && distance[minimum]+grid[minimum][n] < distance[n]){
                        distance[n] = distance[minimum]+grid[minimum][n];
                    }
                }
            }
            stopwatch = clock()-stopwatch;
            //std::cout << "[Debug]: Stopped Stopwatch, the time will be recorded in { time_record.txt }." <<std::endl;

            for(int n = 0; n < vertices; n++){
                path[i][n] = distance[n];
            }

            difference += ((double)stopwatch)/CLOCKS_PER_SEC;
        }
        //std::cout << "[Console]: Updating { time_records.txt } from = Dijkstras." <<std::endl;
        setTime(difference, s, algorithmID);
        //std::cout << "[Console]: Updating { paths_data.txt } from = Dijkstras." <<std::endl;
        setPath(s, algorithmID);
    }


    void floydWarshall(std::string s){

        //Needs implementation.
        double difference;
        std::string algorithmID;
        algorithmID = "Floyd";
        //srand(time(NULL));
        clock_t stopwatch;

        for(int i = 0; i < vertices; i++){
            for(int k = 0; k < vertices; k++){
                path[i][k] = grid[i][k];
            }
        }

        stopwatch = clock();
        for(int i = 0; i < vertices; i++){
            for(int k = 0; k < vertices; k++){
                for(int n = 0; n < vertices; n++){
                    if(path[k][i] + path[i][n] < path[k][n]){
                        path[k][n] = path[k][i] + path[i][n];
                    }
                }
            }
        }

        stopwatch = clock()-stopwatch;
        difference = ((double)stopwatch)/CLOCKS_PER_SEC;
        //std::cout << "[Console]: Updating { time_records.txt } from = Floyd Warshall." <<std::endl;
        setTime(difference, s, algorithmID);
        //std::cout << "[Console]: Updating { paths_data.txt } from = Floyd Warshall." <<std::endl;
        setPath(s,algorithmID);

    }

};


#endif //PROJECT_CLASSES_H
