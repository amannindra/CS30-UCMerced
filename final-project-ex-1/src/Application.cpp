#include "Graph.h"
#include <Application.h>
#include <FL/Enumerations.H>
#include <FL/Fl_Scroll.H>
#include <bobcat_ui/bobcat_ui.h>
#include <bobcat_ui/button.h>
#include <bobcat_ui/dropdown.h>
#include <bobcat_ui/textbox.h>
#include <bobcat_ui/window.h>
#include <climits>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace bobcat;
using namespace std;

Application::Application() {
    // App's constructor
    initData();
    initInterface();
}

void Application::handleClick(bobcat::Widget *sender) {
    cout << "------------------------------------------------------------------"
            "-------------------------------------------------"
         << endl;
    results->clear();
    window->redraw();

    int startIndex = start->value();
    int destIndex = dest->value();
    int selectOption = options->value();
    // system("clear");

    Waypoint *path = nullptr;

    if (selectOption == 0) {
        cout << "Cheapest Price" << endl;
        path = g.ucs(cities[startIndex], cities[destIndex], selectOption);
    } else if (selectOption == 1) {
        cout << "Shortest Travel Time" << endl;
        path = g.ucs(cities[startIndex], cities[destIndex], selectOption);
    } else {
        cout << "Least number of Stops" << endl;
        path = g.bfs(cities[startIndex], cities[destIndex]);
    }

    if (path) {
        Waypoint *temp = path;
        cout << "Intial Temp: " << temp << endl;
        vector<string> pathCities;

        int y = results->y() + 10;
        int getTotalTime = path->totalTime;
        int getTotalCost = path->totalCost;
        int stopNum = 0;
        while (temp != nullptr) {
            stopNum += 1;
            results->add(new TextBox(40, y, 300, 25, temp->vertex->data));
            y += 40;
            if (temp->parent != nullptr) {
                if (selectOption == 0) {
                    results->add(
                        new TextBox(40, y, 300, 25,
                                    "    Price: $" + to_string(temp->weight)));
                } else if (selectOption == 1) {
                    results->add(new TextBox(
                        40, y, 300, 25,
                        "    Flight Time: " + to_string(temp->weight) +
                            " hours"));
                }
                else {
                    results->add(new TextBox(80, y, 300, 25, "Adding stop"));
                }

                y += 40;
            }

            cout << temp->vertex->data << " " << temp->partialCost << endl;

            temp = temp->parent;

            window->redraw();
        }

        if (stopNum == 1) {
            stopNum = 0;
        } else if (stopNum == 2) {
            stopNum = 1;
        } else {
            stopNum -= 1;
        }
        if (selectOption == 2) {

            results->add(new TextBox(40, y, 300, 25,
                                     "  Total Stop: " + to_string(stopNum)));
        }

        totalTime->label("Total Time: " + to_string(getTotalTime));
        cost->label("Cost: " + to_string(getTotalCost));
        stops->label("Stops: " + to_string(stopNum));
    }

    window->redraw();
}

void Application::initData() {

    fstream vertFile("assets/vertices.csv");

    if (vertFile.is_open()) {
        string line;
        while (getline(vertFile, line)) {
            cities.append(new Vertex(line));
        }
        vertFile.close();
    } else {
        cout << "vertices file can't open" << endl;
    }

    for (int i = 0; i < cities.size(); i++) {
        g.addVertex(cities[i]);
    }

    fstream edgeFile("assets/edges.csv");

    if (edgeFile.is_open()) {
        string line;

        while (getline(edgeFile, line)) {
            string start, end, time, cost;
            stringstream lp(line);
            getline(lp, start, ',');
            getline(lp, end, ',');
            getline(lp, time, ',');
            getline(lp, cost, ',');

            int uStart = stoi(start);
            int vEnd = stoi(end);
            int timed = stoi(time);
            int costed = stoi(cost);

            g.addEdge(cities[uStart], cities[vEnd], timed, costed);
        }
    } else {
        cout << "edgefile file can't open" << endl;
    }
}

void Application::initInterface() {
    window = new Window(100, 100, 400, 560, "Flight Planner");

    start = new Dropdown(20, 40, 360, 25, "Starting Point");
    dest = new Dropdown(20, 100, 360, 25, "Destination");

    options = new Dropdown(20, 160, 360, 25, "Options");
    search = new Button(20, 220, 360, 25, "Search");
    totalTime = new TextBox(20, 480, 360, 25, "Total Time: ");
    cost = new TextBox(20, 500, 360, 25, "Cost: ");
    stops = new TextBox(20, 520, 360, 25, "Stops: ");
    results = new Fl_Scroll(20, 280, 350, 180, "Results");

    options->add("Cheapest Price");
    options->add("Shortest travel Time");
    options->add("least number of Stops");

    for (int i = 0; i < cities.size(); i++) {
        start->add(cities[i]->data);
        dest->add(cities[i]->data);
    }

    ON_CLICK(search, Application::handleClick);

    results->align(FL_ALIGN_TOP_LEFT);
    results->box(FL_THIN_UP_BOX);

    window->show();
}

// string pathStr;

// for (int i = (int)pathCities.size() - 1; i >= 0; i--) {
//     pathStr += pathCities[i];
//     if (i > 0) {
//         pathStr += " -> ";
//     }
// }
// cout << "pathStr: " << pathStr << endl;

// int y = results->y() + 10;
// results->add(new TextBox(
//     40, y, 300, 25,
//     "Path" + pathStr));
// y += 30;

// int numStops = (int)pathCities.size() - 1;

// results->add(new TextBox(
//     40, y, 300, 25,
//     "Number of Stops: " + to_string(numStops)));

// if (path && selectOption == 2) {
//     cout << "We found a path" << endl;
//     Waypoint *temp = path;
//     int y = results->y() + 10;
//     while (temp != nullptr) {
//         results->add(new TextBox(40, y, 300, 25, temp->vertex->data));
//         y += 40;
//         if (temp->parent != nullptr) {
//             if (selectOption == 0) {
//                 results->add(new TextBox(
//                     40, y, 300, 25,
//                     "    Cheapest Price: " + to_string(temp->weight) +
//                         " hours"));
//             }
//             if (selectOption == 1) {
//                 results->add(new TextBox(
//                     40, y, 300, 25,
//                     "     Shorten Travel Time: " +
//                     to_string(temp->weight) +
//                         " hours"));
//             }
//             else{
//                 results->add(new TextBox(
//                     40, y, 300, 25,
//                     "     Least number of stops: " +
//                     to_string(temp->weight) +
//                         " hours"));
//             }

//             y += 40;
//         }
//         cout << temp->vertex->data << " " << temp->partialCost << endl;
//         temp = temp->parent;

//         window->redraw();
//     }
// } else {
//     results->add(new TextBox(10,10,100,25,"No Path"));
//     cout << "There is no path" << endl;
// }

// string pathStr;

// for (int i = (int)pathCities.size() - 1; i >= 0; i--) {
//     cout << "Going in forloop" << endl;
//     pathStr += pathCities[i];
//     if (i > 0) {
//         pathStr += " -> ";
//     }
// }
// cout << "pathStr: " << pathStr << endl;

// int y = results->y() + 10;
// results->add(new TextBox(20, y, 300, 25, "Path: "));
// y += 30;

// results->add(new TextBox(20, y, 300, 25, pathStr));
// y += 30;