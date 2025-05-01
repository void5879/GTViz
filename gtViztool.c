//Header Files
#include <stdio.h>
#include <stdbool.h>
//Global variables
int valueN;
int identityElmnt;
//Functions
int closureCheck(int* arr, int sizeofArr, int storeTable[][sizeofArr], int key){
    if (key == 1){
        for (int i = 0; i < sizeofArr; ++i){
            for (int j = 0; j < sizeofArr; ++j){
                storeTable[i][j] = arr[i] + arr[j];
            }
        }
    } else if (key == 2){
        for (int i = 0; i < sizeofArr; ++i){
            for (int j = 0; j < sizeofArr; ++j){
                storeTable[i][j] = arr[i] - arr[j];
            }
        }
    } else if (key == 3){
        for (int i = 0; i < sizeofArr; ++i){
            for (int j = 0; j < sizeofArr; ++j){
                storeTable[i][j] = arr[i] * arr[j];
            }
        }
    } else if (key == 4){
        for (int i = 0; i < sizeofArr; ++i){
            for (int j = 0; j < sizeofArr; ++j){
                if (arr[j] == 0) {
                    printf("Error: Division by zero at arr[%d]!\n", j);
                    return -1;
                }
                storeTable[i][j] = arr[i] / arr[j];
            }
        }
    } else if (key == 5){
        printf("Enter value of n (in '+ mod n'): ");
        scanf("%d",&valueN);
        for (int i = 0; i < sizeofArr; ++i){
            for (int j = 0; j < sizeofArr; ++j){
                storeTable[i][j] = (arr[i] + arr[j]) % valueN;
            }
        }
    }
    bool flag = true ;
    int temp;
    for (int i = 0; i < sizeofArr; ++i){
        for (int j = 0; j < sizeofArr; ++j){
            temp = storeTable[i][j];
            bool found = false;
            for(int k = 0; k < sizeofArr; ++k){
                if (temp == arr[k]){
                    found = true;
                    break;
                }
            }
            if (!found){
                flag = false;
                break;
            }
        }
        if (!flag){
            break;
        }
    }
    if (flag){
        printf("Closure property satisfied !\n");
        return 0;
    } else {
        printf("Closure property NOT satisfied !\nGiven Set and associated operation does NOT form a GROUP !\n");
        return -1;
    }
}
int associativityCheck(int* arr, int sizeofArr, int key){  
    bool flag = true;
    for (int i = 0; i < sizeofArr && flag; ++i) {
        for (int j = 0; j < sizeofArr && flag; ++j) {
            for (int k = 0; k < sizeofArr; ++k) {
                int a = arr[i], b = arr[j], c = arr[k];
                int lhs, rhs;
                switch (key) {
                    case 1:
                        lhs = a + (b + c);
                        rhs = (a + b) + c;
                        break;
                    case 2:
                        lhs = a - (b - c);
                        rhs = (a - b) - c;
                        break;
                    case 3:
                        lhs = a * (b * c);
                        rhs = (a * b) * c;
                        break;
                    case 4:
                        if (b == 0 || c == 0) {
                            printf("Error: Division by zero at arr[%d] or arr[%d]!\n", j, k);
                            return -1;
                        }
                        lhs = a / (b / c);
                        rhs = (a / b) / c;
                        break;
                    case 5:
                        lhs = (a + ((b + c) % valueN)) % valueN;
                        rhs = (((a + b) % valueN) + c) % valueN;
                        break;
                    default:
                        printf("Invalid operation key!\n");
                        return -1;
                }
                if (lhs != rhs) {
                    flag = false;
                    break;
                }
            }
        }
    }
    if (flag) {
        printf("Associative property satisfied!\n");
        return 0;
    } else {
        printf("Associative property NOT satisfied!\nGiven Set and associated operation does NOT form a GROUP!\n");
        return -1;
    }
}
int identityCheck(int* arr, int sizeofArr, int storeTable[][sizeofArr]) {
    for (int e = 0; e < sizeofArr; ++e){
        bool isIdentity = true;
        for (int i = 0; i < sizeofArr; ++i){
            if (!(storeTable[e][i] == arr[i] && storeTable[i][e] == arr[i])){
                isIdentity = false;
                break;
            }
        }
        if (isIdentity){
            identityElmnt = arr[e];
            printf("Identity element found! Element: %d\n", arr[e]);
            return 0;
        }
    }
    printf("Identity element NOT found!\nGiven Set and associated operation does NOT form a GROUP!\n");
    return -1;
}
int inverseCheck(int* arr, int sizeofArr, int storeTable[][sizeofArr]){
    for (int i = 0; i < sizeofArr; ++i){
        bool hasInverse = false;
        for (int j = 0; j < sizeofArr; ++j){
            if ((storeTable[i][j] == identityElmnt) && (storeTable[j][i] == identityElmnt)){
                printf("Element %d has inverse %d\n", arr[i], arr[j]);
                hasInverse = true;
                break;
            }
        }
        if (!hasInverse){
            printf("Element %d does not have an inverse!\nGiven Set and associated operation does NOT form a GROUP!\n", arr[i]);
            return -1;
        }
    }
    printf("All elements have inverses!\n");
    return 0;
}
//Main
int main(){
    printf("GROUP THEORY VISUALIZATION TOOL\n");
    int sizeofArr;
    printf("Enter the total elements of the set you wish to check (! max of 6 !): ");
    scanf("%d",&sizeofArr);
    if (sizeofArr > 6 || sizeofArr <= 0){
        printf("Enter a Valid Size !\n");
        return -1;
    }
    int arr[sizeofArr];
    printf("Enter the elements of the set you wish to check (eg: 1,2,3): ");
    for (int i = 0; i < sizeofArr; ++i){
        scanf("%d,",&arr[i]);
    }
    int storeTable[sizeofArr][sizeofArr];
    int key;
    printf("The associated Set operation available:\n");
    printf("1--->Addition(+)\n");
    printf("2--->Subtraction(-)\n");
    printf("3--->Multiplication(*)\n");
    printf("4--->Division(/)\n");
    printf("5--->Addition Modulo(+ mod n)\n");
    printf("Enter operation: ");
    scanf("%d",&key);
    int check1 = closureCheck(arr,sizeofArr,storeTable,key);
    if (check1 == 0){
        int check2 = associativityCheck(arr,sizeofArr,key);
        if (check2 == 0){
            int check3 = identityCheck(arr,sizeofArr,storeTable);
            if (check3 == 0){
                int check4 = inverseCheck(arr,sizeofArr,storeTable);
                if (check4 ==0){
                    printf("The given set with the associated binary operation forms a GROUP !\n");
                }
            }
        }
    }
    return 0;
}
