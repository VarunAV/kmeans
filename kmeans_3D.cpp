#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Point {
	public:
	
	float x, y, z;

	Point(){

	}

	Point(float a, float b, float c){
		x = a;
		y = b;
		z = c;
	}

	float getX(){
		return x;
	}

	float getY(){
		return y;
	}

	float getZ(){
		return z;
	}
};

class Cluster{

	public: 
	
	vector <Point> clusterPoints;
    vector <int> :: iterator i;
    Point centroid;

    Cluster(Point cen){
    	centroid = cen;
    }

	Cluster(Point cen, vector <Point> points){
		clusterPoints = points;
		centroid = cen;
	}

	void setCentroid(Point cen){
		centroid = cen;
	}

	Point getCentroid(){
		return centroid;
	}

	void addPoint(Point point){
		clusterPoints.push_back(point);
	}

	vector <Point> getClusterPoints()
	{
		return clusterPoints;
	}

	void clearCluster(){
		clusterPoints.clear();
	}
};

float calculateEucledianDistance(Point a, Point b);
Point calculateCentroid(vector <Point> points);

int main(int argc, char *argv[]){
	
	int num_clusters = 2;
	float a, b, c;
	float min_dist, dist;
	int index, end=0;
	vector <Point> points;
	vector <Cluster> clusters, vintage_clusters, b_clusters;
	vector <Point> :: iterator i;

	ifstream infile("points.txt");
	while (infile >> a >> b >> c)
	{
	    points.push_back(Point(a, b, c));
	}

	for(int i=0; i<num_clusters; i++)
 		clusters.push_back(Cluster(points[i]));

 	b_clusters = clusters;


 	while(1){

	 	for(int i=0; i<points.size(); ++i){
	 		for(int j=0; j<clusters.size(); ++j){
				dist = calculateEucledianDistance(points[i], clusters[j].getCentroid());
				cout << dist << ' ';
				if (j == 0){
					min_dist = dist;
					index = j;
				}else{
					if (min_dist > dist){
						min_dist = dist;
						index = j;
					}
				}


	 		}
	 		cout << ' ' << min_dist << ' ' << index << endl;
	 		clusters[index].addPoint(points[i]);
	 	}

	 	vintage_clusters = clusters;

	 	for(int i=0; i<clusters.size(); ++i){
	 		// cout << vintage_clusters.size() << "\n";
	 		// cout << calculateEucledianDistance(vintage_clusters[i].getCentroid(), clusters[i].getCentroid()) << endl;
	 		clusters[i].setCentroid(calculateCentroid(clusters[i].getClusterPoints()));

	 		if((vintage_clusters.size() != 0) && (calculateEucledianDistance(vintage_clusters[i].getCentroid(), clusters[i].getCentroid()) == 0)){
	 			end = 1;
	 		}else{
	 			end = 0;
	 		}
	 		cout << clusters[i].getCentroid().getX() << ' ' << clusters[i].getCentroid().getY() << ' ' << clusters[i].getCentroid().getZ() << ' ' << clusters[i].getClusterPoints().size() << endl;
	 			 		clusters[i].clearCluster();

	 		// cout << vintage_clusters[i].getCentroid().getX() << ' ' << vintage_clusters[i].getCentroid().getY() << ' ' << vintage_clusters[i].getCentroid().getZ() << ' ' << vintage_clusters[i].getClusterPoints().size() << endl;

	 	}

	 	if(end == 1)
	 		break;

	 	vintage_clusters = clusters;
	 }
	return 0;
}

float calculateEucledianDistance(Point a, Point b){

	float x = a.getX() - b.getX();
	float y = a.getY() - b.getY();
	float z = a.getZ() - b.getZ();

	float dist;

	dist = pow(x, 2) + pow(y, 2) + pow(z, 2);
	dist = sqrt(dist);                  

	return dist;
}

Point calculateCentroid(vector <Point> points){

	float x=0, y=0, z=0;
	for(int i=0; i<points.size(); ++i){
		x += points[i].getX();
		y += points[i].getY();
		z += points[i].getZ();
	}
	x = (float) x / (float) points.size();
	y = (float) y / (float) points.size();
	z = (float) z / (float) points.size();

	return Point(x, y, z);
}
