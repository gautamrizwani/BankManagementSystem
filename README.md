# BankManagementSystem

## How to execute?

- Firstly Add a new Admin using a file called "data.c"
- Change the Absolute path mentioned in the code.
- Now Compile and Run the Server:
```
cc server.c -o server.out
./server.out
```
- Compile and Run the Client
```
cc client.c -o client.out
./client.out
```
- Done!

## Outputs:

- On Running Client:
# ![InitClient](./Outputs/Welcome_Page.png)
- Logging Admin In, and creating Normal Account:
# ![InitClient](./Outputs/Create_Nor_Acc.png)
- Admin Modifying Account:
# ![InitClient](./Outputs/ModifyAcc.png)
- Admin can Search and View Details of an Account
# ![InitClient](./Outputs/Admin_Search_Acc.png)
- Admin can Delete Accounts
# ![InitClient](./Outputs/Admin_Del_Acc.png)
- Logging Normal User In, and Viewing Data
# ![InitClient](./Outputs/ViewDetails.png)
- User can Deposite and Withdraw Money from the Accounts(Obviously)
# ![InitClient](./Outputs/DepositeWithdraw.png)
- All the Operations of User are Validated, For eg:
# ![InitClient](./Outputs/ValidDeposite.png)
- Users can also Change their Passwords
# ![InitClient](./Outputs/Change_Password.png)
- Concurrency is taken care of in all the functions, For eg. Withdrawals at the same time:
# ![InitClient](./Outputs/ConcurrWithdraw.png)
- But Users can View their Balances/Details Concurrently:
# ![InitClient](./Outputs/ConcurrViewData.png)
