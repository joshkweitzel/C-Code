/********* main.c ********
    Student Name 	= Joshua Weitzel
    Student Number	= 101301965
*/

// Includes go here
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "a2_functions.h"

int main()
{
    FILE *csv_file = fopen("user_details.csv", "r");
    if (csv_file == NULL)
    {
        perror("Error opening the CSV file");
        return 1;
    }
    // Parse CSV data and create users
    user_t *users = read_CSV_and_create_users(csv_file, 50);

    fclose(csv_file);
    
    //Call functions
    int choice = 0;
    int doublebreak; //Used to break out of the while loop back to the main menu while inside a case
    while(choice != 6){
        print_menu();
        scanf("%d", &choice);
        switch (choice){
            case 1: {
                //Register a new user
                printf("Registering new user... \nEnter username: ");
                char *username = getstring(30);
                printf("Enter password: ");
                char *password = getstring(15);
                users = add_user(users, username, password); 
                break;
            }
            case 2: {
                //Manage profile
                printf("Managing user profile... \nEnter username: ");
                user_t *founduser = find_user(users, getstring(30));
                if(founduser == NULL){
                    printf("--------------\nUSER NOT FOUND\n---------------\n");
                    break;
                }
                printf("Enter the user's password: ");
                char *password = getstring(15);
                //If password does not match enter while loop
                while(strcmp(password, founduser->password) != 0){
                    //User can choose to re-enter the the password or exit back to main menu
                    printf("Incorrect password, do you wish to re-enter? (y/n): \n");
                    bool con = yesno();
                    //If user chooses to exit to menu double break is used to break while loop and switch case
                    if(con == false){
                        doublebreak = 1;
                        break;
                    }
                    //If user continues, prompted to re-enter password
                    printf("Enter the user's password: ");
                    password = getstring(15);
                }
                if(doublebreak == 1){
                    break;
                }
                //Password matches, user updates the password
                printf("Enter updated password: ");
                strcpy(founduser->password, getstring(15));
                break;
            }
            case 3: {
                //Manage posts
                //Find user to manage their posts
                printf("Managing user posts... \nEnter username: ");
                user_t *founduser = find_user(users, getstring(30));
                if(founduser == NULL){
                    printf("--------------\nUSER NOT FOUND\n---------------\n");
                    break;
                } else {
                    printf("Managing %s's posts\n---------------------\n", founduser->username);
                }
                
                int postchoice = 0;
                while(postchoice != 3){
                    //Display the user's post
                    if(founduser->posts == NULL){
                        printf("%s has no posts yet\n---------------------\n", founduser->username);
                    } else {
                        printf("%s's posts: \n---------------------\n", founduser->username);
                        display_all_user_posts(founduser);
                        printf("---------------------\n");
                    }

                    //Enter new switch case for choosing post option
                    printf("1. Add new post\n2. Remove a post\n3. Return to menu\nEnter choice: ");
                    scanf("%d", &postchoice);
                    switch(postchoice){
                        case 1:
                            printf("Enter the content of the post: ");
                            char content[250];
                            scanf(" %[^\n]s", &content);
                            add_post(founduser, content);
                            break;
                        case 2:
                            delete_post(founduser);
                            break;
                        case 3:
                            break;
                        default:
                            printf("Invalid choice\n");
                            break;
                    }
                }
                break;
            }
            case 4: {
                //Manage friends
                //Find user to manage their friends
                printf("Managing user friends... \nEnter username: ");
                user_t *founduser = find_user(users, getstring(30));
                if(founduser == NULL){
                    printf("--------------\nUSER NOT FOUND\n---------------\n");
                    break;
                }else {
                    printf("Managing %s's friends\n-----------------------------------\n", founduser->username);
                }

                //When user is found, friend menu is displayed
                int friendchoice = 0;
                while(friendchoice != 3){
                    printf("1. Add friend\n2. Remove friend\n3. Return to menu\nEnter choice: ");
                    scanf("%d", &friendchoice);
                    switch(friendchoice){
                        case 1:{
                            printf("Enter name of friend to add: ");
                            char *friendname = getstring(30);
                            add_friend(founduser, friendname);
                            printf("Friend added to list!\n");
                            break;
                        }
                        case 2:{
                            printf("%s's friends list: \n", founduser->username);
                            display_user_friends(founduser);
                            if(founduser->friends == NULL){
                                printf("No friends to delete\n");
                                break;
                            }
                            printf("Enter name of friend to delete: ");
                            char *friendname = getstring(30);
                            bool result = delete_friend(founduser, friendname);
                            if(result == true){
                                printf("%s removed from friends list\n", friendname);
                                printf("%s's updated friends list: \n", founduser->username);
                                display_user_friends(founduser);
                            } else {
                                printf("%s not found on friends list\n", friendname);
                            }
                            break;
                        }
                        case 3:{
                            break;
                        }
                        default:{
                            printf("Invalid choice\n");
                        }
                    }
                }
            }
            case 5: {
                //Display posts by a user. Can enter # of posts to display then after if con, display 3 at a time.
                printf("Enter username to display posts: ");
                user_t *founduser = find_user(users, getstring(30));
                if(founduser == NULL){
                    printf("User not found\n");
                    break;
                }
                printf("How many posts would you like to display: ");
                int numposts;
                scanf("%d", &numposts);
                printf("Displaying posts by %s...\n----------------------------------\n", founduser->username);
                display_posts_by_n(founduser, numposts);
                break;
            }
            case 6: {
                break;
            }
            default: {
                printf("Invalid choice\n");
            }
        } 
    }
    teardown(users);
    return 1;
}