#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct fields{
    int item_no;
    char item_name[100];
    int cost;
    int quantity;
};
struct bills{
    int date;
    int month;
    int year;
    int hour;
    int minute;
    char customer_name[100];
    int quantity[10];
    char item_name[10][100];
    int  price[10];
    int i;
};
void add_record(){
    struct fields inp;
    FILE *fop;
    int n;
    fop= fopen("restaurant.dat","ab");
    printf("Enter details of items available in the restaurant : \n");
    printf("----------------------------------------------------\n\n");
    char ch;
    do{
        printf("Enter Item no. : ");
        scanf("%d",&inp.item_no);
        fflush(stdin);
        printf("Enter Item name : ");
        scanf("%[^\n]%*c",inp.item_name);
        printf("Enter cost : ");
        scanf("%d", &inp.cost);
        printf("Enter quantity : ");
        scanf("%d",&inp.quantity);
        fwrite(&inp,sizeof(inp),1,fop);
        printf("\n\nDo you want to continue adding items?(y/n) ");
        fflush(stdin);
        scanf("%c", &ch);
    }while(ch!='n');
    fclose(fop);
}
int show_file(){
    struct fields op;
    int a;
    char c;
    FILE *fop;
    fop= fopen("restaurant.dat","rb");
    printf("\n\t\t------------ FOOD MENU ------------");
    printf("\n\t=================================================");
    printf("\n\tITEM NO.\tITEM NAME\tCOST\tQUANTITY");
    printf("\n\t-------------------------------------------------\n");
    while(fread(&op,sizeof(op),1,fop)){
        if(strlen(op.item_name)>7){
            printf("\t%d\t\t%s\t%d\t%d",op.item_no,op.item_name,op.cost,op.quantity);
        }
        else{
            printf("\t%d\t\t%s\t\t%d\t%d",op.item_no,op.item_name,op.cost,op.quantity);
        }
        
        printf("\n");
    }
    printf("\t=================================================\n");
    printf("\n\nHit Enter to continue : ");
    fflush(stdin);
    getchar();
    fclose(fop);
    system("cls");
    return 0;
}

int delete_record(){
    int item_no,count=0;
    char choice;
    struct fields op;
    FILE *fp1, *fp2;
    fp1= fopen("restaurant.dat","rb+");
    printf("\n\n\t\t\tDELETE ITEM\n");
    printf("\t--------------------------------------------\n\n");
    printf("\tEnter the Item no. of item to be deleted : ");
    scanf("%d",&item_no);
    while(fread(&op,sizeof(op),1,fp1)){
        if(op.item_no==item_no){
            printf("\n\n\tItem no.  : %d",op.item_no);
            printf("\n\n\tItem name : %s",op.item_name);
            printf("\n\n\tCost      : %d",op.cost);
            printf("\n\n\tQuantity  : %d",op.quantity);
            count=1;
            break;
        }
    }
    if(count==0){
        printf("\n\n\t\tERROR : Item not found !! \n\n");
        fclose(fp1);
        printf("\n\n\tHit Enter to continue..... ");
        fflush(stdin);
        getchar();
        system("cls");
        return 0;
    }
    fflush(stdin);
    printf("\n\n\tDelete this item?(y/n) :");
    scanf("%c",&choice);
    if(choice=='y' || choice=='Y'){
        rewind(fp1);
        fp2=fopen("temp.dat","wb");
        while(fread(&op,sizeof(op),1,fp1)){
            if(op.item_no!=item_no){
                fwrite(&op,sizeof(op),1,fp2);
            }
        }
        fclose(fp1);
        fclose(fp2);
        remove("restaurant.dat");
        rename("temp.dat","restaurant.dat");
        printf("\n\n\tItem successfully deleted from menu !!");
        printf("\n\n\tHit Enter to continue..... ");
        fflush(stdin);
        getchar();
        system("cls");
        return 0;
    }
    else{
        fclose(fp1);
        printf("\n\n\tHit Enter to continue..... ");
        fflush(stdin);
        getchar();
        system("cls");
        return 0;
    }
}

int update_record(){
    int item_no,count=0;
    char choice;
    struct fields op;
    FILE *fp1, *fp2;
    fp1= fopen("restaurant.dat","rb+");
    printf("\n\n\t\t\tUPDATE RECORD\n");
    printf("\t--------------------------------------------\n\n");
    printf("\tEnter the Item no. of item to be updated : ");
    scanf("%d",&item_no);
    while(fread(&op,sizeof(op),1,fp1)){
        if(op.item_no==item_no){
            printf("\n\n\tItem no.  : %d",op.item_no);
            printf("\n\n\tItem name : %s",op.item_name);
            printf("\n\n\tCost      : %d",op.cost);
            printf("\n\n\tQuantity  : %d",op.quantity);
            count=1;
            break;
        }
    }
    if(count==0){
        printf("\n\n\t\tERROR : Item not found !! \n\n");
        fclose(fp1);
        printf("\n\n\tHit Enter to continue..... ");
        fflush(stdin);
        getchar();
        system("cls");
        return 0;
    }
    fflush(stdin);
    printf("\n\n\tUpdate this record?(y/n) :");
    scanf("%c",&choice);
    if(choice=='y' || choice=='Y'){
        printf("\n\n\t--------------------------------------------");
        rewind(fp1);
        fp2=fopen("temp.dat","wb");
        while(fread(&op,sizeof(op),1,fp1)){
            if(op.item_no!=item_no){
                fwrite(&op,sizeof(op),1,fp2);
            }
            else{
                printf("\n\n\tEnter the details : \n\n");
                printf("\tEnter Item no. : ");
                scanf("%d",&op.item_no);
                fflush(stdin);
                printf("\tEnter Item name : ");
                scanf("%[^\n]%*c",op.item_name);
                printf("\tEnter cost : ");
                scanf("%d", &op.cost);
                printf("\tEnter quantity : ");
                scanf("%d",&op.quantity);
                fwrite(&op,sizeof(op),1,fp2);
            }
        }
        fclose(fp1);
        fclose(fp2);
        remove("restaurant.dat");
        rename("temp.dat","restaurant.dat");
        printf("\n\n\tRecord successfully updated!!");
        printf("\n\n\tHit Enter to continue..... ");
        fflush(stdin);
        getchar();
        system("cls");
        return 0;
    }
    else{
        fclose(fp1);
        printf("\n\n\tHit Enter to continue..... ");
        fflush(stdin);
        getchar();
        system("cls");
        return 0;
    }
}

int search_bill(){
    struct bills save;
    char cname[100];
    FILE *fp1;
    fp1= fopen("bill.dat","rb");
    printf("\n\t\tSEARCH A BILL");
    printf("\n\t-------------------------------------------");
    printf("\n\nEnter the customer name on the bill : ");
    fflush(stdin);
    scanf("%[^\n]%*c",cname);
    int count=0;
    while(fread(&save,sizeof(save),1,fp1)){
        if(strcmp(save.customer_name,cname)==0){
            printf("\n\n");
            //system("cls");
            printf("\n\t*****************************************\n");
            printf("\t\t\t RECIEPT\n");
            printf("\t*****************************************\n");
            printf("\t%d/%02d/%02d\t\t\t %02d:%02d %s\n",save.date, save.month,save.year, (save.hour>12?save.hour-12:save.hour), save.minute, (save.hour>12?"PM":"AM"));
            printf("\n\t\tOrder for:");
            printf("\t%s",save.customer_name);
            printf("\n\n\t==========================================\n");
            printf("\t    Item\t\t\tPrice");
            printf("\n\t------------------------------------------\n\n");
            int i=save.i;
            for(int j=0;j<i;j++){
                if(strlen(save.item_name[j])>9){
                    printf("\t    %d %s\t\t₹%d\n",save.quantity[j],save.item_name[j],save.price[j]);
                }
                else{
                    printf("\t    %d %s\t\t\t₹%d\n",save.quantity[j],save.item_name[j],save.price[j]);
                }
            }
            printf("\n\t------------------------------------------\n");
            int subtot=0;
            for(int j=0;j<i;j++){
                subtot=subtot+save.price[j];
            }
            printf("\t    SUBTOTAL\t\t\t₹%d",subtot);
            float gst=0.05*subtot;
            printf("\n\t    GST@5%%\t\t\t₹%.2f",gst);
            printf("\n\t------------------------------------------\n");
            float total=gst+subtot;
            printf("\t    TOTAL\t\t\t₹%.2f",total);
            printf("\n\t==========================================\n");
            printf("\n\n\n\t  ******* THANK YOU FOR VISITING *******\n\n");
            fclose(fp1);
            count++;
            printf("\n\nHit enter to continue...");
            fflush(stdin);
            getchar();
            system("cls");
            return 0;
        }
    }
    if(count==0){
        printf("\n\nBill with the given name doesn't exist!!");
        fclose(fp1);
        printf("\n\nHit enter to continue...");
        fflush(stdin);
        getchar();
        system("cls");
        return 0;
    }
    return 0;
}

int billing(){
    struct fields op;
    struct bills save;
    int count=0,quant;
    FILE *fp1, *fp2, *fp3;
    fp1= fopen("restaurant.dat","rb+");
    fp2= fopen("temp.dat","wb");
    fp3= fopen("bill.dat","ab+");
    printf("\n\t\t------AVAILABLE TODAY------");
    printf("\n\t-------------------------------------------");
    printf("\n\t\tItems\t\t\tPrice\n");
    printf("\t-------------------------------------------");
    while(fread(&op,sizeof(op),1,fp1)){
        if(strlen(op.item_name)>7){
            printf("\n\t\t%s\t\t₹%d",op.item_name,op.cost);
        }
        else{
            printf("\n\t\t%s\t\t\t₹%d",op.item_name,op.cost);
        }
    }
    printf("\n\t-------------------------------------------");
    char iname[100];
    char cname[100];
    char order[10][100];
    int quantity[10];
    int price[10];
    int tprice;
    int i=0;
    printf("\n\n\tEnter q when you are done with your order!\n");
    while(1){
        printf("\n\tEnter item name : ");
        fflush(stdin);
        scanf("%[^\n]%*c",iname);
        if(strcmp(iname,"q")==0){
            break;
        }
        else{
            count=0;
            quant=0;
            rewind(fp1);
            while(fread(&op,sizeof(op),1,fp1)){
                if(strcmp(iname,op.item_name)==0 && strcmp(iname,"")!=0){
                    count++;
                    quant=op.quantity;
                    tprice=op.cost;
                }
            }
            if(count==0){
                printf("\n\tPlease enter a valid item!!\n");
                continue;
            }
            else if(quant==0){
                printf("\n\tItem not available!!\n");
                continue;
            }
        }
        strcpy(order[i],iname);
        printf("\tEnter quantity : ");
        scanf("%d",&quantity[i]);
        price[i]=tprice*quantity[i];
        i++;
    }
    printf("\n\nYour order : \n");
    for(int j=0;j<i;j++){
        printf("\t%s × %d\n",order[j],quantity[j]);
    }
    printf("\nYour name? ");
    fflush(stdin);
    scanf("%[^\n]%*c",cname);
    printf("\n\nHit enter to generate bill...");
    fflush(stdin);
    getchar();
    system("cls");
    printf("\n\t*****************************************\n");
    printf("\t\t\t RECIEPT\n");
    printf("\t*****************************************\n");
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("\t%d/%02d/%02d\t\t\t %02d:%02d %s\n",tm.tm_mday, tm.tm_mon + 1,tm.tm_year + 1900, (tm.tm_hour>12?tm.tm_hour-12:tm.tm_hour), tm.tm_min, (tm.tm_hour>12?"PM":"AM"));
    printf("\n\t\tOrder for:");
    printf("\t%s",cname);
    printf("\n\n\t==========================================\n");
    printf("\t    Item\t\t\tPrice");
    printf("\n\t------------------------------------------\n\n");
    for(int j=0;j<i;j++){
        if(strlen(order[j])>9){
            printf("\t    %d %s\t\t₹%d\n",quantity[j],order[j],price[j]);
        }
        else{
            printf("\t    %d %s\t\t\t₹%d\n",quantity[j],order[j],price[j]);
        }
    }
    printf("\n\t------------------------------------------\n");
    int subtot=0;
    for(int j=0;j<i;j++){
        subtot=subtot+price[j];
    }
    printf("\t    SUBTOTAL\t\t\t₹%d",subtot);
    float gst=0.05*subtot;
    printf("\n\t    GST@5%%\t\t\t₹%.2f",gst);
    printf("\n\t------------------------------------------\n");
    float total=gst+subtot;
    printf("\t    TOTAL\t\t\t₹%.2f",total);
    printf("\n\t==========================================\n");
    rewind(fp1);
    printf("\n\n\n\t  ******* THANK YOU FOR VISITING *******\n\n");
    while(fread(&op,sizeof(op),1,fp1)){
        for(int j=0;j<i;j++){
            if(strcmp(op.item_name,order[j])==0){
                op.quantity=op.quantity-quantity[j];
                break;
            }
        }
        fwrite(&op,sizeof(op),1,fp2);
    }
    fclose(fp1);
    fclose(fp2);
    remove("restaurant.dat");
    rename("temp.dat","restaurant.dat");
    printf("\n\nEnter s to save the bill else Hit enter to exit...");
    fflush(stdin);
    if(getchar()=='s'){
        save.date=tm.tm_mday;
        save.month=tm.tm_mon + 1;
        save.year=tm.tm_year + 1900;
        save.hour=tm.tm_hour;
        save.minute=tm.tm_min;
        save.i=i;
        strcpy(save.customer_name,cname);
        for(int j=0;j<=i;j++){
            strcpy(save.item_name[j],order[j]);
            save.quantity[j]=quantity[j];
            save.price[j]=price[j];
        }
        fwrite(&save,sizeof(save),1,fp3);
        fclose(fp3);
        printf("Successfully saved!!");
    }
    else{
        return 0;
    }
    return 0;
}
int main(){
    int ch;
    system("cls");
    while(1){
        printf("\n\n");
        printf("\t*********************************************\n\n");
        printf("\t\tWeclome to Restaurant Database!!\n\n");
        printf("\t*********************************************\n\n");
        printf("\t\t----------- MENU -----------\n\n");
        printf("\t\t(1)Add record\n");
        printf("\t\t(2)Show restaurant menu\n");
        printf("\t\t(3)Delete item from the database\n");
        printf("\t\t(4)Update a record\n");
        printf("\t\t(5)To search a bill\n");
        printf("\t\t(6)Billing\n");
        printf("\t\t(7)Exit\n");
        printf("\n");
        printf("\t\tEnter your choice : ");
        scanf("%d",&ch);
        switch(ch){
            case 1:
                system("cls");
                add_record();
                break;
            case 2:
                system("cls");
                show_file();
                break;
            case 3:
                system("cls");
                delete_record();
                break;
            case 4:
                system("cls");
                update_record();
                break;
            case 5:
                system("cls");
                search_bill();
                break;
            case 6:
                system("cls");
                billing();
                break;
            case 7:
                exit(1);
            default:
                printf("Invalid input\n\n");
        }
    }
    return 0;
}