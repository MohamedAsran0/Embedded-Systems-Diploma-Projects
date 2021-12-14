/*
 ============================================================================
 Name        : Project.c
 Author      : Mohamed Asran
 Description : Vehicle Control system project
 ============================================================================
 */

#include <stdio.h>

void entry(); // for printing the entry message
void entry_action(char entry_char); //for choosing to turn on or off the engine or to quit the program
void Sensors_set_menu(); // for printing the menu that simulates the vehicle sensors readings
void Sensors_set_menu_action(char Sensors_set_menu_char); // for setting the vehicle sensors readings
void traffic_light_color(char color); // for setting the traffic light color
void room_temperature(int temperature); // for setting the room temperature
void engine_temperature(int temperature); // for setting the engine temperature
void current_vehicle_state(); // for displaying the current vehicle state

enum state { OFF , ON };

enum state engineState = OFF , AC = OFF , engineTemperatureController = OFF;

int vehicle_speed = 0, roomTemperature = 35, engineTemperature = 90;

int main()
{
	setvbuf(stdout,NULL,_IONBF,0);
	setvbuf(stderr,NULL,_IONBF,0);

	char entry_char, Sensors_set_menu_char;

	printf("\t\t\t\t\t\tVehicle Control system\n");
	entry();


	do{ // staying in this do_while loop until choosing quit the system

		scanf(" %c", &entry_char);
		entry_action(entry_char);

		if(entry_char == 'a') // if the engine is on
		{

			do{ // staying in this do_while loop until turning off the engine

				scanf(" %c", &Sensors_set_menu_char);
				Sensors_set_menu_action(Sensors_set_menu_char);

			}while(Sensors_set_menu_char != 'a');
		}

	}while(entry_char != 'c');

	printf("Quit the system\n");

	return 0;
}


void entry()
{
	printf("a. Turn on the vehicle engine\nb. Turn off the vehicle engine\nc. Quit the system\n\n");
}

void entry_action(char entry_char)
{
	if(entry_char == 'a')
	{
		printf("Turn on the vehicle engine\n\n");
		engineState = ON;
		Sensors_set_menu();
	}
	else if(entry_char == 'b')
	{
		printf("Turn off the vehicle engine\n\n");
		engineState = OFF;
		entry();
	}
}

void Sensors_set_menu()
{
	printf("a. Turn off the engine\nb. Set the traffic light color.\n");
	printf("c. Set the room temperature (Temperature Sensor)\nd. Set the engine temperature (Engine Temperature Sensor)\n\n");
}

void Sensors_set_menu_action(char Sensors_set_menu_char)
{
	char tr_light_color;
	int  ro_temperature, en_temperature;
	switch(Sensors_set_menu_char)
	{
	case 'a': entry_action('b');
			  break;

	case 'b': printf("Set the traffic light color\n");
			  printf("Please enter 'G' for green, 'O' for orange or 'R' for red\n\n");
			  scanf(" %c", &tr_light_color);
			  traffic_light_color(tr_light_color);
			  current_vehicle_state();
			  Sensors_set_menu();
			  break;

	case 'c': printf("Set the room temperature\n\n");
			  scanf("%d", &ro_temperature);
			  room_temperature(ro_temperature);
			  current_vehicle_state();
			  Sensors_set_menu();
			  break;

	case 'd': printf("Set the engine temperature\n\n");
			  scanf("%d", &en_temperature);
			  engine_temperature(en_temperature);
			  current_vehicle_state();
			  Sensors_set_menu();
			  break;
	}
}

void traffic_light_color(char color)
{
	if((color == 'g') || (color == 'G'))
	{
		vehicle_speed = 100;
	}
	else if((color == 'o') || (color == 'O'))
	{
		vehicle_speed = 30;
	}
	else if((color == 'r') || (color == 'R'))
	{
		vehicle_speed = 0;
	}
}

void room_temperature(int temperature)
{
	if(temperature < 10 || temperature > 30)
	{
		AC = ON;
		roomTemperature = 20;
	}
	else
	{
		AC = OFF;
		roomTemperature = temperature;
	}
}

void engine_temperature(int temperature)
{
	if(temperature < 100 || temperature > 150)
	{
		engineTemperatureController = ON;
		engineTemperature = 125;
	}
	else
	{
		engineTemperatureController = OFF;
		engineTemperature = temperature;
	}
}

void current_vehicle_state()
{
	if(vehicle_speed == 30)
	{
		AC = ON;
		roomTemperature = roomTemperature * (5/4) + 1;
		engineTemperatureController = ON;
		engineTemperature = engineTemperature * (5/4) + 1;
	}

	printf("***************************************\n");

	if(engineState == ON){
		printf("Engine state: ON\n");
	}
	else{
		printf("Engine state: OFF\n");
	}

	if(AC == ON){
		printf("AC: ON\n");
	}
	else{
		printf("AC: OFF\n");
	}

	printf("Vehicle Speed: %d km/hr\n", vehicle_speed);

	printf("Room Temperature: %d C\n", roomTemperature);

	if(engineTemperatureController == ON){
		printf("Engine Temperature Controller State: ON\n");
	}
	else{
		printf("Engine Temperature Controller State: OFF\n");
	}

	printf("Engine Temperature: %d C\n", engineTemperature);

	printf("***************************************\n\n");
}
