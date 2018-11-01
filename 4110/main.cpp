/*Created by Jose Salazar
 * Part of CSCE4110 project.
 * other programs used: classes.h
 * */



#include <string>
#include <iostream>
#include <ctime>
#include "classes.h"
//#include <random>
void buildJobs();

/*main FUNCTION
 *
 * This is the main function where we will begin the program.
 * this function will allow for user input. I have created a filter
 * to where if there is no user input, then the program will
 * continue under it's own generated data. This data is created at
 * Runtime and has not been pre-determined by me.
 *
 * 2 conditions are accepted, given a external input, the program will
 * only run tasks specific to that data file.
 *
 * if no file is detected we will execute generator created data through
 * a buildJobs() method that will handle the tasks.
 *
 * */



int main(int argc, const char * argv[]) {


    srand(time(NULL));

    //PLEASE NOTE This section was an attempt to utilize a new method of randomizing values. NOT WORKING.
    /*
    std::random_device rd;
    std::mt19937 gen(rd());
    uniform_int_distibution<> dis(1,1000);
     */
    std::string data;
    std::cout << "[Console]: Program loaded, checking to see if there is an external input file." << std::endl;

    if(argc > 1){
        std::cout << "[Console]: External input file found, attempting to read data from (" << argv[1] << ")." << std::endl;
        data = argv[1];
        Graph a(0,data);
        std::cout << "[Console]: Building graphs based on (" << argv[1] << ") data." << std::endl;
        std::cout << "[Console]: Running graph data through Dijkstra." << std::endl;
        a.dijkstra(data);
        std::cout << "[Console]: Running graph data though Floyd Warshall." << std::endl;
        a.floydWarshall((data));
        std::cout << "[Console]: Completed jobs." << std::endl;
        std::cout << "[Console]: Results can be found under files { time_records.txt } and { paths_data.txt }" << std::endl;
    }
    else{
        std::cout << "[Console]: No external input file detected, running generator instead." << std::endl;
        std::cout << "[Debug]: External file format should be ./a.out ExternalFile" << std::endl;
        std::cout << "[Console]: Connected to generator, creating graph data." << std::endl;
        buildJobs();
        std::cout << "[Console]: Completed Jobs" << std::endl;
        std::cout << "[Console]: Results can be found under files { time_records.txt } and { paths_data.txt }" << std::endl;
    }
    std::cout << "[Console]: SUCCESS" << std::endl;
    return 0;
}


/*  buildJobs FUNCTION
 *
 * This function is responsible for sending the generator jobs/tasks
 * to perform. In our case, we will first assign the generator to
 * generate 30 complete graphs. Each graph will be part of a group
 * or series, where they will share the same number of vertices, but
 * will differ in the data generating method.
 *
 * ==IMPORTANT:
 * Tester will be able to write the data of each graph created, however
 * since this will create 30 new files, I have disabled this function
 * in order to prevent clutter.... If you wish to get these files,
 * please uncomment where you see sections under each Graph where
 * setGraph(); appears.
 *
 * The last task for this function is to run the generated graphs
 * through Dijkstra's and FloydWarshall's algorithms.
 *
 * ==Format==
 * When creating a Job for the generator, you must specify the
 * number of verticies to generate and the pattern "key".
 *
 * vertices can be raw integer input such as : 50 , 100, 1000
 * pattern keys can be : linear, reversem or random. [strings]
 *
 *
 * */
void buildJobs(){

    std::cout << "[Generator]: Building 30 graphs." << std::endl;
    Graph a(50,"linear");
    Graph aa(50, "reverse");
    Graph aaa(50,"random");
    /*
    a.setGraph("graph_a.txt");
    aa.setGraph("graph_aa.txt");
    aaa.setGraph("graph_aaa.txt");
    */


    Graph b(80,"linear");
    Graph bb(80,"reverse");
    Graph bbb(80,"random");
    /*
    b.setGraph("graph_b.txt");
    bb.setGraph("graph_bb.txt");
    bbb.setGraph("graph_bbb.txt");
    */

    Graph c(110,"linear");
    Graph cc(110, "reverse");
    Graph ccc(110, "random");
    /*
    //c.setGraph("graph_c.txt");
    //cc.setGraph("graph_cc.txt");
    //ccc.setGraph("graph_ccc.txt");
    */

    Graph d(150,"linear");
    Graph dd(150,"reverse");
    Graph ddd(150,"random");
    /*
    //d.setGraph("graph_d.txt");
    //dd.setGraph("graph_dd.txt");
    //ddd.setGraph("graph_ddd.txt");
    */
    Graph e(250,"linear");
    Graph ee(250,"reverse");
    Graph eee(250,"random");
    /*
    e.setGraph("graph_e.txt");
    ee.setGraph("graph_ee.txt");
    eee.setGraph("graph_eee.txt");
    */

    Graph f(450,"linear");
    Graph ff(450,"reverse");
    Graph fff(450,"random");
    /*
    f.setGraph("graph_f.txt");
    ff.setGraph("graph_ff.txt");
    fff.setGraph("graph_fff.txt");
    */
    Graph g(600,"linear");
    Graph gg(600,"reverse");
    Graph ggg(600,"random");
    /*
    g.setGraph("graph_g.txt");
    gg.setGraph("graph_gg.txt");
    ggg.setGraph("graph_ggg.txt");
    */
    Graph h(800,"linear");
    Graph hh(800,"reverse");
    Graph hhh(800,"random");
    /*
    h.setGraph("graph_h.txt");
    hh.setGraph("graph_hh.txt");
    hhh.setGraph("graph_hhh.txt");
    */
    Graph i(900,"linear");
    Graph ii(900,"reverse");
    Graph iii(900,"random");
    /*
    i.setGraph("graph_i.txt");
    ii.setGraph("graph_ii.txt");
    iii.setGraph("graph_iii.txt");
    */
    Graph j(1000,"linear");
    Graph jj(1000,"reverse");
    Graph jjj(1000,"random");
    /*
    j.setGraph("graph_j.txt");
    jj.setGraph("graph_jj.txt");
    jjj.setGraph("graph_jjj.txt");
    */
    std::cout << "[Generator]: Successfully built 30 graphs." << std::endl;

    std::cout << "[Console]: Running graph(s) data through Dijkstra." << std::endl;
    a.dijkstra("a");
    aa.dijkstra("aa");
    aaa.dijkstra("aaa");
    b.dijkstra("b");
    bb.dijkstra("bb");
    bbb.dijkstra("bbb");
    c.dijkstra("c");
    cc.dijkstra("cc");
    ccc.dijkstra("ccc");
    d.dijkstra("d");
    dd.dijkstra("dd");
    ddd.dijkstra("ddd");
    e.dijkstra("e");
    ee.dijkstra("ee");
    eee.dijkstra("eee");
    f.dijkstra("f");
    ff.dijkstra("ff");
    fff.dijkstra("fff");
    g.dijkstra("g");
    gg.dijkstra("gg");
    ggg.dijkstra("ggg");
    h.dijkstra("h");
    hh.dijkstra("hh");
    hhh.dijkstra("hhh");
    i.dijkstra("i");
    ii.dijkstra("ii");
    iii.dijkstra("iii");
    j.dijkstra("j");
    jj.dijkstra("jj");
    jjj.dijkstra("jjj");

    std::cout << "[Console]: Running graph(s) data through Floyd Warshall." << std::endl;
    a.floydWarshall("a");
    aa.floydWarshall("aa");
    aaa.floydWarshall("aaa");
    b.floydWarshall("b");
    bb.floydWarshall("bb");
    bbb.floydWarshall("bbb");
    c.floydWarshall("c");
    cc.floydWarshall("cc");
    ccc.floydWarshall("ccc");
    d.floydWarshall("d");
    dd.floydWarshall("dd");
    ddd.floydWarshall("ddd");
    e.floydWarshall("e");
    ee.floydWarshall("ee");
    eee.floydWarshall("eee");
    f.floydWarshall("f");
    ff.floydWarshall("ff");
    fff.floydWarshall("fff");
    g.floydWarshall("g");
    gg.floydWarshall("gg");
    ggg.floydWarshall("ggg");
    h.floydWarshall("h");
    hh.floydWarshall("hh");
    hhh.floydWarshall("hhh");
    i.floydWarshall("i");
    ii.floydWarshall("ii");
    iii.floydWarshall("iii");
    j.floydWarshall("j");
    jj.floydWarshall("jj");
    jjj.floydWarshall("jjj");
}


