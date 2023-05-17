//S2_20206007
#include <iostream>
using namespace std;

//function to generate ID
int itemID=0;
int generateItemID()
{
    return ++itemID;
}

class item
{
private:
    int ID;
    string name;
    int quantity;
    double price;

public:
    //default constructor
    item()
    {
        ID=generateItemID();
        name = "";
        quantity=0;
        price=0;
    }

    //parameterized constructor
    item(string nameParam, int quantityParam, double priceParam)
    {
        ID=generateItemID();
        name=nameParam;
        quantity=quantityParam;
        price=priceParam;
    }

    //copy constructor
    item(const item &obj)
    {
        ID=obj.ID;
        name=obj.name;
        quantity=obj.quantity;
        price=obj.price;
    }

    //setters & getters
    void setName(string n)
    {name=n;}

    void setQuantity(int quan)
    {quantity=quan;}

    void setPrice(double pri)
    {price=pri;}

    int getID()
    {return ID;}

    string getName()
    {return name;}

    int getQuantity()
    {return quantity;}

    double getPrice()
    {return price;}


    //operator overloading
    bool operator==( item &obj)
    {
        if(name==obj.name)
            return true;
        else
            return false;
    }

    item operator+=(item &obj)
    {
        quantity=quantity+obj.quantity;
    }

    item operator-=(int quantitySoldParam)
    {
        quantity=quantity-quantitySoldParam;
    }

    friend ostream& operator<<(ostream& os, const item &obj)
    {
        os << "Name is " << obj.name << "\nQuantity equals " << obj.quantity << "\nPrice is " << obj.price;
        return os;
    }
    friend istream& operator>>(istream& is, item &obj)
    {
        cout << "Enter item's name" << endl;
        is >> obj.name;
        cout << "Enter item's quantity" << endl;
        is >> obj.quantity;
        cout << "Enter item's price" << endl;
        is >> obj.price;
        return is;
    }
};

class seller
{
private:
    string name, email;
    item * items;
    int maxItems;

public:
    //accessing item functions
    friend class item;

    //parametrized constructor
    seller(string nameParam, string emailParam, int maxItemsParam)
    {
        name=nameParam;
        email=emailParam;
        maxItems=maxItemsParam;
        items = new item[maxItems];
    }

    //operator<<
    friend ostream& operator<<(ostream& os, const seller &obj)
    {
        os << "Name is " << obj.name << "Email equals " << obj.email << "Max items is " << obj.maxItems;
        return os;
    }

    static int counter;

    //add an item
    bool addAnItem(item &obj)
    {
        for (int i=0; i<=maxItems; i++)
        {
            if (items[i]==obj)
            {
                items[i].operator+=(obj);
                break;
            }
            else
            {
                items[counter]=obj;
                counter++;
                break;
            }
        }
    }

    //sell an item
    bool sellAnItem(string nameParam, int quantityParam)
    {
        for(int i=0; i<maxItems; i++)
        {
            if((items[i].getName()==nameParam))
            {
                if(quantityParam<=items[i].getQuantity())
                {
                    items[i].operator-=(quantityParam);
                    break;
                }
                else
                {
                    cout << "There is only " << items[i].getQuantity() << " left for this item." << endl;
                    break;
                }
            }
        }
    }

    //print items
    void printItems()
    {
        for(int i=0; i<maxItems; i++)
        {
            cout << "ITEM #" << i+1 << "\n" << items[i] << endl;
        }
    }

    //find an item by ID
    item findItemByID(int IDParam)
    {
        for (int i=0; i<maxItems; i++)
        {
            if((items[i].getID()-maxItems)==IDParam)
            {
                return items[i];
            }
        }
        if(true)
        {
            cout << "There is no item with this ID" << endl;
        }
    }

    //destructor
    ~seller()
    {
        delete items;
    }

};
int seller::counter=0;

int main()
{
    int choice;
    string nameParam,emailParam;
    int maxItemsParam;

    cout << "Please input your details {name then email}" << endl;
    getline(cin,nameParam);
    cin.ignore();
    getline(cin,emailParam);

    cout << "Please input your store capacity" << endl;
    cin >> maxItemsParam;

    seller no1(nameParam, emailParam, maxItemsParam);


    do
    {
        cout <<"\n";
        cout << "1. Print My Info" << endl;
        cout << "2. Add An Item" << endl;
        cout << "3. Sell An Item" << endl;
        cout << "4. Print Items" << endl;
        cout << "5. Find an Item by ID" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice" << endl;
        cin >> choice;
        cout <<"\n";


        if(choice==1)
        {
            cout << "Name is " << nameParam << endl;
            cout << "Email is " << emailParam << endl;
            cout << "Your maximum items is " << maxItemsParam << endl;
        }
        if(choice==2)
        {
            item A;
            cin >> A; //setting values of item A
            no1.addAnItem(A);
        }
        if(choice==3)
        {
            string itemSoldName;
            int quantitySold;
            cout << "What is the item's name?" << endl;
            cin.ignore();
            getline(cin,itemSoldName);
            cout << "How many you want" << endl;
            cin >> quantitySold;
            no1.sellAnItem(itemSoldName, quantitySold);
        }
        if(choice==4)
        {
            no1.printItems();
        }
        if(choice==5)
        {
            int IDFind; // variable for finding an item by ID
            cout << "Enter ID of wanted item" << endl;
            cin>> IDFind;
            cout << no1.findItemByID(IDFind) << endl;
        }
    }
    while (choice!=6);

    return 0;
}
