#ifndef KMEANS
#define KMEANS

#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

class Point{

    public:
        Point(int id, string line);
        int getDimensions();
        int getCluster();
        int getID();
        void setCluster(int val);
        double getVal(int pos);
    private:
        int pointId, clusterId;
        int dimensions;
        vector<double> values;
};

class Cluster{

    private:
        int clusterId;
        vector<double> centroid;
        vector<Point> points;
    public:
        Cluster(int clusterId, Point centroid);
        void addPoint(Point p);
        bool removePoint(int pointId);
        int getId();
        Point getPoint(int pos);
        int getSize();
        double getCentroidByPos(int pos);
        void setCentroidByPos(int pos, double val);
};

class KMeans{
    private:
        int K;
        int iters;
        int dimensions;
        int total_points;
        vector<Cluster> clusters;
        int getNearestClusterId(Point point);
    public:
        KMeans(int K, int iterations);
        void run(vector<Point>& all_points);

};

#endif