#!/bin/sh
# Assignment 1: Shell Programming
# Expected to perform following operations on the DB: 1)Create,2) View, 3)Insert,4) Delete,5)Modify,6)Exit
# Stock Records	Item Name, Deadstock No., Purchase Order No.,Type(Consumable/NonConsumable)

declare -A NAME         #Declarigng Variable Name 
declare -A DEADSTOCK_NO #Declarigng Deadstock No
declare -A ORDER_NO     #Declarigng Order No
declare -A TYPE         #Declarigng Item Type
declare -A DEL_FLAG     #Declarigng flag for logical delete
declare N
let N=0                 #Initializing toal no. of records as zero
while [ "0" -eq "0" ]   #Beginning of lop for multiple access of switch case
do
    echo -e "\n1)Create\n2)View\n3)Insert\n4)Delete\n5)Modify\n6)Exit\n"
    echo -e -n "Enter Choice: "
    read CHOICE
    case "$CHOICE" in #runs switch case
    "1") echo "Creating New Database"
        echo -e -n "Enter the number of records you will enter: "
        read N
        i=0
        while [ "$i" -lt "$N" ]             #Run no of iterations equal to the no. of records that user wants
        do
            echo "Item No. $[i+1]"
            echo -e -n "Enter the item Name: "
            read NAME[$i]
            echo -e -n "Enter the Deadstock No.: "
            read DEADSTOCK_NO[$i]
            echo -e -n "Enter the Order No.: "
            read ORDER_NO[$i]
            echo -e -n "Enter the item Type(Consumable/NonConsumable)\nEnter 0 for Consumable, 1 for Non-Consumable: "
            read TYPE[$i]
            let DEL_FLAG[$i]=0
            let i++
            done
        ;;
    "2") 
        echo "Viewing Database"
        echo -e "Displaying Database:\n"
        echo -e "ItemName\tDeadstock No.\tPurchase Order No.\tType"
        let i=0
        while [ "$i" -lt "$N" ]             #Traverse all the records that exist
        do
            if [ "${DEL_FLAG[$i]}" -eq "0" ]    #if flag is not raised
            then                                #then print records
                echo -e "${NAME[$i]}\t${DEADSTOCK_NO[$i]}\t${ORDER_NO[$i]}\t${TYPE[$i]}"
            fi                                  #else ignore
            let i++
        done
        ;;
    "3") echo "Inserting Record"            #Appends record at end of database
        let i=N
        echo -e -n "Enter the item Name: "
        read NAME[$i]
        echo -e -n "Enter the Deadstock No.: "
        read DEADSTOCK_NO[$i]
        echo -e -n "Enter the Order No.: "
        read ORDER_NO[$i]
        echo -e -n "Enter the item Type(Consumable/NonConsumable)\nEnter 0 for Consumable, 1 for Non-Consumable: "
        read TYPE[$i]
        let DEL_FLAG[$i]=0
        let N++
        ;;
    "4") echo "Deleting Record"             #Purchase order is treated as a key attribute
        echo -e "Enter the Purchase Order No."
        read PURNO                          #Input purchase number of record to be deleted from user
        let i=0
        while [ "$i" -lt "$N" ]             #traverse all records
        do
            if [ "$PURNO" -eq "${ORDER_NO[$i]}" ]   #If Key value matches
            then                                    #then logically delete that record 
                echo -e "Deleting the following Record" 
                echo -e "${NAME[$i]}\t${DEADSTOCK_NO[$i]}\t${ORDER_NO[$i]}\t${TYPE[$i]}"
                let DEL_FLAG[$i]=1                  #by tripping that flag variable
                break                               #touch only single record at a time hence break
            fi
            let i++
        done
        ;;
    "5") echo "Modifying Record"         #Purchase order is treated as a key attribute
        echo -e "Enter the Purchase Order No."
        read PURNO                       #Input purchase number of record to be deleted from user
        let i=0
        while [ "$i" -lt "$N" ]         #traverse all records 
        do
            if [ "$PURNO" -eq "${ORDER_NO[$i]}" ]    #If Key value matches
            then                                     # then modify entire record
                echo -e "Modifying the following Record"
                echo -e "${NAME[$i]}\t${DEADSTOCK_NO[$i]}\t${ORDER_NO[$i]}\t${TYPE[$i]}"
                echo -e -n "Enter the item Name: "
                read NAME[$i]
                echo -e -n "Enter the Deadstock No.: "
                read DEADSTOCK_NO[$i]
                echo -e -n "Enter the Order No.: "
                read ORDER_NO[$i]
                echo -e -n "Enter the item Type(Consumable/NonConsumable)\nEnter 0 for Consumable, 1 for Non-Consumable: "
                read TYPE[$i]
                let DEL_FLAG[$i]=0
                break                               #touch only single record at a time hence break
            fi
            let i++
        done
        ;;
    "6") echo "Exiting"                 #exit condition
        echo "Thank You for Using our Services"
        break 
        ;;
    *) echo                             #catch all-other case
        "Incorrect Input Perhaps, Try again"
        ;;
    esac
done