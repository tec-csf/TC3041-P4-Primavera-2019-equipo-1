#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h> 
#include <string>
using namespace std;

int INITIAL_ID = 0;
int DATA_COUNT = 20000000;
int ITERATIONS = 1;
string HEADER = "# DDL\n\nCREATE DATABASE trafico_analisis\n\n# DML\n\n# CONTEXT-DATABASE: trafico_analisis\n\n";
time_t aTime;

string getID() {
	INITIAL_ID++;
	return to_string(INITIAL_ID);
}

string getEmail() {
	int x = rand() % 3;
	string end;
	int y = rand() % 10;
	string start;
	switch (x) {
	case 0:
		end = "@gmail.com";
		break;
	case 1:
		end = "@hotmail.com";
		break;
	case 2:
		end = "@yahoo.com";
		break;
	default:
		cout << "End error";
	}

	switch (y) {
	case 0:
		start = "goat";
		break;
	case 1:
		start = "pig";
		break;
	case 2:
		start = "cow";
		break;
	case 3:
		start = "horse";
		break;
	case 4:
		start = "duck";
		break;
	case 5:
		start = "rabbit";
		break;
	case 6:
		start = "chicken";
		break;
	case 7:
		start = "pheasant";
		break;
	case 8:
		start = "deer";
		break;
	case 9:
		start = "camel";
		break;
	default:
		cout << "Start error";
	}

	return start + to_string(INITIAL_ID) + end;
}

string getContinent() {
	int x = rand() % 6;
	switch (x) {
	case 0:
		return "Europe";
	case 1:
		return "North America";
	case 2:
		return "South America";
	case 3:
		return "Asia";
	case 4:
		return "Antartica";
	case 5:
		return "Africa";
	default:
		cout << "Continent error";
	}
	return "";
}

string getDiscovery() {
	return to_string((rand() % 1000) + 1000);
}

string getDescription(int coches) {
	if(coches > 1200) return "tráfico pesado";
	else if (coches < 360) return "tráfico ligero";
	else return "tráfico normal";
}

int getCoches(int hour) {
	int coches = rand() % 50 + 50;
	float multiplier = 0;
	switch (hour) {
	case 2: case 3: case 4: case 5:
		multiplier = 1;
		break;
	case 23: case 0:  case 1:
		multiplier = 5;
		break;
	case 21: case 22:
		multiplier = 10;
		break;
	case 6: case 10: case 11: case 12: case 13: case 14: case 15: case 16: case 19: case 20:
		multiplier = 15;
		break;
	case 7: case 8: case 9: case 17: case 18:
		multiplier = 20;
		break;
	default:
		cout << "Error getting car numbers";
	}
	return coches * multiplier;
}

string getTimeIncrease() {
	string timeToRet = to_string(aTime);
	aTime = aTime + 3600;	//Increase by an hour
	return timeToRet;
}

int getQuality(int hour) {
	int quality = 0;
	switch (hour) {
	case 2: case 3: case 4: case 5:
		quality = rand() % 50 + 50;
		return quality;
	case 23: case 0:  case 1:
		quality = rand() % 100;
		return quality;
	case 21: case 22:
		quality = rand() % 100 + 50;
		return quality;
	case 6: case 10: case 11: case 12: case 13: case 14: case 15: case 16: case 19: case 20:
		quality = rand() % 150 + 100;
		return quality;
	case 7: case 8: case 9: case 17: case 18:
		quality = rand() % 150 + 150;
		return quality;
	default:
		cout << "Error getting quality";
	}
}

int getNoise(int hour) {
	int noise = 0;
	switch (hour) {
	case 2: case 3: case 4: case 5:
		noise = rand() % 20 + 5;
		return noise;
	case 23: case 0:  case 1:
		noise = rand() % 20 + 10;
		return noise;
	case 21: case 22:
		noise = rand() % 20 + 30;
		return noise;
	case 6: case 10: case 11: case 12: case 13: case 14: case 15: case 16: case 19: case 20:
		noise = rand() % 20 + 40;
		return noise;
	case 7: case 8: case 9: case 17: case 18:
		noise = rand() % 20 + 60;
		return noise;
	default:
		cout << "Error getting quality";
	}
}

int writeFile()
{
	ofstream myfile;
	string queryString;
	string filename;

	for (int j = 0; j < ITERATIONS; j++) {
		filename = "data" + to_string(j) + ".txt";
		myfile.open(filename);
		for (int i = 0; i < DATA_COUNT; i++) {
			queryString = "INSERT INTO AnimalsOnTheInternet (id,email,continent, discovery) VALUES (" + getID() + ", '" + getEmail() + "', '" + getContinent() + "', " + getDiscovery() + ");\n";
			myfile << queryString;
		}
		myfile.close();
		cout << "Done " << j << "\n";
	}


	return 0;
}

int writeFile2()
{
	ofstream myfile;
	string queryString;
	string filename;

	for (int j = 0; j < ITERATIONS; j++) {			//Each iteration is a new file
		filename = "data" + to_string(j) + ".txt";
		myfile.open(filename);
		myfile << HEADER;

		aTime = 1556341200;
		for (int i = 0; i < DATA_COUNT; i++) {		//numberOfData pieces, one per line
			int hour = i % 24;
			int coches = getCoches(hour);
			queryString = "car_count,location=av_de_los_poetas coches="; 
			queryString += to_string(coches);
			queryString += ",trafico\\ description=\"" + getDescription(coches);
			queryString += "\" " + getTimeIncrease();
			queryString += "\n";
			myfile << queryString;
		}

		aTime = 1556341200;
		for (int i = 0; i < DATA_COUNT; i++) {
			int hour = i % 24;
			int coches = getCoches(hour);
			queryString = "air_quality,location=av_de_los_poetas quality=";
			queryString += to_string(getQuality(hour));
			queryString += " " + getTimeIncrease();
			queryString += "\n";
			myfile << queryString;
		}

		aTime = 1556341200;
		for (int i = 0; i < DATA_COUNT; i++) {
			int hour = i % 24;
			int coches = getCoches(hour);
			queryString = "avg_noise,location=av_de_los_poetas noise_dB=";
			queryString += to_string(getNoise(hour));
			queryString += " " + getTimeIncrease();
			queryString += "\n";
			myfile << queryString;
		}

		aTime = 1556341200;
		for (int i = 0; i < DATA_COUNT; i++) {		//numberOfData pieces, one per line
			int hour = i % 24;
			int coches = getCoches(hour);
			queryString = "car_count,location=av_carlos_lazo coches=";
			queryString += to_string(coches);
			queryString += ",trafico\\ description=\"" + getDescription(coches);
			queryString += "\" " + getTimeIncrease();
			queryString += "\n";
			myfile << queryString;
		}

		aTime = 1556341200;
		for (int i = 0; i < DATA_COUNT; i++) {
			int hour = i % 24;
			int coches = getCoches(hour);
			queryString = "air_quality,location=av_carlos_lazo quality=";
			queryString += to_string(getQuality(hour));
			queryString += " " + getTimeIncrease();
			queryString += "\n";
			myfile << queryString;
		}

		aTime = 1556341200;
		for (int i = 0; i < DATA_COUNT; i++) {
			int hour = i % 24;
			int coches = getCoches(hour);
			queryString = "avg_noise,location=av_carlos_lazo noise_dB=";
			queryString += to_string(getNoise(hour));
			queryString += " " + getTimeIncrease();
			queryString += "\n";
			myfile << queryString;
		}

		myfile.close();
		cout << "Done " << j << "\n";
	}


	return 0;
}

int main()
{
	int x;
	srand(time(NULL));
	writeFile2();
	cin >> x;
}
