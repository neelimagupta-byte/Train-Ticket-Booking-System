#include<stdio.h>
#include<string.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct {
int train_no;
char train_name[50];
char source[30];
char destination[30];
char arrival[10];
char departure[10];
float price;
int total_seats;
int available_seats;
} train;

typedef struct {
int pnr;
int train_no;
int seats;
float total_price;
char name[50];
int age;
char gender;
char train_name[50];
}ticket;

void add_train();
void update_train();
void display_train();
void delete_train();
void search_and_book();
void display_ticket();
void cancel_ticket ();
int valid_time( char*);
int minutes(char*);
void toLowerCase(char *str);


int main(){
    int choice;
    do{
        printf("\n**************************************************************************************\n");
        printf("                       TICKET BOOKING SYSTEM \n");
        printf("**************************************************************************************\n");
        printf("\nchoice:\n");
        printf("1.ADD TRAIN DETAILS\n");
        printf("2.UPDATE TRAIN DETAILS\n");
        printf("3.DISPLAY ALL TRAINS\n");
        printf("4.DELETE TRAIN DETAIL\n");
        printf("5.SEARCH AND BOOK TICKET\n");
        printf("6.CHECK TICKET DETAILS\n");
        printf("7.CANCEL TICKET \n");
        printf("8.EXIT\n");
        printf("enter choice:\n");
        scanf("%d",&choice);

        switch(choice){
            case 1: add_train();
                    break;
            case 2: update_train();
                    break;
            case 3: display_train();
                    break;       
            case 4: delete_train();
                    break;
            case 5: search_and_book();
                    break;
            case 6: display_ticket();
                    break;
            case 7: cancel_ticket ();
                    break;
            
        }
    } while(choice!=8);
return 0;}
void add_train(){
    FILE*ptr=fopen("train.dat","ab");
        if(!ptr){
        printf("error opening file!\n");
        return ;
    }
    train t;
    printf("\nenter train number: ");
    scanf("%d",&t.train_no);
    printf("enter Train name : ");
    scanf(" %[^\n]",t.train_name);
    printf("enter total seats : ");
    scanf("%d",&t.total_seats);
    printf("enter source : ");
    scanf(" %[^\n]",t.source);
    printf("enter destination : ");
    scanf(" %[^\n]",t.destination);
    printf("enter train ticket fair: ");
    scanf("%f",&t.price);
    do{printf("enter train (HH:MM) : ");
        scanf(" %s",t.arrival);
        if (!valid_time(t.arrival))
        printf("INVALID TIME FORMAT! enter again\n");
    }while(!valid_time(t.arrival));
    do{
        printf("enter departure (HH:MM) : ");
        scanf(" %s",t.departure);
        if(!valid_time(t.departure))
        printf("INVALID TIME FORMAT! enter again\n");
        if(minutes(t.arrival)>=minutes(t.departure))
        printf("Departure must be after arrival! Please enter again.\n");
    }
    while(!valid_time(t.departure) || minutes(t.arrival)>=minutes(t.departure));
    t.available_seats=t.total_seats;
    fwrite(&t,sizeof(train),1,ptr);
    fclose(ptr);
    printf("train added successfully.\n");
}

void update_train(){
    int tno,total;
    FILE*ptr=fopen("train.dat","rb+");
        if(!ptr){
        printf("error opening file!\n");
        return ;
    }
    train t;
    printf("enter train number: ");
    scanf("%d",&tno);
    
    while(fread(&t,sizeof(train),1,ptr)){
    if(tno==t.train_no){
    printf("enter new  train number : ");
    scanf("%d",&t.train_no);
    printf("enter new Train name : ");
    scanf(" %[^\n]",t.train_name);
    total=t.total_seats;
    printf("enter new  total seats : ");
    scanf("%d",&t.total_seats);
    printf("enter new source : ");
    scanf(" %[^\n]",t.source);
    printf("enter new destination : ");
    scanf(" %[^\n]",t.destination);
    printf("enter new  train ticket fair: ");
    scanf("%f",&t.price);
    
    do{printf("enter new train (HH:MM) : ");
        scanf(" %s",t.arrival);
        if (!valid_time(t.arrival))
        printf("INVALID TIME FORMAT! enter again\n");
    }while(!valid_time(t.arrival));
    
    do{
        printf("enter new departure (HH:MM) : ");
        scanf(" %s",t.departure);
        if(!valid_time(t.departure))
        printf("INVALID TIME FORMAT! enter again\n");
        if(minutes(t.arrival)>=minutes(t.departure))
        printf("Departure must be after arrival! Please enter again.\n");
    }
    while(!valid_time(t.departure) || minutes(t.arrival)>=minutes(t.departure));
    
    int booked = total - t.available_seats;
    t.available_seats = t.total_seats - booked;
    if (t.available_seats < 0) {
    t.available_seats = 0;
    }
    fseek(ptr,-sizeof(train),SEEK_CUR);
    fwrite(&t,sizeof(train),1,ptr);
    fclose(ptr);
    printf("train details updated successfully\n");
    return;
}}
    printf("train no. not found!\n");
    fclose(ptr);
}   

void display_train(){
FILE*ptr=fopen("train.dat","rb");
        if(!ptr){
        printf("error opening file!\n");
        return ;
    }
    int f=0;
    train t;
    printf("\n              ------------------ ALL TRAINS -----------------------\n");
    while(fread(&t,sizeof(train),1,ptr)){
        f=1;
        printf("Train No. : %d\n",t.train_no);
        printf("Train Name : %s\n",t.train_name);
        printf("Train arrival : %s\n",t.arrival);
        printf("Train departure : %s\n",t.departure);
        printf("Train price : %.2f\n",t.price);
        printf("Train available seats : %d\n\n",t.available_seats);
        }
if(f==0){
    printf("no data!");
}
fclose(ptr);

}



void delete_train(){
    int tno,f=0;;
FILE*ptr=fopen("train.dat","rb");
        if(!ptr){
        printf("error opening file!\n");
        return ;
    }
FILE*p=fopen("temp.dat","wb");
        if(!p){
        printf("error opening file!\n");
        return ;
    }
train t;
printf("enter train no. to delete : ");
scanf("%d",&tno);

while(fread(&t,sizeof(train),1,ptr)){
    if(tno!=t.train_no){
    fwrite(&t,sizeof(train),1,p);}
    else{
        f=1;
    }}
    fclose(ptr);
    fclose(p);
    if(f){ 
    remove("train.dat");
    rename("temp.dat","train.dat");
    printf("Deleted successfully\n");
    }
    else{
      remove("temp.dat");
      printf("No train number found!\n");}
    }

void search_and_book(){
    char source[50], destination[50];
    int f=0,choice;
FILE*ptr=fopen("train.dat","rb");
 if(!ptr){
        printf("error opening file!\n");
        return ;
    }


    printf("\nEnter source : ");
    fgets(source, sizeof(source), stdin);
    source[strcspn(source, "\n")] = '\0';
    printf("enter destination : ");
    fgets(source, sizeof(source), stdin);
    source[strcspn(source, "\n")] = '\0';
    toLowerCase(source);
    toLowerCase(destination);
    printf("------- AVAILABLE TRAINS FROM %s to %s --------\n",source,destination);
train t;
    while(fread(&t,sizeof(train),1,ptr)){
    toLowerCase(t.source);
    toLowerCase(t.destination);
    if(strstr(t.source,source)!=NULL && strstr(t.destination,destination)!=NULL){
        f=1;
        printf("Train No. : %d\n",t.train_no);
        printf("Train Name : %s\n",t.train_name);
        printf("Train arrival : %s\n",t.arrival);
        printf("Train departure : %s\n",t.departure);
        printf("Train price : %.2f\n",t.price);
        printf("Train available seats : %d\n",t.available_seats);
    }
}
fclose(ptr);
if (!f) {
        printf("No trains available for this route.\n");
        return;
    } else {
    do{
        printf("\nDO you want to book tickets ?\n1.YES \n2.NO\n");
        printf("enter your choice:\n");
        scanf("%d",&choice);
        switch(choice){
            case 1:{ 
                ticket tk;
                train t;
                int tno,match = 0;
                ptr= fopen("train.dat", "rb+");
                printf("\nEnter Train No to book: ");
                scanf("%d", &tno);
                while(fread(&t, sizeof(train), 1,ptr)) {
                            if (t.train_no==tno) {
                                match = 1;
                    printf("Enter Seats to book: ");
                    scanf("%d", &tk.seats);
                    
                    if (tk.seats > t.available_seats) {
                        printf("Not enough seats available! Only %d left.\n", t.available_seats);
                        fclose(ptr);
                        return;}
            printf("Enter Passenger Name: ");
            scanf(" %s",tk.name);
            printf("Enter Age: "); scanf("%d",&tk.age);
            printf("Enter Gender(F/M): "); scanf(" %c",&tk.gender);
            tk.train_no = tno;
            strcpy(tk.train_name,t.train_name);
            tk.total_price = t.price * tk.seats;
            srand(time(0));
            tk.pnr = rand() % 1000000 + 100000;
            printf("PNR: %d\n",tk.pnr);
            t.available_seats -= tk.seats;
            fseek(ptr, -sizeof(train), SEEK_CUR);
            fwrite(&t, sizeof(train), 1,ptr);
            fclose(ptr);

            FILE *ft = fopen("tickets.dat", "ab");
            fwrite(&tk, sizeof(ticket), 1, ft);
            fclose(ft);

            printf("\nTicket booked successfully!\n");
            return;
                }
            }
            fclose(ptr);
            if (!match) {
                printf("Invalid Train No!\n");
            }
            break;}
    case 2: printf("\nback to main menu\n");
            break;
    default : printf("INVALID CHOICE\n");
    }} while(choice!=2);
}
return;
}
void display_ticket(){
    int tno;
FILE*ptr=fopen("tickets.dat","rb");
if(!ptr){
    printf("error opening file!");
    return;
}
ticket tk;
printf("enter train no. or pnr : ");
scanf("%d",&tno);
while(fread(&tk,sizeof(ticket),1,ptr)){
    if(tk.train_no==tno || tk.pnr==tno){
       
            printf("PNR: %d\n",tk.pnr);
            printf("Name: %s\n",tk.name);
            printf("Age : %d\n",tk.age);
            printf("Gender: %c",tk.gender);
            printf("Train: %s\n",tk.train_name);
            printf("Seats: %d\n",tk.seats);
            printf("Total Price: %.2f\n",tk.total_price); 
            fclose(ptr);
            return;
    }
}
printf("Ticket not found !\n");
fclose(ptr);
}
void cancel_ticket(){
display_ticket();
int pnr, found = 0;
    ticket tk;

    FILE *ft = fopen("tickets.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");
    if (!ft) {
        printf("No tickets found!\n");
        return;
    }

    printf("Enter Ticket pnr to cancel: ");
    scanf("%d", &pnr);

    while (fread(&tk, sizeof(ticket), 1, ft)) {
        if (tk.pnr != pnr) {
            fwrite(&tk, sizeof(ticket), 1, temp);
        } else {
            found = 1;
           train t;
           FILE*ptr=fopen("train.dat","rb+");
           if(ptr){
            while(fread(&t,sizeof(train),1,ptr)){
                if(t.train_no==tk.train_no){
                    t.available_seats+=tk.seats;
                    fseek(ptr,-sizeof(train),SEEK_CUR);
                    fwrite(&t,sizeof(train),1,ptr);
                    break;
                }
            }
            fclose(ptr);
           }
        }
    }
    fclose(ft);
    fclose(temp);
    remove("tickets.dat");
    rename("temp.dat","tickets.dat");
    if (found) {

        printf("Ticket cancelled successfully!\n");
    } else {
        printf("Ticket not found!\n");
    }
}

int valid_time( char *time){
    if (strlen(time)!= 5 || time[2] != ':') return 0;

    int hh = (time[0]-'0')*10 + (time[1]-'0');
    int mm = (time[3]-'0')*10 + (time[4]-'0');

    if (hh < 0 || hh > 23) return 0;
    if (mm < 0 || mm > 59) return 0;

    return 1;
}
int minutes(char *time){
    int hh = (time[0]-'0')*10 + (time[1]-'0');
    int mm = (time[3]-'0')*10 + (time[4]-'0');
    return hh*60 + mm;
}
void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}