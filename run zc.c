

#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include <windows.h>
#include<process.h>



HANDLE wHnd;    // Handle to write to the console.
HANDLE rHnd;


void green()
{
    printf("\033[1;32m");
}
void white()
{
    printf("\033[1;39m");
}


//function to move cursor at the specific coordinate-point of console window
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void loadbar(int when)
{
    int i;
    system("CLS");
    gotoxy(12,9);
    (when == 0) ? printf("\t   ENCRYPTING...") : printf("\t   DECRYPTING...");
    gotoxy(13,10);
    for(i=0;i<=26;i++)
    {
        printf("%c",179);
    }
    gotoxy(13,10);
    for(i=0;i<=26;i++)
    {
        Sleep(50); //sleep activity for every .50 seconds
        printf("%c",177);
    }

    return;
}

int check_filename(const char filename[])
{
    if(strlen(filename)==1)
    {
        if(filename[0] == 'x' || filename[0] == 'X')
            return 2;
        else
        {
            printf("\nFilename should be grater than 1 except character X\n");
            return 1;
        }
    }

    /*if(strstr(filename, "\\/:*;\"<>|"))
       {
        printf("\n\n\t\tHello\n\n");
        printf("\n\t\tSorry, your file name contains unsupported characters.\n");
         return 1;
       }*/
    else
        return 0;
}


int set_password(const char passfile[])
 {
start:
    system("CLS");
    printf("\n\n\t\t\aCAUTION: Once you set a password, it can't be undone\n\t\t to open this application.\n");
    gotoxy(8,8);
    printf("\tLet's get started. You need to specify a \n\t\tpassword to open this application.");
   fflush(stdin);
   char password1[25], ch1 = '\0';
   int i=0;
   FILE *fp1;

   gotoxy(12,10);
   printf("\n\t\tEnter a new password (MAXIMUM 24 Characters): ");


   while (ch1!='\r' && i<25) {
      ch1 = getch();
      if (ch1 == '\b' && i>0)
      {
         i--;
         putch('\b');
         putch('\0');
         putch('\b');
      }
      else if(ch1 !='\r' && ch1 !='\b')
      {
      putch('*');
      password1[i] = ch1;
      i++;
      }

   }
   password1[i] = '\0';

   if(strlen(password1) == 0)
   {
       printf("\n");
       gotoxy(10,11);
       printf("\n\t\tINVALID password\n\t\t");
       system("PAUSE");
       return 1;
   }


   //Confirm password
   printf("\n");
   gotoxy(10,12);
   printf("\tConfirm password : ");
   //gotoxy(50,10);
    char password2[25],ch2 = '\0';
       i = 0;
    while (ch2!='\r' && i<25)
    {
      ch2 = getch();
      if (ch2 == '\b' && i>0)
      {
         i--;
         putch('\b');
         putch('\0');
         putch('\b');
      }
      else if(ch2 !='\r' && ch2 !='\b')
      {
      putch('*');
      password2[i] = ch2;
      i++;
      }

   }
   password2[i] = '\0';

   if(strcmp(password1,password2))
    {
        printf("\n");
        gotoxy(11,14);
        printf("\t\tPasswords are not same.");
        gotoxy(11,15);
        printf("\t\tPlease Try again.\n\t\t");
        gotoxy(11,17);
        system("PAUSE");
        system("CLS");
        goto start;
    }
    else
    {
            char confirm;
            printf("\n\n\n\t\tAre you sure to save this password? \n\t\tOnce you set the password,it can't be undone \n\t\tto open this application.");
            printf("\n\n\t\tPress Y to save this password.");
            printf("\n\t\tPress N to reset new password.");
            printf("\n\t\tPress X to close the program. : ");
            scanf("%c",&confirm);
            if(confirm == 'X' || confirm == 'x')
                exit(1);
            else if(confirm == 'N' || confirm == 'n')
                goto start;
            else if((confirm != 'X' || confirm == 'x') && (confirm != 'N' || confirm == 'n') && (confirm != 'Y' || confirm == 'y'))
                exit(1);
        else
        {
                    if(!(fp1 = fopen(passfile,"w")))
                    {
                        gotoxy(11,18);
                        printf("\t\tError writing file.\n\t\tPlease make sure \n\t\tthis program has access to write\n\t\timportant files in HOMEDRIVE %s\n\t\tProgram is Terminating",getenv("HOMEDRIVE"));
                        Sleep(1700);
                        exit(1);
                    }
                    else
                        {
                            gotoxy(11,25);
                            printf("\n\t\tSuccessfully created password\n\t\t");
                            system("PAUSE");
                        }
                    int len = strlen(password1);
                    for(i=0;i<len;i++)
                        password1[i] = password1[i] + 19;
                    fputs(password1,fp1);
                    fclose(fp1);

                    char tmp[50];
                    sprintf(tmp, "attrib +s +h %s", passfile);
                    system(tmp);
                    //system("attrib +s +h C:\AAA.ZCpk");
                    return 0;
            }

    }

}


int get_password(const char passfile[])
{
    char mainpass[25];
    int cnt=3,j;

    // Getting Password from file
    FILE *fp1;
    if(!(fp1 = fopen(passfile,"r")))
    {
        gotoxy(5,10);
        printf("\n\t\tCan't read from file.\n\t\tFatal Error.\n");
        system("PAUSE");
        return 1;
    }
    fgets(mainpass, 30, fp1);

    //set password to original state
    int len = strlen(mainpass);
    for(j=0;j<len;j++)
        mainpass[j] = mainpass[j] - 19;

    //Now ask for password
    while(cnt>=0)
    {
        system("CLS");
        gotoxy(12,10);
        printf("Enter Current Password : ");
        char password1[25], ch1 = '\0';
        password1[0] = '\0';
        int i = 0;
           while (ch1!='\r' && i<25) {
              ch1 = getch();
              if (ch1 == '\b' && i>0)
              {
                 i--;
                 putch('\b');
                 putch('\0');
                 putch('\b');
              }
              else if(ch1 !='\r' && ch1 !='\b')
              {
              putch('*');
              password1[i] = ch1;
              i++;
              }

           }
           password1[i] = '\0';

           if(strcmp(mainpass,password1))
           {
               --cnt;
               gotoxy(25,10);
               system("cls");
               printf("\n\t\t Wrong Password !\n\t\t Try Again please\n\t\t %d attemp(s) remaining\n",cnt);
               gotoxy(25,14);
               system("PAUSE");
                if(cnt == 0)
                    return 1;
                else
                    continue;
           }
           else
            return 0;
    }

}


void create_contact(void)
{
    char contract_file_name[100];
    FILE *fp1 ;

    filename:
    printf("CAUTION: Please Don't include UNSUPPORTED \\/:*;\"<>| \ncharacters in your filename.\nThis might cause the application CRASH\n\n");
    printf("\t\tPlease Give an APPROPRIATE name for \n\t\tSENDER-RECIPIENT CONTRACT file. \n\t\tPlease Don't use any .zcCNTRT extension\n\t\tFILE NAME.\n\t\tPress 'X' to return main menu:\n\t\t");
    contract_file_name[0] = '\0';
    gets(contract_file_name);
    if(check_filename(contract_file_name) == 1)
        goto filename;
    else if(check_filename(contract_file_name) == 2)
        return;
    else
        strcat(contract_file_name,".zcCNTRT");

    if((fp1=fopen(contract_file_name,"r")))
        {
            printf("\n\t\tA Contract File with %s already EXITS.\n\t\tPlease Choose another name\n\n",contract_file_name);
            goto filename;
        }
        else
        {
            printf("\t\t");
            fp1= fopen(contract_file_name,"w");
            fprintf(fp1,"$Sender: %s?\n",getenv("USERNAME"));
            fclose(fp1);

            char tmp[100+50];
            sprintf(tmp,"wmic path win32_physicalmedia get SerialNumber >> %s",  contract_file_name);
            system(tmp);

            fp1 = fopen(contract_file_name,"a");
            fprintf(fp1,"\n");
            fclose(fp1);

        }
        printf("\n\t\t%s File Created\n",contract_file_name);
        Sleep(1700);
        //system("PAUSE");
        return;
    //menu();
}

void create_bond(void)
{
    char contract_file_name[100],bond_file_name[100],name;
    bond_file_name[0] = '\0';

    FILE *fp1;
    filename:
    printf("CAUTION: Please Don't include UNSUPPORTED \\/:*;\"<>| \ncharacters in your filename.\nThis might cause the application CRASH\n\n");
    printf("\t\tPlease Give SENDER-RECIPIENT CONTRACT \n\t\tfile name that SENDER sent you.\n\t\tPlease Don't append .zcCNTRT extension\n\t\tFILE NAME.\n\t\tPress 'X' to return main menu:\n\t\t ");
    contract_file_name[0] = '\0';
    gets(contract_file_name);
    if(check_filename(contract_file_name) ==1)
        goto filename;
    else if(check_filename(contract_file_name) == 2)
        return;
    else
        strcpy(bond_file_name,contract_file_name);
    strcat(contract_file_name,".zcCNTRT");
    strcat(bond_file_name,".zcBOND");

    if((fp1=fopen(contract_file_name,"r"))== NULL)
    {
        printf("\n\t\tNo Such File %s Found.\n\t\tFile might be Invalid, deleted, lost or\n\t\trenamed as %s .\n\t\tProgram is Terminating\n",contract_file_name,bond_file_name);
        goto filename;
    }
    fclose(fp1);

    fp1=fopen(contract_file_name,"r");
    if(fgetc(fp1)!='$')
    {
        printf("\n\t\tThis file is NOT INITIALIZED by any SENDER.\n\t\tPlease Contact Appropriate SENDER\n");
        Sleep(1700);
        return ;
        //menu();
    }
    fclose(fp1);

    // Show Sender Name
    fp1=fopen(contract_file_name,"r");
    printf("\t\t");
    if(fgetc(fp1)=='$')
    {
        while((name=fgetc(fp1))!='?')
            printf("%c",name);
    }
    fclose(fp1);

    char choose;
    printf("\n\t\tCreate Bond file for this Sender?\n\t\tPress Y to confirm\n\t\tPress N to abort: ");
    scanf("%c",&choose);
    if(choose == 'N' || choose == 'n')
    {
        printf("\n\t\tBond creating Aborted..\n");
        Sleep(1700);
        return ;
        //menu();
    }


    fp1=fopen(contract_file_name,"r");
    while(!feof(fp1))
    {
        if(fgetc(fp1)=='#')
        {
            printf("\n\t\tFile has been COMITTED for\n\t\tSender-RECIPIENT ONCE.... \n\t\tCan not COMMIT Further\n");
            fclose(fp1);

            char rnm_when_exists[100+50];
            sprintf(rnm_when_exists,"rename %s %s",  contract_file_name,bond_file_name);
            system(rnm_when_exists);

            Sleep(1700);
            return ;
            //menu();
        }
    }
    printf("\t\t");
    fclose(fp1);
    fp1 = fopen(contract_file_name,"a");
    fprintf(fp1,"#@RECIPIENT: %s+\n",getenv("USERNAME"));
    fclose(fp1);

    char tmp[100+50];
    sprintf(tmp,"wmic path win32_physicalmedia get SerialNumber >> %s",  contract_file_name);
    system(tmp);


    fp1 = fopen(contract_file_name,"a");
    fprintf(fp1,"\n%%");
    fclose(fp1);

    char rnm[100+50];
    sprintf(rnm,"rename %s %s",  contract_file_name,bond_file_name);
    system(rnm);

    printf("\n");

    printf("\n\t\tSuccessfully created %s\n",bond_file_name);
    Sleep(1700);
    return ;
    //menu();
}

int check_hash_dollar(const char bond_file_name[])
{
    char ch1;
    int check_recipient=0;
    FILE *fp1;

    fp1 = fopen(bond_file_name,"r");
        if((ch1=fgetc(fp1)) != '$')
        {
            printf("\n\t\tNO SENDER was FOUND for this %s file.\n\t\tPlease Contact Recipient \n\t\tor Check for appropriate method for creating Bond file\n\n",bond_file_name);
            return 1;
        }

        rewind(fp1);
        while(!feof(fp1))
        {
            if((ch1 = fgetc(fp1)) == '#')
                    {
                        check_recipient = 0;
                        break;
                    }

            else
                check_recipient = 1;  // NO RECIPIENT FOUND

        }
        if(check_recipient)
            {
                printf("\n\t\tNO RECIPIENT was FOUND for this %s file.\n\t\tPlease Contact Appropriate Recipient\n",bond_file_name);
                return 1;
            }
            /*----------------- End of SENDER - RECIPIENT Validity ------------------ */
    return 0;
}

void encrypt(char bond_file_name[])
{
    fflush(stdin);
    //system("COLOR 3F");
    srand(time(NULL));
    FILE *fp1,*fp2;//*fp3;//*fp_key;
    int key;

    filename:
printf("CAUTION: Please Don't include UNSUPPORTED \\/:*;\"<>| \ncharacters in your filename.\nThis might cause the application CRASH\n\n");
            /*-------------------- Encryption Starts------------------------------*/
                system("CLS");
                char Plainfilename[100],ch1,ch2;
                printf("\n\t\tEncryption Process:\n\t\tMake SURE your .txt file is in the \n\t\tSAME DIRECTORY(FOLDER)\n\t\twhere this program is running\n\t\t( Please DO NOT add any .txt extension. \n\t\tProgram will add .txt \n\t\textension automatically !)\n\t\tEnter a .txt file name to \n\t\tENCRYPT(MAX 50 characters)\n\t\tPress 'X' to return main menu:\n\t\t");
                gets(Plainfilename); //Getting .txt file name
                if(check_filename(Plainfilename) == 1)
                    goto filename;
                else if(check_filename(Plainfilename) == 2)
                    return;
                else
                    Plainfilename[strlen(Plainfilename)] = '\0';
                char EncryptFileName[strlen(Plainfilename)+100];
                //char ZCGazfile[strlen(Plainfilename)+100];

                strcpy(EncryptFileName, Plainfilename);
                //strcpy(ZCGazfile, Plainfilename);

                strcat(Plainfilename,".txt");
                strcat(EncryptFileName,"-");
                strcat(EncryptFileName,bond_file_name);

                //strcpy(ZCGazfile,EncryptFileName);
                strcat(EncryptFileName, ".ZebraCrypt");
                //strcat(ZCGazfile,"_src.ZCGaz");

                if((fp1 = fopen(Plainfilename,"r")) == NULL)
                {
                    system("COLOR 4F");
                    printf("\a\t\tNo file found Labeled as: %s .\n\t\tProgram is terminating....\n",Plainfilename);
                    system("PAUSE");
                    return ;
                    //menu();
                }

                else
                {
                fp2 = fopen(EncryptFileName,"w");
                //fp3 = fopen("Visual Confirm of Encryption.txt","w");
                //fp_key = fopen(ZCGazfile,"w");

                key = (rand() % (25 - 2)) + 2;
                //fputc(key, fp_key);
                //fclose(fp_key);
                fprintf(fp2, "<%c>", key);

                /*fclose(fp2);
                fp2 = fopen(EncryptFileName,"a");*/
                while((ch1 = fgetc(fp1))!= EOF)
                {
                    ch1 = ch1 + key;
                    fputc(ch1, fp2);
                    //fputc(ch1, fp3);
                }

                fclose(fp1);
                fclose(fp2);
                //system("COLOR 6B");
                loadbar(0); //Show fancy Loadbar ENCRYPTING...
                printf("\nEncryption done !\n");
                /*----------------- Share Content Notice-----------------------------------*/
                printf("To share encrypted files,\n\t\tyou MUST Share these 3 files:\n\t\t1. %s.zcBOND\n\t\t2. %s\n\t\t3. ZebraCrypt.exe\n\n",bond_file_name,EncryptFileName);
                EncryptFileName[0] = '\0';
                Plainfilename[0] = '\0';
                }
    /*------------------ Encryption Ends-------------------------------*/
    return;

}

void decrypt(char Plainfilename[], char DecryptFileName[])
{
    fflush(stdin);
    //system("COLOR 3F");
    srand(time(NULL));
    FILE *fp1,*fp2;//*fp3,*fp_key;
    int choose, crypt_key;
    char ch1,ch2;

                /*system("CLS");
                system("COLOR B5");
                printf("Decryption Process:\nMake SURE your %s.zcBOND, _encrt.ZebraCrypt and .ZCGaz files is in the SAME DIRECTORY(FOLDER) \twhere this program is running\nEnter an ZebraCrypted (***_encrt.ZebraCrypt) file name WITHOUT its _encrt.ZebraCrypt\textension.\nPlease DO NOT add _encrt.ZebraCrypt extension, Program will automatically add its \textension: ",bond_file_name);
                gets(Plainfilename); // This time Plainfilename is for getting .ZebraCrypt file name
                Plainfilename[strlen(Plainfilename)] = '\0';

                char DecryptFileName[strlen(Plainfilename)+100];*/
                char ZebraDecrypted[strlen(Plainfilename)+100];
                //char ZCGazfile[strlen(Plainfilename)+100];

                //DecryptFileName[0] = '\0';
                ZebraDecrypted[0] = '\0';
                //ZCGazfile[0] = '\0';

                //strcpy(DecryptFileName, Plainfilename);
                strcpy(ZebraDecrypted,Plainfilename);
                //strcpy(ZCGazfile, Plainfilename);

                //strcat(DecryptFileName, "_encrt.ZebraCrypt");
                strcat(ZebraDecrypted, "_Decrypted.txt");
                //strcat(ZCGazfile,"_src.ZCGAZ");

                if ((fp1 = fopen(DecryptFileName,"r")) == NULL )
                {
                    system("COLOR 4F");
                    printf("\a\t\tNo file found Labeled as: %s .\n\t\tProgram is terminating....\n",DecryptFileName);
                    system("PAUSE");
                    return;
                }
                /*else if ((fp_key = fopen(ZCGazfile,"r")) == NULL)
                {
                    system("COLOR 4F");
                    printf("\aFatal ERROR: Critical Resource file %s NOT Found. \nPlease check for this file\nProgram is terminating....\n",ZCGazfile);
                    system("PAUSE");
                    exit(1);
                }*/
        else
        {
                fp2 = fopen(ZebraDecrypted,"w");

                /*------- Checking for Original method of ZCK 1--------------------*/
                if((ch1 = fgetc(fp1)) != '<')
                {
                        printf("\n\t\tSorry This is not a ZebraCrypted file.\n\t\tFraud-Protection being enabled.\n");
                        fclose(fp1);
                        if(remove(DecryptFileName))
                        {
                            printf("\n\t\tError while Protecting.\n");
                            return;
                        }
                        else
                            printf("\nDONE !!!\n");
                }

                else
                    crypt_key = (int) fgetc(fp1);

                /*------- Checking for Original method of ZCK 2--------------------*/
                if((ch1 = fgetc(fp1)) != '>')
                {
                        printf("\n\t\tSorry This is not a ZebraCrypted file.\n\t\tFraud-Protection being enabled.\n");
                        fclose(fp1);
                        if(remove(DecryptFileName))
                            {
                                printf("\t\tError while Protecting.");
                                return;
                            }
                        else
                                printf("\n\t\tDONE !!!\n");
                }


                while((ch1 = fgetc(fp1))!= EOF)
                {
                    ch1 = ch1 - crypt_key;
                    fputc(ch1, fp2);
                }

                //system("COLOR 30");
                loadbar(1); //Show Fancy loadbar DECRYPTING...
                printf("\n\t\tDecryption done !\n");
                DecryptFileName[0] = '\0';
                Plainfilename[0] = '\0';
                fclose(fp1);
                fclose(fp2);
        }
                return;
}


void check_and_encrypt(void)
{
    char bond_file_name[100],ch1,ch2;
    FILE *fp1, *fp2 ;

    filename:
    printf("CAUTION: Please Don't include UNSUPPORTED \\/:*;\"<>| \ncharacters in your filename.\nThis might cause the application CRASH\n\n");
    bond_file_name[0] = '\0';
    printf("\n\t\tPlease Give an APPROPRIATE name for \n\t\tSENDER-RECIPIENT BOND file.\n\t\tPlease Don't use any .zcBOND extension\n\t\tFILE NAME.\n\t\tPress 'X' to return main menu:\n\t\t");
    gets(bond_file_name);
    if(check_filename(bond_file_name) == 1)
        goto filename;
    else if(check_filename(bond_file_name) == 2)
        return;
    else
        strcat(bond_file_name,".zcBOND");
    if((fp1=fopen(bond_file_name,"r"))== NULL)
        {
            printf("\n\t\tNO BOND File with %s EXITS.\n\t\tPlease Choose correct name\n",bond_file_name);
            goto filename;
        }
    else
    {
        if(check_hash_dollar(bond_file_name))
        {
            printf("\n\t\tCan't Proceed to Encryption\n");
            Sleep(1700);
            return ;
            //menu();
        }
    }


    fclose(fp1);

    fp2 = fopen("SK.zcSK","w");
    fprintf(fp2,"$Sender: %s?\n",getenv("USERNAME"));
    fclose(fp2);

    system("wmic path win32_physicalmedia get SerialNumber >> SK.zcSK");

    fp2 = fopen("SK.zcSK","a");
    fprintf(fp2,"\n");
    fclose(fp2);


    if((fp1=fopen(bond_file_name,"r"))== NULL)
        {
            printf("\n\t\tNO BOND File with %s EXITS.\n\t\tPlease make sure you have this file.\n",bond_file_name);
            Sleep(1700);
            goto filename;
        }
    else
    {
        fp2= fopen("SK.zcSK","r");
        while((ch1 = fgetc(fp1))!= '#')
        {
            ch2 = fgetc(fp2);
            if(ch1 == ch2)
                continue;
            else
            {
                printf("\n\t\tSORRY !!! \n\t\t!YOU ARE NOT ACTUAL SENDER OF THIS FILE!\n\t\tIf you think This is a Mistake\n\t\tplease contact appropriate RECIPIENT\n\n");
                /*------------- So now delete everything from this FALSE SENDER -------------------- */
                /*fclose(fp2);
                fclose(fp1);*/

                _fcloseall();
                Sleep(1700);
                if((remove(bond_file_name)) || (remove("SK.zcSK")))
                {
                    printf("\t\tERROR !!!! ......");
                    Sleep(1700);
                    return ;
                    //menu();
                }
                else
                {
                    Sleep(1700);
                    return ;
                    //menu();
                }

            }
        }

        /*------------ Remove SK.zcSK, that's SENDER's Serial Key------------------------*/
        fclose(fp2);
        if(remove("SK.zcSK"))
        {
            printf("\n\t\tERROR !!!......");
            system("PAUSE");
            return ;
            //menu();
        }

    }
    /*---------------------- Show RECIPIENT INFO --------------------------*/
        if((fp1=fopen(bond_file_name,"r"))== NULL)
        {
            printf("\nNO BOND File with %s EXITS.\n\t\tPlease make sure you have this file.\n",bond_file_name);
            goto filename;
        }

        else
        {
            printf("\t\t");
            while((ch1 = fgetc(fp1)) != '@');
            while((ch1 = fgetc(fp1)) !='+' )
                printf("%c",ch1);
            fclose(fp1);

        }

        bond_file_name[strlen(bond_file_name)-1-6] = '\0'; //for appending into the encrypted filename

        char choose;
        printf("\n\t\tStart Encryption  for this RECIPIENT? \n\t\tPress Y to confirm or N to abort. : ");
        scanf("%c",&choose);
        if(choose == 'Y' || choose == 'y')
            encrypt(bond_file_name);
        else
            printf("\n\t\tEncryption Aborted.\n");

    Sleep(1700);
    return ;
    //menu();
}

void check_and_decrypt(void)
{
    char bond_file_name[100],ch1,ch2;
    FILE *fp1, *fp2, *fp3;

    filename:
    printf("CAUTION: Please Don't include UNSUPPORTED \\/:*;\"<>| \ncharacters in your filename.\nThis might cause the application CRASH\n\n");
    bond_file_name[0] = '\0';
    printf("\n\t\tPlease Give an APPROPRIATE name for \n\t\tSENDER-RECIPIENT BOND file.\n\t\tPlease Don't use any .zcBOND extension\n\t\tFILE NAME.\n\t\tPress 'X' to return main menu:\n\t\t");
    gets(bond_file_name);
    if(check_filename(bond_file_name) == 1)
        goto filename;
    else if(check_filename(bond_file_name) == 2)
        return;
    else
        strcat(bond_file_name,".zcBOND");
    if((fp1=fopen(bond_file_name,"r"))== NULL)
        {
            printf("\n\t\tNO BOND File with %s EXITS.\n\t\tPlease Choose correct name\n",bond_file_name);
            _fcloseall();
            //fclose(fp1);
            goto filename;
        }
    else
    {
        if(check_hash_dollar(bond_file_name))
        {
            printf("\n\t\tCan't Proceed to Decryption\n");
            system("PAUSE");
            return ;
            //menu();
        }
    }
    fclose(fp1);

    fp2 = fopen("RK.zcRK","w");
    printf("\t\t");
    fprintf(fp2,"@RECIPIENT: %s+\n",getenv("USERNAME"));
    fclose(fp2);

    system("wmic path win32_physicalmedia get SerialNumber >> RK.zcRK");

    fp2 = fopen("RK.zcRK","a");
    fprintf(fp2,"\n%%");
    fclose(fp2);

    if((fp1=fopen(bond_file_name,"r"))== NULL)
    {
        printf("\n\t\tNO BOND File with %s EXITS.\n\t\tPlease make sure you have this file.\n",bond_file_name);
        fclose(fp1);
            goto filename;
    }

    go_decrypt:
    printf("CAUTION: Please Don't include UNSUPPORTED \\/:*;\"<>| \ncharacters in your filename.\nThis might cause the application CRASH\n\n");
    printf("\n");
    char Plainfilename[100];
    Plainfilename[0] = '\0';
                system("CLS");
                //system("COLOR B5");
                printf("\t\tDecryption Process:\n\t\tMake SURE your %s, .ZebraCrypt\n\t\tfiles is in the SAME DIRECTORY(FOLDER)\n\t\twhere this program is running\n\t\tEnter an ZebraCrypted (****.ZebraCrypt)\n\t\tfile name WITHOUT its .ZebraCrypt\n\t\textension.\n\t\tPlease DO NOT add .ZebraCrypt extension\n\t\tProgram itself will add it's extension: ",bond_file_name);
                gets(Plainfilename);
                if(check_filename(Plainfilename) == 1)
                    goto go_decrypt;
                else if(check_filename(Plainfilename) == 2)
                    return;

                else    // This time Plainfilename is for getting .ZebraCrypt file name
                    Plainfilename[strlen(Plainfilename)] = '\0';

                char DecryptFileName[strlen(Plainfilename)+100];
                //char ZebraDecrypted[strlen(Plainfilename)+100];
                //char ZCGazfile[strlen(Plainfilename)+100];

                DecryptFileName[0] = '\0';
                //ZebraDecrypted[0] = '\0';
                //ZCGazfile[0] = '\0';

                strcpy(DecryptFileName, Plainfilename);
                //strcpy(ZebraDecrypted,Plainfilename);
                //strcpy(ZCGazfile, Plainfilename);

                strcat(DecryptFileName, ".ZebraCrypt");
                //strcat(ZebraDecrypted, "_Decrypted.txt");
                //strcat(ZCGazfile,"_src.ZCGAZ");

                if ((fp3 = fopen(DecryptFileName,"r")) == NULL )
                {
                    system("COLOR 4F");
                    printf("\a\t\tNo file found Labeled as: %s .\n\t\tPlease Check your file name ....\n",DecryptFileName);
                    Sleep(1700);
                    goto go_decrypt;
                }


    else
    {
        while((ch1 = fgetc(fp1)) != '#');
        fp2 = fopen("RK.zcRK","r");
        while((ch1 = fgetc(fp1)) != '%')
        {
            ch2 = fgetc(fp2);
            if(ch1 == ch2)
                continue;

            else
            {
                printf("\n\t\tSORRY !!!\n\t\t!YOU ARE NOT ACTUAL RECIPIENT OF THIS FILE!\n\t\tIf you think This is a Mistake\n\t\tplease contact appropriate SENDER\n\n");
                /*------------- So now delete everything from this FALSE RECIPIENT -------------------- */
                /*fclose(fp2);
                fclose(fp1);
                fclose(fp3);*/

                _fcloseall();
                Sleep(1700);
                if ((remove(bond_file_name)) || (remove("RK.zcRK")) || (remove(DecryptFileName)))
                {
                    printf("\n\t\tERROR !!!! ......\n");
                    Sleep(1700);
                    return ;
                    //menu();
                }
                else
                    return ;
                    //menu();
            }
        }
        /*------------ Remove RK.zcRK, that's RECIPIENTS's Serial Key------------------------*/
        fclose(fp2);
        if(remove("RK.zcRK"))
        {
            printf("\t\tERROR !!!......");
            Sleep(1700);
            return ;
            //menu();
        }
    }
    if((fp1=fopen(bond_file_name,"r"))== NULL)
    {
        printf("\n\t\tNO BOND File with %s EXITS.\n\t\tPlease make sure you have this file.\n",bond_file_name);
        Sleep(1700);
        fclose(fp1);
        goto filename;
    }
    else
    {
        rewind(fp1);
        ch1 = fgetc(fp1);
        printf("\t\t");
        while((ch1 = fgetc(fp1)) != '?')
            printf("%c",ch1);
        fclose(fp1);
    }

        bond_file_name[strlen(bond_file_name)-1-6] = '\0'; //for appending into the decrypted filename

        char choose;
        printf("\n\t\tStart Decryption  from this SENDER?\n\t\tPress Y to confirm or N to abort. : ");
        scanf("%c",&choose);

        if(choose == 'Y' || choose == 'y')
            decrypt(Plainfilename, DecryptFileName);
        else
            printf("\n\t\tDecryption Aborted.\n");

        system("PAUSE");
        return ;
        //menu();
}

int menu()//menu design
{
    _fcloseall();
  fflush(stdin);
  system("CLS");
  char a = '\0';
  int n = 0;
  fflush(stdin);
  while(1)
    {
        printf("\t\t---------------MAIN MENU---------------\n");
        printf("\t\tPress up arrow and down arrow to change \n\t\tbetween options\t\n\t\tPress Enter to select");
        printf("\n\n\t\t_______________________________________\n\n");
        if(n==0)
        {
           green();
           printf("\t\t>>>CREATE CONTRACT<<<");
           white();
           printf("\n\t\t_______________________________________\n\n\t\tCreate bond\n\t\t_______________________________________\n\n\t\tStart encryption\n\t\t_______________________________________\n\n\t\tStart decryption\n\t\t_______________________________________\n\n\t\tChange Password\n\t\t_______________________________________\n\n\t\tExit");
        }
        else if(n==1)
        {
            printf("\t\tCreate contract\n\t\t_______________________________________\n\n");
            green();
            printf("\t\t>>>CREATE BOND<<<");
            white();
            printf("\n\t\t_______________________________________\n\n\t\tStart encryption\n\t\t_______________________________________\n\n\t\tStart decryption\n\t\t_______________________________________\n\n\t\tChange Password\n\t\t_______________________________________\n\n\t\tExit");
        }
        else if(n==2)
        {
            printf("\t\tCreate contract\n\t\t_______________________________________\n\n\t\tCreate bond\n\t\t_______________________________________\n\n");
            green();
            printf("\t\t>>>START ENCRYPTION<<<");
            white();
            printf("\n\t\t_______________________________________\n\n\t\tStart decryption\n\t\t_______________________________________\n\n\t\tChange Password\n\t\t_______________________________________\n\n\t\tExit");
        }
        else if(n==3)
        {
            printf("\t\tCreate contract\n\t\t_______________________________________\n\n\t\tCreate bond\n\t\t_______________________________________\n\n\t\tStart encryption\n\t\t_______________________________________\n\n");
            green();
            printf("\t\t>>>START DECRYPTION<<<");
            white();
            printf("\n\t\t_______________________________________\n\n\t\tChange Password\n\t\t_______________________________________\n\n\t\tExit");
        }
        else if(n==4)
        {
            printf("\t\tCreate contract\n\t\t_______________________________________\n\n\t\tCreate bond\n\t\t_______________________________________\n\n\t\tStart encryption\n\t\t_______________________________________\n\n\t\tStart decryption\n\t\t_______________________________________\n");

            green();
            printf("\n\t\t>>>CHANGE PASSWORD<<<");
            white();
            printf("\n\t\t_______________________________________\n\n\t\tExit");
        }
        else if(n=5)
        {
             printf("\t\tCreate contract\n\t\t_______________________________________\n\n\t\tCreate bond\n\t\t_______________________________________\n\n\t\tStart encryption\n\t\t_______________________________________\n\n\t\tStart decryption\n\t\t_______________________________________\n\n\t\tChange Password\n\t\t_______________________________________\n\n");
             green();
             printf("\t\t>>>EXIT<<<");
             white();
        }
        printf("\n\t\t_______________________________________\n\n");
        a=getch();
        fflush(stdin);
        if(a=='\r')
        {
            if(n==0)
                return 1;
            else if(n==1)
                return 2;
            else if(n==2)
                return 3;
            else if(n==3)
                return 4;
            else if(n==4)
                return 5;
            else if(n==5)
                return 6;
        }
        if(a==80)
            n=n+1;
        else if(a==72)
            n=n-1;
        if(n<0)
            n=6+n;
        n=n%6;
        fflush(stdin);
        system("CLS");
    }
}



int main()
{


    system("COLOR 3F");
    // Set up the handles for reading/writing:
    wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
    rHnd = GetStdHandle(STD_INPUT_HANDLE);
    // Change the window title:
    SetConsoleTitle("ZebraCrypt v2.2 (from Gazzali, Raiyan, Faiyaz)");
    // Set up the requigreen window size:
    SMALL_RECT windowSize = {0, 0, 70, 50};
    SetConsoleWindowInfo(wHnd, 1, &windowSize);
    COORD bufferSize = {10, 10};
    SetConsoleScreenBufferSize(wHnd, bufferSize);
    //system("attrib -s -h C:\\AAA.ZCpk"); //Show'em PK

    //return 0;

    /*--------------- Welcome Screen Starts--------------------------------*/
    printf("\t\t-----Welcome To ZebraCrypt v 2.2.1.-----\n\t\tA WINDOWS(R) OS based .txt file encryption program\n\t\tthat encrypts .txt files with DYNAMIC Encryption key.\n\t\tIt chooses a dynamic key each time\n\t\tyou run this program to encrypt your\n\t\ttext(.txt) file.\n\n\t\tCAUTION: Your text(.txt) MUST be written in\n\t\tANSI Standard fonts\n\t\tThis program can Encrypt or Decrypt\n\t\tANSI characters!\n\t\tSo, Let's GET ZebraCrypted!\n\n\n");
    printf("\t\t");
    system("PAUSE");
    /*---------------- Welcome Screen Ends---------------------------------*/
    int choice=1;

    char passfile[20];
    FILE *fp1;
    //printf("This is : %s\n",getenv("HOMEDRIVE"));
    strcpy(passfile, getenv("HOMEDRIVE"));
    strcat(passfile,"\\AAA.zcPK");

    if((fp1 = fopen(passfile,"r")) == NULL)
    {
        system("CLS");
        while(set_password(passfile))
            set_password(passfile);
        //goto start;
    }

    else if(get_password(passfile))
    {
        gotoxy(25,16);
        printf("\n\t\tSorry ! \n\t\tProgram is terminating.....\n");
        Sleep(1700);
        exit(1);
    }

    //else
    //{
        start:
        while(choice<7 && choice>0)
        {
            fflush(stdin);
            choice=menu();
            //printf("\n\n%d\n\n",choice);
            switch(choice)
            {
            case 1:
                system("cls");
                create_contact();
                break;
                        //CREATE CONTRACT
            case 2:
                system("cls");
                create_bond();
                break;
                    //CREATE BOND
            case 3:
                system("cls");
                check_and_encrypt();
                break;
                    //START ENCRYPTION
            case 4:
                 system("cls");
                 check_and_decrypt();
                 break;
                       //START DECRYPTION
            case 5: //Change password
                   {
                    system("CLS");
                    if(get_password(passfile))
                    {
                        gotoxy(25,16);
                        printf("\n\t\tSorry ! \n\t\tProgram is terminating.....\n");
                        Sleep(1700);
                        exit(1);
                    }
                    else
                    {
                        system("attrib -s -h C:\\AAA.ZCpk");
                        while(set_password(passfile))
                            set_password(passfile);
                    }
                   }
                    break;

            case 6:
                 system("cls");
                 gotoxy(12,10);
                 printf("Like ZebraCrypt ? Please Share it with your friends.\n\t\t\tHappy CRYPTING !!!!\n\n\t\t");
                 system("PAUSE");
                 exit(1);
                 break;//SAVE & EXIT
            default : printf("Wrong Selection.");
            }
        }
    //}
}
