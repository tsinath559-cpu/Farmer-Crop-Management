#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct  details
{
    char cropname[100];
    float area;
    float expenditure;
    char croptime[100];
};
void addcrop();
void displaycrop();
void update();
void delete();
void generate();
void quit();
void cropsuggetions();
int main(){
    printf("\n");
    printf("\t\t\t\t\tYou can choose any of theese elements::\n");
    printf("\n\n");
    printf("\t1.add the crop record\t\t2.to display all crops details\n\t3.update the crop details\t4.delete the crop details\n\t5.generation of the report\t6.cropsugesstions\n\t7.exit\n");
    int choice;
    printf("Enter the choice::");
    scanf("%d",&choice);
    if(choice==1){
        addcrop();
    }
    else if(choice==2){
         displaycrop();
     }
     else if(choice==3){
             update();
     }
    else if(choice==4){
         delete();
     }
    else if(choice==5){
         generate();
     }
    else if(choice==6){
        cropsuggetions();
     }
    else if(choice==7){
        quit();
     }   
    else{
        printf("invalid input");
    }
}

void addcrop() {
    int countofcrops;
    printf("\nhow many crops do you want to enter::");
    scanf("%d",&countofcrops);
    printf("\n");

    for(int i=0;i< countofcrops;i++){
    struct details d1;
    FILE *p=fopen("text1.txt", "a");
    if (p==NULL) {
        printf("Error in opening file!\n");
        return;
    }
    printf("Enter the crop name:");
    scanf("%s",d1.cropname);
    printf("Enter the field area (in acres/hectares): ");
    scanf("%f",&d1.area);
    printf("Enter annual expenditure: ");
    scanf("%f",&d1.expenditure);
    printf("Enter time required for crop (e.g., 6months): ");
    scanf("%s",d1.croptime);
    fprintf(p, "%s %f %f %s\n", d1.cropname, d1.area, d1.expenditure, d1.croptime);
    fclose(p);
}
    printf("Crop details saved successfully!\n");
}

void displaycrop(){
                FILE *p=fopen("text1.txt","r");
                if(p==NULL){
                    printf("error in opening");
                    return;
                }
                struct details d1;
                while (fscanf(p, "%s %f %f %s", d1.cropname, &d1.area, &d1.expenditure, d1.croptime)!=EOF) {
                printf("%s %f %f %s\n", d1.cropname, d1.area, d1.expenditure, d1.croptime);
                }
                fclose(p);    
    }
void update(){
    FILE *fp,*temp;
    struct details d1;
    char crop[100];
    int found = 0;
    fp=fopen("text1.txt","r");
    temp=fopen("temp.txt","w");
    if (fp==NULL||temp==NULL) {
        printf("Error in opening file!\n");
        return;
    }
    printf("Enter the crop name to update:");
    scanf("%s",crop);
    while(fscanf(fp,"%s %f %f %s", d1.cropname, &d1.area, &d1.expenditure, d1.croptime) != EOF) {
        if(strcmp(d1.cropname,crop)==0) {
            found=1;
            printf("\nCurrent details of %s:\n", d1.cropname);
            printf("Area: %.2f | Expenditure: %.2f | Time: %s\n", d1.area, d1.expenditure, d1.croptime);
            printf("\nEnter new details:\n");
            printf("Enter new area: ");
            scanf("%f", &d1.area);
            printf("Enter new expenditure: ");
            scanf("%f", &d1.expenditure);
            printf("Enter new crop time: ");
            scanf("%s", d1.croptime);
            printf("\nRecord updated successfully!\n");
        }
        fprintf(temp, "%s\t %f\t %f\t %s\n", d1.cropname, d1.area, d1.expenditure, d1.croptime);
    }
    fclose(fp);
    fclose(temp);
    if (!found) 
        printf("\nCrop '%s' not found in records.\n", crop);
    remove("text1.txt");
    rename("temp.txt", "text1.txt");
}

void delete() {
    struct details d1;
    char name[50];
    int found = 0;
    FILE *p = fopen("text1.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (p==NULL||temp==NULL) {
        printf("Error opening file!\n");
        return;
    }
    printf("Enter the crop name that you want to delete: ");
    scanf("%s",name);
    while (fscanf(p,"%s %f %f %s",d1.cropname,&d1.area,&d1.expenditure,d1.croptime)!=EOF) {
        if (strcmp(name,d1.cropname)==0){
            found=1;
            printf("\nCrop '%s' deleted successfully!\n", name);
        } else {
            fprintf(temp,"%s %f %f %s\n",d1.cropname,d1.area,d1.expenditure,d1.croptime);
        }
    }
    fclose(p);
    fclose(temp);
    if(!found){
        printf("\nCrop '%s' not found in the records.\n", name);
    }
    remove("text1.txt");
    rename("temp.txt", "text1.txt");
}

void generate() {
    struct details d1;
    float totalacres=0;
    float totalexpenditure=0;
    FILE *p=fopen("text1.txt", "r");
    if (p==NULL) {
        printf("Error opening file!\n");
        return;
    }
    while (fscanf(p,"%s %f %f %s",d1.cropname,&d1.area,&d1.expenditure,d1.croptime)!=EOF){
        totalacres=totalacres+d1.area;
        totalexpenditure=totalexpenditure+d1.expenditure;
    }
    printf("\n\n%f is the total land avialble untill now\n",totalacres);
    printf("%f is the total expenditure to cultivate entire field\n\n",totalexpenditure);
}
void cropsuggetions(){
    printf("choose the options::\n");
    printf("1.summer crops\t2.winter crops\t3.rainy season");
    int option;
    printf("\nenter your option::");
    scanf("%d",&option);
    switch(option){
        case 1:
            printf("Groundnut, Sesame, Cucumber, Muskmelon");
        case 2:
            printf("Wheat, Mustard, Barley, Gram");
        case 3:
            printf("Paddy, Maize, Jowar, Millets");
        default:
            printf("invalid input");
    }
}

void quit(){
    char quit[10];
    printf("DO YOU WANT TO EXIT FROM HERE REALLY(yes/no)");
    scanf("%s",quit);
    if(strcmp(quit,"yes")==0){
        printf("\t\t\t\t\t OK!!all data is fine.\n");
        printf("\t\t\t\t\t you can go now fine bye::");
    }
}
