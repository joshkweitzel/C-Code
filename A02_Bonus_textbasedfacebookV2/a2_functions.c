/*****************
    Student Name 	= Joshua Weitzel
    Student Number	= 101301965
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include <ctype.h>
#include "a2_functions.h"

// Your solution goes here
user_t *add_user(user_t *users, const char *username, const char *password){
    //Create new user with given username and password
    user_t *newuser = malloc(sizeof(user_t));
    assert(newuser != NULL);
    newuser->next = NULL;
    newuser->friends = NULL;
    newuser->posts = NULL;
    strcpy(newuser->username, username);
    strcpy(newuser->password, password);

    user_t *curr = users;

    //If the list is empty or the newuser is replacing the head, the newuser is the head
    if(users == NULL || strcmp(users->username, newuser->username) > 0){
        newuser->next = users;
        return newuser;
    }
    while(curr->next != NULL){
        //Find the proper place for the new user in the list based on the username
        if(strcmp(curr->next->username, newuser->username) > 0) {
            newuser->next = curr->next;
            curr->next = newuser;
            return users;
        }
        curr = curr->next;
    }
    //If the while loop runs to the end of the list, new user is added to the end
    curr->next = newuser;
    return users;
}

user_t *find_user(user_t *users, const char *username){
    user_t *curr = users;
    while(curr != NULL){
        if(strcmp(curr->username, username) == 0){
            return curr;
        }
        curr = curr->next; 
    }
    return NULL;
}

friend_t *create_friend(const char *username){
    friend_t *newfriend = malloc(sizeof(friend_t));
    assert(newfriend != NULL);
    strcpy(newfriend->username, username);
    newfriend->next = NULL;
    return newfriend;
}

void add_friend(user_t *user, const char *friend){
    //Create new friend
    friend_t *friendadd = create_friend(friend);
    //Set curr to the head 
    friend_t *curr = user->friends;

    //If the list is empty or if user is replacing the head, added friend is the head
    if(user->friends == NULL || strcmp(user->friends->username, friendadd->username) > 0){
        friendadd->next = user->friends;
        user->friends = friendadd;
        return;
    }
    while(curr->next != NULL){
        if(strcmp(curr->next->username, friendadd->username) > 0){
            friendadd->next = curr->next;
            curr->next = friendadd;
            return;
        }
        curr = curr->next;
    }
    //If the while loop runs to the end of the list, new friend is added to the end
    curr->next = friendadd;
    return;
}

_Bool delete_friend(user_t *user, char *friend_name){
    //If head node is deleted
    if(strcmp(user->friends->username, friend_name) == 0){
        user->friends = user->friends->next;
        return true;
    }
    if(user->friends->next == NULL){
        return false;
    }
    //If node is within list
    
    friend_t *curr = user->friends->next;
    friend_t *prev = user->friends;
    prev->next = curr;
    while(curr->next != NULL){
        if(strcmp(curr->username, friend_name) == 0){
            curr = curr->next;
            prev->next = curr;
            return true;
        } else {
            curr = curr->next;
            prev = prev->next;
        }
    } 
    //If end of list is reached
    if(strcmp(curr->username, friend_name) == 0){
        prev->next = NULL;
        return true;
    }
    //Friend not found in list
    return false;

}

post_t *create_post(const char *text){
    post_t *newpost = malloc(sizeof(post_t));
    assert(newpost != NULL);
    newpost->next = NULL;
    strcpy(newpost->content, text);
    return newpost;
}

void add_post(user_t *user, const char *text){
    post_t *postadd = create_post(text);

    if(user->posts == NULL){
        user->posts = postadd;
    } else {
        postadd->next = user->posts;
        user->posts = postadd;
    } 
}

_Bool delete_post(user_t *user){
    post_t *removedpost = user->posts;
    user->posts = user->posts->next;
    if(removedpost == user->posts){
        return false;
    } else {
        return true;
    }
}

void display_all_user_posts(user_t *user){
    post_t *currpost = user->posts;
    for(int i = 1; currpost != NULL; i++, currpost = currpost->next){
        printf("%d - %s\n", i, currpost->content);
    }
}

void display_user_friends(user_t *user){
    friend_t *currfriend = user->friends;
    for(int i = 1; currfriend != NULL; i++, currfriend = currfriend->next){
        printf("%d - %s\n", i, currfriend->username);
    }
}

void display_posts_by_n(post_t **posts){
    post_t *currpost = *posts;
    bool con = true;
    int postsdis = 1;
    while(con == true){
        printf("-------------------------- \n");
        for(int i = 0; i < 3 && currpost != NULL; currpost = currpost->next, i++, postsdis++){
            printf("%d - %s\n", postsdis, currpost->content);
        }
        printf("-------------------------- \n");
        if(currpost == NULL){
            printf("All posts displayed\n");
            con = false;
            return;
        }
        printf("Would you like to display more posts? (y/n): ");
        con = yesno();
    }
}

void teardown(user_t *users){
    //Traverse through every user and their associated friends and posts. Free the all allocated memory.
    while(users != NULL){
        user_t *next = users->next;

        //Free memory of each friend
        friend_t *friend = users->friends;
        while(friend != NULL){
            friend_t *next = friend->next;
            free(friend);
            friend = next;
        }

        //Free memory of each post
        post_t *post = users->posts;
        while(post != NULL){
            post_t *next = post->next;
            free(post);
            post = next;
        }

        //Free memory for the user
        free(users);
        users = next;
    }
    printf("Teardown successful, exiting program");
}

void print_usermenu(user_t *user){
    printf("****************************************************************\n");
    printf("                          Welcome %s                            \n", user->username);
    printf("****************************************************************\n");
    printf("1. Manage profile (change password)\n2. Manage posts (add/remove)\n3. Manage friends (add/remove)\n4. Display friend's posts\n5. Logout\n");
}

void print_menu(){
    printf("****************************************************************\n");
    printf("                           MAIN MENU                            \n");
    printf("****************************************************************\n");
    printf("1. Register new user\n2. Login with existing user\n3. Exit\n");
}

char * lower_case(char *string){
    for(int i = 0; string[i]; i++){
        string[i] = tolower(string[i]);
    }
    return string;
}

char * getstring(int select){
    if(select == 30){
        //Enter a username
        static char username[30];
        scanf("%30s", &username);
        return lower_case(username);
    } else if(select == 15){
        //Enter a password
        static char password[15];
        scanf("%15s", &password);
        while(strlen(password) < 8){
            printf("Password must be between 8 and 15 characters long, re-enter password: ");
            scanf("%15s", &password);
        }
        return password;
    } else{
        return NULL;
    }
}

_Bool yesno(){
    char response;
    scanf(" %c", &response);
    if(response == 'y' || response == 'Y'){
        //yes
        return true;
    } else if(response == 'n' || response == 'N'){
        //no
        return false;
    } else {
        //Neither, call recursion case
        printf("Invalid input, enter (y/n): ");
        return yesno();
    }
}


/*
   ******** DONT MODIFY THIS FUNCTION ********
   Function that reads users from the text file.
   IMPORTANT: This function shouldn't be modified and used as is
   ******** DONT MODIFY THIS FUNCTION ********
*/
user_t *read_CSV_and_create_users(FILE *file, int num_users)
{
    srand(time(NULL));
    user_t *users = NULL;
    char buffer[500];
    fgets(buffer, sizeof(buffer), file); // Read and discard the header line
    int count = 0;
    for (int i = 0; i < num_users; i++)
    {
        fgets(buffer, sizeof(buffer), file);
        buffer[strcspn(buffer, "\r\n")] = 0; // Remove newline characters

        char *token = strtok(buffer, ",");
        char *token2 = strtok(NULL, ",");
        users = add_user(users, token, token2);
        char *username = token;

        token = strtok(NULL, ",");

        user_t *current_user = users;
        for (; current_user != NULL && strcmp(current_user->username, username) != 0; current_user = current_user->next)
            ;

        while (token != NULL && strcmp(token, ",") != 0 && count < 3)
        {
            if (strcmp(token, " ") != 0)
            {
                add_friend(current_user, token);
            }
            token = strtok(NULL, ",");
            count++;
        }
        count = 0;

        // token = strtok(NULL, ",");
        while (token != NULL && strcmp(token, ",") != 0)
        {
            add_post(current_user, token);
            token = strtok(NULL, ",");
        }
    }
    return users;
}
