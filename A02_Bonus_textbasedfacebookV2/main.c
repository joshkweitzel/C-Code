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
    //Enter the program at the login screen
    int choice;
    while(choice != 3){
        print_menu();
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch(choice){
            case 1:{
                //Register a user while checking for duplicates
                printf("Registering a new user... \nenter username: ");
                bool userexists = true;
                while(userexists == true){
                    char *newusername = getstring(30);
                    if(find_user(users, newusername) == NULL){
                        printf("Enter password: ");
                        char *password = getstring(15);
                        add_user(users, newusername, password);
                        userexists = false;
                    } else {
                        printf("Username taken, enter a new username: ");
                    }
                }
                break;
            }

            case 2:{
                //Log in to application with a username and password
                printf("Logging in... \nenter username: ");
                char *username = getstring(30);
                if(find_user(users, username) == NULL){
                    printf("Username not found, registering new user... \nEnter password: ");
                    char *password = getstring(15);
                    add_user(users, username, password);
                } else {
                    printf("Enter password: ");
                    char *password = getstring(15);
                    if(strcmp(find_user(users, username)->password, password) != 0){
                        printf("Incorrect password\n");
                        break;
                    }
                }
                //Assign pointer to logged in user
                user_t *userlogin = find_user(users, username);

                //Username and password entered, proceeding to application
                int loggedchoice = 0;
                while(loggedchoice != 5){
                    print_usermenu(userlogin);
                    printf("Enter choice: ");
                    scanf("%d", &loggedchoice);
                    switch(loggedchoice){
                        case 1:{
                            //Change password
                            printf("Managing profile, enter password: ");
                            char *password = getstring(15);
                            //If password does not match return to user menu
                            if(strcmp(password, userlogin->password) != 0){
                                printf("Incorrect password\n");
                                break;
                            }
                            //Password matches, user updates the password
                            printf("Enter updated password: ");
                            strcpy(userlogin->password, getstring(15));
                            break;
                        }

                        case 2:{
                            //Manage user's posts
                            int postchoice = 0;
                            while(postchoice != 3){
                                //Display the user's post
                                if(userlogin->posts == NULL){
                                    printf("%s has no posts yet\n--------------------------\n", userlogin->username);
                                } else {
                                    printf("%s's posts: \n-------------------------\n", userlogin->username);
                                    display_all_user_posts(userlogin);
                                    printf("-------------------------\n");
                                }

                                //Enter new switch case for choosing post option
                                printf("1. Add new post\n2. Remove a post\n3. Return to menu\nEnter choice: ");
                                scanf("%d", &postchoice);
                                switch(postchoice){
                                    case 1:
                                        printf("Enter the content of the post: ");
                                        char content[250];
                                        scanf(" %[^\n]s", &content);
                                        add_post(userlogin, content);
                                        break;
                                    case 2:
                                        if(userlogin->posts == NULL){
                                            printf("No posts to delete\n------------------------- \n");
                                            break;
                                        }
                                        delete_post(userlogin);
                                        break;
                                    case 3:
                                    //Exit
                                        break;
                                    }
                            }
                            break;
                        }
                        case 3:{
                            //Manage user's friends
                            int friendchoice = 0;
                            while(friendchoice != 3){
                                printf("-------------------------- \nManaging friends... \n1. Add friend\n2. Remove friend\n3. Return to menu\nEnter choice: ");
                                scanf("%d", &friendchoice);
                                switch(friendchoice){
                                    case 1:{
                                        //Add a friend that is a registered user
                                        printf("--------------------------\nEnter username of friend to add: ");
                                        char *friendname = getstring(30);
                                        if(find_user(users, friendname) != NULL){
                                            add_friend(userlogin, friendname);
                                            printf("Friend added to list!\n");
                                        } else {
                                            printf("User not found\n");
                                        }
                                        break;
                                    }
                                    case 2:{
                                        //Remove a friend
                                        printf("-------------------------- \n%s's friends list: \n", userlogin->username);
                                        display_user_friends(userlogin);
                                        if(userlogin->friends == NULL){
                                            printf("No friends\n");
                                            break;
                                        }
                                        printf("-------------------------- \nEnter name of friend to delete: ");
                                        char *friendname = getstring(30);
                                        bool result = delete_friend(userlogin, friendname);
                                        if(result == true){
                                            printf("%s removed from friends list\n", friendname);
                                            printf("%s's updated friends list: \n", userlogin->username);
                                            display_user_friends(userlogin);
                                        } else {
                                            printf("%s not found on friends list\n", friendname);
                                        }
                                        break;
                                    }
                                    case 3:{
                                        //Exit
                                        break;
                                    }
                                }
                            }
                            break;
                        }

                        case 4:{
                            //Display posts by a user's friend
                            printf("-------------------------- \n%s's friends list: \n", userlogin->username);
                            display_user_friends(userlogin);
                            printf("-------------------------- \nEnter friend's username to display posts: ");
                            char *friendname = getstring(30);
                            friend_t *currfriend = userlogin->friends;
                            while(currfriend != NULL){
                                if(strcmp(currfriend->username, friendname) == 0){
                                    currfriend->posts = &(find_user(users, friendname)->posts);
                                    display_posts_by_n(currfriend->posts);
                                    break;
                                }
                                currfriend = currfriend->next;
                            }
                            if(currfriend == NULL){
                                printf("User not on friends list\n");
                            }

                            break;
                        }

                        case 5:{
                            //Exit
                            break;
                        }
                    }
                }
                break;
            }

            case 3:{
                //Exit
                break;
            }
        }

    }

    teardown(users);
    return 1;
}