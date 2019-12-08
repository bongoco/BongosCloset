#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <curl\curl.h>
//#include <C:\Users\Jason\Downloads\curl-master\curl-master\include\curl\curl.h>
//#include <E:\E-Files\- Purdue -\CNIT315\Project Files\curl-master\include\curl\curl.h>

typedef struct Data
{
	char city[20];
	double tempMin, tempMax;
	int humidity;
	double wind;
} Data;

Data fillData(char* city, double tempMin, double tempMax, int humidity, double wind);
int* decide(Data data);

int main() {
  Data currentCity;
  int play = 0;
  int set = 0;
  int pick;
  char city[50] = "";
  Data irvineSample = fillData("Irvine", 7.2, 13, 57, 1.5);
  Data chicagoSample = fillData("Chicago", -2.22, 1.11, 81, 6.7);

  
  printf("========== Welcome to Bongo's Closet ==========\n");
  printf("Bongo's closet is a live app that recommends clothes\nto wear based on the weather around you.\n\n");

  while (play == 0) { 
  printf("========== Menu ==========\n1. Input/View City\n2. View Weather\n3. Clothing Recommendation\n4. Clear City\n5. Exit\n==========================\n\n");
  scanf("%d", &pick);

  if (pick == 1) {
    if (set == 0) {
    printf("Please enter a city:\n");
    scanf("%s", city);
    //hardcode
    if (strcmp(irvineSample.city, city) == 0) {
      printf("You have set your city as Irvine.\n\n");
      currentCity = irvineSample;
      set = 1;
    }
    else if (strcmp(chicagoSample.city, city) == 0) {
      printf("You have set your city as Chicago.\n\n");
      currentCity = chicagoSample;
      set = 1;
    }
    else {
      printf("City not found.\n\n");
    }
    }
    else {
      printf("Your current city is %s\n\n", city);
    }

  }

  if (pick == 2) {
    if (set == 1) {
    printf("========== Weather in %s ==========\n", city);
    printf("Minimum Temperature: %f\n", currentCity.tempMin);
    printf("Maximum Temperature: %f\n", currentCity.tempMax);
    printf("Humidity: %d\n", currentCity.humidity);
    printf("Wind: %f mph\n\n", currentCity.wind);
    }
    else {
      printf("You have not set a city.\n\n");
    }
  }
  
  if (pick == 3) {
    if (set == 1) {
      printf("========== Clothing Recommendations ==========\n");
      printf("At %f C right now, we recommend you dress in long sleeves and long pants in %s.\n\n", currentCity.tempMax, city);
    }
    else {
      printf("You have not set a city.\n\n");
    }
  }

  if (pick == 4) {
    set = 0;
    printf(("City has been cleared.\n\n"));
  }  
  
  if (pick == 5) {
    play = 1;
  }

  }
}

Data fillData(char* city, double tempMin, double tempMax, int humidity, double wind)
{
	Data newData;

	strcpy(newData.city, city);
	newData.tempMin = tempMin;
	newData.tempMax = tempMax;
	newData.humidity = humidity;
	newData.wind = wind;

	return newData;
}

int* decide(Data data)
{
	int* dress = malloc(3 * sizeof(int)); // Jacket, shirt, pants: 0 = none/tshirt/shorts, 1 = yes/long sleeve/pants
	//int dress[3] = { 0, 0, 0 }; 
	int temp;     // Temp variable will determine what to dress for

	// Base temp is the average of max and min temps
	temp = (data.tempMin + data.tempMax) / 2;
	// Factor in windchill. Assumes each m/s increase in wind = -2* C
	temp -= data.wind * 2;
	
	if (temp > 25) // Tshirt and shorts weather
	{
		// Do nothing
	}
	else if (temp > 15) // Tshirt and long pants weather
	{
		dress[2] = 1;
	}
	else if (temp > -20) // Long sleeves and long pants weather
	{
		dress[1] = 1;
		dress[2] = 1;
	}
	else
	{
		dress[0] = 1;
		dress[1] = 1;
		dress[2] = 1;
	}

	if (data.humidity > 100)
	{
		if (temp > 25) // If the temp is >15*C and >50% humitidy, dress for hot, humid weather, not rain
		{
			dress[1] = 0;
			dress[2] = 0;
		}
		else // Dress for rain
		{
			dress[0] = 1;
		}
	}

	return dress;
}

/*int main(void)
{
	CURL *curl;
	CURLcode res;

	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "http://api.openweathermap.org/data/2.5/weather?q=Irvine&APPID=3830d62cb65bd7db9662b96b7454faf9");
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

		res = curl_easy_perform(curl);
		if (res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
			curl_easy_strerror(res));

		curl_easy_cleanup(curl);
	}
	return 0;
}*/