/********* a1_functions.c ********
	
	Student Name 	= Joshua Weitzel
	Student Number	= 101301965
*/

#include "a1_functions.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

//User inputs an int
unsigned short int get_input_usi(void){
	int input = 0;
    scanf("%d", &input);
	while (input < 0){
		printf("Int must be positive, re-enter: ");
		scanf("%d", &input);
	}
    return input;
}

//User inputs a float
float get_input_f(void){
	float input = 0.0;
    scanf("%f", &input);
	while (input < 0){
		printf("Number must be positive, re-enter: ");
		scanf("%f", &input);
	}
    return input;
}

//Called to initialize activities inside milestones
void init_activity(activity_t *activity_to_int){
	printf("Initializing activity... \nenter activity id: ");
	activity_to_int->id = get_input_usi();
	printf("Enter activity name: ");
	scanf("%100s", activity_to_int->name);
	printf("Enter duration of activity in hours: ");
	activity_to_int->planned_duration = get_input_f();
	activity_to_int->planned_cost = activity_to_int->planned_duration * 30;
	activity_to_int->actual_cost = 0;
	activity_to_int->actual_duration = 0;
	activity_to_int->completed = false;
}

//Called to initialize milestones in the project
void init_milestone(milestone_t *milestone_to_int, unsigned short int num_activities){
	printf("Initializing milestone... \n");
	printf("enter milestone id: ");
	milestone_to_int->id = get_input_usi();
	printf("Enter milestone name: ");
	scanf("%100s", milestone_to_int->name);

	activity_t arr_actitivities[num_activities];
	for(int i = 0; i < num_activities; i++){
		init_activity(&milestone_to_int->activity_list[i]);
	}
	milestone_to_int->completed = false;
	milestone_to_int->actual_cost = 0;
	milestone_to_int->actual_duration = 0;
}

//Called to initialize project
project_t init_project(char name[], milestone_t *milestone_list, int number_milestones, const int * number_activities){
	project_t proj;
	strcpy(proj.name, name);
	proj.planned_cost = 0;
	proj.planned_duration = 0;
	for(int m = 0; m < number_milestones; ++m, ++number_activities){
		for(int i = 0; i < *number_activities; i++){
			proj.planned_cost += milestone_list[m].activity_list[i].planned_cost;
			proj.planned_duration += milestone_list[m].activity_list[i].planned_duration;
		}
	}
	proj.actual_cost = 0;
	proj.planned_duration = (int) ceil(proj.planned_duration / 8);
	proj.actual_duration = 0;
	proj.completed = false;
	return proj;
}

//Print main menu
void print_main_menu(void){
	printf("1) Update activity \n2) Print stats \n3) Quit \n");
}

//Print milestone stats
void print_milestone_stats(const milestone_t * list_milestones, int num_milestones, const int * number_activities){
	for(int m = 0; m < num_milestones; m++){
		printf("Milestone name: %s\n", list_milestones[m].name);

		int completed_act = 0;
		float total_plan_duration = 0;
		float total_plan_cost = 0;
		for(int a = 0; a < number_activities[m]; a++){
			total_plan_duration += list_milestones[m].activity_list[a].planned_duration;
			total_plan_cost += list_milestones[m].activity_list[a].planned_cost;
			if(list_milestones[m].activity_list[a].completed == true){
				completed_act += 1;
			}
		}

		if(list_milestones[m].completed == false){	
			printf("%d out of %d activites completed \n", completed_act, number_activities[m]);			
			printf("Planned duration: %.2f hours \n", total_plan_duration);	
			printf("Planned cost is %.2f dollars \n", total_plan_cost);

		} else {
			float budget = total_plan_cost - list_milestones[m].actual_cost;
			if(budget >= 0){
				printf("Under budget by %.2f dollars ", budget);
			} else {
				printf("Over budget by %.2f dollars ", budget * -1);
			}

			int days = (int) ceil((total_plan_duration - list_milestones[m].actual_duration) / 8);
			if(days >= 0){
				printf("Early by %d days \n", days);
			} else {
				printf("Late by %d days \n", days * -1);
			}
		}
	} 
}

//Print project stats
void print_project_stats(project_t details, const milestone_t * list_milestones, int num_milestones, const int * number_activities){
	if(details.completed == true){
		float budget = details.planned_cost - details.actual_cost;
		if(budget >= 0){
			printf("Under budget by %.2f dollars ", budget);
		} else {
			printf("Over budget by %.2f dollars ", budget * -1);
		}

		int days = details.planned_duration - details.actual_duration;
		if(days >= 0){
			printf("Early by %d days \n", days);
		} else {
			printf("Late by %d days \n", days * -1);
		}	
	} else {
		print_milestone_stats(list_milestones, num_milestones, number_activities);
	}
}

//Update activity in list of activities
void update_activity(activity_t * activity_to_update){
	printf("Update actual duration... \n");
	activity_to_update->actual_duration = get_input_f();

	printf("Is this activity completed? y/n");
	char status;
	scanf(" %c", &status);
	if(status == 'y'){
		activity_to_update->completed = true;
	}

	activity_to_update->actual_cost = activity_to_update->actual_duration * 30;
}

//Update milestone in list of milestones
void update_milestone(milestone_t * milestone_to_update, int activities_in_milestone){
	//Set default state to complete then run through for loop to check if there are incomplete activities
	milestone_to_update->completed = true;
	for(int a = 0; a < activities_in_milestone; a++){
		if(milestone_to_update->activity_list[a].completed == false){
			milestone_to_update->completed = false;
		}
	}
	if(milestone_to_update->completed == true){
		float total_ac_duration = 0;
		float total_ac_cost = 0;
		for(int a = 0; a < activities_in_milestone; a++){
			total_ac_duration += milestone_to_update->activity_list[a].actual_duration;
			total_ac_cost += milestone_to_update->activity_list[a].actual_cost;
		}
		milestone_to_update->actual_duration = total_ac_duration;
		milestone_to_update->actual_cost = total_ac_cost;
	}
}

//Update project
void update_project(const milestone_t * milestone_array, int num_milestones, const int * number_activities, project_t * my_project){
	//Recalculate actual cost and duration and checks to see if the project is completed
	float total_ac_duration = 0;
	float total_ac_cost = 0;
	my_project->completed = true;
	for(int m = 0; m < num_milestones; m++){
		total_ac_duration += milestone_array[m].actual_duration;
		total_ac_cost += milestone_array[m].actual_cost;
		if(milestone_array[m].completed == false){
			my_project->completed = false;
		}
	}
	my_project->actual_duration = total_ac_duration;
	my_project->actual_cost = total_ac_cost;
}
