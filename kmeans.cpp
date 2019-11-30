#include<iostream>
#include<vector>
#include<map>
#include<ctime>
#include<cmath>
#include<string>

using namespace std;

typedef double TYPE_DATA;
typedef pair<TYPE_DATA, TYPE_DATA> simple_point;
typedef map<simple_point, string> point;
typedef map<point, vector<double>> distances;

point generate_centroids(const int K,const string *labels) {
    srand(time(NULL));
    point centroids;
    for(int i = 0; i < K; i++) {
        const int x = rand()%5;
        const int y = rand()%5;
        simple_point point = make_pair(x,y);
        centroids.insert(make_pair(point,labels[i]));
    }

    return centroids;
}

double cal_distance(simple_point p1, simple_point p2){
    TYPE_DATA distance_x = p1.first - p2.first;
    TYPE_DATA distance_y = p1.second - p2.second;
    return sqrt((distance_x*distance_x) + (distance_y*distance_y));
}

bool centroids_change(point original, point copy) {
    return original != copy;
}

string get_new_centroid(simple_point current_point, point centroids) {
    double distance = cal_distance(current_point, centroids.begin()->first);
    double shortest_distance = distance;
    string new_label = centroids.begin()->second;
    for(auto& centroid: centroids){
        distance = cal_distance(current_point, centroid.first);
        if(distance < shortest_distance) {
            shortest_distance = distance;
            new_label = centroid.second;
        }
    }
    return new_label;
}

vector<simple_point> getCentroidPoints(point points, string centroid_name) {
    vector<simple_point> array;
    for(auto& point: points) {
        if(point.second == centroid_name){
            array.push_back(point.first);
        }
    }
    return array;
}

simple_point move_centroids(pair<simple_point, string> centroid, point points) {
    double distance_x_sum = 0;
    double distance_y_sum = 0;
    vector<simple_point> centroid_points = getCentroidPoints(points, centroid.second);
    for(int i = 0; i < centroid_points.size(); i++) {
        distance_x_sum += centroid_points[i].first;
        distance_y_sum += centroid_points[i].second;
    }
    double new_x = distance_x_sum/centroid_points.size();
    double new_y = distance_y_sum/centroid_points.size();
    simple_point new_position = make_pair(new_x, new_y);
    return new_position;
}

void kmeans(const int K, point data, const string *labels){
    cout << "INICIANDO KMEANS" << endl;

    // cout << "IMPRIMINDO DADOS" << endl;
    // for(auto& point: data){
    //     cout << "X: " << point.first.first << " Y: " << point.first.second << endl;
    // }

    cout << "GERANDO CENTROIDES" << endl;
    point centroids = generate_centroids(K,labels);
    point copy_centroids = centroids;
    // cout << "IMPRIMINDO CENTROIDES" << endl;
    // for(auto& centroid: centroids){
    //     cout << "COR: " << centroid.second << " X: " << centroid.first.first << " Y: " << centroid.first.second << endl;
    // }

    cout << "ATUALIZANDO CENTROIDE - INICIAL" << endl;
    for(auto& point: data) {
        point.second = get_new_centroid(point.first, centroids);
    }

    // cout << "IMPRIMINDO CENTROIDE - INICIAL" << endl;
    // for(auto& point: data) {
    //     cout << "PONTO ";
    //     cout << "X: " << point.first.first << " Y: " << point.first.second;
    //     cout << " Centroide " << point.second << endl;
    // }
    int m = 0;
    do {
        copy_centroids = centroids;
        cout << "IMPRIMINDO CENTROIDES ERA :" << m+1 << endl;
        for(auto& centroid: centroids){
            cout << "COR: " << centroid.second << " X: " << centroid.first.first << " Y: " << centroid.first.second << endl;
        }

        // cout << "IMPRIMINDO CENTROIDE ANTES" << endl;
        cout << "IMPRIMINDO  PONTOS" << endl;
        for(auto& point: data) {
            cout << "PONTO ";
            cout << "X: " << point.first.first << " Y: " << point.first.second;
            cout << " Centroide: " << point.second << endl;
        }

        cout << "ANDANDO O CENTROIDE" << endl;
        for(auto& centroid: centroids) {
            string color = centroid.second;
            simple_point new_point = move_centroids(centroid, data);
            centroids.erase(centroid.first);
            centroids.insert(make_pair(new_point, color));
        }

        cout << "ATUALIZANDO CETROIDE" << endl;
        for(auto& point: data) {
            point.second = get_new_centroid(point.first, centroids);
        }

        // cout << "IMPRIMINDO CENTROIDE DEPOIS" << endl;
        // for(auto& point: data) {
        //     cout << "PONTO ";
        //     cout << "X: " << point.first.first << " Y: " << point.first.second;
        //     cout << " Centroide " << point.second << endl;
        // }
        m++;
    }while(centroids_change(centroids, copy_centroids));

    cout << endl;
    cout << "RESULTADOS FINAIS" << endl;
    cout << "ERAS NECESSARIAS " << m << endl;

    cout << "IMPRIMINDO CENTROIDES" << endl;
    for(auto& centroid: centroids){
        cout << "COR: " << centroid.second << " X: " << centroid.first.first << " Y: " << centroid.first.second << endl;
    }

    cout << "IMPRIMINDO  PONTOS" << endl;
    for(auto& point: data) {
        cout << "PONTO ";
        cout << "X: " << point.first.first << " Y: " << point.first.second;
        cout << " Centroide: " << point.second << endl;
    }
}

int main() {
    const int K = 2;
    point data;
    vector<simple_point> point;

    point.push_back(make_pair(0,1));
    point.push_back(make_pair(1,0));
    point.push_back(make_pair(1,3));
    point.push_back(make_pair(3,1));
    point.push_back(make_pair(4,2));
    point.push_back(make_pair(4,3));

    for(int i = 0; i < point.size(); i++) {
        data.insert(make_pair(point[i],"none"));
    }

    string labels[2] = {"azul", "vermelho"};
    kmeans(K, data, labels);

    return 0;
}