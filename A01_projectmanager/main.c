/********* main.c ********
	
	Student Name 	= Joshua Weitzel
	Student Number	= 101301965
*/

//Complete the includes
#include <stdlib.h>
#include <stdio.h>
#include "a1_functions.h"

int main()
{
   

    /** 1-  Display a welcome message **/

    printf("Welcome to the project manager... ");


    /** 2- Get the project's name and number of milestones **/

    char projname[100] = "";
    printf("Enter project name: ");
    scanf("%100s", projname);
    printf("Enter # of milestones in project: ");
    int num_miles = get_input_usi();
    while(num_miles > 5){
        printf("Too many milestones. Enter a new number... ");
        num_miles = get_input_usi();
    }
    
    /** 3- Initialize all milestones and activities.
     * You need an array of milestones. 
     * The capacity of the array must be the max number of milestones the program 
     * can handle as per the instructions **/

    //Create array of milestones to be initialized
    milestone_t arr_milestones[num_miles]; 

    //Create an empty array to store the number of activites in each milestone
    int number_activities[num_miles];

    //Initialize milestones and activities within
    for(int m = 0; m < num_miles; m++){
        printf("Enter number of activities in milestone: ");
        int loc_num_activities = get_input_usi();
        while(loc_num_activities > 3){
            printf("Too many activities. Enter a new number...");
            loc_num_activities = get_input_usi();
        }
        number_activities[m] = loc_num_activities;
        init_milestone(&arr_milestones[m], loc_num_activities);
    }

    //Check for replica milestone id's
    bool are_replicas = true;
    while(are_replicas == true){
        are_replicas = false;
        for(int m = 0; m < num_miles; m++){
            for(int i = m + 1; i < num_miles; i++){
                if(arr_milestones[m].id == arr_milestones[i].id){
                    printf("%d is already a milestone id. Enter a new id... ", arr_milestones[m].id);
                    arr_milestones[m].id = get_input_usi();
                    are_replicas = true;
                }
            }
        }
    }

    //Check for replica activity id's across all milestones
    are_replicas = true;
    while(are_replicas == true){
        are_replicas = false;
        for(int m = 0; m < num_miles; m++){
            for(int a = 0; a < number_activities[m]; a++){
                for(int i = a + 1; i < number_activities[m]; i++){
                    if(arr_milestones[m].activity_list[a].id == arr_milestones[m].activity_list[i].id){
                        printf("%d is already an activity id. Enter a new id...", arr_milestones[m].activity_list[a].id);
                        arr_milestones[m].activity_list[a].id = get_input_usi();
                        are_replicas = true;
                    }
                }
            }
        }
    }

    /** 4- Initialize the project **/

    project_t details = init_project(projname, arr_milestones, num_miles, number_activities);

    /** 5- Print the main menu **/
    print_main_menu();
   

    /** 6- Get user choice and handle it as per the instructions**/
    int response = get_input_usi();
    while(response != 3){
        while(response > 3){
            printf("Not a valid option. Enter a new number: ");
            response = get_input_usi();
        }
        if(response == 1){
            //Update activity
            for(int m = 0; m < num_miles; m++){
                for(int a = 0; a < number_activities[m]; a++){
                    //Print activity id and name pairs
                    if(arr_milestones[m].activity_list[a].completed == false){
                        printf("Activity ID: %d,\nName: %-100s\n", arr_milestones[m].activity_list[a].id, arr_milestones[m].activity_list[a].name);
                    }
                }
            }

            printf("Enter activity ID to update: ");
            int entered_id = get_input_usi();
            //Find the activity and call to update it
            bool valid_id = false;
            while(valid_id == false){
                for(int m = 0; m < num_miles; m++){
                    for(int a = 0; a < number_activities[m]; a++){
                        if(entered_id == arr_milestones[m].activity_list[a].id){
                            valid_id = true;
                            update_activity(&arr_milestones[m].activity_list[a]);
                        }
                    }
                }
            }

            //Update milestone after activity is updated
            for(int m = 0; m < num_miles; m++){
                update_milestone(&arr_milestones[m], number_activities[m]);
            }

            //Lastly update the project
            update_project(arr_milestones, num_miles, number_activities, &details);

        }
        else if(response == 2){
            print_project_stats(details, arr_milestones, num_miles, number_activities);
        }
        print_main_menu();
        response = get_input_usi();
    }
    printf("Program quit... ");
    return EXIT_SUCCESS;
}