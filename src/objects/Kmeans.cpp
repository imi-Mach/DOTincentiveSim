#include "Kmeans.hpp"

/* point method definitions */

Point::Point(int id, string line){
    dimensions = 0;
    pointId = id;
    stringstream is(line);
    double val;
    while(is >> val){
        values.push_back(val);
        dimensions++;
    }
    clusterId = 0; //Initially not assigned to any cluster
}

int Point::getDimensions(){
    return dimensions;
}

int Point::getCluster(){
    return clusterId;
}

int Point::getID(){
    return pointId;
}

void Point::setCluster(int val){
    clusterId = val;
}

double Point::getVal(int pos){
    return values[pos];
}

/* cluster method definitions */

Cluster::Cluster(int clusterId, Point centroid){
    this->clusterId = clusterId;
    for(int i=0; i<centroid.getDimensions(); i++){
        this->centroid.push_back(centroid.getVal(i));
    }
    this->addPoint(centroid);
}

Cluster::void addPoint(Point p){
    p.setCluster(this->clusterId);
    points.push_back(p);
}

Cluster::bool removePoint(int pointId){
    int size = points.size();

    for(int i = 0; i < size; i++)
    {
        if(points[i].getID() == pointId)
        {
            points.erase(points.begin() + i);
            return true;
        }
    }
    return false;
}

Cluster::int getId(){
    return clusterId;
}

Cluster::Point getPoint(int pos){
    return points[pos];
}

Cluster::int getSize(){
    return points.size();
}

Cluster::double getCentroidByPos(int pos) {
    return centroid[pos];
}

Cluster::void setCentroidByPos(int pos, double val){
    this->centroid[pos] = val;
}

/* Kmeans method definitions */

