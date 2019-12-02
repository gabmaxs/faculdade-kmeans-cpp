#include<iostream>
#include<vector>
#include<map>
#include<ctime>
#include<cmath>
#include<string>
#include<fstream>

using namespace std;

typedef double TYPE_DATA;
typedef pair<TYPE_DATA, TYPE_DATA> simple_point;
typedef map<simple_point, string> point;
typedef map<point, vector<double>> distances;

const string colors[15] = {
    "#0000ff",
    "#ff0000",
    "#ffff00",
    "#66ff66",
    "#ff0099",
    "#808080",
    "#ff8000",
    "#8000ff",
    "#c0c0c0",
    "#00ffff",
    "#008080",
    "#000080",
    "#800000",
    "#00ff00",
    "#808000"
};

point generate_centroids(const int K, int size) {
    srand(time(NULL));
    point centroids;
    for(int i = 0; i < K; i++) {
        const int x = rand()%size;
        const int y = rand()%size;
        simple_point point = make_pair(x,y);
        centroids.insert(make_pair(point,colors[i]));
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

void save_result(point centroids, point data, int K, string file_name) {

    ofstream myfile;
    myfile.open("saidas/" + file_name);

    myfile << "RESULTADOS FINAIS" << endl;

    myfile << "IMPRIMINDO CENTROIDES" << endl;
    for(auto& centroid: centroids){
        myfile << "COR: " << centroid.second << " X: " << centroid.first.first << " Y: " << centroid.first.second << endl;
    }

    myfile << "IMPRIMINDO  PONTOS" << endl;
    for(auto& point: data) {
        myfile << "PONTO ";
        myfile << "X: " << point.first.first << " Y: " << point.first.second;
        myfile << " Centroide: " << point.second << endl;
    }

    myfile.close();

    //SAIDA PARA ARQUIVO NORMAL

    myfile.open("saidas_numeros/" + file_name);

    myfile << K << endl;


    for(auto& centroid: centroids){
        myfile << centroid.first.first << " " << centroid.first.second << " " << centroid.second << endl;
    }

    for(auto& point: data) {
        myfile << point.first.first << " " << point.first.second;
        myfile << " " << point.second << endl;
    }

    myfile.close();
}

int getGraphSize(point data) {
    int biggest = 0;
    for(auto& point: data) {
        if(point.first.first > biggest)
            biggest = point.first.first;
    }

    return biggest;
}

vector<point> kmeans(const int K, point data){
    int size = getGraphSize(data);
    point centroids = generate_centroids(K, size);
    point copy_centroids = centroids;
    point new_centroids;
    
    for(auto& point: data) {
        point.second = get_new_centroid(point.first, centroids);
    }
    int m = 0;
    do {
        copy_centroids = centroids;
        for(auto& centroid: centroids) {
            string color = centroid.second;
            simple_point new_point = move_centroids(centroid, data);
            pair<simple_point, string> new_centroid = make_pair(new_point, color);
            new_centroids.insert(new_centroid);
        }
        centroids.clear();
        centroids = new_centroids;
        new_centroids.clear();

        for(auto& point: data) {
            point.second = get_new_centroid(point.first, centroids);
        }

        m++;
    }while(centroids_change(centroids, copy_centroids));

    vector<point> result;
    result.push_back(centroids);
    result.push_back(data);

    return result;
}

point read_data(){
    point data;
    TYPE_DATA x, y;
    simple_point positions;
    int size;
    cin >> size;
    for(int i = 0; i < size; i++) {
        cin >> x >> y;
        positions = make_pair(x,y);
        data.insert(make_pair(positions, "none"));
    }

    return data;
}

int main(int argc, char *argv[]) {
    const int K = 10;
    point data;
    vector<point> result;

    string file = "saida.txt";

    if(argv[1] == string("-f")) {
        file = argv[2];
    }
    
    data = read_data();

    result = kmeans(K, data);

    save_result(result[0], result[1], K, file);

    if(argc > 3) {
        if(argv[3] == string("-v")) {
            cout << endl;
            cout << "RESULTADOS FINAIS" << endl;

            cout << "IMPRIMINDO CENTROIDES" << endl;
            for(auto& centroid: result[0]){
                cout << "CENTROIDE";
                cout << "COR: " << centroid.second << " X: " << centroid.first.first << " Y: " << centroid.first.second << endl;
            }

            cout << "IMPRIMINDO  PONTOS" << endl;
            for(auto& point: result[1]) {
                cout << "PONTO ";
                cout << "X: " << point.first.first << " Y: " << point.first.second;
                cout << " Centroide: " << point.second << endl;
            }
        }
    }

    return 0;
}