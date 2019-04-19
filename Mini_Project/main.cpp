
///Make Metal Layers Uni Directional

///Add cost of via

///Backtrack



#include <iostream>

#include <stdio.h>

#include <time.h>

using namespace std ;





struct vect {
    
    int x_coordinate = 0;
    
    int y_coordinate = 0 ;
    
    int z_coordinate = 0 ;
    
};



struct cell

{
    
    bool obstacle  = false;
    
    int number = 0 ;
    
    bool S = false;
    
    bool T  = false;
    
};



bool input_validate (bool first , int grid_width , int grid_length ,vect& S , vect& E , cell *** Matrix) ;

void print_number(cell *** Matrix , const int grid_width , const int grid_length) ;

void print_obstacle(cell *** Matrix , const int grid_width , const int grid_length) ;


int main(int argc, const char * argv[]) {
    
    
    
    vect S;
    
    vect S_reverse ;
    
    vect S_copy;
    
    vect E;
    
    vect E_copy ;
    
    int grid_width = 0;
    
    int grid_length = 0 ;
    
    cell *** Matrix  ;
    
    bool  soukup = false ;
    
    bool fill = false ;
    
    bool exit = false ;
    
    int cell_count = 0 ;
    
    int vias_count = 0 ;
    
    float vias_cost ;
    
    
    
    cout <<"Enter Grid Width";
    
    cin >> grid_width ;
    
    
    
    while (grid_width < 1 )
        
    {
        
        cout <<"Width Less than 1, please Re-enter";
        
        cin >> grid_width ;
        
    }
    
    
    
    cout <<"Enter Grid Length";
    
    cin >> grid_length ;
    
    
    
    while (grid_length < 1 )
        
    {
        
        cout <<"Length Less than 1, please Re-enter";
        
        cin >>grid_length;
        
    }
    
    
    
    cout << "Enter Vias Cost";
    
    cin >> vias_cost ;
    
    
    
    while (vias_cost <0)
        
    {
        
        cout << "Re-enter Cost";
        
        cin >>vias_cost ;
        
    }
    
    
    
    exit = input_validate (1,grid_width , grid_length ,  S , E ,Matrix);
    
    
    
    Matrix = new cell **[grid_width];
    
    
    
    for (int i=0 ;i< grid_width ; i++)
        
        Matrix[i] = new cell *[grid_length];
    
    
    
    
    
    for (int j =0 ;j< grid_length ;j++)
        
        for (int i=0 ;i<grid_width ;i++)
            
            Matrix[i][j] = new cell [3];
    
    
    
    for (int z = 0 ; z< 3 ;z++)
        
        for (int j =0 ;j< grid_length ;j++)
            
            for (int i=0 ;i<grid_width ;i++)
                
            {
                
                Matrix[i][j][z].number =0;
                
                Matrix[i][j][z].obstacle = false;
                
                Matrix[i][j][z].S = false ;
                
                Matrix[i][j][z].T = false;
                
            }
    
    // Matrix[7][4][0].obstacle = true ;
    
    while (!exit)
        
    {
        
        double time_taken ;
        
        cell_count = 0 ;
        
        vias_count = 0 ;
       
        
        /////// Mark Cell with Source  ////////
        
        
        
        Matrix [S.x_coordinate] [S.y_coordinate] [S.z_coordinate].S = true ;
        
        cell_count ++ ;
        
        
        
        ////// Mark Cell With Target ////
        
        
        
        Matrix [E.x_coordinate] [E.y_coordinate][E.z_coordinate].T = true ;
        
        cell_count ++ ;
        
        
        
        if (S.x_coordinate == E.x_coordinate && S.y_coordinate == E.y_coordinate && S.z_coordinate == E.z_coordinate)
            
            cell_count -- ;
        
        
        
        print_obstacle( Matrix , grid_width ,  grid_length);
        
        
        
        exit = input_validate (0,grid_width , grid_length ,  S , E , Matrix);
        
        
        
    }
    
    return 0;
    
}

bool input_validate (bool first , int grid_width , int grid_length ,vect& S , vect& E , cell *** Matrix)

{
    
    bool exit = false ;
    
    cout <<"Enter Starting Point X_coordinate";
    
    cin >> S.x_coordinate ;
    
    
    
    while (S.x_coordinate >= grid_width)
        
    {
        
        cout << "Out Of Bounds,please Re-enter";
        
        cin >>  S.x_coordinate ;
        
    }
    
    
    
    if (S.x_coordinate < 0 )
        
        exit = true ;
    
    
    
    cout <<"Enter Starting Point Y_Coordinate";
    
    cin >> S.y_coordinate ;
    
    
    
    while ( S.y_coordinate >= grid_length )
        
    {
        
        cout << "Out Of Bounds, please Re-enter";
        
        cin >> S.y_coordinate ;
        
    }
    
    
    
    if (S.y_coordinate < 0)
        
        exit = true ;
    
    
    
    cout <<"Enter Starting Metal Layer";
    
    cin >> S.z_coordinate ;
    
    
    
    while (S.z_coordinate > 3 || S.z_coordinate < 1 )
        
    {
        
        cout << "Out Of Bounds, please Re-enter";
        
        cin >>  S.z_coordinate;
        
    }
    
    
    
    if (S.z_coordinate < 0)
        
        exit = true ;
    
    
    
    S.z_coordinate -= 1 ;
    
    
    
    if (!first && !exit)
        
    {
        
        while (Matrix[S.x_coordinate][S.y_coordinate][S.z_coordinate].obstacle == true )
            
        {
            
            cout <<"Source Occupied"<<endl;
            
            
            
            cout <<"Enter Starting Point X_coordinate";
            
            cin >> S.x_coordinate ;
            
            
            
            while (S.x_coordinate >= grid_width)
                
            {
                
                cout << "Out Of Bounds,please Re-enter";
                
                cin >>  S.x_coordinate ;
                
            }
            
            
            
            if (S.x_coordinate < 0 )
                
                exit = true ;
            
            
            
            cout <<"Enter Starting Point Y_Coordinate";
            
            cin >> S.y_coordinate ;
            
            
            
            while ( S.y_coordinate >= grid_length )
                
            {
                
                cout << "Out Of Bounds, please Re-enter";
                
                cin >> S.y_coordinate ;
                
            }
            
            
            
            if (S.y_coordinate < 0)
                
                exit = true ;
            
            
            
            cout <<"Enter Starting Metal Layer";
            
            cin >> S.z_coordinate ;
            
            
            
            while (S.z_coordinate > 3 || S.z_coordinate < 1 )
                
            {
                
                cout << "Out Of Bounds, please Re-enter";
                
                cin >>  S.z_coordinate;
                
            }
            
            
            
            if (S.z_coordinate < 0)
                
                exit = true ;
            
            
            
            S.z_coordinate -= 1 ;
            
            
            
            
            
            
            
        }
        
    }
    
    cout <<"Enter Ending Point X_coordinate";
    
    cin >> E.x_coordinate ;
    
    
    
    while ( E.x_coordinate >= grid_width)
        
    {
        
        cout << "Out Of Bounds,please Re-enter";
        
        cin >>  E.x_coordinate ;
        
    }
    
    
    
    if (E.x_coordinate < 0)
        
        exit = true ;
    
    
    
    cout <<"Enter Ending Point Y_Coordinate";
    
    cin >> E.y_coordinate ;
    
    
    
    while ( E.y_coordinate >= grid_length )
        
    {
        
        cout << "Out Of Bounds, please Re-enter";
        
        cin >> E.y_coordinate ;
        
    }
    
    if (E.y_coordinate < 0)
        
        exit = true ;
    
    
    
    cout <<"Enter Ending Metal Layer";
    
    cin >> E.z_coordinate ;
    
    
    
    while (E.z_coordinate > 3 || E.z_coordinate < 1 )
        
    {
        
        cout << "Out Of Bounds, please Re-enter";
        
        cin >>  E.z_coordinate;
        
    }
    
    
    
    if (E.z_coordinate < 0)
        
        exit = true ;
    
    
    
    E.z_coordinate -= 1 ;
    
    
    
    if (E.z_coordinate < 0)
        
        exit = true ;
    
    
    
    if (!first && !exit)
        
    {
        
        while (Matrix[E.x_coordinate][E.y_coordinate][E.z_coordinate].obstacle == true )
            
        {
            
            cout <<"target is Occupied"<<endl ;
            
            cout <<"Enter Ending Point X_coordinate";
            
            cin >> E.x_coordinate ;
            
            
            
            while ( E.x_coordinate >= grid_width)
                
            {
                
                cout << "Out Of Bounds,please Re-enter";
                
                cin >>  E.x_coordinate ;
                
            }
            
            
            
            if (E.x_coordinate < 0)
                
                exit = true ;
            
            
            
            cout <<"Enter Ending Point Y_Coordinate";
            
            cin >> E.y_coordinate ;
            
            
            
            while ( E.y_coordinate >= grid_length )
                
            {
                
                cout << "Out Of Bounds, please Re-enter";
                
                cin >> E.y_coordinate ;
                
            }
            
            if (E.y_coordinate < 0)
                
                exit = true ;
            
            
            
            cout <<"Enter Ending Metal Layer";
            
            cin >> E.z_coordinate ;
            
            
            
            while (E.z_coordinate > 3 || E.z_coordinate < 1 )
                
            {
                
                cout << "Out Of Bounds, please Re-enter";
                
                cin >>  E.z_coordinate;
                
            }
            
            
            
            if (E.z_coordinate < 0)
                
                exit = true ;
            
            
            
            E.z_coordinate -= 1 ;
            
            
            
        }
        
    }
    
    return exit ;
    
    
    
    
    
    
    
}



void print_number(cell *** Matrix, const int grid_width , const int grid_length)

{
    
    cout << "Matrix 1: \n";
    
    for (int i =0 ;i<grid_length ; i++ )
        
    { for (int j =0 ; j< grid_width ;  j++)
        
    {
        
        cout << Matrix[j][i][0].number  ;
        
        if (Matrix[j][i][0].number > 9)
            
            cout << "  ";
        
        else
            
            cout << "   ";
        
    }
        
        cout << endl ;
        
    }
    
    
    
    cout << "Matrix 2: \n";
    
    for (int i =0 ;i<grid_length ; i++ )
        
    { for (int j =0 ; j< grid_width ;  j++)
        
    {
        
        cout << Matrix[j][i][1].number  ;
        
        if (Matrix[j][i][1].number > 9)
            
            cout << "  ";
        
        else
            
            cout << "   ";
        
    }
        
        cout << endl ;
        
    }
    
    
    
    cout << "Matrix 3: \n";
    
    for (int i =0 ;i<grid_length ; i++ )
        
    { for (int j =0 ; j< grid_width ;  j++)
        
    {
        
        cout << Matrix[j][i][2].number  ;
        
        if (Matrix[j][i][2].number > 9)
            
            cout << "  ";
        
        else
            
            cout << "   ";
        
    }
        
        cout << endl ;
        
    }
    
    
    
    
    
    
    
}



void print_obstacle(cell *** Matrix, const int grid_width , const int grid_length)

{
    
    cout << "Matrix 1: \n";
    
    for (int i =0 ;i<grid_length ; i++ )
        
    { for (int j =0 ; j< grid_width ;  j++)
        
    {
        
        cout << Matrix[j][i][0].obstacle  ;
        
        cout << "   ";
        
    }
        
        cout << endl ;
        
    }
    
    
    
    cout << "Matrix 2: \n";
    
    for (int i =0 ;i<grid_length ; i++ )
        
    { for (int j =0 ; j< grid_width ;  j++)
        
    {
        
        cout << Matrix[j][i][1].obstacle  ;
        
        cout << "   ";
        
    }
        
        cout << endl ;
        
    }
    
    
    
    cout << "Matrix 3: \n";
    
    for (int i =0 ;i<grid_length ; i++ )
        
    { for (int j =0 ; j< grid_width ;  j++)
        
    {
        
        cout << Matrix[j][i][2].obstacle  ;
        
        cout << "   ";
        
    }
        
        cout << endl ;
        
    }
    
    
    
    
    
    
    
    
    
}

