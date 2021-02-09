#include<iostream>
#include<cstring>
using namespace std;

struct hashTable
{
    string key;
    int64_t value;
    bool isEmpty=true;
    hashTable *next;
    
};

class Contacts
{
    int num;        //number of entries
    hashTable *phoneBook;
    
public:
    Contacts():phoneBook(NULL)
    {
    }

    void Add()
    {
        int index;
        int64_t phoneNumber;
        string name;
        

        cout<<"ENTER THE NO. OF ENTRIES :  ";
        cin>>num;
        phoneBook=new hashTable[num];
        
        cout<<"\nENTER NAME AND PHONE NO. : "<<endl;
        for(int i=0;i<num;i++)
        {
            cin>>name>>phoneNumber;
            index=hashing(name,num);
        
            if(phoneBook[index].isEmpty)
            {                                       //if the slot is empty(no collision)...
                phoneBook[index].key=name;
                phoneBook[index].value=phoneNumber;
                phoneBook[index].isEmpty=false;     //it is now filled...
                phoneBook[index].next=NULL;
               
            }
        
            else
            {           //in case of collision...
                hashTable *temp=&(phoneBook[index]);
                while(temp->next!=NULL)
                {
                    temp=temp->next;
                }
            
                temp->next=new hashTable;
                temp->next->key=name;
                temp->next->value=phoneNumber;
                temp->next->isEmpty=false;
                temp->next->next=NULL;
                
            }
        }
        
        cout<<"\nCONTACT LIST UPDATED SUCCESSFULLY\n\n";
    }

    int hashing(string name,int n)
    {
        int len,sum=0;
        
        //converting string into char array...
        len=name.length();
        char temp[len+1];
        strcpy(temp,name.c_str());
        
        //calculating hash value...
        for(int i=0;i<len;i++)
        {
            sum=sum+temp[i];
        }
        return (sum%n);
    }

    void SearchContact(string name)
    {
        int check;
        check=hashing(name,num);

        if(phoneBook[check].next==NULL)
        {   //if there is no collision seen in the current block..
            if(phoneBook[check].key==name)
            {
                cout<<"\n\n--- CONTACT DETAILS --- \n";
                cout<<"\nNAME : "<<phoneBook[check].key<<endl;
                cout<<"\nPHONE NO. : "<<phoneBook[check].value<<endl;
            }
            
            else
            {
                cout<<"CONTACT NOT FOUND !\n\n";
            }
        }

        else
        {   //if collision is seen in the current block...
            hashTable *temp=&(phoneBook[check]);
            while(temp!=NULL)
            {
                if(temp->key==name)
                {
                    cout<<"NAME : "<<temp->key<<endl;
                    cout<<"PHONE NO. : "<<temp->value<<endl;
                    break;
                }
                
                else
                    temp=temp->next;
            }

            if(temp==NULL)
                cout<<"CONTACT NOT FOUND !\n\n";
        }
    }


    ~Contacts()
    {
        delete []phoneBook;
    }



};

int main()
    {
        string name;
        int n,ch;
        Contacts d1;
        
        do
        {
            cout<<"----- WELCOME TO PHONE BOOK DIRECTORY -----\n\n";
            cout<<"1. ADD CONTACT\n";
            cout<<"2. SEARCH CONTACTS\n";
            cout<<"0. EXIT THIS APPLICATION\n";
            cout<<"\nENTER YOUR CHOICE : ";
            cin>>ch;
            switch(ch)
            {
                case 1:
                    d1.Add();
                    break;

                case 2:
                    cout<<"\nENTER THE CONTACT'S NAME :  ";
                    cin>>name;
                    d1.SearchContact(name);
                    cout<<"\n\n";
                    break;


                default: ch=0;
                         cout<<"\nTHANK YOU\n";
                        break;
             }

        } while(ch != 0);

	return 0;
}
